/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: upnpdump.cpp
*
*  Revision;
*
*  08/22/03
*    - first revision
*
******************************************************************/

#ifndef _TESTCTRLPOINT_H_
#define _TESTCTRLPOINT_H_

#include <mupnp/mUPnP.h>

using namespace mUPnP;

class TestCtrlPoint : public ControlPoint , public NotifyListener, public EventListener, public SearchResponseListener
{

public:

  TestCtrlPoint();
  
  ////////////////////////////////////////////////
  //  Listener
  ////////////////////////////////////////////////
  
public:

  bool deviceNotifyReceived(SSDPPacket *packet);
  bool deviceSearchResponseReceived(SSDPPacket *packet);
  bool eventNotifyReceived(const std::string &uuid, long seq, const std::string &name, const std::string &value);

  void print();

};

#endif

