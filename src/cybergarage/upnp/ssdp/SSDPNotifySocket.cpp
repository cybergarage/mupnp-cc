/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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
//  post (SSDPNotifySocket)
////////////////////////////////////////////////

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

SSDPNotifySocket::~SSDPNotifySocket() {
  stop();
  close();
}

////////////////////////////////////////////////
//  post (SSDPNotifySocket)
////////////////////////////////////////////////

bool SSDPNotifySocket::post(SSDPNotifyRequest *req) {
  const char *ssdpAddr = SSDP::ADDRESS;
  if (useIPv6Address == true)
    ssdpAddr = SSDP::GetIPv6Address();
  req->setHost(ssdpAddr, SSDP::PORT);
  return HTTPMUSocket::post(req);
}

////////////////////////////////////////////////
//  run  
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
