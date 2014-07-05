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
  close();
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
// open/close
////////////////////////////////////////////////
  
bool SSDPSearchSocketList::open()  {
  bool isAllHostOpened = true;
  size_t nHostAddrs = uHTTP::GetNHostAddresses();
  for (size_t n = 0; n < nHostAddrs; n++) {
    std::string bindAddrStr;
    const char *bindAddr = uHTTP::GetHostAddress(n, bindAddrStr);
    SSDPSearchSocket *ssdpSearchSocket = new SSDPSearchSocket();
    if (ssdpSearchSocket->open(bindAddr) == false) {
      delete ssdpSearchSocket;
      isAllHostOpened = false;
      continue;
    }
    add(ssdpSearchSocket);
  }
  return isAllHostOpened;
}

void SSDPSearchSocketList::close() {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    sock->close();
  }
  clear();
}
  
////////////////////////////////////////////////
// start/stop
////////////////////////////////////////////////
  
void SSDPSearchSocketList::start() {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    sock->start();
  }
}

void SSDPSearchSocketList::stop() {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    sock->stop();
  }
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

void SSDPSearchSocketList::clear() {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    delete sock;
  }
  Vector::clear();
}
