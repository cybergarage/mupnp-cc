/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2002
 *
 *	File : GIFFormat.cpp
 *
 *	Revision:
 *
 *	01/25/04
 *		- first revision.
 *
 ******************************************************************/

#include <mupnp/upnp/media/server/object/format/GIFFormat.h>
#include <stdio.h>
#include <string.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

GIFFormat::GIFFormat()
{
}

GIFFormat::GIFFormat(CyberIO::File* file)
{
  setFile(file);
}

////////////////////////////////////////////////
// Abstract Methods
////////////////////////////////////////////////

bool GIFFormat::equals(CyberIO::File* file)
{
  if (file == NULL)
    return false;

  const char* filename = file->getName();
  if (filename == NULL)
    return false;

  FILE* fp = fopen(filename, "rb");
  if (!fp)
    return false;
  unsigned char signature[5];
  if (fread(signature, 5, 1, fp) != 1) {
    fclose(fp);
    return false;
  }
  fclose(fp);

  if (!strncmp("GIF", (char*)signature, 3))
    return true;

  return false;
}
