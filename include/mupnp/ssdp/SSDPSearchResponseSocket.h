/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHRESPONSESYSOCKET_H_
#define _MUPMPCC_SSDPSEARCHRESPONSESYSOCKET_H_

#include <mupnp/util/Thread.h>
#include <mupnp/ssdp/HTTPUSocket.h>
#include <mupnp/ssdp/SSDPSearchResponse.h>
#include <mupnp/ssdp/SSDPSearchRequest.h>

namespace mUPnP {
class ControlPoint;

class SSDPSearchResponseSocket : public HTTPUSocket, public uHTTP::Thread {
  ControlPoint *controlPoint;

public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SSDPSearchResponseSocket();
  ~SSDPSearchResponseSocket();

  ////////////////////////////////////////////////
  // ControlPoint  
  ////////////////////////////////////////////////
  
  void setControlPoint(ControlPoint *ctrlp) {
    controlPoint = ctrlp;
  }

  ControlPoint *getControlPoint() {
    return controlPoint;
  }

  ////////////////////////////////////////////////
  // run  
  ////////////////////////////////////////////////

  void run();
  
  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

  bool post(const std::string &addr, int port, SSDPSearchResponse *res) {
    std::string headerStr;
    return HTTPUSocket::post(addr, port, res->getHeader(headerStr));
  }

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

  bool post(const std::string &addr, int port, SSDPSearchRequest *req) {
    std::string buf;
    return HTTPUSocket::post(addr, port, req->toString(buf));
  }
};

}

#endif


