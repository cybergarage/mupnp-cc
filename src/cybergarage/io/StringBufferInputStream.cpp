/******************************************************************
*
*	CyberIO for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: StringReader.cpp
*
*	Revision:
*
*	09/19/04
*		- first revision
*
******************************************************************/

#include <string.h>
#include <cybergarage/io/StringBufferInputStream.h>

using namespace CyberIO;

StringBufferInputStream::StringBufferInputStream(const char *str)
{
	buf = str;
	pos = 0;
}

int StringBufferInputStream::read(std::string &b, int len)
{
	int bufLen = buf.length() - pos;
	if (bufLen <= 0)
		return 0;
	int copyLen = (len < bufLen) ? len : bufLen;
	b.append(buf, pos, copyLen);
	pos += copyLen;
	return copyLen;
}

int StringBufferInputStream::read(char *b, int len)
{
	int bufLen = buf.length() - pos;
	if (bufLen <= 0)
		return 0;
	int copyLen = (len < bufLen) ? len : bufLen;
	strncpy(b, (buf.c_str() + pos), copyLen);
	pos += copyLen;
	return copyLen;
}

long StringBufferInputStream::skip(long n)
{
	pos += n;
	return n;
}

