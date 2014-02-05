/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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
class ArgumentList : public uHTTP::Vector  {
  bool delElemFlag;

  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
 public:
  static const char *ELEM_NAME;

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
 public:
  ArgumentList(bool delElemFlag = true) 
  {
    this->delElemFlag = delElemFlag;
  }

  ~ArgumentList() 
  {
    clear();
  }

  ////////////////////////////////////////////////
  //  clear
  ////////////////////////////////////////////////

 public:
  void clear();
  
  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////
  
 public:
  Argument *getArgument(int n) {
    return (Argument *)get(n);
  }

  Argument *getArgument(const std::string &name);

  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////
  
 public:
  void set(ArgumentList *inArgList);
};

}

#endif
