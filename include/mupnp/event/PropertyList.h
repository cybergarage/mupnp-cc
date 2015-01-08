/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
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
#include <cybergarage/upnp/event/Property.h>

namespace CyberLink {

class PropertyList : public uHTTP::Vector<Property>  {
 public:
    
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  PropertyList() {
  }
  
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////

 public:
  bool addProperty(Property *prop) {
        return add(prop);
  }
  
  bool removeProperty(Property *prop) {
    return remove(prop);
  }
  
  bool insertProperty(Property *prop, int index) {
    return insertAt(prop, index);
  }

  Property *getProperty(size_t n) {
    return get(n);
  }
};

}

#endif
