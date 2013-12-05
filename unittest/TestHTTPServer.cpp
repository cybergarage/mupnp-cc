/******************************************************************
*
*	CyberUPnP for Java
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File : TestDevice.cpp
*
******************************************************************/

#include "TestHTTPServer.h"

#include <uhttp/io/StringBufferInputStream.h>
#include <iostream>
#include <sstream>

using namespace std;
using namespace uHTTP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *TestHTTPServer::TEST_URI = "/test";
const char *TestHTTPServer::TEST_INPUTSTREAM_URI = "/testInStream";
const char *TestHTTPServer::TEST_CHUNKED_URI = "/testChunked";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

TestHTTPServer::TestHTTPServer()
{
	addRequestListener(this);
}

////////////////////////////////////////////////
// HttpRequestListner
////////////////////////////////////////////////

uHTTP::HTTP::StatusCode TestHTTPServer::httpRequestRecieved(HTTPRequest *httpReq)
{
		string uri;
		httpReq->getURI(uri);
		if (uri.compare(TEST_INPUTSTREAM_URI) == 0) {
			return httpInputStreamRequestRecieved(httpReq);
		}

		HTTPResponse httpRes;
		httpRes.setStatusCode(HTTP::OK_REQUEST);
		httpRes.setContent(content);
		return httpReq->post(&httpRes);
}

uHTTP::HTTP::StatusCode TestHTTPServer::httpInputStreamRequestRecieved(HTTPRequest *httpReq)
{
	StringBufferInputStream in(content.c_str());

	HTTPResponse httpRes;
	httpRes.setStatusCode(HTTP::OK_REQUEST);
	httpRes.setContentInputStream(&in);
	httpRes.setContentLength(content.length());
	return httpReq->post(&httpRes);
}

uHTTP::HTTP::StatusCode TestHTTPServer::httpChunkedStreamRequestRecieved(uHTTP::HTTPRequest *httpReq)
{
		HTTPResponse httpRes;
		httpRes.setTransferEncoding(HTTP::CHUNKED);
		httpRes.setStatusCode(HTTP::OK_REQUEST);
		httpRes.setContent(content);
		return httpReq->post(&httpRes);
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////

void TestHTTPServer::update()
{
}

