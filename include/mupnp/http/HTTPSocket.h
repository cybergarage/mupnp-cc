/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPSocket.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_HTTPSOCKET_H_
#define _CHTTP_HTTPSOCKET_H_

#include <cybergarage/net/Socket.h>
#include <cybergarage/io/InputStream.h>

namespace CyberHTTP {

class HTTPResponse;

class HTTPSocket
{

	CyberNet::Socket *socket;
	
public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	HTTPSocket(CyberNet::Socket *socket);
	HTTPSocket(HTTPSocket *socket);
	~HTTPSocket();
	
	////////////////////////////////////////////////
	//	Socket
	////////////////////////////////////////////////

	void setSocket(CyberNet::Socket *socket)
	{
		this->socket = socket;
	}

	CyberNet::Socket *getSocket()
	{
		return socket;
	}

	////////////////////////////////////////////////
	//	local address/port
	////////////////////////////////////////////////
	
public:

	const char *getLocalAddress()
	{
		return getSocket()->getLocalAddress();	
	}

	int getLocalPort()
	{
		return getSocket()->getLocalPort();	
	}

	////////////////////////////////////////////////
	//	open/close
	////////////////////////////////////////////////

public:

	bool open();
	bool close();
	
	////////////////////////////////////////////////
	//	post
	////////////////////////////////////////////////

private:

	bool post(HTTPResponse *httpRes, const char *content, int contentOffset, int contentLength, bool isOnlyHeader, bool isChunked);
	bool post(HTTPResponse *httpRes, CyberIO::InputStream *in, long contentOffset, long contentLength, bool isOnlyHeader, bool isChunked);

public:

	bool post(HTTPResponse *httpRes, int contentOffset, int contentLength, bool isOnlyHeader, bool isChunked);

};

}

#endif

