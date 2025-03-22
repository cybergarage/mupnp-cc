/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

////////////////////////////////////////////////
// Compiler Switch (BEGIN)
////////////////////////////////////////////////

#if defined(USE_XMLPARSER_LIBXML2)

////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////

#include <mupnp/Log.h>
#include <mupnp/xml/Parser.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;
using namespace uXML;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Parser::Parser()
{
}

Parser::~Parser()
{
}

////////////////////////////////////////////////
// convertToCLinkFormat
////////////////////////////////////////////////

static Node* convertToCLinkFormat(xmlDocPtr doc, xmlNodePtr cur, int depth)
{
  if (!cur) {
    // This should never happen...
    LogFatal("convertToCLinkFormat: This should never happen!");
    exit(0);
    return nullptr;
  }

  if (depth > 12) {
    LogWarn("convertToCLinkFormat: Recursion depth > 10. Are you sure this is OK!?");
    return nullptr;
  }

  // We are only interested in XML_ELEMENT_NODEs.
  // Note, that the resulting Node tree will only contain them...
  if (cur->type != XML_ELEMENT_NODE)
    return nullptr;

  Node* newNode = new Node();

  // Set name and value for the new node.
  string nodeName;
  if (cur->ns && cur->ns->prefix) {
    // Add the namespace prefix to the element name
    nodeName = (const char*)cur->ns->prefix;
    nodeName += ":";
  }
  nodeName += (const char*)cur->name;
  newNode->setName(nodeName);

  string nodeValue = (const char*)xmlNodeGetContent(cur);
  newNode->setValue(nodeValue);

  // Get attribute declarations (if any) and copy to newNode
  xmlAttrPtr prop = cur->properties;
  while (prop) {
    std::string propName = (const char*)prop->name;
    xmlChar* attrChar = xmlNodeListGetString(doc, prop->xmlChildrenNode, 1);
    std::string attrValue = (const char*)attrChar;
    newNode->setAttribute(propName, attrValue);
    xmlFree(attrChar);
    prop = prop->next;
  }

  // Also add namespace declarations to the attribute list
  xmlNsPtr nsDef = cur->nsDef;
  while (nsDef) {
    string spaceName = "xmlns";
    if (nsDef->prefix) {
      spaceName += ":";
      spaceName += (const char*)nsDef->prefix;
    }
    string spaceValue = (const char*)nsDef->href;
    newNode->setAttribute(spaceName, spaceValue);
    nsDef = nsDef->next;
  }

  // Then convert (recursively) all the children of the current node
  xmlNodePtr child = cur->xmlChildrenNode;
  while (child) {
    Node* newChildNode = convertToCLinkFormat(doc, child, 1);
    if (newChildNode) {
      newNode->addNode(newChildNode);
    }
    child = child->next;
  }

  return newNode;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// parse
////////////////////////////////////////////////////////////////////////////////////////////////

mupnp_shared_ptr<uXML::Node> Parser::parse(const std::string& data, size_t len)
{
  // First, parse the XML memory buffer ito a DOM object
  xmlDocPtr doc = xmlReadMemory(data.c_str(), (int)len, NULL, NULL, XML_PARSE_NOERROR);
  if (!doc) {
    LogWarn("XML file parsing failed:");
    LogWarn("%s", data.c_str());
    return mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
  }

  // Then get a pointer to the root node
  xmlNodePtr cur;
  cur = xmlDocGetRootElement(doc);
  if (!cur) {
    LogWarn("Empty document");
    xmlFreeDoc(doc);
    return mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
  }

  // Then convert the libxml2 type node tree into mUPnP XML node tree
  Node* rootNode = convertToCLinkFormat(doc, cur, 0);

  // Now all data is copied to mUPnP, release the original DOM object tree
  xmlFreeDoc(doc);

  return mupnp_shared_ptr<uXML::Node>(rootNode);
}

////////////////////////////////////////////////
// Compiler Switch (END)
////////////////////////////////////////////////

#endif
