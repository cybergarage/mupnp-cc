/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : DIDLLiteNode.h
*
*	Revision:
*
*	03/31/04
*		- first revision.
*	10/26/04 
*		- Brent Hills <bhills@openshores.com>
*		- Changed DIDLLiteNode is a subclass of Node instead of ContentNode
*		  because the node has the parentID attributes.
*
******************************************************************/

#ifndef _CLINK_MEDIA_DIDLLITENODE_H_
#define _CLINK_MEDIA_DIDLLITENODE_H_

#include <cybergarage/upnp/media/server/object/DIDLLite.h>
#include <cybergarage/upnp/media/server/object/ContentNode.h>

namespace CyberLink {

class DIDLLiteNode : public CyberXML::Node // Thanks for Brent Hills (10/28/04)
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	DIDLLiteNode()
	{
		setName(DIDLLite::NAME);
		setAttribute(DIDLLite::XMLNS, DIDLLite::XMLNS_URL);
		setAttribute(DIDLLite::XMLNS_DC, DIDLLite::XMLNS_DC_URL);
		setAttribute(DIDLLite::XMLNS_UPNP, DIDLLite::XMLNS_UPNP_URL);
	}

	////////////////////////////////////////////////
	//	Child node
	////////////////////////////////////////////////

public:

	void addContentNode(ContentNode *node) 
	{
		addNode(node);
	}

	bool removeContentNode(ContentNode *node) 
	{
		return removeNode(node);
	}
};

}

#endif


