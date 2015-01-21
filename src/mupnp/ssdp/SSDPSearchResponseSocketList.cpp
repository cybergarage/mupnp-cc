/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/ssdp/SSDPSearchResponseSocketList.h>

using namespace std;
using namespace mUPnP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
  
SSDPSearchResponseSocketList::SSDPSearchResponseSocketList()  {
}

SSDPSearchResponseSocketList::~SSDPSearchResponseSocketList()  {
  stop();
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
  if (nHostAddrs == 0)
    return false;
  for (size_t n = 0; n < nHostAddrs; n++) {
    string bindAddr;
    uHTTP::GetHostAddress(n, bindAddr);
    SSDPSearchResponseSocket *ssdpResSocket = new SSDPSearchResponseSocket();
    if (ssdpResSocket->open(port, bindAddr) == false) {
      delete ssdpResSocket;
      areAllHostsOpened = false;
      continue;
    }
    add(ssdpResSocket);
  }
  return areAllHostsOpened;
}

bool SSDPSearchResponseSocketList::close() {
  bool areAllSocketsClosed = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    if (sock->close() == false) {
      areAllSocketsClosed = false;
    }
  }
  clear();
  return areAllSocketsClosed;
}

////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////
  
bool SSDPSearchResponseSocketList::start() {
  bool areAllSocketsStarted = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    if (sock->start() == false) {
      areAllSocketsStarted = false;
    }
  }
  return areAllSocketsStarted;
}

bool SSDPSearchResponseSocketList::stop() {
  bool areAllSocketsStopped = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchResponseSocket *sock = getSSDPSearchResponseSocket(n);
    if (sock->stop() == false) {
      areAllSocketsStopped = false;
    }
  }
  close();
  return areAllSocketsStopped;
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
