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

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponseSocket.h>

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
  while (isRunnable() == true) {
    SSDPPacket packet;
    if (!receive(&packet))
      continue;
    ControlPoint *ctrlPoint = getControlPoint();
    if (!ctrlPoint)
      continue;
    ctrlPoint->searchResponseReceived(&packet);
  }
}
