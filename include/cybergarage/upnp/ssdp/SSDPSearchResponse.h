/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPSearchRequest.h
*
*	Revision;
*
*	07/10/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPSEARCHRESPONSE_H_
#define _CLINK_SSDPSEARCHRESPONSE_H_

#include <sstream>

#include <cybergarage/upnp/UPnP.h>
#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/ssdp/SSDPResponse.h>

namespace CyberLink {

class SSDPSearchResponse : public SSDPResponse
{

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:
	
	SSDPSearchResponse()
	{
<<<<<<< HEAD
		setStatusCode(uHTTP::HTTP::OK_REQUEST);
		setCacheControl(Device::DEFAULT_LEASE_TIME);
		std::string buf;
		setHeader(uHTTP::HTTP::SERVER, UPnP::GetServerName(buf));
		setHeader(uHTTP::HTTP::EXT, "");
=======
		setStatusCode(CyberHTTP::HTTP::OK_REQUEST);
		setCacheControl(Device::DEFAULT_LEASE_TIME);
		std::string buf;
		setHeader(CyberHTTP::HTTP::SERVER, UPnP::GetServerName(buf));
		setHeader(CyberHTTP::HTTP::EXT, "");
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}
};

}

#endif
