/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NTS.h
*
*	Revision;
*
*	07/07/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_NTS_H_
#define _CLINK_NTS_H_

namespace CyberLink {

namespace NTS {

const char ALIVE[] = "ssdp:alive";
const char BYEBYE[] = "ssdp:byebye";
const char PROPCHANGE[] = "upnp:propchange";
	
bool IsAlive(const char *ntsValue);
bool IsByeBye(const char *ntsValue);

}

}

#endif

