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
<<<<<<< HEAD
*	03/03/05
*		- Changed setLeaseTime() not to use iostream for TRON.
=======
*	03/03/05
*		- Changed setLeaseTime() not to use iostream for TRON.
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
*
******************************************************************/

#ifndef _CLINK_SSDPREQUEST_H_
#define _CLINK_SSDPREQUEST_H_

<<<<<<< HEAD
#include <uhttp/http/HTTP.h>
#include <uhttp/http/HTTPRequest.h>
#include <cybergarage/upnp/ssdp/SSDP.h>

#include <uhttp/util/StringUtil.h>

namespace CyberLink {

class SSDPRequest : public uHTTP::HTTPRequest
=======
#include <cybergarage/http/HTTP.h>
#include <cybergarage/http/HTTPRequest.h>
#include <cybergarage/upnp/ssdp/SSDP.h>

#include <cybergarage/util/StringUtil.h>

namespace CyberLink {

class SSDPRequest : public CyberHTTP::HTTPRequest
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SSDPRequest()
	{
<<<<<<< HEAD
		setVersion(uHTTP::HTTP::VER_11);
=======
		setVersion(CyberHTTP::HTTP::VER_11);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	////////////////////////////////////////////////
	//	NT
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setNT(const std::string &value)
	{
		setHeader(uHTTP::HTTP::NT, value);
=======
	void setNT(const char *value)
	{
		setHeader(CyberHTTP::HTTP::NT, value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getNT()
	{
<<<<<<< HEAD
		return getHeaderValue(uHTTP::HTTP::NT);
=======
		return getHeaderValue(CyberHTTP::HTTP::NT);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	////////////////////////////////////////////////
	//	NTS
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setNTS(const std::string &value)
	{
		setHeader(uHTTP::HTTP::NTS, value);
=======
	void setNTS(const char *value)
	{
		setHeader(CyberHTTP::HTTP::NTS, value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getNTS()
	{
<<<<<<< HEAD
		return getHeaderValue(uHTTP::HTTP::NTS);
=======
		return getHeaderValue(CyberHTTP::HTTP::NTS);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	////////////////////////////////////////////////
	//	Location
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setLocation(const std::string &value)
	{
		setHeader(uHTTP::HTTP::LOCATION, value);
=======
	void setLocation(const char *value)
	{
		setHeader(CyberHTTP::HTTP::LOCATION, value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getLocation()
	{
<<<<<<< HEAD
		return getHeaderValue(uHTTP::HTTP::LOCATION);
=======
		return getHeaderValue(CyberHTTP::HTTP::LOCATION);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	////////////////////////////////////////////////
	//	USN
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setUSN(const std::string &value)
	{
		setHeader(uHTTP::HTTP::USN, value);
=======
	void setUSN(const char *value)
	{
		setHeader(CyberHTTP::HTTP::USN, value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getUSN()
	{
<<<<<<< HEAD
		return getHeaderValue(uHTTP::HTTP::USN);
=======
		return getHeaderValue(CyberHTTP::HTTP::USN);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	////////////////////////////////////////////////
	//	CacheControl
	////////////////////////////////////////////////

	void setLeaseTime(int value)
<<<<<<< HEAD
	{
		std::string leaseTime;
		std::string buf;
		leaseTime = "max-age=";
		leaseTime += uHTTP::Integer2String(value, buf);
		setHeader(uHTTP::HTTP::CACHE_CONTROL,  leaseTime.c_str());
=======
	{
		std::string leaseTime;
		std::string buf;
		leaseTime = "max-age=";
		leaseTime += CyberUtil::Integer2String(value, buf);
		setHeader(CyberHTTP::HTTP::CACHE_CONTROL,  leaseTime.c_str());
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	int getLeaseTime()
	{
<<<<<<< HEAD
		const char *cacheCtrl = getHeaderValue(uHTTP::HTTP::CACHE_CONTROL);
=======
		const char *cacheCtrl = getHeaderValue(CyberHTTP::HTTP::CACHE_CONTROL);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		return SSDP::GetLeaseTime(cacheCtrl);
	}
};

}

#endif

