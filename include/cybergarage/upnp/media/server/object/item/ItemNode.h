/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : ItemNode.h
*
*	Revision:
*
*	03/31/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITEMNODE_H_
#define _CLINK_MEDIA_ITEMNODE_H_

#include <cybergarage/io/InputStream.h>
#include <cybergarage/util/Vector.h>
#include <cybergarage/xml/AttributeList.h>
#include <cybergarage/upnp/media/server/DC.h>
#include <cybergarage/upnp/media/server/UPnP.h>
#include <cybergarage/upnp/media/server/object/DIDLLite.h>
#include <cybergarage/upnp/media/server/object/ContentNode.h>

namespace CyberLink {

class ItemNode : public ContentNode
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////

public:

	static const char *NAME;

	static const char *RES;
	
	static const char *PROTOCOL_INFO;
	
	static const char *SIZE;
	static const char *IMPORT_URI;
	static const char *COLOR_DEPTH;
	static const char *RESOLUTION;
	
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	ItemNode();

	////////////////////////////////////////////////
	// isItemNode
	////////////////////////////////////////////////

public:

	static bool isItemNode(CyberXML::Node *node);

	////////////////////////////////////////////////
	//	Child node
	////////////////////////////////////////////////

public:

	void addContentNode(ContentNode *node);
	bool removeContentNode(ContentNode *node);

	////////////////////////////////////////////////
	// dc:date
	////////////////////////////////////////////////

public:

	void setDate(const char *value)
	{
		setProperty(DC::DATE, value);
	}
	
	const char *getDate()
	{
		return getPropertyValue(DC::DATE);
	}

	void setDate(long dateTime);

	long getDateTime();

	////////////////////////////////////////////////
	// dc:creator
	////////////////////////////////////////////////
	
public:

	void setCreator(const char *name)
	{
		setProperty(DC::CREATOR, name);
	}
	
	const char *getCreator()
	{
		return getPropertyValue(DC::CREATOR);
	}
	
	////////////////////////////////////////////////
	// upnp:storageMedium
	////////////////////////////////////////////////
	
public:

	void setStorageMedium(const char *value)
	{
		setProperty(UPnP::STORAGE_MEDIUM, value);
	}
	
	const char *getStorageMedium()
	{
		return getPropertyValue(UPnP::STORAGE_MEDIUM);
	}

	////////////////////////////////////////////////
	// upnp:storageUsed
	////////////////////////////////////////////////
	
public:

	void setStorageUsed(long value)
	{
		setProperty(UPnP::STORAGE_USED, value);
	}
	
	long getStorageUsed()
	{
		return getPropertyLongValue(UPnP::STORAGE_USED);
	}

	////////////////////////////////////////////////
	// Res
	////////////////////////////////////////////////
	
public:

	void setResource(const char *url, const char *protocolInfo, CyberXML::AttributeList *attrList);

	void setResource(const char *url, const char *protocolInfo)
	{
		CyberXML::AttributeList attrList;
		setResource(url, protocolInfo, &attrList);
	}

public:

	const char *getResource()
	{
		return getPropertyValue(DIDLLite::RES);
	}
	
	const char *getProtocolInfo()
	{
		return getPropertyAttribureValue(DIDLLite::RES, DIDLLite::RES_PROTOCOLINFO);
	}
		
	////////////////////////////////////////////////
	// Abstract methods
	////////////////////////////////////////////////

public:

	//virtual const char *getContent() = 0;
	virtual long getContentLength() = 0;
	virtual CyberIO::InputStream *getContentInputStream() = 0;
	virtual const char *getMimeType() = 0;
	
};

}

#endif


