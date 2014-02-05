/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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
class AttributeList : public uHTTP::Vector {
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  AttributeList();
  
  ~AttributeList();
  

  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////

 public:
  bool addAttribute(Attribute *attr);
  bool insertAttribute(Attribute *attr, int index);
  bool removeAttribute(Attribute *attr);

  Attribute *getAttribute(int n) {
    return (Attribute *)Vector::get(n);
  }

  Attribute *getAttribute(const std::string &name);


  ////////////////////////////////////////////////
  //  clear
  ////////////////////////////////////////////////

 public:
  void clear();
};

}

#endif
