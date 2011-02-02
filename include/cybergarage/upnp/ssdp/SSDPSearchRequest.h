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

#ifndef _CLINK_SSDPSEARCHREQUEST_H_
#define _CLINK_SSDPSEARCHREQUEST_H_

#include <string>

#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/ssdp/SSDPRequest.h>
#include <cybergarage/upnp/device/ST.h>
#include <cybergarage/upnp/device/MAN.h>
#include <cybergarage/net/HostInterface.h>
#include <cybergarage/upnp/event/SubscriptionResponse.h>

namespace CyberLink {

class SSDPSearchRequest : public SSDPRequest
{
public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	SSDPSearchRequest(const char *serachTarget, int mx)
	{
		init(serachTarget, mx);
	}
	
	SSDPSearchRequest(const char *serachTarget)
	{
		init(serachTarget, SSDP::DEFAULT_MSEARCH_MX);
	}
	
	SSDPSearchRequest()
	{
		init(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
	}

private:

	void init(const char *serachTarget, int mx)
	{
		setMethod(CyberHTTP::HTTP::M_SEARCH);
		setURI("*");

		setHeader(CyberHTTP::HTTP::ST, serachTarget);
		setHeader(CyberHTTP::HTTP::MX, mx);
		std::string man;
		man = "\"";
		man += MAN::DISCOVER;
		man += "\"";
		setHeader(CyberHTTP::HTTP::MAN, man.c_str());
	}

	////////////////////////////////////////////////
	//	HOST
	////////////////////////////////////////////////

public:
	
	void setLocalAddress(const char *bindAddr)
	{
		const char *ssdpAddr = SSDP::ADDRESS;
		if (CyberNet::IsIPv6Address(bindAddr) == true)
			ssdpAddr = SSDP::GetIPv6Address();
		setHost(ssdpAddr, SSDP::PORT);
	}

};

}

#endif
