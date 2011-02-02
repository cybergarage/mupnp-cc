/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: XML.h
*
*	Revision;
*
*	03/23/03
*		- first revision.
*	
******************************************************************/

#ifndef _CXML_XML_H_
#define _CXML_XML_H_

#include <string>

namespace CyberXML {

typedef unsigned char UnicodeStr;

namespace XML {

const char VERSION_HEADER[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
const char CONTENT_TYPE[] = "text/xml; charset=\"utf-8\"";

const char *EscapeXMLChars(const char *in, std::string &out);
const char *EscapeXMLChars(std::string &in, std::string &out);

UnicodeStr *Local2Unicode(const char *str, int &len);
const char *Unicode2Local(UnicodeStr *str, int &len);

}

}

#endif
