/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ActionList.cpp
*
*  Revision;
*
*  08/13/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/Action.h>
#include <cybergarage/upnp/ActionList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *CyberLink::ActionList::ELEM_NAME = "actionList";

////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////

 void ActionList::clear()  {
  int nAct = size();
  for (int n = 0; n < nAct; n++) {
    Action *act = getAction(n);
    delete act;
  }
  Vector::clear();
}
