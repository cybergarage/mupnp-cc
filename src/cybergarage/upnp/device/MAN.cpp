/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: MAN.cpp
*
*	Revision:
*
*	07/08/03
*		- first revision
*	08/21/05
*		- Changed IsDiscover() using string instead of ostringstream.
*
******************************************************************/

#include <cybergarage/upnp/device/MAN.h>
#include <cybergarage/util/StringUtil.h>

using namespace std;
using namespace CyberUtil;

bool CyberLink::MAN::IsDiscover(const char *value)
{
	if (value == NULL)
		return false;
	CyberUtil::String manStr = value;
	if (manStr.equals(DISCOVER) == true)
		return true;
	string quoteDiscoverStr;
	quoteDiscoverStr.append("\"");
	quoteDiscoverStr.append(DISCOVER);
	quoteDiscoverStr.append("\"");
	return manStr.equals(quoteDiscoverStr.c_str());
}
