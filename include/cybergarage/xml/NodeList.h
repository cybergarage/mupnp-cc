/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: NodeList.h
*
*  Revision;
*
*  05/19/03
*    - first revision
*
******************************************************************/

#ifndef _CXML_NODELIST_H_
#define _CXML_NODELIST_H_

#include <uhttp/util/Vector.h>
#include <uhttp/util/StringUtil.h>

namespace CyberXML {
class Node;

class NodeList : public uHTTP::Vector {
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  NodeList();
  virtual ~NodeList();
  
  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////

 public:
  bool addNode(Node *node);
  bool removeNode(Node *node);
  bool insertNode(Node *node, int index);

  Node *getNode(int n);
  Node *getNode(const std::string &name);
  Node *getEndsWith(const std::string &name);
  Node *getNode(const std::string &name, const std::string &value);

  ////////////////////////////////////////////////
  //  clear
  ////////////////////////////////////////////////

 public:
  void clear();
};

}

#endif
