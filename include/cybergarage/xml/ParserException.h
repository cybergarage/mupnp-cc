/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File:  ParserException.h
*
*  Revision;
*
*  08/30/03
*    - first revision
*
******************************************************************/

#ifndef _CXML_PARSEREXCEPTION_H_
#define _CXML_PARSEREXCEPTION_H_

#include <uhttp/util/Exception.h>

namespace CyberXML {
class ParserException : public uHTTP::Exception {
 public:
  ParserException(const std::string &msg) : Exception(msg) {
  }
  
};

}

#endif
