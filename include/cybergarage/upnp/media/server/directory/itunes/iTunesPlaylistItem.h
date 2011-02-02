/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesPlaylistItem.h
*
*	Revision:
*
*	03/08/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNES_PLAYLISTITEM_H_
#define _CLINK_MEDIA_ITUNES_PLAYLISTITEM_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_ITUNES

#include <cybergarage/upnp/media/server/directory/itunes/iTunesNode.h>

namespace CyberLink {

class iTunesPlaylistItem : public iTunesNode
{
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

public:

	iTunesPlaylistItem(CyberXML::Node *node)
	{
		setNode(node);
	}

	////////////////////////////////////////////////
	// equals
	////////////////////////////////////////////////

public:

	bool equals(iTunesPlaylistItem *otherPlaylistItem);

};

}

#endif

#endif
