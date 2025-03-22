/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/ssdp/SSDPNotifySocket.h>

#include <mupnp/ControlPoint.h>
#include <mupnp/Log.h>

using namespace mUPnP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

SSDPNotifySocket::SSDPNotifySocket()
{
  setControlPoint(NULL);
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

SSDPNotifySocket::~SSDPNotifySocket()
{
  stop();
  close();
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool SSDPNotifySocket::open(const std::string& bindAddr)
{
  const char* addr = SSDP::ADDRESS;
  if (uHTTP::IsIPv6Address(bindAddr) == true) {
    addr = SSDP::GetIPv6Address();
  }
  return HTTPMUSocket::open(addr, SSDP::PORT, bindAddr);
}

////////////////////////////////////////////////
// post
////////////////////////////////////////////////

bool SSDPNotifySocket::post(SSDPNotifyRequest* req, const std::string& ifAddr)
{
  const char* ssdpAddr = SSDP::ADDRESS;
  if (uHTTP::IsIPv6Address(ifAddr) == true)
    ssdpAddr = SSDP::GetIPv6Address();
  req->setHost(ssdpAddr, SSDP::PORT);

  bool isSuccess = HTTPMUSocket::post(ssdpAddr, SSDP::PORT, req);

  if (isSuccess) {
    LogTrace("SSDP Notify Request (%d) : %s %s", isSuccess, req->getNT(), req->getLocation());
  }
  else {
    LogWarn("SSDP Notify Request (%d) : %s %s", isSuccess, req->getNT(), req->getLocation());
  }

  return isSuccess;
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void SSDPNotifySocket::run()
{
  while (isRunnable() == true) {
    SSDPPacket ssdpPacket;
    if (!receive(&ssdpPacket))
      break;

    ControlPoint* ctrlPoint = getControlPoint();
    if (!ctrlPoint)
      break;

    if (!ssdpPacket.isNotifyRequest())
      continue;

    std::string ssdpNTS, ssdpNT, ssdpLocation;
    ssdpPacket.getNTS(ssdpNTS);
    ssdpPacket.getNT(ssdpNT);
    ssdpPacket.getLocation(ssdpLocation);

    LogTrace("SSDP Notify Received : %s %s %s", ssdpNTS.c_str(), ssdpNT.c_str(), ssdpLocation.c_str());

    ctrlPoint->notifyReceived(&ssdpPacket);
  }
}
