/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : Clock.cpp
*
*	08/01/04
*		- Added <stdio.h> for sprintf() for gcc 2.95.3.
*
******************************************************************/

#include "Clock.h"
#include <stdio.h>

////////////////////////////////////////////////
//	getDateString
////////////////////////////////////////////////

static const char *MONTH_STRING[] = {
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

static const char *toMonthString(int value)
{
	if (0 <= value && value < 12)
		return MONTH_STRING[value];
	return "";
}
	
static const char *WEEK_STRING[] = {
	"Sun",
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat",
};

static const char *toWeekString(int value)
{
	if (0 <= value && value < 7)
		return WEEK_STRING[value];
	return "";
}
	
const char *Clock::getDateString(std::string &sbuf)
{
	char buf[64];
	sprintf(buf, "%s, %s %d, %02d",
		toWeekString(getWeek()),
		toMonthString(getMonth()),
		getDay(),
		getYear());
	sbuf = buf;	
	return sbuf.c_str();
}

////////////////////////////////////////////////
//	getTimeString
////////////////////////////////////////////////
	
const char *Clock::getTimeString(std::string &sbuf)
{
	char buf[32];
	sprintf(buf, "%02d%s%02d",
		getHour(),
		((getSecond() % 2) == 0) ? ":" : " ",
		getMinute());
	sbuf = buf;	
	return sbuf.c_str();
}

////////////////////////////////////////////////
//	toString
////////////////////////////////////////////////

const char *Clock::toString(std::string &sbuf)
{
	char buf[128];
	sprintf(buf, "%s, %s %d, %02d, %02d:%02d:%02d",
		toWeekString(getWeek()),
		toMonthString(getMonth()),
		getDay(),
		getYear(),
		getHour(),
		getMinute(),
		getSecond());
	sbuf = buf;	
	return sbuf.c_str();
}
		


