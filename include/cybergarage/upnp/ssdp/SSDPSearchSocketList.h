/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPSearchSocketList.h
*
*  Revision;
*
*  07/05/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDPSEARCHSOCKETLIST_H_
#define _CLINK_SSDPSEARCHSOCKETLIST_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/ssdp/SSDPSearchSocket.h>
#include <cybergarage/upnp/device/SearchListener.h>

namespace CyberLink {
class SSDPSearchSocketList : public uHTTP::Vector  {
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  SSDPSearchSocketList();

  ~SSDPSearchSocketList();

  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////
  
 public:
  SSDPSearchSocket *getSSDPSearchSocket(int n) {
    return (SSDPSearchSocket *)get(n);
  }
  
  void addSearchListener(SearchListener *listener);

  ////////////////////////////////////////////////
  //  open/close
  ////////////////////////////////////////////////
  
 public:
  bool open();

  void close();
  
  
  ////////////////////////////////////////////////
  //  start/stop
  ////////////////////////////////////////////////
  
 public:
  void start();

  void stop();

  ////////////////////////////////////////////////
  //  close
  ////////////////////////////////////////////////
  
 public:
  void clear();
};

}

#endif
