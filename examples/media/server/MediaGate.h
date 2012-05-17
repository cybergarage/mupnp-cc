/******************************************************************
*
*	MediaGate for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File : MediaGate.h
*
*	04/15/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIAGATE_H_
#define _CLINK_MEDIAGATE_H_

#include <cybergarage/upnp/CyberLink.h>
#include <cybergarage/upnp/media/server/MediaServer.h>
#include <cybergarage/upnp/media/server/directory/file/FileDirectory.h>

using namespace std;
using namespace CyberLink;

class MediaGate
{
	MediaServer *mediaServ;
	int option;
	
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////

public:

	static const char *VER;

	/**** Mode Option ****/
	static const int MODE_OPT_MASK;
	static const int FILESYS_MODE;
	static const int MYTHTV_MODE;

	/**** Support Option ****/
	static const int SUPPORT_OPT_MASK;
	static const int FLASH_SUPPORT;

	static const char *MYTHTV_OPT_STRING;
	static const char *MYTHTV_OPT_STRING_OLD;
	static const char *FLASH_OPT_STRING;

	static const char *DEFAULT_PREFERENCE_FILENAME;

	static const char *PREFERENCE_CYBERGARAGE;
	static const char *PREFERENCE_MEDIASERVER;
	static const char *PREFERENCE_CONTENT_DIRECTORY;
	static const char *PREFERENCE_DIRECTORY_LIST;
	static const char *PREFERENCE_DIRECTORY;
	static const char *PREFERENCE_NAME;
	static const char *PREFERENCE_PATH;
	
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

public:

	MediaGate(int mode);

	~MediaGate();

	////////////////////////////////////////////////
	// Mode
	////////////////////////////////////////////////

public:

	void setOption(int value)
	{
		option = value;
	}
	
	int getOption()
	{
		return option;
	}
	
	int getModeOption()
	{
		return (option & MODE_OPT_MASK);
	}
	
	int getSupportOption()
	{
		return (option & SUPPORT_OPT_MASK);
	}

	////////////////////////////////////////////////
	// Preferences (FileSystem)
	////////////////////////////////////////////////

public:

	bool loadPreferences(const char *fname);
	bool savePreferences(const char *fname);
	
	////////////////////////////////////////////////
	// MediaServer
	////////////////////////////////////////////////

public:

	MediaServer *getMediaServer()
	{
		return mediaServ;
	}

	ContentDirectory *getContentDirectory()
	{
		return mediaServ->getContentDirectory();
	}
	
	////////////////////////////////////////////////
	// start/stop
	////////////////////////////////////////////////

public:

	void start();
	void stop();

	////////////////////////////////////////////////
	// print
	////////////////////////////////////////////////

public:

	void print();

};

#endif
