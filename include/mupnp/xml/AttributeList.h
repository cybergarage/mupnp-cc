/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ATTRIBUTELIST_H_
#define _MUPMPCC_ATTRIBUTELIST_H_

#include <mupnp/common/Vector.h>
#include <mupnp/xml/Attribute.h>

namespace uXML {

class AttributeList : public mUPnP::Vector<Attribute> {
  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  AttributeList()
  {
  }

  public:
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////

  bool addAttribute(Attribute* attr)
  {
    return Vector::add(attr);
  }

  bool insertAttribute(Attribute* attr, int index)
  {
    return Vector::insertAt(attr, index);
  }

  bool removeAttribute(Attribute* attr)
  {
    return Vector::remove(attr);
  }

  Attribute* getAttribute(size_t n)
  {
    return Vector::get(n);
  }

  Attribute* getAttribute(const std::string& name);
};

}

#endif
