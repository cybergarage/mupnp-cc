/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: ContentNodeList.h
*
*	Revision;
*
*	03/23/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_CONTENTNODELIST_H_
#define _CLINK_MEDIA_CONTENTNODELIST_H_

#include <cybergarage/util/Vector.h>
#include <cybergarage/upnp/media/server/object/ContentNode.h>

namespace CyberLink {

class ContentNodeList : public CyberUtil::Vector
{
	bool delElemFlag;

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	ContentNodeList(bool delElemFlag = true) 
	{
		this->delElemFlag = delElemFlag;
	}

	~ContentNodeList() 
	{
		clear();
	}
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	ContentNode *getContentNode(int n)
	{
		return (ContentNode *)Vector::get(n);
	}

	ContentNode *getContentNode(const char *name);

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif


