/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SocketImp.h
*
*	Revision;
*
*	08/26/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_SOCKETIMP_H_
#define _CNET_SOCKETIMP_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#if defined(WIN32) && defined(ITRON) && defined (_AFXDLL)
#include <afxwin.h>
#endif

#if (defined(WIN32) || defined(__CYGWIN__)) && !defined(ITRON)
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined(BTRON) || defined(TENGINE) 
#include <typedef.h>
#elif defined(ITRON)
#include <kernel.h>
#endif

#include <string>

#ifndef HAVE_SOCKLEN_T
typedef int socklen_t;
#endif

#if (!defined(WIN32) && !defined(__CYGWIN__)) || defined(ITRON)
#if defined(BTRON) || defined(TENGINE) 
typedef W SOCKET;
#elif defined(ITRON)
typedef ER SOCKET;
#else
typedef int SOCKET;
#endif
#endif

namespace CyberNet {

class SocketImp
{
private:

	int type;
	std::string localAddr;
	int localPort;

public:

	SOCKET	sock;

public:

	SocketImp();
	~SocketImp();

	////////////////////////////////////////////////
	//	Socket
	////////////////////////////////////////////////

public:

	static const int STREAM;
	static const int DGRAM;

	////////////////////////////////////////////////
	//	Socket
	////////////////////////////////////////////////
	
public:

	void setSocket(SOCKET value)
	{
		sock = value;
	}

	SOCKET getSocket()
	{
		return sock;
	}

	////////////////////////////////////////////////
	// bind
	////////////////////////////////////////////////
	
public:

	bool isBound();
	
	////////////////////////////////////////////////
	// close
	////////////////////////////////////////////////

public:
	
	bool close();
	
	////////////////////////////////////////////////
	//	Local address/port
	////////////////////////////////////////////////

public:

	void setLocalAddress(const char *addr)
	{
		localAddr = (addr != NULL) ? addr : "";
		//StripIPv6ScopeID(addr, localAddr);
	}

	const char *getLocalAddress()
	{
		return localAddr.c_str();
	}

	void setLocalPort(int port)
	{
		localPort = port;
	}

	int getLocalPort()
	{
		return localPort;
	}

	////////////////////////////////////////////////
	// Type
	////////////////////////////////////////////////

protected:
	
	void setType(int value)
	{
		type = value;
	}

public:

	int getType()
	{
		return type;
	}

	////////////////////////////////////////////////
	//	Socket Option
	////////////////////////////////////////////////

public:

	bool setReuseAddress(bool on);
	void setTimeout(int timeout);

	#if defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	bool setMulticastInterface(const char *ifaddr);
	#endif
};

void SocketStartup();
void SocketCleanup();

}

#endif
