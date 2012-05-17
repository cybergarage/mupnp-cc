/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
**
*	File: FileItemNodeList.cpp
*
*	Revision;
*
*	04/14/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/item/file/FileItemNodeList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

FileItemNode *FileItemNodeList::getItemNode(uHTTP::File *file)
{
	int itemNodeCnt = size();
	for (int n=0; n<itemNodeCnt; n++) {
		FileItemNode *itemNode = getFileItemNode(n);
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

void FileItemNodeList::clear() 
{
	int nNode = size();
	for (int n=0; n<nNode; n++) {
		FileItemNode *node = getFileItemNode(n);
		delete node;
	}
	Vector::clear();
}
