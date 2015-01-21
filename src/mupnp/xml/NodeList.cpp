/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/xml/NodeList.h>
#include <mupnp/xml/Node.h>

using namespace uXML;

////////////////////////////////////////////////
// get*
////////////////////////////////////////////////

Node *NodeList::getNode(const std::string &name)  {
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    Node *node = getNode(n);
    const char *nodeName = node->getName();
    if (uHTTP::StringEquals(name, nodeName) == true)
      return node;
  }
  return NULL;
}

Node *NodeList::getEndsWith(const std::string &name)  {
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    Node *node = getNode(n);
    const char *nodeName = node->getName();
    if (nodeName == NULL)
      continue;
    if (uHTTP::StringEndsWith(nodeName, name) == true)
      return node;
  }
  return NULL;
}

Node *NodeList::getNode(const std::string &name, const std::string &value)  {
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    Node *node = getNode(n);
    const char *nodeName = node->getName();
    if (uHTTP::StringEquals(name, nodeName) == false)
      continue;
    const char *nodeValue = node->getValue();
    if (uHTTP::StringEquals(value, nodeValue) == true)
      return node;
  }
  return NULL;
}
