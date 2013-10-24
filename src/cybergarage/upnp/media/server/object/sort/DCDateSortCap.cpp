/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: DCDateSortCap.cpp
*
*	Revision;
*
*	03/31/04
*		- first revision.
*	08/01/04
*		- Added <typeinfo> for typeid() for gcc 2.95.3.
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/ContentNode.h>
#include <cybergarage/upnp/media/server/object/item/ItemNode.h>
#include <cybergarage/upnp/media/server/object/sort/DCDateSortCap.h>

#include <string>
#include <typeinfo>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// compare
////////////////////////////////////////////////

int DCDateSortCap::compare(ContentNode *conNode1, ContentNode *conNode2)
{
	if (conNode1 == NULL || conNode2 == NULL)
		return 0;
	if ((typeid(conNode1) != typeid(ItemNode)) || (typeid(conNode2) != typeid(ItemNode)))
		return 0;
	ItemNode *itemNode1 = (ItemNode *)conNode1;
	ItemNode *itemNode2 = (ItemNode *)conNode2;
	long itemTime1 = itemNode1->getDateTime();
	long itemTime2 = itemNode2->getDateTime();
	if (itemTime1 == itemTime2)
		return 0;
	return (itemTime1 < itemTime2) ? -1 : 1;
}

