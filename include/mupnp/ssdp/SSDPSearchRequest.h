/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHREQUEST_H_
#define _MUPMPCC_SSDPSEARCHREQUEST_H_

#include <string>

#include <mupnp/ssdp/SSDP.h>
#include <mupnp/ssdp/SSDPRequest.h>
#include <mupnp/device/ST.h>
#include <mupnp/device/MAN.h>
#include <uhttp/net/HostInterface.h>
#include <mupnp/event/SubscriptionResponse.h>

namespace mUPnP {
class SSDPSearchRequest : public SSDPRequest {
public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SSDPSearchRequest(const std::string &serachTarget, int mx) {
    init(serachTarget, mx);
  }
  
  SSDPSearchRequest(const std::string &serachTarget) {
    init(serachTarget, SSDP::DEFAULT_MSEARCH_MX);
  }
  
  SSDPSearchRequest() {
    init(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
  }

private:

  void init(const std::string &serachTarget, int mx) {
    setMethod(uHTTP::HTTP::M_SEARCH);
    setURI("*");

    setHeader(uHTTP::HTTP::ST, serachTarget);
    setHeader(uHTTP::HTTP::MX, mx);
    std::string man;
    man = "\"";
    man += MAN::DISCOVER;
    man += "\"";
    setHeader(uHTTP::HTTP::MAN, man.c_str());
  }

  ////////////////////////////////////////////////
  // HOST
  ////////////////////////////////////////////////

public:
  
  void setLocalAddress(const std::string &bindAddr) {
    const char *ssdpAddr = SSDP::ADDRESS;
    if (uHTTP::IsIPv6Address(bindAddr) == true)
      ssdpAddr = SSDP::GetIPv6Address();
    setHost(ssdpAddr, SSDP::PORT);
  }

};

}

#endif
