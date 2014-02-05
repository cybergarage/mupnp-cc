/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Disposer.cpp
*
*  Revision;
*
*  01/06/04
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/upnp/device/Disposer.h>
#include <uhttp/util/TimeUtil.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Thread
////////////////////////////////////////////////
  
void Disposer::run()  {
  ControlPoint *ctrlp = getControlPoint();
  long monitorInterval = ctrlp->getExpiredDeviceMonitoringInterval() * 1000;
  
  while (isRunnable() == true) {
    uHTTP::Wait(monitorInterval);
    ctrlp->removeExpiredDevices();
    //ctrlp->print();
  }
}

