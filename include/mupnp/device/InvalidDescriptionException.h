/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_INVALIDDESCRIPTIONEXCEPTION_H_
#define _MUPMPCC_INVALIDDESCRIPTIONEXCEPTION_H_

#include <mupnp/util/Exception.h>

namespace mUPnP {
const char INVALIDDESCRIPTIONEXCEPTION_FILENOTFOUND[] = "File not found";

class InvalidDescriptionException : public uHTTP::Exception {
  std::string errMsg;

  public:
  InvalidDescriptionException(const std::string& msg)
      : Exception(msg)
  {
  }
};

}

#endif
