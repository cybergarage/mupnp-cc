/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDP.cpp
*
*  Revision;
*
*  05/22/03
*    - first revision
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
//  SSDP Address for IPv6
////////////////////////////////////////////////

void CyberLink::SSDP::SetIPv6Address(const std::string &addr) {
  ssdpIPv6Address = addr;
}

const char *CyberLink::SSDP::GetIPv6Address() {
  if (ssdpIPv6Address.length() <= 0)
    SetIPv6Address(IPV6_LINK_LOCAL_ADDRESS);
  return ssdpIPv6Address.c_str();
}

////////////////////////////////////////////////
//  LeaseTime
////////////////////////////////////////////////
  
int CyberLink::SSDP::GetLeaseTime(const std::string &cacheCnt) {
  char *eqStrPos = strchr((char *)cacheCnt.c_str(), '=');
  if (eqStrPos == NULL)
    return 0;
  return atoi((eqStrPos + 1));
}
