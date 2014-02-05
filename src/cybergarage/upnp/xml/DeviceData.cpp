/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: DeviceData.cpp
*
*  Revision;
*
*  07/22/03
*    - first revision
*  12/25/03
*    - Added Advertiser functions.
*  01/06/03
*    - Changed a ssdp packet variable to static.
*  05/19/04
*    - Changed the header include order for Cygwin.
*
******************************************************************/

#include <cybergarage/upnp/Device.h>

using namespace CyberLink;

DeviceData::DeviceData()  {
  setDevice(NULL);
  setSSDPPacket(NULL);
  advertiser = NULL;
  leaseTime = Device::DEFAULT_LEASE_TIME;
  httpPort = Device::HTTP_DEFAULT_PORT;
}
