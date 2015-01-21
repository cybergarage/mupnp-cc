/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <uhttp/http/HTTP.h>
#include <mupnp/UPnPStatus.h>
  
const char *mUPnP::UPnP::StatusCodeToString(int code) {
  switch (code) {
  case UPnP::INVALID_ACTION: return "Invalid Action";
  case UPnP::INVALID_ARGS: return "Invalid Args";
  case UPnP::OUT_OF_SYNC: return "Out of Sync";
  case UPnP::INVALID_VAR: return "Invalid Var";
  case UPnP::ACTION_FAILED: return "Action Failed";
  }
   return "";
}
