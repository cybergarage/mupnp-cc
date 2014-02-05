/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPRequest.h
*
*  Revision;
*
*  07/10/03
*    - first revision
*  03/16/04
*    - Thanks for Darrell Young
*    - Fixed to set v1.1 to the HTTP version.;
*  03/03/05
*    - Changed setLeaseTime() not to use iostream for TRON.
*
******************************************************************/

#ifndef _CLINK_SSDPREQUEST_H_
#define _CLINK_SSDPREQUEST_H_

#include <uhttp/http/HTTP.h>
#include <uhttp/http/HTTPRequest.h>
#include <cybergarage/upnp/ssdp/SSDP.h>

#include <uhttp/util/StringUtil.h>

namespace CyberLink {
class SSDPRequest : public uHTTP::HTTPRequest {
 public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  SSDPRequest() {
    setVersion(uHTTP::HTTP::VER_11);
  }

  ////////////////////////////////////////////////
  //  NT
  ////////////////////////////////////////////////

  void setNT(const std::string &value) {
    setHeader(uHTTP::HTTP::NT, value);
  }

  const char *getNT() {
    return getHeaderValue(uHTTP::HTTP::NT);
  }

  ////////////////////////////////////////////////
  //  NTS
  ////////////////////////////////////////////////

  void setNTS(const std::string &value) {
    setHeader(uHTTP::HTTP::NTS, value);
  }

  const char *getNTS() {
    return getHeaderValue(uHTTP::HTTP::NTS);
  }

  ////////////////////////////////////////////////
  //  Location
  ////////////////////////////////////////////////

  void setLocation(const std::string &value) {
    setHeader(uHTTP::HTTP::LOCATION, value);
  }

  const char *getLocation() {
    return getHeaderValue(uHTTP::HTTP::LOCATION);
  }

  ////////////////////////////////////////////////
  //  USN
  ////////////////////////////////////////////////

  void setUSN(const std::string &value) {
    setHeader(uHTTP::HTTP::USN, value);
  }

  const char *getUSN() {
    return getHeaderValue(uHTTP::HTTP::USN);
  }

  ////////////////////////////////////////////////
  //  CacheControl
  ////////////////////////////////////////////////

  void setLeaseTime(int value) {
    std::string leaseTime;
    std::string buf;
    leaseTime = "max-age=";
    leaseTime += uHTTP::Integer2String(value, buf);
    setHeader(uHTTP::HTTP::CACHE_CONTROL,  leaseTime.c_str());
  }

  int getLeaseTime() {
    const char *cacheCtrl = getHeaderValue(uHTTP::HTTP::CACHE_CONTROL);
    return SSDP::GetLeaseTime(cacheCtrl);
  }
};

}

#endif

