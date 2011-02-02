/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: StringTokenizer.h
*
*	Revision;
*
*	04/02/03
*		- first revision
*
******************************************************************/

#ifndef _CUTIL_STRINGTOKENIZER_H_
#define _CUTIL_STRINGTOKENIZER_H_

#include <string>

namespace CyberUtil {

class StringTokenizer
{
	std::string strBuf;
	std::string strDelim;
	std::string strCurrToken;
	std::string strNextToken;
	std::string::size_type lastDelimPos;
	bool hasNextTokens;

public:

	StringTokenizer(const char *str, const char *delim);
	~StringTokenizer();

	bool hasMoreTokens();

	const char *nextToken();
	const char *nextToken(const char *delim);
};

}

#endif
