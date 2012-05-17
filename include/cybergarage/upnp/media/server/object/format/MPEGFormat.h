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
*	06/08/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MPEGFORMT_H_
#define _CLINK_MEDIA_MPEGFORMT_H_

#include <cybergarage/upnp/media/server/object/format/MovieFormat.h>

namespace CyberLink {

class MPEGFormat : public MovieFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	MPEGFormat();
	MPEGFormat(uHTTP::File *file);

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	bool equals(uHTTP::File *file);
	
	FormatObject *createObject(uHTTP::File *file)
	{
		return new MPEGFormat(file);
	}
	
	const char *getMimeType()
	{
		return "video/mpeg";
	}

	int getAttributeList(CyberXML::AttributeList &attrList);
};

}

#endif


