/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ServerSocket.h
*
*	Revision;
*
*	04/13/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_SERVERSOCKET_H_
#define _CNET_SERVERSOCKET_H_

#include <cybergarage/net/Socket.h>

namespace CyberNet {

class ServerSocket : public Socket
{
public:

	ServerSocket();
	~ServerSocket();

};

}

#endif
