/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2004
*
*  File: SSDPPacket.h
*
*  Revision;
*
*  06/05/03
*    - first revision
*  01/06/04
*    - Added set() and isNull().
*
******************************************************************/

#ifndef _CLINK_SSDPPACKET_H_
#define _CLINK_SSDPPACKET_H_

#include <iostream>
#include <string>

#include <uhttp/net/DatagramPacket.h>
#include <uhttp/http/HTTP.h>
#include <uhttp/http/HTTPHeader.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/device/NTS.h>
#include <cybergarage/upnp/device/MAN.h>
#include <cybergarage/upnp/device/NT.h>
#include <cybergarage/upnp/device/ST.h>
#include <cybergarage/upnp/device/USN.h>

namespace CyberLink {
class SSDPPacket  {
  uHTTP::DatagramPacket  dgmPacket;
  std::string localAddr;
  long timeStamp;

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
 public:
  SSDPPacket() {
  }

  ////////////////////////////////////////////////
  //  DatagramPacket
  ////////////////////////////////////////////////
  
 public:
  void setDatagramPacket(uHTTP::DatagramPacket *packet) {
    dgmPacket.set(packet);
  }

  uHTTP::DatagramPacket &getDatagramPacket() {
    return dgmPacket;
  }

  ////////////////////////////////////////////////
  //  addr
  ////////////////////////////////////////////////
  
 public:
  void setLocalAddress(const std::string & addr) {
    localAddr = addr;
  }
  
  const char *getLocalAddress() {
    return localAddr.c_str();
  }

  ////////////////////////////////////////////////
  //  Time
  ////////////////////////////////////////////////

 public:
  void setTimeStamp(long value) {
    timeStamp = value;
  }
    
  long getTimeStamp() {
    return timeStamp;
  }

  ////////////////////////////////////////////////
  //  Remote host
  ////////////////////////////////////////////////

 public:
  const char *getRemoteAddress() {
    return dgmPacket.getAddress();
  }

  int getRemotePort() {
    return dgmPacket.getPort();
  }
  
  ////////////////////////////////////////////////
  //  Access Methods
  ////////////////////////////////////////////////

 public:
  const char *getData() {
    return dgmPacket.getData();
  }

  ////////////////////////////////////////////////
  //  Access Methods
  ////////////////////////////////////////////////

 public:
  const char *getHost(std::string &buf) {
    return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::HOST, buf);
  }

  const char *getCacheControl(std::string &buf) {
    return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::CACHE_CONTROL, buf);
  }
  
  const char *getLocation(std::string &buf) {
    return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::LOCATION, buf);
  }

  const char *getMAN(std::string &buf) {
    return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::MAN, buf);
  }

  const char *getST(std::string &buf) {
    return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::ST, buf);
  }

  const char *getNT(std::string &buf) {
    return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::NT, buf);
  }

  const char *getNTS(std::string &buf) {
    return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::NTS, buf);
  }

  const char *getServer(std::string &buf) {
    return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::SERVER, buf);
  }

  const char *getUSN(std::string &buf) {
    return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::USN, buf);
  }

  int getMX() {
    return uHTTP::HTTPHeaderGetIntegerValue(getData(), uHTTP::HTTP::MX);
  }

  ////////////////////////////////////////////////
  //  Access Methods (Extension)
  ////////////////////////////////////////////////

 public:
  bool isRootDevice();

  bool isDiscover() {
    std::string buf;
    return MAN::IsDiscover(getMAN(buf));
  }

  bool isAlive() {
    std::string buf;
    return NTS::IsAlive(getNTS(buf));
  }

  bool isByeBye() {
    std::string buf;
    return NTS::IsByeBye(getNTS(buf));
  }

  int getLeaseTime() {
    std::string buf;
    return SSDP::GetLeaseTime(getCacheControl(buf));
  }

  ////////////////////////////////////////////////
  //  set
  ////////////////////////////////////////////////

 public:
  void set(SSDPPacket *ssdpPacket);
  
  bool isNull() {
    return (timeStamp == 0) ? true : false;
  }

  ////////////////////////////////////////////////
  //  toString
  ////////////////////////////////////////////////

 public:
  const char *toString() {
    return getData();
  }

  void print() {
    std::cout << toString() << std::endl;
  }  
};

}

#endif


