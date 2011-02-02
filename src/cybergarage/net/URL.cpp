/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: URL.cpp
*
*	Revision;
*
*	03/18/03
*		- first revision
*	12/16/04
*		- Added support not to use ostringstream
*	03/09/05
*		- Changed to URLGetAbsoluteURL() not to use ostringstream
*	03/16/05
*		- Changed to GetHostURL() not to use ostringstream
*	06/21/05
*		- Add a constructor with no parameters.
*
******************************************************************/

#include <cybergarage/net/HostInterface.h>
#include <cybergarage/net/URL.h>
#include <cybergarage/util/StringUtil.h>

#include <sstream>

using namespace std;
using namespace CyberUtil;
using namespace CyberNet;

static const char HTTP_URI[] = "http://";

////////////////////////////////////////////////
//	URL::URL
////////////////////////////////////////////////

URL::URL() : URI()
{
}

////////////////////////////////////////////////
//	URL::URL
////////////////////////////////////////////////

URL::URL(const char *urlStr) : URI(urlStr)
{
	if (port == URI_KNKOWN_PORT) {
		if (StringStartsWith(getProtocol(), HTTP_URI) == true)
			port = 80;
	}
}

////////////////////////////////////////////////
//	IsAbsoluteURL
////////////////////////////////////////////////

bool CyberNet::IsAbsoluteURL(const char *urlStr)
{
	if (StringStartsWith(urlStr, HTTP_URI) == true)
		return true;
	return false;
}

////////////////////////////////////////////////
//	URLGetHost
////////////////////////////////////////////////

const char *CyberNet::URLGetHost(const char *urlStr, std::string &buf)
{
	URL url(urlStr);
	buf = url.getHost();
	return buf.c_str();
}

////////////////////////////////////////////////
//	URLGetPort
////////////////////////////////////////////////

int CyberNet::URLGetPort(const char *urlStr)
{
		URL url(urlStr);
		return url.getPort();
}

////////////////////////////////////////////////
//	URLGetRelativeURL
////////////////////////////////////////////////

const char *CyberNet::URLGetRelativeURL(const char *uri, std::string &buf, bool withParam)
{
	buf = uri;
	CyberUtil::String urlStr = uri;
	if (IsAbsoluteURL(uri) == false) {
		if (0 < urlStr.length() && urlStr.charAt(0) != '/') {
			buf = "/";
			buf += uri;
		}
	}
	else {
			URL url(uri);
			buf = url.getPath();
			if (withParam == true) {
				String queryStr = url.getQuery();
				if (!queryStr.equals("")){
					buf += "?";
					buf += queryStr.getValue();
				}
			}
			if (urlStr.endsWith("/")) {
				String substrBuf;
				buf = urlStr.substring(0,urlStr.length()-1, substrBuf);
			}
	}
	return buf.c_str();
}

////////////////////////////////////////////////
//	URLGetAbsoluteURL
////////////////////////////////////////////////

const char *CyberNet::URLGetAbsoluteURL(const char *baseURLStr, const char *relURlStr, std::string &buf)
{
	URL baseURL(baseURLStr);
	string relURlStrBuf;
	string portStrBuf;
	buf = "";
	buf += baseURL.getProtocol();
	buf += URI::PROTOCOL_DELIM;
	buf += baseURL.getHost();
	buf += URI::COLON_DELIM;
	buf += Integer2String(baseURL.getPort(), portStrBuf);
	buf += URLGetRelativeURL(relURlStr, relURlStrBuf);
	return buf.c_str();
}

////////////////////////////////////////////////
//	GetHostURL
////////////////////////////////////////////////

const char *CyberNet::GetHostURL(const char *host, int port, const char *uri, std::string &buf)
{
	std::string hostStr = host;
	if (IsIPv6Address(host) == true) {
		StripIPv6ScopeID(host, hostStr);
		hostStr = "[";
		hostStr += hostStr.c_str();
		hostStr += "]";
	}
	string portStr;
	buf = "http://";
	buf += hostStr;
	buf += ":";
	buf += Integer2String(port, portStr);
	buf += uri;
	return buf.c_str();
}
