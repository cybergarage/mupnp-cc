/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : ItemNode.cpp
*
*	Revision:
*
*	03/31/04
*		- first revision.
*	04/26/04
*		- Added isItemNode().
*	08/01/04
*		- Added <stdio.h> for sprintf() for gcc 2.95.3.
*	10/24/04 
*		- Lorenzo Vicisano <lorenzo@vicisano.net>
*		- Changed DATE_FORMAT for FreeBSD.
*
******************************************************************/

#include <cybergarage/util/Date.h>
#include <cybergarage/upnp/media/server/object/item/ItemNode.h>

#include <string>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

using namespace std;
using namespace CyberUtil;
using namespace CyberLink;
using namespace CyberXML;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *ItemNode::NAME = "item";

const char *ItemNode::RES = "res";
	
const char *ItemNode::PROTOCOL_INFO = "protocolInfo";
	
const char *ItemNode::SIZE = "size";
const char *ItemNode::IMPORT_URI = "importUri";
const char *ItemNode::COLOR_DEPTH = "colorDepth";
const char *ItemNode::RESOLUTION = "resolution";

////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////
	
ItemNode::ItemNode()
{
	setID(-1);
	setName(NAME);
	setStorageMedium(UNKNOWN);
	setWriteStatus(UNKNOWN);
}

////////////////////////////////////////////////
// isItemNode
////////////////////////////////////////////////

bool ItemNode::isItemNode(CyberXML::Node *node)
{
	const char *name = node->getName();
	if (name == NULL)
		return false;
	string nameStr = name;
	return (nameStr.compare(NAME) == 0) ? true : false;
}

////////////////////////////////////////////////
//	Child node
////////////////////////////////////////////////

void ItemNode::addContentNode(ContentNode *node) 
{
	addNode(node);
	node->setParentID(getID());
	node->setContentDirectory(getContentDirectory());
}

bool ItemNode::removeContentNode(ContentNode *node) 
{
	return removeNode(node);
}

////////////////////////////////////////////////
// dc:date
////////////////////////////////////////////////

// Thanks for Lorenzo Vicisano (10/24/04)
static const char DATE_FORMAT[] = "yyyy-MM-dd";
	
void ItemNode::setDate(long dateTime)
{	
	Date date(dateTime);
	char dateStr[sizeof(DATE_FORMAT)+1];
	sprintf(dateStr, "%04d-%02d-%02d",
			date.getYear(),
			date.getMonth(),
			date.getDay());
	setDate(dateStr);
}

long ItemNode::getDateTime()
{
	string dateStr = getDate();
	if (dateStr.length() < 10)
		return 0;
	int year, month, day;
	if (sscanf(dateStr.c_str(), "%04d-%02d-%02d", &year, &month, &day) != 3)
			return 0;
	struct tm timetm; 
	timetm.tm_sec = 0;
	timetm.tm_min = 0;
	timetm.tm_hour = 0;
	timetm.tm_mday = day;
	timetm.tm_mon = month;
	timetm.tm_year = year - 1900;
	timetm.tm_wday = 0;
	timetm.tm_yday = 0;
	timetm.tm_isdst = 0; 
	return mktime(&timetm);
}


////////////////////////////////////////////////
// Res
////////////////////////////////////////////////

void ItemNode::setResource(const char *url, const char *protocolInfo, CyberXML::AttributeList *attrList)
{
	setProperty(DIDLLite::RES, url);
	
	setPropertyAttribure(DIDLLite::RES, DIDLLite::RES_PROTOCOLINFO, protocolInfo);
	int attrCnt = attrList->size();
	for (int n=0; n<attrCnt; n++) {		
		Attribute *attr = attrList->getAttribute(n);
		string name = attr->getName();
		string value = attr->getValue();
		setPropertyAttribure(DIDLLite::RES, name.c_str(), value.c_str());			
	}
}
