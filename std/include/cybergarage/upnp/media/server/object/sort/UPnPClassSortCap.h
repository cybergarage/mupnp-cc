/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: UPnPClassSortCap.h
*
*	Revision;
*
*	03/31/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_UPNPCLADDSORTCAP_H_
#define _CLINK_MEDIA_UPNPCLADDSORTCAP_H_

#include <cybergarage/upnp/media/server/UPnP.h>
#include <cybergarage/upnp/media/server/object/SortCap.h>

namespace CyberLink {

class UPnPClassSortCap : public SortCap 
{
public:

	UPnPClassSortCap() 
	{
	}
	
	const char *getType() 
	{
		return UPnP::CLASS;
	}

	int compare(ContentNode *conNode1, ContentNode *conNode2);
};

}

#endif


