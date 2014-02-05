/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPSearchRequest.h
*
*  Revision;
*
*  07/10/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SSDPSEARCHRESPONSE_H_
#define _CLINK_SSDPSEARCHRESPONSE_H_

#include <sstream>

#include <cybergarage/upnp/UPnP.h>
#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/ssdp/SSDPResponse.h>

namespace CyberLink {
class SSDPSearchResponse : public SSDPResponse {
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

public:
  
  SSDPSearchResponse() {
    setStatusCode(uHTTP::HTTP::OK_REQUEST);
    setCacheControl(Device::DEFAULT_LEASE_TIME);
    std::string buf;
    setHeader(uHTTP::HTTP::SERVER, UPnP::GetServerName(buf));
    setHeader(uHTTP::HTTP::EXT, "");
  }
};

}

#endif
