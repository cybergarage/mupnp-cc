/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File : Date.h
*
*	Revision;
*
*	03/16/03
*		- first revision
*
******************************************************************/

#ifndef _CUTIL_DATE_H_
#define _CUTIL_DATE_H_

#if defined(WIN32) && defined(ITRON) && defined (_AFXDLL)
#include <afxwin.h>
#endif

#if defined(BTRON) || defined(TENGINE) 
#include <typedef.h>
#include <btron/proctask.h>
#include <btron/clk.h>
#include <time.h>
#elif defined(ITRON)
#include <kernel.h>
#else
#include <time.h>
#endif

#if defined(TENGINE)
typedef STIME SysTime;
#elif defined(ITRON)
typedef long SysTime;
#else
typedef time_t SysTime;
#endif

namespace CyberUtil {

class Date
{

protected:

	SysTime sysTime;
#if defined(TENGINE) 
	DATE_TIM localDate;
#elif defined(ITRON)
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
	int week;
#elif HAVE_LOCALTIME_R
	struct tm localDate;
#else
	struct tm *localDate;
#endif

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	Date();
	Date(SysTime value);
	Date(
		int year,
		int month,
		int day,
		int hour = 0,
		int min = 0,
		int sec = 0);

	////////////////////////////////////////////////
	//	get*
	////////////////////////////////////////////////

public:

	SysTime getValue()
	{
		return sysTime;
	}

	////////////////////////////////////////////////
	//	Date
	////////////////////////////////////////////////

public:

	int getYear();
	int getMonth();
	int getDay();
	int getWeekDay();

	////////////////////////////////////////////////
	//	Time
	////////////////////////////////////////////////

public:

	int getHour();
	int getMinute();
	int getSecond();

	////////////////////////////////////////////////
	//	Utility
	////////////////////////////////////////////////

private:

#if defined(ITRON)
	bool time2LocalDate(SysTime sysTime);
#endif

};

}

#endif
