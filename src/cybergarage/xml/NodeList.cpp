/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: NodeList.cpp
*
*  Revision;
*
*  04/28/04
*    - first revision
*  06/30/04
*    - Added addNode(), insertNode() and removeNode();
*  03/04/06
*    - Added getNode(name, value) for iTunes Library.
*
******************************************************************/

#include <cybergarage/xml/NodeList.h>
#include <cybergarage/xml/Node.h>

using namespace CyberXML;
using namespace uHTTP;

////////////////////////////////////////////////
// get*
////////////////////////////////////////////////

Node *NodeList::getNode(const std::string &name)  {
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    Node *node = getNode(n);
    const char *nodeName = node->getName();
    if (StringEquals(name, nodeName) == true)
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
    if (StringEndsWith(nodeName, name) == true)
      return node;
  }
  return NULL;
}

Node *NodeList::getNode(const std::string &name, const std::string &value)  {
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    Node *node = getNode(n);
    const char *nodeName = node->getName();
    if (StringEquals(name, nodeName) == false)
      continue;
    const char *nodeValue = node->getValue();
    if (StringEquals(value, nodeValue) == true)
      return node;
  }
  return NULL;
}
