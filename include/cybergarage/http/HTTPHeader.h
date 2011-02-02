/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPHeader.h
*
*	Revision;
*
*	03/22/03
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_HTTPHEADER_H_
#define _CHTTP_HTTPHEADER_H_

#include <string>
#include <stdio.h>

#include <cybergarage/io/LineNumberReader.h>

namespace CyberHTTP {

class HTTPHeader 
{
	std::string name;
	std::string value;

public:

	HTTPHeader(const char *lineStr);
	HTTPHeader(const char *name, const char *value);
	HTTPHeader(HTTPHeader *header);

	~HTTPHeader();

	void setName(const char *name)
	{
		this->name = name;
	}

	const char *getName()
	{
		return name.c_str();
	}

	bool hasName()
	{
		if (name.length() <= 0)
			return false;
		return true;
	}

	void setValue(const char *value)
	{
		this->value = value;
	}

	const char *getValue()
	{
		return value.c_str();
	}
};

const char *HTTPHeaderGetValue(CyberIO::LineNumberReader *reader, const char *name, std::string &buf);
const char *HTTPHeaderGetValue(const char *data, const char *name, std::string &buf);
int HTTPHeaderGetIntegerValue(const char *data, const char *name);

}

#endif
