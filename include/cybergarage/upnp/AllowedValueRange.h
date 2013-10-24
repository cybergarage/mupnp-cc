/******************************************************************
*
<<<<<<< HEAD
*	CyberLink for C++
=======
*	CyberLink for C++
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File: AllowedValueRange.h
<<<<<<< HEAD
*
*	Revision:
*
*	03/29/04
*		- first revision.
*	
******************************************************************/

#ifndef _CLINK_ALLOWEDVALUERANGE_H_
#define _CLINK_ALLOWEDVALUERANGE_H_

#include <cybergarage/xml/Node.h>

namespace CyberLink{

class AllowedValueRange
{
	CyberXML::Node *allowedValueRangeNode;

	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////

public:
	
	static const char *ELEM_NAME;

	static const char *MAXIMUM;
	static const char *MINIMUM;
	static const char *STEP;

	
	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

public:

	void setAllowedValueRangeNode(CyberXML::Node *node)
	{
		allowedValueRangeNode = node;
	}

	CyberXML::Node *getAllowedValueRangeNode()
	{
		return allowedValueRangeNode;
	}

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:
	
	AllowedValueRange()
	{
		setAllowedValueRangeNode(NULL);
	}

	AllowedValueRange(CyberXML::Node *node)
	{
		setAllowedValueRangeNode(node);
	}

	////////////////////////////////////////////////
	//	isIconNode
	////////////////////////////////////////////////

public:

	static bool isAllowedValueRangeNode(CyberXML::Node *node)
	{
		return node->isName(AllowedValueRange::ELEM_NAME);
	}

	////////////////////////////////////////////////
	//	minimum
	////////////////////////////////////////////////

public:

	void setMinimum(const std::string &value)
	{
		getAllowedValueRangeNode()->setNode(MINIMUM, value);
	}

	const char *getMinimum()
	{
		return getAllowedValueRangeNode()->getNodeValue(MINIMUM);
	}

	////////////////////////////////////////////////
	//	maximum
	////////////////////////////////////////////////

public:

	void setMaximum(const std::string &value)
=======
*
*	Revision:
*
*	03/29/04
*		- first revision.
*	
******************************************************************/

#ifndef _CLINK_ALLOWEDVALUERANGE_H_
#define _CLINK_ALLOWEDVALUERANGE_H_

#include <cybergarage/xml/Node.h>

namespace CyberLink{

class AllowedValueRange
{
	CyberXML::Node *allowedValueRangeNode;

	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////

public:
	
	static const char *ELEM_NAME;

	static const char *MAXIMUM;
	static const char *MINIMUM;
	static const char *STEP;

	
	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

public:

	void setAllowedValueRangeNode(CyberXML::Node *node)
	{
		allowedValueRangeNode = node;
	}

	CyberXML::Node *getAllowedValueRangeNode()
	{
		return allowedValueRangeNode;
	}

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:
	
	AllowedValueRange()
	{
		setAllowedValueRangeNode(NULL);
	}

	AllowedValueRange(CyberXML::Node *node)
	{
		setAllowedValueRangeNode(node);
	}

	////////////////////////////////////////////////
	//	isIconNode
	////////////////////////////////////////////////

public:

	static bool isAllowedValueRangeNode(CyberXML::Node *node)
	{
		return node->isName(AllowedValueRange::ELEM_NAME);
	}

	////////////////////////////////////////////////
	//	minimum
	////////////////////////////////////////////////

public:

	void setMinimum(const char *value)
	{
		getAllowedValueRangeNode()->setNode(MINIMUM, value);
	}

	const char *getMinimum()
	{
		return getAllowedValueRangeNode()->getNodeValue(MINIMUM);
	}

	////////////////////////////////////////////////
	//	maximum
	////////////////////////////////////////////////

public:

	void setMaximum(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getAllowedValueRangeNode()->setNode(MAXIMUM, value);
	}

	const char *getMaximum()
	{
		return getAllowedValueRangeNode()->getNodeValue(MAXIMUM);
	}

<<<<<<< HEAD
	////////////////////////////////////////////////
	//	width
	////////////////////////////////////////////////

public:

	void setStep(const std::string &value)
	{
		getAllowedValueRangeNode()->setNode(STEP, value);
	}

	const char *getStep()
	{
		return getAllowedValueRangeNode()->getNodeValue(STEP);
	}
};

}

#endif
=======
	////////////////////////////////////////////////
	//	width
	////////////////////////////////////////////////

public:

	void setStep(const char *value)
	{
		getAllowedValueRangeNode()->setNode(STEP, value);
	}

	const char *getStep()
	{
		return getAllowedValueRangeNode()->getNodeValue(STEP);
	}
};

}

#endif
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

