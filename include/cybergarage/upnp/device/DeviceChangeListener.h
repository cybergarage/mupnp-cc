<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File: DeviceChangeListener.h
*
*	Revision:
*
*	10/16/04
*		- first revision
*
******************************************************************/

#ifndef _CLINK_DEVICECHANGELISTENER_H_
#define _CLINK_DEVICECHANGELISTENER_H_

namespace CyberLink {

class Device;

class DeviceChangeListener
{
public:
	virtual void deviceAdded(Device *dev) = 0;
	virtual void deviceRemoved(Device *dev) = 0;
};

}

#endif
=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File: DeviceChangeListener.h
*
*	Revision:
*
*	10/16/04
*		- first revision
*
******************************************************************/

#ifndef _CLINK_DEVICECHANGELISTENER_H_
#define _CLINK_DEVICECHANGELISTENER_H_

namespace CyberLink {

class Device;

class DeviceChangeListener
{
public:
	virtual void deviceAdded(Device *dev) = 0;
	virtual void deviceRemoved(Device *dev) = 0;
};

}

#endif
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

