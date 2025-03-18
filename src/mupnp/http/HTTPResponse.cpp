/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/http/HTML.h>
#include <mupnp/http/HTTPResponse.h>
#include <mupnp/http/HTTPServer.h>

#if defined(BTRON) || defined(ITRON) || defined(TENGINE)
#include <mupnp/util/StringUtil.h>
#endif

#include <iostream>
#include <sstream>

using namespace std;
using namespace uHTTP;
#if defined(BTRON) || defined(ITRON) || defined(TENGINE)
using namespace uHTTP;
#endif

HTTPResponse::HTTPResponse()
{
  string buf;
  setStatusCode(0);
  setContentType(TEXT_CONTENT_TYPE);
  setVersion(HTTP::VER_11);
  setServer(GetServerName(buf));
}

HTTPResponse::HTTPResponse(HTTPResponse* httpRes)
{
  setStatusCode(0);
  set(httpRes);
}

////////////////////////////////////////////////
//  Status Line
////////////////////////////////////////////////

const char* HTTPResponse::getStatusLineString(string& statusLineBuf)
{
#ifndef NO_USE_OSTRINGSTREAM
  ostringstream strBuf;
  strBuf << "HTTP/" << getVersion() << " " << getStatusCode() << " " << HTTP::StatusCodeToString(getStatusCode()) << HTTP::CRLF;
  statusLineBuf = strBuf.str();
#else
  string ibuf;
  statusLineBuf = "HTTP/";
  statusLineBuf += getVersion();
  statusLineBuf += " ";
  statusLineBuf += Integer2String(getStatusCode(), ibuf);
  statusLineBuf += " ";
  statusLineBuf += HTTP::StatusCodeToString(statusCode);
  statusLineBuf += HTTP::CRLF;
#endif
  return statusLineBuf.c_str();
}

////////////////////////////////////////////////
//  getHeader
////////////////////////////////////////////////

const char* HTTPResponse::getHeader(string& headerBuf)
{
#ifndef NO_USE_OSTRINGSTREAM
  ostringstream strBuf;
  string statusLine;
  string header;
  strBuf << getStatusLineString(statusLine);
  strBuf << getHeaderString(header);
  headerBuf = strBuf.str();
#else
  string strBuf;
  getStatusLineString(headerBuf);
  headerBuf += getHeaderString(strBuf);
#endif
  return headerBuf.c_str();
}

////////////////////////////////////////////////
//  toString
////////////////////////////////////////////////

const char* HTTPResponse::toString(string& buf)
{
  string header;
  buf = "";
  buf.append(getHeader(header));
  buf.append(HTTP::CRLF);
  buf.append(getContent());
  return buf.c_str();
}

void HTTPResponse::print()
{
  std::string buf;
#ifndef NO_USE_STD_COUT
  std::cout << toString(buf) << std::endl;
#else
  printf("%s\n", toString(buf));
#endif
}
