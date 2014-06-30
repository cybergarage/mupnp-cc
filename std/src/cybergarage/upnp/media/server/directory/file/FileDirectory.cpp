/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File : FileDirectory.cpp
*
*	Revision:
*
*	04/14/04
*		- first revision.
*	08/01/04
*		- Added <typeinfo> for typeid() for gcc 2.95.3.
*
******************************************************************/

#include <cybergarage/upnp/media/server/ContentDirectory.h>
#include <cybergarage/upnp/media/server/ConnectionManager.h>
#include <cybergarage/upnp/media/server/object/Format.h>
#include <cybergarage/upnp/media/server/object/FormatObject.h>
#include <cybergarage/upnp/media/server/directory/file/FileDirectory.h>
#include <cybergarage/io/FileList.h>

#include <typeinfo>
#include <sstream>

using namespace std;
using namespace CyberLink;
using namespace CyberIO;
using namespace CyberXML;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
	
FileDirectory::FileDirectory(const char *name, const char *path) : Directory(name)
{
	setPath(path);
}

////////////////////////////////////////////////
// create/updateItemNode
////////////////////////////////////////////////

bool FileDirectory::updateItemNode(FileItemNode *itemNode,  CyberIO::File *file)
{
	Format *format = getContentDirectory()->getFormat(file);
	if (format == NULL)
		return false;
	FormatObject *formatObj = format->createObject(file);
		
	// File/TimeStamp
	itemNode->setFile(file);
		
	// Title
	string title;
	formatObj->getTitle(title);
	if (0 < title.length())
		itemNode->setTitle(title.c_str());
			
	// Creator
	string creator;
	formatObj->getCreator(creator);
	if (0 < creator.length())
		itemNode->setCreator(creator.c_str());

	// Media Class
	string mediaClass = format->getMediaClass();
	if (0 < mediaClass.length())
		itemNode->setUPnPClass(mediaClass.c_str());

	// Date
	long lastModTime = file->lastModified();
	itemNode->setDate(lastModTime);
		
	// Storatge Used
	long fileSize = file->length();
	itemNode->setStorageUsed(fileSize);	
		
	// ProtocolInfo
	string mimeType = format->getMimeType();
	ostringstream protocolBuf;
	protocolBuf << ConnectionManager::HTTP_GET << ":*:" << mimeType << ":*";
	string protocol = protocolBuf.str();
	// = ConnectionManager.HTTP_GET + ":*:" + mimeType + ":*";
	const char *id = itemNode->getID();
	string url;
	getContentDirectory()->getContentExportURL(id, url);
	AttributeList objAttrList;
	formatObj->getAttributeList(objAttrList);
	itemNode->setResource(url.c_str(), protocol.c_str(), &objAttrList);
		
	// Update SystemUpdateID
	getContentDirectory()->updateSystemUpdateID();
		
	return true;
}

FileItemNode *FileDirectory::createCompareItemNode(CyberIO::File *file)
{
	Format *format = getContentDirectory()->getFormat(file);
	if (format == NULL)
		return NULL;
	FileItemNode *itemNode = new FileItemNode();
	itemNode->setFile(file);
	return itemNode;
}

////////////////////////////////////////////////
// FileList
////////////////////////////////////////////////
	
int FileDirectory::getDirectoryItemNodeList(CyberIO::File *dirFile, FileItemNodeList &itemNodeList)
{
	FileList fileList;
	int fileCnt = dirFile->listFiles(fileList);
	for (int n=0; n<fileCnt; n++) {
		File *file = fileList.getFile(n);
		if (file->isDirectory() == true) {
			getDirectoryItemNodeList(file, itemNodeList);
			continue;
		}
		if (file->isFile() == true) {
			File *itemFile = new File(file);
			FileItemNode *itemNode = createCompareItemNode(itemFile);
			if (itemNode == NULL)
				continue;						
			itemNodeList.add(itemNode);
		}
	}
	return itemNodeList.size();
}
	
int FileDirectory::getCurrentDirectoryItemNodeList(FileItemNodeList &itemNodeList)
{
	File pathFile(getPath());
	getDirectoryItemNodeList(&pathFile, itemNodeList);
	return itemNodeList.size();
}

////////////////////////////////////////////////
// updateItemNodeList
////////////////////////////////////////////////
	
FileItemNode *FileDirectory::getItemNode(CyberIO::File *file)
{
	int nContents = getNContentNodes();
	for (int n=0; n<nContents; n++) {
		ContentNode *cnode = getContentNode(n);
		if (typeid(cnode) != typeid(FileItemNode))
			continue;
		FileItemNode *itemNode = (FileItemNode *)cnode;
		if (itemNode->equals(file) == true)
			return itemNode;
	}
	return NULL;
}
	
bool FileDirectory::updateItemNodeList(FileItemNode *newItemNode)
{
	File *newItemNodeFile = newItemNode->getFile();
	FileItemNode *currItemNode = getItemNode(newItemNodeFile);
	if (currItemNode == NULL) {
		FileItemNode *addNewItemNode = createCompareItemNode(newItemNodeFile);
		int newItemID = getContentDirectory()->getNextItemID();
		addNewItemNode->setID(newItemID);
		updateItemNode(addNewItemNode, newItemNodeFile);
		addItemNode(addNewItemNode);
		return true;
	}
		
	long currTimeStamp = currItemNode->getFileTimeStamp();
	long newTimeStamp = newItemNode->getFileTimeStamp();
	if (currTimeStamp == newTimeStamp)
		return false;
			
	updateItemNode(currItemNode, newItemNodeFile);
	
	return true;
}
	
void FileDirectory::updateItemNodeList()
{
	bool updateFlag = false;
	int n;

	// Checking Deleted Items
	int nContents = getNContentNodes();
	ContentNode **cnode = new ContentNode*[nContents];
	for (n=0; n<nContents; n++)
		cnode[n] = getContentNode(n);
	for (n=0; n<nContents; n++) {
		if (typeid(cnode[n]) != typeid(FileItemNode))
			continue;
		FileItemNode *itemNode = (FileItemNode*)cnode[n];
		File *itemFile = itemNode->getFile();
		if (itemFile == NULL)
			continue;
		if (itemFile->exists() == false) {
			removeContentNode(cnode[n]);
			delete cnode[n];
			updateFlag = true;
		}
	}
	delete []cnode;
		
	// Checking Added or Updated Items
	FileItemNodeList itemNodeList;
	int itemNodeCnt = getCurrentDirectoryItemNodeList(itemNodeList);
	for (n=0; n<itemNodeCnt; n++) {
		FileItemNode *itemNode = itemNodeList.getFileItemNode(n);
		if (updateItemNodeList(itemNode) == true)
			updateFlag = true;
	}
		
	nContents = getNContentNodes();
	setChildCount(nContents);
		
	if (updateFlag == true)
		getContentDirectory()->updateSystemUpdateID();
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////
	
void FileDirectory::update()
{
	updateItemNodeList();
}

