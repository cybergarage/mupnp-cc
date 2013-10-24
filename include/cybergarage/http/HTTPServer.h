/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPServer.h
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_HTTPSERVER_H_
#define _CHTTP_HTTPSERVER_H_

#include <cybergarage/net/ServerSocket.h>
#include <cybergarage/util/ListenerList.h>
#include <cybergarage/http/HTTPRequest.h>
#include <cybergarage/http/HTTPRequestListener.h>
#include <cybergarage/util/Thread.h>

#include <string>

namespace CyberHTTP {

class HTTPServer : public CyberUtil::Thread
{
	CyberNet::ServerSocket *serverSock;
	CyberUtil::ListenerList httpRequestListenerList;

public:
	
	HTTPServer();
	~HTTPServer();

	////////////////////////////////////////////////
	//	ServerSocket
	////////////////////////////////////////////////

	CyberNet::ServerSocket *getServerSock()
	{
		return serverSock;
	}

	bool open(const char *addr, int port);
	bool close();
	bool accept(CyberNet::Socket *socket);
	bool isOpened();

	////////////////////////////////////////////////
	//	httpRequest
	////////////////////////////////////////////////
	 	
	void addRequestListener(HTTPRequestListener *listener)
	{
		httpRequestListenerList.add(listener);
	}		

	void removeRequestListener(HTTPRequestListener *listener)
	{
		httpRequestListenerList.remove(listener);
	}		

	void performRequestListener(HTTPRequest *httpReq)
	{
		int listenerSize = httpRequestListenerList.size();
		for (int n=0; n<listenerSize; n++) {
			HTTPRequestListener *listener = (HTTPRequestListener *)httpRequestListenerList.get(n);
			listener->httpRequestRecieved(httpReq);
		}
	}		

	////////////////////////////////////////////////
	//	run	
	////////////////////////////////////////////////

	void run();

};

const char *GetServerName(std::string &buf);

}

#endif
