/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : PNGFormat.h
*
*	Revision:
*
*	04/18/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_PNGFORMT_H_
#define _CLINK_MEDIA_PNGFORMT_H_

#include <cybergarage/upnp/media/server/object/format/ImageFormat.h>

namespace CyberLink {

class PNGFormat : public ImageFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	PNGFormat();
	PNGFormat(CyberIO::File *file);

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	bool equals(CyberIO::File *file);
	
	FormatObject *createObject(CyberIO::File *file)
	{
		return new PNGFormat(file);
	}
	
	const char *getMimeType()
	{
		return "image/png";
	}
};

}

#endif
