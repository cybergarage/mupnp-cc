#ifndef CPP_UNIT_UPNPTESTCASE_H
#define CPP_UNIT_UPNPTESTCASE_H

#include <cppunit/extensions/HelperMacros.h>

/* 
 * A test case that is designed to produce
 * example errors and failures
 *
 */

#include <cybergarage/http/HTTPRequest.h>

class UPnPTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( UPnPTestCase );

  CPPUNIT_TEST( testString2 );
  CPPUNIT_TEST( testThread );
  CPPUNIT_TEST( testMutex);
  
  CPPUNIT_TEST( testHTTPDate );

  CPPUNIT_TEST( testSocketHttpClient );
  CPPUNIT_TEST( testHostInterface );

 #if !defined(TENGINE)
  //CPPUNIT_TEST( testNoUseIOStream );
  //CPPUNIT_TEST( testSocket );
  //CPPUNIT_TEST( testIPv6 );
  //CPPUNIT_TEST( testHTTPConnection );
  //CPPUNIT_TEST( testHTTPContentRange );
  //CPPUNIT_TEST( testHTTPServer );
  //CPPUNIT_TEST( testStringParse );
  //CPPUNIT_TEST( testStringTokenizer );
  //CPPUNIT_TEST( testMemoryDevice );
  //CPPUNIT_TEST( testDevice );
  //CPPUNIT_TEST( testControlPoint );
  //CPPUNIT_TEST( testST );
  //CPPUNIT_TEST( testSSDP );
  //CPPUNIT_TEST( testMediaServer );
  //CPPUNIT_TEST( testContentDirectory );
#ifdef SUPPORT_ITUNES
	CPPUNIT_TEST( testITunesLibrary );
#endif

#endif

  CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

protected:
  
	void testString2();
	void testThread();
	void testMutex();

	void testHTTPDate();

	void testHostInterface();

	void testSocketHttpClient();

 #if !defined(TENGINE)
	void testNoUseIOStream();
	
	void testSocket();
	void testIPv6();
	void testHTTPConnection();
	void testHTTPContentRange();

	void doContentRangeTest(CyberHTTP::HTTPRequest *httpReq, const char *host, int port, const char *postUri, bool keepAlive, const char *content, int firstPos, int lastPos);
	void doHTTPServerTest(const char *postUri, bool keepAlive);
	void testHTTPServer();

	void testStringParse();
	void testStringTokenizer();

	void testMemoryDevice();
	void testDevice();
	void testControlPoint();

	void testMediaServer();
	void testContentDirectory();

	void testST();
	void testSSDP();

#ifdef SUPPORT_ITUNES
	void testITunesLibrary();
#endif

#endif
};

#endif
