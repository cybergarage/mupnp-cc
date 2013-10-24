/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: DatagramSocket.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*	08/01/04
*		- Added <stdio.h> for sprintf() for gcc 2.95.3.
*	09/06/05
*		- Thanks for Roland Moser <rmoser@gmx.at>
*		- Changed bind() because
*		 when trying to run two ControlPoints on the same 
*		 computer, notification doesn't work. The problem is, 
*		 that the ControlPoint tries to bind the same port 
*		 twice and returns before setting the local address 
*		 and port. Consequently the device doesn't know where 
*		 to send the notifications
*
******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <cybergarage/net/Socket.h>
#include <cybergarage/net/DatagramSocket.h>
#include <cybergarage/net/DatagramPacket.h>
#include <cybergarage/net/SocketUtil.h>

using namespace CyberNet;

const int DGRAM_SOCKET_RECV_BUFSIZE = 512;

#if defined(ITRON)
static ER UdpCallback(ID cepid, FN fncd, VP parblk);
static ER TcpCallback(ID cepid, FN fncd, VP parblk);
#endif

////////////////////////////////////////////////
//	DatagramSocket
////////////////////////////////////////////////

DatagramSocket::DatagramSocket()
{
	setType(DGRAM);
}

DatagramSocket::DatagramSocket(int port, const char *bindAddr, bool bindAddrFlag, bool reuseAddrFlag)
{
	setType(DGRAM);
	bind(port, bindAddr, bindAddrFlag, reuseAddrFlag);
}

DatagramSocket::~DatagramSocket()
{
	close();
}

////////////////////////////////////////////////
//	bind
////////////////////////////////////////////////

bool DatagramSocket::bind(int bindPort, const char *bindAddr, bool bindAddrFlag, bool reuseAddrFlag)
{
	setLocalAddress("");
	setLocalPort(0);

	if (bindPort <= 0 || bindAddr == NULL)
		return false;

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	struct sockaddr_in sockaddr;
	if (toSocketAddrIn(bindAddr, bindPort, &sockaddr) == false)
		return false;
   	sock = so_socket(PF_INET, SOCK_DGRAM, 0);
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	struct sockaddr_in sockaddr;
	if (toSocketAddrIn(bindAddr, bindPort, &sockaddr) == false)
		return false;
	ERR sock = ka_socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#elif defined(ITRON)
	sock = GetAvailableSocketID(STREAM);
#else
	struct addrinfo *addrInfo;
	if (toSocketAddrInfo(SOCK_DGRAM, bindAddr, bindPort, &addrInfo, bindAddrFlag) == false)
		return false;
	sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, 0);
#endif

	if (sock < 0)
		return false;
	
	if (reuseAddrFlag == true)
		setReuseAddress(true);

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	ERR ret = so_bind(sock, (SOCKADDR *)&sockaddr, sizeof(struct sockaddr_in));
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	ERR ret = ka_bind(sock, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr_in));
#elif defined(ITRON)
	T_UDP_CCEP udpccep = { 0, { IPV4_ADDRANY, UDP_PORTANY }, (FP)UdpCallback };
	if (bindAddr != NULL)
		udpccep.myaddr.ipaddr = ascii_to_ipaddr((B*)bindAddr);
	udpccep.myaddr.ipaddr = htons(bindPort);
	ER ret = udp_cre_cep(sock, &udpccep);
	if (ret != E_OK) {
		close();
		return false;
	}
#else
	int ret = ::bind(sock, addrInfo->ai_addr, addrInfo->ai_addrlen);
	freeaddrinfo(addrInfo);
#endif

	setLocalAddress(bindAddr);
	setLocalPort(bindPort);

	// Thanks for Roland Moser (09/06/05)
	if (ret != 0)
		return false;

	return true;
}

////////////////////////////////////////////////
//	recv
////////////////////////////////////////////////

int DatagramSocket::receive(DatagramPacket &dataPack)
{
	dataPack.setAddress("");
	dataPack.setPort(0);

	char recvBuf[DGRAM_SOCKET_RECV_BUFSIZE+1];

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	struct sockaddr_in from;
	W fromLen = sizeof(sockaddr_in);
	int recvLen = so_recvfrom(sock, recvBuf, sizeof(recvBuf)-1, 0, (struct sockaddr *)&from, &fromLen);
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	struct sockaddr_in from;
	int fromLen = sizeof(from);
	int recvLen = ka_recvfrom(sock, recvBuf, sizeof(recvBuf)-1, 0, (struct sockaddr *)&from, &fromLen);
#elif defined(ITRON)
	T_IPV4EP remoteHost;
	int recvLen = udp_rcv_dat(sock, &remoteHost, recvBuf, sizeof(recvBuf)-1, TMO_FEVR);
#else
	struct sockaddr_storage from;
	socklen_t fromLen = sizeof(from);
	int recvLen = ::recvfrom(sock, recvBuf, sizeof(recvBuf)-1, 0, (struct sockaddr *)&from, &fromLen);
#endif

	if (recvLen <= 0)
		return 0;
	recvBuf[recvLen] = '\0';
	dataPack.setData(recvBuf);

	dataPack.setAddress("");
	dataPack.setPort(0);

	char remoteAddr[32];
	char remotePort[32];

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	dataPack.setAddress(inet_ntoa(from.sin_addr));
	dataPack.setPort(ntohl(from.sin_port));
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	ka_tfInetToAscii((unsigned long)from.sin_addr.s_addr, remoteAddr);
	dataPack.setAddress(remoteAddr);
	dataPack.setPort(ka_ntohl(from.sin_port));
#elif defined(ITRON)
	ipaddr_to_ascii((B*)remoteAddr, remoteHost.ipaddr);
	dataPack.setAddress(remoteAddr);
	dataPack.setPort(ntohs(remoteHost.portno));
#else
	int ret = getnameinfo((struct sockaddr *)&from, fromLen, remoteAddr, sizeof(remoteAddr), remotePort, sizeof(remotePort), NI_NUMERICHOST | NI_NUMERICSERV);
	if (ret == 0) {
		dataPack.setAddress(remoteAddr);
		dataPack.setPort(atol(remotePort));
	}
#endif

	return recvLen;
}

////////////////////////////////////////////////
//	send
////////////////////////////////////////////////

int DatagramSocket::send(const char *addr, int port, const char *data, int dataLen)
{
	if (data == NULL)
		return 0;
	if (dataLen < 0)
		dataLen = strlen(data);
	if (data <= 0)
		return 0;

	bool isBoundFlag = isBound();

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
	struct sockaddr_in sockaddr;
	if (toSocketAddrIn(addr, port, &sockaddr, true) == false)
		return 0;

	if (isBoundFlag == false)
	   	sock = so_socket(PF_INET, SOCK_DGRAM, 0);

	if (sock < 0)
		return -1;

	int sentLen = so_sendto(sock, (B*)data, dataLen, 0, (SOCKADDR*)&sockaddr, sizeof(sockaddr_in));
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	struct sockaddr_in sockaddr;
	if (toSocketAddrIn(addr, port, &sockaddr, true) == false)
		return 0;

	if (isBoundFlag == FALSE) {
	   	sock = ka_socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
		setMulticastInterface(NULL);
	}

	if (sock < 0)
		return -1;
	int sentLen = ka_sendto(sock, (char *)data, dataLen, 0, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr_in));
#elif defined(ITRON)
	if (isBoundFlag == FALSE) {
		sock = GetAvailableSocketID(DGRAM);
		if (sock < 0)
			return FALSE;
		T_UDP_CCEP udpccep = { 0, { IPV4_ADDRANY, UDP_PORTANY }, (FP)UdpCallback };
		if (udp_cre_cep(sock, &udpccep) != E_OK)
			return FALSE;
	}
	T_IPV4EP dstaddr;
	dstaddr.ipaddr = ascii_to_ipaddr((B*)addr);
	dstaddr.portno = htons(port);
	int sentLen = udp_snd_dat(sock, &dstaddr, data, dataLen, TMO_FEVR);
#else
	struct addrinfo *addrInfo;
	if (toSocketAddrInfo(SOCK_DGRAM, addr, port, &addrInfo, true) == false)
		return false;

	if (isBoundFlag == false)
		sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, 0);

	if (sock < 0)
		return -1;

	int sentLen = ::sendto(sock, data, dataLen, 0, addrInfo->ai_addr, addrInfo->ai_addrlen);
#endif

	if (isBoundFlag == false)
		close();

	return sentLen;
}

int DatagramSocket::send(DatagramPacket *dataPack)
{
	InetSocketAddress *sockAddr = dataPack->getSocketAddress();
	return send(sockAddr->getAddress(), sockAddr->getPort(), dataPack->getData());
}

////////////////////////////////////////////////
//	UdpCallback (ITRON)
////////////////////////////////////////////////

#if defined(ITRON)

static ER UdpCallback(ID cepid, FN fncd, VP parblk)
{
    return E_OK;
}

#endif
