/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
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
  if (queryRes)
    delete queryRes;
}

////////////////////////////////////////////////
// QueryResponse
////////////////////////////////////////////////

void StateVariableData::setQueryResponse(QueryResponse *res)  {
  if (queryRes)
    delete queryRes;
  queryRes = res;
}


