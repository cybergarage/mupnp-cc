/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDP.cpp
*
*	Revision;
*
*	05/22/03
*		- first revision
*
******************************************************************/

#include <stdlib.h>
#include <string.h>
#include <string>
#include <cybergarage/upnp/ssdp/SSDP.h>

using namespace std;
using namespace CyberLink::SSDP;

static string ssdpIPv6Address;

////////////////////////////////////////////////
//	SSDP Address for IPv6
////////////////////////////////////////////////

<<<<<<< HEAD
void CyberLink::SSDP::SetIPv6Address(const std::string &addr)
=======
void CyberLink::SSDP::SetIPv6Address(const char *addr)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	ssdpIPv6Address = addr;
}

const char *CyberLink::SSDP::GetIPv6Address()
{
	if (ssdpIPv6Address.length() <= 0)
		SetIPv6Address(IPV6_LINK_LOCAL_ADDRESS);
	return ssdpIPv6Address.c_str();
}

////////////////////////////////////////////////
//	LeaseTime
////////////////////////////////////////////////
	
<<<<<<< HEAD
int CyberLink::SSDP::GetLeaseTime(const std::string &cacheCnt)
{
	char *eqStrPos = strchr((char *)cacheCnt.c_str(), '=');
=======
int CyberLink::SSDP::GetLeaseTime(const char *cacheCnt)
{
	char *eqStrPos = strchr((char *)cacheCnt, '=');
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	if (eqStrPos == NULL)
		return 0;
	return atoi((eqStrPos + 1));
}
