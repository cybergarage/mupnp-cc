<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: DeviceList.h
*
*	Revision;
*
*	07/20/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_DEVICELIST_H_
#define _CLINK_DEVICELIST_H_

#include <uhttp/util/Vector.h>

namespace CyberLink {

class Device;

class DeviceList : public uHTTP::Vector
{
public:
	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////
	
	static const char *ELEM_NAME;

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	DeviceList() 
	{
	}

	~DeviceList() 
	{
		clear();
	}
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////
	
	Device *getDevice(int n)
	{
		return (Device *)get(n);
	}

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif


=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: DeviceList.h
*
*	Revision;
*
*	07/20/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_DEVICELIST_H_
#define _CLINK_DEVICELIST_H_

#include <cybergarage/util/Vector.h>

namespace CyberLink {

class Device;

class DeviceList : public CyberUtil::Vector
{
public:
	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////
	
	static const char *ELEM_NAME;

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	DeviceList() 
	{
	}

	~DeviceList() 
	{
		clear();
	}
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////
	
	Device *getDevice(int n)
	{
		return (Device *)get(n);
	}

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif


>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
