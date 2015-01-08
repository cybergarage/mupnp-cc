/******************************************************************
*
*  mUPnP for C++
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

#include <mupnp/ssdp/SSDPSearchResponseSocket.h>

#include <mupnp/ControlPoint.h>
#include <mupnp/Log.h>

using namespace mUPnP;

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
  while (isRunnable() == true) {
    SSDPPacket ssdpPacket;
    
    if (!receive(&ssdpPacket))
      break;
    
    ControlPoint *ctrlPoint = getControlPoint();
    if (!ctrlPoint)
      break;
    
    std::string ssdpSt, ssdpNTS, ssdpNT, ssdpLocation;
    ssdpPacket.getST(ssdpSt);
    ssdpPacket.getNTS(ssdpNTS);
    ssdpPacket.getNT(ssdpNT);
    ssdpPacket.getLocation(ssdpLocation);
    LogTrace("SSDP Search Response Received : %s %s %s %s", ssdpSt.c_str(), ssdpNTS.c_str(), ssdpNT.c_str(), ssdpLocation.c_str());
    
    ctrlPoint->searchResponseReceived(&ssdpPacket);
  }
}
