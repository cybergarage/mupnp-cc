/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File : GatewayDirectory.cpp
*
*	Revision:
*
*	04/14/04
*		- first revision.
*	08/01/04
*		- Added <typeinfo> for typeid() for gcc 2.95.3.
*
******************************************************************/

#include <mupnp/upnp/media/server/ContentDirectory.h>
#include <mupnp/upnp/media/server/ConnectionManager.h>
#include <mupnp/upnp/media/server/object/Format.h>
#include <mupnp/upnp/media/server/object/FormatObject.h>
#include <mupnp/upnp/media/server/directory/gateway/GatewayDirectory.h>
#include <mupnp/io/FileList.h>

#include <typeinfo>
#include <sstream>

using namespace std;
using namespace CyberLink;
using namespace CyberIO;
using namespace CyberXML;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
	
GatewayDirectory::GatewayDirectory(const char *name) : Directory(name)
{
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////
	
void GatewayDirectory::update()
{
}

