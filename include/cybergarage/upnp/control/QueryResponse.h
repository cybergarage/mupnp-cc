/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: QueryResponse.h
*
*	Revision;
*
*	08/13/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_QUERYRESPONSE_H_
#define _CLINK_QUERYRESPONSE_H_

#include <cybergarage/upnp/control/ControlResponse.h>
#include <cybergarage/soap/SOAP.h>

#include <sstream>

namespace CyberLink {

class StateVariable;

class QueryResponse : public ControlResponse
{

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	QueryResponse()
	{
	}

	QueryResponse(CyberSOAP::SOAPResponse *soapRes)
	{
		set(soapRes);
	}

	////////////////////////////////////////////////
	//	Qyery
	////////////////////////////////////////////////

private:

	CyberXML::Node *getReturnNode();
	
public:

	const char *getReturnValue();

	////////////////////////////////////////////////
	//	Response
	////////////////////////////////////////////////

public:

	void setResponse(StateVariable *stateVar);

private:

<<<<<<< HEAD
	CyberXML::Node *createResponseNode(const std::string &value);
=======
	CyberXML::Node *createResponseNode(const char *value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
};

}

#endif
