/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <errno.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <string>

#include <mupnp/http/HTTPRequest.h>
#include <mupnp/net/SocketInputStream.h>
#include <mupnp/util/StringTokenizer.h>
#include <mupnp/util/StringUtil.h>

using namespace std;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

HTTPRequest::HTTPRequest()
{
  postSocket = NULL;
  requestPort = -1;

  setVersion(HTTP::VER_11);

  ostringstream defaultUserAgent;
  defaultUserAgent << uHTTP::PRODUCT_NAME << "/" << uHTTP::LIBRARY_VERSION << " " << uHTTP::LIBRARY_NAME << "/" << uHTTP::LIBRARY_VERSION;
  setUserAgent(defaultUserAgent.str());

  setAccept("*/*");
}

HTTPRequest::HTTPRequest(mupnp_shared_ptr<HTTPSocket> httpSock)
    : HTTPPacket(httpSock.get())
{
  setSocket(httpSock);
  postSocket = NULL;
  requestPort = -1;
}

HTTPRequest::~HTTPRequest()
{
  if (postSocket) {
    delete postSocket;
    postSocket = NULL;
  }
}

////////////////////////////////////////////////
//  Method
////////////////////////////////////////////////

bool HTTPRequest::isMethod(const std::string& method)
{
  string headerMethod;
  getMethod(headerMethod);
  return StringEqualsIgnoreCase(headerMethod.c_str(), method);
}

////////////////////////////////////////////////
//  URI
////////////////////////////////////////////////

void uHTTP::HTTPRequest::setURI(const std::string& value)
{
  uri = value;
}

const char* uHTTP::HTTPRequest::getURI(std::string& uriBuf)
{
  if (0 < uri.length())
    uriBuf = uri;
  else
    getFirstLineToken(1, uriBuf);
  return uriBuf.c_str();
}

void uHTTP::HTTPRequest::getURI(URI& uri)
{
  std::string uriString;
  getURI(uriString);
  uri.setString(uriString);
}

////////////////////////////////////////////////
//  URI
////////////////////////////////////////////////

void uHTTP::HTTPRequest::setURL(const std::string& urlString)
{
  URL url(urlString);
  setURL(&url);
}

void uHTTP::HTTPRequest::setURL(URL* url)
{
  setRequestHost(url->getHost());
  setRequestPort(url->getPort());

  setHost(getRequestHost(), getRequestPort());
  std::stringstream uriBuf;

  if (url->hasPath())
    uriBuf << url->getPath();
  if (url->hasFragment())
    uriBuf << URL::SHARP_DELIM << url->getFragment();
  if (url->hasQuery())
    uriBuf << URL::QUESTION_DELIM << url->getQuery();
  setURI(uriBuf.str());
}

////////////////////////////////////////////////
//  URI Parameter
////////////////////////////////////////////////

ParameterList* HTTPRequest::getParameterList(ParameterList& paramList)
{
  string uri;
  getURI(uri);
  if (uri.length() <= 0)
    return &paramList;
  string::size_type paramIdx = uri.find('?');
  if (paramIdx == string::npos)
    return &paramList;
  while (paramIdx != string::npos) {
    string::size_type eqIdx = uri.find('=', (paramIdx + 1));
    string name = uri.substr(paramIdx + 1, eqIdx - (paramIdx + 1));
    string::size_type nextParamIdx = uri.find('&', (eqIdx + 1));
    string value = uri.substr(eqIdx + 1, ((nextParamIdx != string::npos) ? nextParamIdx : uri.length()) - (eqIdx + 1));
    Parameter* param = new Parameter(name.c_str(), value.c_str());
    paramList.add(param);
    paramIdx = nextParamIdx;
  }
  return &paramList;
}

////////////////////////////////////////////////
//  parseRequest
////////////////////////////////////////////////

bool HTTPRequest::parseRequestLine(const std::string& lineStr)
{
  StringTokenizer st(lineStr, HTTP::REQEST_LINE_DELIM);
  if (st.hasMoreTokens() == false)
    return false;
  setMethod(st.nextToken());
  if (st.hasMoreTokens() == false)
    return false;
  setURI(st.nextToken());
  if (st.hasMoreTokens() == false)
    return false;
  setVersion(st.nextToken());
  return true;
}

////////////////////////////////////////////////
//  getHeader
////////////////////////////////////////////////

const char* HTTPRequest::getHTTPVersion(std::string& verBuf)
{
  if (hasFirstLine() == true)
    return getFirstLineToken(2, verBuf);
  verBuf = "";
  verBuf += "HTTP/";
  verBuf += HTTPPacket::getVersion();
  return verBuf.c_str();
}

const char* HTTPRequest::getRequestLine(std::string& requestLineBuf)
{
  std::string buf;
  requestLineBuf = "";
  requestLineBuf += getMethod(buf);
  requestLineBuf += " ";
  requestLineBuf += getURI(buf);
  requestLineBuf += " ";
  requestLineBuf += getHTTPVersion(buf);
  return requestLineBuf.c_str();
}

const char* HTTPRequest::getHeader(std::string& headerBuf)
{
  getRequestLine(headerBuf);
  headerBuf += HTTP::CRLF;
  std::string buf;
  headerBuf += getHeaderString(buf);
  return headerBuf.c_str();
}

////////////////////////////////////////////////
//  isKeepAlive
////////////////////////////////////////////////

bool HTTPRequest::isKeepAlive()
{
  if (isCloseConnection() == true)
    return false;
  if (isKeepAliveConnection() == true)
    return true;
  string httpVer;
  getHTTPVersion(httpVer);
  bool isHTTP10 = (httpVer.find("1.0") != string::npos) ? true : false;
  if (isHTTP10 == true)
    return false;
  return true;
}

////////////////////////////////////////////////
//  returnResponse
////////////////////////////////////////////////

HTTP::StatusCode HTTPRequest::returnResponse(int statusCode)
{
  HTTPResponse httpRes;
  httpRes.setStatusCode(statusCode);
  httpRes.setContentLength(0);
  return post(&httpRes) ? statusCode : HTTP::INTERNAL_SERVER_ERROR;
}

////////////////////////////////////////////////
//  POST (Response)
////////////////////////////////////////////////

HTTP::StatusCode HTTPRequest::post(HTTPResponse* httpRes, bool isOnlyHeader)
{
  mupnp_shared_ptr<HTTPSocket> httpSock = getSocket();
  size_t offset = 0;
  size_t length = httpRes->getContentLength();
  if (hasContentRange() == true) {
    long firstPos = getContentRangeFirstPosition();
    long lastPos = getContentRangeLastPosition();

    // Thanks for Brent Hills (10/26/04)
    if (lastPos <= 0)
      lastPos = length - 1;
    if ((firstPos > length) || (lastPos > length))
      return returnResponse(HTTP::INVALID_RANGE);
    httpRes->setContentRange(firstPos, lastPos, length);
    httpRes->setStatusCode(HTTP::PARTIAL_CONTENT);

    offset = firstPos;
    length = lastPos - firstPos + 1;
  }
  return httpSock->post(httpRes, offset, length, isOnlyHeader, isChunked()) ? HTTP::OK_REQUEST : HTTP::INTERNAL_SERVER_ERROR;
}

////////////////////////////////////////////////
//  POST (Request)
////////////////////////////////////////////////

HTTPResponse* HTTPRequest::post(const std::string& host, int port, HTTPResponse* httpRes, bool isKeepAlive)
{
  if (!postSocket) {
    postSocket = new Socket();
    bool isConnected = postSocket->connect(host, port);
    bool isTimeoutSet = false;
    if (isConnected) {
      isTimeoutSet = postSocket->setTimeout(HTTP::DEFAULT_TIMEOUT_SECOND);
    }
    if (!isConnected || !isTimeoutSet) {
      int socketErrno = postSocket->getErrorCode();
      delete postSocket;
      postSocket = NULL;
      httpRes->setStatusCode((HTTP::INTERNAL_CLIENT_ERROR + socketErrno));
      return httpRes;
    }
  }

  setHost(host, port);
  setConnection((isKeepAlive == true) ? HTTP::KEEP_ALIVE : HTTP::CLOSE);

  string header;
  postSocket->send(getHeader(header));
  postSocket->send(HTTP::CRLF);

  bool isChunkedRequest = isChunked();

  const char* content = getContent();
  size_t contentLength = 0;
  if (content)
    contentLength = strlen(content);

  if (0 < contentLength) {
    if (isChunkedRequest == true) {
      string chunSizeBuf;
      Sizet2HexString(strlen(content), chunSizeBuf);
      postSocket->send(chunSizeBuf.c_str());
      postSocket->send(HTTP::CRLF);
    }
    postSocket->send(content);
    if (isChunkedRequest == true)
      postSocket->send(HTTP::CRLF);
  }

  if (isChunkedRequest == true) {
    postSocket->send("0");
    postSocket->send(HTTP::CRLF);
  }

  httpRes->set(postSocket, isHeadRequest());

  if (isKeepAlive == false) {
    postSocket->close();
    delete postSocket;
    postSocket = NULL;
  }

  return httpRes;
}

////////////////////////////////////////////////
//  toString
////////////////////////////////////////////////

const char* HTTPRequest::toString(std::string& buf)
{
  getHeader(buf);
  buf += HTTP::CRLF;
  buf += getContent();

  return buf.c_str();
}

void HTTPRequest::print()
{
  std::string buf;
#ifndef NO_USE_STD_COUT
  std::cout << toString(buf) << std::endl;
#else
  printf("%s\n", toString(buf));
#endif
}
