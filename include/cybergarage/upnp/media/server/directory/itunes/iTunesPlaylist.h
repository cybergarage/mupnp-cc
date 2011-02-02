/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesPlaylist.h
*
*	Revision:
*
*	03/08/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNES_PLAYLIST_H_
#define _CLINK_MEDIA_ITUNES_PLAYLIST_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_ITUNES

#include <cybergarage/upnp/media/server/directory/itunes/iTunesNode.h>
#include <cybergarage/upnp/media/server/directory/itunes/iTunesPlaylistItemList.h>

namespace CyberLink {

class iTunesPlaylist : public iTunesNode
{
private:

	iTunesPlaylistItemList *playlistItemList;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

public:

	iTunesPlaylist(CyberXML::Node *node);
	~iTunesPlaylist();

	////////////////////////////////////////////////
	// Playlist Item
	////////////////////////////////////////////////

public:

	iTunesPlaylistItemList *getPlaylistItemList()
	{
		return playlistItemList;
	}

	////////////////////////////////////////////////
	// equals
	////////////////////////////////////////////////

public:

	bool equals(iTunesPlaylist *otherPlaylist);

};

}

#endif

#endif
