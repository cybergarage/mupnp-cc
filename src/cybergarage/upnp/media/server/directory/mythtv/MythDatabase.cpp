/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: MythDatabase.cpp
*
*	Revision:
*
*	06/07/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/directory/mythtv/MythDatabase.h>
#include <string>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const int MythDatabase::PORT = 3306;
const char *MythDatabase::NAME = "mythconverg";
const char *MythDatabase::USER = "mythtv";
const char *MythDatabase::PASSWD = "mythtv";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

MythDatabase::MythDatabase()
{
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

const char *MythDatabase::getRecordFilePrefix(std::string &buf)
{
	static const char *sql = "select data from settings where value = 'RecordFilePrefix'";

	if (query(sql) == false)
		return "";

	if (fetch() == false)
		return "";

	buf = getString(0);
	
	return buf.c_str();
}


////////////////////////////////////////////////
// RecordedInfo
////////////////////////////////////////////////

int MythDatabase::getRecordedInfos(MythRecordedInfoList &infoList)
{
	string recFilePrefix;
	getRecordFilePrefix(recFilePrefix);

	static const char *sql = "select chanid, recordid, starttime, endtime, title, subtitle, description, category from recorded";

	if (query(sql) == false)
		return 0;

	while (fetch() == true) {
		MythRecordedInfo *recInfo = new MythRecordedInfo();
		recInfo->setRecordFilePrefix(recFilePrefix.c_str());
		recInfo->setChanID(getInteger(0));
		recInfo->setRecordID(getInteger(1));
		recInfo->setStartTime(getTimestamp(2));
		recInfo->setEndTime(getTimestamp(3));
		recInfo->setTitle(getString(4));
		recInfo->setSubTitle(getString(4));
		recInfo->setDescription(getString(5));
		recInfo->setCategory(getString(6));
		infoList.add(recInfo);
	}

	return infoList.size();
}

#endif


