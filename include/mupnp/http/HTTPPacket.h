/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_HTTPPACKET_H_
#define _UHTTP_HTTPPACKET_H_

#include <mupnp/http/HTTP.h>
#include <mupnp/http/HTTPDate.h>
#include <mupnp/http/HTTPHeader.h>
#include <mupnp/http/HTTPSocket.h>

#include <sstream>
#include <string>
#include <vector>

#include <stdlib.h>

namespace uHTTP {

class HTTPPacket {
  HTTPHeaderList httpHeaderList;

  std::string firstLine;
  std::string content;
  std::string version;

  uHTTP::InputStream* contentInput;

  public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  HTTPPacket();
  HTTPPacket(HTTPPacket* httpPacket);
  HTTPPacket(HTTPSocket* httpSock);
  HTTPPacket(uHTTP::InputStream* in);

  ~HTTPPacket();

  ////////////////////////////////////////////////
  //  init
  ////////////////////////////////////////////////

  public:
  void init();

  ////////////////////////////////////////////////
  //  Version
  ////////////////////////////////////////////////

  public:
  void setVersion(const std::string& ver)
  {
    version = ver;
  }

  const char* getVersion()
  {
    return version.c_str();
  }

  ////////////////////////////////////////////////
  //  set
  ////////////////////////////////////////////////

  bool set(uHTTP::InputStream* in, bool onlyHeaders = false);
  bool set(uHTTP::Socket* sock, bool onlyHeaders = false);
  bool set(HTTPSocket* httpSock);
  void set(HTTPPacket* httpPacket);

  ////////////////////////////////////////////////
  //  read
  ////////////////////////////////////////////////

  bool read(HTTPSocket* httpSock);

  ////////////////////////////////////////////////
  //  String
  ////////////////////////////////////////////////

  void setFirstLine(const std::string& value)
  {
    firstLine = value;
  }

  const char* getFirstLine()
  {
    return firstLine.c_str();
  }

  const char* getFirstLineToken(int num, std::string& tokenBuf);

  bool hasFirstLine()
  {
    return (0 < firstLine.length()) ? true : false;
  }

  ////////////////////////////////////////////////
  //  Header
  ////////////////////////////////////////////////

  size_t getNHeaders()
  {
    return httpHeaderList.size();
  }

  bool addHeader(HTTPHeader* header)
  {
    httpHeaderList.push_back(header);
    return true;
  }

  bool addHeader(const std::string& name, const std::string& value);

  HTTPHeader* getHeader(size_t n);

  HTTPHeaderList& getHeaders()
  {
    return httpHeaderList;
  }

  HTTPHeader* getHeader(const std::string& name);

  void clearHeaders();

  bool hasHeader(const std::string& name)
  {
    return (getHeader(name)) ? true : false;
  }

  void setHeader(const std::string& name, const std::string& value);
  void setHeader(const std::string& name, int value);
  void setHeader(const std::string& name, long value);
  void setHeader(const std::string& name, size_t value);

  void setHeader(HTTPHeader* header)
  {
    setHeader(header->getName(), header->getValue());
  }

  const char* getHeaderValue(const std::string& name)
  {
    HTTPHeader* header = getHeader(name);
    if (!header)
      return "";
    return header->getValue();
  }

  ////////////////////////////////////////////////
  // set*Value
  ////////////////////////////////////////////////

  void setStringHeader(const std::string& name, const std::string& value, const char startWith, const char endWith);

  void setStringHeader(const std::string& name, const std::string& value)
  {
    setStringHeader(name, value, '\"', '\"');
  }

  const char* getStringHeaderValue(const std::string& name, const char startWith, const char endWith, std::string& buf);

  const char* getStringHeaderValue(const std::string& name, std::string& buf)
  {
    return getStringHeaderValue(name, '\"', '\"', buf);
  }

  void setIntegerHeader(const std::string& name, int value)
  {
    setHeader(name, value);
  }

  void setLongHeader(const std::string& name, long value)
  {
    setHeader(name, value);
  }

  void setSizetHeader(const std::string& name, size_t value)
  {
    setHeader(name, value);
  }

  int getIntegerHeaderValue(const std::string& name)
  {
    HTTPHeader* header = getHeader(name);
    if (!header)
      return 0;
    return atoi(header->getValue());
  }

  long getLongHeaderValue(const std::string& name)
  {
    HTTPHeader* header = getHeader(name);
    if (!header)
      return 0;
    return atol(header->getValue());
  }

  size_t getLongLongHeaderValue(const std::string& name)
  {
    HTTPHeader* header = getHeader(name);
    if (!header)
      return 0;
    return atoll(header->getValue());
  }

  ////////////////////////////////////////////////
  //  getHeaderString
  ////////////////////////////////////////////////

  const char* getHeaderString(std::string& headerStr);

  ////////////////////////////////////////////////
  //  Contents
  ////////////////////////////////////////////////

  void setContent(const std::string& data, bool updateWithContentLength = true)
  {
    content = data;
    if (updateWithContentLength == true)
      setContentLength(content.length());
  }

  void setContent(std::string& data, bool updateWithContentLength = true)
  {
    setContent(data.c_str(), updateWithContentLength);
  }

  const char* getContent()
  {
    return content.c_str();
  }

  bool hasContent()
  {
    return (content.length() > 0) ? true : false;
  }

  ////////////////////////////////////////////////
  //  Contents (InputStream)
  ////////////////////////////////////////////////

  void setContentInputStream(uHTTP::InputStream* in)
  {
    contentInput = in;
  }

  uHTTP::InputStream* getContentInputStream()
  {
    return contentInput;
  }

  bool hasContentInputStream()
  {
    return (contentInput) ? true : false;
  }

  ////////////////////////////////////////////////
  //  ContentType
  ////////////////////////////////////////////////

  void setContentType(const std::string& type)
  {
    setHeader(HTTP::CONTENT_TYPE, type);
  }

  const char* getContentType()
  {
    return getHeaderValue(HTTP::CONTENT_TYPE);
  }

  const char* getCharSet(std::string& buf);

  ////////////////////////////////////////////////
  //  ContentLength
  ////////////////////////////////////////////////

  void setContentLength(size_t len)
  {
    setLongHeader(HTTP::CONTENT_LENGTH, len);
  }

  size_t getContentLength()
  {
    return getLongHeaderValue(HTTP::CONTENT_LENGTH);
  }

  ////////////////////////////////////////////////
  //  Connection
  ////////////////////////////////////////////////

  public:
  bool hasConnection()
  {
    return hasHeader(HTTP::CONNECTION);
  }

  void setConnection(const std::string& value)
  {
    setHeader(HTTP::CONNECTION, value);
  }

  const char* getConnection()
  {
    return getHeaderValue(HTTP::CONNECTION);
  }

  bool isCloseConnection();

  bool isKeepAliveConnection();

  ////////////////////////////////////////////////
  //  ContentRange
  ////////////////////////////////////////////////

  public:
  bool hasContentRange();

  void setContentRange(long firstPos, long lastPos, long length);

  void getContentRange(long range[]);

  long getContentRangeFirstPosition()
  {
    long range[3];
    getContentRange(range);
    return range[0];
  }

  long getContentRangeLastPosition()
  {
    long range[3];
    getContentRange(range);
    return range[1];
  }

  long getContentRangeInstanceLength()
  {
    long range[3];
    getContentRange(range);
    return range[2];
  }

  ////////////////////////////////////////////////
  //  CacheControl
  ////////////////////////////////////////////////

  public:
  void setCacheControl(const std::string& directive)
  {
    setHeader(HTTP::CACHE_CONTROL, directive);
  }

  void setCacheControl(const std::string& directive, int value);

  void setCacheControl(int value)
  {
    setCacheControl(HTTP::MAX_AGE, value);
  }

  const char* getCacheControl()
  {
    return getHeaderValue(HTTP::CACHE_CONTROL);
  }

  ////////////////////////////////////////////////
  //  User-Agent
  ////////////////////////////////////////////////

  public:
  void setUserAgent(const std::string& name)
  {
    setHeader(HTTP::USER_AGENT, name);
  }

  const char* getUserAgent()
  {
    return getHeaderValue(HTTP::USER_AGENT);
  }

  ////////////////////////////////////////////////
  //  Accept
  ////////////////////////////////////////////////

  public:
  void setAccept(const std::string& name)
  {
    setHeader(HTTP::ACCEPT, name);
  }

  const char* getAccept()
  {
    return getHeaderValue(HTTP::ACCEPT);
  }

  ////////////////////////////////////////////////
  //  Server
  ////////////////////////////////////////////////

  public:
  void setServer(const std::string& name)
  {
    setHeader(HTTP::SERVER, name);
  }

  const char* getServer()
  {
    return getHeaderValue(HTTP::SERVER);
  }

  ////////////////////////////////////////////////
  //  Host
  ////////////////////////////////////////////////

  public:
  void setHost(const std::string& host, int port);
  void setHost(const std::string& host);

  const char* getHost()
  {
    return getHeaderValue(HTTP::HOST);
  }

  ////////////////////////////////////////////////
  //  Date
  ////////////////////////////////////////////////

  public:
  void setDate(HTTPDate* date)
  {
    setHeader(HTTP::DATE, date->getDateString());
  }

  const char* getDate()
  {
    return getHeaderValue(HTTP::DATE);
  }

  ////////////////////////////////////////////////
  //  Transfer-Encoding
  ////////////////////////////////////////////////

  public:
  bool hasTransferEncoding()
  {
    return hasHeader(HTTP::TRANSFER_ENCODING);
  }

  void setTransferEncoding(const std::string& value)
  {
    setHeader(HTTP::TRANSFER_ENCODING, value);
  }

  const char* getTransferEncoding()
  {
    return getHeaderValue(HTTP::TRANSFER_ENCODING);
  }

  bool isChunked();

  ////////////////////////////////////////////////
  //  Clear
  ////////////////////////////////////////////////

  public:
  void clear();
};

}

#endif
