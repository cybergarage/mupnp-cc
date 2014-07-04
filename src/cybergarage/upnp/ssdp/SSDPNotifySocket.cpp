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

SSDPNotifySocket::SSDPNotifySocket(const std::string &bindAddr) {
  const char *addr = SSDP::ADDRESS;
  useIPv6Address = false;
  if (uHTTP::IsIPv6Address(bindAddr) == true) {
    addr = SSDP::GetIPv6Address();
    useIPv6Address = true;
  }
  open(addr, SSDP::PORT, bindAddr);
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
// post
////////////////////////////////////////////////

bool SSDPNotifySocket::post(SSDPNotifyRequest *req) {
  const char *ssdpAddr = SSDP::ADDRESS;
  if (useIPv6Address == true)
    ssdpAddr = SSDP::GetIPv6Address();
  req->setHost(ssdpAddr, SSDP::PORT);
  return HTTPMUSocket::post(req);
}

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
    //Thread.yield();
    SSDPPacket *packet = receive();
    if (packet == NULL)
      continue;
    if (ctrlPoint != NULL)
      ctrlPoint->notifyReceived(packet); 
  }
}
