/******************************************************************
*
*	libxml2 XML parser support for for CyberLink C++ UPnP stack
*
*	Copyright (C) Nokia 2005
*
*	File:	Libxml2Parser.cpp
*
*	Revision:
*
*	08/24/05
*		- first revision
*	09/07/05
*		- Thanks for  Smolander Visa <visa.smolander@nokia.com>
*		- Fixed some bugs to parser the name spaces.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

////////////////////////////////////////////////
//	Compiler Switch (BEGIN)
////////////////////////////////////////////////

#if defined(USE_XMLPARSER_LIBXML2)

////////////////////////////////////////////////
//	Header Files
////////////////////////////////////////////////

#include <cybergarage/xml/Parser.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;
using namespace CyberXML;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

Parser::Parser()
{
}

Parser::~Parser()
{
}

////////////////////////////////////////////////
//	convertToCLinkFormat
////////////////////////////////////////////////

Node *convertToCLinkFormat( xmlDocPtr doc, xmlNodePtr cur, int depth )
{
  if ( cur == NULL ) {
    // This should never happen...
    cout << "convertToCLinkFormat: This should never happen!" << endl;
    exit( 0 );
    return NULL;
  }

  if ( depth > 12 ) {
    cout << "convertToCLinkFormat: Recursion depth > 10. Are you sure this is OK!?" << endl;
    return NULL;
  }
  
  // We are only interested in XML_ELEMENT_NODEs.
  // Note, that the resulting Node tree will only contain them...
  if ( cur->type == XML_ELEMENT_NODE ) {
    
    Node *newNode = new Node();
      
    // Set name and value for the new node.
    string nameBuf;
    if ( cur->ns && cur->ns->prefix ) {
      // Add the namespace prefix to the element name
      nameBuf = (const char*) cur->ns->prefix;
      nameBuf = ":";
    }
    nameBuf = (const char*) cur->name;

    newNode->setName( nameBuf.c_str() );

    xmlChar *key = NULL;
    if ( cur->xmlChildrenNode ) {
      key = xmlNodeListGetString( doc, cur->xmlChildrenNode, 1 );
    } 
    if ( key ) {
      newNode->setValue( (const char *) key );
      xmlFree( key );
    }
    
    // Get attribute declarations (if any) and copy to newNode
    xmlAttrPtr prop = cur->properties;
    while ( prop ) {
      xmlChar *attrValue = xmlNodeListGetString( doc, prop->xmlChildrenNode, 1 );
      newNode->setAttribute( (const char *) prop->name, (const char *) attrValue );
      xmlFree( attrValue );

      prop = prop->next;
    }

    // Also add namespace declarations to the attribute list
    xmlNsPtr nsDef = cur->nsDef;
    while ( nsDef ) {
      string nsBuf;
      nsBuf = "xmlns";
      if ( nsDef->prefix ) {
	nsBuf = ":";
	nsBuf = (const char *) nsDef->prefix;
      }
      newNode->setAttribute( nsBuf.c_str(), (const char *) nsDef->href );

      nsDef = nsDef->next;
    }
  

    // Then convert (recursively) all the children of the current node
    xmlNodePtr child = cur->xmlChildrenNode;
    while ( child != NULL ) {

      Node *newChildNode = convertToCLinkFormat( doc, child, depth  1 );
      if ( newChildNode ) {
	newNode->addNode( newChildNode );
      }

      child = child->next;
    }

    return newNode;
  }

  return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//	parse
////////////////////////////////////////////////////////////////////////////////////////////////

Node *Parser::parse(const char *data, int len)
{
  // First, parse the XML memory buffer ito a DOM object
  xmlDocPtr doc = xmlParseMemory( data, len );
  if ( doc == NULL ) {
    cout << "XML file parsing failed:" << endl;
    cout << data << endl;
    return NULL;
  }

  // Then get a pointer to the root node
  xmlNodePtr cur;
  cur = xmlDocGetRootElement( doc );
  if (cur == NULL) {
    fprintf(stderr,"Empty document\n");
    xmlFreeDoc(doc);
    return NULL;
  }

  // Then convert the libxml2 type node tree into CyberLink XML node tree
  Node *rootNode = convertToCLinkFormat( doc, cur, 0 );

  // Now all data is copied to CyberLink, release the original DOM object tree
  xmlFreeDoc(doc);

  return rootNode;
}

////////////////////////////////////////////////
//	Compiler Switch (END)
////////////////////////////////////////////////

#endif
