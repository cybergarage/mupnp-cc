/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ServiceStateTable.cpp
*
*  Revision;
*
*  08/13/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/Action.h>
#include <cybergarage/upnp/ServiceStateTable.h>
#include <cybergarage/upnp/StateVariable.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *ServiceStateTable::ELEM_NAME = "serviceStateTable";

////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////

 void ServiceStateTable::clear()  {
  int nVars = size();
  for (int n = 0; n < nVars; n++) {
    StateVariable *var = getStateVariable(n);
    delete var;
  }
  Vector::clear();
}
