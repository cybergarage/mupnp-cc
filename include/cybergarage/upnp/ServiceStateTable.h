<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ServiceStateTable.h
*
*	Revision;
*
*	07/21/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SERVICESTATETABLE_H_
#define _CLINK_SERVICESTATETABLE_H_

#include <uhttp/util/Vector.h>

namespace CyberLink {

class StateVariable;

class ServiceStateTable : public uHTTP::Vector 
{
public:
	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////
	
	static const char *ELEM_NAME;

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	ServiceStateTable() 
	{
	}

	~ServiceStateTable() 
	{
		clear();
	}
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////
	
	StateVariable *getStateVariable(int n)
	{
		return (StateVariable *)get(n);
	}

	void clear();
};

}

#endif


=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ServiceStateTable.h
*
*	Revision;
*
*	07/21/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SERVICESTATETABLE_H_
#define _CLINK_SERVICESTATETABLE_H_

#include <cybergarage/util/Vector.h>

namespace CyberLink {

class StateVariable;

class ServiceStateTable : public CyberUtil::Vector 
{
public:
	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////
	
	static const char *ELEM_NAME;

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	ServiceStateTable() 
	{
	}

	~ServiceStateTable() 
	{
		clear();
	}
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////
	
	StateVariable *getStateVariable(int n)
	{
		return (StateVariable *)get(n);
	}

	void clear();
};

}

#endif


>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
