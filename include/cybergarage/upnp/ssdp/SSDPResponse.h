/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPResponse.h
*
*  Revision;
*
*  07/10/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDPRESPONSE_H_
#define _CLINK_SSDPRESPONSE_H_

#include <uhttp/http/HTTPResponse.h>
#include <uhttp/http/HTTP.h>
#include <cybergarage/upnp/ssdp/SSDP.h>

namespace CyberLink {
class SSDPResponse : public uHTTP::HTTPResponse {
 public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  SSDPResponse() {
    setVersion(uHTTP::HTTP::VER_11);
  }

  ////////////////////////////////////////////////
  //  ST (SearchTarget)
  ////////////////////////////////////////////////

  void setST(const std::string &value) {
    setHeader(uHTTP::HTTP::ST, value);
  }

  const char *getST() {
    return getHeaderValue(uHTTP::HTTP::ST);
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
  //  MYNAME
  ////////////////////////////////////////////////
  
  void setMYNAME(const std::string &value) {
    setHeader(uHTTP::HTTP::MYNAME, value);
  }

  const char *getMYNAME() {
    return getHeaderValue(uHTTP::HTTP::MYNAME);
  }

  ////////////////////////////////////////////////
  //  CacheControl
  ////////////////////////////////////////////////

  void setLeaseTime(int value);

  int getLeaseTime();

  ////////////////////////////////////////////////
  //  getHeader
  ////////////////////////////////////////////////

  const char *getHeader(std::string &headerStr);

};

}

#endif

