/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: SearchCapList.cpp
*
*	Revision;
*
*	08/07/04
*		- first revision.
*
******************************************************************/

#include <string>

#include <cybergarage/upnp/media/server/object/SearchCap.h>
#include <cybergarage/upnp/media/server/object/SearchCapList.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

SearchCap *SearchCapList::getSearchCap(const char *propertyName) 
{
	if (propertyName == NULL)
		return NULL;
	string propertyNameStr = propertyName;
	int nLists = size(); 
	for (int n=0; n<nLists; n++) {
		SearchCap *node = getSearchCap(n);
		if (propertyNameStr.compare(node->getPropertyName()) == 0)
			return node;
	}
	return NULL;
}

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void SearchCapList::clear() 
{
	int nNode = size();
	for (int n=0; n<nNode; n++) {
		SearchCap *scap = getSearchCap(n);
		delete scap;
	}
	Vector::clear();
}

