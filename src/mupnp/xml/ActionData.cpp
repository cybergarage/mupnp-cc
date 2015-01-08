/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ActionData.cpp
*
*  Revision;
*
*  04/26/04
*    - first revision
*  05/19/04
*    - Changed the header include order for Cygwin.
*
******************************************************************/

#include <mupnp/control/ControlResponse.h>
#include <mupnp/xml/ActionData.h>

using namespace mUPnP;
using namespace CyberXML;

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
