<<<<<<< HEAD
/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Attribute.h
*
*	Revision;
*
*	04/22/03
*		- first revision
*
******************************************************************/

#ifndef _CXML_ATTRIBUTE_H_
#define _CXML_ATTRIBUTE_H_

#include <string>

namespace CyberXML {

class Attribute 
{
	std::string name; 
	std::string value; 

public:

	Attribute() 
	{
	}

	Attribute(const std::string &name, const std::string &value) 
	{
		setName(name);
		setValue(value);
	}

	////////////////////////////////////////////////
	//	name
	////////////////////////////////////////////////

	void setName(const std::string &val) 
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

	void setValue(const std::string &val) 
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
=======
/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Attribute.h
*
*	Revision;
*
*	04/22/03
*		- first revision
*
******************************************************************/

#ifndef _CXML_ATTRIBUTE_H_
#define _CXML_ATTRIBUTE_H_

#include <string>

namespace CyberXML {

class Attribute 
{
	std::string name; 
	std::string value; 

public:

	Attribute() 
	{
	}

	Attribute(const char *name, const char *value) 
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
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
