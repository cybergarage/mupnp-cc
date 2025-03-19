/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string.h>

#include <string>
#include <sstream>

#include <mupnp/event/SubscriptionRequest.h>
#include <mupnp/http/HTTP.h>
#include <mupnp/Device.h>
#include <mupnp/Service.h>
#include <mupnp/net/URL.h>

using namespace std;
using namespace mUPnP;
using namespace uHTTP;

////////////////////////////////////////////////
// CALLBACK
////////////////////////////////////////////////

const char SubscriptionRequest::CALLBACK_START_WITH  = '<';
const char SubscriptionRequest::CALLBACK_END_WITH = '>';

////////////////////////////////////////////////
// setRequest
////////////////////////////////////////////////

void SubscriptionRequest::setService(Service *service) {
  const char *eventSubURL = service->getEventSubURL();
    
  // Thanks for Giordano Sassaroli <sassarol@cefriel.it> (05/21/03)
  string relativeURL;
  HTTP::GetRelativeURL(eventSubURL, relativeURL);
  setURI(relativeURL);

  const char *urlBaseStr = "";

  Device *dev = service->getDevice();
  if (dev)
    urlBaseStr = dev->getURLBase();

  if (!urlBaseStr || strlen(urlBaseStr) <= 0) {
    Device *rootDev = service->getRootDevice();
    if (rootDev)
      urlBaseStr = rootDev->getURLBase();
  }
    
  // Thansk for Markus Thurner <markus.thurner@fh-hagenberg.at> (06/11/2004)
  if (!urlBaseStr || strlen(urlBaseStr) <= 0) {
    Device *rootDev = service->getRootDevice();
    if (rootDev)
      urlBaseStr = rootDev->getLocation();
  }

  // Thanks for Giordano Sassaroli <sassarol@cefriel.it> (05/21/03)
  if (!urlBaseStr || strlen(urlBaseStr) <= 0) {
    if (HTTP::IsAbsoluteURL(eventSubURL))
      urlBaseStr = eventSubURL;
  }

  string reqHostBuf;
  const char *reqHost = HTTP::GetHost(urlBaseStr, reqHostBuf);
  int reqPort = HTTP::GetPort(urlBaseStr);
  
  setHost(reqHost, reqPort);
  setRequestHost(reqHost);
  setRequestPort(reqPort);
}

void SubscriptionRequest::setSubscribeRequest(Service *service, const std::string &callback, long timeout) {
  setMethod(Subscription::SUBSCRIBE_METHOD);
  setService(service);
  setCallback(callback);
  setNT(NT::EVENT);
  setTimeout(timeout);
}

void SubscriptionRequest::setRenewRequest(Service *service, const std::string &uuid, long timeout) {
  setMethod(Subscription::SUBSCRIBE_METHOD);
  setService(service);
  setSID(uuid);
  setTimeout(timeout);
}

void SubscriptionRequest::setUnsubscribeRequest(Service *service) {
  setMethod(Subscription::UNSUBSCRIBE_METHOD);
  setService(service);
  setSID(service->getSID());
}
