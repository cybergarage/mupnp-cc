/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: FormatList.cpp
*
*	Revision;
*
*	03/24/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/Format.h>
#include <cybergarage/upnp/media/server/object/FormatList.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

Format *FormatList::getFormat(const char *type) 
{
	if (type == NULL)
		return NULL;
	std::string typeStr = type;
	int nLists = size(); 
	for (int n=0; n<nLists; n++) {
		Format *format = getFormat(n);
		if (typeStr.compare(format->getMimeType()) == 0)
			return format;
	}
	return NULL;
}

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

Format *FormatList::getFormat(CyberIO::File *file) 
{
	if (file == NULL)
		return NULL;
	int nLists = size(); 
	for (int n=0; n<nLists; n++) {
		Format *format= getFormat(n);
		if (format->equals(file) == true)
			return format;
	}
	return NULL;
}

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void FormatList::clear() 
{
	int nNode = size();
	for (int n=0; n<nNode; n++) {
		Format *format = getFormat(n);
		delete format;
	}
	Vector::clear();
}


