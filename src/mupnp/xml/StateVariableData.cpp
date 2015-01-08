/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: StateVariableData.cpp
*
*  Revision;
*
*  04/26/04
*    - first revision
*
******************************************************************/

#include <mupnp/control/QueryResponse.h>
#include <mupnp/xml/StateVariableData.h>

using namespace mUPnP;

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


