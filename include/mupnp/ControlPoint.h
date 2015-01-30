/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_CONTROLPOINT_H_
#define _MUPMPCC_CONTROLPOINT_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/util/Listener.h>
#include <uhttp/util/Mutex.h>
#include <uhttp/http/HTTPRequestListener.h>
#include <uhttp/http/HTTPServerList.h>
#include <mupnp/xml/NodeList.h>
#include <mupnp/ssdp/SSDPPacket.h>
#include <mupnp/ssdp/SSDPNotifySocketList.h>
#include <mupnp/ssdp/SSDPSearchResponseSocketList.h>
#include <mupnp/device/SearchResponseListener.h>
#include <mupnp/device/NotifyListener.h>
#include <mupnp/device/Disposer.h>
#include <mupnp/device/DeviceChangeListener.h>
#include <mupnp/event/EventListener.h>
#include <mupnp/control/RenewSubscriber.h>

namespace mUPnP {
  
typedef uHTTP::ListenerList<NotifyListener>         NotifyListenerList;
typedef uHTTP::ListenerList<SearchResponseListener> SearchResponseListenerList;
typedef uHTTP::ListenerList<DeviceChangeListener>   DeviceChangeListenerList;
typedef uHTTP::ListenerList<EventListener>   EventListenerList;
  
class ControlPoint : public uHTTP::HTTPRequestListener {
  SSDPNotifySocketList ssdpNotifySocketList;
  SSDPSearchResponseSocketList ssdpSearchResponseSocketList;

  int ssdpPort;
  int httpPort;
  size_t httpWorkerCount;
  
  uXML::NodeList  devNodeList;
  uXML::NodeList  removedDevNodeList;

  NotifyListenerList deviceNotifyListenerList;
  SearchResponseListenerList deviceSearchResponseListenerList;
  DeviceChangeListenerList deviceChangeListenerList;

  uHTTP::Mutex mutex;
  DeviceList deviceList;

  int searchMx;

  uHTTP::HTTPServerList httpServerList;
  EventListenerList eventListenerList;

  std::string eventSubURI;

  Disposer *deviceDisposer;
  long expiredDeviceMonitoringInterval;

  bool nmprMode;
  RenewSubscriber *renewSubscriber;

 public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  static const int DEFAULT_EVENTSUB_PORT;
  static const int DEFAULT_EVENTSUB_WORKER_COUNT;
  static const int DEFAULT_SSDP_PORT;
  static const char *DEFAULT_EVENTSUB_URI;
  static const int DEFAULT_EXPIRED_DEVICE_MONITORING_INTERVAL;

private:

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

  SSDPNotifySocketList *getSSDPNotifySocketList() {
    return &ssdpNotifySocketList;
  }
  
  SSDPSearchResponseSocketList *getSSDPSearchResponseSocketList() {
    return &ssdpSearchResponseSocketList;
  }

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  ControlPoint(int ssdpPort = DEFAULT_SSDP_PORT, int httpPort = DEFAULT_EVENTSUB_PORT);
  virtual ~ControlPoint();

  ////////////////////////////////////////////////
  // Port (SSDP)
  ////////////////////////////////////////////////

 public:
  int getSSDPPort() {
    return ssdpPort;
  }

  void setSSDPPort(int port) {
    ssdpPort = port;
  }

  ////////////////////////////////////////////////
  // HTTP (EventSub)
  ////////////////////////////////////////////////

 public:
  int getHTTPPort() {
    return httpPort;
  }

  void setHTTPPort(int port) {
    httpPort = port;
  }
  
  size_t getHTTPWorkerCount() {
    return httpWorkerCount;
  }
  
  void setHTTPWorkerCount(size_t count) {
    httpWorkerCount = count;
  }
  
  ////////////////////////////////////////////////
  // NMPR
  ////////////////////////////////////////////////

 public:
  void setNMPRMode(bool flag) {
    nmprMode = flag;
  }

  bool isNMPRMode() {
    return nmprMode;
  }

  ////////////////////////////////////////////////
  // Device List
  ////////////////////////////////////////////////

private:

  bool addDevice(mupnp_shared_ptr<uXML::Node> rootNode);
  bool addDevice(SSDPPacket *ssdpPacket);

private:
  
  void initDeviceList();

 public:
  DeviceList *getDeviceList() {
    return &deviceList;
  }

  mupnp_shared_ptr<Device> getDevice(mupnp_shared_ptr<uXML::Node> rootNode);
  mupnp_shared_ptr<Device> getDevice(const std::string &name);

  bool hasDevice(const std::string &name) {
    return (getDevice(name) != NULL) ? true : false;
  }

private:

  bool removeDevice(mupnp_shared_ptr<uXML::Node> rootNode);
  bool removeDevice(SSDPPacket *packet);

  ////////////////////////////////////////////////
  // Expired Device
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
  // Notify
  ////////////////////////////////////////////////

 public:
  void addNotifyListener(NotifyListener *listener) {
    deviceNotifyListenerList.add(listener);
  }    

  void removeNotifyListener(NotifyListener *listener) {
    deviceNotifyListenerList.remove(listener);
  }    

  bool performNotifyListener(SSDPPacket *ssdpPacket);

  ////////////////////////////////////////////////
  // SearchResponse
  ////////////////////////////////////////////////

 public:
  void addSearchResponseListener(SearchResponseListener *listener) {
    deviceSearchResponseListenerList.add(listener);
  }    

  void removeSearchResponseListener(SearchResponseListener *listener) {
    deviceSearchResponseListenerList.remove(listener);
  }    

  bool performSearchResponseListener(SSDPPacket *ssdpPacket);

  ////////////////////////////////////////////////
  // DeviceChangeListener
  // Thanks for Oliver Newell (2004/10/16)
  ////////////////////////////////////////////////

 public:
  void addDeviceChangeListener(DeviceChangeListener *listener) {
    deviceChangeListenerList.add(listener);
  }    

  void removeDeviceChangeListener(DeviceChangeListener *listener) {
    deviceChangeListenerList.remove(listener);
  }    

  bool performAddDeviceListener(Device *dev);
  bool performRemoveDeviceListener(Device *dev);

  ////////////////////////////////////////////////
  // SSDPPacket
  ////////////////////////////////////////////////
  
 public:
  void notifyReceived(SSDPPacket *packet);
  void searchResponseReceived(SSDPPacket *packet);

  ////////////////////////////////////////////////
  // M-SEARCH
  ////////////////////////////////////////////////

 public:
  int getSearchMx() {
    return searchMx;
  }

  void setSearchMx(int mx) 
  {
    searchMx = mx;
  }

  bool search(const std::string &target, int mx);

  bool search(const std::string &target) {
    return search(target, SSDP::DEFAULT_MSEARCH_MX);
  }

  bool search() {
    return search(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
  }

  ////////////////////////////////////////////////
  // EventSub HTTPServer
  ////////////////////////////////////////////////

private:

  uHTTP::HTTPServerList *getHTTPServerList() {
    return &httpServerList;
  }

  uHTTP::HTTP::StatusCode httpRequestRecieved(uHTTP::HTTPRequest *httpReq);

  ////////////////////////////////////////////////
  // Event Listener 
  ////////////////////////////////////////////////

 public:
  void addEventListener(EventListener *listener) {
    eventListenerList.add(listener);
  }    

  void removeEventListener(EventListener *listener) {
    eventListenerList.remove(listener);
  }    

  bool performEventListener(const std::string &uuid, long seq, const std::string &name, const std::string &value);

  ////////////////////////////////////////////////
  // Subscription 
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
  void unsubscribe();

  ////////////////////////////////////////////////
  // getSubscriberService  
  ////////////////////////////////////////////////

 public:
  Service *getSubscriberService(const std::string &uuid);
  
  ////////////////////////////////////////////////
  // getSubscriberService  
  ////////////////////////////////////////////////

 public:
  void renewSubscriberService(Device *dev, long timeout);
  void renewSubscriberService(long timeout);
  void renewSubscriberService();
  
  ////////////////////////////////////////////////
  // Subscriber
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
  // run  
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
  // lock
  ////////////////////////////////////////////////

 public:
  void lock() {
    mutex.lock();
  }

  void unlock() {
    mutex.unlock();
  }

  ////////////////////////////////////////////////
  // print
  ////////////////////////////////////////////////

 public:
  void print();
};

}

#endif

