/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SERVICEDATA_H_
#define _MUPMPCC_SERVICEDATA_H_

#include <uhttp/util/Listener.h>
#include <mupnp/xml/Node.h>
#include <mupnp/xml/NodeData.h>
#include <mupnp/event/SubscriberList.h>

#include <string>

namespace mUPnP {
class QueryListener;
class Service;

class ServiceData : public mUPnP::NodeData {
  Service *service;

  std::string sid;
  long timeout;

  SubscriberList subscriberList;

  mUPnP::Node *scpdNode;

 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  ServiceData();

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
  // scpdNode
  ////////////////////////////////////////////////

  mUPnP::Node *getSCPDNode() {
    return scpdNode;
  }

  void setSCPDNode(Node *node);

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
