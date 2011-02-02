/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPMUSocket.cpp
*
*	Revision;
*
*	07/01/03
*		- first revision
*	11/19/04
*		- Theo Beisch <theo.beisch@gmx.de>
*		- Changed send() to set the TTL as 4.
*
******************************************************************/

#include <time.h>
#include <cybergarage/net/HostInterface.h>
#include <cybergarage/upnp/ssdp/HTTPMUSocket.h>

using namespace CyberLink;
using namespace CyberNet;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////
	
HTTPMUSocket::HTTPMUSocket()
{
}

HTTPMUSocket::HTTPMUSocket(const char *addr, int port, const char *bindAddr)
{
	open(addr, port, bindAddr);
}

////////////////////////////////////////////////
//	Destructor
////////////////////////////////////////////////

HTTPMUSocket::~HTTPMUSocket()
{
	close();
}

////////////////////////////////////////////////
//	open/close
////////////////////////////////////////////////

bool HTTPMUSocket::open(const char *addr, int port, const char *bindAddr)
{
	ssdpMultiGroup.setAddress(addr);
	ssdpMultiGroup.setPort(port);
	//ssdpMultiIf.setAddress(bindAddr);

	const char *msockBindAddr = bindAddr;
	if (ssdpMultiSock.bind(port, msockBindAddr) == false)
		return false;
	if (ssdpMultiSock.joinGroup(addr, bindAddr) == false) {
		ssdpMultiSock.close();
		return false;
	}		

	return true;
}

bool HTTPMUSocket::close()
{
	if (ssdpMultiSock.close() == false)
		return false;
	return true;
}

////////////////////////////////////////////////
//	reveive
////////////////////////////////////////////////

bool HTTPMUSocket::send(const char *msg, const char *bindAddr, int bindPort)
{
	MulticastSocket msock;
	if ((bindAddr != NULL) && (0 < bindPort))
			msock.bind(bindPort, bindAddr);
	DatagramPacket dgmPacket(msg, &ssdpMultiGroup);
	// Thnaks for Tho Beisch (11/09/04)
	msock.setTimeToLive(4);
	msock.send(&dgmPacket);
	return true;
}

////////////////////////////////////////////////
//	reveive
////////////////////////////////////////////////

SSDPPacket *HTTPMUSocket::receive()
{
	recvPacket.setLocalAddress(getLocalAddress());
	int nRecv = ssdpMultiSock.receive(recvPacket.getDatagramPacket());
	if (nRecv == 0)
		return NULL;
	recvPacket.setTimeStamp(time(NULL));
	return &recvPacket;
}
