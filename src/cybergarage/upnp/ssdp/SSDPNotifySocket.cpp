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
#include <cybergarage/upnp/Log.h>

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
  
  bool isSuccess = HTTPMUSocket::post(ssdpAddr, SSDP::PORT, req);
  
  if (isSuccess) {
    LogTrace("SSDP Notify Request (%d) : %s", isSuccess, req->getNT());
  }
  else {
    LogWarn("SSDP Notify Request (%d) : %s", isSuccess, req->getNT());
  }
  
  return isSuccess;
}

////////////////////////////////////////////////
// run  
////////////////////////////////////////////////

void SSDPNotifySocket::run() {
  ControlPoint *ctrlPoint = getControlPoint();
  while (isRunnable() == true) {
    SSDPPacket ssdpPacket;
    if (!receive(&ssdpPacket))
      continue;
    
    std::string ssdpNTS, ssdpNT;
    ssdpPacket.getNTS(ssdpNTS);
    ssdpPacket.getNT(ssdpNT);
    
    LogTrace("SSDP Notify Received : %s %s", ssdpNTS.c_str(), ssdpNT.c_str());
    
    if (!ctrlPoint)
      continue;
    
    ctrlPoint->notifyReceived(&ssdpPacket);
  }
}
