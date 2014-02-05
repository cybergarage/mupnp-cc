/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Service.h
*
*  Revision;
*
*  07/22/03
*    - first revision
*  03/30/05
*    - Removed setDescriptionURL() and getDescriptionURL().
*
******************************************************************/

#ifndef _CLINK_SERVICE_H_
#define _CLINK_SERVICE_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/io/File.h>
#include <uhttp/net/URL.h>

#include <cybergarage/upnp/xml/DeviceData.h>
#include <cybergarage/upnp/ActionList.h>
#include <cybergarage/upnp/StateVariable.h>
#include <cybergarage/upnp/ServiceStateTable.h>
#include <cybergarage/upnp/xml/ServiceData.h>
#include <cybergarage/upnp/event/NotifyRequest.h>
#include <cybergarage/upnp/event/SubscriberList.h>
#include <cybergarage/upnp/control/QueryRequest.h>
#include <cybergarage/upnp/control/ActionListener.h>
#include <uhttp/util/Mutex.h>
#include <uhttp/util/Vector.h>
#include <uhttp/util/StringUtil.h>
#include <cybergarage/xml/Node.h>

namespace CyberLink {
class Device;

class Service {
  CyberXML::Node *serviceNode;
  
  ActionList actionList;
  ServiceStateTable serviceStateTable;

  uHTTP::Mutex mutex;

public:
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;
  static const char *SERVICE_TYPE;
  static const char *SERVICE_ID;
  static const char *SCPDURL;
  static const char *CONTROL_URL;
  static const char *EVENT_SUB_URL;

 public:
  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

  CyberXML::Node *getServiceNode() {
    return serviceNode;
  }

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  Service(CyberXML::Node *node);

  ~Service();

private:

  void initServiceData() {
    ServiceData *data = getServiceData();
    if (data != NULL)
      data->setService(this);
  }

  ////////////////////////////////////////////////
  // Mutex
  ////////////////////////////////////////////////
  
 public:
  void lock() {
    mutex.lock();
  }
  
  void unlock() {
    mutex.unlock();
  }

  ////////////////////////////////////////////////
  //  isServiceNode
  ////////////////////////////////////////////////

 public:
  static bool isServiceNode(CyberXML::Node *node) {
    return node->isName(Service::ELEM_NAME);
  }
  
  ////////////////////////////////////////////////
  //  Device/Root Node
  ////////////////////////////////////////////////

private:

  CyberXML::Node *getDeviceNode() {
    CyberXML::Node *node = getServiceNode()->getParentNode();
    if (node == NULL)
      return NULL;
    return node->getParentNode();
  }

  CyberXML::Node *getRootNode() {
    return getServiceNode()->getRootNode();
  }

  ////////////////////////////////////////////////
  //  Device
  ////////////////////////////////////////////////

 public:
  Device *getDevice() {
    CyberXML::Node *node = getDeviceNode();
    DeviceData *data = (DeviceData *)node->getUserData();
    if (data == NULL)
      return NULL;
    return data->getDevice();
  }

  Device *getRootDevice();

  ////////////////////////////////////////////////
  //  serviceType
  ////////////////////////////////////////////////

 public:
  void setServiceType(const std::string &value) {
    getServiceNode()->setNode(SERVICE_TYPE, value);
  }

  const char *getServiceType() {
    return getServiceNode()->getNodeValue(SERVICE_TYPE);
  }

  ////////////////////////////////////////////////
  //  serviceID
  ////////////////////////////////////////////////

 public:
  void setServiceID(const std::string &value) {
    getServiceNode()->setNode(SERVICE_ID, value);
  }

  const char *getServiceID() {
    return getServiceNode()->getNodeValue(SERVICE_ID);
  }

  ////////////////////////////////////////////////
  //  isURL
  ////////////////////////////////////////////////

private:

  bool isURL(const std::string &referenceUrl, const std::string &url);

  ////////////////////////////////////////////////
  //  SCPDURL
  ////////////////////////////////////////////////

 public:
  void setSCPDURL(const std::string &value) {
    getServiceNode()->setNode(SCPDURL, value);
  }

  const char *getSCPDURL() {
    return getServiceNode()->getNodeValue(SCPDURL);
  }

  bool isSCPDURL(const std::string &url) {
    return isURL(getSCPDURL(), url);
  }
  
  const char *getSCPDData(std::string &buf);

  ////////////////////////////////////////////////
  //  controlURL
  ////////////////////////////////////////////////

 public:
  void setControlURL(const std::string &value) {
    getServiceNode()->setNode(CONTROL_URL, value);
  }

  const char *getControlURL() {
    return getServiceNode()->getNodeValue(CONTROL_URL);
  }

  bool isControlURL(const std::string &url) {
    return isURL(getControlURL(), url);
  }

  ////////////////////////////////////////////////
  //  eventSubURL
  ////////////////////////////////////////////////

 public:
  void setEventSubURL(const std::string &value) {
    getServiceNode()->setNode(EVENT_SUB_URL, value);
  }

  const char *getEventSubURL() {
    return getServiceNode()->getNodeValue(EVENT_SUB_URL);
  }

  bool isEventSubURL(const std::string &url) {
    return isURL(getEventSubURL(), url);
  }

  ////////////////////////////////////////////////
  //  SCPD node
  ////////////////////////////////////////////////

 public:
  bool loadSCPD(const std::string &descString);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
  bool loadSCPD(uHTTP::File *file);
#endif

private:
  CyberXML::Node *getSCPDNode(uHTTP::URL *url);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
  CyberXML::Node *getSCPDNode(uHTTP::File *file);
#endif
  CyberXML::Node *getSCPDNode(const std::string &description);
  CyberXML::Node *getSCPDNode();

public:
  ////////////////////////////////////////////////
  //  actionList
  ////////////////////////////////////////////////

private:

  void initActionList();

 public:
  ActionList *getActionList() {
    return &actionList;
  }

  Action *getAction(const std::string &actionName);
  
  ////////////////////////////////////////////////
  //  serviceStateTable
  ////////////////////////////////////////////////

private:

  void initServiceStateTable();

 public:
  ServiceStateTable *getServiceStateTable() {
    return &serviceStateTable;
  }

  StateVariable *getStateVariable(const std::string &name);
  
  bool hasStateVariable(const std::string &name) {
    return (getStateVariable(name) != NULL) ? true : false;
  }

  ////////////////////////////////////////////////
  //  isService
  ////////////////////////////////////////////////
  
  bool isService(const std::string &name) {
    uHTTP::String nameStr(name);
    if (nameStr.endsWith(getServiceType()) == true)
      return true;
    if (nameStr.endsWith(getServiceID()) == true)
      return true;
    return false;
  }
   
  ////////////////////////////////////////////////
  //  UserData
  ////////////////////////////////////////////////

  ServiceData *getServiceData() {
    CyberXML::Node *node = getServiceNode();
    if (node == NULL)
      return NULL;
    ServiceData *userData = (ServiceData *)node->getUserData();
    if (userData == NULL) {
      userData = new ServiceData();
      node->setUserData(userData);
    }
    return userData;
  }

  ////////////////////////////////////////////////
  //  Notify
  ////////////////////////////////////////////////

private:

  const char *getNotifyServiceTypeNT(std::string &buf);
  const char *getNotifyServiceTypeUSN(std::string &buf);

 public:
  void announce(const std::string &bindAddr);
  void byebye(const std::string &bindAddr);

  ////////////////////////////////////////////////
  //  serviceSearchResponse  
  ////////////////////////////////////////////////

 public:
  bool serviceSearchResponse(SSDPPacket *ssdpPacket);

  ////////////////////////////////////////////////
  //  queryAction
  ////////////////////////////////////////////////

 public:
  void setQueryListener(QueryListener *listener);

  ////////////////////////////////////////////////
  //  Subscription
  ////////////////////////////////////////////////

 public:
  SubscriberList *getSubscriberList() 
  {
    return getServiceData()->getSubscriberList();
  }

  void addSubscriber(Subscriber *sub);
  void removeSubscriber(Subscriber *sub);

  Subscriber *getSubscriberBySID(const std::string &name);
  Subscriber *getSubscriberByDeliveryURL(const std::string &name);

private:
  
  bool notify(Subscriber *sub, StateVariable *stateVar);

 public:
  void notify(StateVariable *stateVar);
  void notifyAllStateVariables();
  
  ////////////////////////////////////////////////
  // SID
  ////////////////////////////////////////////////

  const char *getSID() 
  {
    return getServiceData()->getSID();
  }

  void setSID(const std::string &sid) 
  {
    getServiceData()->setSID(sid);
  }

  void clearSID() {
    setSID("");
    setTimeout(0);
  }
  
  bool hasSID() {
    return uHTTP::StringHasData(getSID());
  }    

  bool isSubscribed() {
    return hasSID();
  }
  
  ////////////////////////////////////////////////
  // Timeout
  ////////////////////////////////////////////////

 public:
  long getTimeout() 
  {
    return getServiceData()->getTimeout();
  }

  void setTimeout(long value) 
  {
    getServiceData()->setTimeout(value);
  }

  ////////////////////////////////////////////////
  // AcionListener
  ////////////////////////////////////////////////
  
public:
  
  void setActionListener(ActionListener *listener);

};

}

#endif

