/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#if defined(__APPLE__)
#define HAVE_UUID_UUID_H 1
#define HAVE_LIBUUID 1
#endif

#if defined(HAVE_UUID_UUID_H) || defined(HAVE_LIBUUID)
#include <uuid/uuid.h>
#endif

#include <uhttp/net/HostInterface.h>
#include <mupnp/UPnP.h>
#include <mupnp/Icon.h>
#include <mupnp/ssdp/SSDP.h>
#include <uhttp/http/HTTPServer.h>

#include <stdio.h>
#include <time.h>
#include <limits.h>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/utsname.h>
#endif

using namespace std;
using namespace mUPnP;

////////////////////////////////////////////////
// GetServerName
////////////////////////////////////////////////
  
const char *UPnP::GetServerName(std::string &buf) {
  uHTTP::GetServerName(buf);
  buf += " UPnP/";
  buf += UPnP::VER;
  buf += " ";
  buf += mUPnP::NAME;
  buf += "/";
  buf += mUPnP::VER;
  return buf.c_str();
}

////////////////////////////////////////////////
// UUID
////////////////////////////////////////////////

const char *UPnP::CreateUUID(std::string &buf) {
#if defined(HAVE_LIBUUID)
  #define CG_UPNP_UUID_MAX_LEN 128 /*(5 + ((4+1)*4) + 1)*/
	uuid_t uuid;
	char uuidStr[CG_UPNP_UUID_MAX_LEN];
  uuid_generate(uuid);
	uuid_unparse_lower(uuid, uuidStr);
	char uuidBuf[CG_UPNP_UUID_MAX_LEN];
	snprintf(uuidBuf,sizeof(uuidBuf), "%s",uuidStr);
  buf = uuidStr;
#else
  time_t time1 = time(NULL);
  time_t time2 = (time_t)((double)time(NULL) * ((double)rand() / (double)RAND_MAX));
  char sidBuf[((4+1)*4) + 1];
  sprintf(sidBuf, "%04x-%04x-%04x-%04x",
          (int)(time1 & 0xFFFF),
          (int)(((time1 >> 31) | 0xA000) & 0xFFFF),
          (int)(time2 & 0xFFFF),
          (int)(((time2 >> 31) | 0xE000) & 0xFFFF));
  buf = sidBuf;
#endif
  
  return buf.c_str();
}

////////////////////////////////////////////////
// BootID
////////////////////////////////////////////////

int UPnP::CreateBootID() {
  time_t currentTime = time(NULL);
  return (currentTime % INT_MAX);
}

////////////////////////////////////////////////
// Enable/Disable
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
