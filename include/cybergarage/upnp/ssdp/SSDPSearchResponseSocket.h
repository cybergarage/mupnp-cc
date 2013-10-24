<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPSearchResponseSocket.h
*
*	Revision;
*
*	07/11/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPSEARCHRESPONSESYSOCKET_H_
#define _CLINK_SSDPSEARCHRESPONSESYSOCKET_H_

#include <uhttp/util/Thread.h>
#include <cybergarage/upnp/ssdp/HTTPUSocket.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponse.h>
#include <cybergarage/upnp/ssdp/SSDPSearchRequest.h>

namespace CyberLink {

class ControlPoint;

class SSDPSearchResponseSocket : public HTTPUSocket, public uHTTP::Thread
{
	ControlPoint *controlPoint;

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	SSDPSearchResponseSocket();
	SSDPSearchResponseSocket(const std::string &bindAddr, int port);
	~SSDPSearchResponseSocket();

	////////////////////////////////////////////////
	//	ControlPoint	
	////////////////////////////////////////////////
	
	void setControlPoint(ControlPoint *ctrlp)
	{
		controlPoint = ctrlp;
	}

	ControlPoint *getControlPoint()
	{
		return controlPoint;
	}

	////////////////////////////////////////////////
	//	run	
	////////////////////////////////////////////////

	void run();
	
=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPSearchResponseSocket.h
*
*	Revision;
*
*	07/11/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPSEARCHRESPONSESYSOCKET_H_
#define _CLINK_SSDPSEARCHRESPONSESYSOCKET_H_

#include <cybergarage/util/Thread.h>
#include <cybergarage/upnp/ssdp/HTTPUSocket.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponse.h>
#include <cybergarage/upnp/ssdp/SSDPSearchRequest.h>

namespace CyberLink {

class ControlPoint;

class SSDPSearchResponseSocket : public HTTPUSocket, public CyberUtil::Thread
{
	ControlPoint *controlPoint;

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	SSDPSearchResponseSocket();
	SSDPSearchResponseSocket(const char *bindAddr, int port);
	~SSDPSearchResponseSocket();

	////////////////////////////////////////////////
	//	ControlPoint	
	////////////////////////////////////////////////
	
	void setControlPoint(ControlPoint *ctrlp)
	{
		controlPoint = ctrlp;
	}

	ControlPoint *getControlPoint()
	{
		return controlPoint;
	}

	////////////////////////////////////////////////
	//	run	
	////////////////////////////////////////////////

	void run();
	
	////////////////////////////////////////////////
	//	post
	////////////////////////////////////////////////

	bool post(const char *addr, int port, SSDPSearchResponse *res)
	{
		std::string headerStr;
		return HTTPUSocket::post(addr, port, res->getHeader(headerStr));
	}

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	////////////////////////////////////////////////
	//	post
	////////////////////////////////////////////////

<<<<<<< HEAD
	bool post(const std::string &addr, int port, SSDPSearchResponse *res)
	{
		std::string headerStr;
		return HTTPUSocket::post(addr, port, res->getHeader(headerStr));
	}

	////////////////////////////////////////////////
	//	post
	////////////////////////////////////////////////

	bool post(const std::string &addr, int port, SSDPSearchRequest *req)
	{
		std::string buf;
		return HTTPUSocket::post(addr, port, req->toString(buf));
	}
};

}

#endif


=======
	bool post(const char *addr, int port, SSDPSearchRequest *req)
	{
		std::string buf;
		return HTTPUSocket::post(addr, port, req->toString(buf));
	}
};

}

#endif


>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
