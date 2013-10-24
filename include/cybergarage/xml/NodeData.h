<<<<<<< HEAD
/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Data.h
*
*	Revision;
*
*	07/22/03
*		- first revision
*
******************************************************************/

#ifndef _CXML_XMLNODEDATA_H_
#define _CXML_XMLNODEDATA_H_

namespace CyberXML {

class Node;

class NodeData
{
	Node *node;

public:
	
	NodeData()
	{
	}

	virtual ~NodeData()
	{
	}

	////////////////////////////////////////////////
	// node
	////////////////////////////////////////////////

	void setNode(CyberXML::Node *node)
	{
		this->node = node;
	}

	CyberXML::Node *getNode()
	{
		return node;
	}

};

}

#endif
=======
/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Data.h
*
*	Revision;
*
*	07/22/03
*		- first revision
*
******************************************************************/

#ifndef _CXML_XMLNODEDATA_H_
#define _CXML_XMLNODEDATA_H_

namespace CyberXML {

class Node;

class NodeData
{
	Node *node;

public:
	
	NodeData()
	{
	}

	virtual ~NodeData()
	{
	}

	////////////////////////////////////////////////
	// node
	////////////////////////////////////////////////

	void setNode(CyberXML::Node *node)
	{
		this->node = node;
	}

	CyberXML::Node *getNode()
	{
		return node;
	}

};

}

#endif
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
