/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/device/NTS.h>
#include <uhttp/util/StringUtil.h>
  
bool mUPnP::NTS::IsAlive(const std::string &ntsValue) {
  uHTTP::String ntsStr = ntsValue;
  return ntsStr.startsWith(ALIVE);
}

bool mUPnP::NTS::IsByeBye(const std::string &ntsValue) {
  uHTTP::String ntsStr = ntsValue;
  return ntsStr.startsWith(BYEBYE);
}

