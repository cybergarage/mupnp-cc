/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_DEVICEDATA_H_
#define _MUPMPCC_DEVICEDATA_H_

#include <mupnp/device/Advertiser.h>
#include <mupnp/http/HTTPServerList.h>
#include <mupnp/ssdp/SSDPSearchSocketList.h>
#include <mupnp/util/Listener.h>
#include <mupnp/xml/NodeData.h>

#include <string>

namespace mUPnP {

class Device;

class DeviceData : public ::uXML::NodeData {
  Device* device;

  std::string descriptionURI;
  std::string descriptionFile;
  std::string location;
  int leaseTime;
  int httpPort;
  size_t httpWorkerCount;

  uHTTP::HTTPServerList httpServerList;

  SSDPSearchSocketList ssdpSearchSocketList;
  SSDPPacket ssdpPacket;

  Advertiser* advertiser;

  public:
  DeviceData();

  ////////////////////////////////////////////////
  // Device
  ////////////////////////////////////////////////

  public:
  void setDevice(Device* dev)
  {
    device = dev;
  }

  Device* getDevice()
  {
    return device;
  }

  ////////////////////////////////////////////////
  // description
  ////////////////////////////////////////////////

  const char* getDescriptionFile()
  {
    return descriptionFile.c_str();
  }

  const char* getDescriptionURI()
  {
    return descriptionURI.c_str();
  }

  void setDescriptionFile(const std::string& descriptionFile)
  {
    this->descriptionFile = descriptionFile;
  }

  void setDescriptionURI(const std::string& descriptionURI)
  {
    this->descriptionURI = descriptionURI;
  }

  ////////////////////////////////////////////////
  // description
  ////////////////////////////////////////////////

  const char* getLocation()
  {
    return location.c_str();
  }

  void setLocation(const std::string& location)
  {
    this->location = location;
  }

  ////////////////////////////////////////////////
  // LeaseTime
  ////////////////////////////////////////////////

  int getLeaseTime()
  {
    return leaseTime;
  }

  void setLeaseTime(int leaseTime)
  {
    this->leaseTime = leaseTime;
  }

  ////////////////////////////////////////////////
  // HTTPServer
  ////////////////////////////////////////////////

  uHTTP::HTTPServerList* getHTTPServerList()
  {
    return &httpServerList;
  }

  ////////////////////////////////////////////////
  // httpPort
  ////////////////////////////////////////////////

  int getHTTPPort()
  {
    return httpPort;
  }

  void setHTTPPort(int port)
  {
    httpPort = port;
  }

  ////////////////////////////////////////////////
  // httpPort
  ////////////////////////////////////////////////

  size_t getHTTPWorkerCount()
  {
    return httpWorkerCount;
  }

  void setHTTPWorkerCount(size_t num)
  {
    httpWorkerCount = num;
  }

  ////////////////////////////////////////////////
  // SSDPSearchSocket
  ////////////////////////////////////////////////

  SSDPSearchSocketList* getSSDPSearchSocketList()
  {
    return &ssdpSearchSocketList;
  }

  ////////////////////////////////////////////////
  // SSDPPacket
  ////////////////////////////////////////////////

  SSDPPacket* getSSDPPacket()
  {
    if (ssdpPacket.isNull() == true)
      return nullptr;
    return &ssdpPacket;
  }

  void setSSDPPacket(SSDPPacket* packet)
  {
    ssdpPacket.set(packet);
  }

  ////////////////////////////////////////////////
  // Advertiser
  ////////////////////////////////////////////////

  void setAdvertiser(Advertiser* adv)
  {
    if (advertiser)
      delete advertiser;
    advertiser = adv;
  }

  Advertiser* getAdvertiser()
  {
    return advertiser;
  }
};

}

#endif
