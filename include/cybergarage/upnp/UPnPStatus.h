/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2004
*
*  File: UPnPStatus.h
*
*  Revision;
*
*  08/12/03
*    - first revision
*  01/03/04
*    - Changed the class name from UPnPError to UPnPStatus.
*
******************************************************************/

#ifndef _CLINK_UPNPSTATUS_H_
#define _CLINK_UPNPSTATUS_H_

#include <string>

namespace CyberLink {
namespace UPnP {
const int INVALID_ACTION = 401;
const int INVALID_ARGS = 402;
const int OUT_OF_SYNC = 403;
const int INVALID_VAR = 404;
const int ACTION_FAILED = 501;
}

namespace UPnP {
const char *StatusCode2String(int code);
}

class UPnPStatus {
  int code;
  std::string description;
  
 public:
  UPnPStatus() {
    setCode(0);
    setDescription("");  
  }

  UPnPStatus(int code, const std::string &desc) {
    setCode(code);
    setDescription(desc);  
  }

 public:
  void setCode(int code) {
    this->code = code;
  }

  void setDescription(const std::string &description) {
    this->description = description;
  }

 public:
  const char *getDescription() {
    return description.c_str();
  }

  int getCode() {
    return code;
  }
};

}

#endif

