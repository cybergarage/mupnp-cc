/******************************************************************
*
*	CyberIO for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: LineNumberReader.h
*
*	Revision;
*
*	06/11/03
*		- first revision
*
******************************************************************/

#ifndef _CIO_LINENUMBERREADER_H_
#define _CIO_LINENUMBERREADER_H_

#include <string>

#include <cybergarage/io/BufferedReader.h>

namespace CyberIO {

class LineNumberReader : public BufferedReader
{
	int lineNum;

public:

	LineNumberReader(Reader *reader) : BufferedReader(reader)
	{
		lineNum = -1;
	}

	int getLineNumber()
	{
		return lineNum;
	}

	const char *readLine()
	{
		lineNum++;
		return BufferedReader::readLine();
	}
};

}

#endif
