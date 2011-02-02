/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPRequest.h
*
*	Revision;
*
*	07/10/03
*		- first revision
*	03/16/04
*		- Thanks for Darrell Young
*		- Fixed to set v1.1 to the HTTP version.;
*	03/03/05
*		- Changed setLeaseTime() not to use iostream for TRON.
*
******************************************************************/

#ifndef _CLINK_SSDPREQUEST_H_
#define _CLINK_SSDPREQUEST_H_

#include <cybergarage/http/HTTP.h>
#include <cybergarage/http/HTTPRequest.h>
#include <cybergarage/upnp/ssdp/SSDP.h>

#include <cybergarage/util/StringUtil.h>

namespace CyberLink {

class SSDPRequest : public CyberHTTP::HTTPRequest
{

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SSDPRequest()
	{
		setVersion(CyberHTTP::HTTP::VER_11);
	}

	////////////////////////////////////////////////
	//	NT
	////////////////////////////////////////////////

	void setNT(const char *value)
	{
		setHeader(CyberHTTP::HTTP::NT, value);
	}

	const char *getNT()
	{
		return getHeaderValue(CyberHTTP::HTTP::NT);
	}

	////////////////////////////////////////////////
	//	NTS
	////////////////////////////////////////////////

	void setNTS(const char *value)
	{
		setHeader(CyberHTTP::HTTP::NTS, value);
	}

	const char *getNTS()
	{
		return getHeaderValue(CyberHTTP::HTTP::NTS);
	}

	////////////////////////////////////////////////
	//	Location
	////////////////////////////////////////////////

	void setLocation(const char *value)
	{
		setHeader(CyberHTTP::HTTP::LOCATION, value);
	}

	const char *getLocation()
	{
		return getHeaderValue(CyberHTTP::HTTP::LOCATION);
	}

	////////////////////////////////////////////////
	//	USN
	////////////////////////////////////////////////

	void setUSN(const char *value)
	{
		setHeader(CyberHTTP::HTTP::USN, value);
	}

	const char *getUSN()
	{
		return getHeaderValue(CyberHTTP::HTTP::USN);
	}

	////////////////////////////////////////////////
	//	CacheControl
	////////////////////////////////////////////////

	void setLeaseTime(int value)
	{
		std::string leaseTime;
		std::string buf;
		leaseTime = "max-age=";
		leaseTime += CyberUtil::Integer2String(value, buf);
		setHeader(CyberHTTP::HTTP::CACHE_CONTROL,  leaseTime.c_str());
	}

	int getLeaseTime()
	{
		const char *cacheCtrl = getHeaderValue(CyberHTTP::HTTP::CACHE_CONTROL);
		return SSDP::GetLeaseTime(cacheCtrl);
	}
};

}

#endif

