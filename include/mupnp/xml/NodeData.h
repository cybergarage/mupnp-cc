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

namespace uXML {

class Node;

class NodeData {
  uXML::Node *node;

public:
  
  NodeData() {
  }

  virtual ~NodeData() {
  }

  ////////////////////////////////////////////////
  // node
  ////////////////////////////////////////////////

  void setNode(uXML::Node *node) {
    this->node = node;
  }

  uXML::Node *getNode() {
    return node;
  }

};

}

#endif
