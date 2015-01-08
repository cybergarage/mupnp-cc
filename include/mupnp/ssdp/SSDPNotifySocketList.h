/******************************************************************
*
*  mUPnP for C++
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

#ifndef _MUPMPCC_SSDPNOTIFYSOCKETLIST_H_
#define _MUPMPCC_SSDPNOTIFYSOCKETLIST_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/util/Vector.h>
#include <mupnp/ssdp/SSDPNotifySocket.h>

namespace mUPnP {
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
  bool close();
  
  ////////////////////////////////////////////////
  // start/stop
  ////////////////////////////////////////////////
  
 public:
  bool start();
  bool stop();
};

}

#endif


