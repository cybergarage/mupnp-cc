/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File:	Exception.h
*
*	Revision;
*
*	08/30/03
*		- first revision
*
******************************************************************/

#ifndef _CUTIL_EXCEPTION_H_
#define _CUTIL_EXCEPTION_H_

#include <string>

namespace CyberUtil {

class Exception
{
	std::string msg;

public:

	Exception(const char *msg)
	{
		this->msg = msg;
	}

	const char *getMessage()
	{
		return msg.c_str();
	}
};

}

#endif

