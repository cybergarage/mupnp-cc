/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: MythDirectory.cpp
*
*	Revision:
*
*	06/07/04
*		- first revision.
*	06/29/04
*		- Fixed to abort when the update() is executed.
*
******************************************************************/

#include <cybergarage/upnp/media/server/ContentDirectory.h>
#include <cybergarage/upnp/media/server/directory/mythtv/MythDirectory.h>
#include <cybergarage/upnp/media/server/directory/mythtv/MythDatabase.h>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *MythDirectory::NAME = "MythTV";
	
////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
	
MythDirectory::MythDirectory(const char *name) : Directory(name)
{
}

MythDirectory::MythDirectory() : Directory(NAME)
{
}

////////////////////////////////////////////////
// get*
////////////////////////////////////////////////

int MythDirectory::getAddedRecordedItemNodes(MythRecordedItemNodeList &nodeList)
{
	int nContents = getNContentNodes();
	for (int n=0; n<nContents; n++)
		nodeList.add((MythRecordedItemNode *)getContentNode(n));
	return nodeList.size();		
}		

int MythDirectory::getCurrentRecordedInfos(MythRecordedInfoList &infoList)
{
	MythDatabase mythdb;
	mythdb.open();
	mythdb.getRecordedInfos(infoList);
	mythdb.close();
	return infoList.size();
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////

void MythDirectory::update()
{
	int i, j;
	bool updateFlag = false;

	MythRecordedItemNodeList addedItemNodeList(false);
	int nAddedItems = getAddedRecordedItemNodes(addedItemNodeList);
	MythRecordedInfoList currRecInfoList;
	int nCurrRecInfos = getCurrentRecordedInfos(currRecInfoList);
		
	// Checking Deleted Items
	for (i=0; i<nAddedItems; i++) {
		MythRecordedItemNode *recItem = addedItemNodeList.getRecordedItemNode(i);
		bool hasRecItem = false;
		for (int j=0; j<nCurrRecInfos; j++) {
			MythRecordedInfo *recInfo = currRecInfoList.getRecordedInfo(j);
			if (recItem->equals(recInfo) == true) {
				hasRecItem = true;
				break;
			}
		}
		if (hasRecItem == true)
			continue;
		removeContentNode(recItem);
		updateFlag = true;
	}
		
	// Checking Added Items
	for (j=0; j<nCurrRecInfos; j++) {
		MythRecordedInfo *recInfo = currRecInfoList.getRecordedInfo(j);
		bool hasRecItem = false;
		for (i=0; i<nAddedItems; i++) {
			MythRecordedItemNode *recItem = addedItemNodeList.getRecordedItemNode(i);
			if (recItem->equals(recInfo) == true) {
				hasRecItem = true;
				break;
			}
		}
		if (hasRecItem == true)
			continue;
		
		// Add new item.
		MythRecordedItemNode *recItem = new MythRecordedItemNode();
		int newItemID = getContentDirectory()->getNextItemID();
		recItem->setID(newItemID);
		recItem->setContentDirectory(getContentDirectory());
		recItem->setRecordedInfo(recInfo);
		addContentNode(recItem);
		updateFlag = true;
	}
		
	int nContents = getNContentNodes();
	setChildCount(nContents);
		
	if (updateFlag == true)
		getContentDirectory()->updateSystemUpdateID();
}

#endif
