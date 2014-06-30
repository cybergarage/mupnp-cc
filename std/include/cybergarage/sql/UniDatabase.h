/******************************************************************
*
*	CyberSQL for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: UniDatabase.h
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CSQL_UNI_DATEBASE_H_
#define _CSQL_UNI_DATEBASE_H_

namespace CyberSQL {

class UniDatabase
{
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

public:

	UniDatabase();

	virtual ~UniDatabase();

	////////////////////////////////////////////////
	// Virtual Methods
	////////////////////////////////////////////////

public:

	virtual bool close()
	{
		return true;
	}

	virtual bool isConnected() = 0;
	virtual const char *getConnectionErrorMessage() = 0;

	virtual bool query(const char *sql) = 0;
	virtual bool getQueryStatus() = 0;
	virtual const char *getQueryStatusMessage() = 0;
	virtual const char *getQueryErrorMessage() = 0;
	virtual int getResultSetNum() = 0;

	virtual bool fetch() = 0;
	virtual const char *getString(int n) = 0;

	////////////////////////////////////////////////
	// get*
	////////////////////////////////////////////////

public:

	virtual int getInteger(int n);
	virtual long getTimestamp(int n);

};

}

#endif
