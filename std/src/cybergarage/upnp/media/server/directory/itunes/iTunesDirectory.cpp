/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2006
*
*	File : iTunesDirectory.cpp
*
*	Revision:
*
*	02/22/06
*		- first revision.
*
******************************************************************/

#ifdef SUPPORT_ITUNES

#include <cybergarage/upnp/media/server/ContentDirectory.h>
#include <cybergarage/upnp/media/server/ConnectionManager.h>
#include <cybergarage/upnp/media/server/object/Format.h>
#include <cybergarage/upnp/media/server/object/FormatObject.h>
#include <cybergarage/upnp/media/server/directory/itunes/iTunesDirectory.h>

using namespace std;
using namespace CyberLink;
using namespace CyberIO;
using namespace CyberXML;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
	
iTunesDirectory::iTunesDirectory(const char *name) : Directory(name)
{
	iTunesLib = NULL;
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////
	
iTunesDirectory::~iTunesDirectory()
{
	if (iTunesLib != NULL)
		delete iTunesLib;
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////

void iTunesDirectory::setLibrary(iTunesLibrary *newLib)
{
	lock();

	if (iTunesLib != NULL)
		delete iTunesLib;

	iTunesLib = newLib;

	unlock();
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////
	
void iTunesDirectory::update()
{
	iTunesLibrary *newiTunesLib = new iTunesLibrary();

	if (newiTunesLib->update() == false) {
		delete newiTunesLib;
		return;
	}

	iTunesLibrary *curriTunesLib = getLibrary();

	if (curriTunesLib->equals(newiTunesLib) == true)
		return;

	setLibrary(newiTunesLib);
}

#endif

