/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/device/ST.h>
#include <mupnp/util/StringUtil.h>

using namespace std;
using namespace uHTTP;

bool mUPnP::ST::IsAllDevice(const std::string &value) {
  String valStr = value;
  if (valStr.equals(ALL_DEVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(ALL_DEVICE);
  quoteStr.append("\"");
  return valStr.equals(quoteStr.c_str());
}

bool mUPnP::ST::IsRootDevice(const std::string &value) {
  String valStr = value;
  if (valStr.equals(ROOT_DEVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(ROOT_DEVICE);
  quoteStr.append("\"");
  return valStr.equals(quoteStr.c_str());
}

bool mUPnP::ST::IsUUIDDevice(const std::string &value) {
  String valStr = value;
  if (valStr.startsWith(UUID_DEVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(UUID_DEVICE);
  quoteStr.append("\"");
  return valStr.startsWith(quoteStr.c_str());
}

bool mUPnP::ST::IsURNDevice(const std::string &value) {
  String valStr = value;
  if (valStr.startsWith(URN_DEVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(URN_DEVICE);
  quoteStr.append("\"");
  return valStr.startsWith(quoteStr.c_str());
}

bool mUPnP::ST::IsURNService(const std::string &value) {
  String valStr = value;
  if (valStr.startsWith(URN_SERVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(URN_SERVICE);
  quoteStr.append("\"");
  return valStr.startsWith(quoteStr.c_str());
}
