/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesPlaylistItemList.cpp
*
*	Revision:
*
*	03/13/06
*		- first revision.
*
******************************************************************/

#ifdef SUPPORT_ITUNES

#include <cybergarage/upnp/media/server/directory/itunes/iTunesPlaylistItemList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void iTunesPlaylistItemList::clear() 
{
	int nTrack= size();
	for (int n=0; n<nTrack; n++) {
		iTunesPlaylistItem *item = getItem(n);
		delete item;
	}
	Vector::clear();
}

#endif
