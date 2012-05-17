/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : DefaultPlugIn.h
*
*	Revision:
*
*	04/15/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_DEFAULTFORMT_H_
#define _CLINK_MEDIA_DEFAULTFORMT_H_

#include <uhttp/io/File.h>
#include <cybergarage/upnp/media/server/object/Format.h>
#include <cybergarage/upnp/media/server/object/FormatObject.h>

namespace CyberLink {

class DefaultFormat : public Format, public FormatObject
{
	////////////////////////////////////////////////
	// Member
	////////////////////////////////////////////////

private:

	uHTTP::File *file;
		
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	DefaultFormat()
	{
		setFile(NULL);
	}

	DefaultFormat(uHTTP::File *file)
	{
		setFile(file);
	}
	
	////////////////////////////////////////////////
	// File
	////////////////////////////////////////////////

public:

	void setFile(uHTTP::File *f)
	{
		file = f;
	}

	uHTTP::File *getFile()
	{
		return file;
	}

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////

public:

	virtual bool equals(uHTTP::File *file)
	{
		return true;
	}
	
	virtual FormatObject *createObject(uHTTP::File *file)
	{
		return new DefaultFormat(file);
	}
	
	virtual const char *getMimeType()
	{
		return "*/*";
	}

	virtual const char *getMediaClass()
	{
		return "object.item";
	}
	
	virtual int getAttributeList(CyberXML::AttributeList &attrList)
	{
		attrList.clear();
		return attrList.size();
	}
	
	virtual const char *getTitle(std::string &buf);
	
	virtual const char *getCreator(std::string &buf)
	{
		buf = "";
		return buf.c_str();
	}
};

}

#endif


