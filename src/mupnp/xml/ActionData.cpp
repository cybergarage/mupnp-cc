/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/control/ControlResponse.h>
#include <mupnp/xml/ActionData.h>

using namespace mUPnP;
using namespace mUPnP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

ActionData::ActionData()  {
  setActionListener(NULL);
  ctrlRes = NULL;
}

ActionData::~ActionData()  {
  if (ctrlRes != NULL)
    delete ctrlRes;
}

////////////////////////////////////////////////
// ControlResponse
////////////////////////////////////////////////

void ActionData::setControlResponse(ControlResponse *res)  {
  if (ctrlRes != NULL)
    delete ctrlRes;
  ctrlRes = res;
}
