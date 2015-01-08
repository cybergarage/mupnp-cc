/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SearchListener.h
*
*  Revision;
*
*  07/05/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHLISTENER_H_
#define _MUPMPCC_SSDPSEARCHLISTENER_H_

#include <uhttp/util/Listener.h>
#include <mupnp/ssdp/SSDPPacket.h>

namespace mUPnP {
    
class SearchListener : public uHTTP::Listener {
public:
  virtual bool deviceSearchReceived(SSDPPacket *ssdpPacket) = 0;
};

}

#endif

