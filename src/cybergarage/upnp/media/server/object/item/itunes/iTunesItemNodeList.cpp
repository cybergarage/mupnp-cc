/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
**
*	File: iTunesItemNodeList.cpp
*
*	Revision;
*
*	03/14/06
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/item/itunes/iTunesItemNodeList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

iTunesItemNode *iTunesItemNodeList::getItemNode(uHTTP::File *file)
{
	int itemNodeCnt = size();
	for (int n=0; n<itemNodeCnt; n++) {
		iTunesItemNode *itemNode = getiTunesItemNode(n);
		uHTTP::File *itemNodeFile = itemNode->getFile();
		if (itemNodeFile == NULL)
			continue;
		if (itemNode->equals(file) == true)
			return itemNode;
	}
	return NULL;
}

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void iTunesItemNodeList::clear() 
{
	int nNode = size();
	for (int n=0; n<nNode; n++) {
		iTunesItemNode *node = getiTunesItemNode(n);
		delete node;
	}
	Vector::clear();
}
