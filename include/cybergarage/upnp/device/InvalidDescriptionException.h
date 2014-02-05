/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: InvalidDescriptionException.h
*
*  Revision:
*
*  08/30/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_INVALIDDESCRIPTIONEXCEPTION_H_
#define _CLINK_INVALIDDESCRIPTIONEXCEPTION_H_

#include <uhttp/util/Exception.h>

namespace CyberLink {
const char INVALIDDESCRIPTIONEXCEPTION_FILENOTFOUND[] = "File not found";

class InvalidDescriptionException : public uHTTP::Exception {
  std::string errMsg;
  
 public:
  InvalidDescriptionException(const std::string &msg) : Exception(msg) {
  }

};

}

#endif

