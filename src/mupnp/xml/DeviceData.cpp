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

using namespace mUPnP;

DeviceData::DeviceData()  {
  setDevice(NULL);
  setSSDPPacket(NULL);
  advertiser = NULL;
  leaseTime = Device::DEFAULT_LEASE_TIME;
  httpPort = Device::HTTP_DEFAULT_PORT;
}
