/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: NT.h
*
*  Revision;
*
*  07/07/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_NT_H_
#define _MUPMPCC_NT_H_

#include <string>

namespace mUPnP {
namespace NT {
const char ROOTDEVICE[] = "upnp:rootdevice";
const char EVENT[] = "upnp:event";
  
bool IsRootDevice(const std::string &usnValue);

}

}

#endif

