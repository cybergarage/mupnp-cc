/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ActionList.h
*
*  Revision;
*
*  07/05/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_ACTIONLIST_H_
#define _CLINK_ACTIONLIST_H_

#include <uhttp/util/Vector.h>

namespace CyberLink {
class Action;

class ActionList : public uHTTP::Vector  {
 public:
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  ActionList() 
  {
  }

  ~ActionList() 
  {
    clear();
  }
  
  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////
  
  Action *getAction(int n) {
    return (Action*)get(n);
  }

  void clear();
};

}

#endif
