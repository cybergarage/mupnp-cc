/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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
  int nServers = size();
  for (int n = 0; n < nServers; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    sock->addSearchListener(listener);
  }
}    

////////////////////////////////////////////////
// open/close
////////////////////////////////////////////////
  
bool SSDPSearchSocketList::open()  {
  int nHostAddrs = uHTTP::GetNHostAddresses();
  for (int n = 0; n < nHostAddrs; n++) {
    std::string bindAddrStr;
    const char *bindAddr = uHTTP::GetHostAddress(n, bindAddrStr);
    SSDPSearchSocket *ssdpSearchSocket = new SSDPSearchSocket(bindAddr);
    add(ssdpSearchSocket);
  }
  return true;
}

void SSDPSearchSocketList::close() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    sock->close();
  }
  clear();
}
  
////////////////////////////////////////////////
// start/stop
////////////////////////////////////////////////
  
void SSDPSearchSocketList::start() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    sock->start();
  }
}

void SSDPSearchSocketList::stop() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    sock->stop();
  }
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

void SSDPSearchSocketList::clear() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPSearchSocket *sock = getSSDPSearchSocket(n);
    delete sock;
  }
  Vector::clear();
}
