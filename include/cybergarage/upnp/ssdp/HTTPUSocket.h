/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPUSocket.h
*
*	Revision;
*
*	06/05/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_HTTPUSOCKET_H_
#define _CLINK_HTTPUSOCKET_H_

#include <cybergarage/net/DatagramSocket.h>
#include <cybergarage/upnp/ssdp/SSDPPacket.h>

namespace CyberLink {

class HTTPUSocket 
{

	CyberNet::DatagramSocket ssdpUniSock;
	SSDPPacket recvPacket;

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	HTTPUSocket();
	
	HTTPUSocket(const char *bindAddr, int port);

	~HTTPUSocket();

	////////////////////////////////////////////////
	//	open
	////////////////////////////////////////////////
	
	bool open(int bindPort = -1, const char *bindAddr = "");

	////////////////////////////////////////////////
	//	close
	////////////////////////////////////////////////

	bool close();

	////////////////////////////////////////////////
	//	DatagramSocket
	////////////////////////////////////////////////

	CyberNet::DatagramSocket &getDatagramSocket()
	{
		return ssdpUniSock;
	}

	////////////////////////////////////////////////
	//	bindAddr
	////////////////////////////////////////////////

	const char *getLocalAddress()
	{
		return ssdpUniSock.getLocalAddress();
	}

	////////////////////////////////////////////////
	//	post/receive
	////////////////////////////////////////////////
	
	bool post(const char *addr, int port, const char *msg);
	SSDPPacket *receive();

};

}

#endif


