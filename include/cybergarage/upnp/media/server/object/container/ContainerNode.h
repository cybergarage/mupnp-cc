/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : ContentNode.h
*
*	Revision:
*
*	03/23/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_CONTAINERNODE_H_
#define _CLINK_MEDIA_CONTAINERNODE_H_

#include <cybergarage/upnp/media/server/object/ContentNode.h>

namespace CyberLink {

class ContainerNode : public ContentNode
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////

	static const char *NAME;

	static const char *CHILD_COUNT;
	static const char *SEARCHABLE;

	static const char *OBJECT_CONTAINER;

	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	ContainerNode();

	////////////////////////////////////////////////
	// isContainerNode
	////////////////////////////////////////////////

public:

	static bool isContainerNode(CyberXML::Node *node);

	////////////////////////////////////////////////
	//	Child node
	////////////////////////////////////////////////

public:

	void addContentNode(ContentNode *node);
	bool removeContentNode(ContentNode *node);

	////////////////////////////////////////////////
	// chileCount
	////////////////////////////////////////////////
	
public:
	
	void setChildCount(int count)
	{
		setAttribute(CHILD_COUNT, count);
	}
	
	int getChildCount()
	{
		return getAttributeIntegerValue(CHILD_COUNT);
	}

	////////////////////////////////////////////////
	// searchable
	////////////////////////////////////////////////
	
public:

	void setSearchable(int value)
	{
		setAttribute(SEARCHABLE, value);
	}
	
	int getSearchable()
	{
		return getAttributeIntegerValue(SEARCHABLE);
	}
	
};

}

#endif


