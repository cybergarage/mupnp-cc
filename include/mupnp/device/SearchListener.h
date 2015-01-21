/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
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

