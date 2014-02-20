/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPNotifySocketList.cpp
*
*  Revision;
*
*  08/14/03
*    - first revision
*  07/17/04
*    - Added the destructor and clear().
*
******************************************************************/

#include <cybergarage/upnp/ssdp/SSDPNotifySocketList.h>

using namespace std;
using namespace CyberLink;
using namespace uHTTP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
  
SSDPNotifySocketList::SSDPNotifySocketList()  {
}

SSDPNotifySocketList::~SSDPNotifySocketList()  {
  stop();
  close();
}

////////////////////////////////////////////////
// ControlPoint
////////////////////////////////////////////////

void SSDPNotifySocketList::setControlPoint(ControlPoint *ctrlPoint) {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPNotifySocket *sock = getSSDPNotifySocket(n);
    sock->setControlPoint(ctrlPoint);
  }
}

////////////////////////////////////////////////
// open/close
////////////////////////////////////////////////
  
bool SSDPNotifySocketList::open()  {
  int nHostAddrs = GetNHostAddresses();
  for (int n = 0; n < nHostAddrs; n++) {
    string bindAddr;
    GetHostAddress(n, bindAddr);
    SSDPNotifySocket *ssdpNotifySocket = new SSDPNotifySocket(bindAddr.c_str());
    add(ssdpNotifySocket);
  }
  return true;
}
  
void SSDPNotifySocketList::close() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPNotifySocket *sock = getSSDPNotifySocket(n);
    sock->close();
  }
  clear();
}
  
////////////////////////////////////////////////
// start/stop
////////////////////////////////////////////////
  
void SSDPNotifySocketList::start() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPNotifySocket *sock = getSSDPNotifySocket(n);
    sock->start();
  }
}

void SSDPNotifySocketList::stop() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPNotifySocket *sock = getSSDPNotifySocket(n);
    sock->stop();
  }
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

void SSDPNotifySocketList::clear() {
  int nSockets = size();
  for (int n = 0; n < nSockets; n++) {
    SSDPNotifySocket *sock = getSSDPNotifySocket(n);
    delete sock;
  }
  Vector::clear();
}
