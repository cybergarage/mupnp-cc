/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: NotifyListener.h
*
*  Revision;
*
*  07/05/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_NOTIFYLISTENER_H_
#define _MUPMPCC_NOTIFYLISTENER_H_

#include <uhttp/util/Listener.h>
#include <mupnp/ssdp/SSDPPacket.h>

namespace mUPnP {

class NotifyListener : public uHTTP::Listener {
public:
  virtual bool deviceNotifyReceived(SSDPPacket *ssdpPacket) = 0;
};

}

#endif

