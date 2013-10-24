/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: InetSocketAddress.h
*
*	Revision;
*
*	07/01/03
*		- first revision.
*	01/06/04
*		- Added set().
*	
******************************************************************/

#ifndef _CNET_INETSOCKETADDRESS_H_
#define _CNET_INETSOCKETADDRESS_H_

#include <string>

namespace CyberNet {

class InetSocketAddress 
{
	std::string addr;
	int port;

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	InetSocketAddress()
	{
		setAddress("");
		setPort(-1);
	}

	InetSocketAddress(int port)
	{
		setAddress("");
		setPort(port);
	}

	InetSocketAddress(const char *addr, int port)
	{
		setAddress(addr);
		setPort(port);
	}
	
	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

	void setAddress(const char *value)
	{
		addr = (value != NULL) ? value : "";
	}
		
	const char *getAddress()
	{
		return addr.c_str();
	}
		
	void setPort(int value)
	{
		port = value;
	}
		
	int getPort()
	{
		return port;
	}

	void set(InetSocketAddress *isaddr)
	{
		if (isaddr == NULL) {
			setAddress("");
			setPort(0);
			return;
		}
		setAddress(isaddr->getAddress());
		setPort(isaddr->getPort());
	}
};

}

#endif
