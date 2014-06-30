/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : BrowseResult.h
*
*	Revision:
*
*	04/26/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_BROWSERESULT_H_
#define _CLINK_MEDIA_BROWSERESULT_H_

#include <cybergarage/xml/Node.h>

namespace CyberLink {

class BrowseResult
{
	CyberXML::Node *resultNode;

	////////////////////////////////////////////////
	// Constrictor
	////////////////////////////////////////////////
	
public:

	BrowseResult(CyberXML::Node *node)
	{
		setResultNode(node);
	}

	////////////////////////////////////////////////
	// Request
	////////////////////////////////////////////////

public:

	void setResultNode(CyberXML::Node *node)
	{
		resultNode = node;
	}

	CyberXML::Node *getResultNode()
	{
		return resultNode;
	}

	////////////////////////////////////////////////
	// ContentNode
	////////////////////////////////////////////////

public:

	int getNContentNodes()
	{
		return resultNode->getNNodes();
	}

	CyberXML::Node *getContentNode(int n)
	{
		return resultNode->getNode(n);
	}

};

}

#endif


