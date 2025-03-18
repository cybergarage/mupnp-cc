/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File: Parameter.h
*
*	Revision;
*
*	03/09/04
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_PARAMETER_H_
#define _CHTTP_PARAMETER_H_

#include <string>

namespace CyberHTTP {

class Parameter 
{
	std::string name; 
	std::string value; 

public:

	Parameter() 
	{
	}

	Parameter(const char *name, const char *value) 
	{
		setName(name);
		setValue(value);
	}

	////////////////////////////////////////////////
	//	name
	////////////////////////////////////////////////

	void setName(const char *val) 
	{
		name = val;
	}

	const char *getName() 
	{
		return name.c_str();
	}

	////////////////////////////////////////////////
	//	value
	////////////////////////////////////////////////

	void setValue(const char *val) 
	{
		value = val;
	}

	const char *getValue() 
	{
		return value.c_str();
	}
};

}

#endif
