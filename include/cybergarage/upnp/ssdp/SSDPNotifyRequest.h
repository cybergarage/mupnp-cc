<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPNotifyRequest.h
*
*	Revision;
*
*	07/10/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPNOTIFYREQUEST_H_
#define _CLINK_SSDPNOTIFYREQUEST_H_

#include <sstream>

#include <cybergarage/upnp/ssdp/SSDPRequest.h>

namespace CyberLink {

class SSDPNotifyRequest : public  SSDPRequest
{
public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SSDPNotifyRequest()
	{
		setMethod(uHTTP::HTTP::NOTIFY);
		setURI("*");
	}
};

}

#endif

=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPNotifyRequest.h
*
*	Revision;
*
*	07/10/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPNOTIFYREQUEST_H_
#define _CLINK_SSDPNOTIFYREQUEST_H_

#include <sstream>

#include <cybergarage/upnp/ssdp/SSDPRequest.h>

namespace CyberLink {

class SSDPNotifyRequest : public  SSDPRequest
{
public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SSDPNotifyRequest()
	{
		setMethod(CyberHTTP::HTTP::NOTIFY);
		setURI("*");
	}
};

}

#endif

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
