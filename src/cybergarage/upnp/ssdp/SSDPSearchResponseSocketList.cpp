/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
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
// Constructor
////////////////////////////////////////////////
  
SSDPSearchResponseSocketList::SSDPSearchResponseSocketList()  {
}

SSDPSearchResponseSocketList::~SSDPSearchResponseSocketList()  {
  stop();
  close();
}

////////////////////////////////////////////////
// ControlPoint
////////////////////////////////////////////////

void SSDPSearchResponseSocketList::setControlPoint(ControlPoint *ctrlPoint) {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    sock->setControlPoint(ctrlPoint);
  }
}

////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////
  
bool SSDPSearchResponseSocketList::open(int port) {
  bool areAllHostsOpened = true;
  size_t nHostAddrs = uHTTP::GetNHostAddresses();
  for (size_t n = 0; n < nHostAddrs; n++) {
    string bindAddr;
    uHTTP::GetHostAddress(n, bindAddr);
    SSDPSearchResponseSocket *ssdpResSocket = new SSDPSearchResponseSocket();
    if (ssdpResSocket->open(port, bindAddr.c_str()) == false) {
      delete ssdpResSocket;
      areAllHostsOpened = false;
      continue;
    }
    add(ssdpResSocket);
  }
  return areAllHostsOpened;
}

void SSDPSearchResponseSocketList::close() {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    sock->close();
  }
  clear();
}

////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////
  
void SSDPSearchResponseSocketList::start() {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    sock->start();
  }
}

void SSDPSearchResponseSocketList::stop() {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    sock->stop();
  }
}

////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////

bool SSDPSearchResponseSocketList::post(SSDPSearchRequest *req) {
  bool areAllPostSuccess = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    const char *bindAddr = sock->getLocalAddress();
    req->setLocalAddress(bindAddr);
    const char *ssdpAddr = SSDP::ADDRESS;
    if (uHTTP::IsIPv6Address(bindAddr) == true)
      ssdpAddr = SSDP::GetIPv6Address();
    if (sock->post(ssdpAddr, SSDP::PORT, req) == false)
      areAllPostSuccess = false;
  }
  return areAllPostSuccess;
}

////////////////////////////////////////////////
// ControlPoint
////////////////////////////////////////////////

void SSDPSearchResponseSocketList::clear() {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    delete sock;
  }
  Vector::clear();
}
