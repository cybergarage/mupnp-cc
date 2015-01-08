/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002
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

Attribute *AttributeList::getAttribute(const std::string &name)  {
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    Attribute *elem = getAttribute(n);
    if (uHTTP::StringEquals(name, elem->getName()) == true)
      return elem;
  }
  return NULL;
}
