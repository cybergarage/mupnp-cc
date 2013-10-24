<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Disposer.cpp
*
*	Revision;
*
*	01/06/04
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/upnp/device/Disposer.h>
#include <uhttp/util/TimeUtil.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Thread
////////////////////////////////////////////////
	
void Disposer::run() 
{
	ControlPoint *ctrlp = getControlPoint();
	long monitorInterval = ctrlp->getExpiredDeviceMonitoringInterval() * 1000;
	
	while (isRunnable() == true) {
		uHTTP::Wait(monitorInterval);
		ctrlp->removeExpiredDevices();
		//ctrlp->print();
	}
}

=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Disposer.cpp
*
*	Revision;
*
*	01/06/04
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/upnp/device/Disposer.h>
#include <cybergarage/util/TimeUtil.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Thread
////////////////////////////////////////////////
	
void Disposer::run() 
{
	ControlPoint *ctrlp = getControlPoint();
	long monitorInterval = ctrlp->getExpiredDeviceMonitoringInterval() * 1000;
	
	while (isRunnable() == true) {
		CyberUtil::Wait(monitorInterval);
		ctrlp->removeExpiredDevices();
		//ctrlp->print();
	}
}

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
