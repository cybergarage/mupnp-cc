/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File: iTunesTrack.cpp
*
*	Revision:
*
*	03/13/06
*		- first revision.
*
******************************************************************/

#ifdef SUPPORT_ITUNES

#include <cybergarage/upnp/media/server/directory/itunes/iTunesTrack.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

iTunesTrack::iTunesTrack(CyberXML::Node *node)
{
	setNode(node);
}

iTunesTrack::~iTunesTrack()
{
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool iTunesTrack::equals(iTunesTrack *otherTrack)
{
	if (otherTrack == NULL)
		return false;

	if (getTrackID() != otherTrack->getTrackID())
		return false;

	return true;
}

#endif
