/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: URL.h
*
*	Revision;
*
*	04/07/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_URL_H_
#define _CNET_URL_H_

#include <string>
#include <cybergarage/net/URI.h>

namespace CyberNet {

class URL : public URI
{
public:

	URL();
	URL(const char *urlStr);
};

bool IsAbsoluteURL(const char *urlStr);
const char *URLGetHost(const char *urlStr, std::string &buf);
int URLGetPort(const char *urlStr);
const char *URLGetRelativeURL(const char *urlStr, std::string &buf, bool withParam = true);
const char *URLGetAbsoluteURL(const char *baseURLStr, const char *relURlStr, std::string &buf);
const char *GetHostURL(const char *host, int port, const char *uri, std::string &buf);

}

#endif
