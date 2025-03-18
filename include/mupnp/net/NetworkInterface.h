/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_NETWORKINTERFACE_H_
#define _UHTTP_NET_NETWORKINTERFACE_H_

#include <string>

namespace uHTTP {
class NetworkInterface {
  std::string name;
  std::string addr;
  int index;

  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  NetworkInterface(const std::string& addr = NULL, const std::string& name = NULL, int idx = 0)
  {
    setAddress(addr);
    setName(name);
    setIndex(idx);
  }

  ////////////////////////////////////////////////
  // Address
  ////////////////////////////////////////////////

  void setAddress(const std::string& value)
  {
    addr = value;
  }

  const char* getAddress()
  {
    return addr.c_str();
  }

  ////////////////////////////////////////////////
  // Name
  ////////////////////////////////////////////////

  void setName(const std::string& value)
  {
    name = value;
  }

  const char* getName()
  {
    return name.c_str();
  }

  ////////////////////////////////////////////////
  // Index
  ////////////////////////////////////////////////

  void setIndex(int value)
  {
    index = value;
  }

  int getIndex()
  {
    return index;
  }
};

}

#endif
