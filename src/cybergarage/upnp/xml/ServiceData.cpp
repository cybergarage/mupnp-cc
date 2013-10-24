<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ServiceData.cpp
*
*	Revision;
*
*	04/26/04
*		- first revision
*	01/06/04
*		- Moved setQueryListener() and getQueryListener() to StateVariableData class.
*	05/19/04
*		- Changed the header include order for Cygwin.
*
******************************************************************/

#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/xml/ServiceData.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

ServiceData::ServiceData() 
{
	service = NULL;
	scpdNode = NULL;
}

ServiceData::~ServiceData() 
{
	if (scpdNode != NULL)
		delete scpdNode;
}

////////////////////////////////////////////////
// scpdNode
////////////////////////////////////////////////

void ServiceData::setSCPDNode(CyberXML::Node *node)
{
	if (scpdNode != NULL)
		delete scpdNode;
	scpdNode = node;
}

=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ServiceData.cpp
*
*	Revision;
*
*	04/26/04
*		- first revision
*	01/06/04
*		- Moved setQueryListener() and getQueryListener() to StateVariableData class.
*	05/19/04
*		- Changed the header include order for Cygwin.
*
******************************************************************/

#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/xml/ServiceData.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

ServiceData::ServiceData() 
{
	service = NULL;
	scpdNode = NULL;
}

ServiceData::~ServiceData() 
{
	if (scpdNode != NULL)
		delete scpdNode;
}

////////////////////////////////////////////////
// scpdNode
////////////////////////////////////////////////

void ServiceData::setSCPDNode(CyberXML::Node *node)
{
	if (scpdNode != NULL)
		delete scpdNode;
	scpdNode = node;
}

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
