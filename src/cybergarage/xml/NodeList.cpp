/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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

NodeList::NodeList()  {
}

NodeList::~NodeList()  {
  clear();
}

bool NodeList::addNode(Node *node)  {
  if (node == NULL)
    return false;
  return add(node);
}

bool NodeList::insertNode(Node *node, int index)  {
  if (node == NULL)
    return false;
  return insertAt(node, index);
}

bool NodeList::removeNode(Node *node)  {
  if (node == NULL)
    return false;
  bool ret = remove(node);
  delete node;
  return ret;
}

////////////////////////////////////////////////
//  get*
////////////////////////////////////////////////

Node *NodeList::getNode(int n) {
  return (Node *)Vector::get(n);
}

Node *NodeList::getNode(const std::string &name)  {
  int nLists = size(); 
  for (int n = 0; n < nLists; n++) {
    Node *node = getNode(n);
    const char *nodeName = node->getName();
    if (StringEquals(name, nodeName) == true)
      return node;
  }
  return NULL;
}

Node *NodeList::getEndsWith(const std::string &name)  {
  int nLists = size(); 
  for (int n = 0; n < nLists; n++) {
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
  int nLists = size(); 
  for (int n = 0; n < nLists; n++) {
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

////////////////////////////////////////////////
//  clear
////////////////////////////////////////////////

void NodeList::clear() {
  int nLists = size(); 
  for (int n = 0; n < nLists; n++) {
    Node *node = getNode(n);
    if (node != NULL)
      delete node;
  }
  Vector::clear();
}
