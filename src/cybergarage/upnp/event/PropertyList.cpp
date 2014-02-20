/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: PropertyList.cpp
*
*  Revision;
*
*  09/08/03
*    - first revision
*  06/30/04
*    - Added addProperty(), insertProperty() and removeProperty();
*
******************************************************************/

#include <cybergarage/upnp/event/Property.h>
#include <cybergarage/upnp/event/PropertyList.h>

using namespace CyberLink;

PropertyList::PropertyList() {
}

PropertyList::~PropertyList()  {
  clear();
}

bool PropertyList::addProperty(Property *prop)  {
  if (prop == NULL)
    return false;
  return add(prop);
}

bool PropertyList::insertProperty(Property *prop, int index)  {
  if (prop == NULL)
    return false;
  return insertAt(prop, index);
}

bool PropertyList::removeProperty(Property *prop)  {
  if (prop == NULL)
    return false;
  bool ret = remove(prop);
  delete prop;
  return ret;
}

 void PropertyList::clear()  {
  int nProp = size();
  for (int n = 0; n < nProp; n++) {
    Property *prop = getProperty(n);
    delete prop;
  }
  Vector::clear();
}
