/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: UPnP.cpp
*
*  Revision;
*
*  07/20/03
*    - first revision
*  04/20/04
*    - Updated GetServerName() to return the correct server name.
*  05/19/04
*    - Changed the header include order for Cygwin.
*    - Removed extra heder includes.
*  06/18/03
*    - Added INMPR03 and INMPR03_VERSION.
*  08/01/04
*    - Added <stdio.h> for sprintf() for gcc 2.95.3.
*  03/08/05
*    - Changed GetServerName() not to use iostream and use uHTTP::GetServerName().
*
******************************************************************/

#include <uhttp/net/HostInterface.h>
#include <cybergarage/upnp/UPnP.h>
#include <cybergarage/upnp/Icon.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <uhttp/http/HTTPServer.h>

#include <stdio.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/utsname.h>
#endif

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
//  GetServerName
////////////////////////////////////////////////
  
const char *UPnP::GetServerName(std::string &buf) {
  uHTTP::GetServerName(buf);
  buf += " UPnP/";
  buf += UPnP::VER;
  buf += " ";
  buf += CyberLink::NAME;
  buf += "/";
  buf += CyberLink::VER;
  return buf.c_str();
}

////////////////////////////////////////////////
//  UUID
////////////////////////////////////////////////

const char *UPnP::CreateUUID(std::string &buf) {
  time_t time1 = time(NULL);
  time_t time2 = (time_t)((double)time(NULL) * ((double)rand() / (double)RAND_MAX));
  char sidBuf[((4+1)*4) + 1];
  sprintf(sidBuf, "%04x-%04x-%04x-%04x", 
    (int)(time1 & 0xFFFF), 
    (int)(((time1 >> 31) | 0xA000) & 0xFFFF),
    (int)(time2 & 0xFFFF), 
    (int)(((time2 >> 31) | 0xE000) & 0xFFFF));
  buf = sidBuf;
  return buf.c_str();
}

////////////////////////////////////////////////
//  Enable/Disable
////////////////////////////////////////////////

void UPnP::SetEnable(int value) {
  switch (value) {
  case USE_ONLY_IPV6_ADDR:
    {
      uHTTP::HostInterface::USE_ONLY_IPV6_ADDR = true;
    }
    break;  
  case USE_ONLY_IPV4_ADDR:
    {
      uHTTP::HostInterface::USE_ONLY_IPV4_ADDR = true;
    }
    break;  
  case USE_LOOPBACK_ADDR:
    {
      uHTTP::HostInterface::USE_LOOPBACK_ADDR = true;
    }
    break;  
  case USE_IPV6_LINK_LOCAL_SCOPE:
    {
      SSDP::SetIPv6Address(SSDP::IPV6_LINK_LOCAL_ADDRESS);
    }
    break;  
  case USE_IPV6_SUBNET_SCOPE:
    {
      SSDP::SetIPv6Address(SSDP::IPV6_SUBNET_ADDRESS);
    }
    break;  
  case USE_IPV6_ADMINISTRATIVE_SCOPE:
    {
      SSDP::SetIPv6Address(SSDP::IPV6_ADMINISTRATIVE_ADDRESS);
    }
    break;  
  case USE_IPV6_SITE_LOCAL_SCOPE:
    {
      SSDP::SetIPv6Address(SSDP::IPV6_SITE_LOCAL_ADDRESS);
    }
    break;  
  case USE_IPV6_GLOBAL_SCOPE:
    {
      SSDP::SetIPv6Address(SSDP::IPV6_GLOBAL_ADDRESS);
    }
    break;  
  }
}

void UPnP::SetDisable(int value) {
  switch (value) {
  case USE_ONLY_IPV6_ADDR:
    {
      uHTTP::HostInterface::USE_ONLY_IPV6_ADDR = false;
    }
    break;  
  case USE_ONLY_IPV4_ADDR:
    {
      uHTTP::HostInterface::USE_ONLY_IPV4_ADDR = false;
    }
    break;  
  case USE_LOOPBACK_ADDR:
    {
      uHTTP::HostInterface::USE_LOOPBACK_ADDR = false;
    }
    break;  
  }
}

bool UPnP::IsEnabled(int value) {
  switch (value) {
  case USE_ONLY_IPV6_ADDR:
    {
      return uHTTP::HostInterface::USE_ONLY_IPV6_ADDR;
    }
  case USE_ONLY_IPV4_ADDR:
    {
      return uHTTP::HostInterface::USE_ONLY_IPV4_ADDR;
    }
  case USE_LOOPBACK_ADDR:
    {
      return uHTTP::HostInterface::USE_LOOPBACK_ADDR;
    }
  }
  return false;
}
