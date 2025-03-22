/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_NTS_H_
#define _MUPMPCC_NTS_H_

#include <string>

namespace mUPnP {
namespace NTS {
  const char ALIVE[] = "ssdp:alive";
  const char BYEBYE[] = "ssdp:byebye";
  const char PROPCHANGE[] = "upnp:propchange";

  bool IsAlive(const std::string& ntsValue);
  bool IsByeBye(const std::string& ntsValue);

}

}

#endif
