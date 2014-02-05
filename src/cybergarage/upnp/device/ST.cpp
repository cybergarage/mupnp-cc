/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ST.cpp
*
*  Revision;
*
*  07/08/03
*    - first revision
*  08/21/05
*    - Changed IsAllDevice() using string instead of ostringstream.
*    - Changed IsRootDevice() using string instead of ostringstream.
*    - Changed IsUUIDDevice() using string instead of ostringstream.
*    - Changed IsURNDevice() using string instead of ostringstream.
*    - Changed IsURNService() using string instead of ostringstream.
*
******************************************************************/

#include <cybergarage/upnp/device/ST.h>
#include <uhttp/util/StringUtil.h>

using namespace std;
using namespace uHTTP;

bool CyberLink::ST::IsAllDevice(const std::string &value) {
  String valStr = value;
  if (valStr.equals(ALL_DEVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(ALL_DEVICE);
  quoteStr.append("\"");
  return valStr.equals(quoteStr.c_str());
}

bool CyberLink::ST::IsRootDevice(const std::string &value) {
  String valStr = value;
  if (valStr.equals(ROOT_DEVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(ROOT_DEVICE);
  quoteStr.append("\"");
  return valStr.equals(quoteStr.c_str());
}

bool CyberLink::ST::IsUUIDDevice(const std::string &value) {
  String valStr = value;
  if (valStr.startsWith(UUID_DEVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(UUID_DEVICE);
  quoteStr.append("\"");
  return valStr.startsWith(quoteStr.c_str());
}

bool CyberLink::ST::IsURNDevice(const std::string &value) {
  String valStr = value;
  if (valStr.startsWith(URN_DEVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(URN_DEVICE);
  quoteStr.append("\"");
  return valStr.startsWith(quoteStr.c_str());
}

bool CyberLink::ST::IsURNService(const std::string &value) {
  String valStr = value;
  if (valStr.startsWith(URN_SERVICE) == true)
    return true;
  string quoteStr;
  quoteStr.append("\"");
  quoteStr.append(URN_SERVICE);
  quoteStr.append("\"");
  return valStr.startsWith(quoteStr.c_str());
}
