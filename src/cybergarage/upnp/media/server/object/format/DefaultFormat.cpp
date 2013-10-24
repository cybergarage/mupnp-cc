/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : ImageFormat.cpp
*
*	Revision:
*
*	04/16/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/format/DefaultFormat.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// title
////////////////////////////////////////////////

const char *DefaultFormat::getTitle(std::string &buf)
{
	if (file == NULL) {
		buf = "";
		return buf.c_str();
	}
	string fname;
	file->getFileName(fname);
	int idx = fname.rfind(".");
	if (idx < 0)
		return "";
	buf = fname.substr(0, idx);
	return buf.c_str();
}
	
