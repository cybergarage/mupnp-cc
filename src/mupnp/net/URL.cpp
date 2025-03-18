/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/net/HostInterface.h>
#include <mupnp/net/URL.h>
#include <mupnp/util/StringUtil.h>

#include <sstream>

////////////////////////////////////////////////
//  URL::URL
////////////////////////////////////////////////

uHTTP::URL::URL()
    : URI()
{
}

////////////////////////////////////////////////
//  URL::URL
////////////////////////////////////////////////

uHTTP::URL::URL(const std::string& urlStr)
    : URI(urlStr)
{
}

////////////////////////////////////////////////
//  IsAbsoluteURL
////////////////////////////////////////////////

bool uHTTP::IsAbsoluteURL(const std::string& urlStr)
{
  URL url(urlStr);
  return url.hasProtocol();
}

////////////////////////////////////////////////
//  URLGetHost
////////////////////////////////////////////////

const char* uHTTP::URLGetHost(const std::string& urlStr, std::string& buf)
{
  URL url(urlStr);
  buf = url.getHost();
  return buf.c_str();
}

////////////////////////////////////////////////
//  URLGetPort
////////////////////////////////////////////////

int uHTTP::URLGetPort(const std::string& urlStr)
{
  URL url(urlStr);
  return url.getPort();
}

////////////////////////////////////////////////
//  URLGetRelativeURL
////////////////////////////////////////////////

const char* uHTTP::URLGetRelativeURL(const std::string& uri, std::string& buf, bool withParam)
{
  buf = uri;
  uHTTP::String urlStr = uri;
  if (IsAbsoluteURL(uri) == false) {
    if (0 < urlStr.length() && urlStr.charAt(0) != '/') {
      buf = "/";
      buf += uri;
    }
  }
  else {
    URL url(uri);
    buf = url.getPath();
    if (withParam == true) {
      String queryStr(url.getQuery());
      if (!queryStr.equals("")) {
        buf += "?";
        buf += queryStr.getValue();
      }
    }
    if (urlStr.endsWith("/")) {
      String substrBuf;
      buf = urlStr.substring(0, urlStr.length() - 1, substrBuf);
    }
  }
  return buf.c_str();
}

////////////////////////////////////////////////
//  URLGetAbsoluteURL
////////////////////////////////////////////////

const char* uHTTP::URLGetAbsoluteURL(const std::string& baseURLStr, const std::string& relURlStr, std::string& buf)
{
  URL baseURL(baseURLStr);
  std::string relURlStrBuf;
  std::string portStrBuf;
  buf = "";
  buf += baseURL.getProtocol();
  buf += URI::PROTOCOL_DELIM;
  buf += baseURL.getHost();
  buf += URI::COLON_DELIM;
  buf += Integer2String(baseURL.getPort(), portStrBuf);
  buf += URLGetRelativeURL(relURlStr, relURlStrBuf);
  return buf.c_str();
}

////////////////////////////////////////////////
//  GetHostURL
////////////////////////////////////////////////

bool uHTTP::URI::isValid()
{
  if (!hasProtocol())
    return false;
  if (!hasPath())
    return false;
  return true;
}

////////////////////////////////////////////////
//  GetHostURL
////////////////////////////////////////////////

const char* uHTTP::GetHostURL(const std::string& host, int port, const std::string& uri, std::string& buf)
{
  std::string hostStr = host;
  if (IsIPv6Address(host) == true) {
    StripIPv6ScopeID(host, hostStr);
    hostStr = "[";
    hostStr += hostStr.c_str();
    hostStr += "]";
  }
  std::string portStr;
  buf = "http://";
  buf += hostStr;
  buf += ":";
  buf += Integer2String(port, portStr);
  buf += uri;
  return buf.c_str();
}
