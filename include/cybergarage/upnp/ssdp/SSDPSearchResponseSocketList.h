/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
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

class SSDPSearchResponseSocketList : public uHTTP::Vector<SSDPSearchResponseSocket>  {

public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  SSDPSearchResponseSocketList();
  ~SSDPSearchResponseSocketList();

  ////////////////////////////////////////////////
  // ControlPoint
  ////////////////////////////////////////////////

  void setControlPoint(ControlPoint *ctrlPoint);

  ////////////////////////////////////////////////
  // get
  ////////////////////////////////////////////////
  
  SSDPSearchResponseSocket *getSSDPSearchResponseSocket(size_t n) {
    return get(n);
  }
  
  ////////////////////////////////////////////////
  // open/close
  ////////////////////////////////////////////////
  
  bool open(int port);

  bool open()  {
    return open(SSDP::PORT);
  }
    
  bool close();

  ////////////////////////////////////////////////
  // start/stop
  ////////////////////////////////////////////////
  
  bool start();
  bool stop();

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////

 public:
  bool post(SSDPSearchRequest *req);
};

}

#endif


