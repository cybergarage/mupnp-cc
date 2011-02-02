/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ConnectionInfo.cpp
*
*	Revision;
*
*	06/19/04
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/media/server/ConnectionInfo.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *ConnectionInfo::INPUT = "Input";
const char *ConnectionInfo::OUTPUT = "Output";
const char *ConnectionInfo::OK = "OK";
const char *ConnectionInfo::UNKNOWN = "Unknown";

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

ConnectionInfo::ConnectionInfo(int id)
{
	setID(id);
	setRcsID(-1);
	setAVTransportID(-1);
	setProtocolInfo("");
	setPeerConnectionManager("");
	setPeerConnectionID(-1);
	setDirection(OUTPUT);
	setStatus(UNKNOWN);
}

ConnectionInfo::~ConnectionInfo()
{
}
