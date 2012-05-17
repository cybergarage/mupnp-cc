/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : BrowseResultNode.h
*
*	Revision:
*
*	04/27/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_BROWSWRRESULTNODE_H_
#define _CLINK_MEDIA_BROWSWRRESULTNODE_H_

#include <cybergarage/upnp/media/server/object/item/ItemNode.h>

namespace CyberLink {

class BrowseResultNode : public ItemNode
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	BrowseResultNode()
	{
	}

	////////////////////////////////////////////////
	// Abstract methods
	////////////////////////////////////////////////

public:

	const char *getContent(std::string &buf)
	{
		buf = "";
		return buf.c_str();
	}
	
	long getContentLength()
	{
		return 0;
	}

	uHTTP::InputStream *getContentInputStream()
	{
		return NULL;
	}

	const char *getMimeType()
	{
		return "*/*";
	}
};

}

#endif


