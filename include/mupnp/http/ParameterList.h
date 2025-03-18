/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File: ParameterList.h
*
*	Revision;
*
*	03/09/04
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_PARAMETERLIST_H_
#define _CHTTP_PARAMETERLIST_H_

#include <cybergarage/util/Vector.h>
#include <cybergarage/util/StringUtil.h>
#include <cybergarage/http/Parameter.h>

namespace CyberHTTP {

class ParameterList : public CyberUtil::Vector
{

public:
	
	ParameterList() 
	{
	}
	
	~ParameterList() 
	{
		int nLists = size(); 
		for (int n=0; n<nLists; n++) {
			Parameter *param = at(n);
			delete param;
		}
	}

	Parameter *at(int n)
	{
		return (Parameter *)Vector::get(n);
	}

	Parameter *getParameter(int n)
	{
		return (Parameter *)Vector::get(n);
	}

	Parameter *getParameter(const char *name) 
	{
		if (name == NULL)
			return NULL;
		
		int nLists = size(); 
		for (int n=0; n<nLists; n++) {
			Parameter *param = at(n);
			if (CyberUtil::StringEquals(name, param->getName()) == true)
				return param;
		}
		return NULL;
	}

	const char *getValue(const char *name) 
	{
		Parameter *param = getParameter(name);
		if (param == NULL)
			return "";
		return param->getValue();
	}
};

}

#endif
