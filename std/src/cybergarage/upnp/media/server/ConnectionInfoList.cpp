/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ConnectionInfoList.cpp
*
*	Revision;
*
*	06/19/04
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/media/server/ConnectionInfoList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	clear
////////////////////////////////////////////////

void ConnectionInfoList::clear() 
{
	int nInfos = size();
	for (int n=0; n<nInfos; n++) {
		ConnectionInfo *info = getConnectionInfo(n);
		delete info;
	}
	Vector::clear();
}
