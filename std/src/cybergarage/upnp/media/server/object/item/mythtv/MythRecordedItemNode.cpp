/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : MythRecordedItemNode.cpp
*
*	Revision:
*
*	06/07/04
*		- first revision.
*	08/10/04
*		- Changed the mime type to video/mpeg.
*		- Added the size attribure to the protocolInfo.
*
******************************************************************/

#include <cybergarage/upnp/media/server/ContentDirectory.h>
#include <cybergarage/upnp/media/server/ConnectionManager.h>
#include <cybergarage/upnp/media/server/object/item/mythtv/MythRecordedItemNode.h>
#include <cybergarage/io/File.h>
#include <string>
#include <sstream>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

using namespace std;
using namespace CyberIO;
using namespace CyberLink;
using namespace CyberXML;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

//const char *MythRecordedItemNode::MIME_TYPE = "*/*";
const char *MythRecordedItemNode::MIME_TYPE = "video/mpeg";

////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////

MythRecordedItemNode::MythRecordedItemNode()
{
}

MythRecordedItemNode::~MythRecordedItemNode()
{
}

////////////////////////////////////////////////
// RecordedInfo
////////////////////////////////////////////////

void MythRecordedItemNode::setRecordedInfo(MythRecordedInfo *info)
{
	if (info == NULL)
		return;

	recInfo.set(info);

	// Title
	setTitle(info->getTitle());

	// Creator
	setCreator("");

	// Media Class
	setUPnPClass(UPnP::OBJECT_ITEM_VIDEOITEM_MOVIE);

	// Date
	setDate(info->getStartTime());

	// Storatge Used
	string recFileName;
	info->getFileName(recFileName);
	File recFile(recFileName.c_str());
	long fileSize = recFile.length();
	setStorageUsed(fileSize);

	// ProtocolInfo
	ostringstream protocol;
	protocol << ConnectionManager::HTTP_GET << ":*:" << MIME_TYPE << ":*";
	const char *id = getID();
	string url;
	getContentDirectory()->getContentExportURL(id, url);
	ostringstream sizeAttrStr;
	sizeAttrStr << fileSize;
	AttributeList attrList;
	Attribute *attr = new Attribute(ItemNode::SIZE, sizeAttrStr.str().c_str());
	attrList.add(attr);
	setResource(url.c_str(), protocol.str().c_str(), &attrList);
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool MythRecordedItemNode::equals(MythRecordedInfo *info)
{
	MythRecordedInfo *recInfo = getRecordedInfo();
	if (info == NULL || recInfo == NULL)
		return false;
	if (info->getChanID() == recInfo->getChanID())
		return true;
	return false;
}

////////////////////////////////////////////////
// Abstract methods
////////////////////////////////////////////////

const char *MythRecordedItemNode::getContent(std::string &buf)
{
	string recFileName;
	recInfo.getFileName(recFileName);
	File recFile(recFileName.c_str());
	recFile.load(buf);
	return buf.c_str();
}

CyberIO::InputStream *MythRecordedItemNode::getContentInputStream()
{
	string recFileName;
	recInfo.getFileName(recFileName);
	File recFile(recFileName.c_str());
	return new FileInputStream(&recFile, File::O_BINARY);
}

long MythRecordedItemNode::getContentLength()
{
	string recFileName;
	recInfo.getFileName(recFileName);
	File recFile(recFileName.c_str());
	return recFile.length();
}

const char *MythRecordedItemNode::getMimeType()
{
	return MIME_TYPE;
}

#endif
