/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
**
*	File: ItemNodeList.java
*
*	Revision;
*
*	03/25/04
*		- first revision.
*
******************************************************************/


#include <cybergarage/upnp/media/server/object/item/ItemNodeList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void ItemNodeList::clear() 
{
	int nNode = size();
	for (int n=0; n<nNode; n++) {
		ItemNode *node = getItemNode(n);
		delete node;
	}
	Vector::clear();
}
