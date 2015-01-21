/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHRESPONSE_H_
#define _MUPMPCC_SSDPSEARCHRESPONSE_H_

#include <sstream>

#include <mupnp/UPnP.h>
#include <mupnp/Device.h>
#include <mupnp/ssdp/SSDPResponse.h>

namespace mUPnP {
class SSDPSearchResponse : public SSDPResponse {
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

public:
  
  SSDPSearchResponse() {
    setStatusCode(uHTTP::HTTP::OK_REQUEST);
    setCacheControl(Device::DEFAULT_LEASE_TIME);
    std::string buf;
    setHeader(uHTTP::HTTP::SERVER, UPnP::GetServerName(buf));
    setHeader(uHTTP::HTTP::EXT, "");
  }
};

}

#endif
