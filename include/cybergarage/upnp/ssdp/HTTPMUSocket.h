/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPMUSocket.h
*
*	Revision;
*
*	07/01/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_HTTPMUSOCKET_H_
#define _CLINK_HTTPMUSOCKET_H_

#include <cybergarage/net/MulticastSocket.h>
#include <cybergarage/net/InetSocketAddress.h>
#include <cybergarage/net/NetworkInterface.h>
#include <cybergarage/http/HTTPRequest.h>
#include <cybergarage/upnp/ssdp/SSDPPacket.h>

namespace CyberLink {

class HTTPMUSocket
{
	CyberNet::InetSocketAddress ssdpMultiGroup;
	CyberNet::MulticastSocket ssdpMultiSock;
	//CyberNet::NetworkInterface ssdpMultiIf;
	SSDPPacket recvPacket;

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	HTTPMUSocket();
	
	HTTPMUSocket(const char *addr, int port, const char *bindAddr);

	~HTTPMUSocket();

	////////////////////////////////////////////////
	//	bindAddr
	////////////////////////////////////////////////

	const char *getLocalAddress()
	{
		return ssdpMultiSock.getLocalAddress();
	}

	////////////////////////////////////////////////
	//	open/close
	////////////////////////////////////////////////

	bool open(const char *addr, int port, const char *bindAddr);
	bool close();

	////////////////////////////////////////////////
	//	send
	////////////////////////////////////////////////

	bool send(const char *msg, const char *bindAddr = "", int bindPort = -1);

	////////////////////////////////////////////////
	//	post (HTTPRequest)
	////////////////////////////////////////////////

	bool post(CyberHTTP::HTTPRequest *req, const char *bindAddr, int bindPort)
	{
		std::string reqStr;
		return send(req->toString(reqStr), bindAddr, bindPort);
	}

	bool post(CyberHTTP::HTTPRequest *req)
	{
		std::string reqStr;
		return send(req->toString(reqStr));
	}

	////////////////////////////////////////////////
	//	reveive
	////////////////////////////////////////////////

	SSDPPacket *receive();
};

}

#endif


