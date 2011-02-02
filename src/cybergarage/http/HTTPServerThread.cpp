/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPServerThread.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*	05/19/04
*		- Changed the header include order for Cygwin.
*
******************************************************************/

#include <cybergarage/net/Socket.h>
#include <cybergarage/http/HTTPServerThread.h>

#include <sstream>

using namespace CyberHTTP;
using namespace CyberNet;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////
	
HTTPServerThread::HTTPServerThread(HTTPServer *server, Socket *sock)
{
	clientSock = sock;
	httpServer = server;
}

HTTPServerThread::~HTTPServerThread()
{
}

////////////////////////////////////////////////
//	run	
////////////////////////////////////////////////

void HTTPServerThread::run()
{
	HTTPSocket httpSock(clientSock);
	if (httpSock.open() == false) {
		delete clientSock;
		delete this;
		return;
	}
	HTTPRequest httpReq;
	httpReq.setSocket(&httpSock);
	while (httpReq.read() == true) {
		httpServer->performRequestListener(&httpReq);
		if (httpReq.isKeepAlive() == false)
			break;
	}
	httpSock.close();
	delete clientSock;
	delete this;
}
