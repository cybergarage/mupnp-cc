/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002-2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <cybergarage/upnp/CyberLink.h>
#include <cybergarage/xml/Parser.h>

using namespace CyberLink;
using namespace std;
using namespace CyberXML;

const std::string XML_TEST_SAMPLE_01 =
"<?xml version=\"1.0\" ?> \n"
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n"
" 	<specVersion> \n"
" 		<major>1</major>\n"
" 		<minor>0</minor>\n"
" 	</specVersion> \n"
"</root> \n";

BOOST_AUTO_TEST_CASE(XMLParserTests)
{
    Parser xmlParser;
    
    Node *rootNode = xmlParser.parse(XML_TEST_SAMPLE_01);
    BOOST_CHECK(rootNode);
    Attribute *rootAttr = rootNode->getAttribute("xmlns");
    string rootAttrValue = rootAttr->getValue();
    BOOST_CHECK_EQUAL(rootAttrValue.compare("urn:schemas-upnp-org:device-1-0"), 0);
    
    Node *specNode = rootNode->getNode("specVersion");
    BOOST_CHECK(specNode);
    
    Node *majorNode = specNode->getNode("major");
    BOOST_CHECK(majorNode);
    string majorValue = majorNode->getValue();
    BOOST_CHECK_EQUAL(majorValue.compare("1"), 0);
    
    Node *minorNode = specNode->getNode("minor");
    BOOST_CHECK(minorNode);
    string minorValue = minorNode->getValue();
    BOOST_CHECK_EQUAL(minorValue.compare("0"), 0);
}
