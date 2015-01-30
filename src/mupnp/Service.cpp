/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/Device.h>
#include <mupnp/Service.h>
#include <mupnp/Action.h>
#include <mupnp/UPnPStatus.h>
#include <mupnp/device/ST.h>
#include <mupnp/ssdp/SSDPNotifySocket.h>
#include <mupnp/ssdp/SSDPNotifyRequest.h>
#include <mupnp/control/QueryRequest.h>
#include <mupnp/control/QueryListener.h>
#include <mupnp/xml/Parser.h>
#include <uhttp/util/Debug.h>
#include <string>

using namespace mUPnP;
using namespace mUPnP;
using namespace uHTTP;
using namespace std;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *Service::ELEM_NAME = "service";
const char *Service::SERVICE_TYPE = "serviceType";
const char *Service::SERVICE_ID = "serviceId";
const char *Service::SCPDURL = "SCPDURL";
const char *Service::CONTROL_URL = "controlURL";
const char *Service::EVENT_SUB_URL = "eventSubURL";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Service::Service(mupnp_shared_ptr<uXML::Node> node) {
  serviceNode = node;
  
  initServiceData();
  initActionList();
  initServiceStateTable();
}

Service::~Service() {
}

////////////////////////////////////////////////
// Device
////////////////////////////////////////////////

Device *Service::getRootDevice() {
  Device *dev = getDevice();
  if (!dev)
    return nullptr;
  return dev->getRootDevice();
}

////////////////////////////////////////////////
// deviceList
////////////////////////////////////////////////

void Service::initActionList() {
  actionList.clear();
  mupnp_shared_ptr<uXML::Node> scdpNode = getSCPDNode();
  if (!scdpNode)
    return;
  mupnp_shared_ptr<uXML::Node> actionListNode = scdpNode->getNode(ActionList::ELEM_NAME);
  if (!actionListNode)
    return;
  mupnp_shared_ptr<uXML::Node> serviceNode = getServiceNode();
  size_t nNode = actionListNode->getNNodes();
  for (size_t n = 0; n < nNode; n++) {
    mupnp_shared_ptr<uXML::Node> node = actionListNode->getNode(n);
    if (Action::isActionNode(node) == false)
      continue;
    Action *action = new Action(serviceNode, node);
    actionList.add(action);
  } 
}

mUPnP::Action *Service::getAction(const std::string &actionName) {
  ActionList *actionList = getActionList();
  size_t nActions = actionList->size();
  for (size_t n = 0; n < nActions; n++) {
    Action *action = actionList->getAction(n);
    const char *name = action->getName();
    if (!name)
      continue;
    string nameStr = name;
    if (nameStr.compare(actionName) == 0)
      return action;
  }
  return nullptr;
}

////////////////////////////////////////////////
// serviceStateTable
////////////////////////////////////////////////

void Service::initServiceStateTable() {
  serviceStateTable.clear();
  mupnp_shared_ptr<uXML::Node> scpdNode = getSCPDNode();
  if (!scpdNode)
    return;
  mupnp_shared_ptr<uXML::Node> stateTableNode = scpdNode->getNode(ServiceStateTable::ELEM_NAME);
  if (!stateTableNode)
    return;
  mupnp_shared_ptr<uXML::Node> serviceNode = getServiceNode();
  size_t nNode = stateTableNode->getNNodes();
  for (size_t n = 0; n < nNode; n++) {
    mupnp_shared_ptr<uXML::Node> node = stateTableNode->getNode(n);
    if (StateVariable::isStateVariableNode(node) == false)
      continue;
    StateVariable *serviceVar = new StateVariable(serviceNode, node);
    serviceStateTable.add(serviceVar);
  } 
}

StateVariable *Service::getStateVariable(const std::string &name) {
  ServiceStateTable *stateTable = getServiceStateTable();
  size_t tableSize = stateTable->size();
  for (size_t n = 0; n < tableSize; n++) {
    StateVariable *var = stateTable->getStateVariable(n);
    const char *varName = var->getName();
    if (!varName)
      continue;
    string varNameStr = varName;
    if (varNameStr.compare(name) == 0)
      return var;
  }
  return nullptr;
}

////////////////////////////////////////////////
// SCPD node
////////////////////////////////////////////////

mupnp_shared_ptr<uXML::Node> Service::getSCPDNode(uHTTP::URL *url) {
  uXML::Parser parser;
  return parser.parse(url);
}

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 

mupnp_shared_ptr<uXML::Node> Service::getSCPDNode(uHTTP::File *file) {
  uXML::Parser parser;
  return parser.parse(file);
}

#endif

mupnp_shared_ptr<uXML::Node> Service::getSCPDNode(const std::string &description) {
  uXML::Parser parser;
  return parser.parse(description);
}

mupnp_shared_ptr<uXML::Node> Service::getSCPDNode() {
  ServiceData *data = getServiceData();
  mupnp_shared_ptr<uXML::Node> scpdNode = data->getSCPDNode();
  if (scpdNode)
    return scpdNode;
  
  const char *scpdURLStr = getSCPDURL();
  URL scpdURL(scpdURLStr);
  scpdNode = getSCPDNode(&scpdURL);
  if (scpdNode) {
    data->setSCPDNode(scpdNode);
    return scpdNode;
  }

  Device *rootDev = getRootDevice();
  if (!rootDev)
    return nullptr;

  string urlBaseStr = rootDev->getURLBase();
  // Thanks for Steven Yen (2003/09/03)
  if (urlBaseStr.length() <= 0) {
    string location = rootDev->getLocation();
    if (location.length() <= 0)
      return nullptr;
    string locationHost;
    HTTP::GetHost(location, locationHost);
    int locationPort = HTTP::GetPort(location);
    HTTP::GetRequestHostURL(locationHost.c_str(), locationPort, urlBaseStr);
  }
  
  string scpdURLStrBuf;
  scpdURLStr = HTTP::GetRelativeURL(scpdURLStr, scpdURLStrBuf);
  string newScpdURLStr;
  newScpdURLStr = urlBaseStr;
  newScpdURLStr.append(scpdURLStr);
  URL newScpdURL(newScpdURLStr.c_str());
  scpdNode = getSCPDNode(&newScpdURL);
  if (scpdNode) {
    data->setSCPDNode(scpdNode);
    return scpdNode;
  }

  string newScpdURLStrBuf;
  newScpdURLStr = HTTP::GetAbsoluteURL(urlBaseStr.c_str(), scpdURLStr, newScpdURLStrBuf);
  newScpdURL.setString(newScpdURLStr.c_str());
  scpdNode = getSCPDNode(&newScpdURL);
  if (scpdNode) {
    data->setSCPDNode(scpdNode);
    return scpdNode;
  }

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  string descrFilePathBuf;
  string newScpdFileStr;
  newScpdFileStr = rootDev->getDescriptionFilePath(descrFilePathBuf);
  newScpdFileStr.append(scpdURLStr);
  File newScpdFile(newScpdFileStr.c_str());
  scpdNode = getSCPDNode(&newScpdFile);
  if (scpdNode) {
    data->setSCPDNode(scpdNode);
    return scpdNode;
  }
#endif

  return nullptr;
}

const char *Service::getSCPDData(string &buf) {
  mupnp_shared_ptr<uXML::Node> scpdNode = getSCPDNode();
  buf = "";
  if (scpdNode) {
    string nodeBuf;
    // Thanks for Mikael Hakman (04/25/05)
    buf = UPnP::XML_DECLARATION;
    buf += "\n";
    buf += scpdNode->toString(nodeBuf);
  }
  return buf.c_str();
}

////////////////////////////////////////////////
// Load SCPD
////////////////////////////////////////////////

bool Service::loadSCPD(const std::string &description) {
  mupnp_shared_ptr<uXML::Node> scpdNode;
  
  try {
    scpdNode = getSCPDNode(description);
  }
  catch (uXML::ParserException e) {
    string msg;
    msg = "Couldn't load description";
    Debug::warning(msg);
    Debug::warning(e);
    //throw InvalidDescriptionException(msg.c_str()); 
    return false;
  }

  if (!scpdNode)
    return false;

  ServiceData *data = getServiceData();
  data->setSCPDNode(scpdNode);

  initServiceData();
  initActionList();
  initServiceStateTable();

  return true;
}

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 

bool Service::loadSCPD(uHTTP::File *file) {
  string description;

  if (file->load(description) == false) {
    string msg;
    msg += "Couldn't load description file (";
    msg += file->getName();
    msg += ")";
    Debug::warning(msg);
    //throw InvalidDescriptionException(msg.c_str()); 
    return false;
  }

  if (loadSCPD(description.c_str()) == false)
    return false;

  return true;
}

#endif

////////////////////////////////////////////////
// Notify
////////////////////////////////////////////////

bool Service::notify(Subscriber *sub, StateVariable *stateVar) {
  const char *varName = stateVar->getName();
  const char *value = stateVar->getValue();
    
  const char *host = sub->getDeliveryHost();
  int port = sub->getDeliveryPort();
    
  NotifyRequest notifyReq;
  notifyReq.setRequest(sub, varName, value);
  
  uHTTP::HTTPResponse *res = notifyReq.post(host, port);
  if (res->isSuccessful() == false)
    return false;
      
  sub->incrementNotifyCount();    
    
  return true;
}

void Service::notify(StateVariable *stateVar) {
  SubscriberList *subList = getSubscriberList();

  Subscriber **subArray;
  size_t subArrayCnt, n;

  // Remove expired subArraycribers.
  subArrayCnt = subList->size();
  subArray = new Subscriber*[subArrayCnt];
  for (n = 0; n < subArrayCnt; n++)
    subArray[n] = subList->getSubscriber(n);
  for (n = 0; n < subArrayCnt; n++) {
    Subscriber *sub = subArray[n];
    if (!sub)
      continue;
    if (sub->isExpired() == true)
      removeSubscriber(sub);
  }
  delete []subArray;
    
  // Notify to subArraycribers.
  subArrayCnt = subList->size();
  subArray = new Subscriber*[subArrayCnt];
  for (n = 0; n < subArrayCnt; n++)
    subArray[n] = subList->getSubscriber(n);
  for (n = 0; n < subArrayCnt; n++) {
    Subscriber *sub = subArray[n];
    if (!sub)
      continue;
    if (notify(sub, stateVar) == false) {
      /* Don't remove for NMPR specification.
      removeSubscriber(sub);
      */
    }
  }
  delete []subArray;
}

void Service::notifyAllStateVariables() {
  ServiceStateTable *stateTable = getServiceStateTable();
  size_t tableSize = stateTable->size();
  for (size_t n = 0; n < tableSize; n++) {
    StateVariable *var = stateTable->getStateVariable(n);
    if (var->isSendEvents() == true)
      notify(var);
  }
}

////////////////////////////////////////////////
// annouce
////////////////////////////////////////////////

const char *Service::getNotifyServiceTypeNT(std::string &buf) {
  buf = getServiceType();
  return buf.c_str();
}

const char *Service::getNotifyServiceTypeUSN(string &buf) {
  Device *dev = getDevice();
  buf = dev->getUDN();
  buf.append("::");
  buf.append(getServiceType());
  return  buf.c_str();
}

bool Service::announce(const std::string &ifAddr) {
  // uuid:device-UUID::urn:schemas-upnp-org:service:serviceType:v 
  
  string devLocation;
  Device *rootDev = getRootDevice();
  rootDev->getLocationURL(ifAddr, devLocation);

  string devNT, devUSN;
  getNotifyServiceTypeNT(devNT);      
  getNotifyServiceTypeUSN(devUSN);

  Device *dev = getDevice();
    
  SSDPNotifyRequest ssdpReq;
  string serverName;
  ssdpReq.setServer(UPnP::GetServerName(serverName));
  ssdpReq.setLeaseTime(dev->getLeaseTime());
  ssdpReq.setLocation(devLocation.c_str());
  ssdpReq.setNTS(NTS::ALIVE);
  ssdpReq.setNT(devNT.c_str());
  ssdpReq.setUSN(devUSN.c_str());

  Device::notifyWait();
  
  SSDPNotifySocket ssdpSock;
  return ssdpSock.post(&ssdpReq, ifAddr);
}

bool Service::byebye(const std::string &ifAddr) {
  // uuid:device-UUID::urn:schemas-upnp-org:service:serviceType:v 
    
  string devNT, devUSN;
  getNotifyServiceTypeNT(devNT);      
  getNotifyServiceTypeUSN(devUSN);
    
  SSDPNotifyRequest ssdpReq;
  ssdpReq.setNTS(NTS::BYEBYE);
  ssdpReq.setNT(devNT.c_str());
  ssdpReq.setUSN(devUSN.c_str());

  Device::notifyWait();
  
  SSDPNotifySocket ssdpSock;
  return ssdpSock.post(&ssdpReq, ifAddr);
}

////////////////////////////////////////////////
// queryAction
////////////////////////////////////////////////

void Service::setQueryListener(QueryListener *listener) {
  ServiceStateTable *stateTable = getServiceStateTable();
  size_t tableSize = stateTable->size();
  for (size_t n = 0; n < tableSize; n++) {
    StateVariable *var = stateTable->getStateVariable(n);
    var->setQueryListener(listener);
  }
}

////////////////////////////////////////////////
// isURL
////////////////////////////////////////////////
  
// Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/03/03)
bool Service::isURL(const std::string &referenceUrl, const std::string &url) {
  bool ret = StringEquals(referenceUrl, url);
  if (ret == true)
    return true;
  string relativeRefUrl;
  HTTP::GetRelativeURL(referenceUrl, relativeRefUrl, false);
  ret = StringEquals(relativeRefUrl.c_str(), url);
  if (ret == true)
    return true;
  return false;
}

////////////////////////////////////////////////
// Subscription
////////////////////////////////////////////////

void Service::addSubscriber(Subscriber *sub)  {
  lock();
  SubscriberList *subList = getSubscriberList();
  subList->add(sub);
  unlock();
}

void Service::removeSubscriber(Subscriber *sub)  {
  lock();
  getSubscriberList()->remove(sub);
  unlock();
}

Subscriber *Service::getSubscriberBySID(const std::string &name) {
  SubscriberList *subList = getSubscriberList();
  Subscriber *findSub = NULL;
  lock();
  size_t subListCnt = subList->size();
  //cout << "subListCnt = " << subListCnt << endl;
  for (size_t n = 0; n < subListCnt; n++) {
    Subscriber *sub = subList->getSubscriber(n);
    const char *sid = sub->getSID();
    //cout << "[" << n << "] = " << sid << endl;
    if (!sid)
      continue;
    string sidStr = sid;
    if (sidStr.compare(name) == 0) {
      findSub = sub;
      break;
    }
  }
  unlock();
  return findSub;
}

Subscriber *Service::getSubscriberByDeliveryURL(const std::string &name) {
  SubscriberList *subList = getSubscriberList();
  Subscriber *findSub = NULL;
  lock();
  size_t subListCnt = subList->size();
  for (size_t n = 0; n < subListCnt; n++) {
    Subscriber *sub = subList->getSubscriber(n);
    if (!sub)
      continue;
    const char *url = sub->getDeliveryURL();
    if (!url)
      continue;
    string urlStr = url;
    if (urlStr.compare(name) == 0) {
      findSub = sub;
      break;
    }
  }
  unlock();
  return findSub;
}

////////////////////////////////////////////////
// serviceSearchResponse
////////////////////////////////////////////////

bool Service::serviceSearchResponse(SSDPPacket *ssdpPacket) {
  string ssdpST;
  ssdpPacket->getST(ssdpST);
  
  if (ssdpST.length() <= 0)
    return false;
    
  Device *dev = getDevice();
      
  string serviceNT, serviceUSN;
  getNotifyServiceTypeNT(serviceNT);      
  getNotifyServiceTypeUSN(serviceUSN);
  
  if (ST::IsAllDevice(ssdpST.c_str()) == true) {
    dev->postSearchResponse(ssdpPacket, serviceNT.c_str(), serviceUSN.c_str());
  }
  else if (ST::IsURNService(ssdpST.c_str()) == true) {
    const char *serviceType = getServiceType();
    if (ssdpST.compare(serviceType) == 0)
      dev->postSearchResponse(ssdpPacket, serviceType, serviceUSN.c_str());
  }
  
  return true;
}

////////////////////////////////////////////////
// ActionListener
////////////////////////////////////////////////

void Service::setActionListener(ActionListener *listener) {
  lock();
  ActionList *actionList = getActionList();
  size_t nActions = actionList->size();
  for (size_t n = 0; n < nActions; n++) {
    Action *action = actionList->getAction(n);
    action->setActionListener(listener);
  }
  unlock();
}
