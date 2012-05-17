/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File : iTunesLibrary.h
*
*	Revision:
*
*	02/22/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNES_LIBRARY_H_
#define _CLINK_MEDIA_ITUNES_LIBRARY_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_ITUNES

#include <string>
#include <uhttp/io/File.h>
#include <cybergarage/xml/Parser.h>
#include <cybergarage/upnp/media/server/directory/itunes/iTunesTrackList.h>
#include <cybergarage/upnp/media/server/directory/itunes/iTunesPlaylistList.h>

namespace CyberLink {

class iTunesLibrary
{
	CyberXML::Node *rootNode;
	iTunesTrackList *itunesTrackList;
	iTunesPlaylistList *itunesPlaylistList;

	////////////////////////////////////////////////
	// Constant
	////////////////////////////////////////////////

private:

	static const char *DICT_TAG;
	static const char *KEY_TAG;
	static const char *ARRAY_TAG;
	static const char *KEY_TRACKS;
	static const char *KEY_PLAYLISTS;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:

	iTunesLibrary();
	~iTunesLibrary();
	
	////////////////////////////////////////////////
	// Music Library
	////////////////////////////////////////////////

private:

	static const char *GetMusicLibraryXMLFileName(std::string &buf);

	////////////////////////////////////////////////
	// Root Node
	////////////////////////////////////////////////

public:

	CyberXML::Node *getRootNode()
	{
		return rootNode;
	}

	////////////////////////////////////////////////
	// Track List
	////////////////////////////////////////////////

public:

	iTunesTrackList *getTrackList()
	{
		return itunesTrackList;
	}

	////////////////////////////////////////////////
	// Track List
	////////////////////////////////////////////////

public:

	iTunesPlaylistList *getPlaylistList()
	{
		return itunesPlaylistList;
	}

	////////////////////////////////////////////////
	// equals 
	////////////////////////////////////////////////

public:

	bool equals(iTunesLibrary *otherLib);

	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////

private:

	bool updateTracks();
	bool updatePlaylists();

public:

	void clear();
	bool update();
};

}

#endif

#endif


