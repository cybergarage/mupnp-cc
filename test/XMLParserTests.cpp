/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <mupnp/UPnP.h>
#include <mupnp/xml/Parser.h>
using namespace mUPnP;
using namespace std;

const std::string XML_TEST_SAMPLE_01 = "<?xml version=\"1.0\" ?> \n"
                                       "<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n"
                                       "   <specVersion> \n"
                                       "     <major>1</major>\n"
                                       "     <minor>0</minor>\n"
                                       "   </specVersion> \n"
                                       "</root> \n";

BOOST_AUTO_TEST_CASE(XMLParserTests)
{
  uXML::Parser xmlParser;

  mupnp_shared_ptr<uXML::Node> rootNode = xmlParser.parse(XML_TEST_SAMPLE_01);
  BOOST_CHECK(rootNode);
  uXML::Attribute* rootAttr = rootNode->getAttribute("xmlns");
  string rootAttrValue = rootAttr->getValue();
  BOOST_CHECK_EQUAL(rootAttrValue.compare("urn:schemas-upnp-org:device-1-0"), 0);

  mupnp_shared_ptr<uXML::Node> specNode = rootNode->getNode("specVersion");
  BOOST_CHECK(specNode);

  mupnp_shared_ptr<uXML::Node> majorNode = specNode->getNode("major");
  BOOST_CHECK(majorNode);
  string majorValue = majorNode->getValue();
  BOOST_CHECK_EQUAL(majorValue.compare("1"), 0);

  mupnp_shared_ptr<uXML::Node> minorNode = specNode->getNode("minor");
  BOOST_CHECK(minorNode);
  string minorValue = minorNode->getValue();
  BOOST_CHECK_EQUAL(minorValue.compare("0"), 0);
}
