/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NetworkInterfaceList.h
*
*	Revision;
*
*	07/05/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_NETWORKINTERFACELIST_H_
#define _CNET_NETWORKINTERFACELIST_H_

#include <iostream>
#include <cybergarage/util/Vector.h>
#include <cybergarage/net/NetworkInterface.h>

namespace CyberNet {

class NetworkInterfaceList : public CyberUtil::Vector 
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
public:

	NetworkInterfaceList() 
	{
	}
	
	~NetworkInterfaceList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////
	
public:

	NetworkInterface *getNetworkInterface(int n)
	{
		return (NetworkInterface *)get(n);
	}

	void clear() 
	{
		int nNetIf = size();
		for (int n=0; n<nNetIf; n++) {
			NetworkInterface *netif = getNetworkInterface(n);
			delete netif;
		}
		Vector::clear();
	}

	void remove(NetworkInterface *netif)
	{
		if (netif == NULL)
				return;
		delete netif;
		Vector::remove(netif);
	}

	void print()
	{
		int ifNum = size();
		for (int n=0; n<ifNum; n++) {
			NetworkInterface *netif = getNetworkInterface(n);
			const char *addr = netif->getAddress();
			const char *name = netif->getName();
			int idx = netif->getIndex();
			std::cout << "[" << n << "]" <<  addr << ", " << name << ", " << idx << std::endl;
		}
	}
};

}

#endif
