/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPNotifySocket.h
*
*  Revision;
*
*  07/11/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDPNOTIFYSOCKET_H_
#define _CLINK_SSDPNOTIFYSOCKET_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/util/Thread.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/ssdp/HTTPMUSocket.h>
#include <cybergarage/upnp/ssdp/SSDPNotifyRequest.h>

namespace CyberLink {
class ControlPoint;

class SSDPNotifySocket : public HTTPMUSocket, public uHTTP::Thread {
  ControlPoint *controlPoint;
  bool useIPv6Address;

 public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  SSDPNotifySocket(const std::string &bindAddr);
  ~SSDPNotifySocket();

  ////////////////////////////////////////////////
  //  ControlPoint  
  ////////////////////////////////////////////////
  
  void setControlPoint(ControlPoint *ctrlp) {
    controlPoint = ctrlp;
  }

  ControlPoint *getControlPoint() {
    return controlPoint;
  }

  ////////////////////////////////////////////////
  //  post (SSDPNotifySocket)
  ////////////////////////////////////////////////

  bool post(SSDPNotifyRequest *req);

  ////////////////////////////////////////////////
  //  run  
  ////////////////////////////////////////////////

  void run();
  
};

}

#endif


