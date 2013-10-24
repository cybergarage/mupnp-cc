<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPNotifySocket.h
*
*	Revision;
*
*	07/11/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPNOTIFYSOCKET_H_
#define _CLINK_SSDPNOTIFYSOCKET_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/util/Thread.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/ssdp/HTTPMUSocket.h>
#include <cybergarage/upnp/ssdp/SSDPNotifyRequest.h>

namespace CyberLink {

class ControlPoint;

class SSDPNotifySocket : public HTTPMUSocket, public uHTTP::Thread
{
	ControlPoint *controlPoint;
	bool useIPv6Address;

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SSDPNotifySocket(const std::string &bindAddr);
	~SSDPNotifySocket();

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
=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPNotifySocket.h
*
*	Revision;
*
*	07/11/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPNOTIFYSOCKET_H_
#define _CLINK_SSDPNOTIFYSOCKET_H_

#include <cybergarage/net/HostInterface.h>
#include <cybergarage/util/Thread.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/ssdp/HTTPMUSocket.h>
#include <cybergarage/upnp/ssdp/SSDPNotifyRequest.h>

namespace CyberLink {

class ControlPoint;

class SSDPNotifySocket : public HTTPMUSocket, public CyberUtil::Thread
{
	ControlPoint *controlPoint;
	bool useIPv6Address;

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SSDPNotifySocket(const char *bindAddr);
	~SSDPNotifySocket();

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
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	post (SSDPNotifySocket)
	////////////////////////////////////////////////

	bool post(SSDPNotifyRequest *req);

<<<<<<< HEAD
	////////////////////////////////////////////////
	//	run	
	////////////////////////////////////////////////

	void run();
	
};

}

#endif


=======
	////////////////////////////////////////////////
	//	run	
	////////////////////////////////////////////////

	void run();
	
};

}

#endif


>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
