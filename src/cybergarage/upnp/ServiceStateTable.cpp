/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
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
// Constants
////////////////////////////////////////////////

const char *ServiceStateTable::ELEM_NAME = "serviceStateTable";

////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////

 void ServiceStateTable::clear()  {
  size_t nVars = size();
  for (size_t n = 0; n < nVars; n++) {
    StateVariable *var = getStateVariable(n);
    delete var;
  }
  Vector::clear();
}
