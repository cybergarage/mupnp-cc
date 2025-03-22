/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_TESTHTTPSERVER_H_
#define _MUPMPCC_TESTHTTPSERVER_H_

#include <mupnp/mUPnP.h>
#include <string>

class TestHTTPServer : public uHTTP::HTTPServer, public uHTTP::HTTPRequestListener {
  public:
  static const char* TEST_URI;
  static const char* TEST_INPUTSTREAM_URI;
  static const char* TEST_CHUNKED_URI;

  public:
  TestHTTPServer();

  ////////////////////////////////////////////////
  // setContent
  ////////////////////////////////////////////////

  std::string content;

  void setContent(const char* value)
  {
    content = value;
  }

  ////////////////////////////////////////////////
  // HttpRequestListner
  ////////////////////////////////////////////////

  uHTTP::HTTP::StatusCode httpRequestRecieved(uHTTP::HTTPRequest* httpReq);
  uHTTP::HTTP::StatusCode httpInputStreamRequestRecieved(uHTTP::HTTPRequest* httpReq);
  uHTTP::HTTP::StatusCode httpChunkedStreamRequestRecieved(uHTTP::HTTPRequest* httpReq);

  ////////////////////////////////////////////////
  // update
  ////////////////////////////////////////////////

  void update();
};

#endif
