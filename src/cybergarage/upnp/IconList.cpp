/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: IconList.cpp
*
*  Revision;
*
*  08/15/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/Icon.h>
#include <cybergarage/upnp/IconList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *IconList::ELEM_NAME = "iconList";

////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////

 void IconList::clear()  {
  int nIcon = size();
  for (int n = 0; n < nIcon; n++) {
    Icon *ico = getIcon(n);
    delete ico;
  }
  Vector::clear();
}
