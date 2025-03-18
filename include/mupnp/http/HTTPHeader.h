/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_HTTPHEADER_H_
#define _UHTTP_HTTPHEADER_H_

#include <stdio.h>
#include <string>
#include <vector>

#include <mupnp/io/LineNumberReader.h>

namespace uHTTP {
class HTTPHeader {
  std::string name;
  std::string value;

  public:
  HTTPHeader(const std::string& lineStr);
  HTTPHeader(const std::string& name, const std::string& value);
  HTTPHeader(HTTPHeader* header);

  ~HTTPHeader();

  void setName(const std::string& name)
  {
    this->name = name;
  }

  const char* getName()
  {
    return name.c_str();
  }

  bool hasName()
  {
    if (name.length() <= 0)
      return false;
    return true;
  }

  void setValue(const std::string& value)
  {
    this->value = value;
  }

  const char* getValue()
  {
    return value.c_str();
  }
};

class HTTPHeaderList : public std::vector<HTTPHeader*> {
  public:
  HTTPHeaderList()
  {
  }
};

const char* HTTPHeaderGetValue(uHTTP::LineNumberReader* reader, const std::string& name, std::string& buf);
const char* HTTPHeaderGetValue(const std::string& data, const std::string& name, std::string& buf);
int HTTPHeaderGetIntegerValue(const std::string& data, const std::string& name);

}

#endif
