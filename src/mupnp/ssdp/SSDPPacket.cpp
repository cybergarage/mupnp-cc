/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string>
#include <string.h>
#include <uhttp/HTTP.h>
#include <mupnp/ssdp/SSDPPacket.h>

using namespace mUPnP;

////////////////////////////////////////////////
// SSDPPacket
////////////////////////////////////////////////

bool SSDPPacket::isNotifyRequest()
{
  const char *dgmPackatData = getData();
  if (!dgmPackatData)
    return false;
  return (strncmp(dgmPackatData, uHTTP::HTTP::NOTIFY , strlen(uHTTP::HTTP::NOTIFY)) == 0) ? true : false;
}

////////////////////////////////////////////////
// SSDPPacket
////////////////////////////////////////////////

bool SSDPPacket::isSearchRequest()
{
  const char *dgmPackatData = getData();
  if (!dgmPackatData)
    return false;
  return (strncmp(dgmPackatData, uHTTP::HTTP::M_SEARCH, strlen(uHTTP::HTTP::M_SEARCH)) == 0) ? true : false;
}

////////////////////////////////////////////////
// isRootDevice
////////////////////////////////////////////////

bool SSDPPacket::isRootDevice() {
  std::string buf;
  if (NT::IsRootDevice(getNT(buf)) == true)
    return true;
  if (ST::IsRootDevice(getST(buf)) == true)
    return true;
  return USN::IsRootDevice(getUSN(buf));
}

////////////////////////////////////////////////
// set
////////////////////////////////////////////////

void SSDPPacket::set(SSDPPacket *ssdpPacket) {
  if (!ssdpPacket) {
    setLocalAddress("");
    setTimeStamp(0);
    setDatagramPacket(NULL);
    return;
  }
  setLocalAddress(ssdpPacket->getLocalAddress());
  setTimeStamp(ssdpPacket->getTimeStamp());
  setDatagramPacket(&ssdpPacket->getDatagramPacket());
}
