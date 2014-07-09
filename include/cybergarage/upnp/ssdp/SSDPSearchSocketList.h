/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
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
    
class SSDPSearchSocketList : public uHTTP::Vector<SSDPSearchSocket>  {
public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SSDPSearchSocketList();
  ~SSDPSearchSocketList();

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  SSDPSearchSocket *getSSDPSearchSocket(size_t n) {
    return get(n);
  }
  
  void addSearchListener(SearchListener *listener);

  bool open();
  void close();
    
  void start();
  void stop();

};

}

#endif
