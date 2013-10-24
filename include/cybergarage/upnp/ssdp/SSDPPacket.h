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

<<<<<<< HEAD
#include <uhttp/net/DatagramPacket.h>
#include <uhttp/http/HTTP.h>
#include <uhttp/http/HTTPHeader.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/device/NTS.h>
#include <cybergarage/upnp/device/MAN.h>
#include <cybergarage/upnp/device/NT.h>
#include <cybergarage/upnp/device/ST.h>
#include <cybergarage/upnp/device/USN.h>
=======
#include <cybergarage/net/DatagramPacket.h>
#include <cybergarage/http/HTTP.h>
#include <cybergarage/http/HTTPHeader.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/device/NTS.h>
#include <cybergarage/upnp/device/MAN.h>
#include <cybergarage/upnp/device/NT.h>
#include <cybergarage/upnp/device/ST.h>
#include <cybergarage/upnp/device/USN.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

namespace CyberLink {

class SSDPPacket 
{
<<<<<<< HEAD
	uHTTP::DatagramPacket	dgmPacket;
=======
	CyberNet::DatagramPacket	dgmPacket;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
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

<<<<<<< HEAD
	void setDatagramPacket(uHTTP::DatagramPacket *packet)
=======
	void setDatagramPacket(CyberNet::DatagramPacket *packet)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		dgmPacket.set(packet);
	}

<<<<<<< HEAD
	uHTTP::DatagramPacket &getDatagramPacket()
=======
	CyberNet::DatagramPacket &getDatagramPacket()
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return dgmPacket;
	}

	////////////////////////////////////////////////
	//	addr
	////////////////////////////////////////////////
	
public:

<<<<<<< HEAD
	void setLocalAddress(const std::string & addr)
	{
		localAddr = addr;
=======
	void setLocalAddress(const char * addr)
	{
		localAddr = (addr != NULL) ? addr : "";
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
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
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::HOST, buf);
=======
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::HOST, buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getCacheControl(std::string &buf)
	{
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::CACHE_CONTROL, buf);
=======
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::CACHE_CONTROL, buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}
	
	const char *getLocation(std::string &buf)
	{
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::LOCATION, buf);
=======
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::LOCATION, buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getMAN(std::string &buf)
	{
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::MAN, buf);
=======
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::MAN, buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getST(std::string &buf)
	{
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::ST, buf);
=======
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::ST, buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getNT(std::string &buf)
	{
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::NT, buf);
=======
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::NT, buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getNTS(std::string &buf)
	{
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::NTS, buf);
=======
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::NTS, buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getServer(std::string &buf)
	{
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::SERVER, buf);
=======
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::SERVER, buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	const char *getUSN(std::string &buf)
	{
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetValue(getData(), uHTTP::HTTP::USN, buf);
=======
		return CyberHTTP::HTTPHeaderGetValue(getData(), CyberHTTP::HTTP::USN, buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

	int getMX()
	{
<<<<<<< HEAD
		return uHTTP::HTTPHeaderGetIntegerValue(getData(), uHTTP::HTTP::MX);
=======
		return CyberHTTP::HTTPHeaderGetIntegerValue(getData(), CyberHTTP::HTTP::MX);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
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


