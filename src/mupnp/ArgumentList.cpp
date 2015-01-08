/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ArgumentList.cpp
*
*  Revision;
*
*  08/21/03
*    - first revision
*
******************************************************************/

#include <mupnp/Argument.h>
#include <mupnp/ArgumentList.h>

using namespace std;
using namespace mUPnP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *ArgumentList::ELEM_NAME = "argumentList";

////////////////////////////////////////////////
// getArgument
////////////////////////////////////////////////

Argument *ArgumentList::getArgument(const std::string &name) {
  size_t nArgs = size();
  for (size_t n = 0; n < nArgs; n++) {
    Argument *arg = getArgument(n);
    const char *argName = arg->getName();
    if (argName == NULL)
      continue;
    uHTTP::String argNameStr(argName);
    if (argNameStr.equals(name) == true)
      return arg;
  }
  return NULL;
}

////////////////////////////////////////////////
// set
////////////////////////////////////////////////
  
void ArgumentList::set(ArgumentList *inArgList) {
  size_t nInArgs = inArgList->size();
  for (size_t n = 0; n < nInArgs; n++) {
    Argument *inArg = inArgList->getArgument(n);
    const char *inArgName = inArg->getName();
    Argument *arg = getArgument(inArgName);
    if (arg == NULL)
      continue;
    string inArgValue = inArg->getValue();
    arg->setValue(inArgValue.c_str());
  }
}
