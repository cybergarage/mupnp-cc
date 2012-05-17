/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : PNGFormat.cpp
*
*	Revision:
*
*	04/18/04
*		- first revision.
*
******************************************************************/

#include <stdio.h>
#include <string.h>

#include <cybergarage/upnp/media/server/object/format/PNGFormat.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

PNGFormat::PNGFormat()
{
}
	
PNGFormat::PNGFormat(uHTTP::File *file)
{
	setFile(file);
}

////////////////////////////////////////////////
// Abstract Methods
////////////////////////////////////////////////
	
bool PNGFormat::equals(uHTTP::File *file)
{
	if (file == NULL)
		return false;

	const char *filename = file->getName();
	if (filename == NULL)
		return false;

	FILE *fp = fopen(filename, "rb");
	if (!fp)	
		return false;
	unsigned char signature[5];
	if (fread(signature, 5, 1, fp) != 1) {
		fclose(fp);
		return false;
	}
	fclose(fp);

	if (!strncmp("PNG", (char *)(signature+1), 3))
		return true;

	return false;
}

