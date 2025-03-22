/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File : GatewayDirectory.h
*
*	Revision:
*
*	11/15/05
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_GATEWAY_DIRECTORY_H_
#define _CLINK_MEDIA_GATEWAY_DIRECTORY_H_

#include <mupnp/io/File.h>
#include <mupnp/upnp/media/server/Directory.h>
#include <mupnp/upnp/media/server/object/item/file/FileItemNode.h>
#include <mupnp/upnp/media/server/object/item/file/FileItemNodeList.h>

namespace CyberLink {

class GatewayDirectory : public Directory
{
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:

	GatewayDirectory(const char *name);
	
	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////
	
public:

	void update();
};

}

#endif


