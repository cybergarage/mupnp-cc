/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPSearchRequest.h
*
*  Revision;
*
*  07/10/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDPSEARCHREQUEST_H_
#define _CLINK_SSDPSEARCHREQUEST_H_

#include <string>

#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/ssdp/SSDPRequest.h>
#include <cybergarage/upnp/device/ST.h>
#include <cybergarage/upnp/device/MAN.h>
#include <uhttp/net/HostInterface.h>
#include <cybergarage/upnp/event/SubscriptionResponse.h>

namespace CyberLink {
class SSDPSearchRequest : public SSDPRequest {
public:
  ////////////////////////////////////////////////
  //  Constructor
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
  //  HOST
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
