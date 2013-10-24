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
<<<<<<< HEAD
*	11/19/04
*		- Theo Beisch <theo.beisch@gmx.de>
*		- Changed send() to set the TTL as 4.
=======
*	11/19/04
*		- Theo Beisch <theo.beisch@gmx.de>
*		- Changed send() to set the TTL as 4.
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
*
******************************************************************/

#include <time.h>
<<<<<<< HEAD
#include <uhttp/net/HostInterface.h>
#include <cybergarage/upnp/ssdp/HTTPMUSocket.h>

using namespace CyberLink;
using namespace uHTTP;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////
	
HTTPMUSocket::HTTPMUSocket()
{
}

HTTPMUSocket::HTTPMUSocket(const std::string &addr, int port, const std::string &bindAddr)
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
=======
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
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

////////////////////////////////////////////////
//	open/close
////////////////////////////////////////////////

<<<<<<< HEAD
bool HTTPMUSocket::open(const std::string &addr, int port, const std::string &bindAddr)
{
	ssdpMultiGroup.setAddress(addr);
	ssdpMultiGroup.setPort(port);
	//ssdpMultiIf.setAddress(bindAddr);

	const char *msockBindAddr = bindAddr.c_str();
=======
bool HTTPMUSocket::open(const char *addr, int port, const char *bindAddr)
{
	ssdpMultiGroup.setAddress(addr);
	ssdpMultiGroup.setPort(port);
	//ssdpMultiIf.setAddress(bindAddr);

	const char *msockBindAddr = bindAddr;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	if (ssdpMultiSock.bind(port, msockBindAddr) == false)
		return false;
	if (ssdpMultiSock.joinGroup(addr, bindAddr) == false) {
		ssdpMultiSock.close();
		return false;
<<<<<<< HEAD
	}		
=======
	}		
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

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

<<<<<<< HEAD
bool HTTPMUSocket::send(const std::string &msg, const std::string &bindAddr, int bindPort)
{
	MulticastSocket msock;
	if ((0 < bindAddr.length()) && (0 < bindPort))
			msock.bind(bindPort, bindAddr);
	DatagramPacket dgmPacket(msg, &ssdpMultiGroup);
	// Thnaks for Tho Beisch (11/09/04)
	msock.setTimeToLive(4);
	msock.send(&dgmPacket);
=======
bool HTTPMUSocket::send(const char *msg, const char *bindAddr, int bindPort)
{
	MulticastSocket msock;
	if ((bindAddr != NULL) && (0 < bindPort))
			msock.bind(bindPort, bindAddr);
	DatagramPacket dgmPacket(msg, &ssdpMultiGroup);
	// Thnaks for Tho Beisch (11/09/04)
	msock.setTimeToLive(4);
	msock.send(&dgmPacket);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
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
