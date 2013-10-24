/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: XML.cpp
*
*	Revision;
*
*	03/10/04
*		- first revision
*	05/10/04
*		- Added Local2Unicode.
*	05/19/04
*		- Added some defines for Cygwin.
*	06/01/04
*		- Changed Added UnicodeStr from unsinged short to unsigned char.
*	08/01/04
*		- Added <stdio.h> for sprintf() for gcc 2.95.3.
*	12/02/04
*		- Brian Owens <brian@b-owens.com>
*		- Fixed EscapeXMLChars() to convert from "'" to "&apos;" instead of "\".
*	12/16/04
*		- Added support for BTRON
*	09/06/06
*		- Thanks for Smolander Visa <visa.smolander@nokia.com>
*		- Changed EscapeXMLChars() to process the '&' character at first for libxml2.
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
<<<<<<< HEAD
#include <uhttp/util/StringUtil.h>
#ifndef WIN32
#include <uhttp/util/Mutex.h>
=======
#include <cybergarage/util/StringUtil.h>
#ifndef WIN32
#include <cybergarage/util/Mutex.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#endif

#include <stdio.h>

using namespace std;
using namespace CyberXML;
<<<<<<< HEAD
using namespace uHTTP;
=======
using namespace CyberUtil;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

#ifndef WIN32
static Mutex iconvMutex;
#endif

////////////////////////////////////////////////
//	EscapeXMLChars
////////////////////////////////////////////////

<<<<<<< HEAD
const char *CyberXML::XML::EscapeXMLChars(const std::string &in, std::string &out)
=======
const char *CyberXML::XML::EscapeXMLChars(const char *in, std::string &out)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
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
<<<<<<< HEAD
=======

////////////////////////////////////////////////
//	Local2Unicode
////////////////////////////////////////////////

UnicodeStr *CyberXML::XML::Local2Unicode(const char *str, int &outLen)
{
#if defined(WIN32) || defined(__CYGWIN__)
	// ANSI -> Unicode
	outLen = MultiByteToWideChar(CP_OEMCP, 0, str, -1, NULL, 0);
	if (outLen == 0)
		return NULL;
	LPWSTR unistr = new WCHAR[outLen+1];
	outLen = MultiByteToWideChar(CP_OEMCP, 0, str, -1, unistr, outLen);
	if (outLen == 0) {
		delete []unistr;
		return NULL;
	}

	// Unicode -> UTF-8
	outLen = WideCharToMultiByte(CP_UTF8, 0, unistr, -1, NULL, 0, NULL, NULL);
	if (outLen == 0)
		return NULL;
	UnicodeStr *utf8str = new UnicodeStr[outLen+1];
	outLen = WideCharToMultiByte(CP_UTF8, 0, unistr, -1, (LPSTR)utf8str, outLen, NULL, NULL);
	delete []unistr;
	if (outLen == 0) {
		delete []utf8str;
		return NULL;
	}
	utf8str[outLen] = '\0';
	return utf8str;
#elif defined(HAVE_ICONV) || defined(HAVE_ICONV_H)
	iconvMutex.lock();

	char *cpbuf = strdup(str);
	if (cpbuf == NULL)
		return NULL;
	char *inbuf = cpbuf;
	size_t inbyteleft = strlen(str);
	size_t outbufSize = inbyteleft * sizeof(UnicodeStr) * 4;
	UnicodeStr *outbuf = new UnicodeStr[outbufSize + 1];
	size_t outbyteleft = outbufSize;

	char *lcEnc = "iso-8859-1";
	char *lcCtype = setlocale (LC_CTYPE, "");
	if (lcCtype != NULL) {
	        char *sep = strchr(lcCtype, '.');
        	if (sep != NULL)
        	    lcEnc = sep + 1;
	}

	iconv_t cd = iconv_open("UTF-8", lcEnc);
	if (cd == (iconv_t)-1) {
		perror("iconv_open");
		free(cpbuf);
	   	iconvMutex.unlock();
		return NULL;
	}

	UnicodeStr *unistr;

	char *coutbuf = (char *)outbuf;
	size_t ret = iconv(cd, &inbuf, &inbyteleft, &coutbuf, &outbyteleft);
	if (ret == (size_t)-1) {
		perror("iconv");
		unistr = NULL;
		outLen = 0;
		delete []outbuf;
	}
	else {
		unistr = outbuf;
		outLen = outbufSize - outbyteleft;
		unistr[outLen] = '\0';
	}

	iconv_close (cd);

	free(cpbuf);
   	iconvMutex.unlock();

	return unistr;
#else
	outLen = strlen(str);
	UnicodeStr *utf8str = new UnicodeStr[outLen+1];
	memcpy(utf8str, str, outLen);
	utf8str[outLen] = '\0';
	return utf8str;
#endif
}
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
