/******************************************************************
*
*  libxml2 XML parser support for for CyberLink C++ UPnP stack
*
*  Copyright (C) Nokia 2005
*
*  File:  Libxml2Parser.cpp
*
*  Revision:
*
*  08/24/05
*    - first revision
*  09/07/05
*    - Thanks for  Smolander Visa <visa.smolander@nokia.com>
*    - Fixed some bugs to parser the name spaces.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

////////////////////////////////////////////////
//  Compiler Switch (BEGIN)
////////////////////////////////////////////////

#if defined(USE_XMLPARSER_LIBXML2)

////////////////////////////////////////////////
//  Header Files
////////////////////////////////////////////////

#include <cybergarage/xml/Parser.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;
using namespace CyberXML;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

Parser::Parser() {
}

Parser::~Parser() {
}

////////////////////////////////////////////////
//  convertToCLinkFormat
////////////////////////////////////////////////

static Node *convertToCLinkFormat( xmlDocPtr doc, xmlNodePtr cur, int depth ) {
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
  if ( cur->type != XML_ELEMENT_NODE )
    return NULL;
  
  Node *newNode = new Node();
    
  // Set name and value for the new node.
  string nodeName;
  if ( cur->ns && cur->ns->prefix ) {
    // Add the namespace prefix to the element name
    nodeName = (const char *)cur->ns->prefix;
    nodeName += ":";
  }
  nodeName += (const char*) cur->name;
  newNode->setName(nodeName);

  string nodeValue = (const char *)xmlNodeGetContent(cur);
  newNode->setValue(nodeValue);
    
  // Get attribute declarations (if any) and copy to newNode
  xmlAttrPtr prop = cur->properties;
  while ( prop ) {
    std::string propName = (const char *)prop->name;
    xmlChar *attrChar = xmlNodeListGetString( doc, prop->xmlChildrenNode, 1 );
    std::string attrValue = (const char *)attrChar;
    newNode->setAttribute(propName, attrValue);
    xmlFree(attrChar);
    prop = prop->next;
  }

  // Also add namespace declarations to the attribute list
  xmlNsPtr nsDef = cur->nsDef;
  while ( nsDef ) {
    string spaceName = "xmlns";
    if (nsDef->prefix) {
      spaceName += ":";
      spaceName += (const char *)nsDef->prefix;
    }
    string spaceValue = (const char *)nsDef->href;
    newNode->setAttribute(spaceName, spaceValue);
    nsDef = nsDef->next;
  }

  // Then convert (recursively) all the children of the current node
  xmlNodePtr child = cur->xmlChildrenNode;
  while ( child != NULL ) {
    Node *newChildNode = convertToCLinkFormat( doc, child, 1);
    if ( newChildNode ) {
      newNode->addNode( newChildNode );
    }
    child = child->next;
  }

  return newNode;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//  parse
////////////////////////////////////////////////////////////////////////////////////////////////

Node *Parser::parse(const std::string &data, size_t len) {
  // First, parse the XML memory buffer ito a DOM object
  xmlDocPtr doc = xmlParseMemory( data.c_str(), (int)len );
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
//  Compiler Switch (END)
////////////////////////////////////////////////

#endif
