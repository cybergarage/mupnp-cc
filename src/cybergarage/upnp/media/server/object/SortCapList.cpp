/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: SortCapList.cpp
*
*	Revision;
*
*	03/24/04
*		- first revision.
*
******************************************************************/

#include <string>

#include <cybergarage/upnp/media/server/object/SortCap.h>
#include <cybergarage/upnp/media/server/object/SortCapList.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

SortCap *SortCapList::getSortCap(const char *type) 
{
	if (type == NULL)
		return NULL;
	string typeStr = type;
	int nLists = size(); 
	for (int n=0; n<nLists; n++) {
		SortCap *node = getSortCap(n);
		if (typeStr.compare(node->getType()) == 0)
			return node;
	}
	return NULL;
}

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void SortCapList::clear() 
{
	int nNode = size();
	for (int n=0; n<nNode; n++) {
		SortCap *scap = getSortCap(n);
		delete scap;
	}
	Vector::clear();
}

