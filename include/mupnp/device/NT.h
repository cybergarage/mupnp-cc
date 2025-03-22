/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_NT_H_
#define _MUPMPCC_NT_H_

#include <string>

namespace mUPnP {
namespace NT {
  const char ROOTDEVICE[] = "upnp:rootdevice";
  const char EVENT[] = "upnp:event";

  bool IsRootDevice(const std::string& usnValue);

}

}

#endif
