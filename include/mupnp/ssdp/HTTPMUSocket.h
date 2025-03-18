/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_HTTPMUSOCKET_H_
#define _MUPMPCC_HTTPMUSOCKET_H_

#include <mupnp/net/MulticastSocket.h>
#include <mupnp/net/InetSocketAddress.h>
#include <mupnp/net/NetworkInterface.h>
#include <mupnp/http/HTTPRequest.h>
#include <mupnp/ssdp/SSDPPacket.h>

namespace mUPnP {
class HTTPMUSocket {
  uHTTP::InetSocketAddress ssdpMultiGroup;
  uHTTP::MulticastSocket ssdpMultiSock;

 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  HTTPMUSocket();  
  ~HTTPMUSocket();

  ////////////////////////////////////////////////
  // bindAddr
  ////////////////////////////////////////////////

  const char *getLocalAddress() {
    return ssdpMultiSock.getLocalAddress();
  }

  ////////////////////////////////////////////////
  // open/close
  ////////////////////////////////////////////////

  bool open(const std::string &addr, int port, const std::string &bindAddr);
  bool close();

  ////////////////////////////////////////////////
  // send
  ////////////////////////////////////////////////

  bool send(const std::string &host, int port, const std::string &msg);

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////
  
  bool post(const std::string &host, int port, uHTTP::HTTPRequest *req) {
    std::string reqStr;
    return send(host, port, req->toString(reqStr));
  }
  
  ////////////////////////////////////////////////
  // reveive
  ////////////////////////////////////////////////

   bool receive(SSDPPacket *ssdpPacket);
};

}

#endif


