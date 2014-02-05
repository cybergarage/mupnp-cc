/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: HTTPUSocket.cpp
*
*  Revision;
*
*  06/30/03
*    - first revision
*  01/06/04
*    - Oliver Newell <olivern@users.sourceforge.net>
*    - Added to set a current timestamp when the packet are received.
*
******************************************************************/

#include <cybergarage/upnp/ssdp/HTTPUSocket.h>
#include <time.h>

using namespace CyberLink;


////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

HTTPUSocket::HTTPUSocket() {
  open();
}
  
HTTPUSocket::HTTPUSocket(const std::string &bindAddr, int port) {
  open(port, bindAddr);
}

HTTPUSocket::~HTTPUSocket() {
  close();
}

////////////////////////////////////////////////
//  open
////////////////////////////////////////////////
  
bool HTTPUSocket::open(int bindPort, const std::string &bindAddr) {
  close();
  return ssdpUniSock.bind(bindPort, bindAddr);
}

////////////////////////////////////////////////
//  close
////////////////////////////////////////////////

bool HTTPUSocket::close() {
  ssdpUniSock.close();
  return true;
}

////////////////////////////////////////////////
//  post
////////////////////////////////////////////////

bool HTTPUSocket::post(const std::string &addr, int port, const std::string &msg) {
  ssdpUniSock.send(addr, port, msg);
  return true;
}

////////////////////////////////////////////////
//  reveive
////////////////////////////////////////////////

SSDPPacket *HTTPUSocket::receive() {
  recvPacket.setLocalAddress(getLocalAddress());
  size_t nRecv = ssdpUniSock.receive(recvPacket.getDatagramPacket());
  if (nRecv == 0)
    return NULL;
  recvPacket.setTimeStamp(time(NULL));
  return &recvPacket;
}

