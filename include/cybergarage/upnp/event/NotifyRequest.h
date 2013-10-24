/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NotifyRequest.h
*
*	Revision;
*
*	07/08/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_NOTIFYREQUEST_H_
#define _CLINK_NOTIFYREQUEST_H_

#include <cybergarage/soap/SOAPRequest.h>
#include <cybergarage/upnp/device/NT.h>
#include <cybergarage/upnp/device/NTS.h>
#include <cybergarage/upnp/event/Property.h>
#include <cybergarage/upnp/event/Subscription.h>
#include <cybergarage/upnp/event/Subscriber.h>
#include <cybergarage/upnp/event/PropertyList.h>
<<<<<<< HEAD

#include <sstream>
=======

#include <sstream>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

namespace CyberLink {

class NotifyRequest : public CyberSOAP::SOAPRequest
{
	PropertyList propList;

public:

	static const char *XMLNS;
	static const char *PROPERTY;
	static const char *PROPERTYSET;

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
public:

	NotifyRequest()
	{
	}

<<<<<<< HEAD
	NotifyRequest(uHTTP::HTTPRequest *httpReq)
=======
	NotifyRequest(CyberHTTP::HTTPRequest *httpReq)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		set(httpReq);
	}

	////////////////////////////////////////////////
	//	NT
	////////////////////////////////////////////////

public:

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

	////////////////////////////////////////////////
	//	NTS
	////////////////////////////////////////////////

public:

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

	////////////////////////////////////////////////
	//	SID
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	void setSID(const std::string &sid)
	{
		std::string buf;
		setHeader(uHTTP::HTTP::SID, Subscription::toSIDHeaderString(sid, buf));
=======
	void setSID(const char *sid)
	{
		std::string buf;
		setHeader(CyberHTTP::HTTP::SID, Subscription::toSIDHeaderString(sid, buf));
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getSID(std::string &buf)
	{
<<<<<<< HEAD
		return Subscription::GetSID(getHeaderValue(uHTTP::HTTP::SID), buf);
=======
		return Subscription::GetSID(getHeaderValue(CyberHTTP::HTTP::SID), buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	////////////////////////////////////////////////
	//	SEQ
	////////////////////////////////////////////////

public:

	void setSEQ(long value)
	{
<<<<<<< HEAD
		setHeader(uHTTP::HTTP::SEQ, value);
=======
		setHeader(CyberHTTP::HTTP::SEQ, value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	long getSEQ()
	{
<<<<<<< HEAD
		return getLongHeaderValue(uHTTP::HTTP::SEQ);
=======
		return getLongHeaderValue(CyberHTTP::HTTP::SEQ);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	////////////////////////////////////////////////
	//	Request
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	bool setRequest(Subscriber *sub, const std::string &varName, const std::string &value);

private:
	
	CyberXML::Node *createPropertySetNode(const std::string &varName, const std::string &value);
=======
	bool setRequest(Subscriber *sub, const char *varName, const char *value);

private:
	
	CyberXML::Node *createPropertySetNode(const char *varName, const char *value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	CyberXML::Node *getVariableNode();

	////////////////////////////////////////////////
	//	Property
	////////////////////////////////////////////////

private:
	
	Property *getProperty(CyberXML::Node *varNode);

public:

	PropertyList *getPropertyList();
	
};

}

#endif

