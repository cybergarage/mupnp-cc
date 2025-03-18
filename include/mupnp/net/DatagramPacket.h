/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: DatagramPacket.h
*
*	Revision;
*
*	05/27/03
*		- first revision
*	01/06/04
*		- Added set().
*
******************************************************************/

#ifndef _CNET_DATAGRAMPACKET_H_
#define _CNET_DATAGRAMPACKET_H_

#include <cybergarage/net/InetSocketAddress.h>

#include <string>

namespace CyberNet {

class DatagramPacket
{
	InetSocketAddress sockAddr;
	std::string data;

public:

	DatagramPacket()
	{
	}

	DatagramPacket(const char *msg, InetSocketAddress *addr)
	{
		setData(msg);
		setSocketAddress(addr);
	}

	~DatagramPacket()
	{
	}

	////////////////////////////////////////////////
	//	date
	////////////////////////////////////////////////

	void setData(const char *value)
	{
		data = value;
	}

	const char *getData()
	{
		return data.c_str();
	}

	int getLength()
	{
		return (int)data.length();
	}

	////////////////////////////////////////////////
	//	address/port
	////////////////////////////////////////////////

	void setSocketAddress(InetSocketAddress *addr)
	{
		sockAddr.set(addr);
	}

	InetSocketAddress *getSocketAddress()
	{
		return &sockAddr;
	}

	void setAddress(const char *addr)
	{
		sockAddr.setAddress(addr);
	}

	void setPort(int port)
	{
		sockAddr.setPort(port);
	}

	const char *getAddress()
	{
		return sockAddr.getAddress();
	}

	int getPort()
	{
		return sockAddr.getPort();
	}

	void set(DatagramPacket *dgmPack)
	{
		if (dgmPack == NULL) {
			setSocketAddress(NULL);
			setData("");
			return;
		}
		setSocketAddress(dgmPack->getSocketAddress());
		setData(dgmPack->getData());
	}
};

}

#endif
