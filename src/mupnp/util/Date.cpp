/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File : Date.cpp
*
*	Revision;
*
*	01/05/03
*		- first revision
*	12/16/04
*		- Added support for BTRON
*		- Changed to use localtime_r instead of localtime
*
******************************************************************/

#include <cybergarage/util/Date.h>

#include <stdio.h>
#include <stdlib.h>

using namespace CyberUtil;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

Date::Date()
{
#if defined(BTRON) || defined(TENGINE) 
	TIMEZONE tz;
	if (get_tim(&sysTime, &tz) != 0)
		sysTime = 0;
	get_tod(&localDate, sysTime, True);
#elif defined(ITRON)
	SYSTIM localTime;
	get_tim(&localTime);
	sysTime = (localTime.ltime / 1000) + ((localTime.utime / 1000) << 32);
	time2LocalDate(sysTime);
#else
	time(&sysTime);
	#ifdef HAVE_LOCALTIME_R
	localtime_r(&sysTime, &localDate);
	#else
	localDate = localtime(&sysTime);
	#endif
#endif
}

Date::Date(SysTime value)
{
	sysTime = value;
#if defined(BTRON) || defined(TENGINE) 
	get_tod(&localDate, sysTime, True);
#elif defined(ITRON)
	time2LocalDate(sysTime);
#else
	#ifdef HAVE_LOCALTIME_R
	localtime_r(&sysTime, &localDate);
	#else
	localDate = localtime(&sysTime);
	#endif
#endif
}

Date::Date(
	int year,
	int month,
	int day,
	int hour,
	int min,
	int sec)
{
#if defined(BTRON) || defined(TENGINE) 
	DATE_TIM dt;
	dt.d_sec = sec;
	dt.d_min = min;
	dt.d_hour = hour;
	dt.d_day = day;
	dt.d_month = month;
	dt.d_year = year - 1900;
	dt.d_wday = 0;
	dt.d_week = 0;
	dt.d_days = 0;
	set_tod(&dt, &sysTime, False);
	get_tod(&localDate, sysTime, True);
#elif defined(ITRON)
	this->sec = sec;
	this->min = min;
	this->hour = hour;
	this->day = day;
	this->month = month;
	this->year = year;
	sysTime = 0;
#else
	struct tm tmval;
	tmval.tm_sec = sec;
	tmval.tm_min = min;
	tmval.tm_hour = hour;
	tmval.tm_mday = day;
	tmval.tm_mon = month - 1;
	tmval.tm_year = year - 1900;
	tmval.tm_wday = 0;
	tmval.tm_yday = 0;
	tmval.tm_isdst = 0;

	sysTime = mktime(&tmval);
	#ifdef HAVE_LOCALTIME_R
	localtime_r(&sysTime, &localDate);
	#else
	localDate = localtime(&sysTime);
	#endif
#endif
}

////////////////////////////////////////////////
//	Date
////////////////////////////////////////////////

int Date::getYear()
{
#if defined(BTRON) || defined(TENGINE) 
	return localDate.d_year + 1900;
#elif defined(ITRON)
	return year;
#else
	#ifdef HAVE_LOCALTIME_R
	return localDate.tm_year + 1900;
	#else
	return localDate->tm_year + 1900;
	#endif
#endif
}

int Date::getMonth()
{
#if defined(BTRON) || defined(TENGINE) 
	return localDate.d_month;
#elif defined(ITRON)
	return month + 1;
#else
	#ifdef HAVE_LOCALTIME_R
	return localDate.tm_mon + 1;
	#else
	return localDate->tm_mon + 1;
	#endif
#endif
}

int Date::getDay()
{
#if defined(BTRON) || defined(TENGINE) 
	return localDate.d_day;
#elif defined(ITRON)
	return day;
#else
	#ifdef HAVE_LOCALTIME_R
	return localDate.tm_mday;
	#else
	return localDate->tm_mday;
	#endif
#endif
}

int Date::getWeekDay()
{
#if defined(BTRON) || defined(TENGINE) 
	return localDate.d_wday;
#elif defined(ITRON)
	return week;
#else
	#ifdef HAVE_LOCALTIME_R
	return localDate.tm_wday;
	#else
	return localDate->tm_wday;
	#endif
#endif
}

////////////////////////////////////////////////
//	Time
////////////////////////////////////////////////

int Date::getHour()
{
#if defined(BTRON) || defined(TENGINE) 
	return localDate.d_hour;
#elif defined(ITRON)
	return hour;
#else
	#ifdef HAVE_LOCALTIME_R
	return localDate.tm_hour;
	#else
	return localDate->tm_hour;
	#endif
#endif
}

int Date::getMinute()
{
#if defined(BTRON) || defined(TENGINE) 
	return localDate.d_min;
#elif defined(ITRON)
	return min;
#else
	#ifdef HAVE_LOCALTIME_R
	return localDate.tm_min;
	#else
	return localDate->tm_min;
	#endif
#endif
}

int Date::getSecond()
{
#if defined(BTRON) || defined(TENGINE) 
	return localDate.d_sec;
#elif defined(ITRON)
	return sec;
#else
	#ifdef HAVE_LOCALTIME_R
	return localDate.tm_sec;
	#else
	return localDate->tm_sec;
	#endif
#endif
}

////////////////////////////////////////////////
//	time2LocalDate
////////////////////////////////////////////////

#if defined(ITRON)

static const int dayYear[ ] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const int dayLearYear[ ] = {
	31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static bool IsLeapYear(int year)
{
    if (!(year % 4) && ((year % 100) || !(year % 400)))
        return true;
	return false;
}

bool Date::time2LocalDate(SysTime uxtime)
{
	sec = uxtime % 60;
	uxtime -= sec;
	uxtime /= 60;

	min = uxtime % 60;
	uxtime -= min;
	uxtime /= 60;

	hour = uxtime % 24;
	uxtime -= hour;
	uxtime /= 24;

	week = uxtime % 7;

	year = 1970;
	day = uxtime;
	while (day > 366) {
		if (IsLeapYear(year))
			day -= 366;
		else
			day -= 365;
		year++;
    }
	day++;

	month = 0;
	while (1) {					
		if (IsLeapYear(year)) {
			if (day <= dayLearYear[month])
				break;
			day -= dayLearYear[month];
			month++;
		} else {
			if (day <= dayYear[month])
				break;
			day -= dayYear[month];
			month++;
		}
	}
}

#endif
