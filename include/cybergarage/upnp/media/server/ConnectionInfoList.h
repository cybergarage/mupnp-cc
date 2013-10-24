/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: ConnectionInfoList.h
*
*	Revision:
*
*	06/19/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_CONNECTIONINFOLIST_H_
#define _CLINK_MEDIA_CONNECTIONINFOLIST_H_

#include <cybergarage/util/Vector.h>
#include <cybergarage/upnp/media/server/ConnectionInfo.h>

namespace CyberLink {

class ConnectionInfoList : public CyberUtil::Vector
{
	////////////////////////////////////////////////
	// Constrictor
	////////////////////////////////////////////////
	
public:

	ConnectionInfoList() 
	{
	}
	
	~ConnectionInfoList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	// getConnectionInfo
	////////////////////////////////////////////////
	
public:

	ConnectionInfo *getConnectionInfo(int n)
	{
		return (ConnectionInfo *)Vector::get(n);
	}

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();

};

}

#endif


