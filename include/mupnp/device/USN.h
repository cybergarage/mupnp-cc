/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_USN_H_
#define _MUPMPCC_USN_H_

#include <string>

namespace mUPnP {
namespace USN {
  const char ROOTDEVICE[] = "upnp:rootdevice";

  bool IsRootDevice(const std::string& usnValue);
  const char* GetUDN(const std::string& usnValue, std::string& udn);

}

}

#endif
