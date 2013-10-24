/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: URI.cpp
*
*	Revision;
*
*	04/07/03
*		- first revision
*	03/26/04
*		- Jay Deen <j2deen_ca@yahoo.ca>
*		- Fixed URI::getProtocol() to retuen the name without "://".
*	12/16/04
*		- Added support not to use cout.
*	03/09/04
*		- Changed print() not to use cout and to use CG_NOUSE_STDOUT.
*	06/21/05
*		- Add a constructor with no parameters.
*
******************************************************************/

#include <cybergarage/net/URI.h>
#include <cybergarage/util/StringUtil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;
using namespace CyberUtil;
using namespace CyberNet;

const char *URI::PROTOCOL_DELIM = "://";
const char *URI::USER_DELIM = "@";
const char *URI::COLON_DELIM = ":";
const char *URI::SLASH_DELIM = "/";
const char *URI::SBLACET_DELIM = "[";
const char *URI::EBLACET_DELIM = "]";
const char *URI::SHARP_DELIM = "#";
const char *URI::QUESTION_DELIM = "?";

////////////////////////////////////////////////
//	URI::URI
////////////////////////////////////////////////

URI::URI()
{
}

URI::URI(const char *value)
{
	setString(value);
}

////////////////////////////////////////////////
// setString
////////////////////////////////////////////////

void URI::setString(const char *value)
{
	uriStr = value;

	// Protocol
	size_t idx = uriStr.find(PROTOCOL_DELIM);
	if (idx != (int)string::npos) {
		int protocolStrLen = strlen(PROTOCOL_DELIM);
		// Thanks for Jay Deen (03/26/04)
		protocol = uriStr.substr(0, idx/* + protocolStrLen*/);
		idx += protocolStrLen;
	}
	else
		idx = 0;

	// User (Password)
	int atIdx = uriStr.find(USER_DELIM, idx);
	if (atIdx != (int)string::npos) {
		string userPassStr = uriStr.substr(idx, atIdx - idx);
		int colonIdx = userPassStr.find(COLON_DELIM);
		if (colonIdx != (int)string::npos) {
			user = userPassStr.substr(0, colonIdx);
			password = userPassStr.substr(colonIdx + 1, userPassStr.length() - colonIdx -1);
		}
		else
			user = userPassStr;
		idx = atIdx + 1;
	}

	// Host (Port)
	int shashIdx = uriStr.find(SLASH_DELIM, idx);
	if (shashIdx != (int)string::npos)
		host = uriStr.substr(idx, shashIdx - idx);
	else
		host = uriStr.substr(idx, uriStr.length() - idx);
	int colonIdx = host.rfind(COLON_DELIM);
	int eblacketIdx = host.rfind(EBLACET_DELIM);
	if (colonIdx != (int)string::npos && eblacketIdx < colonIdx) {
		string hostStr = host;
		host = hostStr.substr(0, colonIdx);
		if (0 < host.length()) {
			if (host.at(0) == '[' && host.at(host.length()-1) == ']')
				host = host.substr(1, colonIdx-2);
		}
		string portStr = hostStr.substr(colonIdx + 1, hostStr.length() - colonIdx -1);
		port = atoi(portStr.c_str());
	}
	else
		port = URI_KNKOWN_PORT;
	if (shashIdx == (int)string::npos)
		return;
	idx = shashIdx/* + 1*/;

	// Path (Query/Fragment)
	path = uriStr.substr(idx, uriStr.length() - idx);
	int sharpIdx = path.find(SHARP_DELIM);
	if (sharpIdx != (int)string::npos) {
		string pathStr = path;
		path = pathStr.substr(0, sharpIdx);
		fragment = pathStr.substr(sharpIdx + 1, pathStr.length() - sharpIdx -1);
	}
	int questionIdx = path.find(QUESTION_DELIM);
	if (questionIdx != (int)string::npos) {
		string pathStr = path;
		path = pathStr.substr(0, questionIdx);
		query = pathStr.substr(questionIdx + 1, pathStr.length() - questionIdx -1);
	}
	
}

////////////////////////////////////////////////
// IsAbsoluteURI
////////////////////////////////////////////////

bool URI::IsAbsoluteURI()
{
	if (0 < protocol.length())
		return true;
	return false;
}

////////////////////////////////////////////////
// print
////////////////////////////////////////////////

void URI::print()
{
#if !defined(CG_NOUSE_STDOUT)
	printf("URI = %s\n", uriStr.c_str());
	printf("  protocol = %s\n", protocol.c_str());
	printf("  user = %s\n", user.c_str());
	printf("  password = %s\n", password.c_str());
	printf("  host = %s\n", host.c_str());
	printf("  port = %d\n", port);
	printf("  path = %s\n", path.c_str());
	printf("  query = %s\n", query.c_str());
	printf("  fragment = %s\n", fragment.c_str());
#endif
}

