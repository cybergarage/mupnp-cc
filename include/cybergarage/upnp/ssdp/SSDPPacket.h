/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File: SSDPPacket.h
*
*	Revision;
*
*	06/05/03
*		- first revision
*	01/06/04
*		- Added set() and isNull().
*
******************************************************************/

#ifndef _CLINK_SSDPPACKET_H_
#define _CLINK_SSDPPACKET_H_

#include <iostream>
#include <string>

#include <cybergarage/net/DatagramPacket.h>
#include <cybergarage/http/HTTP.h>
#include <cybergarage/http/HTTPHeader.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/device/NTS.h>
#include <cybergarage/upnp/device/MAN.h>
#include <cybergarage/upnp/device/NT.h>
#include <cybergarage/upnp/device/ST.h>
#include <cybergarage/upnp/device/USN.h>

namespace CyberLink {

class SSDPPacket 
{
	CyberNet::DatagramPacket	dgmPacket;
	std::string localAddr;
	long timeStamp;

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
public:

	SSDPPacket()
	{
	}

	////////////////////////////////////////////////
	//	DatagramPacket
	////////////////////////////////////////////////
	
public:

	void setDatagramPacket(CyberNet::DatagramPacket *packet)
	{
		dgmPacket.set(packet);
	}

	CyberNet::DatagramPacket &getDatagramPacket()
	{
		return dgmPacket;
	}

	////////////////////////////////////////////////
	//	addr
	////////////////////////////////////////////////
	
public:

	void setLocalAddress(const char * addr)
	{
		localAddr = (addr != NULL) ? addr : "";
	}
	
	const char *getLocalAddress()
	{
		return localAddr.c_str();
	}

	////////////////////////////////////////////////
	//	Time
	////////////////////////////////////////////////

public:

	void setTimeStamp(long value)
	{
		timeStamp = value;
	}
		
	long getTimeStamp()
	{
		return timeStamp;
	}

	////////////////////////////////////////////////
	//	Remote host
	////////////////////////////////////////////////

public:

	const char *getRemoteAddress()
	{
		return dgmPacket.getAddress();
	}

	int getRemotePort()
	{
		return dgmPacket.getPort();
	}
	
	////////////////////////////////////////////////
	//	Access Methods
	////////////////////////////////////////////////

public:

	const char *getData()
	{
		return dgmPacket.getData();
	}

	////////////////////////////////////////////////
	//	Access Methods
	////////////////////////////////////////////////

public:

	const char *getHost(std::string &buf)
	{
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::HOST, buf);
	}

	const char *getCacheControl(std::string &buf)
	{
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::CACHE_CONTROL, buf);
	}
	
	const char *getLocation(std::string &buf)
	{
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::LOCATION, buf);
	}

	const char *getMAN(std::string &buf)
	{
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::MAN, buf);
	}

	const char *getST(std::string &buf)
	{
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::ST, buf);
	}

	const char *getNT(std::string &buf)
	{
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::NT, buf);
	}

	const char *getNTS(std::string &buf)
	{
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::NTS, buf);
	}

	const char *getServer(std::string &buf)
	{
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::SERVER, buf);
	}

	const char *getUSN(std::string &buf)
	{
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::USN, buf);
	}

	int getMX()
	{
		return CyberHTTP::HTTPHeaderGetIntegerValue(getData(), CyberHTTP::HTTP::MX);
	}

	////////////////////////////////////////////////
	//	Access Methods (Extension)
	////////////////////////////////////////////////

public:

	bool isRootDevice();

	bool isDiscover()
	{
		std::string buf;
		return MAN::IsDiscover(getMAN(buf));
	}

	bool isAlive()
	{
		std::string buf;
		return NTS::IsAlive(getNTS(buf));
	}

	bool isByeBye()
	{
		std::string buf;
		return NTS::IsByeBye(getNTS(buf));
	}

	int getLeaseTime()
	{
		std::string buf;
		return SSDP::GetLeaseTime(getCacheControl(buf));
	}

	////////////////////////////////////////////////
	//	set
	////////////////////////////////////////////////

public:

	void set(SSDPPacket *ssdpPacket);
	
	bool isNull()
	{
		return (timeStamp == 0) ? true : false;
	}

	////////////////////////////////////////////////
	//	toString
	////////////////////////////////////////////////

public:

	const char *toString()
	{
		return getData();
	}

	void print()
	{
		std::cout << toString() << std::endl;
	}	
};

}

#endif


