/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
**
*	File: FileItemNodeList.h
*
*	Revision;
*
*	04/14/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_FILEITEMNODELIST_H_
#define _CLINK_MEDIA_FILEITEMNODELIST_H_

#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/media/server/object/item/file/FileItemNode.h>

namespace CyberLink {

class FileItemNodeList : public uHTTP::Vector
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	FileItemNodeList() 
	{
	}
	
	~FileItemNodeList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	FileItemNode *getFileItemNode(int n)
	{
		return (FileItemNode *)Vector::get(n);
	}
	
	FileItemNode *getItemNode(uHTTP::File *file);

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif


