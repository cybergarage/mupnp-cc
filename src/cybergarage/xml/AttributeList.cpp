/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: AttributeList.cpp
*
*  Revision:
*
*  04/22/03
*    - first revision
*  06/30/04
*    - Added addAttribute(), insertAttribute() and removeAttribute();
*
******************************************************************/

#include <cybergarage/xml/AttributeList.h>
#include <uhttp/util/StringUtil.h>

using namespace CyberXML;

AttributeList::AttributeList()  {
}

AttributeList::~AttributeList()  {
  clear();
}

bool AttributeList::addAttribute(Attribute *attr)  {
  if (attr == NULL)
    return false;
  return add(attr);
}

bool AttributeList::insertAttribute(Attribute *attr, int index)  {
  if (attr == NULL)
    return false;
  return insertAt(attr, index);
}

bool AttributeList::removeAttribute(Attribute *attr)  {
  if (attr == NULL)
    return false;
  bool ret = remove(attr);
  delete attr;
  return ret;
}
  
Attribute *AttributeList::getAttribute(const std::string &name)  {
  int nLists = size(); 
  for (int n = 0; n < nLists; n++) {
    Attribute *elem = getAttribute(n);
    if (uHTTP::StringEquals(name, elem->getName()) == true)
      return elem;
  }
  return NULL;
}

void AttributeList::clear() {
  int nLists = size(); 
  for (int n = 0; n < nLists; n++) {
    Attribute *attr = getAttribute(n);
    if (attr != NULL)
      delete attr;
  }
  Vector::clear();
}
