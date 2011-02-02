/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File : FileDirectory.h
*
*	Revision:
*
*	04/14/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_FILE_DIRECTORY_H_
#define _CLINK_MEDIA_FILE_DIRECTORY_H_

#include <string>
#include <cybergarage/io/File.h>
#include <cybergarage/upnp/media/server/Directory.h>
#include <cybergarage/upnp/media/server/object/item/file/FileItemNode.h>
#include <cybergarage/upnp/media/server/object/item/file/FileItemNodeList.h>

namespace CyberLink {

class FileDirectory : public Directory
{
	std::string path;
	
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:

	FileDirectory(const char *name, const char *path);
	
	////////////////////////////////////////////////
	// Path
	////////////////////////////////////////////////

public:

	void setPath(const char *value)
	{
		path = value;		
	}
	
	const char *getPath()
	{
		return path.c_str();
	}

	////////////////////////////////////////////////
	// create/updateItemNode
	////////////////////////////////////////////////

private:

	bool updateItemNode(FileItemNode *itemNode, CyberIO::File *file);
	FileItemNode *createCompareItemNode(CyberIO::File *file);
	
	////////////////////////////////////////////////
	// FileList
	////////////////////////////////////////////////

private:

	int getDirectoryItemNodeList(CyberIO::File *dirFile, FileItemNodeList &itemNodeList);
	int getCurrentDirectoryItemNodeList(FileItemNodeList &fileNodeList);

	////////////////////////////////////////////////
	// updateItemNodeList
	////////////////////////////////////////////////

private:

	FileItemNode *getItemNode(CyberIO::File *file);

	void addItemNode(FileItemNode *itemNode)
	{
		addContentNode(itemNode);
	}
	
	bool updateItemNodeList(FileItemNode *newItemNode);
	void updateItemNodeList();

	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////
	
public:

	void update();
};

}

#endif


