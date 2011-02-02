/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPResponse.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_HTTPRESPONSE_H_
#define _CHTTP_HTTPRESPONSE_H_

#include <cybergarage/http/HTTPPacket.h>
#include <cybergarage/http/HTTPStatus.h>

#include <string>

namespace CyberHTTP {

class HTTPResponse : public HTTPPacket
{
	int statusCode;

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
public:

	HTTPResponse();

	HTTPResponse(HTTPResponse *httpRes);

	////////////////////////////////////////////////
	//	Status Line
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
		return HTTPStatus::isSuccessful(getStatusCode());
	}

	const char *getStatusLineString(std::string &statusLineBuf);

	////////////////////////////////////////////////
	//	getHeader
	////////////////////////////////////////////////
	
public:

	const char *getHeader(std::string &headerBuf);

	////////////////////////////////////////////////
	//	toString
	////////////////////////////////////////////////

public:

	const char *toString(std::string &buf);

	void print();

};

}

#endif
