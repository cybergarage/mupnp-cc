/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_NODELIST_H_
#define _MUPMPCC_NODELIST_H_

#include <uhttp/util/Vector.h>
#include <uhttp/util/StringUtil.h>

namespace uXML {

class Node;

class NodeList : public uHTTP::Vector<Node> {
public:
  
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  NodeList() {
  }
  
public:
  
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  bool addNode(Node *node) {
    return add(node);
  }
  
  bool removeNode(Node *node) {
    return remove(node);
  }
  
  bool insertNode(Node *node, size_t index) {
    return insertAt(node, index);
  }
  
  Node *getNode(size_t n) {
    return Vector::get(n);
  }
  
  Node *getNode(const std::string &name);
  Node *getEndsWith(const std::string &name);
  Node *getNode(const std::string &name, const std::string &value);
};

}

#endif
