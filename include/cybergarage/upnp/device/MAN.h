/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: MAN.h
*
*  Revision;
*
*  07/08/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_MAN_H_
#define _CLINK_MAN_H_

#include <sstream>

namespace CyberLink {
namespace MAN {
const char DISCOVER[] = "ssdp:discover";
  
bool IsDiscover(const std::string &value);

}

}

#endif

