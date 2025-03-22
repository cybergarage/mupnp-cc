/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_DEVICE_H_
#define _MUPMPCC_DEVICE_H_

#include <mupnp/Action.h>
#include <mupnp/Device.h>
#include <mupnp/DeviceList.h>
#include <mupnp/IconList.h>
#include <mupnp/Service.h>
#include <mupnp/ServiceList.h>
#include <mupnp/StateVariable.h>
#include <mupnp/UPnP.h>
#include <mupnp/device/Advertiser.h>
#include <mupnp/device/InvalidDescriptionException.h>
#include <mupnp/device/SearchListener.h>
#include <mupnp/event/SubscriptionRequest.h>
#include <mupnp/event/SubscriptionResponse.h>
#include <mupnp/http/HTTPRequestListener.h>
#include <mupnp/io/File.h>
#include <mupnp/ssdp/SSDPResponse.h>
#include <mupnp/util/Mutex.h>
#include <mupnp/util/StringUtil.h>
#include <mupnp/util/TimeUtil.h>
#include <mupnp/xml/DeviceData.h>
#include <mupnp/xml/Node.h>

#include <sstream>

namespace mUPnP {
class Device : public uHTTP::HTTPRequestListener, public SearchListener {
  mupnp_shared_ptr<uXML::Node> rootNode;
  mupnp_shared_ptr<uXML::Node> deviceNode;

  Device* rootDevice;
  Device* parentDevice;

  DeviceList deviceList;
  ServiceList serviceList;
  IconList iconList;

  bool localRootDeviceFlag;

  std::string devUUID;
  int devBootID;

  uHTTP::Mutex mutex;

  bool wirelessMode;

  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  public:
  static const char* ELEM_NAME;
  static const char* UPNP_ROOTDEVICE;
  static const int DEFAULT_STARTUP_WAIT_TIME;
  static const int DEFAULT_DISCOVERY_WAIT_TIME;
  static const int DEFAULT_LEASE_TIME;
  static const int HTTP_DEFAULT_PORT;
  static const int HTTP_DEFAULT_WORKER_COUNT;
  static const char* DEFAULT_DESCRIPTION_URI;
  static const char* URLBASE_NAME;
  static const char* DEVICE_TYPE;
  static const char* FRIENDLY_NAME;
  static const char* MANUFACTURER;
  static const char* MANUFACTURER_URL;
  static const char* MODEL_DESCRIPTION;
  static const char* MODEL_NAME;
  static const char* MODEL_NUMBER;
  static const char* MODEL_URL;
  static const char* SERIAL_NUMBER;
  static const char* UDN;
  static const char* UPC;
  static const char* presentationURL;

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

  public:
  mupnp_shared_ptr<uXML::Node> getRootNode()
  {
    return rootNode;
  }

  mupnp_shared_ptr<uXML::Node> getDeviceNode()
  {
    return deviceNode;
  }

  bool hasDeviceNode()
  {
    return (deviceNode) ? true : false;
  }

  void setRootNode(mupnp_shared_ptr<uXML::Node> node)
  {
    rootNode = node;
  }

  void setDeviceNode(mupnp_shared_ptr<uXML::Node> node)
  {
    deviceNode = node;
  }

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  Device();
  Device(mupnp_shared_ptr<uXML::Node> root, mupnp_shared_ptr<uXML::Node> device);
  Device(mupnp_shared_ptr<uXML::Node> device);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  Device(uHTTP::File* descriptionFile);
  Device(const std::string& descriptionFileName);
#endif

  private:
  void initUUID();
  void updateBootID();
  void initDeviceData();
  void initChildList();

  public:
  virtual ~Device();

  ////////////////////////////////////////////////
  // Mutex
  ////////////////////////////////////////////////

  public:
  void lock()
  {
    mutex.lock();
  }

  void unlock()
  {
    mutex.unlock();
  }

  ////////////////////////////////////////////////
  // NMPR
  ////////////////////////////////////////////////

  public:
  void setNMPRMode(bool flag);
  bool isNMPRMode();

  ////////////////////////////////////////////////
  // Wireless
  ////////////////////////////////////////////////

  public:
  void setWirelessMode(bool flag)
  {
    wirelessMode = flag;
  }

  bool isWirelessMode()
  {
    return wirelessMode;
  }

  int getSSDPAnnounceCount()
  {
    if (isNMPRMode() == true && isWirelessMode() == true)
      return UPnP::INMPR03_DISCOVERY_OVER_WIRELESS_COUNT;
    return 1;
  }

  ////////////////////////////////////////////////
  // Device UUID
  ////////////////////////////////////////////////

  private:
  void setUUID(const std::string& uuid)
  {
    devUUID = uuid;
  }

  void updateUDN()
  {
    std::string uuid;
    uuid.append("uuid:");
    uuid.append(getUUID());
    setUDN(uuid.c_str());
  }

  public:
  const char* getUUID()
  {
    return devUUID.c_str();
  }

  ////////////////////////////////////////////////
  // Device BootID
  ////////////////////////////////////////////////

  private:
  void setBootID(int bootId)
  {
    devBootID = bootId;
  }

  public:
  int getBootID()
  {
    return devBootID;
  }

  //////////////////////////////////////////////
  // Root Device
  ////////////////////////////////////////////////

  private:
  void setLocalRootDeviceFlag(bool flag)
  {
    localRootDeviceFlag = flag;
  }

  bool isLocalRootDevice()
  {
    return localRootDeviceFlag;
  }

  ////////////////////////////////////////////////
  // Root Device
  ////////////////////////////////////////////////

  public:
  Device* getRootDevice();

  ////////////////////////////////////////////////
  // Parent Device
  ////////////////////////////////////////////////

  public:
  Device* getParentDevice();

  ////////////////////////////////////////////////
  // UserData
  ////////////////////////////////////////////////

  public:
  DeviceData* getDeviceData();

  bool hasDeviceData()
  {
    return (getDeviceData() ? true : false);
  }

  ////////////////////////////////////////////////
  // Description
  ////////////////////////////////////////////////

  public:
  void setDescriptionFile(const std::string& file)
  {
    if (!hasDeviceData())
      return;
    getDeviceData()->setDescriptionFile(file);
  }

  const char* getDescriptionFile()
  {
    if (!hasDeviceData())
      return "";
    return getDeviceData()->getDescriptionFile();
  }

  void setDescriptionURI(const std::string& uri)
  {
    if (!hasDeviceData())
      return;
    getDeviceData()->setDescriptionURI(uri);
  }

  const char* getDescriptionURI()
  {
    if (!hasDeviceData())
      return "";
    return getDeviceData()->getDescriptionURI();
  }

  bool isDescriptionURI(const std::string& uri)
  {
    const char* descriptionURI = getDescriptionURI();
    if (!descriptionURI)
      return false;
    uHTTP::String descriptionURIStr(descriptionURI);
    return descriptionURIStr.equals(uri);
  }

  const char* getDescriptionFilePath(std::string& buf)
  {
    const char* descriptionFileName = getDescriptionFile();
    if (!descriptionFileName)
      return "";
    uHTTP::File descriptionFile(descriptionFileName);
    buf = descriptionFile.getAbsoluteFile()->getParent();
    return buf.c_str();
  }

  bool loadDescription(const std::string& descString);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  bool loadDescription(uHTTP::File* file);
#endif

  private:
  bool initializeLoadedDescription();

  ////////////////////////////////////////////////
  // isDeviceNode
  ////////////////////////////////////////////////

  public:
  static bool isDeviceNode(mupnp_shared_ptr<uXML::Node> node)
  {
    return node->isName(Device::ELEM_NAME);
  }

  ////////////////////////////////////////////////
  // Root Device
  ////////////////////////////////////////////////

  bool isRootDevice()
  {
    return (getRootNode()) ? true : false;
  }

  ////////////////////////////////////////////////
  // Root Device
  ////////////////////////////////////////////////

  void setSSDPPacket(SSDPPacket* packet)
  {
    if (!hasDeviceData())
      return;
    getDeviceData()->setSSDPPacket(packet);
  }

  SSDPPacket* getSSDPPacket()
  {
    if (isRootDevice() == false)
      return nullptr;
    if (!hasDeviceData())
      return nullptr;
    return getDeviceData()->getSSDPPacket();
  }

  ////////////////////////////////////////////////
  // Location
  ////////////////////////////////////////////////

  void setLocation(const std::string& value)
  {
    getDeviceData()->setLocation(value);
  }

  const char* getLocation()
  {
    SSDPPacket* packet = getSSDPPacket();
    if (packet) {
      std::string buf;
      setLocation(packet->getLocation(buf));
    }
    if (!hasDeviceData())
      return "";
    return getDeviceData()->getLocation();
  }

  ////////////////////////////////////////////////
  // LeaseTime
  ////////////////////////////////////////////////

  public:
  void setLeaseTime(int value);
  int getLeaseTime();

  ////////////////////////////////////////////////
  // TimeStamp
  ////////////////////////////////////////////////

  public:
  long getTimeStamp();
  long getElapsedTime()
  {
    return time(NULL) - getTimeStamp();
  }

  bool isExpired();

  ////////////////////////////////////////////////
  // URL Base
  ////////////////////////////////////////////////

  private:
  void setURLBase(const std::string& value);

  void updateURLBase(const std::string& host);

  public:
  const char* getURLBase();

  ////////////////////////////////////////////////
  // Device Node Value
  ////////////////////////////////////////////////

  private:
  bool setDeviceNodeValue(const std::string& name, const std::string& value);

  const char* getDeviceNodeValue(const std::string& name);

  ////////////////////////////////////////////////
  // deviceType
  ////////////////////////////////////////////////

  public:
  bool setDeviceType(const std::string& value)
  {
    return setDeviceNodeValue(DEVICE_TYPE, value);
  }

  const char* getDeviceType()
  {
    return getDeviceNodeValue(DEVICE_TYPE);
  }

  bool isDeviceType(const std::string& value);

  ////////////////////////////////////////////////
  // friendlyName
  ////////////////////////////////////////////////

  bool setFriendlyName(const std::string& value)
  {
    return setDeviceNodeValue(FRIENDLY_NAME, value);
  }

  const char* getFriendlyName()
  {
    return getDeviceNodeValue(FRIENDLY_NAME);
  }

  ////////////////////////////////////////////////
  // manufacture
  ////////////////////////////////////////////////

  bool setManufacturer(const std::string& value)
  {
    return setDeviceNodeValue(MANUFACTURER, value);
  }

  const char* getManufacturer()
  {
    return getDeviceNodeValue(MANUFACTURER);
  }

  ////////////////////////////////////////////////
  // manufactureURL
  ////////////////////////////////////////////////

  bool setManufacturerURL(const std::string& value)
  {
    return setDeviceNodeValue(MANUFACTURER_URL, value);
  }

  const char* getManufacturerURL()
  {
    return getDeviceNodeValue(MANUFACTURER_URL);
  }

  ////////////////////////////////////////////////
  // modelDescription
  ////////////////////////////////////////////////

  bool setModelDescription(const std::string& value)
  {
    return setDeviceNodeValue(MODEL_DESCRIPTION, value);
  }

  const char* getModelDescription()
  {
    return getDeviceNodeValue(MODEL_DESCRIPTION);
  }

  ////////////////////////////////////////////////
  // modelName
  ////////////////////////////////////////////////

  bool setModelName(const std::string& value)
  {
    return setDeviceNodeValue(MODEL_NAME, value);
  }

  const char* getModelName()
  {
    return getDeviceNodeValue(MODEL_NAME);
  }

  ////////////////////////////////////////////////
  // modelNumber
  ////////////////////////////////////////////////

  bool setModelNumber(const std::string& value)
  {
    return setDeviceNodeValue(MODEL_NUMBER, value);
  }

  const char* getModelNumber()
  {
    return getDeviceNodeValue(MODEL_NUMBER);
  }

  ////////////////////////////////////////////////
  // modelURL
  ////////////////////////////////////////////////

  bool setModelURL(const std::string& value)
  {
    return setDeviceNodeValue(MODEL_URL, value);
  }

  const char* getModelURL()
  {
    return getDeviceNodeValue(MODEL_URL);
  }

  ////////////////////////////////////////////////
  // serialNumber
  ////////////////////////////////////////////////

  bool setSerialNumber(const std::string& value)
  {
    return setDeviceNodeValue(SERIAL_NUMBER, value);
  }

  const char* getSerialNumber()
  {
    return getDeviceNodeValue(SERIAL_NUMBER);
  }

  ////////////////////////////////////////////////
  // UDN
  ////////////////////////////////////////////////

  bool setUDN(const std::string& value)
  {
    return setDeviceNodeValue(UDN, value);
  }

  const char* getUDN()
  {
    return getDeviceNodeValue(UDN);
  }

  bool hasUDN()
  {
    const char* udn = getUDN();
    if (!udn)
      return false;
    std::string udnStr = udn;
    if (udnStr.length() <= 0)
      return false;
    return true;
  }

  ////////////////////////////////////////////////
  // UPC
  ////////////////////////////////////////////////

  bool setUPC(const std::string& value)
  {
    return setDeviceNodeValue(UPC, value);
  }

  const char* getUPC()
  {
    return getDeviceNodeValue(UPC);
  }

  ////////////////////////////////////////////////
  // presentationURL
  ////////////////////////////////////////////////

  bool setPresentationURL(const std::string& value)
  {
    return setDeviceNodeValue(presentationURL, value);
  }

  const char* getPresentationURL()
  {
    return getDeviceNodeValue(presentationURL);
  }

  ////////////////////////////////////////////////
  // deviceList
  ////////////////////////////////////////////////

  private:
  void initDeviceList();

  public:
  DeviceList* getDeviceList()
  {
    return &deviceList;
  }

  bool isDevice(const std::string& name);

  mupnp_shared_ptr<Device> getDevice(const std::string& name);
  mupnp_shared_ptr<Device> getDeviceByDescriptionURI(const std::string& uri);

  ////////////////////////////////////////////////
  // serviceList
  ////////////////////////////////////////////////

  private:
  void initServiceList();

  public:
  ServiceList* getServiceList()
  {
    return &serviceList;
  }

  Service* getService(const std::string& name);
  Service* getSubscriberService(const std::string& uuid);

  public:
  Service* getServiceBySCPDURL(const std::string& searchUrl);
  Service* getServiceByControlURL(const std::string& searchUrl);
  Service* getServiceByEventSubURL(const std::string& searchUrl);

  ////////////////////////////////////////////////
  // StateVariable
  ////////////////////////////////////////////////

  public:
  StateVariable* getStateVariable(const std::string& serviceType, const std::string& name);
  StateVariable* getStateVariable(const std::string& name);

  ////////////////////////////////////////////////
  // Action
  ////////////////////////////////////////////////

  public:
  Action* getAction(const std::string& name);

  ////////////////////////////////////////////////
  // iconList
  ////////////////////////////////////////////////

  private:
  void initIconList();

  public:
  IconList* getIconList()
  {
    return &iconList;
  }

  Icon* getIcon(size_t n)
  {
    IconList* iconList = getIconList();
    if ((iconList->size() - 1) < n)
      return nullptr;
    return iconList->getIcon(n);
  }

  ////////////////////////////////////////////////
  // Notify
  ////////////////////////////////////////////////

  public:
  const char* getLocationURL(const std::string& host, std::string& buf);

  private:
  const char* getNotifyDeviceNT(std::string& buf);
  const char* getNotifyDeviceUSN(std::string& buf);
  const char* getNotifyDeviceTypeNT(std::string& buf);
  const char* getNotifyDeviceTypeUSN(std::string& buf);

  public:
  static void notifyWait();

  bool announce(const std::string& ifAddr);
  bool announce();

  bool byebye(const std::string& ifAddr);
  bool byebye();

  ////////////////////////////////////////////////
  // Search
  ////////////////////////////////////////////////

  public:
  bool postSearchResponse(SSDPPacket* ssdpPacket, const std::string& st, const std::string& usn);
  bool deviceSearchResponse(SSDPPacket* ssdpPacket);
  bool deviceSearchReceived(SSDPPacket* ssdpPacket);

  ////////////////////////////////////////////////
  // HTTP Server
  ////////////////////////////////////////////////

  public:
  void setHTTPPort(int port)
  {
    if (!hasDeviceData())
      return;
    getDeviceData()->setHTTPPort(port);
  }

  int getHTTPPort()
  {
    if (!hasDeviceData())
      return 0;
    return getDeviceData()->getHTTPPort();
  }

  void setHTTPWorkerCount(size_t count)
  {
    if (!hasDeviceData())
      return;
    getDeviceData()->setHTTPWorkerCount(count);
  }

  size_t getHTTPWorkerCount()
  {
    if (!hasDeviceData())
      return 0;
    return getDeviceData()->getHTTPWorkerCount();
  }

  uHTTP::HTTP::StatusCode httpRequestRecieved(uHTTP::HTTPRequest* httpReq);

  private:
  const char* getDescriptionData(const std::string& host, std::string& buf);
  uHTTP::HTTP::StatusCode httpGetRequestRecieved(uHTTP::HTTPRequest* httpReq);
  uHTTP::HTTP::StatusCode httpPostRequestRecieved(uHTTP::HTTPRequest* httpReq);

  ////////////////////////////////////////////////
  // SOAP
  ////////////////////////////////////////////////

  private:
  uHTTP::HTTP::StatusCode soapBadActionRecieved(uHTTP::HTTPRequest* soapReq);
  uHTTP::HTTP::StatusCode soapActionRecieved(uHTTP::HTTPRequest* soapReq);

  ////////////////////////////////////////////////
  // controlAction
  ////////////////////////////////////////////////

  private:
  uHTTP::HTTP::StatusCode invalidActionControlRecieved(ControlRequest* ctlReq);
  uHTTP::HTTP::StatusCode deviceControlRequestRecieved(ControlRequest* ctlReq, Service* service);
  uHTTP::HTTP::StatusCode deviceActionControlRecieved(ActionRequest* ctlReq, Service* service);
  uHTTP::HTTP::StatusCode deviceQueryControlRecieved(QueryRequest* ctlReq, Service* service);

  ////////////////////////////////////////////////
  // eventSubscribe
  ////////////////////////////////////////////////

  private:
  uHTTP::HTTP::StatusCode upnpBadSubscriptionRecieved(SubscriptionRequest* subReq, int code);
  uHTTP::HTTP::StatusCode deviceEventSubscriptionRecieved(SubscriptionRequest* subReq);
  uHTTP::HTTP::StatusCode deviceEventNewSubscriptionRecieved(Service* service, SubscriptionRequest* subReq);
  uHTTP::HTTP::StatusCode deviceEventRenewSubscriptionRecieved(Service* service, SubscriptionRequest* subReq);
  uHTTP::HTTP::StatusCode deviceEventUnsubscriptionRecieved(Service* service, SubscriptionRequest* subReq);

  ////////////////////////////////////////////////
  // Thread
  ////////////////////////////////////////////////

  public:
  uHTTP::HTTPServerList* getHTTPServerList()
  {
    if (!hasDeviceData())
      return nullptr;
    return getDeviceData()->getHTTPServerList();
  }

  SSDPSearchSocketList* getSSDPSearchSocketList()
  {
    if (!hasDeviceData())
      return nullptr;
    return getDeviceData()->getSSDPSearchSocketList();
  }

  void setAdvertiser(Advertiser* adv)
  {
    if (!hasDeviceData())
      return;
    getDeviceData()->setAdvertiser(adv);
  }

  Advertiser* getAdvertiser()
  {
    if (!hasDeviceData())
      return nullptr;
    return getDeviceData()->getAdvertiser();
  }

  public:
  bool start();
  bool stop()
  {
    return stop(true);
  }

  private:
  bool stop(bool doByeBye);

  ////////////////////////////////////////////////
  // Interface Address
  ////////////////////////////////////////////////

  public:
  const char* getInterfaceAddress()
  {
    SSDPPacket* ssdpPacket = getSSDPPacket();
    if (!ssdpPacket)
      return "";
    return ssdpPacket->getLocalAddress();
  }

  ////////////////////////////////////////////////
  // AcionListener
  ////////////////////////////////////////////////

  public:
  void setActionListener(ActionListener* listener);
  void setQueryListener(QueryListener* listener);

  ////////////////////////////////////////////////
  // AcionListener (includeSubDevices)
  ////////////////////////////////////////////////

  public:
  void setActionListener(ActionListener* listener, bool includeSubDevices);
  void setQueryListener(QueryListener* listener, bool includeSubDevices);
};

}

#endif
