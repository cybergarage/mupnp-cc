/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
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
// Thread
////////////////////////////////////////////////
  
void Disposer::run()  {
  ControlPoint *ctrlPoint = getControlPoint();
  long monitorInterval = ctrlPoint->getExpiredDeviceMonitoringInterval() * 1000;
  
  while (isRunnable() == true) {
    uHTTP::Wait(monitorInterval);
    ControlPoint *ctrlPoint = getControlPoint();
    if (!ctrlPoint)
      break;
    ctrlPoint->removeExpiredDevices();
  }
}

