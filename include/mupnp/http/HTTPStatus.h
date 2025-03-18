/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPStatus.h
*
*	Revision;
*
*	03/23/03
*		- first revision.
*	
******************************************************************/

#ifndef _CHTTP_HTTPSTATUS_H_
#define _CHTTP_HTTPSTATUS_H_

#include <string>

namespace CyberHTTP {

namespace HTTP {
const int CONTINUE = 100;
const int OK_REQUEST = 200;
// Thanks for Brent Hills (10/20/04)
const int PARTIAL_CONTENT = 206;
const int BAD_REQUEST = 400;
const int NOT_FOUND = 404;
const int PRECONDITION_FAILED = 412;
// Thanks for Brent Hills (10/20/04)
const int INVALID_RANGE =416;
const int INTERNAL_SERVER_ERROR = 500;
}

namespace HTTP {
const char *StatusCode2String(int code);
}

class HTTPStatus 
{
	std::string version;
	int statusCode;
	std::string reasonPhrase;

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	HTTPStatus();
	HTTPStatus(const char *lineStr);
	HTTPStatus(const char *ver, int code, const char *reason);
	
	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

public:

	void setVersion(const char *value)
	{
		this->version = value;
	}
		
	void setStatusCode(int value)
	{
		this->statusCode = value;
	}
		
	void setReasonPhrase(const char *value)
	{
		this->reasonPhrase = value;
	}
		
	const char *getVersion()
	{
		return version.c_str();
	}
		
	int getStatusCode()
	{
		return statusCode;
	}
		
	const char *getReasonPhrase()
	{
		return reasonPhrase.c_str();
	}

	////////////////////////////////////////////////
	//	Status
	////////////////////////////////////////////////
	
public:

	static bool isSuccessful(int statCode);

	bool isSuccessful()
	{
		return isSuccessful(getStatusCode());
	}

	////////////////////////////////////////////////
	//	set
	////////////////////////////////////////////////

public:

	void set(const char *lineStr);

};

}

#endif
