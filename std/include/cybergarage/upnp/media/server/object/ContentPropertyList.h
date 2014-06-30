/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ContentPropertyList.h
*
*	Revision;
*
*	03/14/04
*		- first revision
*
******************************************************************/

#ifndef _CLINK_MEDIA_CONTENTPROPERTYLIST_H_
#define _CLINK_MEDIA_CONTENTPROPERTYLIST_H_

#include <cybergarage/util/Vector.h>
#include <cybergarage/upnp/media/server/object/ContentProperty.h>

namespace CyberLink {

class ContentPropertyList : public CyberUtil::Vector 
{

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	ContentPropertyList();
	
	~ContentPropertyList();

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	bool addContentProperty(ContentProperty *prop);
	bool removeContentProperty(ContentProperty *prop);
	bool insertContentProperty(ContentProperty *prop, int index);

	ContentProperty *getContentProperty(int n)
	{
		return (ContentProperty*)Vector::get(n);
	}

	ContentProperty *getContentProperty(const char *name);

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif


