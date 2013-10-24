/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File:	ExpatParser.cpp
*
*	Revision;
*
*	11/29/04
*		- first revision
<<<<<<< HEAD
*	06/14/05
*		- Changed ExpatCharacterData() to use Node::addValue() instead of Node::setValue().
=======
*	06/14/05
*		- Changed ExpatCharacterData() to use Node::addValue() instead of Node::setValue().
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

////////////////////////////////////////////////
//	Compiler Switch (BEGIN)
////////////////////////////////////////////////

#if defined(USE_XMLPARSER_EXPAT)

#if defined(WIN32)
#define XML_STATIC
#endif

#if !defined(WIN32)
#define XMLCALL
#endif

////////////////////////////////////////////////
//	Header Files
////////////////////////////////////////////////

#include <cybergarage/xml/Parser.h>

#include <expat.h>

#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;
using namespace CyberXML;
<<<<<<< HEAD
using namespace uHTTP;
=======
using namespace CyberUtil;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

Parser::Parser()
{
}

Parser::~Parser()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
//	parse (Expact)
////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _ExpatData {
	Node *rootNode;
	Node *currNode;
} ExpatData;

<<<<<<< HEAD
static void XMLCALL ExpatElementStart(void *userData, const std::string &el, const std::string &*attr)
=======
static void XMLCALL ExpatElementStart(void *userData, const char *el, const char **attr)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	ExpatData *expatData = (ExpatData *)userData;

	Node *node = new Node();
	node->setName(el);

	for (int n = 0; attr[n]; n += 2)
		node->setAttribute(attr[n], attr[n+1]);

	if (expatData->rootNode != NULL) {
		if (expatData->currNode != NULL)
			expatData->currNode->addNode(node);
		else
			expatData->rootNode->addNode(node);
	}
	else
		expatData->rootNode = node;

	expatData->currNode = node;
}

<<<<<<< HEAD
static void XMLCALL ExpatElementEnd(void *userData, const std::string &el)
=======
static void XMLCALL ExpatElementEnd(void *userData, const char *el)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	ExpatData *expatData = (ExpatData *)userData;
	if (expatData->currNode != NULL)
		expatData->currNode = expatData->currNode->getParentNode();
}

static void XMLCALL ExpatCharacterData(void *userData, const XML_Char *s, int len)
{
	ExpatData *expatData = (ExpatData *)userData;
<<<<<<< HEAD

=======

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	if (expatData->currNode != NULL)
		expatData->currNode->addValue(s, len);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//	parse
////////////////////////////////////////////////////////////////////////////////////////////////

<<<<<<< HEAD
Node *Parser::parse(const std::string &data, int len)
=======
Node *Parser::parse(const char *data, int len)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	XML_Parser p = XML_ParserCreate(NULL);
	if (!p)
		return NULL;

	ExpatData expatData;
	expatData.rootNode = NULL;
	expatData.currNode = NULL;
	XML_SetUserData(p, &expatData);
	XML_SetElementHandler(p, ExpatElementStart, ExpatElementEnd);
	XML_SetCharacterDataHandler(p, ExpatCharacterData); 

    int parseRet = XML_Parse(p, data, len, 1);
	XML_ParserFree(p);

	if (parseRet == 0 /*XML_STATUS_ERROR*/) {
		if (expatData.rootNode != NULL)
				delete expatData.rootNode;
		return NULL;
	}

	//if (expatData.rootNode != NULL)
	//	expatData.rootNode->print();

	return expatData.rootNode;
}

////////////////////////////////////////////////
//	Compiler Switch (END)
////////////////////////////////////////////////

#endif
