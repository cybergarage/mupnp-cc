/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <uhttp/util/Debug.h>
#include <mupnp/ControlPoint.h>
#include <mupnp/xml/Parser.h>
#include <mupnp/Log.h>

#include <iostream>

using namespace std;
using namespace mUPnP;
using namespace mUPnP;
using namespace uHTTP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const int ControlPoint::DEFAULT_EVENTSUB_PORT = 8058;
const int ControlPoint::DEFAULT_EVENTSUB_WORKER_COUNT = 1;
const int ControlPoint::DEFAULT_SSDP_PORT = 8008;
const char *ControlPoint::DEFAULT_EVENTSUB_URI = "/evetSub";
const int ControlPoint::DEFAULT_EXPIRED_DEVICE_MONITORING_INTERVAL = 60;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

ControlPoint::ControlPoint(int ssdpPort, int httpPort) {
  setSSDPPort(ssdpPort);
  setHTTPPort(httpPort);
  setHTTPWorkerCount(DEFAULT_EVENTSUB_WORKER_COUNT);
  setSearchMx(SSDP::DEFAULT_MSEARCH_MX);
  setEventSubURI(DEFAULT_EVENTSUB_URI);
  setExpiredDeviceMonitoringInterval(DEFAULT_EXPIRED_DEVICE_MONITORING_INTERVAL);
  setNMPRMode(false);
  
  deviceDisposer = NULL;
  renewSubscriber = NULL;
}

ControlPoint::~ControlPoint() {
  stop();
}

////////////////////////////////////////////////
// Device List
////////////////////////////////////////////////

mupnp_shared_ptr<Device> ControlPoint::getDevice(uXML::Node *rootNode) {
  if (rootNode == NULL)
      return NULL;
  uXML::Node *devNode = rootNode->getNode(Device::ELEM_NAME);
  if (devNode == NULL)
      return NULL;
  return mupnp_shared_ptr<Device>(new Device(rootNode, devNode));
}

void ControlPoint::initDeviceList() {
  deviceList.clear();
  
  size_t nRoots = devNodeList.size();
  for (size_t n = 0; n < nRoots; n++) {
    uXML::Node *rootNode = devNodeList.getNode(n);
    mupnp_shared_ptr<Device> dev = getDevice(rootNode);
    if (dev == NULL)
      continue;
    deviceList.add(dev);
  }
}

mupnp_shared_ptr<Device> ControlPoint::getDevice(const std::string &name) {
  DeviceList *devList = getDeviceList();
  size_t nDevs = devList->size();
  for (size_t n = 0; n < nDevs; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    if (dev->isDevice(name) == true)
      return dev;
    mupnp_shared_ptr<Device> cdev = dev->getDevice(name);
    if (cdev != NULL)
      return cdev;
  } 
  return NULL;
}

////////////////////////////////////////////////
// add
////////////////////////////////////////////////

bool ControlPoint::addDevice(uXML::Node *rootNode) {
  if (!devNodeList.add(rootNode))
    return false;
  initDeviceList();
  return true;
}

bool ControlPoint::addDevice(SSDPPacket *ssdpPacket) {
  if (ssdpPacket->isRootDevice() == false)
    return false;
  
  lock();
  
  string usnBuf;
  string udnBuf;
  const char *usn = ssdpPacket->getUSN(usnBuf);
  const char *udn = USN::GetUDN(usn, udnBuf);
  mupnp_shared_ptr<Device> dev = getDevice(udn);
  if (dev != NULL) {
    dev->setSSDPPacket(ssdpPacket);
    unlock();
    return false;
  }

  string locationBuf;
  const char *location = ssdpPacket->getLocation(locationBuf);
  URL locationURL(location);
  uXML::Parser parser;
  uXML::Node *rootNode = parser.parse(&locationURL);
  mupnp_shared_ptr<Device> rootDev = getDevice(rootNode);
  if (rootDev == NULL) {
    unlock();
    return false;
  }
  rootDev->setSSDPPacket(ssdpPacket);

  addDevice(rootNode);

  // Thanks for Oliver Newell (2004/10/16)
  performAddDeviceListener(rootDev.get());

  unlock();
  
  return true;
}

////////////////////////////////////////////////
// remove
////////////////////////////////////////////////

bool ControlPoint::removeDevice(uXML::Node *rootNode) {
  if (!devNodeList.remove(rootNode))
    return false;
  removedDevNodeList.add(rootNode);
  initDeviceList();
  return true;
}

bool ControlPoint::removeDevice(SSDPPacket *packet) {
  if (packet->isByeBye() == false)
    return false;
  
  lock();
  
  string usnBuf;
  string udnBuf;
  const char *usn = packet->getUSN(usnBuf);
  const char *udn = USN::GetUDN(usn, udnBuf);
  
  mupnp_shared_ptr<Device> dev = getDevice(udn);
  if (dev == NULL) {
    unlock();
    return false;
  }
  
  // Thanks for Oliver Newell (2004/10/16)
  if(dev->isRootDevice() == true)
    performRemoveDeviceListener(dev.get());
  
  bool isRemoved = removeDevice(dev->getRootNode());
  
  unlock();
  
  return isRemoved;
}

////////////////////////////////////////////////
// Expired Device
////////////////////////////////////////////////
  
void ControlPoint::removeExpiredDevices() {
  lock();
  
  int n;
  
  DeviceList *devList = getDeviceList();
  size_t devCnt = devList->size();
  mupnp_shared_ptr<Device> *dev = new mupnp_shared_ptr<Device>[devCnt];

  for (n = 0; n < devCnt; n++) {
    dev[n] = devList->getDevice(n);
  }
  
  for (n = 0; n < devCnt; n++) {
    if (!dev[n]->isRootDevice())
      continue;
    if (dev[n]->isExpired() == true) {
      string msg = "Expired device = ";
      msg += dev[n]->getFriendlyName();
      Debug::message(msg.c_str());
      uXML::Node *rootNode = dev[n]->getRootNode();
      removeDevice(rootNode);
    }
  }
  
  delete []dev;

  unlock();
}

void ControlPoint::clean() {
  removedDevNodeList.clear();
}

////////////////////////////////////////////////
// Notify
////////////////////////////////////////////////
    
bool ControlPoint::performNotifyListener(SSDPPacket *ssdpPacket) {
  bool areAllListenerSuccess = true;
  size_t listenerSize = deviceNotifyListenerList.size();
  for (size_t n = 0; n < listenerSize; n++) {
    NotifyListener *listener = deviceNotifyListenerList.get(n);
    if (listener->deviceNotifyReceived(ssdpPacket) == false) {
      areAllListenerSuccess = false;
    }
  }
  return areAllListenerSuccess;
}

////////////////////////////////////////////////
// SearchResponse
////////////////////////////////////////////////

bool ControlPoint::performSearchResponseListener(SSDPPacket *ssdpPacket) {
  bool areAllListenerSuccess = true;
  size_t listenerSize = deviceSearchResponseListenerList.size();
  for (size_t n = 0; n < listenerSize; n++) {
    SearchResponseListener *listener = deviceSearchResponseListenerList.get(n);
    if (listener->deviceSearchResponseReceived(ssdpPacket) == false) {
      areAllListenerSuccess = false;
    }
  }
  return areAllListenerSuccess;
}

////////////////////////////////////////////////
// DeviceChangeListener
// Thanks for Oliver Newell (2004/10/16)
////////////////////////////////////////////////

bool ControlPoint::performAddDeviceListener(Device *dev) {
  bool areAllListenerSuccess = true;
  size_t listenerSize = deviceChangeListenerList.size();
  for (size_t n = 0; n < listenerSize; n++) {
    DeviceChangeListener *listener = deviceChangeListenerList.get(n);
    if (listener->deviceAdded(dev) == false) {
      areAllListenerSuccess = false;
    }
  }
  return areAllListenerSuccess;
}

bool ControlPoint::performRemoveDeviceListener(Device *dev) {
  bool areAllListenerSuccess = true;
  size_t listenerSize = deviceChangeListenerList.size();
  for (size_t n = 0; n < listenerSize; n++) {
    DeviceChangeListener *listener = deviceChangeListenerList.get(n);
    if (listener->deviceRemoved(dev) == false) {
      areAllListenerSuccess = false;
    }
  }
  return areAllListenerSuccess;
}

bool ControlPoint::performEventListener(const std::string &uuid, long seq, const std::string &name, const std::string &value) {
  bool areAllListenerSuccess = true;
  size_t listenerSize = eventListenerList.size();
  for (size_t n = 0; n < listenerSize; n++) {
    EventListener *listener = eventListenerList.get(n);
    if (listener->eventNotifyReceived(uuid, seq, name, value) == false) {
      areAllListenerSuccess = false;
    }
  }
  return areAllListenerSuccess;
}

////////////////////////////////////////////////
// SSDPPacket
////////////////////////////////////////////////
  
void ControlPoint::notifyReceived(SSDPPacket *ssdpPacket) {
  if (ssdpPacket->isRootDevice() == true) {
    if (ssdpPacket->isAlive() == true)
      addDevice(ssdpPacket);
    if (ssdpPacket->isByeBye() == true)
      removeDevice(ssdpPacket);
  }
  performNotifyListener(ssdpPacket);
}

void ControlPoint::searchResponseReceived(SSDPPacket *ssdpPacket) {
  if (ssdpPacket->isRootDevice() == true)
    addDevice(ssdpPacket);
  performSearchResponseListener(ssdpPacket);
}

////////////////////////////////////////////////
// M-SEARCH
////////////////////////////////////////////////

bool ControlPoint::search(const std::string &target, int mx) {
  SSDPSearchRequest msReq(target, mx);
  SSDPSearchResponseSocketList *ssdpSearchResponseSocketList = getSSDPSearchResponseSocketList();
  return ssdpSearchResponseSocketList->post(&msReq);
}

////////////////////////////////////////////////
// EventSub HTTPServer
////////////////////////////////////////////////

uHTTP::HTTP::StatusCode ControlPoint::httpRequestRecieved(HTTPRequest *httpReq) {
  if (Debug::isOn() == true)
    httpReq->print();
    
  // Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/08/03)
  if (httpReq->isNotifyRequest() == true) {
    NotifyRequest notifyReq(httpReq);
    string uuidBuf;
    const char *uuid = notifyReq.getSID(uuidBuf);
    long seq = notifyReq.getSEQ();
    PropertyList *props = notifyReq.getPropertyList();
    size_t propCnt = props->size();
    for (size_t n = 0; n < propCnt; n++) {
      Property *prop = props->getProperty(n);
      const char *varName = prop->getName();
      const char *varValue = prop->getValue();
      performEventListener(uuid, seq, varName, varValue);
    }
    return httpReq->returnOK();
  }
    
  return httpReq->returnBadRequest();
}

////////////////////////////////////////////////
// Subscription 
////////////////////////////////////////////////

bool ControlPoint::subscribe(Service *service, long timeout) {
  if (service->isSubscribed() == true) {
    const char *sid = service->getSID();
    return subscribe(service, sid, timeout);
  }
  
  Device *rootDev = service->getRootDevice();
  if (rootDev == NULL)
    return false;
  
  lock();
  
  const char *ifAddress = rootDev->getInterfaceAddress();     
  SubscriptionRequest subReq;
  string callbackURLBuf;
  subReq.setSubscribeRequest(service, getEventSubCallbackURL(ifAddress, callbackURLBuf), timeout);
  if (Debug::isOn() == true)
    subReq.print();  
  SubscriptionResponse *subRes = subReq.post();
  if (Debug::isOn() == true)
    subRes->print();  
  bool ret = false;
  if (subRes->isSuccessful() == true) {
    string sidBuf;
    service->setSID(subRes->getSID(sidBuf));
    service->setTimeout(subRes->getTimeout());
    ret = true;
  }
  else
    service->clearSID();
  
  unlock();
  
  return ret;
}

bool ControlPoint::subscribe(Service *service, const std::string &uuid, long timeout) {
  SubscriptionRequest subReq;
  subReq.setRenewRequest(service, uuid, timeout);
  if (Debug::isOn() == true)
    subReq.print();  
  SubscriptionResponse *subRes = subReq.post();
  if (Debug::isOn() == true)
    subRes->print();  
  if (subRes->isSuccessful() == true) {
    string sidBuf;
    service->setSID(subRes->getSID(sidBuf));
    service->setTimeout(subRes->getTimeout());
    return true;
  }
  service->clearSID();
  return false;
}

bool ControlPoint::isSubscribed(Service *service) {
  if (service == NULL)
    return false;
  return service->isSubscribed();
}

bool ControlPoint::unsubscribe(Service *service) {
  SubscriptionRequest subReq;
  subReq.setUnsubscribeRequest(service);
  if (Debug::isOn() == true)
    subReq.print();  
  SubscriptionResponse *subRes = subReq.post();
  if (Debug::isOn() == true)
    subRes->print();  
  if (subRes->isSuccessful() == true) {
    service->clearSID();
    return true;
  }
  return false;
}

void ControlPoint::unsubscribe(Device *device) {
  size_t n;

  ServiceList *serviceList = device->getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service *service = serviceList->getService(n);
    if (service->hasSID() == true)
      unsubscribe(service);
  }

  DeviceList *childDevList = device->getDeviceList();
  size_t childDevCnt = childDevList->size();
  for (n = 0; n < childDevCnt; n++) {
    mupnp_shared_ptr<Device> cdev = childDevList->getDevice(n);
    unsubscribe(cdev.get());
  }    
}

void ControlPoint::unsubscribe() {
  DeviceList *devList = getDeviceList();
  size_t devCnt = devList->size();
  for (size_t n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    unsubscribe(dev.get());
  }
}

////////////////////////////////////////////////
// getSubscriberService  
////////////////////////////////////////////////

void ControlPoint::renewSubscriberService(Device *dev, long timeout) {
  size_t n;

  ServiceList *serviceList = dev->getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service *service = serviceList->getService(n);
    if (service->isSubscribed() == false)
      continue;
    const char *sid = service->getSID();
    bool isRenewed = subscribe(service, sid, timeout);
    if (isRenewed == false)
      subscribe(service, timeout);
  }
    
  DeviceList *cdevList = dev->getDeviceList();
  size_t cdevCnt = cdevList->size();
  for (n = 0; n < cdevCnt; n++) {
    mupnp_shared_ptr<Device> cdev = cdevList->getDevice(n);
    renewSubscriberService(cdev.get(), timeout);
  }
}
  
void ControlPoint::renewSubscriberService(long timeout) {
  lock();
  DeviceList *devList = getDeviceList();
  size_t devCnt = devList->size();
  for (size_t n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    renewSubscriberService(dev.get(), timeout);
  }
  unlock();
}
  
void ControlPoint::renewSubscriberService() {
  renewSubscriberService(Subscription::INFINITE_VALUE);
}

////////////////////////////////////////////////
// getSubscriberService
////////////////////////////////////////////////

Service *ControlPoint::getSubscriberService(const std::string &uuid) {
  DeviceList *devList = getDeviceList();
  size_t devCnt = devList->size();
  for (size_t n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    Service *service = dev->getSubscriberService(uuid);
    if (service != NULL)
      return service;
  }
  return NULL;
}

////////////////////////////////////////////////
// run  
////////////////////////////////////////////////

bool ControlPoint::start(const std::string &target, int mx) {
  LogTrace("ControlPoint::start() - BEGIN");
  
  stop();

  ////////////////////////////////////////
  // HTTP Server
  ////////////////////////////////////////
    
  int retryCnt = 0;
  int bindPort = getHTTPPort();
  HTTPServerList *httpServerList = getHTTPServerList();
  while (httpServerList->open(bindPort) == false) {
    retryCnt++;
    if (UPnP::SERVER_RETRY_COUNT < retryCnt) {
      stop();
      return false;
    }
    setHTTPPort(bindPort + 1);
    bindPort = getHTTPPort();
  }
  httpServerList->addRequestListener(this);
  httpServerList->setWorkerCount(getHTTPWorkerCount());
  if (httpServerList->start() == false) {
    stop();
    return false;
  }
    
  ////////////////////////////////////////
  // Notify Socket
  ////////////////////////////////////////
    
  SSDPNotifySocketList *ssdpNotifySocketList = getSSDPNotifySocketList();
  if (ssdpNotifySocketList->open() == false) {
    stop();
    return false;
  }
  ssdpNotifySocketList->setControlPoint(this);
  if (ssdpNotifySocketList->start() == false) {
    stop();
    return false;
  }
    
  ////////////////////////////////////////
  // SeachResponse Socket
  ////////////////////////////////////////
    
  int ssdpPort = getSSDPPort();
  retryCnt = 0;
  SSDPSearchResponseSocketList *ssdpSearchResponseSocketList = getSSDPSearchResponseSocketList();
  while (ssdpSearchResponseSocketList->open(ssdpPort) == false) {
    retryCnt++;
    if (UPnP::SERVER_RETRY_COUNT < retryCnt) {
      stop();
      return false;
    }
    setSSDPPort(ssdpPort + 1);
    ssdpPort = getSSDPPort();
  }
  ssdpSearchResponseSocketList->setControlPoint(this);
  if (ssdpSearchResponseSocketList->start() == false) {
    stop();
    return false;
  }

  ////////////////////////////////////////
  // search root devices
  ////////////////////////////////////////
    
  search(target, mx);

  ////////////////////////////////////////
  // Disposer
  ////////////////////////////////////////

  Disposer *disposer = new Disposer(this);
  setDeviceDisposer(disposer);
  if (disposer->start() == false) {
    stop();
    return false;
  }
  
  ////////////////////////////////////////
  // Subscriber
  ////////////////////////////////////////
    
  if (isNMPRMode() == true) {
    RenewSubscriber *renewSub = new RenewSubscriber(this);
    setRenewSubscriber(renewSub);
    renewSub->start();
  }

  LogTrace("ControlPoint::start() - END");
  
  return true;
}
  
bool ControlPoint::stop() {
  LogTrace("ControlPoint::stop() - BEGIN");
  
  unsubscribe();
    
  SSDPNotifySocketList *ssdpNotifySocketList = getSSDPNotifySocketList();
  ssdpNotifySocketList->setControlPoint(NULL);
  ssdpNotifySocketList->stop();
  ssdpNotifySocketList->close();
  ssdpNotifySocketList->clear();
    
  SSDPSearchResponseSocketList *ssdpSearchResponseSocketList = getSSDPSearchResponseSocketList();
  ssdpSearchResponseSocketList->setControlPoint(NULL);
  ssdpSearchResponseSocketList->stop();
  ssdpSearchResponseSocketList->close();

  HTTPServerList *httpServerList = getHTTPServerList();
  httpServerList->removeRequestListener(this);
  httpServerList->stop();
  httpServerList->close();
  httpServerList->clear();

  ////////////////////////////////////////
  // Disposer
  ////////////////////////////////////////

  Disposer *disposer = getDeviceDisposer();
  if (disposer != NULL) {
    disposer->stop();
    setDeviceDisposer(NULL);
  }
  
  ////////////////////////////////////////
  // Subscriber
  ////////////////////////////////////////
    
  RenewSubscriber *renewSub = getRenewSubscriber();
  if (renewSub != NULL) {
    renewSub->stop();
    setRenewSubscriber(NULL);
  }

  LogTrace("ControlPoint::stop() - END");
  
  return true;
}

////////////////////////////////////////////////
// print
////////////////////////////////////////////////

void ControlPoint::print() {
    DeviceList *devList = getDeviceList();
    size_t devCnt = devList->size();
    cout << "Device Num = " << devCnt << endl;
    for (size_t n = 0; n < devCnt; n++) {
      mupnp_shared_ptr<Device> dev = devList->getDevice(n);
      cout << "[" << n <<  "] " << dev->getFriendlyName() << ", " << dev->getLeaseTime() << ", " << dev->getElapsedTime() << endl;
    }    
}

