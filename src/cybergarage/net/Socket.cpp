/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2005
*
*	File: Socket.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*	08/01/04
*		- Added <stdio.h> for sprintf() for gcc 2.95.3.
*	10/20/04
*		- Brent Hills <bhills@openshores.com>
*		- Fixed to abort send() when the socket can't write the packet.
*	12/21/04 
*		- Changed accept() to return false when the socket is invalid for WIN32.
*	12/22/04 
*		- Changed listen() to return the result.
*	02/07/05
*		- Changed accept() to set the local address and port.
*	02/26/05
*		- Changed send() to retry when the packet is not sent normally.
*
******************************************************************/

#include <cybergarage/net/Socket.h>
#include <cybergarage/util/StringUtil.h>
#include <cybergarage/util/TimeUtil.h>
#include <cybergarage/net/SocketUtil.h>

#include <stdio.h>

using namespace CyberNet;
using namespace CyberUtil;

#if defined(ITRON)
static ER TcpCallback(ID cepid, FN fncd, VP parblk);
#endif

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

#if defined(ITRON)
const int Socket::WINDOW_BUF_SIZE = 4096;
#endif

////////////////////////////////////////////////
//	Socket
////////////////////////////////////////////////

Socket::Socket()
{
	setType(STREAM);
#if defined(ITRON)
	sendWinBuf = NULL;
	recvWinBuf = NULL;
#endif
}

Socket::~Socket()
{
	close();

#if defined(ITRON)
	delete[] sendWinBuf;
	delete[] recvWinBuf;
#endif
}

////////////////////////////////////////////////
//	listen
////////////////////////////////////////////////

bool Socket::listen()
{
#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	ERR ret = so_listen(sock, 10);
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	ERR ret = ka_listen(sock, 10);
#elif defined(ITRON)
	/**** Not Supported ****/
	int ret = 0;
#else
	int ret = ::listen(sock, SOMAXCONN);
#endif
	return (ret == 0) ? true: false;
}

////////////////////////////////////////////////
//	bind
////////////////////////////////////////////////

bool Socket::bind(int bindPort, const char *bindAddr)
{
	setLocalAddress("");
	setLocalPort(0);

	if (bindPort <= 0 || bindAddr == NULL)
		return false;

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	struct sockaddr_in sockaddr;
	if (toSocketAddrIn(bindAddr, bindPort, &sockaddr) == false)
		return false;
   	sock = so_socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		return false;
	ERR ret = so_bind(sock, (SOCKADDR *)&sockaddr, sizeof(struct sockaddr_in));
	if (ret < 0) {
		close();
		return false;
	}
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	struct sockaddr_in sockaddr;
	if (toSocketAddrIn(bindAddr, bindPort, &sockaddr) == false)
		return false;
	sock = ka_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0)
		return false;
	/*
	if (SetMulticastInterface(bindAddr) == FALSE)
		return FALSE;
	*/
	ERR ret = ka_bind(sock, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr_in));
	if (ret < 0) {
		close();
		return false;
	}
#elif defined(ITRON)
	T_TCP_CREP tcpcrep = { 0, { IPV4_ADDRANY, 0 } };
	T_TCP_CCEP tcpccep = { 0, sendWinBuf, WINDOW_BUF_SIZE, recvWinBuf, WINDOW_BUF_SIZE, (FP)TcpCallback };
	sock = GetAvailableSocketID(STREAM);
	if (sock < 0)
		return false;
	if (bindAddr != NULL)
		tcpcrep.myaddr.ipaddr = ascii_to_ipaddr((B*)bindAddr);
	tcpcrep.myaddr.ipaddr = htons(bindPort);
	if (tcp_cre_rep(sock, &tcpcrep) != E_OK) {
		close();
		return false;
	}
	if (tcp_cre_cep(sock, &tcpccep) != E_OK) {
		close();
		return false;
	}
	int ret = 0;
#else
	struct addrinfo *addrInfo;
	if (toSocketAddrInfo(SOCK_STREAM, bindAddr, bindPort, &addrInfo, true) == false)
		return false;
	sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, 0);
	if (sock == -1) {
		close();
		return false;
	}
	size_t ret = ::bind(sock, addrInfo->ai_addr, addrInfo->ai_addrlen);
	freeaddrinfo(addrInfo);
#endif

	if (ret != 0)
		return false;

	setLocalAddress(bindAddr);
	setLocalPort(bindPort);

	return true;
}

////////////////////////////////////////////////
//	accept
////////////////////////////////////////////////

bool Socket::accept(Socket *socket)
{
	SOCKET clientSock;

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	struct sockaddr_in sockaddr;
	W nLength = sizeof(struct sockaddr_in);
	clientSock = so_accept(sock, (SOCKADDR *)&sockaddr, &nLength);
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	struct sockaddr_in sockaddr;
	int nLength = sizeof(struct sockaddr_in);
	clientSock = ka_accept(sock, (struct sockaddr *)&sockaddr, &nLength);
#elif defined(ITRON)
	T_IPV4EP dstAddr;
	if (tcp_acp_cep(sock, sock, &dstAddr, TMO_FEVR) != E_OK)
		return FALSE;
	clientSock = sock;
#else
	struct sockaddr_storage sockClientAddr;
	socklen_t nLength = sizeof(sockClientAddr);
	clientSock = ::accept(sock, (struct sockaddr *)&sockClientAddr, &nLength);
#endif

#if defined(WIN32) && !defined(ITRON)
	if (clientSock == INVALID_SOCKET)
		return false;
#else
	if (clientSock < 0)
		return false;
#endif

	socket->setSocket(clientSock);
	socket->setLocalAddress(getLocalAddress());
	socket->setLocalPort(getLocalPort());

	return true;
}

////////////////////////////////////////////////
//	connect
////////////////////////////////////////////////

bool Socket::connect(const char *addr, int port)
{
#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	struct sockaddr_in sockaddr;
	if (toSocketAddrIn(addr, port, &sockaddr) == false)
		return false;

	if (isBound() == false)
	   	sock = so_socket(PF_INET, SOCK_STREAM, 0);
		
	ERR ret = so_connect(sock, (SOCKADDR *)&sockaddr, sizeof(sockaddr_in));
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	ERR ret;
	struct sockaddr_in sockaddr;
	if (toSocketAddrIn(addr, port, &sockaddr) == false)
		return false;

	if (isBound() == false)
	   	sock = ka_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	ret = ka_connect(sock, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr_in));
#elif defined(ITRON)
	T_TCP_CCEP tcpccep = { 0, sendWinBuf, WINDOW_BUF_SIZE, recvWinBuf, WINDOW_BUF_SIZE, (FP)TcpCallback };
	T_IPV4EP localAddr;
	T_IPV4EP dstAddr;
	ER ret;
	if (GetAvailableLocalAddress(&localAddr) == FALSE)
		return false;
	if (isBound() == false) {
		initWindowBuffer();
		sock = GetAvailableSocketID(STREAM);
		if (tcp_cre_cep(sock, &tcpccep) != E_OK)
			return false;
	}
	dstAddr.ipaddr = ascii_to_ipaddr((B*)addr);
	dstAddr.portno = htons(port);
	ret = tcp_con_cep(sock, &localAddr, &dstAddr, TMO_FEVR);
	if (ret == E_OK) {
		setLocalAddress(""/*ipaddr_to_ascii(localAddr.ipaddr)*/);
		setLocalPort(ntohs(localAddr.portno));
		ret = 0;
	}
	else 
		ret = -1;
#else
	struct addrinfo *toaddrInfo;
	if (toSocketAddrInfo(SOCK_STREAM, addr, port, &toaddrInfo, true) == false)
		return false;

	if (isBound() == false)
		sock = socket(toaddrInfo->ai_family, toaddrInfo->ai_socktype, 0);

	int ret = ::connect(sock, toaddrInfo->ai_addr, toaddrInfo->ai_addrlen);
	freeaddrinfo(toaddrInfo);
#endif

	return (ret == 0) ? true : false;
}

////////////////////////////////////////////////
//	recv
////////////////////////////////////////////////

int Socket::recv(char *buffer, int bufferLen)
{
	int recvLen;
#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	recvLen = so_recv(sock, buffer, bufferLen, 0);
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	recvLen = ka_recv(sock, buffer, bufferLen, 0);
#elif defined(ITRON)
	recvLen = tcp_rcv_dat(sock, buffer, bufferLen, TMO_FEVR);
#else
	recvLen = ::recv(sock, buffer, bufferLen, 0);
#endif
	return recvLen;
}


////////////////////////////////////////////////
//	send
////////////////////////////////////////////////

const int CG_NET_SOCKET_SEND_RETRY_CNT = 10;
const int CG_NET_SOCKET_SEND_RETRY_WAIT_MSEC = 1000;

int Socket::send(const char *cmd, int cmdLen)
{
	if (cmdLen <= 0)
		return 0;
	int nTotalSent = 0;
	int cmdPos = 0;
	int retryCnt = 0;
	do {
#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
		WERR nSent = so_send(sock, (B*)(cmd + cmdPos), cmdLen, 0);
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
		int nSent = ka_send(sock, (B*)(cmd + cmdPos), cmdLen, 0);
#elif defined(ITRON)
		int nSent = tcp_snd_dat(sock, cmd + cmdPos, cmdLen, TMO_FEVR);
#else
		int nSent = ::send(sock, cmd + cmdPos, cmdLen, 0);
#endif
		// Thanks for Brent Hills (10/20/04)
		if (nSent <= 0)  {
			retryCnt++;
			if (CG_NET_SOCKET_SEND_RETRY_CNT < retryCnt)
				break;
			WaitRandom(CG_NET_SOCKET_SEND_RETRY_WAIT_MSEC);
			continue;
		}
		nTotalSent += nSent;
		cmdPos += nSent;
		cmdLen -= nSent;
		retryCnt = 0;
	} while (0 < cmdLen);
	return nTotalSent;
}

int Socket::send(const char *cmd)
{
	return send(cmd, StringLength(cmd));
}

////////////////////////////////////////////////
//	initWindowBuffer (ITRON)
////////////////////////////////////////////////

#if defined(ITRON)

void Socket::initWindowBuffer()
{
#if defined(ITRON)
	if (sendWinBuf == NULL)
		sendWinBuf = new UH[WINDOW_BUF_SIZE];
	if (recvWinBuf == NULL)
		recvWinBuf = new UH[WINDOW_BUF_SIZE];
#endif
}

#endif

////////////////////////////////////////////////
//	TcpCallback (ITRON)
////////////////////////////////////////////////

#if defined(ITRON)

static ER TcpCallback(ID cepid, FN fncd, VP parblk)
{
    return E_OK;
}

#endif
