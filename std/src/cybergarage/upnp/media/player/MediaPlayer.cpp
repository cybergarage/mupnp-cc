/******************************************************************
*
*	MediaPlayer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : MediaPlayer.cpp
*
*	04/20/04
*		- first revision.
*	05/19/04
*		- Changed the header include order for Cygwin.
*
******************************************************************/

#include <cybergarage/upnp/media/server/MediaServer.h>
#include <cybergarage/upnp/media/server/object/item/ItemNode.h>
#include <cybergarage/upnp/media/player/MediaPlayer.h>
#include <cybergarage/upnp/media/player/action/BrowseResult.h>
#include <cybergarage/upnp/media/player/action/BrowseResultNode.h>
#include <cybergarage/xml/XML.h>
#include <cybergarage/xml/Parser.h>
#include <cybergarage/util/Debug.h>

#include <string>
#include <fstream>


using namespace std;
using namespace CyberLink;
using namespace CyberNet;
using namespace CyberXML;
using namespace CyberUtil;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *MediaPlayer::DEVICE_TYPE = "urn:schemas-upnp-org:device:MediaRenderer:1";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
	
MediaPlayer::MediaPlayer()
{
}

MediaPlayer::~MediaPlayer()
{
}

////////////////////////////////////////////////
// start/stop
////////////////////////////////////////////////
	
bool MediaPlayer::start()
{
	return ControlPoint::start(/*MediaServer::DEVICE_TYPE*/);
}

bool MediaPlayer::stop()
{
	return ControlPoint::stop();
}

////////////////////////////////////////////////
// BrowseMetaData
////////////////////////////////////////////////

CyberXML::Node *MediaPlayer::browse(
Device *dev,
const char *objectID,
const char *browseFlag,
const char *filter,
int startIndex,
int requestedCount,
const char *sortCaiteria)
{
	if (dev == NULL)
		return NULL;
	Service *conDir = dev->getService(ContentDirectory::SERVICE_TYPE);
	if (conDir == NULL)
		return NULL;
	Action *action = conDir->getAction(ContentDirectory::BROWSE);
	if (action == NULL)
		return NULL;

	BrowseAction browseAction(action);
	browseAction.setObjectID(objectID);
	browseAction.setBrowseFlag(browseFlag);
	browseAction.setStartingIndex(startIndex);
	browseAction.setRequestedCount(requestedCount);
	browseAction.setFilter(filter);
	browseAction.setSortCriteria(sortCaiteria);
	if (browseAction.postControlAction() == false)
		return NULL;

	Argument *resultArg = browseAction.getArgument(BrowseAction::RESULT);
	if (resultArg == NULL)
		return NULL;

	const char *resultStr = resultArg->getValue();
	if (resultStr == NULL)
		return NULL;

	Node *node = NULL;

	Parser xmlParser;

	int resultUniStrLen;
	UnicodeStr *resultUniStr = XML::Local2Unicode(resultStr, resultUniStrLen);
	if (resultUniStr != NULL) {
		node = xmlParser.parse(resultUniStr, resultUniStrLen);
		delete []resultUniStr;
	}

	if (node == NULL)
		node = xmlParser.parse(resultStr);

	return node;
}

////////////////////////////////////////////////
// Content
////////////////////////////////////////////////

int MediaPlayer::getContentDirectory(ContentNode *parentNode, Device *dev, const char *objectID)
{
	if (objectID == NULL)
		return 0;

	CyberXML::Node *resultNode = browseDirectChildren(dev, objectID, "*", 0, 0, "");
	if (resultNode == NULL)
		return 0;

	BrowseResult browseResult(resultNode);
	//cout << browseResult.getNContentNodes() << endl;
	int nResultNode = 0;
	int nContents = browseResult.getNContentNodes();
	for (int n=0; n<nContents; n++) {
		Node *xmlNode = browseResult.getContentNode(n);
		ContentNode *contentNode = NULL;
		if (ContainerNode::isContainerNode(xmlNode) == true) {
			contentNode = new ContainerNode();
		}
		if (ItemNode::isItemNode(xmlNode) == true)
			contentNode = new BrowseResultNode();
		if (contentNode == NULL)
			continue;
		contentNode->set(xmlNode);
		parentNode->addContentNode(contentNode);
		nResultNode++;
		// Add Child Nodes
		if (contentNode->isContainerNode() == true) {
			ContainerNode *containerNode = (ContainerNode*)contentNode;
			int childCnt = containerNode->getChildCount();
			if (0 < childCnt) {
				const char *objid = containerNode->getID();
				getContentDirectory(contentNode, dev, objid);
			}
		}
	}
	delete resultNode;

	return nResultNode;
}

ContentNode *MediaPlayer::getContentDirectory(Device *dev)
{
	CyberXML::Node *rootNode = browseMetaData(dev, "0", "*", 0, 0, "");
	if (rootNode == NULL)
		return NULL;

	ContentNode *contentRootNode = new RootNode();
	contentRootNode->set(rootNode);
	delete rootNode;

	getContentDirectory(contentRootNode, dev, "0");
	if (Debug::isOn() == true)
		contentRootNode->print();

	return contentRootNode;
}
