/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/device/MAN.h>
#include <uhttp/util/StringUtil.h>

using namespace std;
using namespace uHTTP;

bool mUPnP::MAN::IsDiscover(const std::string &value) {
  uHTTP::String manStr = value;
  if (manStr.equals(DISCOVER) == true)
    return true;
  string quoteDiscoverStr;
  quoteDiscoverStr.append("\"");
  quoteDiscoverStr.append(DISCOVER);
  quoteDiscoverStr.append("\"");
  return manStr.equals(quoteDiscoverStr.c_str());
}
