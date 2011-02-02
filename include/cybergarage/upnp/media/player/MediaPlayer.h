/******************************************************************
*
*	MediaPlayer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : MediaPlayer.h
*
*	04/20/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MEDIAPLAYER_H_
#define _CLINK_MEDIA_MEDIAPLAYER_H_

#include <cybergarage/upnp/media/server/MediaServer.h>
#include <cybergarage/upnp/media/server/action/BrowseAction.h>
#include <cybergarage/xml/Node.h>
#include <cybergarage/upnp/ControlPoint.h>

namespace CyberLink {

class MediaPlayer : public ControlPoint
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////
	
public:

	static const char *DEVICE_TYPE;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:
	
	MediaPlayer();
	~MediaPlayer();
	
	////////////////////////////////////////////////
	// start/stop (Overided)
	////////////////////////////////////////////////
	
public:

	bool start();
	bool stop();
	
	////////////////////////////////////////////////
	// Browse
	////////////////////////////////////////////////

public:

	CyberXML::Node *browse(
		Device *dev,
		const char *objectID,
		const char *browseFlag,
		const char *filter,
		int startIndex,
		int requestedCount,
		const char *sortCaiteria);

	CyberXML::Node *browseMetaData(
		Device *dev,
		const char *objectID,
		const char *filter,
		int startIndex,
		int requestedCount,
		const char *sortCaiteria)
	{
		return browse(dev, objectID, BrowseAction::BROWSE_METADATA, filter, startIndex, requestedCount, sortCaiteria);
	}

	CyberXML::Node *browseDirectChildren(
		Device *dev,
		const char *objectID,
		const char *filter,
		int startIndex,
		int requestedCount,
		const char *sortCaiteria)
	{
		return browse(dev, objectID, BrowseAction::BROWSE_DIRECT_CHILDREN, filter, startIndex, requestedCount, sortCaiteria);
	}

	////////////////////////////////////////////////
	// Content
	////////////////////////////////////////////////

public:

	ContentNode *getContentDirectory(Device *dev);

private:

	int getContentDirectory(ContentNode *parentNode, Device *dev, const char *objectID);

};

}

#endif


