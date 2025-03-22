/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
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

#include <mupnp/upnp/media/server/object/format/ImageFormat.h>

namespace CyberLink {

class GIFFormat : public ImageFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	GIFFormat();
	GIFFormat(CyberIO::File *file);

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	bool equals(CyberIO::File *file);
	
	FormatObject *createObject(CyberIO::File *file)
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
