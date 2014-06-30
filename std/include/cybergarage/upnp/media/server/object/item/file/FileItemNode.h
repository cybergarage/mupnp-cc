/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : FileItemNode.java
*
*	Revision:
*
*	02/12/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_FILEITEMNODE_H_
#define _CLINK_MEDIA_FILEITEMNODE_H_

#include <cybergarage/io/File.h>
#include <cybergarage/io/FileInputStream.h>
#include <cybergarage/upnp/media/server/object/item/ItemNode.h>

namespace CyberLink {

class FileItemNode : public ItemNode
{
	CyberIO::File *itemFile;

	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	FileItemNode();

	////////////////////////////////////////////////
	// File/TimeStamp
	////////////////////////////////////////////////
	
public:

	void setFile(CyberIO::File *file)
	{
		itemFile = file;
	}
	
	CyberIO::File *getFile()
	{
		return itemFile;
	}

	long getFileTimeStamp()
	{
		return itemFile->lastModified();
	}
	
	bool equals(CyberIO::File *file)
	{
		if (itemFile == NULL)
			return false;
		return itemFile->equals(file);
	}

	////////////////////////////////////////////////
	// Abstract methods
	////////////////////////////////////////////////

public:

	const char *getContent(std::string &buf);
	
	long getContentLength()
	{
		return itemFile->length();
	}

	CyberIO::InputStream *getContentInputStream();

	const char *getMimeType();
};

}

#endif


