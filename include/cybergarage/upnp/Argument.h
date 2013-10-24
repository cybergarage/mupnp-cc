/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Argument.h
*
*	Revision;
*
*	07/08/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_ARGUMENT_H_
#define _CLINK_ARGUMENT_H_

#include <stdlib.h>

<<<<<<< HEAD
#include <uhttp/util/StringUtil.h>
=======
#include <cybergarage/util/StringUtil.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#include <cybergarage/xml/Node.h>
#include <cybergarage/upnp/xml/ArgumentData.h>

namespace CyberLink{

class Service;
class StateVariable;

class Argument
{
	
	CyberXML::Node *serviceNode;
	CyberXML::Node *argumentNode;

	CyberXML::Node defaultArgumentNode;
	CyberXML::Node defaultServiceNode;
	
public:

	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////

	static const char *ELEM_NAME;
	static const char *IN_DIR;
	static const char *OUT_DIR;
	static const char *NAME;
	static const char *DIRECTION;
	static const char *RELATED_STATE_VARIABLE;

public:

	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

	CyberXML::Node *getServiceNode()
	{
		return serviceNode;
	}

	CyberXML::Node *getArgumentNode()
	{
		return argumentNode;
	}
	
	Service *getService();

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	Argument();
	Argument(CyberXML::Node *servNode, CyberXML::Node *argNode);
<<<<<<< HEAD
	Argument(const std::string &name, const std::string &value);
=======
	Argument(const char *name, const char *value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	~Argument();

	////////////////////////////////////////////////
	//	isArgumentNode
	////////////////////////////////////////////////

	static bool isArgumentNode(CyberXML::Node *node)
	{
		return node->isName(Argument::ELEM_NAME);
	}

	////////////////////////////////////////////////
	//	name
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setName(const std::string &value)
=======
	void setName(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getArgumentNode()->setNode(NAME, value);
	}

	const char *getName()
	{
		return getArgumentNode()->getNodeValue(NAME);
	}

	////////////////////////////////////////////////
	//	direction
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setDirection(const std::string &value)
=======
	void setDirection(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getArgumentNode()->setNode(DIRECTION, value);
	}

	const char *getDirection()
	{
		return getArgumentNode()->getNodeValue(DIRECTION);
	}

	bool isInDirection()
	{
		const char *dir = getDirection();
		if (dir == NULL)
			return false;
<<<<<<< HEAD
		uHTTP::String dirStr(dir);
=======
		CyberUtil::String dirStr = dir;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		return dirStr.equalsIgnoreCase(IN_DIR);
	}

	bool isOutDirection()
	{
		return !isInDirection();
	}
	
	////////////////////////////////////////////////
	//	relatedStateVariable
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setRelatedStateVariableName(const std::string &value)
=======
	void setRelatedStateVariableName(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getArgumentNode()->setNode(RELATED_STATE_VARIABLE, value);
	}

	const char *getRelatedStateVariableName()
	{
		return getArgumentNode()->getNodeValue(RELATED_STATE_VARIABLE);
	}

	StateVariable *getRelatedStateVariable();

	////////////////////////////////////////////////
	//	UserData
	////////////////////////////////////////////////

	ArgumentData *getArgumentData()
	{
		CyberXML::Node *node = getArgumentNode();
		ArgumentData *userData = (ArgumentData *)node->getUserData();
		if (userData == NULL) {
			userData = new ArgumentData();
			node->setUserData(userData);
		}
		return userData;
	}

	////////////////////////////////////////////////
	//	value
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setValue(const std::string &value)
=======
	void setValue(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getArgumentData()->setValue(value);
	}

	void setValue(int value);

	const char *getValue()
	{
		return getArgumentData()->getValue();
	}

	int getIntegerValue()
	{
		return atoi(getValue());
	}

};

}

#endif
