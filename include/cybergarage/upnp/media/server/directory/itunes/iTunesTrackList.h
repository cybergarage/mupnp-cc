/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesTrackList.h
*
*	Revision:
*
*	03/08/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNES_TRACKLIST_H_
#define _CLINK_MEDIA_ITUNES_TRACKLIST_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_ITUNES

#include <cybergarage/util/Vector.h>
#include <cybergarage/upnp/media/server/directory/itunes/iTunesTrack.h>

namespace CyberLink {

class iTunesTrackList : public CyberUtil::Vector
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	iTunesTrackList() 
	{
	}
	
	~iTunesTrackList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	iTunesTrack *getTrack(int n)
	{
		return (iTunesTrack *)Vector::get(n);
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
