/******************************************************************
*
*	CyberSQL for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: UniMySQL.h
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CSQL_UNI_MYSQL_H_
#define _CSQL_UNI_MYSQL_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYSQL

#include <cybergarage/sql/UniDatabase.h>
#ifdef WIN32
#include <windows.h>
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

namespace CyberSQL {

class UniMySQL : public UniDatabase
{
	MYSQL mySQL;
	MYSQL_RES *res;
	MYSQL_ROW row;
	unsigned int num_fields;

	bool openFlag;
	bool queryRes;
	int fetchCnt;
	int nTuples;

public:

	UniMySQL();
	virtual ~UniMySQL();

	bool open(
		const char *host,
		int port,
		const char *dbname,
		const char *user,
		const char *passwd);

	bool close();

	bool isConnected();

	const char *getConnectionErrorMessage();

	bool query(const char *sql);
	bool getQueryStatus();
	const char *getQueryStatusMessage();
	const char *getQueryErrorMessage();
	int getResultSetNum();

	bool fetch();
	const char *getString(int n);

	long getTimestamp(int n);
};

}

#endif

#endif
