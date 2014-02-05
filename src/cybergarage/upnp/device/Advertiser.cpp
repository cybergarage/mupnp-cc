/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Advertiser.cpp
*
*  Revision;
*
*  12/25/03
*    - first revision
*  06/18/04
*    - Changed to advertise every 25%-50% of the periodic notification cycle for NMPR;
*
******************************************************************/

#include <cybergarage/upnp/Device.h>
#include <uhttp/util/TimeUtil.h>

using namespace CyberLink;
using namespace uHTTP;

////////////////////////////////////////////////
//  Thread
////////////////////////////////////////////////
  
void Advertiser::run()  {
  Device *dev = getDevice();
  long leaseTime = dev->getLeaseTime();
  long notifyInterval;
  while (isRunnable() == true) {
    notifyInterval = (leaseTime/4) + (long)((float)leaseTime * (Random() * 0.25f));
    notifyInterval *= 1000;
    Wait(notifyInterval);
    dev->announce();
  }
}

