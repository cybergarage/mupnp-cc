<<<<<<< HEAD
/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File:	ParserException.h
*
*	Revision;
*
*	08/30/03
*		- first revision
*
******************************************************************/

#ifndef _CXML_PARSEREXCEPTION_H_
#define _CXML_PARSEREXCEPTION_H_

#include <uhttp/util/Exception.h>

namespace CyberXML {

class ParserException : public uHTTP::Exception
{
public:

	ParserException(const std::string &msg) : Exception(msg)
	{
	}
	
};

}

#endif
=======
/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File:	ParserException.h
*
*	Revision;
*
*	08/30/03
*		- first revision
*
******************************************************************/

#ifndef _CXML_PARSEREXCEPTION_H_
#define _CXML_PARSEREXCEPTION_H_

#include <cybergarage/util/Exception.h>

namespace CyberXML {

class ParserException : public CyberUtil::Exception
{
public:

	ParserException(const char *msg) : Exception(msg)
	{
	}
	
};

}

#endif
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
