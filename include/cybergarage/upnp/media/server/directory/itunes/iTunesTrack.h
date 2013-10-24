/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesTrack.h
*
*	Revision:
*
*	03/08/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNES_TRACK_H_
#define _CLINK_MEDIA_ITUNES_TRACK_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_ITUNES

#include <cybergarage/upnp/media/server/directory/itunes/iTunesNode.h>

namespace CyberLink {

class iTunesTrack : public iTunesNode
{
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

public:

	iTunesTrack(CyberXML::Node *node);
	~iTunesTrack();

	////////////////////////////////////////////////
	// Tag Value
	////////////////////////////////////////////////

public:
	
	int getTrackID()
	{
		return getKeyInteger("Track ID");
	}

	const char *getTrackName()
	{
		return getKeyValue("Name");
	}

	long getSize()
	{
		return getKeyLong("Size");
	}

	////////////////////////////////////////////////
	// equals
	////////////////////////////////////////////////

public:

	bool equals(iTunesTrack *otherTrack);

};

}

#endif

#endif
