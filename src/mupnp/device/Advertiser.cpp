/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/Device.h>
#include <mupnp/util/TimeUtil.h>

using namespace mUPnP;
using namespace uHTTP;

////////////////////////////////////////////////
// Thread
////////////////////////////////////////////////

void Advertiser::run()
{
  Device* dev = getDevice();
  long leaseTime = dev->getLeaseTime();
  long notifyInterval;
  while (isRunnable() == true) {
    notifyInterval = (leaseTime / 4) + (long)((float)leaseTime * (Random() * 0.25f));
    notifyInterval *= 1000;
    Wait(notifyInterval);
    dev->announce();
  }
}
