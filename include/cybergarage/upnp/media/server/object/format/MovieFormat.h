/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : MovieFormat.h
*
*	Revision:
*
*	06/08/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MOVIEFORMAT_H_
#define _CLINK_MEDIA_MOVIEFORMAT_H_

#include <cybergarage/upnp/media/server/object/format/DefaultFormat.h>

namespace CyberLink {

class MovieFormat : public DefaultFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	MovieFormat()
	{	
		setFile(NULL);
	}
	
	MovieFormat(uHTTP::File *file)
	{
		setFile(file);
	}

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	virtual bool equals(uHTTP::File *file) = 0;
	virtual FormatObject *createObject(uHTTP::File *file) = 0;
	virtual const char *getMimeType() = 0;
	
	const char *getMediaClass()
	{
		return "object.item.videoItem.movie";
	}
	
	virtual int getAttributeList(CyberXML::AttributeList &attrList)
	{
		attrList.clear();
		return attrList.size();
	}

	const char *getCreator(std::string &buf)
	{
		buf = "";
		return buf.c_str();
	}
};

}

#endif
