/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : ConnectionInfo.h
*
*	Revision:
*
*	06/19/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_CONNECTIONINFO_H_
#define _CLINK_MEDIA_CONNECTIONINFO_H_

#include <string>

namespace CyberLink {

class ConnectionInfo
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////
	
public:

	static const char *INPUT;
	static const char *OUTPUT;
	static const char *OK;
	static const char *UNKNOWN;
	
	////////////////////////////////////////////////
	// Member
	////////////////////////////////////////////////

private:

	int conId;
	int rcsId;
	int transId;
	std::string protocolInfo;
	std::string peerConnectionManager;
	int peerConnectionID;
	std::string direction;
	std::string status;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:

	ConnectionInfo(int conId);
	~ConnectionInfo();
		
	////////////////////////////////////////////////
	// ID
	////////////////////////////////////////////////
	
public:

	void setID(int value)
	{
		conId = value;
	}
	
	int getID()
	{
		return conId;
	}

	////////////////////////////////////////////////
	// RcsID
	////////////////////////////////////////////////
	
public:

	void setRcsID(int value)
	{
		rcsId = value;
	}
	
	int getRcsID()
	{
		return rcsId;
	}

	////////////////////////////////////////////////
	// AVTransportID
	////////////////////////////////////////////////
	
public:

	void setAVTransportID(int value)
	{
		transId = value;
	}
	
	int getAVTransportID()
	{
		return transId;
	}
	 
	////////////////////////////////////////////////
	// ProtocolInfo
	////////////////////////////////////////////////
	
public:

	void setProtocolInfo(const char *value)
	{
		protocolInfo = value;
	}
	
	const char *getProtocolInfo()
	{
		return protocolInfo.c_str();
	}
	
	////////////////////////////////////////////////
	// PeerConnectionManager
	////////////////////////////////////////////////
	
public:

	void setPeerConnectionManager(const char *value)
	{
		peerConnectionManager = value;
	}
	
	const char *getPeerConnectionManager()
	{
		return peerConnectionManager.c_str();
	}
	 
	////////////////////////////////////////////////
	// PeerConnectionID 
	////////////////////////////////////////////////
	
public:

	void setPeerConnectionID(int value)
	{
		peerConnectionID = value;
	}
	
	int getPeerConnectionID()
	{
		return peerConnectionID;
	}

	////////////////////////////////////////////////
	// Direction
	////////////////////////////////////////////////
	
public:

	void setDirection(const char *value)
	{
		direction = value;
	}
	
	const char *getDirection()
	{
		return direction.c_str();
	}

	////////////////////////////////////////////////
	// Status
	////////////////////////////////////////////////
	
public:

	void setStatus(const char *value)
	{
		status = value;
	}
	
	const char *getStatus()
	{
		return status.c_str();
	}
};

}

#endif
