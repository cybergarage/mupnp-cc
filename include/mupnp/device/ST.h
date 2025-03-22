/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ST_H_
#define _MUPMPCC_ST_H_

#include <sstream>

namespace mUPnP {
namespace ST {
  const char ALL_DEVICE[] = "ssdp:all";
  const char ROOT_DEVICE[] = "upnp:rootdevice";
  const char UUID_DEVICE[] = "uuid";
  const char URN_DEVICE[] = "urn:schemas-upnp-org:device:";
  const char URN_SERVICE[] = "urn:schemas-upnp-org:service:";

  bool IsAllDevice(const std::string& value);
  bool IsRootDevice(const std::string& value);
  bool IsUUIDDevice(const std::string& value);
  bool IsURNDevice(const std::string& value);
  bool IsURNService(const std::string& value);

}

}

#endif
