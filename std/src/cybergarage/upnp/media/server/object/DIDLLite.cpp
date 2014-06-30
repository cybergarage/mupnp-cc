/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : DIDLLite.cpp
*
*	Revision:
*
*	03/31/04
*		- first revision.
*	06/01/04
*		- Added toUnicodeString().
*	10/26/04 
*		- Brent Hills <bhills@openshores.com>
*		- Removed a SOAP header from output().
*
******************************************************************/

#include <cybergarage/soap/SOAP.h>
#include <cybergarage/upnp/media/server/object/DIDLLite.h>
#include <cybergarage/upnp/media/server/object/DIDLLiteNode.h>
#include <cybergarage/xml/XML.h>

using namespace std;
using namespace CyberLink;
using namespace CyberSOAP;
using namespace CyberXML;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *DIDLLite::NAME = "DIDL-Lite";
const char *DIDLLite::XMLNS = "xmlns";
const char *DIDLLite::XMLNS_URL = "urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/";
const char *DIDLLite::XMLNS_DC = "xmlns:dc";
const char *DIDLLite::XMLNS_DC_URL = "http://purl.org/dc/elements/1.1/";
const char *DIDLLite::XMLNS_UPNP = "xmlns:upnp";
const char *DIDLLite::XMLNS_UPNP_URL = "urn:schemas-upnp-org:metadata-1-0/upnp/";

const char *DIDLLite::CONTAINER = "container";
const char *DIDLLite::ID = "id";
const char *DIDLLite::SEARCHABLE = "searchable";
const char *DIDLLite::PARENTID = "parentID";
const char *DIDLLite::RESTICTED = "restricted";
	
const char *DIDLLite::OBJECT_CONTAINER = "object.container";

const char *DIDLLite::RES = "res";
const char *DIDLLite::RES_PROTOCOLINFO = "protocolInfo";

////////////////////////////////////////////////
// Constrictor
////////////////////////////////////////////////
	
DIDLLite::DIDLLite(bool delElemFlag)
{
	nodeList = new ContentNodeList(delElemFlag);
}

DIDLLite::~DIDLLite()
{
	delete nodeList;
}

////////////////////////////////////////////////
//	output
////////////////////////////////////////////////

void DIDLLite::output(std::ostream& ps) 
{
	// Thanks for Brent Hills (10/26/04)
	//ps << SOAP::VERSION_HEADER;

	DIDLLiteNode didlNode;
	
	string name = didlNode.getName();
	string value = didlNode.getValue();
		
	ps << "<" << name;
	didlNode.outputAttributes(ps);
	ps << ">" << endl;

	int nNodes = getNContentNodes();
	for (int n=0; n<nNodes; n++) {
		ContentNode *contentNode = getContentNode(n);
		contentNode->output(ps, 1, false);
	}	

	ps << "</" << name << ">" << endl;
}

////////////////////////////////////////////////
//	toString
////////////////////////////////////////////////

const char *DIDLLite::toString(std::string &buf)
{
	ostringstream strBuf;
	output(strBuf);
	buf = strBuf.str();
	return buf.c_str();
}

const char *DIDLLite::toUnicodeString(std::string &buf)
{
	string localStr;
	toString(localStr);
	int outLen;
	UnicodeStr *uniStr = XML::Local2Unicode(localStr.c_str(), outLen);
	buf = (char *)uniStr;
	delete []uniStr;
	return buf.c_str();
}
