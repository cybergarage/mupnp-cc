/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: DeviceData.h
*
*  Revision;
*
*  07/22/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_DEVICEDATA_H_
#define _CLINK_DEVICEDATA_H_

#include <uhttp/http/HTTPServerList.h>
#include <uhttp/util/ListenerList.h>
#include <cybergarage/upnp/ssdp/SSDPSearchSocketList.h>
#include <cybergarage/upnp/device/Advertiser.h>
#include <cybergarage/xml/NodeData.h>

#include <string>

namespace CyberLink {
class Device;

class DeviceData : public CyberXML::NodeData {
  Device *device;

  std::string descriptionURI; 
  std::string descriptionFile;
  std::string location;
  int leaseTime;
  int httpPort;

  uHTTP::HTTPServerList httpServerList;    
  uHTTP::ListenerList controlActionListenerList;

  SSDPSearchSocketList ssdpSearchSocketList;
  SSDPPacket ssdpPacket;

  Advertiser *advertiser;
  
public:
  
  DeviceData();

  ////////////////////////////////////////////////
  // Device
  ////////////////////////////////////////////////

 public:
  void setDevice(Device *dev) {
    device = dev;
  }

  Device *getDevice() {
    return device;
  }

  ////////////////////////////////////////////////
  // description
  ////////////////////////////////////////////////
  
  const char *getDescriptionFile() {
    return descriptionFile.c_str();
  }

  const char *getDescriptionURI() {
    return descriptionURI.c_str();
  }

  void setDescriptionFile(const std::string &descriptionFile) {
    this->descriptionFile = descriptionFile;
  }

  void setDescriptionURI(const std::string &descriptionURI) {
    this->descriptionURI = descriptionURI;
  }

  ////////////////////////////////////////////////
  // description
  ////////////////////////////////////////////////

  const char *getLocation() {
    return location.c_str();
  }

  void setLocation(const std::string &location) {
    this->location = location;
  }

  ////////////////////////////////////////////////
  //  LeaseTime 
  ////////////////////////////////////////////////

  int getLeaseTime() {
    return leaseTime;
  }

  void setLeaseTime(int leaseTime) {
    this->leaseTime = leaseTime;
  }

  ////////////////////////////////////////////////
  //  HTTPServer 
  ////////////////////////////////////////////////

  uHTTP::HTTPServerList *getHTTPServerList() {
    return &httpServerList;
  }

  ////////////////////////////////////////////////
  //  httpPort 
  ////////////////////////////////////////////////

  int getHTTPPort() {
    return httpPort;
  }

  void setHTTPPort(int port) {
    httpPort = port;
  }

  ////////////////////////////////////////////////
  // controlActionListenerList
  ////////////////////////////////////////////////

  uHTTP::ListenerList &getControlActionListenerList() {
    return controlActionListenerList;
  }

  ////////////////////////////////////////////////
  // SSDPSearchSocket
  ////////////////////////////////////////////////
  
  SSDPSearchSocketList *getSSDPSearchSocketList() {
    return &ssdpSearchSocketList;
  }

  ////////////////////////////////////////////////
  // SSDPPacket
  ////////////////////////////////////////////////
  
  SSDPPacket *getSSDPPacket() 
  {
    if (ssdpPacket.isNull() == true)
      return NULL;
    return &ssdpPacket;
  }

  void setSSDPPacket(SSDPPacket *packet) 
  {
    ssdpPacket.set(packet);
  }

  ////////////////////////////////////////////////
  // Advertiser
  ////////////////////////////////////////////////

  void setAdvertiser(Advertiser *adv) 
  {
    if (advertiser != NULL)
      delete advertiser;
    advertiser = adv;
  }
  
  Advertiser *getAdvertiser() 
  {
    return advertiser;
  }
};

}

#endif



