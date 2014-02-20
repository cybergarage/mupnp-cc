/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPSearchResponseSocketList.cpp
*
*  Revision:
*
*  08/14/03
*    - first revision
*  07/17/04
*    - Added the destructor and clear().
*
******************************************************************/

#include <cybergarage/upnp/ssdp/SSDPSearchResponseSocketList.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////
  
SSDPSearchResponseSocketList::SSDPSearchResponseSocketList()  {
}

SSDPSearchResponseSocketList::~SSDPSearchResponseSocketList()  {
  stop();
  close();
}

////////////////////////////////////////////////
//  ControlPoint
////////////////////////////////////////////////

void SSDPSearchResponseSocketList::setControlPoint(ControlPoint *ctrlPoint) {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    sock->setControlPoint(ctrlPoint);
  }
}

////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////
  
bool SSDPSearchResponseSocketList::open(int port) {
  int nHostAddrs = uHTTP::GetNHostAddresses();
  for (int n = 0; n < nHostAddrs; n++) {
    string bindAddr;
    uHTTP::GetHostAddress(n, bindAddr);
    SSDPSearchResponseSocket *socket = new SSDPSearchResponseSocket(bindAddr.c_str(), port);
    add(socket);
  }
  return true;
}

void SSDPSearchResponseSocketList::close() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    sock->close();
  }
  clear();
}

////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////
  
void SSDPSearchResponseSocketList::start() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    sock->start();
  }
}

void SSDPSearchResponseSocketList::stop() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    sock->stop();
  }
}

////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////

bool SSDPSearchResponseSocketList::post(SSDPSearchRequest *req) {
  bool ret = true;
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    const char *bindAddr = sock->getLocalAddress();
    req->setLocalAddress(bindAddr);
    const char *ssdpAddr = SSDP::ADDRESS;
    if (uHTTP::IsIPv6Address(bindAddr) == true)
      ssdpAddr = SSDP::GetIPv6Address();
    //sock.joinGroup(ssdpAddr, SSDP.PORT, bindAddr);
    if (sock->post(ssdpAddr, SSDP::PORT, req) == false)
      ret = false;
    //sock.leaveGroup(ssdpAddr, SSDP.PORT, bindAddr);
  }
  return ret;
}

////////////////////////////////////////////////
//  ControlPoint
////////////////////////////////////////////////

void SSDPSearchResponseSocketList::clear() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    delete sock;
  }
  Vector::clear();
}
