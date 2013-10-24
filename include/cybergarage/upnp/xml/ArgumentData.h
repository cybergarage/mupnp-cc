<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ArgumentData.h
*
*	Revision;
*
*	07/14/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_ARGUMENTDATA_H_
#define _CLINK_ARGUMENTDATA_H_

#include <string>
#include <cybergarage/xml/NodeData.h>

namespace CyberLink {

class ArgumentData : public CyberXML::NodeData
{

	std::string value;
	
public:

=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ArgumentData.h
*
*	Revision;
*
*	07/14/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_ARGUMENTDATA_H_
#define _CLINK_ARGUMENTDATA_H_

#include <string>
#include <cybergarage/xml/NodeData.h>

namespace CyberLink {

class ArgumentData : public CyberXML::NodeData
{

	std::string value;
	
public:

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	ArgumentData() 
	{
	}

	////////////////////////////////////////////////
	// value
	////////////////////////////////////////////////

	const char *getValue()
	{
		return value.c_str();
	}

<<<<<<< HEAD
	void setValue(const std::string &val)
=======
	void setValue(const char *val)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		value = val;
	}

<<<<<<< HEAD
};

}

#endif
=======
};

}

#endif
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
