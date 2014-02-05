/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDP.h
*
*  Revision;
*
*  05/22/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDP_H_
#define _CLINK_SSDP_H_

namespace CyberLink {
namespace SSDP {
const int PORT = 1900;
  
const char ADDRESS[] = "239.255.255.250";

const char IPV6_IF_LOCAL_ADDRESS[] = "FF01::C";
const char IPV6_LINK_LOCAL_ADDRESS[] = "FF02::C";
const char IPV6_SUBNET_ADDRESS[] = "FF03::C";
const char IPV6_ADMINISTRATIVE_ADDRESS[] = "FF04::C";
const char IPV6_SITE_LOCAL_ADDRESS[] = "FF05::C";
const char IPV6_GLOBAL_ADDRESS[] = "FF0E::C";

void SetIPv6Address(const std::string &addr);
const char *GetIPv6Address();

const int DEFAULT_MSEARCH_MX = 3;
const int RECV_MESSAGE_BUFSIZE = 1024;

int GetLeaseTime(const std::string &cacheCont);

}

}

#endif
