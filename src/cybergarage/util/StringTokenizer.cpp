/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: StringTokenizer.cpp
*
*	Revision;
*
*	04/02/03
*		- first revision
*	07/13/03
*		- Changed to implement no using strtok().
*
******************************************************************/

#include <cybergarage/util/StringTokenizer.h>

#include <string.h>

using namespace std;
using namespace CyberUtil;

StringTokenizer::StringTokenizer(const char *str, const char *delim)
{
	if (str == NULL) {
		hasNextTokens = false;
		lastDelimPos = 0;
		strNextToken = "";
		strBuf = "";
		return;
	}

	hasNextTokens = true;
	strBuf = str;
	strDelim = delim;
	lastDelimPos = string::npos;

	nextToken(delim);
}

StringTokenizer::~StringTokenizer()
{
}

bool StringTokenizer::hasMoreTokens()
{
	return hasNextTokens;
}

const char *StringTokenizer::nextToken()
{
	return nextToken(strDelim.c_str());
}

const char *StringTokenizer::nextToken(const char *delim)
{
	strCurrToken = strNextToken;

	string::size_type findStartDelimPos = (lastDelimPos == string::npos) ? 0 : (lastDelimPos+1);
	string::size_type startDelimPos = strBuf.find_first_not_of(delim, findStartDelimPos);
	if (startDelimPos == string::npos) {
		hasNextTokens = false;
		strNextToken = "";
		return strCurrToken.c_str();
	}

	string::size_type endDelimPos = strBuf.find_first_of(delim, startDelimPos);
	if (endDelimPos == string::npos)
		endDelimPos = strBuf.length();
	strNextToken = strBuf.substr(startDelimPos, endDelimPos-startDelimPos);

	lastDelimPos = endDelimPos;

	return strCurrToken.c_str();
}
