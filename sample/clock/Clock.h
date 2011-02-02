/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : Clock.cpp
*
******************************************************************/

#ifndef _CLINK_CLOCK_H_
#define _CLINK_CLOCK_H_

#include <time.h>
#include <string>

class Clock
{

	time_t currTime;

public:

	Clock()
	{
		time(&currTime);
	}

	////////////////////////////////////////////////
	//	Time
	////////////////////////////////////////////////

public:

	int getYear()
	{
		struct tm *localTime = localtime(&currTime);
		return localTime->tm_year + 1900;
	}

	int getMonth()
	{
		struct tm *localTime = localtime(&currTime);
		return localTime->tm_mon;
	}

	int getWeek()
	{
		struct tm *localTime = localtime(&currTime);
		return localTime->tm_wday;
	}

	int getDay()
	{
		struct tm *localTime = localtime(&currTime);
		return localTime->tm_mday;
	}

	int getHour()
	{
		struct tm *localTime = localtime(&currTime);
		return localTime->tm_hour;
	}

	int getMinute()
	{
		struct tm *localTime = localtime(&currTime);
		return localTime->tm_min;
	}

	int getSecond()
	{
		struct tm *localTime = localtime(&currTime);
		return localTime->tm_sec;
	}
	
	////////////////////////////////////////////////
	//	getDateString
	////////////////////////////////////////////////

public:

	const char *getDateString(std::string &buf);

	////////////////////////////////////////////////
	//	getTimeString
	////////////////////////////////////////////////
	
public:

	const char *getTimeString(std::string &sbuf);

	////////////////////////////////////////////////
	//	toString
	////////////////////////////////////////////////

public:

	const char *toString(std::string &buf);
		
};

#endif


