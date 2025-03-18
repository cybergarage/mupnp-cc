/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_SOCKETUTIL_H_
#define _UHTTP_NET_SOCKETUTIL_H_

#include <mupnp/platform.h>

#include <string.h>

#if defined(WIN32) && defined(ITRON) && defined(_AFXDLL)
#include <afxwin.h>
#endif

#if (defined(WIN32) || defined(__CYGWIN__)) && !defined(ITRON)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
#include <btron/bsocket.h>
#include <net/sock_com.h>
#include <string.h> //for mem___()
#include <typedef.h>
#elif defined(ITRON)
#include <kernel.h>
#if defined(NORTiAPI)
#include <nonet.h>
#endif
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
#include <btron/kasago.h>
#include <string.h> //for mem___()
#include <sys/svc/ifkasago.h>
#include <tk/tkernel.h>
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#endif

#if defined(ITRON)
#define USE_SOCKET_LIST 1
#endif

namespace uHTTP {
int GetSocketLastErrorCode();
const char* DecodeSocketError(int ErrorCode);

bool toSocketAddrIn(const std::string& addr, int port, struct sockaddr_in* sockaddr, bool isBindAddr = true);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
bool toSocketAddrInfo(int sockType, const std::string& addr, int port, struct addrinfo** addrInfo, bool isBindAddr = true);
#endif

#if defined(USE_SOCKET_LIST)
int GetAvailableSocketID(int type);
int GetAvailableSocketPort();
#endif

#if defined(ITRON)
BOOL GetAvailableLocalAddress(T_IPV4EP* localAddr);
#endif

}

#endif
