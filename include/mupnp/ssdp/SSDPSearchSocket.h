/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHSOCKET_H_
#define _MUPMPCC_SSDPSEARCHSOCKET_H_

#include <string>

#include <mupnp/util/Thread.h>
#include <mupnp/net/HostInterface.h>
#include <mupnp/ssdp/SSDP.h>
#include <mupnp/ssdp/HTTPMUSocket.h>
#include <mupnp/device/SearchListener.h>

namespace mUPnP {
  
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



