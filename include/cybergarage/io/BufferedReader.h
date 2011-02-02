/******************************************************************
*
*	CyberIO for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: BufferedReader.h
*
*	Revision;
*
*	04/02/03
*		- first revision
*
******************************************************************/

#ifndef _CIO_BUFFEREDREADER_H_
#define _CIO_BUFFEREDREADER_H_

#include <string>
#include <cybergarage/io/Reader.h>

namespace CyberIO {

class BufferedReader
{	
	Reader *reader;
	std::string lineStr;

public:

	BufferedReader(Reader *reader)
	{
		this->reader = reader;
	}

	int read(std::string &b, int len)
	{
		return reader->read(b, len);
	}

	long skip(long n)
	{
		return reader->skip(n);
	}

	void unread(std::string &b, int off, int len)
	{
		reader->unread(b, off, len);
	}

	void unread(std::string &b, int len)
	{
		reader->unread(b, len);
	}

	void unread(char b)
	{
		reader->unread(b);
	}

	void close()
	{
		reader->close();
	}

	const char *readLine();
};

}

#endif
