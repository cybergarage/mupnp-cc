/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SSDPNotifySocket.cpp
*
*  Revision;
*
*  08/14/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/ssdp/SSDPNotifySocket.h>
#include <cybergarage/upnp/ControlPoint.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

SSDPNotifySocket::SSDPNotifySocket() {
  setControlPoint(NULL);
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

SSDPNotifySocket::~SSDPNotifySocket() {
  stop();
  close();
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool SSDPNotifySocket::open(const std::string &bindAddr) {
  const char *addr = SSDP::ADDRESS;
  if (uHTTP::IsIPv6Address(bindAddr) == true) {
    addr = SSDP::GetIPv6Address();
  }
  return HTTPMUSocket::open(addr, SSDP::PORT, bindAddr);
}

////////////////////////////////////////////////
// post
////////////////////////////////////////////////

bool SSDPNotifySocket::post(SSDPNotifyRequest *req, const std::string &ifAddr) {
  const char *ssdpAddr = SSDP::ADDRESS;
  if (uHTTP::IsIPv6Address(ifAddr) == true)
    ssdpAddr = SSDP::GetIPv6Address();
  req->setHost(ssdpAddr, SSDP::PORT);
  return HTTPMUSocket::post(ssdpAddr, SSDP::PORT, req);
}

////////////////////////////////////////////////
// run  
////////////////////////////////////////////////

void SSDPNotifySocket::run() {
  ControlPoint *ctrlPoint = getControlPoint();
  while (isRunnable() == true) {
    SSDPPacket packet;
    if (!receive(&packet))
      continue;
    if (!ctrlPoint)
      continue;
    ctrlPoint->notifyReceived(&packet);
  }
}
