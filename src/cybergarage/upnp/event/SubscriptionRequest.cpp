/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SubscriptionRequest.cpp
*
*  Revision;
*
*  08/16/03
*    - first revision
*  09/02/03
*    - Giordano Sassaroli <sassarol@cefriel.it>
*    - Problem : NullpointerException thrown for devices whose description use absolute urls
*    - Error : the presence of a base url is not mandatory, the API code makes the assumption that control and event subscription urls are relative. If the baseUrl is not present, the request host and port should be extracted from the control/subscription url
*    - Description: The method setRequestHost/setService should be changed as follows
*  06/11/04
*    - Markus Thurner <markus.thurner@fh-hagenberg.at> (06/11/2004)
*    - Changed setServie() to get the host address from the SSDP Location field when the URLBase is null.
*
******************************************************************/

#include <string.h>

#include <string>
#include <sstream>

#include <cybergarage/upnp/event/SubscriptionRequest.h>
#include <uhttp/http/HTTP.h>
#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/Service.h>
#include <uhttp/net/URL.h>

using namespace std;
using namespace CyberLink;
using namespace uHTTP;
using namespace CyberXML;

////////////////////////////////////////////////
//  CALLBACK
////////////////////////////////////////////////

const char SubscriptionRequest::CALLBACK_START_WITH  = '<';
const char SubscriptionRequest::CALLBACK_END_WITH = '>';

////////////////////////////////////////////////
//  setRequest
////////////////////////////////////////////////

void SubscriptionRequest::setService(Service *service) {
  const char *eventSubURL = service->getEventSubURL();
    
  // Thanks for Giordano Sassaroli <sassarol@cefriel.it> (05/21/03)
  string relativeURL;
  HTTP::GetRelativeURL(eventSubURL, relativeURL);
  setURI(relativeURL);

  const char *urlBaseStr = "";

  Device *dev = service->getDevice();
  if (dev != NULL)
    urlBaseStr = dev->getURLBase();

  if (urlBaseStr == NULL || strlen(urlBaseStr) <= 0) {
    Device *rootDev = service->getRootDevice();
    if (rootDev != NULL)
      urlBaseStr = rootDev->getURLBase();
  }
    
  // Thansk for Markus Thurner <markus.thurner@fh-hagenberg.at> (06/11/2004)
  if (urlBaseStr == NULL || strlen(urlBaseStr) <= 0) {
    Device *rootDev = service->getRootDevice();
    if (rootDev != NULL)
      urlBaseStr = rootDev->getLocation();
  }

  // Thanks for Giordano Sassaroli <sassarol@cefriel.it> (05/21/03)
  if (urlBaseStr == NULL || strlen(urlBaseStr) <= 0) {
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
