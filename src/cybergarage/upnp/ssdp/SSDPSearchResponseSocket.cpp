/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SSDPSearchResponseSocket.cpp
*
*  Revision;
*
*  08/14/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/ssdp/SSDPSearchResponseSocket.h>

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/upnp/Log.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

SSDPSearchResponseSocket::SSDPSearchResponseSocket() {
  setControlPoint(NULL);
}
  
SSDPSearchResponseSocket::~SSDPSearchResponseSocket() {
  stop();
  close();
}

////////////////////////////////////////////////
// run  
////////////////////////////////////////////////

void SSDPSearchResponseSocket::run() {
  ControlPoint *ctrlPoint = getControlPoint();
  while (isRunnable() == true) {
    SSDPPacket ssdpPacket;
    
    if (!receive(&ssdpPacket))
      continue;
    if (!ctrlPoint)
      continue;
    
    std::string ssdpSt;
    ssdpPacket.getST(ssdpSt);
    LogTrace("SSDP Search Response Received : %s", ssdpSt.c_str());
    
    ctrlPoint->searchResponseReceived(&ssdpPacket);
  }
}
