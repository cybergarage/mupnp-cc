<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: InvalidDescriptionException.h
*
*	Revision:
*
*	08/30/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_INVALIDDESCRIPTIONEXCEPTION_H_
#define _CLINK_INVALIDDESCRIPTIONEXCEPTION_H_

#include <uhttp/util/Exception.h>

namespace CyberLink {

const char INVALIDDESCRIPTIONEXCEPTION_FILENOTFOUND[] = "File not found";

class InvalidDescriptionException : public uHTTP::Exception
{

	std::string errMsg;
	
public:

	InvalidDescriptionException(const std::string &msg) : Exception(msg)
	{
	}

};

}

#endif

=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: InvalidDescriptionException.h
*
*	Revision:
*
*	08/30/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_INVALIDDESCRIPTIONEXCEPTION_H_
#define _CLINK_INVALIDDESCRIPTIONEXCEPTION_H_

#include <cybergarage/util/Exception.h>

namespace CyberLink {

const char INVALIDDESCRIPTIONEXCEPTION_FILENOTFOUND[] = "File not found";

class InvalidDescriptionException : public CyberUtil::Exception
{

	std::string errMsg;
	
public:

	InvalidDescriptionException(const char *msg) : Exception(msg)
	{
	}

};

}

#endif

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
