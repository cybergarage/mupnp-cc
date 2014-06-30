/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: DCTitleSortCap.java
*
*	Revision;
*
*	03/31/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_DCTITLESORTCAP_H_
#define _CLINK_MEDIA_DCTITLESORTCAP_H_

#include <cybergarage/upnp/media/server/DC.h>
#include <cybergarage/upnp/media/server/object/SortCap.h>

namespace CyberLink {

class DCTitleSortCap : public SortCap 
{
public:

	DCTitleSortCap() 
	{
	}
	
	const char *getType() 
	{
		return DC::TITLE;
	}

	int compare(ContentNode *conNode1, ContentNode *conNode2);
};

}

#endif
