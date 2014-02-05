/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: NotifyListener.h
*
*  Revision;
*
*  07/05/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_NOTIFYLISTENER_H_
#define _CLINK_NOTIFYLISTENER_H_

#include <cybergarage/upnp/ssdp/SSDPPacket.h>

namespace CyberLink {
class NotifyListener {
public:
  virtual void deviceNotifyReceived(SSDPPacket *ssdpPacket) = 0;
};

}

#endif

