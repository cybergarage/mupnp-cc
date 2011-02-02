/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ContentPropertyList.cpp
*
*	Revision;
*
*	03/14/04
*		- first revision
*	06/30/04
*		- Added addContentProperty(), insertContentProperty() and removeContentProperty();
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/ContentPropertyList.h>

using namespace CyberLink;

ContentPropertyList::ContentPropertyList() 
{
}
	
ContentPropertyList::~ContentPropertyList() 
{
	clear();
}

bool ContentPropertyList::addContentProperty(ContentProperty *prop) 
{
	if (prop == NULL)
		return false;
	return add(prop);
}

bool ContentPropertyList::insertContentProperty(ContentProperty *prop, int index) 
{
	if (prop == NULL)
		return false;
	return insertAt(prop, index);
}

bool ContentPropertyList::removeContentProperty(ContentProperty *prop) 
{
	if (prop == NULL)
		return false;
	bool ret = remove(prop);
	delete prop;
	return ret;
}

ContentProperty *ContentPropertyList::getContentProperty(const char *name) 
{
	if (name == NULL)
		return NULL;
	std::string nameStr = name;
	int nLists = size(); 
	for (int n=0; n<nLists; n++) {
		ContentProperty *elem = getContentProperty(n);
		if (nameStr.compare(elem->getName()) == 0)
			return elem;
	}
	return NULL;
}

void ContentPropertyList::clear() 
{
	int nProp = size();
	for (int n=0; n<nProp; n++) {
		ContentProperty *prop = getContentProperty(n);
		delete prop;
	}
	Vector::clear();
}
