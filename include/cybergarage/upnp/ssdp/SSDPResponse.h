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

<<<<<<< HEAD
#include <uhttp/http/HTTPResponse.h>
#include <uhttp/http/HTTP.h>
=======
#include <cybergarage/http/HTTPResponse.h>
#include <cybergarage/http/HTTP.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#include <cybergarage/upnp/ssdp/SSDP.h>

namespace CyberLink {

<<<<<<< HEAD
class SSDPResponse : public uHTTP::HTTPResponse
=======
class SSDPResponse : public CyberHTTP::HTTPResponse
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SSDPResponse()
	{
<<<<<<< HEAD
		setVersion(uHTTP::HTTP::VER_11);
=======
		setVersion(CyberHTTP::HTTP::VER_11);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	////////////////////////////////////////////////
	//	ST (SearchTarget)
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setST(const std::string &value)
	{
		setHeader(uHTTP::HTTP::ST, value);
=======
	void setST(const char *value)
	{
		setHeader(CyberHTTP::HTTP::ST, value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getST()
	{
<<<<<<< HEAD
		return getHeaderValue(uHTTP::HTTP::ST);
=======
		return getHeaderValue(CyberHTTP::HTTP::ST);
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
	//	MYNAME
	////////////////////////////////////////////////
	
<<<<<<< HEAD
	void setMYNAME(const std::string &value)
	{
		setHeader(uHTTP::HTTP::MYNAME, value);
=======
	void setMYNAME(const char *value)
	{
		setHeader(CyberHTTP::HTTP::MYNAME, value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getMYNAME()
	{
<<<<<<< HEAD
		return getHeaderValue(uHTTP::HTTP::MYNAME);
=======
		return getHeaderValue(CyberHTTP::HTTP::MYNAME);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
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

