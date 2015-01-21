/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_HTTPUSOCKET_H_
#define _MUPMPCC_HTTPUSOCKET_H_

#include <uhttp/net/DatagramSocket.h>
#include <mupnp/ssdp/SSDPPacket.h>

namespace mUPnP {
class HTTPUSocket  {
  uHTTP::DatagramSocket ssdpUniSock;

 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  HTTPUSocket();
  
  ~HTTPUSocket();

  ////////////////////////////////////////////////
  // open
  ////////////////////////////////////////////////
  
  bool open(int bindPort = -1, const std::string &bindAddr = "");

  ////////////////////////////////////////////////
  // close
  ////////////////////////////////////////////////

  bool close();

  ////////////////////////////////////////////////
  // DatagramSocket
  ////////////////////////////////////////////////

  uHTTP::DatagramSocket &getDatagramSocket() {
    return ssdpUniSock;
  }

  ////////////////////////////////////////////////
  // bindAddr
  ////////////////////////////////////////////////

  const char *getLocalAddress() {
    return ssdpUniSock.getLocalAddress();
  }

  ////////////////////////////////////////////////
  // post/receive
  ////////////////////////////////////////////////
  
  bool post(const std::string &addr, int port, const std::string &msg);

  bool receive(SSDPPacket *ssdpPacket);

};

}

#endif


