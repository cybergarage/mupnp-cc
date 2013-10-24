/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Subscriber.h
*
*	Revision:
*
*	08/02/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SUBSCRIBER_H_
#define _CLINK_SUBSCRIBER_H_

#include <time.h>
#include <string>
#include <limits.h>
<<<<<<< HEAD
#include <uhttp/net/URL.h>
=======
#include <cybergarage/net/URL.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

namespace CyberLink {

class Subscriber
{
	std::string SID;
	std::string ifAddr;
	
<<<<<<< HEAD
	uHTTP::URL deliveryURL;
=======
	CyberNet::URL deliveryURL;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	
	long timeOut;
	long notifyCount;
	long subscriptionTime;

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	Subscriber();
	~Subscriber();

	////////////////////////////////////////////////
	//	SID
	////////////////////////////////////////////////

	const char *getSID() {
		return SID.c_str();
	}

<<<<<<< HEAD
	void setSID(const std::string &sid) {
=======
	void setSID(const char *sid) {
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		SID = sid;
	}

	////////////////////////////////////////////////
	//	deliveryURL
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setInterfaceAddress(const std::string &addr)
=======
	void setInterfaceAddress(const char *addr)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		ifAddr = addr;
	}
	
	const char *getInterfaceAddress()
	{
		return ifAddr.c_str();
	}
	
	////////////////////////////////////////////////
	//	deliveryURL
	////////////////////////////////////////////////

	const char *getDeliveryURL() {
		return deliveryURL.getSting();
	}

<<<<<<< HEAD
	void setDeliveryURL(const std::string &url)
=======
	void setDeliveryURL(const char *url)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		deliveryURL.setString(url);
	}

	const char *getDeliveryHost() {
		return deliveryURL.getHost();
	}

	const char *getDeliveryPath() {
		return deliveryURL.getPath();
	}

	int getDeliveryPort() {
		return deliveryURL.getPort();
	}
	
	////////////////////////////////////////////////
	//	Timeout
	////////////////////////////////////////////////

	long getTimeOut() {
		return timeOut;
	}

	void setTimeOut(long value) {
		timeOut = value;
	}

	bool isExpired();

	////////////////////////////////////////////////
	//	SubscriptionTIme
	////////////////////////////////////////////////

	long getSubscriptionTime() {
		return subscriptionTime;
	}

	void setSubscriptionTime(long time) {
		subscriptionTime = time;
	}

	////////////////////////////////////////////////
	//	SEQ
	////////////////////////////////////////////////

	long getNotifyCount() {
		return notifyCount;
	}

	void setNotifyCount(int cnt) {
		notifyCount = cnt;
	}

	void incrementNotifyCount();
	
	////////////////////////////////////////////////
	//	renew
	////////////////////////////////////////////////
	
	void renew();

};

}

#endif

