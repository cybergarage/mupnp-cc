/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : DIDLLite.h
*
*	Revision:
*
*	10/22/03
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_DIDLLITE_H_
#define _CLINK_MEDIA_DIDLLITE_H_

#include <string>
#include <iostream>
#include <sstream>

#include <cybergarage/upnp/media/server/object/ContentNodeList.h>

namespace CyberLink {

class DIDLLite
{
	ContentNodeList *nodeList;

	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////

public:

	static const char *NAME;
	static const char *XMLNS;
	static const char *XMLNS_URL;
	static const char *XMLNS_DC;
	static const char *XMLNS_DC_URL;
	static const char *XMLNS_UPNP;
	static const char *XMLNS_UPNP_URL;

	static const char *CONTAINER;
	static const char *ID;
	static const char *SEARCHABLE;
	static const char *PARENTID;
	static const char *RESTICTED;
	
	static const char *OBJECT_CONTAINER;

	static const char *RES;
	static const char *RES_PROTOCOLINFO;
	
	////////////////////////////////////////////////
	// Constrictor
	////////////////////////////////////////////////
	
public:

	DIDLLite(bool delElemFlag = true);

	~DIDLLite();

	////////////////////////////////////////////////
	//	ContentNode
	////////////////////////////////////////////////

public:

	void setContentNode(ContentNode *node)
	{
		nodeList->clear();
		nodeList->add(node);
	}
	
	void addContentNode(ContentNode *node)
	{
		nodeList->add(node);
	}
	
	int getNContentNodes()
	{
		return nodeList->size();
	}
	
	ContentNode *getContentNode(int n)
	{
		return nodeList->getContentNode(n);
	}

	////////////////////////////////////////////////
	//	toString
	////////////////////////////////////////////////

public:

	void output(std::ostream& ps);

	const char *toString(std::string &buf);
	const char *toUnicodeString(std::string &buf);
};

}

#endif
