/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPSearchSocket.h
*
*  Revision;
*
*  07/05/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDPSEARCHSOCKET_H_
#define _CLINK_SSDPSEARCHSOCKET_H_

#include <string>

#include <uhttp/util/ListenerList.h>
#include <uhttp/util/Thread.h>
#include <uhttp/net/HostInterface.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/ssdp/HTTPMUSocket.h>
#include <cybergarage/upnp/device/SearchListener.h>

namespace CyberLink {
class SSDPSearchSocket : public HTTPMUSocket, public uHTTP::Thread {
  bool useIPv6Address;
  uHTTP::ListenerList deviceSearchListenerList;

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  SSDPSearchSocket();
  SSDPSearchSocket(const std::string &bindAddr);
  ~SSDPSearchSocket();

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  bool open(const std::string &bindAddr);

  ////////////////////////////////////////////////
  //  deviceSearch
  ////////////////////////////////////////////////

 public:
  void addSearchListener(SearchListener *listener) {
    deviceSearchListenerList.add(listener);
  }    

  void removeSearchListener(SearchListener *listener) {
    deviceSearchListenerList.remove(listener);
  }    

  void performSearchListener(SSDPPacket *ssdpPacket) {
    int listenerSize = deviceSearchListenerList.size();
    for (int n = 0; n < listenerSize; n++) {
      SearchListener *listener = (SearchListener *)deviceSearchListenerList.get(n);
      listener->deviceSearchReceived(ssdpPacket);
    }
  }    

  ////////////////////////////////////////////////
  //  run  
  ////////////////////////////////////////////////

 public:
  void run();

};

}

#endif



