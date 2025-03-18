/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SUBSCRIPTIONREQUEST_H_
#define _MUPMPCC_SUBSCRIPTIONREQUEST_H_

#include <mupnp/http/HTTPRequest.h>
#include <mupnp/http/HTTP.h>
#include <mupnp/event/Subscription.h>
#include <mupnp/device/NT.h>
#include <mupnp/event/SubscriptionRequest.h>
#include <mupnp/event/SubscriptionResponse.h>

#include <string>

namespace mUPnP {
class Service;

class SubscriptionRequest : public uHTTP::HTTPRequest {
  SubscriptionResponse subRes;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  SubscriptionRequest() {
  }

  SubscriptionRequest(uHTTP::HTTPRequest *httpReq) {
    set(httpReq);
  }
  
  ////////////////////////////////////////////////
  // setRequest
  ////////////////////////////////////////////////

private:

  void setService(Service *service);

 public:
  void setSubscribeRequest(Service *service, const std::string &callback, long timeout);
  void setRenewRequest(Service *service, const std::string &uuid, long timeout);
  void setUnsubscribeRequest(Service *service);

  ////////////////////////////////////////////////
  // NT
  ////////////////////////////////////////////////

 public:
  void setNT(const std::string &value) {
    setHeader(uHTTP::HTTP::NT, value);
  }

  const char *getNT() {
    return getHeaderValue(uHTTP::HTTP::NT);
  }
  
  ////////////////////////////////////////////////
  // CALLBACK
  ////////////////////////////////////////////////

private:

  static const char CALLBACK_START_WITH;
  static const char CALLBACK_END_WITH;

 public:
  void setCallback(const std::string &value) {
    setStringHeader(uHTTP::HTTP::CALBACK, value, CALLBACK_START_WITH, CALLBACK_END_WITH);
  }
  
  const char *getCallback(std::string &buf) {
    return getStringHeaderValue(uHTTP::HTTP::CALBACK, CALLBACK_START_WITH, CALLBACK_END_WITH, buf);
  }

  bool hasCallback() {
    std::string callback;
    getCallback(callback);
    return (0 < callback.length()) ? true : false;
  }

  ////////////////////////////////////////////////
  // SID
  ////////////////////////////////////////////////

 public:
  void setSID(const std::string &sid) {
    std::string buf;
    setHeader(uHTTP::HTTP::SID, Subscription::toSIDHeaderString(sid, buf));
  }

  const char *getSID(std::string &buf) {
    return Subscription::GetSID(getHeaderValue(uHTTP::HTTP::SID), buf);
  }
  
  bool hasSID() {
    std::string sid;
    getSID(sid);
    return (0 < sid.length()) ? true : false;
  }

  ////////////////////////////////////////////////
  // Timeout
  ////////////////////////////////////////////////

 public:
  void setTimeout(long value) {
    std::string buf;
    setHeader(uHTTP::HTTP::TIMEOUT, Subscription::toTimeoutHeaderString(value, buf));
  }

  long getTimeout() {
    return Subscription::GetTimeout(getHeaderValue(uHTTP::HTTP::TIMEOUT));
  }

  ////////////////////////////////////////////////
  // post (Response)
  ////////////////////////////////////////////////

 public:
  uHTTP::HTTP::StatusCode post(SubscriptionResponse *subRes) {
    return HTTPRequest::post(subRes);
  }

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

 public:
  SubscriptionResponse *post() {
    uHTTP::HTTPResponse *httpRes = HTTPRequest::post(getRequestHost(), getRequestPort());
    subRes.set(httpRes);
    return &subRes;
  }
};

}

#endif

