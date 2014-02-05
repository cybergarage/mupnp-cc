/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: PropertyList.h
*
*  Revision;
*
*  09/08/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_PROPERTYLIST_H_
#define _CLINK_PROPERTYLIST_H_

#include <uhttp/util/Vector.h>

namespace CyberLink {
class Property;

class PropertyList : public uHTTP::Vector  {
 public:
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
 public:
  PropertyList();

  ~PropertyList();
  
  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////

 public:
  bool addProperty(Property *prop);
  bool removeProperty(Property *prop);
  bool insertProperty(Property *prop, int index);

  Property *getProperty(int n) {
    return (Property *)get(n);
  }

  ////////////////////////////////////////////////
  // clear
  ////////////////////////////////////////////////

 public:
  void clear();
};

}

#endif
