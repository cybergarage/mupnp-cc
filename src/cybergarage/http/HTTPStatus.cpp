/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPStatus.java
*
*	Revision;
*
*	03/23/03
*		- first revision.
*	10/20/04 
*		- Brent Hills <bhills@openshores.com>
*		- Added PARTIAL_CONTENT and INVALID_RANGE;
*	10/22/04
*		- Added isSuccessful().
*	10/29/04
*		- Fixed set() to set the verion and the response code when the mothod is null.
*		- Fixed set() to read multi words of the response sring such as Not Found.
*	
******************************************************************/

#include <stdlib.h>

#include <cybergarage/http/HTTP.h>
#include <cybergarage/http/HTTPStatus.h>
#include <cybergarage/util/StringTokenizer.h>
#include <cybergarage/util/StringUtil.h>

using namespace CyberHTTP;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

HTTPStatus::HTTPStatus()
{
	setVersion("");
	setStatusCode(0);
	setReasonPhrase("");
}
	
HTTPStatus::HTTPStatus(const char *ver, int code, const char *reason)
{
	setVersion(ver);
	setStatusCode(code);
	setReasonPhrase(reason);
}

HTTPStatus::HTTPStatus(const char *lineStr)
{
	set(lineStr);
}

////////////////////////////////////////////////
//	set
////////////////////////////////////////////////

void HTTPStatus::set(const char *lineStr)
{
		if (StringHasData(lineStr) == false) {
			setVersion(HTTP::VER);
			setStatusCode(HTTP::INTERNAL_SERVER_ERROR);
			setReasonPhrase(HTTP::StatusCode2String(HTTP::INTERNAL_SERVER_ERROR));
			return;
		}

		StringTokenizer st(lineStr, HTTP::STATUS_LINE_DELIM);
		std::string trimBuf;
		
		if (st.hasMoreTokens() == false)
			return;
		std::string ver = st.nextToken();
		setVersion(StringTrim(ver.c_str(), trimBuf));

		if (st.hasMoreTokens() == false)
			return;
		std::string codeStr = st.nextToken();
		int code = atoi(codeStr.c_str());
		setStatusCode(code);

		std::string reason = "";
		while (st.hasMoreTokens() == true) {
			if (0 <= reason.length())
				reason.append(" ");
			reason.append(st.nextToken());
		}
		setReasonPhrase(StringTrim(reason.c_str(), trimBuf));
}

////////////////////////////////////////////////
//	Status
////////////////////////////////////////////////
	
bool HTTPStatus::isSuccessful(int statCode)
{
	if (200 <= statCode && statCode < 300)
		return true;
	return false;
}

////////////////////////////////////////////////
//	StatusCode2String
////////////////////////////////////////////////
	
const char *CyberHTTP::HTTP::StatusCode2String(int code)
{
	switch (code) {
	case HTTP::CONTINUE: return "Continue";
	case HTTP::OK_REQUEST: return "OK";
	case HTTP::PARTIAL_CONTENT: return "Partial Content";
	case HTTP::BAD_REQUEST: return "Bad Request";
	case HTTP::NOT_FOUND: return "Not Found";
	case HTTP::PRECONDITION_FAILED: return "Precondition Failed";
	case HTTP::INVALID_RANGE: return "Invalid Range";
	case HTTP::INTERNAL_SERVER_ERROR: return "Internal Server Error";
	}
	 return "";
}

