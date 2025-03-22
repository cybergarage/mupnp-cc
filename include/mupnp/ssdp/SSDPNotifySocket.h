/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPNOTIFYSOCKET_H_
#define _MUPMPCC_SSDPNOTIFYSOCKET_H_

#include <mupnp/net/HostInterface.h>
#include <mupnp/ssdp/HTTPMUSocket.h>
#include <mupnp/ssdp/SSDP.h>
#include <mupnp/ssdp/SSDPNotifyRequest.h>
#include <mupnp/util/Thread.h>

namespace mUPnP {
class ControlPoint;

class SSDPNotifySocket : public HTTPMUSocket, public uHTTP::Thread {
  ControlPoint* controlPoint;

  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SSDPNotifySocket();
  ~SSDPNotifySocket();

  ////////////////////////////////////////////////
  // ControlPoint
  ////////////////////////////////////////////////

  void setControlPoint(ControlPoint* ctrlp)
  {
    controlPoint = ctrlp;
  }

  ControlPoint* getControlPoint()
  {
    return controlPoint;
  }

  ////////////////////////////////////////////////
  // open
  ////////////////////////////////////////////////

  bool open(const std::string& bindAddr);

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

  bool post(SSDPNotifyRequest* req, const std::string& ifAddr);

  ////////////////////////////////////////////////
  // run
  ////////////////////////////////////////////////

  void run();
};

}

#endif
