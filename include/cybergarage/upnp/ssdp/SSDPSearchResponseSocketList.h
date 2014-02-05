/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPSearchResponseSocketList.h
*
*  Revision;
*
*  07/11/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDPSEARCHRESPONSESYSOCKETLIST_H_
#define _CLINK_SSDPSEARCHRESPONSESYSOCKETLIST_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponseSocket.h>

namespace CyberLink {
class ControlPoint;

class SSDPSearchResponseSocketList : public uHTTP::Vector  {
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
 public:
  SSDPSearchResponseSocketList();

  ~SSDPSearchResponseSocketList();

  ////////////////////////////////////////////////
  //  ControlPoint
  ////////////////////////////////////////////////

 public:
  void setControlPoint(ControlPoint *ctrlPoint);

  ////////////////////////////////////////////////
  //  get
  ////////////////////////////////////////////////
  
 public:
  SSDPSearchResponseSocket *getSSDPSearchResponseSocket(int n) {
    return (SSDPSearchResponseSocket *)get(n);
  }
  
  ////////////////////////////////////////////////
  //  open/close
  ////////////////////////////////////////////////
  
 public:
  bool open(int port);

  bool open() 
  {
    return open(SSDP::PORT);
  }
    
  void close();

  ////////////////////////////////////////////////
  //  start/stop
  ////////////////////////////////////////////////
  
 public:
  void start();

  void stop();

  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////

 public:
  bool post(SSDPSearchRequest *req);
  
  ////////////////////////////////////////////////
  //  clear
  ////////////////////////////////////////////////
  
 public:
  void clear();
};

}

#endif


