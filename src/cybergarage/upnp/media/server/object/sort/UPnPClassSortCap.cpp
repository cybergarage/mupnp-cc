/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: UPnPClassSortCap.cpp
*
*	Revision;
*
*	03/31/04
*		- first revision.
*
******************************************************************/

#include <string>
#include <cybergarage/upnp/media/server/object/ContentNode.h>
#include <cybergarage/upnp/media/server/object/sort/UPnPClassSortCap.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// compare
////////////////////////////////////////////////

int UPnPClassSortCap::compare(ContentNode *conNode1, ContentNode *conNode2)
{
	if (conNode1 == NULL || conNode2 == NULL)
		return -1;
	const char *upnpClass1 = conNode1->getTitle();
	const char *upnpClass2 = conNode2->getTitle();
	if (upnpClass2 == NULL || upnpClass2 == NULL)
		return -1;
	string upnpClass1Str = upnpClass1;
	string upnpClass2Str = upnpClass2;
	if (upnpClass1Str.length() == 0 || upnpClass2Str.length() == 0)
		return 0;
	return upnpClass1Str.compare(upnpClass2Str);
}

