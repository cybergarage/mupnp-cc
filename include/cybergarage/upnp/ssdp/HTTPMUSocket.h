/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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
  //uHTTP::NetworkInterface ssdpMultiIf;
  SSDPPacket recvPacket;

 public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  HTTPMUSocket();
  
  HTTPMUSocket(const std::string &addr, int port, const std::string &bindAddr);

  ~HTTPMUSocket();

  ////////////////////////////////////////////////
  //  bindAddr
  ////////////////////////////////////////////////

  const char *getLocalAddress() {
    return ssdpMultiSock.getLocalAddress();
  }

  ////////////////////////////////////////////////
  //  open/close
  ////////////////////////////////////////////////

  bool open(const std::string &addr, int port, const std::string &bindAddr);
  bool close();

  ////////////////////////////////////////////////
  //  send
  ////////////////////////////////////////////////

  bool send(const std::string &msg, const std::string &bindAddr = "", int bindPort = -1);

  ////////////////////////////////////////////////
  //  post (HTTPRequest)
  ////////////////////////////////////////////////

  bool post(uHTTP::HTTPRequest *req, const std::string &bindAddr, int bindPort) {
    std::string reqStr;
    return send(req->toString(reqStr), bindAddr, bindPort);
  }

  bool post(uHTTP::HTTPRequest *req) {
    std::string reqStr;
    return send(req->toString(reqStr));
  }

  ////////////////////////////////////////////////
  //  reveive
  ////////////////////////////////////////////////

  SSDPPacket *receive();
};

}

#endif


