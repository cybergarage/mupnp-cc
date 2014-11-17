/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SSDPSearchSocket.cpp
*
*  Revision;
*
*  08/14/03
*    - first revision
*  04/20/05
*    - Mikael Hakman <mhakman@dkab.net>
*    - Added close() in stop().
*    - Added test for null return from receive() in run().
*
******************************************************************/

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/upnp/ssdp/SSDPSearchSocket.h>
#include <cybergarage/upnp/Log.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

SSDPSearchSocket::SSDPSearchSocket() {
}

SSDPSearchSocket::~SSDPSearchSocket() {
  stop();
  close();
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool SSDPSearchSocket::open(const std::string &bindAddr) {
  const char *addr = SSDP::ADDRESS;
  useIPv6Address = false;
  if (uHTTP::IsIPv6Address(bindAddr) == true) {
    addr = SSDP::GetIPv6Address();
    useIPv6Address = true;
  }
  return HTTPMUSocket::open(addr, SSDP::PORT, bindAddr);
}

////////////////////////////////////////////////
// performSearchListener
////////////////////////////////////////////////

bool SSDPSearchSocket::performSearchListener(SSDPPacket *ssdpPacket) {
  bool areAllListnersSuccess = true;
  size_t listenerSize = deviceSearchListenerList.size();
  for (size_t n = 0; n < listenerSize; n++) {
    SearchListener *listener = deviceSearchListenerList.get(n);
    if (listener->deviceSearchReceived(ssdpPacket) == false) {
      areAllListnersSuccess = false;
    }
  }
  return areAllListnersSuccess;
}

////////////////////////////////////////////////
// run  
////////////////////////////////////////////////

void SSDPSearchSocket::run() {
  while (isRunnable() == true) {
    SSDPPacket ssdpPacket;
    if (!receive(&ssdpPacket))
      continue;
    
    if (!ssdpPacket.isSearchRequest())
      continue;
    
    std::string ssdpST;
    ssdpPacket.getST(ssdpST);
    LogTrace("SSDP Search Received : %s", ssdpST.c_str());
    
    if (ssdpPacket.isDiscover() == false)
      continue;
    
    performSearchListener(&ssdpPacket);
  }
}
