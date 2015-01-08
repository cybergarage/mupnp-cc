/******************************************************************
*
*  mUPnP for C++
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

#include <mupnp/ControlPoint.h>
#include <mupnp/device/Disposer.h>
#include <uhttp/util/TimeUtil.h>

using namespace mUPnP;

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

