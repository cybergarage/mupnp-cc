/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: AttributeList.h
*
*  Revision;
*
*  04/22/03
*    - first revision
*
******************************************************************/

#ifndef _CXML_ATTRIBUTELIST_H_
#define _CXML_ATTRIBUTELIST_H_

#include <uhttp/util/Vector.h>
#include <cybergarage/xml/Attribute.h>

namespace CyberXML {

class AttributeList : public uHTTP::Vector<Attribute> {
public:
  
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  AttributeList() {
  }
  
public:
  
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  bool addAttribute(Attribute *attr) {
    return Vector::add(attr);
  }
  
  bool insertAttribute(Attribute *attr, int index) {
    return Vector::insertAt(attr, index);
    
  }
  
  bool removeAttribute(Attribute *attr) {
    return Vector::remove(attr);
  }

  Attribute *getAttribute(size_t n) {
    return Vector::get(n);
  }

  Attribute *getAttribute(const std::string &name);
};

}

#endif
