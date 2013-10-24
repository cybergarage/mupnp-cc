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
<<<<<<< HEAD
#include <uhttp/net/HostInterface.h>
=======
#include <cybergarage/net/HostInterface.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#include <cybergarage/upnp/event/SubscriptionResponse.h>

namespace CyberLink {

class SSDPSearchRequest : public SSDPRequest
{
public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

<<<<<<< HEAD
	SSDPSearchRequest(const std::string &serachTarget, int mx)
=======
	SSDPSearchRequest(const char *serachTarget, int mx)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		init(serachTarget, mx);
	}
	
<<<<<<< HEAD
	SSDPSearchRequest(const std::string &serachTarget)
=======
	SSDPSearchRequest(const char *serachTarget)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		init(serachTarget, SSDP::DEFAULT_MSEARCH_MX);
	}
	
	SSDPSearchRequest()
	{
		init(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
	}

private:

<<<<<<< HEAD
	void init(const std::string &serachTarget, int mx)
	{
		setMethod(uHTTP::HTTP::M_SEARCH);
		setURI("*");

		setHeader(uHTTP::HTTP::ST, serachTarget);
		setHeader(uHTTP::HTTP::MX, mx);
=======
	void init(const char *serachTarget, int mx)
	{
		setMethod(CyberHTTP::HTTP::M_SEARCH);
		setURI("*");

		setHeader(CyberHTTP::HTTP::ST, serachTarget);
		setHeader(CyberHTTP::HTTP::MX, mx);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		std::string man;
		man = "\"";
		man += MAN::DISCOVER;
		man += "\"";
<<<<<<< HEAD
		setHeader(uHTTP::HTTP::MAN, man.c_str());
=======
		setHeader(CyberHTTP::HTTP::MAN, man.c_str());
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	////////////////////////////////////////////////
	//	HOST
	////////////////////////////////////////////////

public:
	
<<<<<<< HEAD
	void setLocalAddress(const std::string &bindAddr)
	{
		const char *ssdpAddr = SSDP::ADDRESS;
		if (uHTTP::IsIPv6Address(bindAddr) == true)
=======
	void setLocalAddress(const char *bindAddr)
	{
		const char *ssdpAddr = SSDP::ADDRESS;
		if (CyberNet::IsIPv6Address(bindAddr) == true)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
			ssdpAddr = SSDP::GetIPv6Address();
		setHost(ssdpAddr, SSDP::PORT);
	}

};

}

#endif
