/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: DCTitleSortCap.cpp
*
*	Revision;
*
*	03/31/04
*		- first revision.
*
******************************************************************/

#include <string>
#include <cybergarage/upnp/media/server/object/ContentNode.h>
#include <cybergarage/upnp/media/server/object/sort/DCTitleSortCap.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// compare
////////////////////////////////////////////////

int DCTitleSortCap::compare(ContentNode *conNode1, ContentNode *conNode2)
{
	if (conNode1 == NULL || conNode2 == NULL)
		return -1;
	const char *title1 = conNode1->getTitle();
	const char * title2 = conNode2->getTitle();
	if (title1 == NULL || title2 == NULL)
		return -1;
	string title1Str = title1;
	string title2Str = title2;
	if (title1Str.length() == 0 || title2Str.length() == 0)
		return 0;
	return title1Str.compare(title2Str);
}
