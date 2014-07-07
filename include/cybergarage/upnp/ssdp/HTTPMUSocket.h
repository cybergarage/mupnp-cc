/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: HTTPMUSocket.h
*
*  Revision;
*
*  07/01/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_HTTPMUSOCKET_H_
#define _CLINK_HTTPMUSOCKET_H_

#include <uhttp/net/MulticastSocket.h>
#include <uhttp/net/InetSocketAddress.h>
#include <uhttp/net/NetworkInterface.h>
#include <uhttp/http/HTTPRequest.h>
#include <cybergarage/upnp/ssdp/SSDPPacket.h>

namespace CyberLink {
class HTTPMUSocket {
  uHTTP::InetSocketAddress ssdpMultiGroup;
  uHTTP::MulticastSocket ssdpMultiSock;
  SSDPPacket recvPacket;

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

  SSDPPacket *receive();
};

}

#endif


