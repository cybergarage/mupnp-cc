<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NT.cpp
*
*	Revision:
*
*	07/07/03
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/device/NT.h>
#include <uhttp/util/StringUtil.h>

bool CyberLink::NT::IsRootDevice(const std::string &ntValue)
{
	uHTTP::String ntStr = ntValue;
	return ntStr.startsWith(ROOTDEVICE);
}
=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NT.cpp
*
*	Revision:
*
*	07/07/03
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/device/NT.h>
#include <cybergarage/util/StringUtil.h>

bool CyberLink::NT::IsRootDevice(const char *ntValue)
{
	if (ntValue == NULL)
		return false;
	CyberUtil::String ntStr = ntValue;
	return ntStr.startsWith(ROOTDEVICE);
}
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
