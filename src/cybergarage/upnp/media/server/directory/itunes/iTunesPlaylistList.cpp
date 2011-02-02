/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesPlaylistList.cpp
*
*	Revision:
*
*	03/13/06
*		- first revision.
*
******************************************************************/

#ifdef SUPPORT_ITUNES

#include <cybergarage/upnp/media/server/directory/itunes/iTunesPlaylistList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void iTunesPlaylistList::clear() 
{
	int nTrack= size();
	for (int n=0; n<nTrack; n++) {
		iTunesPlaylist *plist= getPlaylist(n);
		delete plist;
	}
	Vector::clear();
}

#endif
