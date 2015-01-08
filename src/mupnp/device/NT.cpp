/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: NT.cpp
*
*  Revision:
*
*  07/07/03
*    - first revision
*
******************************************************************/

#include <mupnp/device/NT.h>
#include <uhttp/util/StringUtil.h>

bool mUPnP::NT::IsRootDevice(const std::string &ntValue) {
  uHTTP::String ntStr = ntValue;
  return ntStr.startsWith(ROOTDEVICE);
}
