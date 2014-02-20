/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: DeviceList.cpp
*
*  Revision;
*
*  08/13/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/DeviceList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *DeviceList::ELEM_NAME = "deviceList";

////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////

void DeviceList::clear()  {
  int nDev = size();
  for (int n = 0; n < nDev; n++) {
    Device *dev = getDevice(n);
    delete dev;
  }
  Vector::clear();
}
