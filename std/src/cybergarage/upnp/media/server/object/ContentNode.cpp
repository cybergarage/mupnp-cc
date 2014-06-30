/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : ContentNode.cpp
*
*	Revision:
*
*	03/14/04
*		- first revision.
*	04/27/04
*		- Changed is*Node() to typeid(*this) instead of typeid(this). 
*		- Enabled the RTTI option for Visual C++ to all projects.
*	04/27/04
*		- Added setID(String) and setParentID(String).
*		- Changed getID() and getParentID() to return the string value instead of interger.
*		- Changed findContentNodeByID() to serach using a string id.
*	05/09/04
*		- Changed is*Node() using dynamic_cast(). 
*	05/10/04
*		- Added hasContainerNodes() and hasItemNodes(). 
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/ContentNode.h>
#include <cybergarage/upnp/media/server/object/container/ContainerNode.h>
#include <cybergarage/upnp/media/server/object/item/ItemNode.h>

using namespace std;
using namespace CyberLink;
using namespace CyberXML;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *ContentNode::ID = "id";
const char *ContentNode::PARENT_ID = "parentID";
const char *ContentNode::RESTRICTED = "restricted";

const char *ContentNode::UNKNOWN = "UNKNOWN";

////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////
	
ContentNode::ContentNode()
{
	setID(0);
	setParentID(-1);
	setRestricted(1);
	setContentDirectory(NULL);
}

ContentNode::~ContentNode()
{
}

////////////////////////////////////////////////
// is*Node
////////////////////////////////////////////////

bool ContentNode::isContainerNode()
{
	//return (typeid(*this) == typeid(ContainerNode)) ? true : false;
	ContainerNode *cnode = dynamic_cast<ContainerNode*>(this);
	return (cnode != NULL) ? true : false;
}

bool ContentNode::isItemNode()
{
	//return (typeid(*this) == typeid(ItemNode)) ? true : false;
	ItemNode *inode = dynamic_cast<ItemNode*>(this);
	return (inode != NULL) ? true : false;
}

////////////////////////////////////////////////
// has*Nodes
////////////////////////////////////////////////

bool ContentNode::hasContainerNodes()
{
	int nContentNodes = getNContentNodes();
	for (int n=0; n<nContentNodes; n++) {
		ContentNode *cnode = getContentNode(n);
		if (cnode->isContainerNode() == true)
			return true;
	}
	return false;
}

bool ContentNode::hasItemNodes()
{
	int nContentNodes = getNContentNodes();
	for (int n=0; n<nContentNodes; n++) {
		ContentNode *cnode = getContentNode(n);
		if (cnode->isItemNode() == true)
			return true;
	}
	return false;
}

////////////////////////////////////////////////
//	findContentNodeBy*
////////////////////////////////////////////////

ContentNode *ContentNode::findContentNodeByID(const char *id)
{
	if (id == NULL)
		return NULL;

	string idStr = id;
	const char *nodeID = getID();
	if (idStr.compare(nodeID) == 0)
		return this;

	int nodeCnt = getNContentNodes();
	for (int n=0; n<nodeCnt; n++) {
		ContentNode *cnode = getContentNode(n);
		ContentNode *fnode = cnode->findContentNodeByID(id);
		if (fnode != NULL)
			return fnode;	
	}
		
	return NULL;
}

////////////////////////////////////////////////
// set
////////////////////////////////////////////////

void ContentNode::set(CyberXML::Node *node)
{
	int n;

	// Child Node -> Property;
	int nNode = node->getNNodes();
	for (n=0; n<nNode; n++) {
		Node *cnode = node->getNode(n);
		if (ContainerNode::isContainerNode(cnode) == true)
			continue;
		if (ItemNode::isItemNode(cnode) == true)
			continue;
		setProperty(cnode->getName(), cnode->getValue());
	}

	// Attribute -> Attribute;
	int nAttr = node->getNAttributes();
	for (n=0; n<nAttr; n++) {
		Attribute *attr = node->getAttribute(n);
		setAttribute(attr->getName(), attr->getValue());
	}
}

////////////////////////////////////////////////
//	toString 
////////////////////////////////////////////////

void ContentNode::outputPropertyAttributes(std::ostream& ps, ContentProperty *prop)
{
	int nAttributes = prop->getNAttributes();
	for (int n=0; n<nAttributes; n++) {
		Attribute *attr = prop->getAttribute(n);
		ps << " " << attr->getName() << "=\"" << attr->getValue() << "\"";
	}
}

void ContentNode::output(std::ostream& ps, int indentLevel, bool hasChildNode) 
{
	string indentString;
	getIndentLevelString(indentLevel, indentString);

	const char *name = getName();
	const char *value = getValue();

	if (hasNodes() == false && hasProperties() == false) {		
		ps << indentString << "<" << name;
		Node::outputAttributes(ps);
		ps << ">" << value << "</" << name << ">" << endl;
		return;
	}
		
	ps << indentString << "<" << name;
	outputAttributes(ps);
	ps << ">" << endl;
	
	int nProps = getNProperties();
	for (int n=0; n<nProps; n++) {
		string propIndentString;
		getIndentLevelString(indentLevel+1, propIndentString);
		ContentProperty *prop = getProperty(n);
		const char *propName = prop->getName();
		const char *propValue = prop->getValue();
		if (prop->hasAttributes() == true) {
			ps << propIndentString << "<" << propName;
			outputPropertyAttributes(ps, prop);
			ps << ">" << propValue << "</" << propName << ">" << endl;
		}
		else
			ps << propIndentString << "<" << propName << ">" << propValue << "</" << propName << ">" << endl;
	}
		
	if (hasChildNode == true) {
		int nChildNodes = getNNodes();
		for (int n=0; n<nChildNodes; n++) {
			Node *cnode = getNode(n);
			cnode->output(ps, indentLevel+1, true);
		}
	}

	ps << indentString << "</" << name << ">" << endl;
}
