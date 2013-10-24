/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Socket.cpp
*
*	Revision:
*
*	03/27/03
*		- first revision
*	05/19/04
*		- Changed the header include order for Cygwin.
*	05/21/04
*		- Added support for MinGW.
*	08/03/04
*		- Changed SocketCleanup() not to call WSACleanup().
*	08/28/04
*		- Added setTimeout().
*	10/26/04
*		- Brent Hills <bhills@openshores.com>
*		- Changed to ignore SIGPIPE signal.
*	12/17/04
*		- Added support for BTRON
*	12/21/04
*		- Added toSocketAddrInfo() and toSocketAddrIn().
*	02/08/05
*		- Fixed to use INVALID_SOCKET instead of -1 for WIN32.
*
******************************************************************/

#include <cybergarage/net/SocketImp.h>
#include <cybergarage/net/SocketUtil.h>
#include <cybergarage/net/HostInterface.h>
#include <cybergarage/util/Mutex.h>
#include <cybergarage/util/StringUtil.h>

#if !defined(WIN32) && !defined(__CYGWIN__)
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
#include <fcntl.h>
#include <signal.h>
#endif
#endif

using namespace CyberNet;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

const int SocketImp::STREAM = 1;
const int SocketImp::DGRAM = 2;

////////////////////////////////////////////////
//	SocketInit/Close
////////////////////////////////////////////////

static int socketCnt = 0;
static Mutex sockMutex;

#if defined(TENGINE) && defined(TENGINE_NET_KASAGO)
ttUserInterface kaInterfaceHandle;
#endif

void CyberNet::SocketStartup()
{
	sockMutex.lock();
	if (socketCnt == 0) {
#if (defined(WIN32) || defined(__CYGWIN__)) && !defined(ITRON)
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
#elif defined(ITRON) && defined(NORTiAPI)
		tcp_ini();
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
		kaInterfaceHandle = ka_tfAddInterface(HostInterface::DEFAULT_IFNAME);
#endif

#if !defined(WIN32) || defined(__CYGWIN__)
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	// Thanks for Brent Hills (10/26/04)
    signal(SIGPIPE,SIG_IGN);
#endif
#endif
	}
	socketCnt++;
	sockMutex.unlock();
}

void CyberNet::SocketCleanup()
{
	sockMutex.lock();
	socketCnt--;
	if (socketCnt <= 0) {
#if defined(WIN32) || defined(__CYGWIN__)
		//	WSACleanup( );
#endif
#if !defined(WIN32) || defined(__CYGWIN__)
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	// Thanks for Brent Hills (10/26/04)
    signal(SIGPIPE,SIG_DFL);
#endif
#endif
	}
	sockMutex.unlock();
}

////////////////////////////////////////////////
//	Constructor/Destructor
////////////////////////////////////////////////

SocketImp::SocketImp()
{
	SocketStartup();
	setType(0);
	setLocalAddress("");
	setLocalPort(0);
#if (defined(WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__)) && !defined(ITRON)
	setSocket(INVALID_SOCKET);
#else
	setSocket(-1);
#endif
}

SocketImp::~SocketImp()
{
	SocketCleanup();
}

bool SocketImp::isBound()
{
#if (defined(WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__)) && !defined(ITRON)
	return (sock != INVALID_SOCKET) ? true : false;
#else
	return (0 <= sock) ? true : false;
#endif
}

////////////////////////////////////////////////
//	close
////////////////////////////////////////////////

bool SocketImp::close()
{
	if (isBound() == true)
		return true;

#if (defined(WIN32) || defined(__CYGWIN__)) && !defined(ITRON)
	WSAAsyncSelect(sock, NULL, 0, FD_CLOSE);
	shutdown(sock, SD_BOTH );
	closesocket(sock);
	#if !defined(__CYGWIN__) && !defined(__MINGW32__)
	setSocket(INVALID_SOCKET);
	#else
	setSocket(-1);
	#endif
#else
	#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	so_shutdown(sock, 2);
	so_close(sock);
	#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	ka_tfClose(sock);
	#elif defined(ITRON)
	if (getType() == STREAM) {
		tcp_can_cep(sock, TFN_TCP_ALL);
		tcp_sht_cep(sock);
		tcp_del_cep(sock);
		tcp_cls_cep(sock, TMO_FEVR);
		tcp_del_rep(sock);
	}
	else {
		udp_can_cep(sock, TFN_UDP_ALL);
		udp_del_cep(sock);
	}
	#else
	int flag = fcntl(sock, F_GETFL, 0);
	if (0 <= flag)
		fcntl(sock, F_SETFL, flag | O_NONBLOCK);
	shutdown(sock, 2);
	::close(sock);
	#endif
	setSocket(-1);
#endif

	return true;
}

////////////////////////////////////////////////
//	Socket Option
////////////////////////////////////////////////

bool SocketImp::setReuseAddress(bool flag)
{
	int sockOptRet;
#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	B optval = (flag == true) ? 1 : 0;
	sockOptRet = so_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (B *)&optval, sizeof(optval));
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	int optval = (flag == true) ? 1 : 0;
	sockOptRet = ka_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof(optval));
	//printf("setReuseAddress : %d\n", sockOptRet);
#elif defined (ITRON)
	/**** Not Implemented for NORTi ***/
	sockOptRet = -1;
#elif defined (WIN32)
	BOOL optval = (flag == true) ? 1 : 0;
	sockOptRet = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof(optval));
#else
	int optval = (flag == true) ? 1 : 0;
	sockOptRet = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof(optval));
	#ifdef USE_SO_REUSEPORT
	setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (const char *)&optval, sizeof(optval));
	#endif
#endif
	return (sockOptRet == 0) ? true : false;
}

void SocketImp::setTimeout(int timeout)
{
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout));
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
#endif
}

////////////////////////////////////////////////
//	setMulticastInterface
////////////////////////////////////////////////

#if defined(TENGINE) && defined(TENGINE_NET_KASAGO)

bool SocketImp::setMulticastInterface(const char *ifaddr)
{
	NetworkInterfaceList netIfList;

	if (ifaddr == NULL || strlen(ifaddr) <= 0) {
		int netIfCnt = GetHostAddresses(netIfList);
		if (netIfCnt <= 0)
			return false;
		NetworkInterface *netIf = netIfList.getNetworkInterface(0);
		ifaddr = netIf->getAddress();
	}

	struct sockaddr_in sockaddr;
	bool sockAddrSuccess = toSocketAddrIn(ifaddr, 0, &sockaddr, TRUE);
	if (sockAddrSuccess == false)
		return false;

	int optSuccess = ka_setsockopt(sock, IP_PROTOIP, IPO_MULTICAST_IF, (const char *)&sockaddr.sin_addr, sizeof(sockaddr.sin_addr));
	if (optSuccess != 0)
		return false;

	return true;
}

#endif
