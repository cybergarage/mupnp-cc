/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPRequest.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*	03/16/04
*		- Removed setVersion() because the method is added to the super class.
*		- Changed getVersion() to return the version when the first line string has the length.
*	04/25/04
*		- Added post(const char *host, int port, HTTPResponse *httpRes);
*	05/19/04
*		- Changed the header include order for Cygwin.
*	05/19/04
*		- Changed post(HTTPResponse *) to close the socket stream from the server.
*	08/19/04
*		- Fixed getHeader() and getHTTPVersion() no to return "HTTP/HTTP/version".
*	08/25/04
*		- Added isHeadRequest().
*	08/26/04
*		- Changed post(HTTPResponse *) not to close the connection.
*		- Changed post(const char *, int) to add a connection header to close.
*	08/27/04
*		- Changed post(String, int) to support the persistent connection.
*	08/28/04
*		- Added isKeepAlive().
*	10/22/04
*		- Added isSuccessful().
*	10/26/04
*		- Brent Hills <bhills@openshores.com>
*		- Added a fix to post() when the last position of Content-Range header is 0.
*		- Added a Content-Range header to the response in post().
*		- Changed the status code for the Content-Range request in post().
*	06/10/05
*		- Changed post() to add a HOST headedr before the posting.
*	07/07/05
*		- Lee Peik Feng <pflee@users.sourceforge.net>
*		- Fixed post() to output the chunk size as a hex string.
*
******************************************************************/

#include <string.h>

#include <string>
#include <iostream>
#include <sstream>

#include <cybergarage/http/HTTPRequest.h>
#include <cybergarage/util/StringTokenizer.h>
#include <cybergarage/net/SocketInputStream.h>
#include <cybergarage/util/StringUtil.h>

using namespace std;
using namespace CyberNet;
using namespace CyberHTTP;
using namespace CyberUtil;

 ////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

HTTPRequest::HTTPRequest()
{
	httpSocket = NULL;
	postSock = NULL;
	requestPort = -1;

	setVersion(HTTP::VER_10);
}

HTTPRequest::HTTPRequest(HTTPSocket *httpSock) : HTTPPacket(httpSock)
{
	setSocket(httpSock);
	postSock = NULL;
	requestPort = -1;
}

////////////////////////////////////////////////
//	Method
////////////////////////////////////////////////

bool HTTPRequest::isMethod(const char *method)
{
	string headerMethod;
	getMethod(headerMethod);
	return CyberUtil::StringEqualsIgnoreCase(headerMethod.c_str(), method);
}

////////////////////////////////////////////////
//	URI
////////////////////////////////////////////////

void HTTPRequest::setURI(const char *value, bool isCheckRelativeURL)
{
	uri = value;
	if (isCheckRelativeURL == false)
		return;
	HTTP::GetRelativeURL(value, uri);
}

const char *HTTPRequest::getURI(std::string &uriBuf)
{
	if (0 < uri.length())
		uriBuf = uri;
	else
		getFirstLineToken(1, uriBuf);
	return uriBuf.c_str();
}


////////////////////////////////////////////////
//	URI Parameter
////////////////////////////////////////////////
	
ParameterList *HTTPRequest::getParameterList(ParameterList &paramList)
{
	string uri;
	getURI(uri);
	if (uri.length() <= 0)
		return &paramList;
	string::size_type paramIdx = uri.find('?');
	if (paramIdx == string::npos)
		return &paramList;
	while (paramIdx != string::npos) {
		string::size_type eqIdx = uri.find('=', (paramIdx+1));
		string name = uri.substr(paramIdx+1, eqIdx-(paramIdx+1));
		string::size_type nextParamIdx = uri.find('&', (eqIdx+1));
		string value = uri.substr(eqIdx+1, ((nextParamIdx != string::npos) ? nextParamIdx : uri.length()) - (eqIdx+1));
		Parameter *param = new Parameter(name.c_str(), value.c_str());
		paramList.add(param);
		paramIdx = nextParamIdx;
	}
	return &paramList;
}

////////////////////////////////////////////////
//	parseRequest
////////////////////////////////////////////////

bool HTTPRequest::parseRequestLine(const char *lineStr)
{
	CyberUtil::StringTokenizer st(lineStr, HTTP::REQEST_LINE_DELIM);
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
//	getHeader
////////////////////////////////////////////////
	
const char *HTTPRequest::getHTTPVersion(std::string &verBuf)
{
	if (hasFirstLine() == true)
		return getFirstLineToken(2, verBuf);
	verBuf = "";
	verBuf += "HTTP/";
	verBuf += HTTPPacket::getVersion();
	return verBuf.c_str();
}

const char *HTTPRequest::getHeader(std::string &headerBuf)
{
	std::string buf;
	headerBuf = "";
	headerBuf += getMethod(buf);
	headerBuf += " ";
	headerBuf += getURI(buf);
	headerBuf += " ";
	headerBuf += getHTTPVersion(buf);
	headerBuf += HTTP::CRLF;
	headerBuf += getHeaderString(buf);
	return headerBuf.c_str();
}
	
////////////////////////////////////////////////
//	isKeepAlive
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
//	returnResponse
////////////////////////////////////////////////

bool HTTPRequest::returnResponse(int statusCode)
{
	HTTPResponse httpRes;
	httpRes.setStatusCode(statusCode);
	httpRes.setContentLength(0);
	return post(&httpRes);
}

////////////////////////////////////////////////
//	POST (Response)
////////////////////////////////////////////////

bool HTTPRequest::post(HTTPResponse *httpRes)
{
	HTTPSocket *httpSock = getSocket();
	long offset = 0;
	long length = httpRes->getContentLength();
	if (hasContentRange() == true) {
		long firstPos = getContentRangeFirstPosition();
		long lastPos = getContentRangeLastPosition();
		
		// Thanks for Brent Hills (10/26/04)
		if (lastPos <= 0) 
			lastPos = length - 1;
		if ((firstPos > length ) || (lastPos > length))
			return returnResponse(HTTP::INVALID_RANGE);
		httpRes->setContentRange(firstPos, lastPos, length);
		httpRes->setStatusCode(HTTP::PARTIAL_CONTENT);

		offset = firstPos;
		length = lastPos - firstPos + 1;
	}
	return httpSock->post(httpRes, offset, length, isHeadRequest(), isChunked());
}

////////////////////////////////////////////////
//	POST (Request)
////////////////////////////////////////////////

HTTPResponse *HTTPRequest::post(const char *host, int port, HTTPResponse *httpRes, bool isKeepAlive)
{
	if (postSock == NULL) {
		postSock = new Socket();
		if (postSock->connect(host, port) == false) {
			httpRes->setStatusCode(HTTP::INTERNAL_SERVER_ERROR);
			return httpRes;
		}
	}	

	setHost(host);

	setConnection((isKeepAlive == true) ? HTTP::KEEP_ALIVE : HTTP::CLOSE);

	string header;
	postSock->send(getHeader(header));
	postSock->send(HTTP::CRLF);
	
	bool isChunkedRequest = isChunked();

	const char *content = getContent();
	int contentLength = 0;
	if (content != NULL)
		contentLength = strlen(content);

	if (0 < contentLength) {
		if (isChunkedRequest == true) {
			string chunSizeBuf;
			Integer2HexString(strlen(content), chunSizeBuf);
			postSock->send(chunSizeBuf.c_str());
			postSock->send(HTTP::CRLF);
		}
		postSock->send(content);
		if (isChunkedRequest == true)
			postSock->send(HTTP::CRLF);
	}

	if (isChunkedRequest == true) {
		postSock->send("0");
		postSock->send(HTTP::CRLF);
	}

	httpRes->set(postSock, isHeadRequest());			

	if (isKeepAlive == false) {	
		postSock->close();
		delete postSock;
		postSock = NULL;
	}

	return httpRes;
}

////////////////////////////////////////////////
//	toString
////////////////////////////////////////////////

const char *HTTPRequest::toString(std::string &buf)
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
