/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SocketUtil.h
*
*	Revision;
*
*	08/26/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_SOCKETUTIL_H_
#define _CNET_SOCKETUTIL_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#if defined(WIN32) && defined(ITRON) && defined (_AFXDLL)
#include <afxwin.h>
#endif

#if (defined(WIN32) || defined(__CYGWIN__)) && !defined (ITRON)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
#include <typedef.h>
#include <net/sock_com.h>
#include <btron/bsocket.h>
#include <string.h> //for mem___()
#elif defined(ITRON)
#include <kernel.h>
	#if defined(NORTiAPI)
	#include <nonet.h>
	#endif
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
#include <tk/tkernel.h>
#include <btron/kasago.h>
#include <sys/svc/ifkasago.h>
#include <string.h> //for mem___()
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#endif

#if defined(ITRON)
#define USE_SOCKET_LIST 1
#endif

namespace CyberNet {

int GetSocketLastErrorCode();
const char *DecodeSocketError(int ErrorCode);

bool toSocketAddrIn(const char *addr, int port, struct sockaddr_in *sockaddr, bool isBindAddr = true);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
bool toSocketAddrInfo(int sockType, const char *addr, int port, struct addrinfo **addrInfo, bool isBindAddr = true);
#endif

#if defined(USE_SOCKET_LIST)
int GetAvailableSocketID(int type);
int GetAvailableSocketPort();
#endif

#if defined(ITRON)
BOOL GetAvailableLocalAddress(T_IPV4EP *localAddr);
#endif

}

#endif

