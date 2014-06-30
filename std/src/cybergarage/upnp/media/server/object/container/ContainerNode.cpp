/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: ContainerNode.cpp
*
*	Revision;
*
*	03/23/04
*		- first revision
*	04/26/04
*		- Added isContainerNode().
*	04/27/04
*		- Added set(Node *).
*	04/27/04
*		- Added setParentID(String).
*		- Changed getParentID() to return the string value instead of interger.
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/container/ContainerNode.h>

using namespace std;
using namespace CyberLink;
using namespace CyberXML;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *ContainerNode::NAME = "container";

const char *ContainerNode::CHILD_COUNT = "childCount";
const char *ContainerNode::SEARCHABLE = "searchable";

const char *ContainerNode::OBJECT_CONTAINER = "object.container";

////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////

ContainerNode::ContainerNode()
{
	setID(-1);
	setName(NAME);
	setSearchable(0);
	setChildCount(0);
	setUPnPClass(OBJECT_CONTAINER);
	setWriteStatus(UNKNOWN);
}

////////////////////////////////////////////////
// isContainerNode
////////////////////////////////////////////////

bool ContainerNode::isContainerNode(CyberXML::Node *node)
{
	const char *name = node->getName();
	if (name == NULL)
		return false;
	string nameStr = name;
	return (nameStr.compare(NAME) == 0) ? true : false;
}

////////////////////////////////////////////////
//	Child node
////////////////////////////////////////////////

void ContainerNode::addContentNode(ContentNode *node) 
{
	addNode(node);
	node->setParentID(getID());
	setChildCount(getNContentNodes());
	node->setContentDirectory(getContentDirectory());
}

bool ContainerNode::removeContentNode(ContentNode *node) 
{
	bool ret = removeNode(node);
	setChildCount(getNContentNodes());
	return ret;
}

