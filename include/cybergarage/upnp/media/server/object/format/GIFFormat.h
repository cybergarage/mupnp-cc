/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : GIFPlugIn.h
*
*	Revision:
*
*	01/25/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_GIFFORMT_H_
#define _CLINK_MEDIA_GIFFORMT_H_

#include <cybergarage/upnp/media/server/object/format/ImageFormat.h>

namespace CyberLink {

class GIFFormat : public ImageFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	GIFFormat();
	GIFFormat(uHTTP::File *file);

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	bool equals(uHTTP::File *file);
	
	FormatObject *createObject(uHTTP::File *file)
	{
		return new GIFFormat(file);
	}
	
	const char *getMimeType()
	{
		return "image/gif";
	}
};

}

#endif
