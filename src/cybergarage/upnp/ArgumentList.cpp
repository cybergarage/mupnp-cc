/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ArgumentList.cpp
*
*  Revision;
*
*  08/21/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/Argument.h>
#include <cybergarage/upnp/ArgumentList.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *ArgumentList::ELEM_NAME = "argumentList";

////////////////////////////////////////////////
//  clear
////////////////////////////////////////////////

void ArgumentList::clear()  {
  if (delElemFlag == true) {
    int nArgs = size();
    for (int n = 0; n < nArgs; n++) {
      Argument *arg = getArgument(n);
      delete arg;
    }
  }
  Vector::clear();
}

////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////

Argument *ArgumentList::getArgument(const std::string &name) {
  int nArgs = size();
  for (int n = 0; n < nArgs; n++) {
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
//  Methods
////////////////////////////////////////////////
  
void ArgumentList::set(ArgumentList *inArgList) {
  int nInArgs = inArgList->size();
  for (int n = 0; n < nInArgs; n++) {
    Argument *inArg = inArgList->getArgument(n);
    const char *inArgName = inArg->getName();
    Argument *arg = getArgument(inArgName);
    if (arg == NULL)
      continue;
    string inArgValue = inArg->getValue();
    arg->setValue(inArgValue.c_str());
  }
}
