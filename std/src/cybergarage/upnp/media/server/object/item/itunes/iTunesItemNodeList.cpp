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

#include <mupnp/upnp/media/server/object/item/itunes/iTunesItemNodeList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

iTunesItemNode *iTunesItemNodeList::getItemNode(CyberIO::File *file)
{
	int itemNodeCnt = size();
	for (int n=0; n<itemNodeCnt; n++) {
		iTunesItemNode *itemNode = getiTunesItemNode(n);
		CyberIO::File *itemNodeFile = itemNode->getFile();
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
