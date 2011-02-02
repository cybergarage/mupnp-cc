/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: MythDatabase.h
*
*	Revision:
*
*	06/07/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MYTH_DATABASE_H_
#define _CLINK_MEDIA_MYTH_DATABASE_H_

#include <cybergarage/sql/UniMySQL.h>
#include <cybergarage/upnp/media/server/directory/mythtv/MythRecordedInfoList.h>
#include <string>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

namespace CyberLink {

class MythDatabase : public CyberSQL::UniMySQL
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////
	
	static const int PORT;
	static const char *NAME;
	static const char *USER;
	static const char *PASSWD;
	
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:

	MythDatabase();
	
	////////////////////////////////////////////////
	// open
	////////////////////////////////////////////////

public:

	bool open(const char *host)
	{
		return UniMySQL::open(host, PORT, NAME, USER, PASSWD);
	}
	
	bool open()
	{
		return open("localhost");
	}

	////////////////////////////////////////////////
	// getRecordFilePrefix
	////////////////////////////////////////////////

public:

	const char *getRecordFilePrefix(std::string &buf);
	
	////////////////////////////////////////////////
	// RecordedInfo
	////////////////////////////////////////////////
	
public:

	int getRecordedInfos(MythRecordedInfoList &infoList);

};

}

#endif

#endif

