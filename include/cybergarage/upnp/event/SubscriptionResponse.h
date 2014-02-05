/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SubscriptionResponse.h
*
*  Revision;
*
*  08/16/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SUBSCRIPTIONRESPONSE_H_
#define _CLINK_SUBSCRIPTIONRESPONSE_H_

#include <uhttp/http/HTTPResponse.h>
#include <cybergarage/upnp/UPnP.h>
#include <cybergarage/upnp/event/Subscription.h>

#include <string>

namespace CyberLink {
class SubscriptionResponse : public uHTTP::HTTPResponse {
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  SubscriptionResponse() {
    std::string serverName;
    setServer(UPnP::GetServerName(serverName));
  }

  SubscriptionResponse(uHTTP::HTTPResponse *httpRes) {
    set(httpRes);
  }

  ////////////////////////////////////////////////
  //  Error
  ////////////////////////////////////////////////

public:
  
  void setResponse(int code) {
    setStatusCode(code);
    setContentLength(0);
  }
  
  ////////////////////////////////////////////////
  //  Error
  ////////////////////////////////////////////////

 public:
  void setErrorResponse(int code) {
    setStatusCode(code);
    setContentLength(0);
  }
    
  ////////////////////////////////////////////////
  //  SID
  ////////////////////////////////////////////////

 public:
  void setSID(const std::string &sid) {
    std::string buf;
    setHeader(uHTTP::HTTP::SID, Subscription::toSIDHeaderString(sid, buf));
  }

  const char *getSID(std::string &buf) {
    return Subscription::GetSID(getHeaderValue(uHTTP::HTTP::SID), buf);
  }

  ////////////////////////////////////////////////
  //  Timeout
  ////////////////////////////////////////////////

 public:
  void setTimeout(long value) {
    std::string buf;
    setHeader(uHTTP::HTTP::TIMEOUT, Subscription::toTimeoutHeaderString(value, buf));
  }

  long getTimeout() {
    return Subscription::GetTimeout(getHeaderValue(uHTTP::HTTP::TIMEOUT));
  }
};

}

#endif

