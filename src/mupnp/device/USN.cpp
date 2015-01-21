/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/device/USN.h>
#include <uhttp/util/StringUtil.h>

bool mUPnP::USN::IsRootDevice(const std::string &usnValue) {
  uHTTP::String usnStr = usnValue;
  return usnStr.endsWith(ROOTDEVICE);
}
  
const char *mUPnP::USN::GetUDN(const std::string &usnValue, std::string &udn) {
  uHTTP::String usnStr = usnValue;
  int idx = usnStr.indexOf("::");
  if (idx < 0)
    return usnStr.trim();
  uHTTP::String udnStr(usnStr.getValue(), 0, idx);
  udn = udnStr.trim();
  return udn.c_str();
}
