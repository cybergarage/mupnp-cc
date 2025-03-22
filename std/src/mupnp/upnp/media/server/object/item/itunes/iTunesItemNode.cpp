/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2003
 *
 *	File : iTunesItemNode.java
 *
 *	Revision:
 *
 *	03/14/06
 *		- first revision.
 *
 ******************************************************************/

#include <mupnp/upnp/media/server/ContentDirectory.h>
#include <mupnp/upnp/media/server/object/Format.h>
#include <mupnp/upnp/media/server/object/item/itunes/iTunesItemNode.h>

using namespace CyberLink;
using namespace CyberIO;

////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////

iTunesItemNode::iTunesItemNode()
{
  setFile(NULL);
}

////////////////////////////////////////////////
// Abstract methods
////////////////////////////////////////////////

const char* iTunesItemNode::getContent(std::string& buf)
{
  buf = "";
  if (itemFile == NULL)
    itemFile->load(buf);
  return buf.c_str();
}

CyberIO::InputStream* iTunesItemNode::getContentInputStream()
{
  if (itemFile == NULL)
    return NULL;
  return new FileInputStream(itemFile, File::O_BINARY);
}

const char* iTunesItemNode::getMimeType()
{
  ContentDirectory* cdir = getContentDirectory();
  CyberIO::File* itemFile = getFile();
  Format* itemFormat = cdir->getFormat(itemFile);
  if (itemFormat == NULL) {
    return "*/*";
  }
  return itemFormat->getMimeType();
}
