/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: NTS.cpp
*
*  Revision;
*
*  07/07/03
*    - first revision
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

