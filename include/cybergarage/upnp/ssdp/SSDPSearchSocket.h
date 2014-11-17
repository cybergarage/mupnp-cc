/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
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

#include <uhttp/util/Thread.h>
#include <uhttp/net/HostInterface.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/ssdp/HTTPMUSocket.h>
#include <cybergarage/upnp/device/SearchListener.h>

namespace CyberLink {
  
typedef uHTTP::ListenerList<SearchListener> SearchListenerList;
  
class SSDPSearchSocket : public HTTPMUSocket, public uHTTP::Thread {
  bool useIPv6Address;
  SearchListenerList deviceSearchListenerList;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  SSDPSearchSocket();
  ~SSDPSearchSocket();

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  bool open(const std::string &bindAddr);

  ////////////////////////////////////////////////
  // deviceSearch
  ////////////////////////////////////////////////

 public:
  void addSearchListener(SearchListener *listener) {
    deviceSearchListenerList.add(listener);
  }    

  void removeSearchListener(SearchListener *listener) {
    deviceSearchListenerList.remove(listener);
  }    

  bool performSearchListener(SSDPPacket *ssdpPacket);

  ////////////////////////////////////////////////
  // run  
  ////////////////////////////////////////////////

 public:
  void run();

};

}

#endif



