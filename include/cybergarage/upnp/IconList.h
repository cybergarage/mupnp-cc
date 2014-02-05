/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: IconList.h
*
*  Revision;
*
*  07/20/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_ICONLIST_H_
#define _CLINK_ICONLIST_H_

#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/Icon.h>

namespace CyberLink{
class IconList : public uHTTP::Vector {
 public:
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

 public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  IconList() 
  {
  }

  ~IconList() 
  {
    clear();
  }
  
  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////
  
  Icon *getIcon(int n) {
    return (Icon *)get(n);
  }

  void clear();
};

}

#endif



