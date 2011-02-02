/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NodeList.h
*
*	Revision;
*
*	05/19/03
*		- first revision
*
******************************************************************/

#ifndef _CXML_NODELIST_H_
#define _CXML_NODELIST_H_

#include <cybergarage/util/Vector.h>
#include <cybergarage/util/StringUtil.h>

namespace CyberXML {

class Node;

class NodeList : public CyberUtil::Vector
{

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	NodeList();
	virtual ~NodeList();
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	bool addNode(Node *node);
	bool removeNode(Node *node);
	bool insertNode(Node *node, int index);

	Node *getNode(int n);
	Node *getNode(const char *name);
	Node *getEndsWith(const char *name);
	Node *getNode(const char *name, const char *value);

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif
