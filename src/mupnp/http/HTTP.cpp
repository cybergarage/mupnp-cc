/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sstream>
#include <mupnp/http/HTTP.h>
#include <mupnp/net/URI.h>

#ifdef NO_USE_OSTRINGSTREAM
#include <mupnp/util/StringUtil.h>
#endif

using namespace std;
using namespace uHTTP;
#ifdef NO_USE_OSTRINGSTREAM
using namespace uHTTP;
#endif

int uHTTP::HTTP::GetPort(const std::string& urlStr)
{
  int port = uHTTP::URLGetPort(urlStr);
  if (port <= 0)
    port = HTTP::DEFAULT_PORT;
  return port;
}

const char* uHTTP::HTTP::GetAbsoluteURL(const std::string& baseURLStr, const std::string& relURlStr, std::string& buf)
{
  uHTTP::URL baseURL(baseURLStr);
  int port = baseURL.getPort();
  if (port <= 0)
    port = HTTP::DEFAULT_PORT;
  string relURlStrBuf;
#ifndef NO_USE_OSTRINGSTREAM
  ostringstream url;
  url << baseURL.getProtocol() << URI::PROTOCOL_DELIM << baseURL.getHost() << URI::COLON_DELIM << port << HTTP::GetRelativeURL(relURlStr, relURlStrBuf);
  buf = url.str();
#else
  string ibuf;
  buf = "";
  buf += baseURL.getProtocol();
  buf += URI::PROTOCOL_DELIM;
  buf += baseURL.getHost();
  buf += URI::COLON_DELIM;
  buf += Integer2String(port, ibuf);
  buf += HTTP::GetRelativeURL(relURlStr, relURlStrBuf);
#endif
  return buf.c_str();
}

const char* uHTTP::HTTP::GetRequestHostURL(const std::string& host, int port, std::string& buf)
{
#ifndef NO_USE_OSTRINGSTREAM
  std::ostringstream url;
  url << "http://" << host << ":" << port;
  buf = url.str();
#else
  string ibuf;
  buf = "";
  buf += "http://";
  buf += host;
  buf += ":";
  buf += Integer2String(port, ibuf);
#endif
  return buf.c_str();
}

////////////////////////////////////////////////
// Chunk Size
////////////////////////////////////////////////

static int httpChunkSize = uHTTP::HTTP::DEFAULT_CHUNK_SIZE;

void uHTTP::HTTP::SetChunkSize(int size)
{
  httpChunkSize = size;
}

int uHTTP::HTTP::GetChunkSize()
{
  return httpChunkSize;
}
