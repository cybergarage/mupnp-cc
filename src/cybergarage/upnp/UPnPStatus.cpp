/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2004
*
*  File: UPnPStatus.java
*
*  Revision;
*
*  01/05/04
*    - first revision.
*  
******************************************************************/

#include <uhttp/http/HTTP.h>
#include <cybergarage/upnp/UPnPStatus.h>
  
const char *CyberLink::UPnP::StatusCode2String(int code) {
  switch (code) {
  case UPnP::INVALID_ACTION: return "Invalid Action";
  case UPnP::INVALID_ARGS: return "Invalid Args";
  case UPnP::OUT_OF_SYNC: return "Out of Sync";
  case UPnP::INVALID_VAR: return "Invalid Var";
  case UPnP::ACTION_FAILED: return "Action Failed";
  }
   return "";
}
