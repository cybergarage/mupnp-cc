/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ControlPoint.h
*
*  Revision;
*
*  07/11/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_CONTROLPOINT_H_
#define _CLINK_CONTROLPOINT_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/util/ListenerList.h>
#include <uhttp/util/Mutex.h>
#include <cybergarage/xml/NodeList.h>
#include <uhttp/http/HTTPRequestListener.h>
#include <uhttp/http/HTTPServerList.h>
#include <cybergarage/upnp/ssdp/SSDPPacket.h>
#include <cybergarage/upnp/ssdp/SSDPNotifySocketList.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponseSocketList.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponseSocket.h>
#include <cybergarage/upnp/device/SearchResponseListener.h>
#include <cybergarage/upnp/device/NotifyListener.h>
#include <cybergarage/upnp/device/Disposer.h>
#include <cybergarage/upnp/device/DeviceChangeListener.h>
#include <cybergarage/upnp/event/EventListener.h>
#include <cybergarage/upnp/control/RenewSubscriber.h>

namespace CyberLink {
class ControlPoint : public uHTTP::HTTPRequestListener {
  SSDPNotifySocketList ssdpNotifySocketList;
  SSDPSearchResponseSocketList ssdpSearchResponseSocketList;
  SSDPSearchResponseSocket ssdpSearchResponseSocket;

  int ssdpPort;
  int httpPort;
  
  CyberXML::NodeList  devNodeList;
  CyberXML::NodeList  removedDevNodeList;

  uHTTP::ListenerList deviceNotifyListenerList;
  uHTTP::ListenerList deviceSearchResponseListenerList;
  uHTTP::ListenerList deviceChangeListenerList;

  uHTTP::Mutex mutex;
  DeviceList deviceList;

  int searchMx;

  uHTTP::HTTPServerList httpServerList;
  uHTTP::ListenerList eventListenerList;

  std::string eventSubURI;

  Disposer *deviceDisposer;
  long expiredDeviceMonitoringInterval;

  bool nmprMode;
  RenewSubscriber *renewSubscriber;

 public:
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////

  static const int DEFAULT_EVENTSUB_PORT;
  static const int DEFAULT_SSDP_PORT;
  static const char *DEFAULT_EVENTSUB_URI;
  static const int DEFAULT_EXPIRED_DEVICE_MONITORING_INTERVAL;

private:

  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

  SSDPNotifySocketList *getSSDPNotifySocketList() {
    return &ssdpNotifySocketList;
  }
  
  SSDPSearchResponseSocketList *getSSDPSearchResponseSocketList() {
    return &ssdpSearchResponseSocketList;
  }

  SSDPSearchResponseSocket *getSSDPSearchResponseSocket() {
    return &ssdpSearchResponseSocket;
  }
  
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  ControlPoint(int ssdpPort = DEFAULT_SSDP_PORT, int httpPort = DEFAULT_EVENTSUB_PORT);
  virtual ~ControlPoint();

  ////////////////////////////////////////////////
  //  Port (SSDP)
  ////////////////////////////////////////////////

 public:
  int getSSDPPort() {
    return ssdpPort;
  }

  void setSSDPPort(int port) {
    ssdpPort = port;
  }

  ////////////////////////////////////////////////
  //  Port (EventSub)
  ////////////////////////////////////////////////

 public:
  int getHTTPPort() {
    return httpPort;
  }

  void setHTTPPort(int port) {
    httpPort = port;
  }
  
  ////////////////////////////////////////////////
  //  NMPR
  ////////////////////////////////////////////////

 public:
  void setNMPRMode(bool flag) {
    nmprMode = flag;
  }

  bool isNMPRMode() {
    return nmprMode;
  }

  ////////////////////////////////////////////////
  //  Device List
  ////////////////////////////////////////////////

private:

  void addDevice(CyberXML::Node *rootNode);
  void addDevice(SSDPPacket *ssdpPacket);

private:
  
  void initDeviceList();

 public:
  Device *getDevice(CyberXML::Node *rootNode);

  DeviceList *getDeviceList() {
    return &deviceList;
  }

  Device *getDevice(const std::string &name);

  bool hasDevice(const std::string &name) {
    return (getDevice(name) != NULL) ? true : false;
  }

private:

  void removeDevice(CyberXML::Node *rootNode);
  void removeDevice(Device *device);
  void removeDevice(const std::string &name);
  void removeDevice(SSDPPacket *packet);

  ////////////////////////////////////////////////
  //  Expired Device
  ////////////////////////////////////////////////

 public:
  void setExpiredDeviceMonitoringInterval(long interval) {
    expiredDeviceMonitoringInterval = interval;
  }

  long getExpiredDeviceMonitoringInterval() {
    return expiredDeviceMonitoringInterval;
  }
  
  void setDeviceDisposer(Disposer *disposer) {
    if (deviceDisposer != NULL)
      delete deviceDisposer;
    deviceDisposer = disposer;
  }
  
  Disposer *getDeviceDisposer() {
    return deviceDisposer;
  }

  void removeExpiredDevices();

  void clean();

  ////////////////////////////////////////////////
  //  Notify
  ////////////////////////////////////////////////

 public:
  void addNotifyListener(NotifyListener *listener) {
    deviceNotifyListenerList.add(listener);
  }    

  void removeNotifyListener(NotifyListener *listener) {
    deviceNotifyListenerList.remove(listener);
  }    

  void performNotifyListener(SSDPPacket *ssdpPacket);

  ////////////////////////////////////////////////
  //  SearchResponse
  ////////////////////////////////////////////////

 public:
  void addSearchResponseListener(SearchResponseListener *listener) {
    deviceSearchResponseListenerList.add(listener);
  }    

  void removeSearchResponseListener(SearchResponseListener *listener) {
    deviceSearchResponseListenerList.remove(listener);
  }    

  void performSearchResponseListener(SSDPPacket *ssdpPacket);

  ////////////////////////////////////////////////
  //  DeviceChangeListener
  //  Thanks for Oliver Newell (2004/10/16)
  ////////////////////////////////////////////////

 public:
  void addDeviceChangeListener(DeviceChangeListener *listener) {
    deviceChangeListenerList.add(listener);
  }    

  void removeDeviceChangeListener(DeviceChangeListener *listener) {
    deviceChangeListenerList.remove(listener);
  }    

  void performAddDeviceListener(Device *dev);
  void performRemoveDeviceListener(Device *dev);

  ////////////////////////////////////////////////
  //  SSDPPacket
  ////////////////////////////////////////////////
  
 public:
  void notifyReceived(SSDPPacket *packet);
  void searchResponseReceived(SSDPPacket *packet);

  ////////////////////////////////////////////////
  //  M-SEARCH
  ////////////////////////////////////////////////

 public:
  int getSearchMx() {
    return searchMx;
  }

  void setSearchMx(int mx) 
  {
    searchMx = mx;
  }

  void search(const std::string &target, int mx);

  void search(const std::string &target) {
    search(target, SSDP::DEFAULT_MSEARCH_MX);
  }

  void search() {
    search(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
  }

  ////////////////////////////////////////////////
  //  EventSub HTTPServer
  ////////////////////////////////////////////////

private:

  uHTTP::HTTPServerList *getHTTPServerList() {
    return &httpServerList;
  }

  uHTTP::HTTP::StatusCode httpRequestRecieved(uHTTP::HTTPRequest *httpReq);

  ////////////////////////////////////////////////
  //  Event Listener 
  ////////////////////////////////////////////////

 public:
  void addEventListener(EventListener *listener) {
    eventListenerList.add(listener);
  }    

  void removeEventListener(EventListener *listener) {
    eventListenerList.remove(listener);
  }    

  void performEventListener(const std::string &uuid, long seq, const std::string &name, const std::string &value) {
    int listenerSize = eventListenerList.size();
    for (int n = 0; n < listenerSize; n++) {
      EventListener *listener = (EventListener *)eventListenerList.get(n);
      listener->eventNotifyReceived(uuid, seq, name, value);
    }
  }

  ////////////////////////////////////////////////
  //  Subscription 
  ////////////////////////////////////////////////

public:  
  
  const char *getEventSubURI() {
    return eventSubURI.c_str();
  }

  void setEventSubURI(const std::string &url) {
    eventSubURI = url;
  }

private:

  const char *getEventSubCallbackURL(const std::string &host, std::string &buf) {
    return uHTTP::GetHostURL(host, getHTTPPort(), getEventSubURI(), buf);
  }

 public:
  bool subscribe(Service *service, long timeout);

  bool subscribe(Service *service) {
    return subscribe(service, Subscription::INFINITE_VALUE);
  }

  bool subscribe(Service *service, const std::string &uuid, long timeout);

  bool subscribe(Service *service, const std::string &uuid) {
    return subscribe(service, uuid, Subscription::INFINITE_VALUE);
  }

  bool isSubscribed(Service *service);
  
  bool unsubscribe(Service *service);
  void unsubscribe(Device *device);

  void unsubscribe() {
    DeviceList *devList = getDeviceList();
    int devCnt = devList->size();
    for (int n = 0; n < devCnt; n++) {
      Device *dev = devList->getDevice(n);
      unsubscribe(dev);
    }    
  }

  ////////////////////////////////////////////////
  //  getSubscriberService  
  ////////////////////////////////////////////////

 public:
  Service *getSubscriberService(const std::string &uuid) {
    DeviceList *devList = getDeviceList();
    int devCnt = devList->size();
    for (int n = 0; n < devCnt; n++) {
      Device *dev = devList->getDevice(n);
      Service *service = dev->getSubscriberService(uuid);
      if (service != NULL)
        return service;
    }    
    return NULL;
  }
  
  ////////////////////////////////////////////////
  //  getSubscriberService  
  ////////////////////////////////////////////////

 public:
  void renewSubscriberService(Device *dev, long timeout);
  void renewSubscriberService(long timeout);
  void renewSubscriberService();
  
  ////////////////////////////////////////////////
  //  Subscriber
  ////////////////////////////////////////////////
  
 public:
  void setRenewSubscriber(RenewSubscriber *sub) {
    if (renewSubscriber != NULL)
      delete renewSubscriber;
    renewSubscriber = sub;
  }
  
  RenewSubscriber *getRenewSubscriber() {
    return renewSubscriber;  
  }

  ////////////////////////////////////////////////
  //  run  
  ////////////////////////////////////////////////

 public:
  bool start(const std::string &target, int mx);

  bool start(const std::string &target) {
    return start(target, SSDP::DEFAULT_MSEARCH_MX);
  }

  bool start() {
    return start(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
  }

  bool stop();

  ////////////////////////////////////////////////
  //  lock
  ////////////////////////////////////////////////

 public:
  void lock() {
    mutex.lock();
  }

  void unlock() {
    mutex.unlock();
  }

  ////////////////////////////////////////////////
  //  print
  ////////////////////////////////////////////////

 public:
  void print();
};

}

#endif

