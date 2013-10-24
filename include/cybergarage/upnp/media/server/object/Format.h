/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: Format.h
*
*	Revision;
*
*	03/24/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_FORMAT_H_
#define _CLINK_MEDIA_FORMAT_H_

#include <cybergarage/io/File.h>

namespace CyberLink {

class FormatObject;

class Format
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:
		Format()
		{
		}

		virtual ~Format()
		{
		}

	////////////////////////////////////////////////
	//	abstruct methods
	////////////////////////////////////////////////

public:

	virtual FormatObject *createObject(CyberIO::File *file) = 0;
	virtual bool equals(CyberIO::File *file) = 0;
	virtual const char *getMimeType() = 0;
	virtual const char *getMediaClass() = 0;
};

}

#endif
