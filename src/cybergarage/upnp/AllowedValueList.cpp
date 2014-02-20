/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2004
*
*  File: AllowedValueList.h
*
*  Revision:
*
*  03/29/04
*    - first revision.
*  02/28/05
*    - Changed to use AllowedValue class instead of string as the member.
*  
******************************************************************/

#include <cybergarage/upnp/AllowedValueList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////
  
const char *AllowedValueList::ELEM_NAME = "allowedValueList";

////////////////////////////////////////////////
//  clear
////////////////////////////////////////////////

void AllowedValueList::clear()  {
  int nValues = size();
  for (int n = 0; n < nValues; n++) {
    AllowedValue *value = getAllowedValue(n);
    delete value;
  }
  Vector::clear();
}
