/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesPlaylistList.h
*
*	Revision:
*
*	03/13/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNES_PLAYLISTLIST_H_
#define _CLINK_MEDIA_ITUNES_PLAYLISTLIST_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_ITUNES

#include <cybergarage/util/Vector.h>
#include <cybergarage/upnp/media/server/directory/itunes/iTunesPlaylist.h>

namespace CyberLink {

class iTunesPlaylistList : public CyberUtil::Vector
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	iTunesPlaylistList() 
	{
	}
	
	~iTunesPlaylistList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	iTunesPlaylist *getPlaylist(int n)
	{
		return (iTunesPlaylist *)Vector::get(n);
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
