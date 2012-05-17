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
*		- Added postMessage(const std::string &host, int port, SOAPResponse *soapRes);
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
#include <uhttp/util/StringUtil.h>
#include <cybergarage/xml/Parser.h>

using namespace CyberSOAP;
using namespace uHTTP;
using namespace CyberXML;
using namespace std;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////
	
SOAPRequest::SOAPRequest()
{
	setContentType(CyberXML::XML::CONTENT_TYPE);
	setMethod(uHTTP::HTTP::POST);
	setRootNode(NULL);
}

SOAPRequest::SOAPRequest(uHTTP::HTTPRequest *httpReq)
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

bool SOAPRequest::isSOAPAction(const std::string &value)
{
	const char *headerValue = getHeaderValue(SOAPACTION);
	if (headerValue == NULL)
		return false;
	if (uHTTP::StringEquals(headerValue, value) == true)
		return true;
	std::string buf;
	const char *soapAction = getSOAPAction(buf);
	if (soapAction == NULL)
		return false;
	return uHTTP::StringEquals(soapAction, value);
}

////////////////////////////////////////////////
//	parseMessage
////////////////////////////////////////////////

CyberXML::Node *SOAPRequest::parseMessage(const std::string &content, int contentLen)
{
	if (contentLen <= 0)
		return NULL;

	Parser xmlParser;
	
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

SOAPResponse *SOAPRequest::postMessage(const std::string &host, int port, SOAPResponse *soapRes)
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
