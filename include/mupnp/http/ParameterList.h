/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_PARAMETERLIST_H_
#define _UHTTP_PARAMETERLIST_H_

#include <mupnp/http/Parameter.h>
#include <mupnp/util/StringUtil.h>
#include <mupnp/util/Vector.h>

namespace uHTTP {

class ParameterList : public ::uHTTP::SharedVector<Parameter> {
  public:
  ParameterList()
  {
  }

  Parameter* at(size_t n)
  {
    return get(n).get();
  }

  Parameter* getParameter(int n)
  {
    return get(n).get();
  }

  Parameter* getParameter(const std::string& name)
  {
    size_t nLists = size();
    for (size_t n = 0; n < nLists; n++) {
      Parameter* param = at(n);
      if (uHTTP::StringEquals(name, param->getName()) == true)
        return param;
    }
    return nullptr;
  }

  bool getParameterValue(const std::string& name, std::string* value)
  {
    Parameter* param = getParameter(name);
    if (!param)
      return false;
    *value = param->getValue();
    return true;
  }
};

}

#endif
