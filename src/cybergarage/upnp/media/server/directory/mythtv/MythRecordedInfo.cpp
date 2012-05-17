/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: MythRecordedInfo.cpp
*
*	Revision;
*
*	06/05/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/directory/mythtv/MythRecordedInfo.h>
#include <uhttp/util/Date.h>
#include <uhttp/util/Debug.h>
#include <sstream>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

using namespace std;
using namespace uHTTP;
using namespace CyberLink;

////////////////////////////////////////////////
// file
////////////////////////////////////////////////

static const char *NUV_FILE_DATE_FORMAT = "%04d%02d%02d%02d%02d%02d";
static const int NUV_FILE_DATE_FORMAT_LEN = (4+2+2+2+2+2);
static const char *NUV_FILE_EXT = "nuv";

const char *MythRecordedInfo::getFileName(std::string &buf)
{
	ostringstream osBuf;

	char statDateBuf[NUV_FILE_DATE_FORMAT_LEN+1];
	Date statDate(getStartTime());
	sprintf(statDateBuf, NUV_FILE_DATE_FORMAT,
		statDate.getYear(),
		statDate.getMonth(),
		statDate.getDay(),
		statDate.getHour(),
		statDate.getMinute(),
		statDate.getSecond());

	char endDateBuf[NUV_FILE_DATE_FORMAT_LEN+1];
	Date endDate(getEndTime());
	sprintf(endDateBuf, NUV_FILE_DATE_FORMAT,
		endDate.getYear(),
		endDate.getMonth(),
		endDate.getDay(),
		endDate.getHour(),
		endDate.getMinute(),
		endDate.getSecond());

	osBuf << getRecordFilePrefix() << getChanID() << "_" << statDateBuf << "_"  << endDateBuf << "." << NUV_FILE_EXT;

	buf = osBuf.str();

	return buf.c_str();
}

////////////////////////////////////////////////
// set
////////////////////////////////////////////////

void MythRecordedInfo::set(MythRecordedInfo *info)
{
	recordFilePrefix = info->recordFilePrefix;
	category = info->category;
	chanID = info->chanID;
	description = info->description;
	endTime = info->endTime;
	recGroup = info->recGroup;
	recordID = info->recordID;
	startTime = info->startTime;
	title = info->title;
	subTitle = info->subTitle;
}

////////////////////////////////////////////////
// print
////////////////////////////////////////////////

void MythRecordedInfo::print()
{
/*
	Debug.message("title = " + getTitle());
	Debug.message("subTitle = " + getSubTitle());
	Debug.message("file = " + getFile());
*/
}

#endif
