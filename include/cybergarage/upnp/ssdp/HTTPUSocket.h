<<<<<<< HEAD
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

#include <uhttp/net/DatagramSocket.h>
#include <cybergarage/upnp/ssdp/SSDPPacket.h>

namespace CyberLink {

class HTTPUSocket 
{

	uHTTP::DatagramSocket ssdpUniSock;
	SSDPPacket recvPacket;

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	HTTPUSocket();
	
	HTTPUSocket(const std::string &bindAddr, int port);

	~HTTPUSocket();

	////////////////////////////////////////////////
	//	open
	////////////////////////////////////////////////
	
	bool open(int bindPort = -1, const std::string &bindAddr = "");

	////////////////////////////////////////////////
	//	close
	////////////////////////////////////////////////

	bool close();

	////////////////////////////////////////////////
	//	DatagramSocket
	////////////////////////////////////////////////

	uHTTP::DatagramSocket &getDatagramSocket()
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
	
	bool post(const std::string &addr, int port, const std::string &msg);
	SSDPPacket *receive();

};

}

#endif


=======
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


>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
