/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPRequestListener.h
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_HTTPREQUESTLISTENER_H_
#define _CHTTP_HTTPREQUESTLISTENER_H_

#include <cybergarage/http/HTTPRequest.h>

namespace CyberHTTP {

class HTTPRequestListener
{
public:
	virtual void httpRequestRecieved(HTTPRequest *httpReq) = 0;
};

}

#endif
