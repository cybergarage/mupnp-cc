/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SSDPSearchSocketList.cpp
*
*  Revision;
*
*  08/14/03
*    - first revision
*  07/17/04
*    - Added the destructor and clear().
*
******************************************************************/

#include <cybergarage/upnp/ssdp/SSDPSearchSocketList.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

SSDPSearchSocketList::SSDPSearchSocketList()  {
}

SSDPSearchSocketList::~SSDPSearchSocketList()  {
  stop();
}

////////////////////////////////////////////////
// addSearchListener
////////////////////////////////////////////////
  
void SSDPSearchSocketList::addSearchListener(SearchListener *listener) {
  size_t nServers = size();
  for (size_t n = 0; n < nServers; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    sock->addSearchListener(listener);
  }
}    

////////////////////////////////////////////////
// removeSearchListener
////////////////////////////////////////////////

void SSDPSearchSocketList::removeSearchListener(SearchListener *listener) {
  size_t nServers = size();
  for (size_t n = 0; n < nServers; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    sock->removeSearchListener(listener);
  }
}

////////////////////////////////////////////////
// open/close
////////////////////////////////////////////////
  
bool SSDPSearchSocketList::open()  {
  bool areAllSocketsOpened = true;
  size_t nHostAddrs = uHTTP::GetNHostAddresses();
  if (nHostAddrs == 0)
    return false;
  for (size_t n = 0; n < nHostAddrs; n++) {
    std::string bindAddrStr;
    const char *bindAddr = uHTTP::GetHostAddress(n, bindAddrStr);
    SSDPSearchSocket *ssdpSearchSocket = new SSDPSearchSocket();
    if (ssdpSearchSocket->open(bindAddr) == false) {
      delete ssdpSearchSocket;
      areAllSocketsOpened = false;
      continue;
    }
    add(ssdpSearchSocket);
  }
  return areAllSocketsOpened;
}

bool SSDPSearchSocketList::close() {
  bool areAllSocketsClosed = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    if (sock->close() == false) {
      areAllSocketsClosed = false;
    }
  }
  clear();
  return areAllSocketsClosed;
}
  
////////////////////////////////////////////////
// start/stop
////////////////////////////////////////////////
  
bool SSDPSearchSocketList::start() {
  bool areAllSocketsStarted = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    if (sock->start() == false) {
      areAllSocketsStarted = false;
    }
  }
  return areAllSocketsStarted;
}

bool SSDPSearchSocketList::stop() {
  bool areAllSocketsStopped = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    if (sock->stop() == false) {
      areAllSocketsStopped = false;
    }
  }
  close();
  return areAllSocketsStopped;
}
