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
#include <mupnp/Log.h>
#include <mupnp/Service.h>
#include <mupnp/UPnPStatus.h>
#include <mupnp/device/ST.h>
#include <mupnp/event/SubscriptionResponse.h>
#include <mupnp/http/HTTPDate.h>
#include <mupnp/io/File.h>
#include <mupnp/net/HostInterface.h>
#include <mupnp/net/URL.h>
#include <mupnp/ssdp/SSDPNotifyRequest.h>
#include <mupnp/ssdp/SSDPNotifySocket.h>
#include <mupnp/ssdp/SSDPSearchResponse.h>
#include <mupnp/ssdp/SSDPSearchResponseSocket.h>
#include <mupnp/util/Debug.h>
#include <mupnp/util/TimeUtil.h>
#include <mupnp/xml/Parser.h>

#include <iostream>

using namespace std;
using namespace uHTTP;
using namespace mUPnP;
using namespace uHTTP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char* Device::ELEM_NAME = "device";

const char* Device::UPNP_ROOTDEVICE = "upnp:rootdevice";
const int Device::DEFAULT_STARTUP_WAIT_TIME = 1000;
const int Device::DEFAULT_DISCOVERY_WAIT_TIME = 500;
const int Device::DEFAULT_LEASE_TIME = 30 * 60;
const int Device::HTTP_DEFAULT_PORT = 4004;
const int Device::HTTP_DEFAULT_WORKER_COUNT = 2;
const char* Device::DEFAULT_DESCRIPTION_URI = "/description.xml";
const char* Device::URLBASE_NAME = "URLBase";
const char* Device::DEVICE_TYPE = "deviceType";
const char* Device::FRIENDLY_NAME = "friendlyName";
const char* Device::MANUFACTURER = "manufacturer";
const char* Device::MANUFACTURER_URL = "manufacturerURL";
const char* Device::MODEL_DESCRIPTION = "modelDescription";
const char* Device::MODEL_NAME = "modelName";
const char* Device::MODEL_NUMBER = "modelNumber";
const char* Device::MODEL_URL = "modelURL";
const char* Device::SERIAL_NUMBER = "serialNumber";
const char* Device::UDN = "UDN";
const char* Device::UPC = "UPC";
const char* Device::presentationURL = "presentationURL";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Device::Device(mupnp_shared_ptr<uXML::Node> root, mupnp_shared_ptr<uXML::Node> device)
{
  setLocalRootDeviceFlag(false);
  rootNode = root;
  deviceNode = device;
  initUUID();
  updateBootID();
  initDeviceData();
  initChildList();
  setWirelessMode(false);
}

Device::Device()
{
  setLocalRootDeviceFlag(false);
  rootNode = mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
  deviceNode = mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
  initUUID();
  updateBootID();
  initDeviceData();
  initChildList();
}

Device::Device(mupnp_shared_ptr<uXML::Node> device)
{
  setLocalRootDeviceFlag(false);
  rootNode = mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
  deviceNode = device;
  initUUID();
  updateBootID();
  initDeviceData();
  initChildList();
}

void Device::initUUID()
{
  string uuid;
  setUUID(UPnP::CreateUUID(uuid));
}

void Device::updateBootID()
{
  setBootID(UPnP::CreateBootID());
}

void Device::initDeviceData()
{
  rootDevice = NULL;
  parentDevice = NULL;
  DeviceData* data = getDeviceData();
  if (data)
    data->setDevice(this);
}

void Device::initChildList()
{
  initDeviceList();
  initServiceList();
  initIconList();
}

////////////////////////////////////////////////
// Constructor (File)
////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)

Device::Device(uHTTP::File* descriptionFile)
{
  setLocalRootDeviceFlag(true);
  rootNode = mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
  ;
  deviceNode = mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
  initUUID();
  updateBootID();
  bool ret = loadDescription(descriptionFile);
  if (ret == false)
    throw InvalidDescriptionException(INVALIDDESCRIPTIONEXCEPTION_FILENOTFOUND);
}

Device::Device(const std::string& descriptionFileName)
{
  setLocalRootDeviceFlag(true);
  rootNode = mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
  ;
  deviceNode = mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
  initUUID();
  updateBootID();
  uHTTP::File descriptionFile(descriptionFileName);
  bool ret = loadDescription(&descriptionFile);
  if (ret == false)
    throw InvalidDescriptionException(INVALIDDESCRIPTIONEXCEPTION_FILENOTFOUND);
}

#endif

////////////////////////////////////////////////
// NMPR
////////////////////////////////////////////////

void Device::setNMPRMode(bool flag)
{
  mupnp_shared_ptr<uXML::Node> devNode = getDeviceNode();
  if (!devNode)
    return;
  if (flag == true) {
    devNode->setNode(UPnP::INMPR03, UPnP::INMPR03_VER);
    devNode->removeNode(Device::URLBASE_NAME);
  }
  else {
    devNode->removeNode(UPnP::INMPR03);
  }
}

bool Device::isNMPRMode()
{
  mupnp_shared_ptr<uXML::Node> devNode = getDeviceNode();
  if (!devNode)
    return false;
  return (devNode->getNode(UPnP::INMPR03)) ? true : false;
}

////////////////////////////////////////////////
// URL Base
////////////////////////////////////////////////

void Device::setURLBase(const std::string& value)
{
  if (isRootDevice() == true) {
    mupnp_shared_ptr<uXML::Node> node = getRootNode()->getNode(URLBASE_NAME);
    if (node) {
      node->setValue(value);
      return;
    }
    uXML::Node* newNode = new uXML::Node(URLBASE_NAME);
    newNode->setValue(value);
    int index = 1;
    if (getRootNode()->hasNodes() == false)
      index = 1;
    getRootNode()->insertNode(newNode, index);
  }
}

void Device::updateURLBase(const std::string& host)
{
  string urlBase;
  GetHostURL(host, getHTTPPort(), "", urlBase);
  setURLBase(urlBase.c_str());
}

const char* Device::getURLBase()
{
  if (isRootDevice() == true)
    return getRootNode()->getNodeValue(URLBASE_NAME);
  return "";
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Device::~Device()
{
  if (isLocalRootDevice() == true) {
    stop();
  }
}

////////////////////////////////////////////////
// isDeviceType
////////////////////////////////////////////////

bool Device::isDeviceType(const std::string& value)
{
  string valueStr = value;
  return (valueStr.compare(getDeviceType()) == 0) ? true : false;
}

////////////////////////////////////////////////
// LeaseTime
////////////////////////////////////////////////

void Device::setLeaseTime(int value)
{
  if (hasDeviceData())
    getDeviceData()->setLeaseTime(value);
  Advertiser* adv = getAdvertiser();
  if (adv) {
    announce();
    adv->restart();
  }
}

int Device::getLeaseTime()
{
  SSDPPacket* packet = getSSDPPacket();
  if (packet)
    return packet->getLeaseTime();
  if (hasDeviceData())
    return getDeviceData()->getLeaseTime();
  return 0;
}

////////////////////////////////////////////////
// TimeStamp
////////////////////////////////////////////////

long Device::getTimeStamp()
{
  SSDPPacket* packet = getSSDPPacket();
  if (packet)
    return packet->getTimeStamp();
  return 0;
}

bool Device::isExpired()
{
  long elipsedTime = getElapsedTime();
  long leaseTime = getLeaseTime() + UPnP::DEFAULT_EXPIRED_DEVICE_EXTRA_TIME;
  if (leaseTime < 0)
    return false;
  if (leaseTime < elipsedTime)
    return true;
  return false;
}

////////////////////////////////////////////////
// Root Device
////////////////////////////////////////////////

Device* Device::getRootDevice()
{
  if (rootDevice)
    return rootDevice;
  mupnp_shared_ptr<uXML::Node> rootNode = getRootNode();
  if (!rootNode)
    return nullptr;
  mupnp_shared_ptr<uXML::Node> devNode = rootNode->getNode(Device::ELEM_NAME);
  if (!devNode)
    return nullptr;
  rootDevice = new Device();
  rootDevice->setDeviceNode(devNode);
  rootDevice->setRootNode(rootNode);
  return rootDevice;
}

////////////////////////////////////////////////
// Root Device
////////////////////////////////////////////////

// Thanks for Stefano Lenzi (07/24/04)

Device* Device::getParentDevice()
{
  if (parentDevice)
    return parentDevice;

  if (isRootDevice() == true)
    return nullptr;

  mupnp_shared_ptr<uXML::Node> rootNode = getRootNode();
  if (!rootNode)
    return nullptr;

  mupnp_shared_ptr<uXML::Node> devNode = getDeviceNode();
  if (!devNode)
    return nullptr;

  //<device><deviceList><device>

  uXML::Node* parentNode = devNode->getParentNode();
  if (!parentNode)
    return nullptr;
  devNode = mupnp_shared_ptr<uXML::Node>(parentNode->getParentNode());
  if (!devNode)
    return nullptr;

  parentDevice = new Device();
  parentDevice->setDeviceNode(devNode);
  parentDevice->setRootNode(rootNode);

  return parentDevice;
}

////////////////////////////////////////////////
// UserData
////////////////////////////////////////////////

DeviceData* Device::getDeviceData()
{
  mupnp_shared_ptr<uXML::Node> node = getDeviceNode();
  if (!node)
    return nullptr;
  DeviceData* userData = dynamic_cast<DeviceData*>(node->getUserData());
  if (!userData) {
    userData = new DeviceData();
    node->setUserData(userData);
  }
  return userData;
}

////////////////////////////////////////////////
// Device Node Value
////////////////////////////////////////////////

bool Device::setDeviceNodeValue(const std::string& name, const std::string& value)
{
  if (hasDeviceNode() == false)
    return false;
  return getDeviceNode()->setNode(name, value);
}

const char* Device::getDeviceNodeValue(const std::string& name)
{
  if (hasDeviceNode() == false)
    return "";
  return getDeviceNode()->getNodeValue(name);
}

////////////////////////////////////////////////
// loadDescription
////////////////////////////////////////////////

bool Device::loadDescription(const std::string& description)
{
  try {
    uXML::Parser parser;
    rootNode = parser.parse(description);
  }
  catch (uXML::ParserException e) {
    string msg;
    msg = "Couldn't load description";
    Debug::warning(msg);
    Debug::warning(e);
    // throw InvalidDescriptionException(msg.c_str());
    return false;
  }

  if (!rootNode)
    return false;

  if (Debug::isOn() == true)
    rootNode->print();

  deviceNode = rootNode->getNode(Device::ELEM_NAME);
  if (!deviceNode)
    return false;

  setDescriptionFile("");
  setDescriptionURI(DEFAULT_DESCRIPTION_URI);
  setLeaseTime(DEFAULT_LEASE_TIME);
  setHTTPPort(HTTP_DEFAULT_PORT);
  setHTTPWorkerCount(HTTP_DEFAULT_WORKER_COUNT);

  // Thanks for Oliver Newell (03/23/04)
  if (hasUDN() == false)
    updateUDN();

  initDeviceData();
  initChildList();

  return true;
}

////////////////////////////////////////////////
// Description (File)
////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)

bool Device::loadDescription(uHTTP::File* file)
{
  string description;

  if (file->load(description) == false) {
    string msg;
    msg += "Couldn't load description file (";
    msg += file->getName();
    msg += ")";
    Debug::warning(msg);
    // throw InvalidDescriptionException(msg.c_str());
    return false;
  }

  if (loadDescription(description.c_str()) == false)
    return false;

  setDescriptionFile(file->getName());

  // initialize childlist again
  initDeviceData();
  initChildList();

  return true;
}

#endif

////////////////////////////////////////////////
// deviceList
////////////////////////////////////////////////

void Device::initDeviceList()
{
  deviceList.clear();
  mupnp_shared_ptr<uXML::Node> devNode = getDeviceNode();
  if (!devNode)
    return;
  mupnp_shared_ptr<uXML::Node> devListNode = devNode->getNode(DeviceList::ELEM_NAME);
  if (!devListNode)
    return;
  size_t nNode = devListNode->getNNodes();
  for (size_t n = 0; n < nNode; n++) {
    mupnp_shared_ptr<uXML::Node> node = devListNode->getNode(n);
    if (Device::isDeviceNode(node) == false)
      continue;
    Device* dev = new Device(node);
    deviceList.add(dev);
  }
}

bool Device::isDevice(const std::string& name)
{
  String nameStr = name;
  if (nameStr.endsWith(getUDN()) == true)
    return true;
  if (nameStr.equals(getFriendlyName()) == true)
    return true;
  if (nameStr.endsWith(getDeviceType()) == true)
    return true;
  return false;
}

mupnp_shared_ptr<Device> Device::getDevice(const std::string& name)
{
  DeviceList* devList = getDeviceList();
  size_t devCnt = devList->size();
  for (size_t n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    if (dev->isDevice(name) == true)
      return dev;
    mupnp_shared_ptr<Device> cdev = dev->getDevice(name);
    if (cdev)
      return cdev;
  }
  return mupnp_shared_ptr<Device>((Device*)nullptr);
}

mupnp_shared_ptr<Device> Device::getDeviceByDescriptionURI(const std::string& uri)
{
  DeviceList* devList = getDeviceList();
  size_t devCnt = devList->size();
  for (size_t n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    if (dev->isDescriptionURI(uri) == true)
      return dev;
    mupnp_shared_ptr<Device> cdev = dev->getDeviceByDescriptionURI(uri);
    if (cdev)
      return cdev;
  }
  return mupnp_shared_ptr<Device>((Device*)nullptr);
}

////////////////////////////////////////////////
// serviceList
////////////////////////////////////////////////

void Device::initServiceList()
{
  serviceList.clear();
  mupnp_shared_ptr<uXML::Node> devNode = getDeviceNode();
  if (!devNode)
    return;
  mupnp_shared_ptr<uXML::Node> serviceListNode = devNode->getNode(ServiceList::ELEM_NAME);
  if (!serviceListNode)
    return;
  size_t nNode = serviceListNode->getNNodes();
  for (size_t n = 0; n < nNode; n++) {
    mupnp_shared_ptr<uXML::Node> node = serviceListNode->getNode(n);
    if (Service::isServiceNode(node) == false)
      continue;
    Service* service = new Service(node);
    serviceList.add(service);
  }
}

Service* Device::getService(const std::string& name)
{
  size_t n;

  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    if (service->isService(name) == true)
      return service;
  }

  DeviceList* devList = getDeviceList();
  size_t devCnt = devList->size();
  for (n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    Service* service = dev->getService(name);
    if (service)
      return service;
  }

  return nullptr;
}

Service* Device::getServiceBySCPDURL(const std::string& searchUrl)
{
  size_t n;

  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    if (service->isSCPDURL(searchUrl) == true)
      return service;
  }

  DeviceList* devList = getDeviceList();
  size_t devCnt = devList->size();
  for (n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    Service* service = dev->getServiceBySCPDURL(searchUrl);
    if (service)
      return service;
  }

  return nullptr;
}

Service* Device::getServiceByControlURL(const std::string& searchUrl)
{
  size_t n;

  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    if (service->isControlURL(searchUrl) == true)
      return service;
  }

  DeviceList* devList = getDeviceList();
  size_t devCnt = devList->size();
  for (n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    Service* service = dev->getServiceByControlURL(searchUrl);
    if (service)
      return service;
  }

  return nullptr;
}

Service* Device::getServiceByEventSubURL(const std::string& searchUrl)
{
  size_t n;

  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    if (service->isEventSubURL(searchUrl) == true)
      return service;
  }

  DeviceList* devList = getDeviceList();
  size_t devCnt = devList->size();
  for (n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    Service* service = dev->getServiceByEventSubURL(searchUrl);
    if (service)
      return service;
  }

  return nullptr;
}

Service* Device::getSubscriberService(const std::string& uuid)
{
  size_t n;

  String uuidStr = uuid;
  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    const char* sid = service->getSID();
    if (uuidStr.equals(sid) == true)
      return service;
  }

  DeviceList* devList = getDeviceList();
  size_t devCnt = devList->size();
  for (n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    Service* service = dev->getSubscriberService(uuid);
    if (service)
      return service;
  }

  return nullptr;
}

////////////////////////////////////////////////
// StateVariable
////////////////////////////////////////////////

StateVariable* Device::getStateVariable(const std::string& serviceType, const std::string& name)
{
  size_t n;

  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    // Thanks for Theo Beisch (11/09/04)
    if (0 < serviceType.length()) {
      if (serviceType.compare(service->getServiceType()) != 0)
        continue;
    }
    StateVariable* stateVar = service->getStateVariable(name);
    if (stateVar)
      return stateVar;
  }

  DeviceList* devList = getDeviceList();
  size_t devCnt = devList->size();
  for (n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    StateVariable* stateVar = dev->getStateVariable(name);
    if (stateVar)
      return stateVar;
  }

  return nullptr;
}

StateVariable* Device::getStateVariable(const std::string& name)
{
  return getStateVariable("", name);
}

////////////////////////////////////////////////
// Action
////////////////////////////////////////////////

mUPnP::Action* Device::getAction(const std::string& name)
{
  size_t n;
  uHTTP::String nameStr = name;

  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    ActionList* actionList = service->getActionList();
    size_t actionCnt = actionList->size();
    for (size_t i = 0; i < actionCnt; i++) {
      Action* action = actionList->getAction(i);
      const char* actionName = action->getName();
      if (!actionName)
        continue;
      if (nameStr.equals(actionName) == true)
        return action;
    }
  }

  DeviceList* devList = getDeviceList();
  size_t devCnt = devList->size();
  for (n = 0; n < devCnt; n++) {
    mupnp_shared_ptr<Device> dev = devList->getDevice(n);
    Action* action = dev->getAction(name);
    if (action)
      return action;
  }

  return nullptr;
}

////////////////////////////////////////////////
// iconList
////////////////////////////////////////////////

void Device::initIconList()
{
  iconList.clear();
  mupnp_shared_ptr<uXML::Node> devNode = getDeviceNode();
  if (!devNode)
    return;
  mupnp_shared_ptr<uXML::Node> iconListNode = devNode->getNode(IconList::ELEM_NAME);
  if (!iconListNode)
    return;
  size_t nNode = iconListNode->getNNodes();
  for (size_t n = 0; n < nNode; n++) {
    mupnp_shared_ptr<uXML::Node> node = iconListNode->getNode(n);
    if (Icon::isIconNode(node) == false)
      continue;
    Icon* icon = new Icon(node);
    iconList.add(icon);
  }
}

////////////////////////////////////////////////
// Notify
////////////////////////////////////////////////

void Device::notifyWait()
{
  uHTTP::WaitRandom(DEFAULT_DISCOVERY_WAIT_TIME);
}

const char* Device::getLocationURL(const std::string& host, std::string& buf)
{
  return uHTTP::GetHostURL(host, getHTTPPort(), getDescriptionURI(), buf);
}

const char* Device::getNotifyDeviceNT(std::string& buf)
{
  if (isRootDevice() == false)
    buf = getUDN();
  buf = UPNP_ROOTDEVICE;
  return buf.c_str();
}

const char* Device::getNotifyDeviceUSN(std::string& buf)
{
  buf = getUDN();
  if (isRootDevice() == true) {
    buf.append("::");
    buf.append(UPNP_ROOTDEVICE);
  }
  return buf.c_str();
}

const char* Device::getNotifyDeviceTypeNT(std::string& buf)
{
  buf = getDeviceType();
  return buf.c_str();
}

const char* Device::getNotifyDeviceTypeUSN(std::string& buf)
{
  buf = getUDN();
  buf.append("::");
  buf.append(getDeviceType());
  return buf.c_str();
}

bool Device::announce(const std::string& ifAddr)
{
  bool isSuccess = true;

  string devLocationBuf;
  const char* devLocation = getLocationURL(ifAddr, devLocationBuf);

  SSDPNotifyRequest ssdpReq;
  string serverName;
  ssdpReq.setServer(UPnP::GetServerName(serverName));
  ssdpReq.setLeaseTime(getLeaseTime());
  ssdpReq.setLocation(devLocation);
  ssdpReq.setNTS(NTS::ALIVE);
  ssdpReq.setBootID(getBootID());

  SSDPNotifySocket ssdpSock;

  // uuid:device-UUID(::upnp:rootdevice)*
  if (isRootDevice() == true) {
    string devNT, devUSN;
    getNotifyDeviceNT(devNT);
    getNotifyDeviceUSN(devUSN);
    ssdpReq.setNT(devNT.c_str());
    ssdpReq.setUSN(devUSN.c_str());
    if (!ssdpSock.post(&ssdpReq, ifAddr))
      isSuccess = false;
  }

  // uuid:device-UUID::urn:schemas-upnp-org:device:deviceType:v
  string devNT, devUSN;
  getNotifyDeviceTypeNT(devNT);
  getNotifyDeviceTypeUSN(devUSN);
  ssdpReq.setNT(devNT.c_str());
  ssdpReq.setUSN(devUSN.c_str());
  if (!ssdpSock.post(&ssdpReq, ifAddr))
    isSuccess = false;

  // Thanks for Mikael Hakman (04/25/05)
  ssdpSock.close();

  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (size_t n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    if (!service->announce(ifAddr))
      isSuccess = false;
  }

  DeviceList* childDeviceList = getDeviceList();
  size_t childDeviceCnt = childDeviceList->size();
  for (size_t n = 0; n < childDeviceCnt; n++) {
    mupnp_shared_ptr<Device> childDevice = childDeviceList->getDevice(n);
    if (!childDevice->announce(ifAddr))
      isSuccess = false;
  }

  return isSuccess;
}

bool Device::announce()
{
  bool isSuccess = true;

  notifyWait();

  size_t nHostAddrs = uHTTP::GetNHostAddresses();
  for (size_t n = 0; n < nHostAddrs; n++) {
    std::string bindAddrBuf;
    const char* bindAddr = uHTTP::GetHostAddress(n, bindAddrBuf);
    if (uHTTP::StringHasData(bindAddr) == false)
      continue;
    int ssdpCount = getSSDPAnnounceCount();
    for (int i = 0; i < ssdpCount; i++) {
      if (!announce(bindAddr))
        isSuccess = false;
    }
  }

  return isSuccess;
}

bool Device::byebye(const std::string& ifAddr)
{
  bool isSuccess = true;

  SSDPNotifyRequest ssdpReq;
  ssdpReq.setNTS(NTS::BYEBYE);

  SSDPNotifySocket ssdpSock;

  // uuid:device-UUID(::upnp:rootdevice)*
  if (isRootDevice() == true) {
    string devNT, devUSN;
    getNotifyDeviceNT(devNT);
    getNotifyDeviceUSN(devUSN);
    ssdpReq.setNT(devNT.c_str());
    ssdpReq.setUSN(devUSN.c_str());
    if (!ssdpSock.post(&ssdpReq, ifAddr))
      isSuccess = false;
  }

  // uuid:device-UUID::urn:schemas-upnp-org:device:deviceType:v
  string devNT, devUSN;
  getNotifyDeviceTypeNT(devNT);
  getNotifyDeviceTypeUSN(devUSN);
  ssdpReq.setNT(devNT.c_str());
  ssdpReq.setUSN(devUSN.c_str());
  if (!ssdpSock.post(&ssdpReq, ifAddr))
    isSuccess = false;

  // Thanks for Mikael Hakman (04/25/05)
  ssdpSock.close();

  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (size_t n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    if (!service->byebye(ifAddr))
      isSuccess = false;
  }

  DeviceList* childDeviceList = getDeviceList();
  size_t childDeviceCnt = childDeviceList->size();
  for (size_t n = 0; n < childDeviceCnt; n++) {
    mupnp_shared_ptr<Device> childDevice = childDeviceList->getDevice(n);
    if (!childDevice->byebye(ifAddr))
      isSuccess = false;
  }

  return isSuccess;
}

bool Device::byebye()
{
  bool isSuccess = true;
  size_t nHostAddrs = uHTTP::GetNHostAddresses();
  for (size_t n = 0; n < nHostAddrs; n++) {
    std::string bindAddrBuf;
    const char* bindAddr = uHTTP::GetHostAddress(n, bindAddrBuf);
    if (uHTTP::StringHasData(bindAddr) == false)
      continue;
    int ssdpCount = getSSDPAnnounceCount();
    for (int i = 0; i < ssdpCount; i++) {
      if (!byebye(bindAddr))
        isSuccess = false;
    }
  }
  return isSuccess;
}

////////////////////////////////////////////////
// Search
////////////////////////////////////////////////

bool Device::postSearchResponse(SSDPPacket* ssdpPacket, const std::string& st, const std::string& usn)
{
  const char* localAddr = ssdpPacket->getLocalAddress();
  Device* rootDev = getRootDevice();
  string rootDevLocation;
  rootDev->getLocationURL(localAddr, rootDevLocation);

  SSDPSearchResponse ssdpRes;
  HTTPDate currDate;
  ssdpRes.setLeaseTime(getLeaseTime());
  ssdpRes.setDate(&currDate);
  ssdpRes.setST(st);
  ssdpRes.setUSN(usn);
  ssdpRes.setLocation(rootDevLocation.c_str());
  ssdpRes.setBootID(getBootID());
  // Thanks for Brent Hills (10/20/04)
  ssdpRes.setMYNAME(getFriendlyName());

  int mx = ssdpPacket->getMX();
  uHTTP::WaitRandom(mx * 1000);

  const char* remoteAddr = ssdpPacket->getRemoteAddress();
  int remotePort = ssdpPacket->getRemotePort();
  SSDPSearchResponseSocket ssdpResSock;
  if (Debug::isOn() == true)
    ssdpRes.print();

  bool areAllResponseSucess = true;

  int ssdpCount = getSSDPAnnounceCount();
  for (int i = 0; i < ssdpCount; i++) {
    if (!ssdpResSock.post(remoteAddr, remotePort, &ssdpRes))
      areAllResponseSucess = false;
  }

  return areAllResponseSucess;
}

bool Device::deviceSearchResponse(SSDPPacket* ssdpPacket)
{
  string ssdpST;
  ssdpPacket->getST(ssdpST);

  if (ssdpST.length() <= 0)
    return false;

  bool isRootDev = isRootDevice();

  string devUSN = getUDN();
  if (isRootDev == true) {
    devUSN.append("::");
    devUSN.append(USN::ROOTDEVICE);
  }

  bool isDeviceResponseSuccess = false;

  if (ST::IsAllDevice(ssdpST.c_str()) == true) {
    string devNT;
    getNotifyDeviceNT(devNT);
    int repeatCnt = (isRootDev == true) ? 3 : 2;
    for (int n = 0; n < repeatCnt; n++) {
      isDeviceResponseSuccess = postSearchResponse(ssdpPacket, devNT.c_str(), devUSN.c_str());
    }
  }
  else if (ST::IsRootDevice(ssdpST.c_str()) == true) {
    if (isRootDev == true) {
      isDeviceResponseSuccess = postSearchResponse(ssdpPacket, ST::ROOT_DEVICE, devUSN.c_str());
    }
  }
  else if (ST::IsUUIDDevice(ssdpST.c_str()) == true) {
    const char* devUDN = getUDN();
    if (ssdpST.compare(devUDN) == 0) {
      isDeviceResponseSuccess = postSearchResponse(ssdpPacket, devUDN, devUSN.c_str());
    }
  }
  else if (ST::IsURNDevice(ssdpST.c_str()) == true) {
    const char* devType = getDeviceType();
    if (ssdpST.compare(devType) == 0) {
      // Thanks for Mikael Hakman (04/25/05)
      devUSN = getUDN();
      devUSN += "::";
      devUSN += devType;
      isDeviceResponseSuccess = postSearchResponse(ssdpPacket, devType, devUSN.c_str());
    }
  }

  bool areServiceResponsesSuccess = true;
  size_t n;

  ServiceList* serviceList = getServiceList();
  size_t serviceCnt = serviceList->size();
  for (n = 0; n < serviceCnt; n++) {
    Service* service = serviceList->getService(n);
    if (service->serviceSearchResponse(ssdpPacket) == false) {
      areServiceResponsesSuccess = false;
    }
  }

  bool areEmbeddedDeviceResponsesSuccess = true;

  DeviceList* childDeviceList = getDeviceList();
  size_t childDeviceCnt = childDeviceList->size();
  for (n = 0; n < childDeviceCnt; n++) {
    mupnp_shared_ptr<Device> childDevice = childDeviceList->getDevice(n);
    if (childDevice->deviceSearchResponse(ssdpPacket) == false) {
      areEmbeddedDeviceResponsesSuccess = false;
    }
  }

  return (isDeviceResponseSuccess & areServiceResponsesSuccess & areEmbeddedDeviceResponsesSuccess);
}

bool Device::deviceSearchReceived(SSDPPacket* ssdpPacket)
{
  return deviceSearchResponse(ssdpPacket);
}

////////////////////////////////////////////////
// HTTP Server
////////////////////////////////////////////////

uHTTP::HTTP::StatusCode Device::httpRequestRecieved(uHTTP::HTTPRequest* httpReq)
{
  if (Debug::isOn() == true)
    httpReq->print();

  if (httpReq->isGetRequest() == true || httpReq->isHeadRequest()) {
    return httpGetRequestRecieved(httpReq);
  }

  if (httpReq->isPostRequest() == true) {
    return httpPostRequestRecieved(httpReq);
  }

  if (httpReq->isSubscribeRequest() == true || httpReq->isUnsubscribeRequest() == true) {
    SubscriptionRequest subReq(httpReq);
    return deviceEventSubscriptionRecieved(&subReq);
  }

  return httpReq->returnBadRequest();
}

////////////////////////////////////////////////
// HTTP Server
////////////////////////////////////////////////

const char* Device::getDescriptionData(const std::string& host, string& buf)
{
  lock();
  if (isNMPRMode() == false)
    updateURLBase(host);
  mupnp_shared_ptr<uXML::Node> rootNode = getRootNode();
  buf = "";
  if (rootNode) {
    string nodeBuf;
    // Thanks for Mikael Hakman (04/25/05)
    buf = UPnP::XML_DECLARATION;
    buf += "\n";
    buf += rootNode->toString(nodeBuf);
  }
  unlock();
  return buf.c_str();
}

uHTTP::HTTP::StatusCode Device::httpGetRequestRecieved(HTTPRequest* httpReq)
{
  string uri;
  httpReq->getURI(uri);
  if (uri.length() <= 0) {
    return httpReq->returnBadRequest();
  }

  string fileByteBuf;
  const char* fileByte = "";

  mupnp_shared_ptr<Device> embDev;
  Service* embService;

  if (isDescriptionURI(uri.c_str()) == true) {
    const char* localAddr = httpReq->getLocalAddress();
    fileByte = getDescriptionData(localAddr, fileByteBuf);
  }
  else if ((embDev = getDeviceByDescriptionURI(uri.c_str()))) {
    const char* localAddr = httpReq->getLocalAddress();
    fileByte = embDev->getDescriptionData(localAddr, fileByteBuf);
  }
  else if ((embService = getServiceBySCPDURL(uri.c_str()))) {
    fileByte = embService->getSCPDData(fileByteBuf);
  }
  else {
    return httpReq->returnBadRequest();
  }

  HTTPResponse httpRes;
  if (File::isXMLFileName(uri.c_str()) == true)
    httpRes.setContentType(uXML::XML::CONTENT_TYPE);
  httpRes.setStatusCode(HTTP::OK_REQUEST);
  httpRes.setContent(fileByte);
  return httpReq->post(&httpRes);
}

uHTTP::HTTP::StatusCode Device::httpPostRequestRecieved(HTTPRequest* httpReq)
{
  if (httpReq->isSOAPAction() == true) {
    return soapActionRecieved(httpReq);
  }
  return httpReq->returnBadRequest();
}

////////////////////////////////////////////////
// SOAP
////////////////////////////////////////////////

uHTTP::HTTP::StatusCode Device::soapBadActionRecieved(HTTPRequest* soapReq)
{
  uSOAP::SOAPResponse soapRes;
  soapRes.setStatusCode(HTTP::BAD_REQUEST);
  soapReq->post(&soapRes);
  return soapRes.getStatusCode();
}

uHTTP::HTTP::StatusCode Device::soapActionRecieved(HTTPRequest* soapReq)
{
  string uri;
  soapReq->getURI(uri);
  Service* ctlService = getServiceByControlURL(uri.c_str());
  if (ctlService) {
    ControlRequest crlReq(soapReq);
    return deviceControlRequestRecieved(&crlReq, ctlService);
  }
  return soapBadActionRecieved(soapReq);
}

////////////////////////////////////////////////
// controlAction
////////////////////////////////////////////////

uHTTP::HTTP::StatusCode Device::invalidActionControlRecieved(ControlRequest* ctlReq)
{
  ControlResponse actRes;
  actRes.setFaultResponse(UPnP::INVALID_ACTION);
  return ctlReq->post(&actRes);
}

uHTTP::HTTP::StatusCode Device::deviceControlRequestRecieved(ControlRequest* ctlReq, Service* service)
{
  if (ctlReq->isQueryControl() == true) {
    QueryRequest queryRes(ctlReq);
    return deviceQueryControlRecieved(&queryRes, service);
  }

  ActionRequest actRes(ctlReq);
  return deviceActionControlRecieved(&actRes, service);
}

uHTTP::HTTP::StatusCode Device::deviceActionControlRecieved(ActionRequest* ctlReq, Service* service)
{
  if (Debug::isOn() == true)
    ctlReq->print();

  string actionNameBuf;
  const char* actionName = ctlReq->getActionName(actionNameBuf);
  Action* action = service->getAction(actionName);
  if (!action) {
    return invalidActionControlRecieved(ctlReq);
  }
  ArgumentList* actionArgList = action->getArgumentList();
  ArgumentList* reqArgList = ctlReq->getArgumentList();
  actionArgList->set(reqArgList);
  if (action->performActionListener(ctlReq) == false)
    return invalidActionControlRecieved(ctlReq);
  return HTTP::OK_REQUEST;
}

uHTTP::HTTP::StatusCode Device::deviceQueryControlRecieved(QueryRequest* ctlReq, Service* service)
{
  if (Debug::isOn() == true)
    ctlReq->print();
  const char* varName = ctlReq->getVarName();
  if (service->hasStateVariable(varName) == false) {
    return invalidActionControlRecieved(ctlReq);
  }
  StateVariable* stateVar = getStateVariable(varName);
  if (stateVar->performQueryListener(ctlReq) == false)
    return invalidActionControlRecieved(ctlReq);
  return HTTP::OK_REQUEST;
}

////////////////////////////////////////////////
// eventSubscribe
////////////////////////////////////////////////

uHTTP::HTTP::StatusCode Device::upnpBadSubscriptionRecieved(SubscriptionRequest* subReq, int code)
{
  SubscriptionResponse subRes;
  subRes.setErrorResponse(code);
  return subReq->post(&subRes);
}

uHTTP::HTTP::StatusCode Device::deviceEventSubscriptionRecieved(SubscriptionRequest* subReq)
{
  if (Debug::isOn() == true)
    subReq->print();
  string uri;
  subReq->getURI(uri);
  Service* service = getServiceByEventSubURL(uri.c_str());
  if (!service) {
    return subReq->returnBadRequest();
  }
  if (subReq->hasCallback() == false && subReq->hasSID() == false) {
    return upnpBadSubscriptionRecieved(subReq, uHTTP::HTTP::PRECONDITION_FAILED);
  }

  // UNSUBSCRIBE
  if (subReq->isUnsubscribeRequest() == true) {
    return deviceEventUnsubscriptionRecieved(service, subReq);
  }

  // SUBSCRIBE (NEW)
  if (subReq->hasCallback() == true) {
    return deviceEventNewSubscriptionRecieved(service, subReq);
  }

  // SUBSCRIBE (RENEW)
  if (subReq->hasSID() == true) {
    return deviceEventRenewSubscriptionRecieved(service, subReq);
  }

  return upnpBadSubscriptionRecieved(subReq, uHTTP::HTTP::PRECONDITION_FAILED);
}

uHTTP::HTTP::StatusCode Device::deviceEventNewSubscriptionRecieved(Service* service, SubscriptionRequest* subReq)
{
  string callback;
  subReq->getCallback(callback);

  URL url(callback.c_str());

  long timeOut = subReq->getTimeout();
  string sid;
  Subscription::CreateSID(sid);

  Subscriber* sub = new Subscriber();
  sub->setDeliveryURL(callback.c_str());
  sub->setTimeOut(timeOut);
  sub->setSID(sid.c_str());
  service->addSubscriber(sub);

  SubscriptionResponse subRes;
  subRes.setStatusCode(HTTP::OK_REQUEST);
  subRes.setSID(sid.c_str());
  subRes.setTimeout(timeOut);
  subReq->post(&subRes);

  service->notifyAllStateVariables();

  return uHTTP::HTTP::OK_REQUEST;
}

uHTTP::HTTP::StatusCode Device::deviceEventRenewSubscriptionRecieved(Service* service, SubscriptionRequest* subReq)
{
  string sidBuf;
  const char* sid = subReq->getSID(sidBuf);
  Subscriber* sub = service->getSubscriberBySID(sid);

  if (!sub) {
    return upnpBadSubscriptionRecieved(subReq, uHTTP::HTTP::PRECONDITION_FAILED);
  }

  long timeOut = subReq->getTimeout();
  sub->setTimeOut(timeOut);
  sub->renew();

  SubscriptionResponse subRes;
  subRes.setStatusCode(HTTP::OK_REQUEST);
  subRes.setSID(sid);
  subRes.setTimeout(timeOut);
  return subReq->post(&subRes);
}

uHTTP::HTTP::StatusCode Device::deviceEventUnsubscriptionRecieved(Service* service, SubscriptionRequest* subReq)
{
  string sidBuf;
  const char* sid = subReq->getSID(sidBuf);

  Subscriber* sub = service->getSubscriberBySID(sid);
  if (!sub) {
    return upnpBadSubscriptionRecieved(subReq, uHTTP::HTTP::PRECONDITION_FAILED);
  }

  service->removeSubscriber(sub);

  SubscriptionResponse subRes;
  subRes.setStatusCode(HTTP::OK_REQUEST);
  return subReq->post(&subRes);
}

////////////////////////////////////////////////
// Thread
////////////////////////////////////////////////

bool Device::start()
{
  LogTrace("Device::start() - BEGIN");

  stop(true);

  ////////////////////////////////////////
  // HTTP Server
  ////////////////////////////////////////

  int retryCnt = 0;
  int bindPort = getHTTPPort();
  HTTPServerList* httpServerList = getHTTPServerList();
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
  // SSDP Seach Socket
  ////////////////////////////////////////

  SSDPSearchSocketList* ssdpSearchSockList = getSSDPSearchSocketList();
  if (ssdpSearchSockList->open() == false) {
    stop();
    return false;
  }
  ssdpSearchSockList->addSearchListener(this);
  if (ssdpSearchSockList->start() == false) {
    stop();
    return false;
  }

  ////////////////////////////////////////
  // BOOTID.UPNP.ORG
  ////////////////////////////////////////

  updateBootID();

  ////////////////////////////////////////
  // Announce
  ////////////////////////////////////////

  announce();

  ////////////////////////////////////////
  // Advertiser
  ////////////////////////////////////////

  Advertiser* adv = new Advertiser(this);
  setAdvertiser(adv);
  if (adv->start() == false) {
    stop();
    return false;
  }

  LogTrace("Device::start() - END");

  return true;
}

bool Device::stop(bool doByeBye)
{
  LogTrace("Device::stop() - BEGIN");

  HTTPServerList* httpServerList = getHTTPServerList();
  httpServerList->removeRequestListener(this);
  httpServerList->close();
  httpServerList->stop();
  httpServerList->clear();

  SSDPSearchSocketList* ssdpSearchSockList = getSSDPSearchSocketList();
  ssdpSearchSockList->removeSearchListener(this);
  ssdpSearchSockList->close();
  ssdpSearchSockList->stop();
  ssdpSearchSockList->clear();

  Advertiser* adv = getAdvertiser();
  if (adv) {
    adv->stop();
    setAdvertiser(NULL);
  }

  LogTrace("Device::stop() - END");

  if (doByeBye == true)
    byebye();

  return true;
}

////////////////////////////////////////////////
// Action/QueryListener
////////////////////////////////////////////////

void Device::setActionListener(ActionListener* listener)
{
  ServiceList* ServiceList = getServiceList();
  size_t nServices = ServiceList->size();
  for (size_t n = 0; n < nServices; n++) {
    Service* Service = ServiceList->getService(n);
    Service->setActionListener(listener);
  }
}

void Device::setQueryListener(QueryListener* listener)
{
  ServiceList* ServiceList = getServiceList();
  size_t nServices = ServiceList->size();
  for (size_t n = 0; n < nServices; n++) {
    Service* Service = ServiceList->getService(n);
    Service->setQueryListener(listener);
  }
}

////////////////////////////////////////////////
// Action/QueryListener
////////////////////////////////////////////////

// Thanks for Mikael Hakman (04/25/05)
void Device::setActionListener(ActionListener* listener, bool includeSubDevices)
{
  setActionListener(listener);
  if (includeSubDevices == true) {
    DeviceList* devList = getDeviceList();
    size_t devCnt = devList->size();
    for (size_t n = 0; n < devCnt; n++) {
      mupnp_shared_ptr<Device> dev = devList->getDevice(n);
      dev->setActionListener(listener, true);
    }
  }
}

// Thanks for Mikael Hakman (04/25/05)
void Device::setQueryListener(QueryListener* listener, bool includeSubDevices)
{
  setQueryListener(listener);
  if (includeSubDevices == true) {
    DeviceList* devList = getDeviceList();
    size_t devCnt = devList->size();
    for (size_t n = 0; n < devCnt; n++) {
      mupnp_shared_ptr<Device> dev = devList->getDevice(n);
      dev->setQueryListener(listener, true);
    }
  }
}
