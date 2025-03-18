/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HostInterface.h
*
*	Revision;
*
*	05/18/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_HOSTINTERFACE_H_
#define _CNET_HOSTINTERFACE_H_

#include <cybergarage/net/Socket.h>
#include <cybergarage/net/NetworkInterfaceList.h>

#include <string>

namespace CyberNet {

class HostInterface {
public:
	static bool USE_LOOPBACK_ADDR;
	static bool USE_ONLY_IPV4_ADDR;
	static bool USE_ONLY_IPV6_ADDR;
	const static char *DEFAULT_IFNAME;
};

int GetNHostAddresses();
const char *GetHostAddress(int n, std::string &buf);
int GetHostAddresses(NetworkInterfaceList &netifList);

bool IsIPv6Address(const char *host);
const char *StripIPv6ScopeID(const char *addr, std::string &buf);
int GetIPv6ScopeID(const char *addr);
bool HasIPv4Addresses();
bool HasIPv6Addresses();

void SetHostInterface(const char *ifaddr);
const char *GetHostInterface();
bool HasAssignedHostInterface();

}

#endif
