/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: FormatObject.java
*
*	Revision;
*
*	03/24/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_FORMATOBJECT_H_
#define _CLINK_MEDIA_FORMATOBJECT_H_

#include <string>
#include <cybergarage/xml/AttributeList.h>

namespace CyberLink {

class FormatObject
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

		FormatObject()
		{
		}

		virtual ~FormatObject()
		{
		}

	////////////////////////////////////////////////
	//	abstruct methods
	////////////////////////////////////////////////

public:
	
	virtual int getAttributeList(CyberXML::AttributeList &attrList) = 0;
	virtual const char *getTitle(std::string &buf) = 0;
	virtual const char *getCreator(std::string &buf) = 0;
};

}

#endif
