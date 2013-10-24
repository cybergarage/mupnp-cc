/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPServerList.h
*
*	Revision;
*
*	05/18/03
*		- first revision
*	05/19/04
*		- Changed the header include order for Cygwin.
*
******************************************************************/

#ifndef _CHTTP_HTTPSERVERLIST_H_
#define _CHTTP_HTTPSERVERLIST_H_

#include <cybergarage/http/HTTPServer.h>
#include <cybergarage/net/HostInterface.h>
#include <cybergarage/util/Vector.h>

namespace CyberHTTP {

class HTTPServerList : public CyberUtil::Vector 
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
public:

	HTTPServerList();
	~HTTPServerList();

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	HTTPServer *getHTTPServer(int n)
	{
		return (HTTPServer *)get(n);
	}

	void addRequestListener(HTTPRequestListener *listener);
	
	////////////////////////////////////////////////
	//	open/close
	////////////////////////////////////////////////

public:

	void close();
	bool open(int port);

	////////////////////////////////////////////////
	//	start/stop
	////////////////////////////////////////////////

public:

	void start();
	void stop();

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif
