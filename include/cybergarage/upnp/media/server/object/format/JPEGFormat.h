/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : JPEGFormat.h
*
*	Revision:
*
*	04/18/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_JPEGFORMT_H_
#define _CLINK_MEDIA_JPEGFORMT_H_

#include <cybergarage/upnp/media/server/object/format/ImageFormat.h>

namespace CyberLink {

class JPEGFormat : public ImageFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	JPEGFormat();
	JPEGFormat(uHTTP::File *file);

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	bool equals(uHTTP::File *file);
	
	FormatObject *createObject(uHTTP::File *file)
	{
		return new JPEGFormat(file);
	}
	
	const char *getMimeType()
	{
		return "image/jpeg";
	}
};

}

#endif
