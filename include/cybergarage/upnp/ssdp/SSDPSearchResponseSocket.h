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

	////////////////////////////////////////////////
	//	post
	////////////////////////////////////////////////

	bool post(const char *addr, int port, SSDPSearchRequest *req)
	{
		std::string buf;
		return HTTPUSocket::post(addr, port, req->toString(buf));
	}
};

}

#endif


