/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdlib.h>
#include <string.h>
#include <string>
#include <mupnp/ssdp/SSDP.h>

using namespace std;
using namespace mUPnP::SSDP;

static string ssdpIPv6Address;

////////////////////////////////////////////////
// SSDP Address for IPv6
////////////////////////////////////////////////

void mUPnP::SSDP::SetIPv6Address(const std::string &addr) {
  ssdpIPv6Address = addr;
}

const char *mUPnP::SSDP::GetIPv6Address() {
  if (ssdpIPv6Address.length() <= 0)
    SetIPv6Address(IPV6_LINK_LOCAL_ADDRESS);
  return ssdpIPv6Address.c_str();
}

////////////////////////////////////////////////
// LeaseTime
////////////////////////////////////////////////
  
int mUPnP::SSDP::GetLeaseTime(const std::string &cacheCnt) {
  char *eqStrPos = strchr((char *)cacheCnt.c_str(), '=');
  if (!eqStrPos)
    return 0;
  return atoi((eqStrPos + 1));
}
