/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_XML_H_
#define _MUPMPCC_XML_H_

#include <string>

namespace uXML {

typedef unsigned char UnicodeStr;

namespace XML {
const char VERSION_HEADER[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
const char CONTENT_TYPE[] = "text/xml; charset=\"utf-8\"";

const char *EscapeXMLChars(const std::string &in, std::string &out);
const char *EscapeXMLChars(std::string &in, std::string &out);

}

}

#endif
