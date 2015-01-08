/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: Description.h
*
*  Revision;
*
*  07/08/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_DESCRIPTON_H_
#define _MUPMPCC_DESCRIPTON_H_

#include <sstream>
#include <uhttp/util/StringUtil.h>

namespace mUPnP {
namespace Description {
const char LOADING_EXCEPTION[] = "Couldn't load a specified description file ";
const char NOROOT_EXCEPTION[] = "Couldn't find a root node";
const char NOROOTDEVICE_EXCEPTION[] = "Couldn't find a root device node";

}

}

#endif

