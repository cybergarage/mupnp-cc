/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/util/StringUtil.h>
#include <mupnp/xml/AttributeList.h>

uXML::Attribute* uXML::AttributeList::getAttribute(const std::string& name)
{
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    Attribute* elem = getAttribute(n);
    if (uHTTP::StringEquals(name, elem->getName()) == true)
      return elem;
  }
  return nullptr;
}
