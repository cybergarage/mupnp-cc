/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ServiceData.cpp
*
*  Revision;
*
*  04/26/04
*    - first revision
*  01/06/04
*    - Moved setQueryListener() and getQueryListener() to StateVariableData class.
*  05/19/04
*    - Changed the header include order for Cygwin.
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

void ServiceData::setSCPDNode(CyberXML::Node *node) {
  scpdNode = node;
}

