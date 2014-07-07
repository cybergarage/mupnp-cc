/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: HTTPMUSocket.cpp
*
*  Revision;
*
*  07/01/03
*    - first revision
*  11/19/04
*    - Theo Beisch <theo.beisch@gmx.de>
*    - Changed send() to set the TTL as 4.
*
******************************************************************/

#include <time.h>
#include <uhttp/net/HostInterface.h>
#include <cybergarage/upnp/ssdp/HTTPMUSocket.h>

using namespace CyberLink;
using namespace uHTTP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
  
HTTPMUSocket::HTTPMUSocket() {
}

HTTPMUSocket::HTTPMUSocket(const std::string &addr, int port, const std::string &bindAddr) {
  open(addr, port, bindAddr);
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

HTTPMUSocket::~HTTPMUSocket() {
  close();
}

////////////////////////////////////////////////
// open/close
////////////////////////////////////////////////

bool HTTPMUSocket::open(const std::string &addr, int port, const std::string &bindAddr) {
  ssdpMultiGroup.setAddress(addr);
  ssdpMultiGroup.setPort(port);

  if (ssdpMultiSock.bind(port, bindAddr) == false)
    return false;
  
  if (ssdpMultiSock.joinGroup(addr, bindAddr) == false) {
    ssdpMultiSock.close();
    return false;
  }    

  return true;
}

bool HTTPMUSocket::close() {
  if (ssdpMultiSock.close() == false)
    return false;
  return true;
}

////////////////////////////////////////////////
// send
////////////////////////////////////////////////

bool HTTPMUSocket::send(const std::string &host, int port, const std::string &msg) {
  InetSocketAddress inetAddr(host, port);
  
  DatagramPacket dgmPacket(msg, &inetAddr);
  
  MulticastSocket msock;
  msock.setTimeToLive(4);
  return (0 < msock.send(&dgmPacket)) ? true : false;
}

////////////////////////////////////////////////
// reveive
////////////////////////////////////////////////

SSDPPacket *HTTPMUSocket::receive() {
  recvPacket.setLocalAddress(getLocalAddress());
  size_t nRecv = ssdpMultiSock.receive(recvPacket.getDatagramPacket());
  if (nRecv == 0)
    return NULL;
  recvPacket.setTimeStamp(time(NULL));
  return &recvPacket;
}
