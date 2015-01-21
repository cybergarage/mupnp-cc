/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <stdlib.h>

#if defined(WIN32) || defined(__CYGWIN__)
#include <windows.h>
#include <winnls.h>
#else
#include <string.h>
#include <locale.h>
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
#include <iconv.h>
#endif
#endif

#include <mupnp/xml/XML.h>
#include <uhttp/util/StringUtil.h>
#ifndef WIN32
#include <uhttp/util/Mutex.h>
#endif

#include <stdio.h>

using namespace std;
using namespace mUPnP;
using namespace uHTTP;

#ifndef WIN32
static Mutex iconvMutex;
#endif

////////////////////////////////////////////////
// EscapeXMLChars
////////////////////////////////////////////////

const char *mUPnP::XML::EscapeXMLChars(const std::string &in, std::string &out) {
  out = in;
  
  // Thanks for Smolander Visa (09/06/05)
  StringReplaceChars(out, "&", "&amp;");

  StringReplaceChars(out, "<", "&lt;");
  StringReplaceChars(out, ">", "&gt;");
  StringReplaceChars(out, "\"", "&quot;");
  
  // Thanks for Brian Owens (12/02/04)
  StringReplaceChars(out, "'", "&apos;");
  
  return out.c_str();
}

const char *mUPnP::XML::EscapeXMLChars(std::string &in, std::string &out) {
  return EscapeXMLChars(in.c_str(), out);
}
