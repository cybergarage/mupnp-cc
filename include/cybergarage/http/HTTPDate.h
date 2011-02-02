/******************************************************************
*
*	CyberHTTP for C++
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

#ifndef _CHTTP_HTTPDATE_H_
#define _CHTTP_HTTPDATE_H_

#include <cybergarage/util/Date.h>

namespace CyberHTTP {

class HTTPDate : public CyberUtil::Date
{
	char dateStr[64];
	char timeStr[64];

public:

	HTTPDate();
	HTTPDate(SysTime date);

	////////////////////////////////////////////////
	//	get*String
	////////////////////////////////////////////////

	const char *getDateString();
};

const char *toMonthString(int value);
const char *toWeekString(int value);

}

#endif
