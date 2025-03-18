/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: URI.h
*
*	Revision;
*
*	04/07/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_URI_H_
#define _CNET_URI_H_

#include <string>

namespace CyberNet {

const int URI_KNKOWN_PORT = -1;

class URI {

protected:

	std::string uriStr;
	std::string protocol;
	std::string user;
	std::string password;
	std::string host;
	int port;
	std::string path;
	std::string query;
	std::string fragment;

public:

	static const char *PROTOCOL_DELIM;
	static const char *USER_DELIM;
	static const char *COLON_DELIM;
	static const char *SLASH_DELIM;
	static const char *SBLACET_DELIM;
	static const char *EBLACET_DELIM;
	static const char *SHARP_DELIM;
	static const char *QUESTION_DELIM;
	
public:

	URI();
	URI(const char *uriStr);

	bool IsAbsoluteURI();

	void setString(const char *uriStr);

	const char *getSting()
	{
		return uriStr.c_str();
	}

	const char *getProtocol()
	{
		return protocol.c_str();
	}

	const char *getUser()
	{
		return user.c_str();
	}

	const char *getPassword()
	{
		return password.c_str();
	}

	const char *getHost()
	{
		return host.c_str();
	}

	int getPort()
	{
		return port;
	}

	const char *getPath()
	{
		return path.c_str();
	}

	const char *getQuery()
	{
		return query.c_str();
	}

	const char *getFragment()
	{
		return fragment.c_str();
	}

	void print();
};

}

#endif
