/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: RenewSubscriber.cpp
*
*	Revision:
*
*	07/07/04
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/util/TimeUtil.h>

using namespace CyberLink;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

const long RenewSubscriber::INTERVAL= 120;

////////////////////////////////////////////////
//	Thread
////////////////////////////////////////////////
	
void RenewSubscriber::run() 
{
	ControlPoint *ctrlp = getControlPoint();
	long renewInterval = RenewSubscriber::INTERVAL * 1000;
	while (isRunnable() == true) {
		Wait(renewInterval);
		ctrlp->renewSubscriberService();
	}
}

