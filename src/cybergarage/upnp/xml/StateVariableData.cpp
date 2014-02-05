/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: StateVariableData.cpp
*
*  Revision;
*
*  04/26/04
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/control/QueryResponse.h>
#include <cybergarage/upnp/xml/StateVariableData.h>

using namespace CyberLink;

////////////////////////////////////////////////
// value
////////////////////////////////////////////////

StateVariableData::StateVariableData()  {
  queryRes = NULL;
}

StateVariableData::~StateVariableData() {
  if (queryRes != NULL)
    delete queryRes;
}

////////////////////////////////////////////////
// QueryResponse
////////////////////////////////////////////////

void StateVariableData::setQueryResponse(QueryResponse *res)  {
  if (queryRes != NULL)
    delete queryRes;
  queryRes = res;
}


