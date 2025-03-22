/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPNOTIFYREQUEST_H_
#define _MUPMPCC_SSDPNOTIFYREQUEST_H_

#include <sstream>

#include <mupnp/ssdp/SSDPRequest.h>

namespace mUPnP {

class SSDPNotifyRequest : public SSDPRequest {
  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SSDPNotifyRequest()
  {
    setMethod(uHTTP::HTTP::NOTIFY);
    setURI("*");
  }
};

}

#endif
