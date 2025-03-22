/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_MAN_H_
#define _MUPMPCC_MAN_H_

#include <sstream>

namespace mUPnP {
namespace MAN {
  const char DISCOVER[] = "ssdp:discover";

  bool IsDiscover(const std::string& value);

}

}

#endif
