/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SSDPNotifySocketList.h
*
*  Revision;
*
*  07/11/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDPNOTIFYSOCKETLIST_H_
#define _CLINK_SSDPNOTIFYSOCKETLIST_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/ssdp/SSDPNotifySocket.h>

namespace CyberLink {
class ControlPoint;

class SSDPNotifySocketList : public uHTTP::Vector<SSDPNotifySocket>  {
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
 public:
  SSDPNotifySocketList();
  ~SSDPNotifySocketList();

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
 public:
  SSDPNotifySocket *getSSDPNotifySocket(size_t n) {
    return get(n);
  }

  ////////////////////////////////////////////////
  // ControlPoint
  ////////////////////////////////////////////////

 public:
  void setControlPoint(ControlPoint *ctrlPoint);

  ////////////////////////////////////////////////
  // open/close
  ////////////////////////////////////////////////
  
 public:
  bool open();
  void close();
  
  ////////////////////////////////////////////////
  // start/stop
  ////////////////////////////////////////////////
  
 public:
  void start();
  void stop();
};

}

#endif


