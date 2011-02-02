/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NetworkInterface.h
*
*	Revision;
*
*	07/01/03
*		- first revision.
*	
******************************************************************/

#ifndef _CNET_NETWORKINTERFACE_H_
#define _CNET_NETWORKINTERFACE_H_

#include <string>

namespace CyberNet {

class NetworkInterface 
{
	std::string name;
	std::string addr;
	int index;
public:

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

	NetworkInterface(const char *addr = NULL, const char *name = NULL, int idx = 0)
	{
		setAddress(addr);
		setName(name);
		setIndex(idx);
	}
	
	////////////////////////////////////////////////
	// Address
	////////////////////////////////////////////////

	void setAddress(const char *value)
	{
		addr = (value != NULL) ? value : "";
	}
		
	const char *getAddress()
	{
		return addr.c_str();
	}
		
	////////////////////////////////////////////////
	// Name
	////////////////////////////////////////////////

	void setName(const char *value)
	{
		name = (value != NULL) ? value : "";
	}
		
	const char *getName()
	{
		return name.c_str();
	}

	////////////////////////////////////////////////
	// Index
	////////////////////////////////////////////////

	void setIndex(int value)
	{
		index = value;
	}
		
	int getIndex()
	{
		return index;
	}
};

}

#endif
