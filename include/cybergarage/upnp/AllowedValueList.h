/******************************************************************
*
*	CyberLink for Java
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File: AllowedValueList.java
*
*	Revision:
*
*	03/29/04
*		- first revision.
*	
******************************************************************/

#ifndef _CLINK_ALLOWEDVALUELIST_H_
#define _CLINK_ALLOWEDVALUELIST_H_

#include <string>
<<<<<<< HEAD
#include <uhttp/util/Vector.h>
=======
#include <cybergarage/util/Vector.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#include <cybergarage/upnp/AllowedValue.h>

namespace CyberLink {

<<<<<<< HEAD
class AllowedValueList : public uHTTP::Vector 
=======
class AllowedValueList : public CyberUtil::Vector 
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////
	
public:

	static const char *ELEM_NAME;


	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	AllowedValueList() 
	{
	}

	~AllowedValueList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////
	
public:

	AllowedValue *getAllowedValue(int n)
	{
		return (AllowedValue *)get(n);
	}

};

}

#endif

