/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: MulticastSocket.h
*
*	Revision;
*
*	05/29/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_MULTICASTSOCKET_H_
#define _CNET_MULTICASTSOCKET_H_

#include <cybergarage/net/DatagramSocket.h>
#include <cybergarage/net/InetSocketAddress.h>
#include <cybergarage/net/NetworkInterface.h>

namespace CyberNet {

class MulticastSocket : public DatagramSocket
{

public:

	MulticastSocket();
	MulticastSocket(int port, const char *bindAddr);
	~MulticastSocket();

	bool bind(int port, const char *addr);
	
	bool joinGroup(const char *mcastAddr, const char *ifAddr = NULL);
	bool joinGroup(InetSocketAddress *mcastAddr, NetworkInterface *ifAddr)
	{
		return joinGroup(mcastAddr->getAddress(), ifAddr->getAddress());
	}

	void setTimeToLive(int ttl);
};

}

#endif
