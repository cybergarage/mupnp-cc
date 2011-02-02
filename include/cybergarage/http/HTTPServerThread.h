/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPServerThread.h
*
*	Revision;
*
*	10/21/03
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_HTTPSERVERTHREAD_H_
#define _CHTTP_HTTPSERVERTHREAD_H_

#include <cybergarage/util/Thread.h>
#include <cybergarage/http/HTTPServer.h>

namespace CyberHTTP {

class HTTPServerThread : public CyberUtil::Thread
{
	CyberNet::Socket *clientSock;
	CyberHTTP::HTTPServer *httpServer;

public:
	
	HTTPServerThread(CyberHTTP::HTTPServer *server, CyberNet::Socket *sock);
	~HTTPServerThread();

	////////////////////////////////////////////////
	//	run	
	////////////////////////////////////////////////

	void run();

};


}

#endif
