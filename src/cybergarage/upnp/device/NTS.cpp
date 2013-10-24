<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NTS.cpp
*
*	Revision;
*
*	07/07/03
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/device/NTS.h>
#include <uhttp/util/StringUtil.h>
	
bool CyberLink::NTS::IsAlive(const std::string &ntsValue)
{
	uHTTP::String ntsStr = ntsValue;
	return ntsStr.startsWith(ALIVE);
}

bool CyberLink::NTS::IsByeBye(const std::string &ntsValue)
{
	uHTTP::String ntsStr = ntsValue;
	return ntsStr.startsWith(BYEBYE);
}

=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NTS.cpp
*
*	Revision;
*
*	07/07/03
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/device/NTS.h>
#include <cybergarage/util/StringUtil.h>
	
bool CyberLink::NTS::IsAlive(const char *ntsValue)
{
	if (ntsValue == NULL)
		return false;
	CyberUtil::String ntsStr = ntsValue;
	return ntsStr.startsWith(ALIVE);
}

bool CyberLink::NTS::IsByeBye(const char *ntsValue)
{
	if (ntsValue == NULL)
		return false;
	CyberUtil::String ntsStr = ntsValue;
	return ntsStr.startsWith(BYEBYE);
}

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
