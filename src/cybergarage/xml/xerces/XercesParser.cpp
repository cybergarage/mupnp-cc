/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File:	XercesParser.cpp
*
*	Revision;
*
*	05/20/03
*		- first revision
*	04/19/04
*		- Fixed the parse() to read under the buffer size.
*	04/27/04
*		- Chaged XMLCh2Char() to return the value using string buffer.
*	05/19/04
*		- Changed the header include order for Cygwin.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

////////////////////////////////////////////////
//	Compiler Switch (BEGIN)
////////////////////////////////////////////////

#if !defined(USE_XMLPARSER_EXPAT) && !defined(USE_XMLPARSER_LIBXML2)

////////////////////////////////////////////////
//	Header Files
////////////////////////////////////////////////

#include <cybergarage/util/Mutex.h>
#include <cybergarage/xml/Parser.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/URLInputSource.hpp>

#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;
using namespace xercesc;
using namespace CyberXML;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

static int parserCnt = 0;
static Mutex parserMutex;

Parser::Parser()
{
	parserMutex.lock();
	if (parserCnt == 0)
			XMLPlatformUtils::Initialize();
	parserCnt++;
	parserMutex.unlock();
}

Parser::~Parser()
{
	parserMutex.lock();
	parserCnt--;
	if (parserCnt <= 0)
		XMLPlatformUtils::Terminate();
	parserMutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////////////////////
//	parse (Xerces)
////////////////////////////////////////////////////////////////////////////////////////////////

const char *XMLCh2Char(const XMLCh *value, string &buf)
{
	char *xmlChars = XMLString::transcode(value);
	if (xmlChars == NULL) {
		buf = "";
		return buf.c_str();
	}
	buf = xmlChars;
	XMLString::release(&xmlChars);
	return buf.c_str();
}

Node *XMLParse(Node *parentNode, DOMNode *domNode, int rank)
{
	int domNodeType = domNode->getNodeType();
			
	string domNodeName;
	XMLCh2Char(domNode->getNodeName(), domNodeName);
	string domNodeValue;
	XMLCh2Char(domNode->getNodeValue(), domNodeValue);
	DOMNamedNodeMap *attrs = domNode->getAttributes(); 
	
	int arrrsLen = 0;
	if (attrs != NULL)
		arrrsLen = attrs->getLength();

//	Debug.message("[" + rank + "] ELEM : " + domNodeName + ", " + domNodeValue + ", type = " + domNodeType + ", attrs = " + arrrsLen);

	if (domNodeType == DOMNode::TEXT_NODE) {
		parentNode->setValue(domNodeValue.c_str());
		return parentNode;
	}

	if (domNodeType != DOMNode::ELEMENT_NODE)
		return parentNode;

	Node *node = new Node();
	node->setName(domNodeName.c_str());
	node->setValue(domNodeValue.c_str());

	if (parentNode != NULL)
		parentNode->addNode(node);

	DOMNamedNodeMap *attrMap = domNode->getAttributes(); 
	int attrLen = attrMap->getLength();
	//Debug.message("attrLen = " + attrLen);
	for (int n = 0; n<attrLen; n++) {
		DOMNode *attr = attrMap->item(n);
		string attrName;
		XMLCh2Char(attr->getNodeName(), attrName);
		string attrValue;
		XMLCh2Char(attr->getNodeValue(), attrValue);
		node->setAttribute(attrName.c_str(), attrValue.c_str());
	}
		
	DOMNode *child = domNode->getFirstChild();
	while (child != NULL) {
		XMLParse(node, child, rank+1);
		child = child->getNextSibling();
	}

	return node;
}

Node *XMLParse(InputSource &inSrc)
{
	Node *root = NULL;
		
	XercesDOMParser *parser = new XercesDOMParser();
	/*
	parser->setDoSchema(false);
	parser->setDoValidation(false);
	parser->setValidationScheme(XercesDOMParser::Val_Never);
	*/
	try {
		parser->parse(inSrc);
		xercesc::DOMDocument *doc = parser->getDocument();
		if (doc == NULL)
			return NULL;
		DOMElement *docElem = doc->getDocumentElement();
		if (docElem != NULL)
			root = XMLParse(root, docElem, 0);
	}
	catch (const XMLException &toCatch) {
		string msg;
		XMLCh2Char(toCatch.getMessage(), msg);
		throw ParserException(msg.c_str()); 
		return NULL;
	}
	
	return root;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//	parse
////////////////////////////////////////////////////////////////////////////////////////////////

Node *Parser::parse(const char *data, int len)
{
	try {
		/*
		XMLCh *xmlChars = XMLString::transcode(data);
		MemBufInputSource memIn((XMLByte *)xmlChars, XMLString::stringLen(xmlChars), "membuf", false);
		XMLString::release(&xmlChars);
		*/
		MemBufInputSource memIn((XMLByte *)data, len, "membuf", false);
		return XMLParse(memIn);
	}
	catch (const XMLException &toCatch) {
		string msg;
		XMLCh2Char(toCatch.getMessage(), msg);
		throw ParserException(msg.c_str()); 
	}
}

////////////////////////////////////////////////
//	Compiler Switch (END)
////////////////////////////////////////////////

#endif
