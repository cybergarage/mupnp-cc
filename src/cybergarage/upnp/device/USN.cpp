/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: USN.cpp
*
*  Revision:
*
*  07/07/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/device/USN.h>
#include <uhttp/util/StringUtil.h>

bool CyberLink::USN::IsRootDevice(const std::string &usnValue) {
  uHTTP::String usnStr = usnValue;
  return usnStr.endsWith(ROOTDEVICE);
}
  
const char *CyberLink::USN::GetUDN(const std::string &usnValue, std::string &udn) {
  uHTTP::String usnStr = usnValue;
  int idx = usnStr.indexOf("::");
  if (idx < 0)
    return usnStr.trim();
  uHTTP::String udnStr(usnStr.getValue(), 0, idx);
  udn = udnStr.trim();
  return udn.c_str();
}
