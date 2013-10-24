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

#include <cybergarage/io/StringBufferInputStream.h>
#include <iostream>
#include <sstream>

using namespace std;
using namespace CyberHTTP;
using namespace CyberIO;

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

void TestHTTPServer::httpRequestRecieved(HTTPRequest *httpReq)
{
		string uri;
		httpReq->getURI(uri);
		if (uri.compare(TEST_INPUTSTREAM_URI) == 0) {
			httpInputStreamRequestRecieved(httpReq);
			return;
		}

		HTTPResponse httpRes;
		httpRes.setStatusCode(HTTP::OK_REQUEST);
		httpRes.setContent(content);
		httpReq->post(&httpRes);
}

void TestHTTPServer::httpInputStreamRequestRecieved(HTTPRequest *httpReq)
{
	StringBufferInputStream in(content.c_str());

	HTTPResponse httpRes;
	httpRes.setStatusCode(HTTP::OK_REQUEST);
	httpRes.setContentInputStream(&in);
	httpRes.setContentLength(content.length());
	httpReq->post(&httpRes);
}

void TestHTTPServer::httpChunkedStreamRequestRecieved(CyberHTTP::HTTPRequest *httpReq)
{
		HTTPResponse httpRes;
		httpRes.setTransferEncoding(HTTP::CHUNKED);
		httpRes.setStatusCode(HTTP::OK_REQUEST);
		httpRes.setContent(content);
		httpReq->post(&httpRes);
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////

void TestHTTPServer::update()
{
}

