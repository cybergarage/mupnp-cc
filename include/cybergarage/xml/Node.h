/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Node.h
*
*	Revision;
*
*	04/22/03
*		- first revision
*
******************************************************************/

#ifndef _CXML_NODE_H_
#define _CXML_NODE_H_

#include <iostream>
#include <sstream>
#include <string>

#include <cybergarage/xml/AttributeList.h>
#include <cybergarage/xml/NodeList.h>
#include <cybergarage/xml/NodeData.h>

namespace CyberXML {

class Node 
{

	Node *parentNode;

	std::string name;
	std::string value;
	
	AttributeList attrList;
	NodeList nodeList;
	
	NodeData *userData; 
	
public:
	
	Node();

<<<<<<< HEAD
	Node(const std::string &name);

	Node(const std::string &ns, const std::string &name);
=======
	Node(const char *name);

	Node(const char *ns, const char *name);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	virtual ~Node();

	////////////////////////////////////////////////
	//	parent node
	////////////////////////////////////////////////

	void setParentNode(Node *node) 
	{
		parentNode = node;
	}

	Node *getParentNode() 
	{
		return parentNode;
	}

	////////////////////////////////////////////////
	//	root node
	////////////////////////////////////////////////

	Node *getRootNode()
	{
		Node *rootNode = NULL;
		Node *parentNode = getParentNode();
		while (parentNode != NULL) {
			 rootNode = parentNode;
			 parentNode = rootNode->getParentNode();
		}
		return rootNode;
	}

	////////////////////////////////////////////////
	//	name
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setName(const std::string &val) 
=======
	void setName(const char *val) 
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		name = val;
	}

<<<<<<< HEAD
	void setName(const std::string &ns, const std::string &val) 
=======
	void setName(const char *ns, const char *val) 
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		name = ns;
		name += ":";
		name += val;
	}

	const char *getName()
	{
		return name.c_str();
	}

<<<<<<< HEAD
	bool isName(const std::string &val)
=======
	bool isName(const char *val)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return (name.compare(val) == 0) ? true : false;
	}

	////////////////////////////////////////////////
	//	value (set)
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setValue(const std::string &val)
=======
	void setValue(const char *val)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		value = val;
	}

	void setValue(int val);

	const char *getValue()
	{
		return value.c_str();
	}

<<<<<<< HEAD
	bool isValue(const std::string &val)
=======
	bool isValue(const char *val)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return (value.compare(val) == 0) ? true : false;
	}

<<<<<<< HEAD
	////////////////////////////////////////////////
	//	value (add)
	////////////////////////////////////////////////

	void addValue(const std::string &val)
	{
		value.append(val);
	}

	void addValue(const std::string &val, int len)
	{
		value.append(val, 0, len);
	}

=======
	////////////////////////////////////////////////
	//	value (add)
	////////////////////////////////////////////////

	void addValue(const char *val)
	{
		value.append(val);
	}

	void addValue(const char *val, int len)
	{
		value.append(val, 0, len);
	}

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	////////////////////////////////////////////////
	//	Attribute (Basic)
	////////////////////////////////////////////////

	int getNAttributes() {
		return (int)attrList.size();
	}

	Attribute *getAttribute(int index) {
		return attrList.getAttribute(index);
	}

<<<<<<< HEAD
	Attribute *getAttribute(const std::string & name)
=======
	Attribute *getAttribute(const char * name)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return attrList.getAttribute(name);
	}

	void addAttribute(Attribute *attr) {
		attrList.addAttribute(attr);
	}

	void insertAttributeAt(Attribute *attr, int index) {
		attrList.insertAttribute(attr, index);
	}

<<<<<<< HEAD
	void addAttribute(const std::string & name, const std::string & value) {
=======
	void addAttribute(const char * name, const char * value) {
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		Attribute *attr = new Attribute(name, value);
		addAttribute(attr);
	}

	bool removeAttribute(Attribute *attr) {
		return attrList.removeAttribute(attr);
	}

<<<<<<< HEAD
	bool removeAttribute(const std::string & name) {
=======
	bool removeAttribute(const char * name) {
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
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

<<<<<<< HEAD
	void setAttribute(const std::string & name, const std::string & value);

	void setAttribute(const std::string &name, int value);

	const char *getAttributeValue(const std::string & name);

	int getAttributeIntegerValue(const std::string &name);
=======
	void setAttribute(const char * name, const char * value);

	void setAttribute(const char *name, int value);

	const char *getAttributeValue(const char * name);

	int getAttributeIntegerValue(const char *name);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	Attribute (xmlns)
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setNameSpace(const std::string & ns, const std::string & val)
=======
	void setNameSpace(const char * ns, const char * val)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		std::string nspace;
		nspace = "xmlns:";
		nspace += ns;
		setAttribute(nspace.c_str(), val);
	}

	////////////////////////////////////////////////
	//	Child node
	////////////////////////////////////////////////

	int getNNodes() {
		return (int)nodeList.size();
	}

	Node *getNode(int index) {
		return nodeList.getNode(index);
	}

<<<<<<< HEAD
	Node *getNode(const std::string & name)
=======
	Node *getNode(const char * name)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return nodeList.getNode(name);
	}

<<<<<<< HEAD
	Node *getNode(const std::string & name, const std::string &value)
=======
	Node *getNode(const char * name, const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return nodeList.getNode(name, value);
	}

<<<<<<< HEAD
	Node *getNodeEndsWith(const std::string & name)
=======
	Node *getNodeEndsWith(const char * name)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return nodeList.getEndsWith(name);
	}

	void addNode(Node *node) {
		node->setParentNode(this);
		nodeList.addNode(node);
	}

	void insertNode(Node *node, int index) {
		node->setParentNode(this);
		nodeList.insertNode(node, index);
	}

	bool removeNode(Node *node) {
		node->setParentNode(NULL);
		return nodeList.removeNode(node);
	}

<<<<<<< HEAD
	bool removeNode(const std::string & name) {
=======
	bool removeNode(const char * name) {
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		return nodeList.removeNode(getNode(name));
	}

	bool hasNodes()
	{
		if (0 < getNNodes())
			return true;
		return false;
	}

	void removeAllNodes(void)
	{
		nodeList.clear();
	}

	////////////////////////////////////////////////
	//	Element (Child Node)
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setNode(const std::string & name, const std::string & value) {
=======
	void setNode(const char * name, const char * value) {
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		Node *node = getNode(name);
		if (node != NULL) {
			node->setValue(value);
			return;
		}
		node = new Node(name);
		node->setValue(value);
		addNode(node);
	}

<<<<<<< HEAD
	const char *getNodeValue(const std::string & name) {
=======
	const char *getNodeValue(const char * name) {
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		Node *node = getNode(name);
		if (node != NULL)
			return node->getValue();
		return "";
	}

	////////////////////////////////////////////////
	//	userData
	////////////////////////////////////////////////

	void setUserData(NodeData *data);

	NodeData *getUserData()
	{
		return userData;
	}

	////////////////////////////////////////////////
	//	toString
	////////////////////////////////////////////////

protected:

	const char *getIndentLevelString(int nIndentLevel, std::string &buf)
	{
		buf = "";
		for (int n=0; n<nIndentLevel; n++)
			buf.append("\t");
		return buf.c_str();
	}

public:

#ifndef NO_USE_OSTRINGSTREAM
	void outputAttributes(std::ostream& ps);
#else
	void outputAttributes(std::string& ps);
#endif

public:

#ifndef NO_USE_OSTRINGSTREAM
	virtual void output(std::ostream& ps, int indentLevel, bool hasChildNode);
#else
	virtual void output(std::string& ps, int indentLevel, bool hasChildNode);
#endif

	const char *toString(std::string &buf, bool hasChildNode = true);

<<<<<<< HEAD
=======
	const char *toUnicodeString(std::string &buf, bool hasChildNode = true);

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	void print(bool hasChildNode = true);

};

}

#endif
