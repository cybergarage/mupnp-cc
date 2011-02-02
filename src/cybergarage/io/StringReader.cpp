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
*	07/05/03
*		- first revision
*	02/28/05
*		- Added skip().
*
******************************************************************/

#include <cybergarage/io/StringReader.h>

using namespace CyberIO;

StringReader::StringReader(const char *str)
{
	buf = str;
	pos = 0;
}

int StringReader::read(std::string &b, int len)
{
	int bufLen = buf.length() - pos;
	if (bufLen <= 0)
		return 0;
	int copyLen = (len < bufLen) ? len : bufLen;
	b.append(buf, pos, copyLen);
	pos += copyLen;
	return copyLen;
}

long StringReader::skip(long skipLen)
{
	pos += skipLen;
	return skipLen;
}
