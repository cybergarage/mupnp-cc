/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTP.cpp
*
*	Revision;
*
*	03/22/03
*		- first revision
*	05/26/04
*		- Added NO_CATCH and MAX_AGE.
*	10/20/04 
*		- Brent Hills <bhills@openshores.com>
*		- Added Range and MYNAME;
*	12/21/04
*		- Added support not to ostringstream.
*
******************************************************************/

#include <sstream>
#include <cybergarage/http/HTTP.h>
#include <cybergarage/net/URI.h>

#ifdef NO_USE_OSTRINGSTREAM
#include <cybergarage/util/StringUtil.h>
#endif

using namespace std;
using namespace CyberNet;
#ifdef NO_USE_OSTRINGSTREAM
using namespace CyberUtil;
#endif

int CyberHTTP::HTTP::GetPort(const char *urlStr)
{
	int port = CyberNet::URLGetPort(urlStr);
	if (port <= 0)
		port = HTTP::DEFAULT_PORT;
		return port;
}

const char *CyberHTTP::HTTP::GetAbsoluteURL(const char *baseURLStr, const char *relURlStr, std::string &buf)
{
	CyberNet::URL baseURL(baseURLStr);
	int port = baseURL.getPort();
	if (port <= 0)
		port = HTTP::DEFAULT_PORT;
	string relURlStrBuf;
#ifndef NO_USE_OSTRINGSTREAM
	ostringstream url;
	url << 
		baseURL.getProtocol() << URI::PROTOCOL_DELIM <<
		baseURL.getHost() << URI::COLON_DELIM <<
		port <<
		HTTP::GetRelativeURL(relURlStr, relURlStrBuf);
	buf = url.str();
#else
	string ibuf;
	buf = "";
	buf += baseURL.getProtocol();
	buf += URI::PROTOCOL_DELIM;
	buf += baseURL.getHost();
	buf += URI::COLON_DELIM;
	buf += Integer2String(port, ibuf);
	buf += HTTP::GetRelativeURL(relURlStr, relURlStrBuf);
#endif
	return buf.c_str();
}

const char *CyberHTTP::HTTP::GetRequestHostURL(const char *host, int port, std::string &buf)
{
#ifndef NO_USE_OSTRINGSTREAM
	std::ostringstream url;
	url << "http://" << host << ":" << port;
	buf = url.str();
#else
	string ibuf;
	buf = "";
	buf +="http://";
	buf += host;
	buf += ":";
	buf += Integer2String(port, ibuf);
#endif
	return buf.c_str();
}

////////////////////////////////////////////////
// Chunk Size
////////////////////////////////////////////////
	
static int httpChunkSize = CyberHTTP::HTTP::DEFAULT_CHUNK_SIZE;

void CyberHTTP::HTTP::SetChunkSize(int size)
{
	httpChunkSize = size;
}
	
int CyberHTTP::HTTP::GetChunkSize()
{
	return httpChunkSize;
}
