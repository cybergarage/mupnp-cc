/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesPlaylistItemList.h
*
*	Revision:
*
*	03/13/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNES_PLAYLISTITEMLIST_H_
#define _CLINK_MEDIA_ITUNES_PLAYLISTITEMLIST_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_ITUNES

#include <mupnp/util/Vector.h>
#include <mupnp/upnp/media/server/directory/itunes/iTunesPlaylistItem.h>

namespace CyberLink {

class iTunesPlaylistItemList : public CyberUtil::Vector
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	iTunesPlaylistItemList() 
	{
	}
	
	~iTunesPlaylistItemList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	iTunesPlaylistItem *getItem(int n)
	{
		return (iTunesPlaylistItem *)Vector::get(n);
	}
	
	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif

#endif
