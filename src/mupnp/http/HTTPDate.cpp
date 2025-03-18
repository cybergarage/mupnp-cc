/******************************************************************
*
*	CyberHTTP for Java
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File : Date.cpp
*
*	Revision;
*
*	01/05/03
*		- first revision
*	06/07/04
*		- Changed to a sub class of CyberUtil::Date.
*	06/10/05
*		- Changed getDateString() to return the string of GMT.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <cybergarage/http/HTTPDate.h>
#include <stdio.h>
#include <stdlib.h>

using namespace CyberHTTP;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

HTTPDate::HTTPDate()
{
}

HTTPDate::HTTPDate(SysTime date) : CyberUtil::Date(date)
{
}

////////////////////////////////////////////////
//	get*String
////////////////////////////////////////////////

const char *HTTPDate::getDateString()
{
#if defined(HAVE_GMTIME_R)
	struct tm gmTimeBuf;
	struct tm *gmTime = &gmTimeBuf;
	gmtime_r(&sysTime, &gmTimeBuf);
#else
	struct tm *gmTime;
	gmTime = gmtime(&sysTime);
#endif

#if defined(HAVE_SNPRINTF)
	snprintf(dateStr, sizeof(dateStr),
#else
	sprintf(dateStr,
#endif
		"%s, %02d %s %04d %02d:%02d:%02d GMT",
		toWeekString(gmTime->tm_wday),
		gmTime->tm_mday,
		toMonthString(gmTime->tm_mon),
		gmTime->tm_year + 1900,
		gmTime->tm_hour,
		gmTime->tm_min,
		gmTime->tm_sec);
		
	return dateStr;
}

////////////////////////////////////////////////
//	Date Util
////////////////////////////////////////////////

static const char MONTH_STRING[][4] = {
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec",
};

static const char WEEK_STRING[][4] = {
	"Sun",
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat",
};

const char *CyberHTTP::toMonthString(int value)
{
	if (0 <= value && value < 12)
		return MONTH_STRING[value];
	return "";
}
	
const char *CyberHTTP::toWeekString(int value)
{
	if (0 <= value && value < 7)
		return WEEK_STRING[value];
	return "";
}

