/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File: ContentProperty.h
*
*	Revision;
*
*	03/14/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_CONTENTPROPERTY_H_
#define _CLINK_MEDIA_CONTENTPROPERTY_H_

#include <stdlib.h>

#include <string>
#include <sstream>
#include <cybergarage/xml/AttributeList.h>

namespace CyberLink {

class ContentProperty
{
	std::string name; 
	std::string value; 

	CyberXML::AttributeList attrList;

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	ContentProperty() 
	{
	}

	ContentProperty(const char *name, const char *value) 
	{
		setName(name);
		setValue(value);
	}

	////////////////////////////////////////////////
	//	name
	////////////////////////////////////////////////

public:

	void setName(const char *val) 
	{
		name = val;
	}

	const char *getName() 
	{
		return name.c_str();
	}

	////////////////////////////////////////////////
	//	value
	////////////////////////////////////////////////

public:

	void setValue(const char *val) 
	{
		value = val;
	}

	const char *getValue() 
	{
		return value.c_str();
	}

	////////////////////////////////////////////////
	//	Attribute (Basic)
	////////////////////////////////////////////////

public:

	int getNAttributes() {
		return (int)attrList.size();
	}

	CyberXML::Attribute *getAttribute(int index) {
		return attrList.getAttribute(index);
	}

	CyberXML::Attribute *getAttribute(const char *name) 
	{
		return attrList.getAttribute(name);
	}

	void addAttribute(CyberXML::Attribute *attr) {
		attrList.addAttribute(attr);
	}

	void insertAttributeAt(CyberXML::Attribute *attr, int index) {
		attrList.insertAttribute(attr, index);
	}

	void addAttribute(const char *name, const char *value) {
		CyberXML::Attribute *attr = new CyberXML::Attribute(name, value);
		addAttribute(attr);
	}

	bool removeAttribute(CyberXML::Attribute *attr) {
		return attrList.removeAttribute(attr);
	}

	bool removeAttribute(const char *name) {
		return removeAttribute(getAttribute(name));
	}

	bool hasAttributes()
	{
		if (0 < getNAttributes())
			return true;
		return false;
	}

	////////////////////////////////////////////////
	//	Attribute (Extention)
	////////////////////////////////////////////////

public:

	void setAttribute(const char *name, const char *value) {
		CyberXML::Attribute *attr = getAttribute(name);
		if (attr != NULL) {
			attr->setValue(value);
			return;
		}
		attr = new CyberXML::Attribute(name, value);
		addAttribute(attr);
	}

	void setAttribute(const char *name, int value) {
		std::ostringstream valBuf;
		valBuf << value;
		std::string valStr = valBuf.str();
		setAttribute(name, valStr.c_str());
	}

	const char *getAttributeValue(const char *name) {
		CyberXML::Attribute *attr = getAttribute(name);
		if (attr != NULL)
			return attr->getValue();
		return "";
	}

	int getAttributeIntegerValue(const char *name) {
		const char *val = getAttributeValue(name);
		if (val == NULL)
			return 0;
		return atoi(val);
	}
};

}

#endif


