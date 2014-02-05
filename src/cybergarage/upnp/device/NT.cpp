/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: NT.cpp
*
*  Revision:
*
*  07/07/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/device/NT.h>
#include <uhttp/util/StringUtil.h>

bool CyberLink::NT::IsRootDevice(const std::string &ntValue) {
  uHTTP::String ntStr = ntValue;
  return ntStr.startsWith(ROOTDEVICE);
}
