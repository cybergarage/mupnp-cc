/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: UPnP.h
*
*  Revision;
*
*  07/10/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_UPNP_H_
#define _CLINK_UPNP_H_

#include <string>

namespace CyberLink {
const char NAME[] = "CyberLinkC++";
const char VER[]= "1.7";

namespace UPnP {
////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////
  
const char VER[]= "1.0";

const int SERVER_RETRY_COUNT = 100;
const int DEFAULT_EXPIRED_DEVICE_EXTRA_TIME = 60;

const char INMPR03[]= "INMPR03";
const char INMPR03_VER[]= "1.0";
const int INMPR03_DISCOVERY_OVER_WIRELESS_COUNT = 4;

const char XML_DECLARATION[] = "<?xml version=\"1.0\"?>";

////////////////////////////////////////////////
//  Functions
////////////////////////////////////////////////

const char *GetServerName(std::string &buf);
const char *CreateUUID(std::string &buf);

////////////////////////////////////////////////
//  Enable / Disable
////////////////////////////////////////////////
  
const int USE_ONLY_IPV6_ADDR = 1;
const int USE_LOOPBACK_ADDR = 2;
const int USE_IPV6_LINK_LOCAL_SCOPE = 3;
const int USE_IPV6_SUBNET_SCOPE = 4;
const int USE_IPV6_ADMINISTRATIVE_SCOPE = 5;
const int USE_IPV6_SITE_LOCAL_SCOPE = 6;
const int USE_IPV6_GLOBAL_SCOPE = 7;
const int USE_SSDP_SEARCHRESPONSE_MULTIPLE_INTERFACES = 8;
const int USE_ONLY_IPV4_ADDR = 9;

void SetEnable(int value);
void SetDisable(int value);
bool IsEnabled(int value);

}

}

#endif
