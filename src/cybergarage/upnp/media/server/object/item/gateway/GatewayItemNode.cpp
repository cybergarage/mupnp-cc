/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2005
*
*	File : GatewayItemNode.java
*
*	Revision:
*
*	11/15/05
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/ContentDirectory.h>
#include <cybergarage/upnp/media/server/object/Format.h>
#include <cybergarage/upnp/media/server/object/item/gateway/GatewayItemNode.h>

using namespace CyberLink;
using namespace uHTTP;

////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////
	
GatewayItemNode::GatewayItemNode()
{
	setFile(NULL);
}

////////////////////////////////////////////////
// Abstract methods
////////////////////////////////////////////////

const char *GatewayItemNode::getContent(std::string &buf)
{
	buf = "";
	if (itemFile == NULL)
		itemFile->load(buf);
	return buf.c_str();
}

uHTTP::InputStream *GatewayItemNode::getContentInputStream()
{
	if (itemFile == NULL)
		return NULL;
	return new FileInputStream(itemFile, File::O_BINARY);
}

const char *GatewayItemNode::getMimeType()
{
	ContentDirectory *cdir = getContentDirectory();
	uHTTP::File *itemFile = getFile();
	Format *itemFormat = cdir->getFormat(itemFile);
	if (itemFormat == NULL) {
		return "*/*";
	}
	return itemFormat->getMimeType();
}



