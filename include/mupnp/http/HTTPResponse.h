/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_HTTPRESPONSE_H_
#define _UHTTP_HTTPRESPONSE_H_

#include <mupnp/http/HTTPPacket.h>
#include <mupnp/http/HTTPStatus.h>

#include <string>

namespace uHTTP {
class HTTPResponse : public HTTPPacket {
  int statusCode;

  public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  public:
  HTTPResponse();

  HTTPResponse(HTTPResponse* httpRes);

  ////////////////////////////////////////////////
  //  Status Line
  ////////////////////////////////////////////////

  public:
  void setStatusCode(int code)
  {
    statusCode = code;
  }

  int getStatusCode()
  {
    if (statusCode != 0)
      return statusCode;
    HTTPStatus httpStatus(getFirstLine());
    return httpStatus.getStatusCode();
  }

  bool isSuccessful()
  {
    return HTTP::IsStatusCodeSuccess(getStatusCode());
  }

  const char* getStatusLineString(std::string& statusLineBuf);

  ////////////////////////////////////////////////
  //  getHeader
  ////////////////////////////////////////////////

  public:
  const char* getHeader(std::string& headerBuf);

  ////////////////////////////////////////////////
  //  toString
  ////////////////////////////////////////////////

  public:
  const char* toString(std::string& buf);

  void print();
};

}

#endif
