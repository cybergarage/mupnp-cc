/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_PARSEREXCEPTION_H_
#define _MUPMPCC_PARSEREXCEPTION_H_

#include <uhttp/util/Exception.h>

namespace uXML {

class ParserException : public uHTTP::Exception {
 public:
  ParserException(const std::string &msg) : Exception(msg) {
  }
  
};

}

#endif
