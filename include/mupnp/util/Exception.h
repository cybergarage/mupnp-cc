/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_UTIL_EXCEPTION_H_
#define _UHTTP_UTIL_EXCEPTION_H_

#include <string>

namespace uHTTP {
class Exception {
  std::string msg;

  public:
  Exception(const std::string& msg)
  {
    this->msg = msg;
  }

  const char* getMessage()
  {
    return msg.c_str();
  }
};

}

#endif
