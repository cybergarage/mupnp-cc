/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HostInterface.cpp
*
*	Revision;
*
*	05/18/03
*		- first revision
*	03/10/04
*		- Added the following methods to set only a interface.
*		- SetHostInterface(), GetHostInterface(), HasAssignedHostInterface()
*	05/19/04
*		- Changed the header include order for Cygwin.
*		- Added NOUSE_WIN32_GETHOSTADDRESSES define for Cygwin.
*	05/21/04
*		- Added support for MinGW.
*	08/02/04
*		- Added GetHostAddresses() using ioctl for UNIX platforms.
*	12/27/04
*		- Added support for BTRON.
*	05/27/05
*		- Added support for gcc 4.0.
*	01/15/06
*		- Thanks for Tobias.Gansen (Tobias.Gansen@lineas.de)
*		- Changed cg_net_gethostinterfaces() not to bind the MAC address interface on QNX platform.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>

#include <cybergarage/net/Socket.h>
#include <cybergarage/net/HostInterface.h>
#include <cybergarage/net/NetworkInterfaceList.h>
#include <cybergarage/net/SocketUtil.h>
#include <cybergarage/util/StringUtil.h>

#if (defined(WIN32) || defined(__CYGWIN__)) && !defined(ITRON)
	#include <Iptypes.h>
	#include <Iphlpapi.h>
#elif !defined(BTRON) && !defined(TENGINE) && !defined(ITRON)
	#include <sys/socket.h>
	#include <net/if.h>
	#if defined(HAVE_IFADDRS_H)
	#include <netdb.h>
	#include <ifaddrs.h>
	#else
	#include <sys/ioctl.h>
	#endif
#endif

#include <iostream>
#include <sstream>

using namespace std;
using namespace CyberNet;
using namespace CyberUtil;

bool CyberNet::HostInterface::USE_LOOPBACK_ADDR = false;
bool CyberNet::HostInterface::USE_ONLY_IPV4_ADDR = false;
bool CyberNet::HostInterface::USE_ONLY_IPV6_ADDR = false;

#if defined(BTRON) || defined(TENGINE)
const char *CyberNet::HostInterface::DEFAULT_IFNAME = "Neta";
#endif

#if defined(TENGINE) && defined(TENGINE_NET_KASAGO)
extern ttUserInterface kaInterfaceHandle;
#endif

////////////////////////////////////////////////
//	GetNHostAddresses
////////////////////////////////////////////////

int CyberNet::GetNHostAddresses()
{
	if (HasAssignedHostInterface() == true)
		return 1;

	NetworkInterfaceList netIfList;
	return GetHostAddresses(netIfList);
}

const char *CyberNet::GetHostAddress(int n, std::string &buf)
{
	if (HasAssignedHostInterface() == true)
		return GetHostInterface();

	NetworkInterfaceList netIfList;
	int ifNum = GetHostAddresses(netIfList);
	if (0 < ifNum || n < ifNum) {
		NetworkInterface *netif = netIfList.getNetworkInterface(n);
		buf = netif->getAddress();
	}
	else
		buf = "";
	return buf.c_str();
}

static bool IsUseAddress(const char *host)
{
	if (CyberNet::HostInterface::USE_ONLY_IPV6_ADDR == true) {
		if (IsIPv6Address(host) == false)
			return false;
	}
	if (CyberNet::HostInterface::USE_ONLY_IPV4_ADDR == true) {
		if (IsIPv6Address(host) == true)
			return false;
	}
	return true;
}

////////////////////////////////////////////////
//	GetHostAddresses (WIN32)
////////////////////////////////////////////////

#if (defined(WIN32) || defined(__CYGWIN__)) && !defined(ITRON)

#if defined(__CYGWIN__) || defined(__MINGW32__)
#define NOUSE_WIN32_GETHOSTADDRESSES 1
#endif

int CyberNet::GetHostAddresses(NetworkInterfaceList &netIfList)
{
	SocketStartup();

	netIfList.clear();

#ifdef NOUSE_WIN32_GETHOSTADDRESSES

	SOCKET sd = WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
	if (sd == SOCKET_ERROR)
		return 0;

	INTERFACE_INFO InterfaceList[20];
	unsigned long nBytesReturned;
	if (WSAIoctl(sd, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList, sizeof(InterfaceList), &nBytesReturned, 0, 0) == SOCKET_ERROR)
		return 0;

	int nNumInterfaces = nBytesReturned / sizeof(INTERFACE_INFO);
    for (int i = 0; i < nNumInterfaces; ++i) {
        sockaddr_in *pAddress = (sockaddr_in *) & (InterfaceList[i].iiAddress);
		char *host = inet_ntoa(pAddress->sin_addr);
		u_long nFlags = InterfaceList[i].iiFlags;
		if (CyberNet::HostInterface::USE_LOOPBACK_ADDR == false) {
			if (nFlags & IFF_LOOPBACK)
				continue;
		}
		if (!(nFlags & IFF_UP))
			continue;
		if (IsUseAddress(host) == false)
			continue;
		NetworkInterface *netIf = new NetworkInterface(host);
		netIfList.add(netIf);
	}

#else

	IP_ADAPTER_ADDRESSES *pAdapterAddresses, *ai;
	DWORD ifFlags = 
		GAA_FLAG_SKIP_ANYCAST | 
		GAA_FLAG_SKIP_FRIENDLY_NAME | 
		GAA_FLAG_SKIP_MULTICAST | 
		GAA_FLAG_SKIP_DNS_SERVER;
	ULONG outBufLen = 0;

	IP_ADAPTER_UNICAST_ADDRESS *uai;

	GetAdaptersAddresses(AF_UNSPEC, ifFlags, NULL, NULL, &outBufLen);
	pAdapterAddresses = (IP_ADAPTER_ADDRESSES *) LocalAlloc(LMEM_ZEROINIT, outBufLen);
	GetAdaptersAddresses(AF_UNSPEC, ifFlags, NULL, pAdapterAddresses, &outBufLen);
	ai = pAdapterAddresses;
	while (ai != NULL) {
		if (ai->OperStatus != IfOperStatusUp) {
			ai = ai->Next;
			continue;
		}
		if (ai->IfType == IF_TYPE_SOFTWARE_LOOPBACK) {
			ai = ai->Next;
			continue;
		}
		if (ai->IfType == IF_TYPE_TUNNEL) {
			ai = ai->Next;
			continue;
		}
		uai = ai->FirstUnicastAddress;
		while (uai != NULL) {
			SOCKET_ADDRESS sockaddr = uai->Address;
			SOCKADDR *saddr = sockaddr.lpSockaddr;
			INT saddrlen = sockaddr.iSockaddrLength;
			char addr[NI_MAXHOST];
			char port[NI_MAXSERV];
			int ret = getnameinfo(saddr, saddrlen, addr, sizeof(addr), port, sizeof(port), NI_NUMERICHOST | NI_NUMERICSERV);
			if (ret == 0) {
				if (IsUseAddress(addr) == true) {
					std::string addrStr = addr;
					int ifIdx = 0;
					if (IsIPv6Address(addr) == true) {
						ifIdx = GetIPv6ScopeID(addr);
						/*
						int pos = addrStr.find("%");
						if (pos != std::string::npos)
							addrStr = addrStr.substr(0, pos);
						*/
					}
					NetworkInterface *netIf = new NetworkInterface(addrStr.c_str(), "", ifIdx);
					netIfList.add(netIf);
				}
			}
			else {
				int err = WSAGetLastError();
			}
			uai = uai->Next;
		}
		ai = ai->Next;
	}
	LocalFree(pAdapterAddresses);

#endif

	return netIfList.size();
}

#else

////////////////////////////////////////////////
//	GetHostAddresses (UNIX)
////////////////////////////////////////////////

#if defined(HAVE_IFADDRS_H)

int CyberNet::GetHostAddresses(NetworkInterfaceList &netIfList)
{
	netIfList.clear();
	struct ifaddrs *ifaddr;
	if (getifaddrs(&ifaddr) != 0)
		return 0;
	while (ifaddr != NULL) {
		// Thanks for Tobias.Gansen (01/15/06)
		if(ifaddr->ifa_addr->sa_family != AF_INET){
			ifaddr = ifaddr->ifa_next;
			continue;
		}
		if (!(ifaddr->ifa_flags & IFF_UP)) {
			ifaddr = ifaddr->ifa_next;
			continue;
		}
		if (ifaddr->ifa_flags & IFF_LOOPBACK) {
			ifaddr = ifaddr->ifa_next;
			continue;
		}		
		char addr[NI_MAXHOST+1];
		if (getnameinfo(ifaddr->ifa_addr, sizeof(sockaddr), addr, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) == 0) {
			if (IsUseAddress(addr) == true) {
				std::string addrStr = addr;
				char *ifname = ifaddr->ifa_name;
				int ifIdx = if_nametoindex(ifname);
				//cout << ifname << ", " << ifIdx << endl;
				NetworkInterface *netIf = new NetworkInterface(addr, ifname, ifIdx);
				netIfList.add(netIf);
			}
		}
		ifaddr = ifaddr->ifa_next;
	}
	freeifaddrs(ifaddr);
	return netIfList.size();
}

#elif !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 

static const char *PATH_PROC_NET_DEV = "/proc/net/dev";

int CyberNet::GetHostAddresses(NetworkInterfaceList &netIfList)
{
	netIfList.clear();
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		return 0;
	FILE *fd = fopen(PATH_PROC_NET_DEV, "r");
	char buffer[256+1];
	fgets(buffer, sizeof(buffer)-1, fd);
	fgets(buffer, sizeof(buffer)-1, fd);
	while (!feof(fd)) {
		char *ifname = buffer;
		char *sep;
		if (fgets(buffer, sizeof(buffer)-1, fd) == NULL)
			break;
		sep = strrchr(buffer, ':');
		if (sep)
			*sep = 0;
		while (*ifname == ' ')
			ifname++;
		struct ifreq req;
		strcpy(req.ifr_name, ifname);
		if (ioctl(s, SIOCGIFFLAGS, &req) < 0)
			continue;
		if (!(req.ifr_flags & IFF_UP))
			continue;
		if (req.ifr_flags & IFF_LOOPBACK)
			continue;
		if (ioctl(s, SIOCGIFADDR, &req) < 0)
			continue;
		char ifaddr[20+1];
		strncpy(ifaddr, inet_ntoa(((struct sockaddr_in*)&req.ifr_addr)->sin_addr), sizeof(ifaddr)-1);
		NetworkInterface *netIf = new NetworkInterface(ifaddr, ifname, 0);
		netIfList.add(netIf);
		//cout << ifname << ", " << ifaddr << endl;
	}
	fclose(fd);
	close(s);
	return netIfList.size();
}

#endif

#endif

////////////////////////////////////////////////
//	GetHostAddresses (BTRON)
////////////////////////////////////////////////

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))

int CyberNet::GetHostAddresses(NetworkInterfaceList &netIfList)
{
	netIfList.clear();
	
	struct hostent hostEnt;
	B buf[HBUFLEN];
	ERR err = so_gethostbyname("localhost", &hostEnt, buf);
	if (err != 0)
		return 0;
	
	const char *ifname = "Neta";
	char ifaddr[32];
	inet_ntop(hostEnt.h_addrtype, hostEnt.h_addr, ifaddr, sizeof(ifaddr));
	
	NetworkInterface *netIf = new NetworkInterface(ifaddr, ifname, 0);
	netIfList.add(netIf);
	
	return netIfList.size();
}

#endif

////////////////////////////////////////////////
//	GetHostAddresses  (TENGINE-KASAGO)
////////////////////////////////////////////////

#if defined(TENGINE) && defined(TENGINE_NET_KASAGO)

int CyberNet::GetHostAddresses(NetworkInterfaceList &netIfList)
{
	SocketStartup();

	const char *ifname = "Neta";
	char ifaddr[32];

    struct in_addr inAddr;
    inAddr.s_addr = 0;
    int kaRet = ka_tfGetIpAddress(kaInterfaceHandle, &(inAddr.s_addr), 0);
    if(kaRet != 0)
		return 0;
		
    ka_tfInetToAscii((unsigned long)inAddr.s_addr, ifaddr);
	
	NetworkInterface *netIf = new NetworkInterface(ifaddr, ifname, 0);
	netIfList.add(netIf);

	return netIfList.size();
}

#endif

////////////////////////////////////////////////
//	IsIPv6Address
////////////////////////////////////////////////

bool CyberNet::IsIPv6Address(const char *addr)
{
	if (addr == NULL)
		return false;
	std::string addrStr = addr;
	if (addrStr.find(":") != std::string::npos)
		return true;
	return false;
}

////////////////////////////////////////////////
//	ScopeID
////////////////////////////////////////////////

const char *CyberNet::StripIPv6ScopeID(const char *addr, std::string &buf)
{
	std::string addrStr = addr;
	if (IsIPv6Address(addr) == true) {
		unsigned int pos = addrStr.find("%");
		if (pos != std::string::npos)
				addrStr = addrStr.substr(0, pos);
	}
	buf = addrStr;
	return buf.c_str();
}

int CyberNet::GetIPv6ScopeID(const char *addr)
{
	if (IsIPv6Address(addr) == false)
		return 0;
	std::string addrStr = addr;
	int pos = addrStr.find("%");
	if (pos == (int)std::string::npos)
		return 0;
	std::string scopeStr = addrStr.substr(pos+1, addrStr.length());
	return atoi(scopeStr.c_str());
}

////////////////////////////////////////////////
//	GetHostURL
////////////////////////////////////////////////

static string ifAddress;

void CyberNet::SetHostInterface(const char *ifaddr)
{
	ifAddress = ifaddr;
}

const char *CyberNet::GetHostInterface()
{
	return ifAddress.c_str();
}

bool CyberNet::HasAssignedHostInterface()
{
	return (0 < ifAddress.length()) ? true : false;
}
