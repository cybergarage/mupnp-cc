/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : JPEGFormat.cpp
*
*	Revision:
*
*	04/18/04
*		- first revision.
*
******************************************************************/

#include <stdio.h>
#include <cybergarage/upnp/media/server/object/format/JPEGFormat.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

JPEGFormat::JPEGFormat()
{
}
	
JPEGFormat::JPEGFormat(uHTTP::File *file)
{
	setFile(file);
}

////////////////////////////////////////////////
// Abstract Methods
////////////////////////////////////////////////
	
bool JPEGFormat::equals(uHTTP::File *file)
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

	if (signature[0] == 0xff && signature[1] == 0xd8)
		return true;

	return false;
}

