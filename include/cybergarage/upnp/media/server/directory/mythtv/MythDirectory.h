/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: MythDirectory.h
*
*	Revision:
*
*	06/07/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MYTH_DIRECTORY_H_
#define _CLINK_MEDIA_MYTH_DIRECTORY_H_

#include <cybergarage/upnp/media/server/Directory.h>
#include <cybergarage/upnp/media/server/directory/mythtv/MythRecordedInfoList.h>
#include <cybergarage/upnp/media/server/object/item/mythtv/MythRecordedItemNodeList.h>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

namespace CyberLink {

class MythDirectory : public Directory
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////
	
public:

	static const char *NAME;
	
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

public:

	MythDirectory(const char *name);
	MythDirectory();
	
	////////////////////////////////////////////////
	// get*
	////////////////////////////////////////////////

private:

	int getAddedRecordedItemNodes(MythRecordedItemNodeList &itemNode);
	int getCurrentRecordedInfos(MythRecordedInfoList &infoList);

	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////

public:

	void update();

};

}

#endif

#endif
