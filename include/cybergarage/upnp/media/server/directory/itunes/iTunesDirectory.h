/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File : iTunesDirectory.h
*
*	Revision:
*
*	02/22/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNES_DIRECTORY_H_
#define _CLINK_MEDIA_ITUNES_DIRECTORY_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_ITUNES

#include <cybergarage/upnp/media/server/Directory.h>
#include <cybergarage/upnp/media/server/directory/itunes/iTunesLibrary.h>

namespace CyberLink {

class iTunesDirectory : public Directory
{
	iTunesLibrary *iTunesLib;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:

	iTunesDirectory(const char *name);
	~iTunesDirectory();
	
	////////////////////////////////////////////////
	// Library
	////////////////////////////////////////////////
	
private:

	void setLibrary(iTunesLibrary *newlib);

	iTunesLibrary *getLibrary()
	{
		return iTunesLib;
	}

	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////
	
public:

	void update();
};

}

#endif

#endif


