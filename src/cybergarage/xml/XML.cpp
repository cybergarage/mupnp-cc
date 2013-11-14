/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: XML.cpp
*
*  Revision;
*
*  03/10/04
*    - first revision
*  05/10/04
*    - Added Local2Unicode.
*  05/19/04
*    - Added some defines for Cygwin.
*  06/01/04
*    - Changed Added UnicodeStr from unsinged short to unsigned char.
*  08/01/04
*    - Added <stdio.h> for sprintf() for gcc 2.95.3.
*  12/02/04
*    - Brian Owens <brian@b-owens.com>
*    - Fixed EscapeXMLChars() to convert from "'" to "&apos;" instead of "\".
*  12/16/04
*    - Added support for BTRON
*  09/06/06
*    - Thanks for Smolander Visa <visa.smolander@nokia.com>
*    - Changed EscapeXMLChars() to process the '&' character at first for libxml2.
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

#include <cybergarage/xml/XML.h>
#include <uhttp/util/StringUtil.h>
#ifndef WIN32
#include <uhttp/util/Mutex.h>
#endif

#include <stdio.h>

using namespace std;
using namespace CyberXML;
using namespace uHTTP;

#ifndef WIN32
static Mutex iconvMutex;
#endif

////////////////////////////////////////////////
//  EscapeXMLChars
////////////////////////////////////////////////

const char *CyberXML::XML::EscapeXMLChars(const std::string &in, std::string &out)
{
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

const char *CyberXML::XML::EscapeXMLChars(std::string &in, std::string &out)
{
  return EscapeXMLChars(in.c_str(), out);
}
