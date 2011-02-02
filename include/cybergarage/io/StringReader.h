/******************************************************************
*
*	CyberIO for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: StringReader.h
*
*	Revision;
*
*	07/05/03
*		- first revision
*
******************************************************************/

#ifndef _CIO_STRINGREADER_H_
#define _CIO_STRINGREADER_H_

#include <string>

#include <cybergarage/io/Reader.h>
#include <cybergarage/io/InputStream.h>

namespace CyberIO {

class StringReader : public Reader
{
	std::string buf;
	int pos;

public:

	StringReader(const char *str);
	
	int read(std::string &b, int len);
	
	long skip(long n);

	void unread(std::string &b, int off, int len)
	{
		// Not Implemented yet.
	}

	void close()
	{
	}
};

}

#endif
