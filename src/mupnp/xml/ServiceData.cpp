/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/Service.h>
#include <mupnp/xml/ServiceData.h>

using namespace mUPnP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

ServiceData::ServiceData()  {
  service = NULL;
  scpdNode = NULL;
}

////////////////////////////////////////////////
// scpdNode
////////////////////////////////////////////////

void ServiceData::setSCPDNode(uXML::Node *node) {
  scpdNode = node;
}
