/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: MAN.h
*
*  Revision;
*
*  07/08/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_MAN_H_
#define _MUPMPCC_MAN_H_

#include <sstream>

namespace mUPnP {
namespace MAN {
const char DISCOVER[] = "ssdp:discover";
  
bool IsDiscover(const std::string &value);

}

}

#endif

