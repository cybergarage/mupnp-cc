/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ARGUMENTLIST_H_
#define _MUPMPCC_ARGUMENTLIST_H_

#include <uhttp/util/Vector.h>
#include <uhttp/util/StringUtil.h>
#include <mupnp/Argument.h>

namespace mUPnP {
    
class ArgumentList : public Vector<Argument>  {
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
