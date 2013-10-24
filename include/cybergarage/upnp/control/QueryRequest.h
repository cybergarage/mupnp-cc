/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: QueryRequest.h
*
*	Revision;
*
*	08/13/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_QUERYREQUEST_H_
#define _CLINK_QUERYREQUEST_H_

#include <cybergarage/upnp/control/ControlRequest.h>
#include <cybergarage/upnp/control/QueryResponse.h>
#include <cybergarage/soap/SOAP.h>

#include <sstream>

namespace CyberLink {

class Service;
class StateVariable;

class QueryRequest : public ControlRequest
{
	QueryResponse queryRes;

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	QueryRequest()
	{
	}

<<<<<<< HEAD
	QueryRequest(uHTTP::HTTPRequest *httpReq)
=======
	QueryRequest(CyberHTTP::HTTPRequest *httpReq)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		set(httpReq);
	}

	////////////////////////////////////////////////
	//	Qyery
	////////////////////////////////////////////////

private:

	CyberXML::Node *getVarNameNode();
	
public:

	const char *getVarName();

	////////////////////////////////////////////////
	//	setRequest
	////////////////////////////////////////////////
	
	void setRequest(StateVariable *stateVar);

	////////////////////////////////////////////////
	//	Contents
	////////////////////////////////////////////////

private:

	CyberXML::Node *createContentNode(StateVariable *stateVar);

	////////////////////////////////////////////////
	//	post
	////////////////////////////////////////////////

public:

	QueryResponse *post(QueryResponse *actionRes);

	QueryResponse *post()
	{
		return post(&queryRes);
	}

};

}

#endif
