/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_XMLNODEDATA_H_
#define _MUPMPCC_XMLNODEDATA_H_

namespace mUPnP {
class Node;

class NodeData {
  Node *node;

public:
  
  NodeData() {
  }

  virtual ~NodeData() {
  }

  ////////////////////////////////////////////////
  // node
  ////////////////////////////////////////////////

  void setNode(Node *node) {
    this->node = node;
  }

  mUPnP::Node *getNode() {
    return node;
  }

};

}

#endif
