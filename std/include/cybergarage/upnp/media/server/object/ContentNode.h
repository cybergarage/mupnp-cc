/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File : ContentNode.h
*
*	Revision:
*
*	03/14/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_CONTENTNODE_H_
#define _CLINK_MEDIA_CONTENTNODE_H_

#include <stdlib.h>

#include <string>
#include <sstream>
#include <iostream>

#include <cybergarage/xml/Node.h>
#include <cybergarage/upnp/media/server/UPnP.h>
#include <cybergarage/upnp/media/server/DC.h>
#include <cybergarage/upnp/media/server/object/ContentPropertyList.h>

namespace CyberLink {

class ItemNode;
class ContainerNode;
class ContentDirectory;

class ContentNode : public CyberXML::Node
{
	ContentDirectory *contentDir;
	ContentPropertyList propList;
	
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////

public:

	static const char *ID;
	static const char *PARENT_ID;
	static const char *RESTRICTED;
	static const char *UNKNOWN;
	
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	ContentNode();
	virtual ~ContentNode();

	////////////////////////////////////////////////
	// ContentDirectory
	////////////////////////////////////////////////

public:

	void setContentDirectory(ContentDirectory *cdir)
	{
		contentDir = cdir;
	}
	
	ContentDirectory *getContentDirectory()
	{
		return contentDir;
	}

/*
	public MediaServer getMediaServer()
	{
		return getContentDirectory().getMediaServer();
	}
*/
	
	////////////////////////////////////////////////
	// is*Node
	////////////////////////////////////////////////

public:

	bool isContainerNode();

	bool isItemNode();
	
	////////////////////////////////////////////////
	//	Child node
	////////////////////////////////////////////////

public:

	bool hasContentNodes()
	{
		return hasNodes();
	}
	
	bool hasContainerNodes();
	
	bool hasItemNodes();
	
	int getNContentNodes() 
	{
		return getNNodes();
	}

	ContentNode *getContentNode(int index) 
	{
		return (ContentNode *)getNode(index);
	}

	ContentNode *getContentNode(const char *name) 
	{
		return (ContentNode *)getNode(name);
	}
	
	virtual void addContentNode(ContentNode *node) = 0;
	virtual bool removeContentNode(ContentNode *node) = 0;
	
	void removeAllContentNodes()
	{
		removeAllNodes();	
	}
	
	////////////////////////////////////////////////
	//	Property (Basic)
	////////////////////////////////////////////////

public:

	int getNProperties() {
		return (int)propList.size();
	}

	ContentProperty *getProperty(int index) {
		return propList.getContentProperty(index);
	}

	ContentProperty *getProperty(const char *name) 
	{
		return propList.getContentProperty(name);
	}

	void addProperty(ContentProperty *prop) {
		propList.addContentProperty(prop);
	}

	void insertPropertyAt(ContentProperty *prop, int index) {
		propList.insertContentProperty(prop, index);
	}

	void addProperty(const char *name, const char *value) {
		ContentProperty *prop = new ContentProperty(name, value);
		addProperty(prop);
	}

	bool removeProperty(ContentProperty *prop) {
		return propList.removeContentProperty(prop);
	}

	bool removeProperty(const char *name) {
		return removeProperty(getProperty(name));
	}

	bool hasProperties()
	{
		if (0 < getNProperties())
			return true;
		return false;
	}
	
	////////////////////////////////////////////////
	//	Property (Extention)
	////////////////////////////////////////////////

public:

	void setProperty(const char *name, const char *value) {
		ContentProperty *prop = getProperty(name);
		if (prop != NULL) {
			prop->setValue(value);
			return;
		}
		prop = new ContentProperty(name, value);
		addProperty(prop);
	}

	void setProperty(const char *name, int value) {
		std::ostringstream valBuf;
		valBuf << value;
		std::string valStr = valBuf.str();
		setProperty(name, valStr.c_str());
	}

	void setProperty(const char *name, long value) {
		std::ostringstream valBuf;
		valBuf << value;
		std::string valStr = valBuf.str();
		setProperty(name, valStr.c_str());
	}

	const char *getPropertyValue(const char *name) {
		ContentProperty *prop = getProperty(name);
		if (prop != NULL)
			return prop->getValue();
		return "";
	}

	int getPropertyIntegerValue(const char *name) {
		const char *val = getPropertyValue(name);
		if (val == NULL)
			return 0;
		return atoi(val);
	}

	long getPropertyLongValue(const char *name) {
		const char *val = getPropertyValue(name);
		if (val == NULL)
			return 0;
		return atol(val);
	}

	////////////////////////////////////////////////
	//	Property Attribute (Extention)
	////////////////////////////////////////////////

public:

	void setPropertyAttribure(const char *propName, const char *attrName, const char *value) 
	{
		ContentProperty *prop = getProperty(propName);
		if (prop == NULL) {
			prop = new ContentProperty(propName, "");
			addProperty(prop);
		}
		prop->setAttribute(attrName, value);
	}

	const char *getPropertyAttribureValue(const char *propName, const char *attrName) 
	{
		ContentProperty *prop = getProperty(propName);
		if (prop != NULL)
			return prop->getAttributeValue(attrName);
		return "";
	}

	////////////////////////////////////////////////
	//	findContentNodeBy*
	////////////////////////////////////////////////

public:

	ContentNode *findContentNodeByID(const char *conId);
	
	////////////////////////////////////////////////
	// ID
	////////////////////////////////////////////////
	
public:

	void setID(int conId)
	{
		setAttribute(ID, conId);
	}

	void setID(const char *conId)
	{
		setAttribute(ID, conId);
	}
	
	const char *getID()
	{
		return getAttributeValue(ID);
	}

	////////////////////////////////////////////////
	// parentID
	////////////////////////////////////////////////
	
public:

	void setParentID(int parentId)
	{
		setAttribute(PARENT_ID, parentId);
	}
	
	void setParentID(const char *parentId)
	{
		setAttribute(PARENT_ID, parentId);
	}

	const char *getParentID()
	{
		return getAttributeValue(PARENT_ID);
	}

	////////////////////////////////////////////////
	// parentID
	////////////////////////////////////////////////
	
public:

	void setRestricted(int restID)
	{
		setAttribute(RESTRICTED, restID);
	}
	
	int getRestricted()
	{
		return getAttributeIntegerValue(RESTRICTED);
	}

	////////////////////////////////////////////////
	// dc:title
	////////////////////////////////////////////////
	
public:

	void setTitle(const char *title)
	{
		setProperty(DC::TITLE, title);
	}
	
	const char *getTitle()
	{
		return getPropertyValue(DC::TITLE);
	}

	////////////////////////////////////////////////
	// upnp:class
	////////////////////////////////////////////////

public:

	void setUPnPClass(const char *title)
	{
		setProperty(UPnP::CLASS, title);
	}
	
	const char *getUPnPClass()
	{
		return getPropertyValue(UPnP::CLASS);
	}

	////////////////////////////////////////////////
	// upnp:writeStatus
	////////////////////////////////////////////////

public:

	void setWriteStatus(const char *status)
	{
		setProperty(UPnP::WRITE_STATUS, status);
	}
	
	const char *getWriteStatus()
	{
		return getPropertyValue(UPnP::WRITE_STATUS);
	}

	////////////////////////////////////////////////
	// set
	////////////////////////////////////////////////
	
public:

	void set(CyberXML::Node *node);

	////////////////////////////////////////////////
	//	toString 
	////////////////////////////////////////////////

private:
	
	void outputPropertyAttributes(std::ostream& ps, ContentProperty *prop);

public:

	void output(std::ostream& ps, int indentLevel, bool hasChildNode);

};

}

#endif


