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

#include <cybergarage/upnp/media/server/ContentDirectory.h>
#include <cybergarage/upnp/media/server/ConnectionManager.h>
#include <cybergarage/upnp/media/server/object/Format.h>
#include <cybergarage/upnp/media/server/object/FormatObject.h>
#include <cybergarage/upnp/media/server/directory/gateway/GatewayDirectory.h>

#include <typeinfo>
#include <sstream>

using namespace std;
using namespace CyberLink;
using namespace CyberXML;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
	
GatewayDirectory::GatewayDirectory(const std::string &name) : Directory(name)
{
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////
	
void GatewayDirectory::update()
{
}

