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

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

mUPnP::ActionData::ActionData()
{
  setActionListener(NULL);
  ctrlRes = NULL;
}

mUPnP::ActionData::~ActionData()
{
  if (ctrlRes)
    delete ctrlRes;
}

////////////////////////////////////////////////
// ControlResponse
////////////////////////////////////////////////

void mUPnP::ActionData::setControlResponse(ControlResponse* res)
{
  if (ctrlRes)
    delete ctrlRes;
  ctrlRes = res;
}
