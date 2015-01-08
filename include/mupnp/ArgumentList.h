/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ArgumentList.h
*
*  Revision;
*
*  07/21/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_ARGUMENTLIST_H_
#define _CLINK_ARGUMENTLIST_H_

#include <uhttp/util/Vector.h>
#include <uhttp/util/StringUtil.h>
#include <cybergarage/upnp/Argument.h>

namespace CyberLink {
    
class ArgumentList : public uHTTP::Vector<Argument>  {
public:
    
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  ArgumentList(bool delElemFlag = true) {
    setWeekContainer(!delElemFlag);
  }
    
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  Argument *getArgument(size_t n) {
    return get(n);
  }

  Argument *getArgument(const std::string &name);

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  void set(ArgumentList *inArgList);
};

}

#endif
