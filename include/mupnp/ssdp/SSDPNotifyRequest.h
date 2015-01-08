/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SSDPNotifyRequest.h
*
*  Revision;
*
*  07/10/03
*    - first revision
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
  
  SSDPNotifyRequest() {
    setMethod(uHTTP::HTTP::NOTIFY);
    setURI("*");
  }
};

}

#endif

