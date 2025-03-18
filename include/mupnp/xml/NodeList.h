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

#include <mupnp/common/Vector.h>
#include <mupnp/util/StringUtil.h>

namespace uXML {

class Node;

class NodeList : public mUPnP::SharedVector<Node> {
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
  
  bool removeNode(mupnp_shared_ptr<Node> node) {
    return remove(node);
  }
  
  bool insertNode(Node *node, size_t index) {
    return insertAt(node, index);
  }
  
  mupnp_shared_ptr<Node> getNode(size_t n) {
    return get(n);
  }
  
  mupnp_shared_ptr<Node> getNode(const std::string &name);
  mupnp_shared_ptr<Node> getEndsWith(const std::string &name);
  mupnp_shared_ptr<Node> getNode(const std::string &name, const std::string &value);
};

}

#endif
