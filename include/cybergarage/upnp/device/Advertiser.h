/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Advertiser.h
*
*  Revision;
*
*  12/25/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_ADVERTISER_H_
#define _CLINK_ADVERTISER_H_

#include <uhttp/util/Thread.h>

namespace CyberLink {
class Device;

class Advertiser : public uHTTP::Thread {
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  Advertiser(Device *dev) {
    setDevice(dev);
  }
  
  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

private:
  
  Device *device;

 public:
  void setDevice(Device *dev) {
    device = dev;
  }
  
  Device *getDevice() {
    return device;
  }

  ////////////////////////////////////////////////
  //  Thread
  ////////////////////////////////////////////////
  
 public:
  void run();

};

}

#endif

