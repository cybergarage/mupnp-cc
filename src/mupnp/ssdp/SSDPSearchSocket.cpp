/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/ControlPoint.h>
#include <mupnp/ssdp/SSDPSearchSocket.h>
#include <mupnp/Log.h>

using namespace mUPnP;

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
      break;
    
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
