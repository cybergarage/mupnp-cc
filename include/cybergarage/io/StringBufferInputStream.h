/******************************************************************
*
*	CyberIO for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: StringBufferInputStream.h
*
*	Revision;
*
*	09/19/04
*		- first revision
*
******************************************************************/

#ifndef _CIO_STRINGBUFFERINPUTSTREAM_H_
#define _CIO_STRINGBUFFERINPUTSTREAM_H_

#include <stdio.h>
#include <string>
#include <cybergarage/io/File.h>
#include <cybergarage/io/InputStream.h>

namespace CyberIO {

class StringBufferInputStream : public InputStream
{
	std::string buf;
	long pos;

public:

	StringBufferInputStream(const char *str);

	int read(std::string &b, int len);
	int read(char *b, int len);

	void unread(std::string &b, int off, int len)
	{
		// Not Implemented yet
	}

	long skip(long n);

	void close()
	{
	}
};

}

#endif
