/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPREQUEST_H_
#define _MUPMPCC_SSDPREQUEST_H_

#include <mupnp/http/HTTP.h>
#include <mupnp/http/HTTPRequest.h>
#include <mupnp/ssdp/SSDP.h>

#include <mupnp/util/StringUtil.h>

namespace mUPnP {

class SSDPRequest : public uHTTP::HTTPRequest {
  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SSDPRequest()
  {
    setVersion(uHTTP::HTTP::VER_11);
  }

  ////////////////////////////////////////////////
  // NT
  ////////////////////////////////////////////////

  void setNT(const std::string& value)
  {
    setHeader(uHTTP::HTTP::NT, value);
  }

  const char* getNT()
  {
    return getHeaderValue(uHTTP::HTTP::NT);
  }

  ////////////////////////////////////////////////
  // NTS
  ////////////////////////////////////////////////

  void setNTS(const std::string& value)
  {
    setHeader(uHTTP::HTTP::NTS, value);
  }

  const char* getNTS()
  {
    return getHeaderValue(uHTTP::HTTP::NTS);
  }

  ////////////////////////////////////////////////
  // Location
  ////////////////////////////////////////////////

  void setLocation(const std::string& value)
  {
    setHeader(uHTTP::HTTP::LOCATION, value);
  }

  const char* getLocation()
  {
    return getHeaderValue(uHTTP::HTTP::LOCATION);
  }

  ////////////////////////////////////////////////
  // USN
  ////////////////////////////////////////////////

  void setUSN(const std::string& value)
  {
    setHeader(uHTTP::HTTP::USN, value);
  }

  const char* getUSN()
  {
    return getHeaderValue(uHTTP::HTTP::USN);
  }

  ////////////////////////////////////////////////
  // CacheControl
  ////////////////////////////////////////////////

  void setLeaseTime(int value)
  {
    std::string leaseTime;
    std::string buf;
    leaseTime = "max-age=";
    leaseTime += uHTTP::Integer2String(value, buf);
    setHeader(uHTTP::HTTP::CACHE_CONTROL, leaseTime.c_str());
  }

  int getLeaseTime()
  {
    const char* cacheCtrl = getHeaderValue(uHTTP::HTTP::CACHE_CONTROL);
    return SSDP::GetLeaseTime(cacheCtrl);
  }

  ////////////////////////////////////////////////
  // BOOTID.UPNP.ORG
  ////////////////////////////////////////////////

  void setBootID(int value)
  {
    setHeader(SSDP::BOOTID_UPNP_ORG, value);
  }

  int getBootID()
  {
    return getIntegerHeaderValue(SSDP::BOOTID_UPNP_ORG);
  }
};

}

#endif
