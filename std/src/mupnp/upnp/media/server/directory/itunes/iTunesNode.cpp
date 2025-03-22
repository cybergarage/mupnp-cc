/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2006
 *
 *	File: iTunesNode.cpp
 *
 *	Revision:
 *
 *	03/13/06
 *		- first revision.
 *
 ******************************************************************/

#ifdef SUPPORT_ITUNES

#include <mupnp/upnp/media/server/directory/itunes/iTunesNode.h>

#include <mupnp/util/StringUtil.h>

using namespace CyberLink;
using namespace CyberXML;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

iTunesNode::iTunesNode()
{
}

iTunesNode::~iTunesNode()
{
}

////////////////////////////////////////////////
//	getKeyValue
////////////////////////////////////////////////

const char* iTunesNode::getKeyValue(const char* keyName)
{
  Node* node = getNode();
  if (node == NULL)
    return NULL;

  Node* keyValueNode = NULL;

  int childNodeCnt = node->getNNodes();
  for (int n = 0; n < childNodeCnt; n++) {
    Node* childNode = node->getNode(n);
    if (childNode == NULL)
      continue;
    if (node->isName(keyName) == false)
      continue;
    if ((childNodeCnt - 1) <= n)
      continue;
    keyValueNode = node->getNode(n + 1);
  }

  if (keyValueNode == NULL)
    return NULL;

  return node->getValue();
}

////////////////////////////////////////////////
//	getKeyInteger
////////////////////////////////////////////////

int iTunesNode::getKeyInteger(const char* keyName)
{
  const char* keyValue = getKeyValue(keyName);
  if (keyValue == NULL)
    return 0;
  return String2Integer(keyValue);
}

////////////////////////////////////////////////
//	getKeyLong
////////////////////////////////////////////////

long iTunesNode::getKeyLong(const char* keyName)
{
  const char* keyValue = getKeyValue(keyName);
  if (keyValue == NULL)
    return 0;
  return String2Long(keyValue);
}

#endif
