/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_INETSOCKETADDRESS_H_
#define _UHTTP_NET_INETSOCKETADDRESS_H_

#include <string>

namespace uHTTP {
class InetSocketAddress {
  std::string addr;
  int port;

  public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  InetSocketAddress()
  {
    setAddress("");
    setPort(-1);
  }

  InetSocketAddress(int port)
  {
    setAddress("");
    setPort(port);
  }

  InetSocketAddress(const std::string& addr, int port)
  {
    setAddress(addr);
    setPort(port);
  }

  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

  void setAddress(const std::string& value)
  {
    addr = value;
  }

  const char* getAddress()
  {
    return addr.c_str();
  }

  void setPort(int value)
  {
    port = value;
  }

  int getPort()
  {
    return port;
  }

  void set(InetSocketAddress* isaddr)
  {
    if (!isaddr) {
      setAddress("");
      setPort(0);
      return;
    }
    setAddress(isaddr->getAddress());
    setPort(isaddr->getPort());
  }
};

}

#endif
