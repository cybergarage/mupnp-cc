/******************************************************************
*
*	CyberSOAP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SOAPRequest.h
*
*	Revision;
*
*	05/21/03
*		- first revision
*
******************************************************************/

#ifndef _CSOAP_SOAPREQUEST_H_
#define _CSOAP_SOAPREQUEST_H_

<<<<<<< HEAD
#include <uhttp/http/HTTPRequest.h>
#include <uhttp/http/HTTPResponse.h>
#include <uhttp/http/HTTP.h>
=======
#include <cybergarage/http/HTTPRequest.h>
#include <cybergarage/http/HTTPResponse.h>
#include <cybergarage/http/HTTP.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#include <cybergarage/soap/SOAP.h>
#include <cybergarage/soap/SOAPResponse.h>
#include <cybergarage/xml/Node.h>

namespace CyberSOAP {

const char SOAPACTION[] = "SOAPACTION";

<<<<<<< HEAD
class SOAPRequest : public uHTTP::HTTPRequest
=======
class SOAPRequest : public CyberHTTP::HTTPRequest
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{

	CyberXML::Node *rootNode;
	SOAPResponse soapRes;
		
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
public:

	SOAPRequest();
<<<<<<< HEAD
	SOAPRequest(uHTTP::HTTPRequest *httpReq);
=======
	SOAPRequest(CyberHTTP::HTTPRequest *httpReq);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	~SOAPRequest();

	////////////////////////////////////////////////
	// SOAPACTION
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	void setSOAPAction(const std::string &action)
=======
	void setSOAPAction(const char *action)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		setStringHeader(SOAPACTION, action);
	}
	
	const char *getSOAPAction(std::string &buf)
	{
		return getStringHeaderValue(SOAPACTION, buf);
	}

<<<<<<< HEAD
	bool isSOAPAction(const std::string &value);
=======
	bool isSOAPAction(const char *value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
 
	////////////////////////////////////////////////
	//	Header
	////////////////////////////////////////////////

public:

	const char *getHeader(std::string &buf)
	{
		return SOAP::GetHeader(getContent(), buf);
	}

	////////////////////////////////////////////////
	//	Encoding
	////////////////////////////////////////////////

public:

	const char *getEncording(std::string &buf)
	{
		return SOAP::GetEncording(getContent(), buf);
	}

<<<<<<< HEAD
	bool isEncording(const std::string &encType)
=======
	bool isEncording(const char *encType)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return SOAP::IsEncording(getContent(), encType);
	}

	////////////////////////////////////////////////
	//	post
	////////////////////////////////////////////////

private:

<<<<<<< HEAD
	CyberXML::Node *parseMessage(const std::string &content, int contentLen);

public:

	SOAPResponse *postMessage(const std::string &host, int port, SOAPResponse *soapRes);

	SOAPResponse *postMessage(const std::string &host, int port)
=======
	CyberXML::Node *parseMessage(const char *content, int contentLen);

public:

	SOAPResponse *postMessage(const char *host, int port, SOAPResponse *soapRes);

	SOAPResponse *postMessage(const char *host, int port)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return postMessage(host, port, &soapRes);
	}

	////////////////////////////////////////////////
	//	Node
	////////////////////////////////////////////////

private:

	void setRootNode(CyberXML::Node *node)
	{
		rootNode = node;
	}

	CyberXML::Node *getRootNode();
	
	////////////////////////////////////////////////
	//	XML
	////////////////////////////////////////////////

public:

	void setEnvelopeNode(CyberXML::Node *node)
	{
		setRootNode(node);
	}
	
	CyberXML::Node *getEnvelopeNode()
	{
		return getRootNode();
	}
		
	CyberXML::Node *getBodyNode()
	{
		CyberXML::Node *envNode = getEnvelopeNode();
		if (envNode == NULL)
			return NULL;
		if (envNode->hasNodes() == false)
			return NULL;
		return envNode->getNode(0);
	}

	////////////////////////////////////////////////
	//	SOAP UPnP
	////////////////////////////////////////////////
	
public:

	void setContent(CyberXML::Node *node);

	////////////////////////////////////////////////
	//	print
	////////////////////////////////////////////////
/*	
	public void print()
	{
		System.out.println(toString());
		if (hasContent() == true)
			return;
		Node rootElem = getRootNode();
		if (rootElem == null)
			return;
		System.out.println(rootElem.toString());
	}
*/
};

}

#endif
