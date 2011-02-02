/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SubscriptionRequest.h
*
*	Revision;
*
*	08/16/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SUBSCRIPTIONREQUEST_H_
#define _CLINK_SUBSCRIPTIONREQUEST_H_

#include <cybergarage/http/HTTPRequest.h>
#include <cybergarage/http/HTTP.h>
#include <cybergarage/upnp/event/Subscription.h>
#include <cybergarage/upnp/device/NT.h>
#include <cybergarage/upnp/event/SubscriptionRequest.h>
#include <cybergarage/upnp/event/SubscriptionResponse.h>

#include <string>

namespace CyberLink {

class Service;

class SubscriptionRequest : public CyberHTTP::HTTPRequest
{
	SubscriptionResponse subRes;

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	SubscriptionRequest()
	{
	}

	SubscriptionRequest(CyberHTTP::HTTPRequest *httpReq)
	{
		set(httpReq);
	}
	
	////////////////////////////////////////////////
	//	setRequest
	////////////////////////////////////////////////

private:

	void setService(Service *service);

public:

	void setSubscribeRequest(Service *service, const char *callback, long timeout);
	void setRenewRequest(Service *service, const char *uuid, long timeout);
	void setUnsubscribeRequest(Service *service);

	////////////////////////////////////////////////
	//	NT
	////////////////////////////////////////////////

public:

	void setNT(const char *value)
	{
		setHeader(CyberHTTP::HTTP::NT, value);
	}

	const char *getNT()
	{
		return getHeaderValue(CyberHTTP::HTTP::NT);
	}
	
	////////////////////////////////////////////////
	//	CALLBACK
	////////////////////////////////////////////////

private:

	static const char CALLBACK_START_WITH;
	static const char CALLBACK_END_WITH;

public:

	void setCallback(const char *value)
	{
		setStringHeader(CyberHTTP::HTTP::CALBACK, value, CALLBACK_START_WITH, CALLBACK_END_WITH);
	}
	
	const char *getCallback(std::string &buf)
	{
		return getStringHeaderValue(CyberHTTP::HTTP::CALBACK, CALLBACK_START_WITH, CALLBACK_END_WITH, buf);
	}

	bool hasCallback()
	{
		std::string callback;
		getCallback(callback);
		return (0 < callback.length()) ? true : false;
	}

	////////////////////////////////////////////////
	//	SID
	////////////////////////////////////////////////

public:

	void setSID(const char *sid)
	{
		std::string buf;
		setHeader(CyberHTTP::HTTP::SID, Subscription::toSIDHeaderString(sid, buf));
	}

	const char *getSID(std::string &buf)
	{
		return Subscription::GetSID(getHeaderValue(CyberHTTP::HTTP::SID), buf);
	}
	
	bool hasSID()
	{
		std::string sid;
		getSID(sid);
		return (0 < sid.length()) ? true : false;
	}

	////////////////////////////////////////////////
	//	Timeout
	////////////////////////////////////////////////

public:

	void setTimeout(long value)
	{
		std::string buf;
		setHeader(CyberHTTP::HTTP::TIMEOUT, Subscription::toTimeoutHeaderString(value, buf));
	}

	long getTimeout()
	{
		return Subscription::GetTimeout(getHeaderValue(CyberHTTP::HTTP::TIMEOUT));
	}

	////////////////////////////////////////////////
	//	post (Response)
	////////////////////////////////////////////////

public:

	void post(SubscriptionResponse *subRes)
	{
		HTTPRequest::post(subRes);
	}

	////////////////////////////////////////////////
	//	post
	////////////////////////////////////////////////

public:

	SubscriptionResponse *post()
	{
		CyberHTTP::HTTPResponse *httpRes = HTTPRequest::post(getRequestHost(), getRequestPort());
		subRes.set(httpRes);
		return &subRes;
	}
};

}

#endif

