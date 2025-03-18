/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SocketUtil.cpp
*
*	Revision:
*
*	03/27/03
*		- first revision
*	12/17/04
*		- Added support for BTRON
*	12/21/04
*		- Added toSocketAddrInfo() and toSocketAddrIn().
*	01/07/05
*		- Changed from GetLastErrorCode to GetSocketLastErrorCode().
*		- Changed from DecodeError to DecodeSocketError();
*
******************************************************************/

#include <stdio.h>
#include <string.h>

#include <cybergarage/net/SocketImp.h>
#include <cybergarage/net/SocketUtil.h>

using namespace CyberNet;

////////////////////////////////////////////////
//	DecodeError
////////////////////////////////////////////////

int CyberNet::GetSocketLastErrorCode()
{
#if (defined(WIN32) || defined(__CYGWIN__)) && !defined(ITRON)
	return WSAGetLastError();
#else
	return 0;
#endif
}

const char *CyberNet::DecodeSocketError(int ErrorCode)
{
	static char msg[1024];

#if defined(WIN32) || defined(__CYGWIN__)
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_MAX_WIDTH_MASK,
		NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)msg, 1024, NULL);
#else
	msg[0] = '\0';
#endif
	return msg;
}

////////////////////////////////////////////////
//	toSocketAddrIn
////////////////////////////////////////////////

#if !defined(ITRON)

bool CyberNet::toSocketAddrIn(const char *addr, int port, struct sockaddr_in *sockaddr, bool isBindAddr)
{
	SocketStartup();

	memset(sockaddr, 0, sizeof(sockaddr_in));

#if defined(TENGINE) && defined(TENGINE_NET_KASAGO)
	sockaddr->sin_family = AF_INET;
	sockaddr->sin_addr.s_addr = ka_htonl(INADDR_ANY);
	sockaddr->sin_port = ka_htons((unsigned short)port);
#else
	sockaddr->sin_family = AF_INET;
	sockaddr->sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr->sin_port = htons((unsigned short)port);
#endif

	if (isBindAddr == true) {
#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
		sockaddr->sin_addr.s_addr = inet_addr(addr);
		if (sockaddr->sin_addr.s_addr == -1 /*INADDR_NONE*/) {
			struct hostent hent;
			B hostBuf[HBUFLEN];
			if (so_gethostbyname((B*)addr, &hent, hostBuf) != 0)
				return false;
			memcpy(&(sockaddr->sin_addr), hent.h_addr, hent.h_length);
		}
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
		sockaddr->sin_addr.s_addr = ka_inet_addr((char *)addr);
#else
		sockaddr->sin_addr.s_addr = inet_addr(addr);
		if (sockaddr->sin_addr.s_addr == INADDR_NONE) {
			struct hostent *hent = gethostbyname(addr);
			if (hent == NULL)
				return false;
			memcpy(&(sockaddr->sin_addr), hent->h_addr, hent->h_length);
		}
#endif
	}

	return true;
}

#endif

////////////////////////////////////////////////
//	toSocketAddrInfo
////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 

bool CyberNet::toSocketAddrInfo(int sockType, const char *addr, int port, struct addrinfo **addrInfo, bool isBindAddr)
{
	SocketStartup();

	struct addrinfo hints;

	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_socktype = sockType;
	hints.ai_flags= AI_NUMERICHOST | AI_PASSIVE;
	char portStr[32];
	sprintf(portStr, "%d", port);
	if (getaddrinfo(addr, portStr, &hints, addrInfo) != 0)
		return false;
	if (isBindAddr == true)
		return true;
	hints.ai_family = (*addrInfo)->ai_family;
	freeaddrinfo(*addrInfo);
	if (getaddrinfo(NULL, portStr, &hints, addrInfo) != 0)
		return false;
	return true;
 }

#endif
