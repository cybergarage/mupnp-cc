/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/device/NT.h>
#include <mupnp/util/StringUtil.h>

bool mUPnP::NT::IsRootDevice(const std::string &ntValue) {
  uHTTP::String ntStr = ntValue;
  return ntStr.startsWith(ROOTDEVICE);
}
