/******************************************************************
*
*	CyberSOAP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SOAPRequest.cpp
*
*	Revision;
*
*	05/21/03
*		- first revision
*	02/13/04
*		- Ralf G. R. Bergs <Ralf@Ber.gs>, Inma Marin Lopez <inma@dif.um.es>.
*		- Added XML header, <?xml version=\"1.0\"?> to setContent().
*	04/25/04
<<<<<<< HEAD
*		- Added postMessage(const std::string &host, int port, SOAPResponse *soapRes);
=======
*		- Added postMessage(const char *host, int port, SOAPResponse *soapRes);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
*	05/19/04
*		- Changed the header include order for Cygwin.
*	05/26/04
*		- Changed getRootNode() and postMessage() to convert the local string to UTF8 before the XML parser..
*	06/01/04
*		- Added getHeader().
*		- Added getEncording() and isEncording().
*		- Added parseMessage().
*
******************************************************************/

#include <cybergarage/soap/SOAPRequest.h>
<<<<<<< HEAD
#include <uhttp/util/StringUtil.h>
#include <cybergarage/xml/Parser.h>

using namespace CyberSOAP;
using namespace uHTTP;
=======
#include <cybergarage/util/StringUtil.h>
#include <cybergarage/xml/Parser.h>

using namespace CyberSOAP;
using namespace CyberUtil;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
using namespace CyberXML;
using namespace std;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////
	
SOAPRequest::SOAPRequest()
{
	setContentType(CyberXML::XML::CONTENT_TYPE);
<<<<<<< HEAD
	setMethod(uHTTP::HTTP::POST);
	setRootNode(NULL);
}

SOAPRequest::SOAPRequest(uHTTP::HTTPRequest *httpReq)
=======
	setMethod(CyberHTTP::HTTP::POST);
	setRootNode(NULL);
}

SOAPRequest::SOAPRequest(CyberHTTP::HTTPRequest *httpReq)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	set(httpReq);
	setRootNode(NULL);
}

SOAPRequest::~SOAPRequest()
{
	if (rootNode != NULL)
		delete rootNode;
}

////////////////////////////////////////////////
// SOAPACTION
////////////////////////////////////////////////

<<<<<<< HEAD
bool SOAPRequest::isSOAPAction(const std::string &value)
=======
bool SOAPRequest::isSOAPAction(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	const char *headerValue = getHeaderValue(SOAPACTION);
	if (headerValue == NULL)
		return false;
<<<<<<< HEAD
	if (uHTTP::StringEquals(headerValue, value) == true)
=======
	if (CyberUtil::StringEquals(headerValue, value) == true)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		return true;
	std::string buf;
	const char *soapAction = getSOAPAction(buf);
	if (soapAction == NULL)
		return false;
<<<<<<< HEAD
	return uHTTP::StringEquals(soapAction, value);
=======
	return CyberUtil::StringEquals(soapAction, value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
}

////////////////////////////////////////////////
//	parseMessage
////////////////////////////////////////////////

<<<<<<< HEAD
CyberXML::Node *SOAPRequest::parseMessage(const std::string &content, int contentLen)
=======
CyberXML::Node *SOAPRequest::parseMessage(const char *content, int contentLen)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	if (contentLen <= 0)
		return NULL;

	Parser xmlParser;
<<<<<<< HEAD
    return xmlParser.parse(content, contentLen);
=======
	
	Node *retNode =	retNode = xmlParser.parse(content, contentLen);
	if (retNode != NULL)
		return retNode;
		
	if (SOAP::IsEncording(content, SOAP::UTF_8) == true) {
		int uniContentLen;
		UnicodeStr *uniContentStr = XML::Local2Unicode(content, uniContentLen);
		if (uniContentStr != NULL) {
			retNode = xmlParser.parse(uniContentStr, uniContentLen);
			delete []uniContentStr;
		}
	}

	return retNode;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
}

////////////////////////////////////////////////
//	Node
////////////////////////////////////////////////

CyberXML::Node *SOAPRequest::getRootNode()
{
	if (rootNode != NULL)
		return rootNode;
			
	const char *content = getContent();
	int contentLen = getContentLength();

	rootNode = parseMessage(content, contentLen);

	return rootNode;
}

////////////////////////////////////////////////
//	post
////////////////////////////////////////////////

<<<<<<< HEAD
SOAPResponse *SOAPRequest::postMessage(const std::string &host, int port, SOAPResponse *soapRes)
=======
SOAPResponse *SOAPRequest::postMessage(const char *host, int port, SOAPResponse *soapRes)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	post(host, port, soapRes);

	const char *content = soapRes->getContent();
	size_t contentLen = soapRes->getContentLength();
	if (contentLen <= 0)
		return soapRes;

	Node *retNode = parseMessage(content, contentLen);
	soapRes->setEnvelopeNode(retNode);

	return soapRes;
}

////////////////////////////////////////////////
//	setContent
////////////////////////////////////////////////

void SOAPRequest::setContent(CyberXML::Node *node)
{
	string nodeBuf;
	node->toString(nodeBuf);
	string buf;
	buf.append(SOAP::VERSION_HEADER);
	buf.append("\n");
	buf.append(nodeBuf);
	HTTPRequest::setContent(buf.c_str());
}
