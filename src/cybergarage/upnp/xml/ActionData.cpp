/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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

#include <cybergarage/upnp/control/ControlResponse.h>
#include <cybergarage/upnp/xml/ActionData.h>

using namespace CyberLink;
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
