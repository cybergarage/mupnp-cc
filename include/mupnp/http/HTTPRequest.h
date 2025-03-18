/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_HTTPREQUEST_H_
#define _UHTTP_HTTPREQUEST_H_

#include <mupnp/http/HTML.h>
#include <mupnp/http/HTTPPacket.h>
#include <mupnp/http/HTTPResponse.h>
#include <mupnp/http/HTTPSocket.h>
#include <mupnp/http/ParameterList.h>

#include <string>

namespace uHTTP {
class HTTPRequest : public HTTPPacket {
  std::string method;
  std::string version;
  std::string uri;

  std::string requestHost;
  int requestPort;

  mupnp_shared_ptr<HTTPSocket> httpSocket;
  Socket* postSocket;

  HTTPResponse httpRes;

  public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  HTTPRequest();
  HTTPRequest(mupnp_shared_ptr<HTTPSocket> httpSock);
  ~HTTPRequest();

  ////////////////////////////////////////////////
  //  Method
  ////////////////////////////////////////////////

  public:
  void setMethod(const std::string& value)
  {
    method = value;
  }

  const char* getMethod(std::string& methodBuf)
  {
    if (0 < method.length()) {
      methodBuf = method;
      return methodBuf.c_str();
    }
    return getFirstLineToken(0, methodBuf);
  }

  bool isMethod(const std::string& value);

  bool isGetRequest()
  {
    return isMethod(HTTP::GET);
  }

  bool isPutRequest()
  {
    return isMethod(HTTP::PUT);
  }

  bool isPostRequest()
  {
    return isMethod(HTTP::POST);
  }

  bool isHeadRequest()
  {
    return isMethod(HTTP::HEAD);
  }

  bool isDeleteRequest()
  {
    return isMethod(HTTP::DELETE);
  }

  bool isUpdateRequest()
  {
    return isMethod(HTTP::UPDATE);
  }

  bool isSubscribeRequest()
  {
    return isMethod(HTTP::SUBSCRIBE);
  }

  bool isUnsubscribeRequest()
  {
    return isMethod(HTTP::UNSUBSCRIBE);
  }

  bool isNotifyRequest()
  {
    return isMethod(HTTP::NOTIFY);
  }

  ////////////////////////////////////////////////
  //  URI
  ////////////////////////////////////////////////

  public:
  void setURI(const std::string& value);
  const char* getURI(std::string& uriBuf);
  void getURI(URI& uri);

  ////////////////////////////////////////////////
  //  URL
  ////////////////////////////////////////////////

  public:
  void setURL(const std::string& value);
  void setURL(URL* url);

  ////////////////////////////////////////////////
  //  URI Parameter
  ////////////////////////////////////////////////

  public:
  ParameterList* getParameterList(ParameterList& paramList);

  bool getParameterValue(const std::string& name, std::string* paramBuf)
  {
    ParameterList paramList;
    getParameterList(paramList);
    return paramList.getParameterValue(name, paramBuf);
  }

  ////////////////////////////////////////////////
  //  SOAPAction
  ////////////////////////////////////////////////

  public:
  bool isSOAPAction()
  {
    return hasHeader(HTTP::SOAP_ACTION);
  }

  ////////////////////////////////////////////////
  // Host / Port
  ////////////////////////////////////////////////

  public:
  void setRequestHost(const std::string& host)
  {
    requestHost = host;
  }

  const char* getRequestHost()
  {
    return requestHost.c_str();
  }

  void setRequestPort(int host)
  {
    requestPort = host;
  }

  int getRequestPort()
  {
    return requestPort;
  }

  ////////////////////////////////////////////////
  //  Socket
  ////////////////////////////////////////////////

  public:
  void setSocket(mupnp_shared_ptr<HTTPSocket> socket)
  {
    httpSocket = socket;
  }

  mupnp_shared_ptr<HTTPSocket> getSocket()
  {
    return httpSocket;
  }

  /////////////////////////// /////////////////////
  //  local address/port
  ////////////////////////////////////////////////

  public:
  const char* getLocalAddress()
  {
    return getSocket()->getLocalAddress();
  }

  int getLocalPort()
  {
    return getSocket()->getLocalPort();
  }

  ////////////////////////////////////////////////
  //  parseRequest
  ////////////////////////////////////////////////

  public:
  bool parseRequestLine(const std::string& lineStr);

  ////////////////////////////////////////////////
  //  getHeader
  ////////////////////////////////////////////////

  private:
  const char* getHTTPVersion(std::string& verBuf);

  public:
  const char* getRequestLine(std::string& requestLineBuf);
  const char* getHeader(std::string& headerBuf);

  ////////////////////////////////////////////////
  //  isKeepAlive
  ////////////////////////////////////////////////

  public:
  bool isKeepAlive();

  ////////////////////////////////////////////////
  //  read
  ////////////////////////////////////////////////

  public:
  bool read()
  {
    return HTTPPacket::read(getSocket().get());
  }

  ////////////////////////////////////////////////
  //  POST (Response)
  ////////////////////////////////////////////////

  public:
  HTTP::StatusCode post(HTTPResponse* httpRes, bool isOnlyHeader = false);

  ////////////////////////////////////////////////
  //  POST (Request)
  ////////////////////////////////////////////////

  public:
  HTTPResponse* post(const std::string& host, int port, HTTPResponse* httpRes, bool isKeepAlive);

  HTTPResponse* post(const std::string& host, int port, HTTPResponse* httpRes)
  {
    return post(host, port, httpRes, false);
  }

  HTTPResponse* post(const std::string& host, int port, bool isKeepAlive)
  {
    return post(host, port, &httpRes, isKeepAlive);
  }

  HTTPResponse* post(const std::string& host, int port)
  {
    return post(host, port, (bool)false);
  }

  HTTPResponse* post(bool isKeepAlive = false)
  {
    return post(getRequestHost(), getRequestPort(), &httpRes, isKeepAlive);
  }

  ////////////////////////////////////////////////
  //  set
  ////////////////////////////////////////////////

  public:
  void set(HTTPRequest* httpReq)
  {
    HTTPPacket::set((HTTPPacket*)httpReq);
    setSocket(httpReq->getSocket());
  }

  ////////////////////////////////////////////////
  //  OK/BAD_REQUEST
  ////////////////////////////////////////////////

  public:
  HTTP::StatusCode returnResponse(int statusCode);

  HTTP::StatusCode returnOK()
  {
    return returnResponse(HTTP::OK_REQUEST);
  }

  HTTP::StatusCode returnBadRequest()
  {
    return returnResponse(HTTP::BAD_REQUEST);
  }

  HTTP::StatusCode returnNotFound()
  {
    return returnResponse(HTTP::NOT_FOUND);
  }

  ////////////////////////////////////////////////
  //  toString
  ////////////////////////////////////////////////

  public:
  const char* toString(std::string& buf);

  void print();
};

}

#endif
