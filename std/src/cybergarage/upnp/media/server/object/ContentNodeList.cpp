/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ContentNodeList.cpp
*
*	Revision;
*
*	03/14/04
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/ContentNodeList.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

ContentNode *ContentNodeList::getContentNode(const char *name) 
{
	if (name == NULL)
		return NULL;
	std::string nameStr = name;
	int nLists = size(); 
	for (int n=0; n<nLists; n++) {
		ContentNode *node = getContentNode(n);
		if (nameStr.compare(node->getName()) == 0)
			return node;
	}
	return NULL;
}

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void ContentNodeList::clear() 
{
	if (delElemFlag == true) {
		int nNode = size();
		for (int n=0; n<nNode; n++) {
			ContentNode *cnode = getContentNode(n);
			delete cnode;
		}
	}
	Vector::clear();
}
