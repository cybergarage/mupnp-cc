/******************************************************************
*
*	CyberSQL for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: UniDatabase.cpp
*
*	Revision:
*
*	03/27/03
*		- first revision
*
******************************************************************/

#include <uhttp/util/Date.h>
#include <cybergarage/sql/UniDatabase.h>
#include <stdio.h>
#include <stdlib.h>

using namespace CyberSQL;
using namespace uHTTP;

//////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////

UniDatabase::UniDatabase()
{
}

UniDatabase::~UniDatabase()
{
	close();
}

////////////////////////////////////////////////
// get*
////////////////////////////////////////////////

int UniDatabase::getInteger(int n)
{
	return atoi(getString(n));
}

long UniDatabase::getTimestamp(int n)
{
	const char *str = getString(n);
	if (str == NULL)
		return 0;

	int year, month, day, hour, min, sec;
	if (sscanf(str, "%04d-%02d-%02d %02d:%02d:%02d", &year, &month, &day, &hour, &min, &sec) != 6)
		return 0;

	Date sqlDate(year, month, day, hour, min, sec);
	long lvalue = (long)sqlDate.getValue();

	return lvalue;
}
