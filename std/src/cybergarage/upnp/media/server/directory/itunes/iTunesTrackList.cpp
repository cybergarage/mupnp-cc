/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesTrackList.cpp
*
*	Revision:
*
*	03/08/06
*		- first revision.
*
******************************************************************/

#ifdef SUPPORT_ITUNES

#include <cybergarage/upnp/media/server/directory/itunes/iTunesTrackList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void iTunesTrackList::clear() 
{
	int nTrack= size();
	for (int n=0; n<nTrack; n++) {
		iTunesTrack *track= getTrack(n);
		delete track;
	}
	Vector::clear();
}

#endif
