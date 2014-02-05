/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2004
*
*  File: DeviceChangeListener.h
*
*  Revision:
*
*  10/16/04
*    - first revision
*
******************************************************************/

#ifndef _CLINK_DEVICECHANGELISTENER_H_
#define _CLINK_DEVICECHANGELISTENER_H_

namespace CyberLink {
class Device;

class DeviceChangeListener {
public:
  virtual void deviceAdded(Device *dev) = 0;
  virtual void deviceRemoved(Device *dev) = 0;
};

}

#endif

