/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ServiceData.h
*
*  Revision;
*
*  07/20/03
*    - first revision
*  03/30/05
*    - Removed setDescriptionURL() and getDescriptionURL().
*
******************************************************************/

#ifndef _CLINK_SERVICEDATA_H_
#define _CLINK_SERVICEDATA_H_

#include <uhttp/util/ListenerList.h>
#include <cybergarage/xml/Node.h>
#include <cybergarage/xml/NodeData.h>
#include <cybergarage/upnp/event/SubscriberList.h>

#include <string>

namespace CyberLink {
class QueryListener;
class Service;

class ServiceData : public CyberXML::NodeData {
  Service *service;

  std::string sid;
  long timeout;

  uHTTP::ListenerList controlActionListenerList;
  SubscriberList subscriberList;

  CyberXML::Node *scpdNode;

 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  ServiceData();

  ~ServiceData();

  ////////////////////////////////////////////////
  // Service
  ////////////////////////////////////////////////

 public:
  void setService(Service *serv) {
    service = serv;
  }

  Service *getService() {
    return service;
  }

  ////////////////////////////////////////////////
  // controlActionListenerList
  ////////////////////////////////////////////////

  uHTTP::ListenerList *getControlActionListenerList() {
    return &controlActionListenerList;
  }

  ////////////////////////////////////////////////
  // scpdNode
  ////////////////////////////////////////////////

  CyberXML::Node *getSCPDNode() {
    return scpdNode;
  }

  void setSCPDNode(CyberXML::Node *node);

  ////////////////////////////////////////////////
  // SubscriberList
  ////////////////////////////////////////////////

  SubscriberList *getSubscriberList() {
    return &subscriberList;
  }

  ////////////////////////////////////////////////
  // SID
  ////////////////////////////////////////////////

  const char *getSID() {
    return sid.c_str();
  }

  void setSID(const std::string &value) {
    sid = value;
  }

  ////////////////////////////////////////////////
  // Timeout
  ////////////////////////////////////////////////

  long getTimeout() 
  {
    return timeout;
  }

  void setTimeout(long value) 
  {
    timeout = value;
  }

};

}

#endif
