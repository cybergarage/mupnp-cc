<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: DeviceList.cpp
*
*	Revision;
*
*	08/13/03
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/DeviceList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

const char *DeviceList::ELEM_NAME = "deviceList";

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void DeviceList::clear() 
{
	int nDev = size();
	for (int n=0; n<nDev; n++) {
		Device *dev = getDevice(n);
		delete dev;
	}
	Vector::clear();
}
=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: DeviceList.cpp
*
*	Revision;
*
*	08/13/03
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/DeviceList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

const char *DeviceList::ELEM_NAME = "deviceList";

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void DeviceList::clear() 
{
	int nDev = size();
	for (int n=0; n<nDev; n++) {
		Device *dev = getDevice(n);
		delete dev;
	}
	Vector::clear();
}
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
