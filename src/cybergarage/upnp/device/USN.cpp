/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: USN.cpp
*
*	Revision:
*
*	07/07/03
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/device/USN.h>
#include <cybergarage/util/StringUtil.h>

bool CyberLink::USN::IsRootDevice(const char *usnValue)
{
	if (usnValue == NULL)
		return false;
	CyberUtil::String usnStr = usnValue;
	return usnStr.endsWith(ROOTDEVICE);
}
	
const char *CyberLink::USN::GetUDN(const char *usnValue, std::string &udn)
{
	if (usnValue == NULL)
		return "";
	CyberUtil::String usnStr = usnValue;
	int idx = usnStr.indexOf("::");
	if (idx < 0)
		return usnStr.trim();
	CyberUtil::String udnStr(usnStr.getValue(), 0, idx);
	udn = udnStr.trim();
	return udn.c_str();
}
