/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: SearchCriteria.h
*
*	Revision:
*
*	08/06/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_SEARCHCRITERIA_H_
#define _CLINK_MEDIA_SEARCHCRITERIA_H_

#include <string>

namespace CyberLink {

class SearchCriteria
{
	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////
	
public:

	static const char *ID;
	static const char *PARENT_ID;
	static const char *TITLE;
	static const char *CREATOR;
	static const char *CLASS;
	static const char *DATE;

	static const char *AND;
	static const char *OR;

	static const char *EQ;
	static const char *NEQ;
	static const char *LT;
	static const char *LE;
	static const char *GT;
	static const char *GE;

	static const char *CONTAINS;
	static const char *DOESNOTCONTAIN;
	static const char *DERIVEDFROM;
	static const char *EXISTS;

	static const char *TRUE_STR;
	static const char *FALSE_STR;

	static const char *WCHARS;

	////////////////////////////////////////////////
	// Member
	////////////////////////////////////////////////

private:

	std::string property;
	std::string operation;
	std::string value;
	std::string logic;
	bool		result;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:

	SearchCriteria() 
	{
		setResult(false);
	}
	
	SearchCriteria(SearchCriteria *searchCri) 
	{
		setProperty(searchCri->getProperty());
		setOperation(searchCri->getOperation());
		setValue(searchCri->getValue());
		setLogic(searchCri->getLogic());
		setResult(searchCri->getResult());
	}

	~SearchCriteria() 
	{
	}

	////////////////////////////////////////////////
	// Propety
	////////////////////////////////////////////////

public:

	void setProperty(const char * val)
	{
		property = val;
	}

	const char *getProperty()
	{
		return property.c_str();
	}

	////////////////////////////////////////////////
	// Operation
	////////////////////////////////////////////////

public:

	void setOperation(const char * val)
	{
		operation = val;
	}

	const char *getOperation()
	{
		return operation.c_str();
	}

	bool isEQ()
	{
		return (operation.compare(EQ) == 0) ? true : false;
	}

	bool isNEQ()
	{
		return (operation.compare(NEQ) == 0) ? true : false;
	}

	bool isLT()
	{
		return (operation.compare(LT) == 0) ? true : false;
	}

	bool isLE()
	{
		return (operation.compare(LE) == 0) ? true : false;
	}

	bool isGT()
	{
		return (operation.compare(GT) == 0) ? true : false;
	}

	bool isGE()
	{
		return (operation.compare(GE) == 0) ? true : false;
	}

	bool isContains()
	{
		return (operation.compare(CONTAINS) == 0) ? true : false;
	}

	bool isDoesNotContain()
	{
		return (operation.compare(DOESNOTCONTAIN) == 0) ? true : false;
	}

	bool isDerivedFrom()
	{
		return (operation.compare(DERIVEDFROM) == 0) ? true : false;
	}

	bool isExists()
	{
		return (operation.compare(EXISTS) == 0) ? true : false;
	}

	////////////////////////////////////////////////
	// Value
	////////////////////////////////////////////////

public:

	void setValue(const char * val)
	{
		value = val;
	}

	const char *getValue()
	{
		return value.c_str();
	}

	bool isTrueValue()
	{
		return (value.compare(TRUE_STR) == 0) ? true : false;
	}

	bool isFalseValue()
	{
		return (value.compare(FALSE_STR) == 0) ? true : false;
	}

	////////////////////////////////////////////////
	// Logic
	////////////////////////////////////////////////

public:

	void setLogic(const char * val)
	{
		logic = val;
	}

	const char *getLogic()
	{
		return logic.c_str();
	}

	bool isLogicalAND()
	{
		return (logic.compare(AND) == 0) ? true : false;
	}

	bool isLogicalOR()
	{
		return (logic.compare(OR) == 0) ? true : false;
	}

	////////////////////////////////////////////////
	// Result
	////////////////////////////////////////////////

public:

	void setResult(bool value)
	{
		result = value;
	}

	bool getResult()
	{
		return result;
	}
};

}

#endif
