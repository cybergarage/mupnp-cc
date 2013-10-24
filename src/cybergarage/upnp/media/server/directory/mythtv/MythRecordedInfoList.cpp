/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: MythRecordedInfo.cpp
*
*	Revision:
*
*	06/07/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/directory/mythtv/MythRecordedInfoList.h>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

using namespace CyberLink;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void MythRecordedInfoList::clear() 
{
	int nNode = size();
	for (int n=0; n<nNode; n++) {
		MythRecordedInfo *node = getRecordedInfo(n);
		delete node;
	}
	Vector::clear();
}

#endif
