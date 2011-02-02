/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2005
*
*	File: GatewayItemNodeList.cpp
*
*	Revision;
*
*	11/15/05
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/item/gateway/GatewayItemNodeList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void GatewayItemNodeList::clear() 
{
	int nNode = size();
	for (int n=0; n<nNode; n++) {
		GatewayItemNode *node = getGatewayItemNode(n);
		delete node;
	}
	Vector::clear();
}
