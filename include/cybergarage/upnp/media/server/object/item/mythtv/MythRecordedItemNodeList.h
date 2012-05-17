/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
**
*	File: MythRecordedItemNodeList.h
*
*	Revision;
*
*	06/07/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MYTHTV_RECORDEDITEMNODELIST_H_
#define _CLINK_MEDIA_MYTHTV_RECORDEDITEMNODELIST_H_

#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/media/server/object/item/mythtv/MythRecordedItemNode.h>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

namespace CyberLink {

class MythRecordedItemNodeList : public uHTTP::Vector
{
	bool delElemFlag;

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	MythRecordedItemNodeList(bool delElemFlag = true) 
	{
		this->delElemFlag = delElemFlag;
	}
	
	~MythRecordedItemNodeList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	MythRecordedItemNode *getRecordedItemNode(int n)
	{
		return (MythRecordedItemNode *)Vector::get(n);
	}
	
	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif

#endif


