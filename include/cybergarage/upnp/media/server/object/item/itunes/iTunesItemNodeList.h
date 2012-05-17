/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
**
*	File: iTunesItemNodeList.h
*
*	Revision;
*
*	03/14/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNESITEMNODELIST_H_
#define _CLINK_MEDIA_ITUNESITEMNODELIST_H_

#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/media/server/object/item/itunes/iTunesItemNode.h>

namespace CyberLink {

class iTunesItemNodeList : public uHTTP::Vector
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	iTunesItemNodeList() 
	{
	}
	
	~iTunesItemNodeList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	iTunesItemNode *getiTunesItemNode(int n)
	{
		return (iTunesItemNode *)Vector::get(n);
	}
	
	iTunesItemNode *getItemNode(uHTTP::File *file);

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif


