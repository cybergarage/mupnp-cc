/******************************************************************
*
*	CyberSQL for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: UniMySQL.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#include <cybergarage/sql/UniMySQL.h>
#include <cybergarage/util/Date.h>
#include <iostream>

#ifdef SUPPORT_MYSQL

using namespace std;
using namespace CyberSQL;
using namespace CyberUtil;

//////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////

UniMySQL::UniMySQL()
{
	mysql_init(&mySQL);
	res = NULL;
	openFlag = false;
}

UniMySQL::~UniMySQL()
{
}

//////////////////////////////////////////////////////////////////////////
// open
//////////////////////////////////////////////////////////////////////////

bool UniMySQL::open(
        const char *host,
        int port,
        const char *dbname,
        const char *user,
        const char *passwd)
{
#ifdef USE_MYSQL_CONNECT
        MYSQL *ret = mysql_connect(
                &mySQL,
                host,
                user,
                passwd);

        if (ret == NULL)
                return false;

        int res = mysql_select_db(&mySQL, dbname);
        if (res != 0)
                return false;
#endif

        if (!mysql_real_connect(&mySQL, host, user, passwd , dbname, port, NULL,0)) {
                cout << "Failed to connect to database: Error: " << mysql_error(&mySQL);
                return false;
        }

        openFlag = true;

        return true;
}

//////////////////////////////////////////////////////////////////////////
// close
//////////////////////////////////////////////////////////////////////////

bool UniMySQL::close()
{
	if (res != NULL) {
		mysql_free_result(res);
		res = NULL;
	}

	mysql_close(&mySQL);
	return true;
}

bool UniMySQL::isConnected()
{
	return openFlag;
}

const char *UniMySQL::getConnectionErrorMessage()
{
	return (const char *)mysql_error(&mySQL);
}

bool UniMySQL::query(const char *sql)
{
	if (res != NULL)
		mysql_free_result(res);
	nTuples = 0;
	fetchCnt = -1;
	int ret = mysql_query(&mySQL, sql);
	queryRes = (ret == 0) ? true : false;
	//cout << "query = " << sql << endl;
	if (ret != 0) {
		cerr << mysql_error(&mySQL) << endl;
		return false;
	}
	res = mysql_store_result(&mySQL);
	if (res != NULL)
		nTuples = mysql_num_rows(res);
	//cout << "fetch = " << res << ", " << nTuples << endl;
	return queryRes;
}

bool UniMySQL::getQueryStatus()
{
	return queryRes;
}

int UniMySQL::getResultSetNum()
{
	return nTuples;
}

const char *UniMySQL::getQueryStatusMessage()
{
	return (const char *)mysql_error(&mySQL);
}

const char *UniMySQL::getQueryErrorMessage()
{
	return (const char *)mysql_error(&mySQL);
}

bool UniMySQL::fetch()
{
	fetchCnt++;
	//cout << "fetch = " << fetchCnt << ", " << nTuples << endl;
	if (fetchCnt < nTuples) {
		num_fields = mysql_num_fields(res);
		row = mysql_fetch_row(res);
		if (row == NULL)
			return false;
		return true;
	}
	return false;
}

////////////////////////////////////////////////
// get*
////////////////////////////////////////////////

const char *UniMySQL::getString(int n)
{
	if (n < num_fields) {
		if (row[n] == NULL)
			return "";
		return row[n];
	}
	return "";
}

long UniMySQL::getTimestamp(int n)
{
	const char *str = getString(n);
	if (str == NULL)
		return 0;

	int year, month, day, hour, min, sec;
	if (sscanf(str, "%04d%02d%02d%02d%02d%02d", &year, &month, &day, &hour, &min, &sec) != 6)
		return 0;

	Date sqlDate(year, month, day, hour, min, sec);
	long lvalue = (long)sqlDate.getValue();

	return lvalue;
}

#endif
