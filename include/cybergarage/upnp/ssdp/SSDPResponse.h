/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPResponse.h
*
*	Revision;
*
*	07/10/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPRESPONSE_H_
#define _CLINK_SSDPRESPONSE_H_

#include <cybergarage/http/HTTPResponse.h>
#include <cybergarage/http/HTTP.h>
#include <cybergarage/upnp/ssdp/SSDP.h>

namespace CyberLink {

class SSDPResponse : public CyberHTTP::HTTPResponse
{

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SSDPResponse()
	{
		setVersion(CyberHTTP::HTTP::VER_11);
	}

	////////////////////////////////////////////////
	//	ST (SearchTarget)
	////////////////////////////////////////////////

	void setST(const char *value)
	{
		setHeader(CyberHTTP::HTTP::ST, value);
	}

	const char *getST()
	{
		return getHeaderValue(CyberHTTP::HTTP::ST);
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
	//	MYNAME
	////////////////////////////////////////////////
	
	void setMYNAME(const char *value)
	{
		setHeader(CyberHTTP::HTTP::MYNAME, value);
	}

	const char *getMYNAME()
	{
		return getHeaderValue(CyberHTTP::HTTP::MYNAME);
	}

	////////////////////////////////////////////////
	//	CacheControl
	////////////////////////////////////////////////

	void setLeaseTime(int value);

	int getLeaseTime();

	////////////////////////////////////////////////
	//	getHeader
	////////////////////////////////////////////////

	const char *getHeader(std::string &headerStr);

};

}

#endif

