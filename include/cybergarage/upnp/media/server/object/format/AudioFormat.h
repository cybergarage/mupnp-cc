/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : AudioFormat.h
*
*	Revision:
*
*	06/09/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_AUDIOFORMAT_H_
#define _CLINK_MEDIA_AUDIOFORMAT_H_

#include <cybergarage/upnp/media/server/object/format/DefaultFormat.h>

namespace CyberLink {

class AudioFormat : public DefaultFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	AudioFormat()
	{	
		setFile(NULL);
	}
	
	AudioFormat(uHTTP::File *file)
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
		return "object.item.audioItem.musicTrack";
	}
	
	virtual int getAttributeList(CyberXML::AttributeList &attrList)
	{
		attrList.clear();
		return attrList.size();
	}

	virtual const char *getCreator(std::string &buf)
	{
		buf = "";
		return buf.c_str();
	}
};

}

#endif
