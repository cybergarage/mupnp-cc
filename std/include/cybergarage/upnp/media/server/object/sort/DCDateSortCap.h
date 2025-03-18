/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: DCDateSortCap.h
*
*	Revision;
*
*	03/31/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_DCDATESORTCAP_H_
#define _CLINK_MEDIA_DCDATESORTCAP_H_

#include <mupnp/upnp/media/server/DC.h>
#include <mupnp/upnp/media/server/object/SortCap.h>

namespace CyberLink {

class DCDateSortCap : public SortCap 
{
public:

	DCDateSortCap() 
	{
	}
	
	const char *getType() 
	{
		return DC::DATE;
	}

	int compare(ContentNode *conNode1, ContentNode *conNode2);
};

}

#endif


