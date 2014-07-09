/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SearchResponseListener.h
*
*  Revision;
*
*  07/05/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDPRESPONSELISTENER_H_
#define _CLINK_SSDPRESPONSELISTENER_H_

#include <uhttp/util/Listener.h>
#include <cybergarage/upnp/ssdp/SSDPPacket.h>

namespace CyberLink {

class SearchResponseListener : public uHTTP::Listener {
public:
  virtual void deviceSearchResponseReceived(SSDPPacket *ssdpPacket) = 0;
};

}

#endif

