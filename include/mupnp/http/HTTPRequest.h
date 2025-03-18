/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPRequest.h
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_HTTPREQUEST_H_
#define _CHTTP_HTTPREQUEST_H_

#include <cybergarage/http/HTML.h>
#include <cybergarage/http/HTTPPacket.h>
#include <cybergarage/http/HTTPSocket.h>
#include <cybergarage/http/HTTPResponse.h>
#include <cybergarage/http/ParameterList.h>

#include <string>

namespace CyberHTTP {

class HTTPRequest : public HTTPPacket
{
	std::string method;
	std::string requestHost;
	std::string version;
	std::string uri;

	HTTPSocket *httpSocket;
	int requestPort;

	CyberNet::Socket *postSock;
	HTTPResponse httpRes;

public:
	
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	HTTPRequest();

	HTTPRequest(HTTPSocket *httpSock);
	
	////////////////////////////////////////////////
	//	Method
	////////////////////////////////////////////////

public:

	void setMethod(const char *value)
	{
		method = value;
	}
		
	const char *getMethod(std::string &methodBuf)
	{
		if (0 < method.length()) {
			methodBuf = method;
			return methodBuf.c_str();
		}
		return getFirstLineToken(0, methodBuf);
	}

	bool isMethod(const char *value);

	bool isGetRequest()
	{
		return isMethod(HTTP::GET);
	}

	bool isPostRequest()
	{
		return isMethod(HTTP::POST);
	}

	bool isHeadRequest()
	{
		return isMethod(HTTP::HEAD);
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
	//	URI
	////////////////////////////////////////////////

public:

	void setURI(const char *value, bool isCheckRelativeURL = false);
	
	const char *getURI(std::string &uriBuf);

	////////////////////////////////////////////////
	//	URI Parameter
	////////////////////////////////////////////////
	
public:

	ParameterList *getParameterList(ParameterList &paramList);
	
	const char *getParameterValue(const char *name, std::string &paramBuf)
	{
		ParameterList paramList;
		getParameterList(paramList);
		paramBuf = paramList.getValue(name);
		return paramBuf.c_str();
	}

	////////////////////////////////////////////////
	//	SOAPAction
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

	void setRequestHost(const char *host)
	{
		requestHost = host;
	}

	const char * getRequestHost()
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
	//	Socket
	////////////////////////////////////////////////

public:

	void setSocket(HTTPSocket *value)
	{
		httpSocket = value;
	}
		
	HTTPSocket *getSocket()
	{
		return httpSocket;
	}

	/////////////////////////// /////////////////////
	//	local address/port
	////////////////////////////////////////////////

public:

	const char *getLocalAddress()
	{
		return getSocket()->getLocalAddress();	
	}

	int getLocalPort()
	{
		return getSocket()->getLocalPort();	
	}

	////////////////////////////////////////////////
	//	parseRequest
	////////////////////////////////////////////////

public:

	bool parseRequestLine(const char *lineStr);

	////////////////////////////////////////////////
	//	getHeader
	////////////////////////////////////////////////

private:

	const char *getHTTPVersion(std::string &verBuf);

public:

	const char *getHeader(std::string &headerBuf);

	////////////////////////////////////////////////
	//	isKeepAlive
	////////////////////////////////////////////////
	
public:

	bool isKeepAlive();

	////////////////////////////////////////////////
	//	read
	////////////////////////////////////////////////

public:

	bool read()
	{
		return HTTPPacket::read(getSocket());
	}

	////////////////////////////////////////////////
	//	POST (Response)
	////////////////////////////////////////////////

public:

	bool post(HTTPResponse *httpRes);

	////////////////////////////////////////////////
	//	POST (Request)
	////////////////////////////////////////////////

public:

	HTTPResponse *post(const char *host, int port, HTTPResponse *httpRes, bool isKeepAlive);

	HTTPResponse *post(const char *host, int port, HTTPResponse *httpRes)
	{
		return post(host, port, httpRes, false);
	}

	HTTPResponse *post(const char *host, int port, bool isKeepAlive)
	{
		return post(host, port, &httpRes, isKeepAlive);
	}

	HTTPResponse *post(const char *host, int port)
	{
		return post(host, port, false);
	}

	////////////////////////////////////////////////
	//	set
	////////////////////////////////////////////////

public:

	void set(HTTPRequest *httpReq)
	{
		HTTPPacket::set((HTTPPacket *)httpReq);
		setSocket(httpReq->getSocket());
	}

	////////////////////////////////////////////////
	//	OK/BAD_REQUEST
	////////////////////////////////////////////////

public:

	bool returnResponse(int statusCode);

	bool returnOK()
	{
		return returnResponse(HTTP::OK_REQUEST);
	}

	bool returnBadRequest()
	{
		return returnResponse(HTTP::BAD_REQUEST);
	}

	////////////////////////////////////////////////
	//	toString
	////////////////////////////////////////////////

public:

	const char *toString(std::string &buf);

	void print();

};

}

#endif

