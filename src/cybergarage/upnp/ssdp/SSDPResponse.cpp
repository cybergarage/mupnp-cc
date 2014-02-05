/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SSDPResponse.cpp
*
*  Revision;
*
*  07/10/03
*    - first revision
*  01/23/04
*    - Oliver Newell
*    - Overided HTTPResponse::getHeader() for Intel UPnP control points.
*  03/16/04
*    - Thanks for Darrell Young
*    - Fixed to set v1.1 to the HTTP version.;
*  10/20/04
*    - Brent Hills <bhills@openshores.com>
*    - Added setMYNAME() and getMYNAME();
*  08/21/05
*    - Changed setLeaseTime() using Integer2String instead of ostringstream.
*    - Changed getHeader() using string instead of ostringstream.
*
******************************************************************/

#include <cybergarage/upnp/ssdp/SSDPResponse.h>
#include <uhttp/util/StringUtil.h>

using namespace std;
using namespace CyberLink;
using namespace uHTTP;
using namespace uHTTP;

////////////////////////////////////////////////
//  CacheControl
////////////////////////////////////////////////

void SSDPResponse::setLeaseTime(int value) {
  string valueStr;
  string leaseTimeStr;
  leaseTimeStr= "max-age=";
  leaseTimeStr.append(Integer2String(value, valueStr));
  setHeader(uHTTP::HTTP::CACHE_CONTROL, leaseTimeStr.c_str());
}

int SSDPResponse::getLeaseTime() {
  const char *cacheCtrl = getHeaderValue(uHTTP::HTTP::CACHE_CONTROL);
  return SSDP::GetLeaseTime(cacheCtrl);
}


////////////////////////////////////////////////
//  getHeader
////////////////////////////////////////////////

const char *SSDPResponse::getHeader(string &headerStr) {
  string statusLineBuf;
  string headerBuf;

  headerStr.append(getStatusLineString(statusLineBuf));
  headerStr.append(getHeaderString(headerBuf));
  headerStr.append(HTTP::CRLF); // for Intel UPnP control points

  return headerStr.c_str();
}

