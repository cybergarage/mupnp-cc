/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPNPDUMP_CTRLPOINT_H_
#define _MUPNPDUMP_CTRLPOINT_H_

#include <mupnp/mUPnP.h>

using namespace mUPnP;

class CtrlPoint : public ControlPoint, public NotifyListener, public EventListener, public SearchResponseListener {

  public:
  CtrlPoint();

  ////////////////////////////////////////////////
  //	Listener
  ////////////////////////////////////////////////

  public:
  bool deviceNotifyReceived(SSDPPacket* packet);
  bool deviceSearchResponseReceived(SSDPPacket* packet);
  bool eventNotifyReceived(const std::string& uuid, long seq, const std::string& name, const std::string& value);

  void print();
};

#endif
