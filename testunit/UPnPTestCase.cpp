#include "UPnPTestCase.h"

#include <cybergarage/util/Thread.h>
#include <cybergarage/util/TimeUtil.h>
#include <cybergarage/util/Mutex.h>
#include <cybergarage/http/HTTP.h>
#include <cybergarage/http/HTTPDate.h>
#include <cybergarage/net/Socket.h>
#include <cybergarage/net/SocketInputStream.h>
#include <cybergarage/io/InputStreamReader.h>
#include <cybergarage/io/BufferedReader.h>

#if !defined(TENGINE)

#include <cybergarage/upnp/CyberLink.h>
#include <cybergarage/upnp/media/server/MediaServer.h>
#include <cybergarage/upnp/media/server/object/SearchCriteriaList.h>
#include <cybergarage/upnp/media/server/directory/itunes/iTunesLibrary.h>
#include <cybergarage/util/Debug.h>
#include <cybergarage/util/StringTokenizer.h>
#include <cybergarage/net/SocketUtil.h>
#include "TestHTTPServer.h"
#include "TestDevice.h"
#include "TestCtrlPoint.h"
#include "TestMediaServer.h"
#include <limits.h>

using namespace CyberLink;

#endif

using namespace std;
using namespace CyberHTTP;
using namespace CyberUtil;
using namespace CyberIO;
using namespace CyberNet;

CPPUNIT_TEST_SUITE_REGISTRATION( UPnPTestCase );

////////////////////////////////////////
// setUp
////////////////////////////////////////

void UPnPTestCase::setUp()
{
#if !defined(TENGINE)
	Debug::on();
#endif
}

////////////////////////////////////////
// tearDown
////////////////////////////////////////

void UPnPTestCase::tearDown()
{
}

////////////////////////////////////////
// testString2
////////////////////////////////////////

void UPnPTestCase::testString2()
{
	CPPUNIT_ASSERT(HexString2Long("1") == 1);
	CPPUNIT_ASSERT(HexString2Long("9") == 9);
	CPPUNIT_ASSERT(HexString2Long("A") == 10);
	CPPUNIT_ASSERT(HexString2Long("F") == 15);
	CPPUNIT_ASSERT(HexString2Long("FF") == 255);
	CPPUNIT_ASSERT(HexString2Long("a") == 10);
	CPPUNIT_ASSERT(HexString2Long("f") == 15);
	CPPUNIT_ASSERT(HexString2Long("ff") == 255);

	string buf;
	CPPUNIT_ASSERT(strcmp(Integer2HexString(1, buf), "1") == 0);
	CPPUNIT_ASSERT(strcmp(Integer2HexString(9, buf), "9") == 0);
	CPPUNIT_ASSERT(strcmp(Integer2HexString(10, buf), "a") == 0);
	CPPUNIT_ASSERT(strcmp(Integer2HexString(15, buf), "f") == 0);
	CPPUNIT_ASSERT(strcmp(Integer2HexString(255, buf), "ff") == 0);
}

////////////////////////////////////////
// testThread
////////////////////////////////////////

const int THREAD_TEST_LOOP_NUM = 10;

class TestThread : public Thread
{
public:
	
	int value;

	TestThread()
	{
		value = 0;
	}

	void run()
	{
		for (int n=0; n<THREAD_TEST_LOOP_NUM; n++)
			value++;
	}
};

void UPnPTestCase::testThread()
{
	TestThread *thread = new TestThread();
	CPPUNIT_ASSERT (thread->start() == true);
	while (thread->value != THREAD_TEST_LOOP_NUM)
		Wait(100);
	CPPUNIT_ASSERT(thread->value == THREAD_TEST_LOOP_NUM);
	CPPUNIT_ASSERT(thread->stop() == true);
	delete thread;
}

////////////////////////////////////////
// testMutex
////////////////////////////////////////

void UPnPTestCase::testMutex()
{
	Mutex *mutex = new Mutex();
	CPPUNIT_ASSERT (mutex->lock() == true);
	CPPUNIT_ASSERT (mutex->unlock() == true);
	delete mutex;
}

////////////////////////////////////////
// testHTTPDate
////////////////////////////////////////

void UPnPTestCase::testHTTPDate()
{
	HTTPDate httpDate(1118220696);
	const char *dateStr = httpDate.getDateString();
	printf("%s\n", dateStr);
#if !defined(TENGINE)
	CPPUNIT_ASSERT(strcmp(dateStr, "Wed, 08 Jun 2005 08:51:36 GMT") == 0);
#endif
}

////////////////////////////////////////
// testHostInterface
////////////////////////////////////////

void UPnPTestCase::testHostInterface()
{
	NetworkInterfaceList ifList;
	GetHostAddresses(ifList);
	
	int ifCnt = ifList.size();
	CPPUNIT_ASSERT(0 < ifCnt);
}

////////////////////////////////////////
// testSocketHttp
////////////////////////////////////////

const char *CG_HOST_IPADDR = "203.138.119.39";
const char *TEST_HTTP_METHOD = "GET /index.html HTTP/1.0";
 
void UPnPTestCase::testSocketHttpClient()
{
	Socket *sock;
	int sentLen;
	int readLen;
	const char *line;

#if !defined(TENGINE)
	sock = new Socket();
	CPPUNIT_ASSERT(sock != NULL);
	CPPUNIT_ASSERT(sock->connect(CG_HOST_IPADDR, 80) == TRUE);
	printf("\n");
	printf("%s\n", TEST_HTTP_METHOD);

	sentLen = sock->send(TEST_HTTP_METHOD, strlen(TEST_HTTP_METHOD));
	CPPUNIT_ASSERT(sentLen == strlen(TEST_HTTP_METHOD));
	sentLen = sock->send(HTTP::CRLF, strlen(HTTP::CRLF));
	CPPUNIT_ASSERT(sentLen == strlen(HTTP::CRLF));
	sentLen = sock->send(HTTP::CRLF, strlen(HTTP::CRLF));
	CPPUNIT_ASSERT(sentLen == strlen(HTTP::CRLF));

	SocketInputStream sockIn(sock);
	InputStreamReader inReader(&sockIn);
	BufferedReader bufReader(&inReader);

	do {
		line = bufReader.readLine();
		readLen = strlen(line);
		printf("%d:%s\n", readLen, line);
	} while (2 < readLen);

	CPPUNIT_ASSERT(sock->close() == true);
	delete sock;
#else
	sock = new Socket();
	printf("connect = %d\n", sock->connect(CG_HOST_IPADDR, 80));
	printf("\n");
	printf("%s\n", TEST_HTTP_METHOD);

	sentLen = sock->send(TEST_HTTP_METHOD, strlen(TEST_HTTP_METHOD));
	printf("sentLen = %d\n", sentLen);
	sentLen = sock->send(HTTP::CRLF, strlen(HTTP::CRLF));
	printf("sentLen = %d\n", sentLen);
	sentLen = sock->send(HTTP::CRLF, strlen(HTTP::CRLF));
	printf("sentLen = %d\n", sentLen);

	SocketInputStream sockIn(sock);
	InputStreamReader inReader(&sockIn);
	BufferedReader bufReader(&inReader);

	do {
		line = bufReader.readLine();
		readLen = strlen(line);
		printf("%d:%s\n", readLen, line);
	} while (2 < readLen);

	printf("close = %d\n", sock->close());
	delete sock;
#endif
}

////////////////////////////////////////
// defined TENGINE
////////////////////////////////////////

#if !defined(TENGINE)

////////////////////////////////////////
// testNoUseIOStream
////////////////////////////////////////

const char *TEST_HTTP_HEADER_NAME = "testHeader";
const char *TEST_HTTP_HEADER2_NAME = "testHeader2";
const int TEST_HTTP_HEADER_INT_VALUE = 123456;
const long TEST_HTTP_HEADER_LONG_VALUE = 123456789;
const char *TEST_HTTP_HEADER_STRING = "testHeader: 123456\r\ntestHeader2: 123456789\r\n" ;

const char TEST_HTTP_CONTENT_RANGE_STRING1[] = "bytes 111-222/333";
const char TEST_HTTP_CONTENT_RANGE_STRING2[] = "bytes 111-222/*";

const char TEST_HTTP_CASHCTRL_STRING[] = "max-age=123456";

void UPnPTestCase::testNoUseIOStream()
{
	HTTPPacket *httpPacket;
	HTTPHeader *header;
	string headerStr;
	
	// HTTPPacket::setHeader (int)
	httpPacket = new HTTPPacket();
	httpPacket->setHeader(TEST_HTTP_HEADER_NAME, TEST_HTTP_HEADER_INT_VALUE);
	CPPUNIT_ASSERT(httpPacket->getHeader(TEST_HTTP_HEADER_NAME) != NULL);
	CPPUNIT_ASSERT(httpPacket->getIntegerHeaderValue(TEST_HTTP_HEADER_NAME) ==  TEST_HTTP_HEADER_INT_VALUE);
	delete httpPacket;

	// HTTPPacket::setHeader (long)
	httpPacket = new HTTPPacket();
	httpPacket->setHeader(TEST_HTTP_HEADER_NAME, TEST_HTTP_HEADER_LONG_VALUE);
	CPPUNIT_ASSERT(httpPacket->getHeader(TEST_HTTP_HEADER_NAME) != NULL);
	CPPUNIT_ASSERT(httpPacket->getLongHeaderValue(TEST_HTTP_HEADER_NAME) ==  TEST_HTTP_HEADER_LONG_VALUE);
	delete httpPacket;

	// HTTPPacket::getHeaderString
	httpPacket = new HTTPPacket();
	httpPacket->setHeader(TEST_HTTP_HEADER_NAME, TEST_HTTP_HEADER_INT_VALUE);
	httpPacket->setHeader(TEST_HTTP_HEADER2_NAME, TEST_HTTP_HEADER_LONG_VALUE);
	httpPacket->getHeaderString(headerStr);
	CPPUNIT_ASSERT(headerStr.compare(TEST_HTTP_HEADER_STRING) == 0);
	delete httpPacket;

	// HTTPPacket::setContentRange
	long contentRagne[3];
	httpPacket = new HTTPPacket();
	
	httpPacket->setContentRange(111, 222, 333);
	header = httpPacket->getHeader(HTTP::CONTENT_RANGE);
	CPPUNIT_ASSERT(header != NULL);
	CPPUNIT_ASSERT(strcmp(header->getValue(), TEST_HTTP_CONTENT_RANGE_STRING1) == 0);
	httpPacket->getContentRange(contentRagne);
	CPPUNIT_ASSERT(contentRagne[0] == 111);
	CPPUNIT_ASSERT(contentRagne[1] == 222);
	CPPUNIT_ASSERT(contentRagne[2] == 333);
	
	httpPacket->setContentRange(111, 222, 0);
	header = httpPacket->getHeader(HTTP::CONTENT_RANGE);
	CPPUNIT_ASSERT(header != NULL);
	CPPUNIT_ASSERT(strcmp(header->getValue(), TEST_HTTP_CONTENT_RANGE_STRING2) == 0);
	httpPacket->getContentRange(contentRagne);
	CPPUNIT_ASSERT(contentRagne[0] == 111);
	CPPUNIT_ASSERT(contentRagne[1] == 222);
	CPPUNIT_ASSERT(contentRagne[2] == 0);
	delete httpPacket;
	
	// HTTPPacket::setCacheControl
	httpPacket = new HTTPPacket();
	httpPacket->setCacheControl(HTTP::MAX_AGE, 123456);
	header = httpPacket->getHeader(HTTP::CACHE_CONTROL);
	CPPUNIT_ASSERT(header != NULL);
	CPPUNIT_ASSERT(strcmp(header->getValue(), TEST_HTTP_CASHCTRL_STRING) == 0);
	CPPUNIT_ASSERT(strcmp(httpPacket->getCacheControl(), TEST_HTTP_CASHCTRL_STRING) == 0);
	delete httpPacket;

	// SSDPRequest::setLeaseTime
	SSDPRequest *ssdpReq = new SSDPRequest();
	ssdpReq->setLeaseTime(300);
	CPPUNIT_ASSERT(ssdpReq->getLeaseTime() == 300);
	
	// URLGetAbsoluteURL
	string urlBuf;
	URLGetAbsoluteURL("http://www.cybergarage.org:8080/test.html", "blog/index.html", urlBuf);
	CPPUNIT_ASSERT(strcmp(urlBuf.c_str(), "http://www.cybergarage.org:8080/blog/index.html") == 0);
	delete ssdpReq;

	// GetHostURL
	string hostBuf;
	GetHostURL("www.cybergarage.org", 8080, "/blog/index.html", hostBuf);
	CPPUNIT_ASSERT(strcmp(hostBuf.c_str(), "http://www.cybergarage.org:8080/blog/index.html") == 0);
}

////////////////////////////////////////
// testSocket
////////////////////////////////////////

void UPnPTestCase::testSocket()
{
	struct addrinfo *addrInfo;
	bool ret = toSocketAddrInfo(SOCK_STREAM, "192.168.100.10", 80, &addrInfo, true);
	if (ret == true)
		freeaddrinfo(addrInfo);
	CPPUNIT_ASSERT(ret);
}

////////////////////////////////////////
// testIPv6
////////////////////////////////////////

void UPnPTestCase::testIPv6()
{
	NetworkInterfaceList ifList;
	GetHostAddresses(ifList);
	
	int ifCnt = ifList.size();
	CPPUNIT_ASSERT(0 < ifCnt);

	string ipv6if;
	for (int n=0; n<ifCnt; n++) {
		NetworkInterface *netif = ifList.getNetworkInterface(n);
		const char *ifaddr = netif->getAddress();
		if (CyberNet::IsIPv6Address(ifaddr) == false)
			continue;
		ipv6if = ifaddr;
	}

	CPPUNIT_ASSERT(0 < ipv6if.size());

	SSDPSearchSocket ssdpSearchSock;
	CPPUNIT_ASSERT (ssdpSearchSock.open(ipv6if.c_str()) == true);
	ssdpSearchSock.close();
}

////////////////////////////////////////
// testHTTPContentRange
////////////////////////////////////////

	
void UPnPTestCase::testHTTPContentRange() 
{
	HTTPRequest httpReq;
		
	//The first 500 bytes:
	httpReq.setContentRange(0, 499, 1234);
	CPPUNIT_ASSERT(httpReq.getContentRangeFirstPosition() == 0);
	CPPUNIT_ASSERT(httpReq.getContentRangeLastPosition() == 499);
	CPPUNIT_ASSERT(httpReq.getContentRangeInstanceLength() == 1234);
		
	//The second 500 bytes:
	httpReq.setContentRange(500, 999, 1234);
	CPPUNIT_ASSERT(httpReq.getContentRangeFirstPosition() == 500);
	CPPUNIT_ASSERT(httpReq.getContentRangeLastPosition() == 999);
	CPPUNIT_ASSERT(httpReq.getContentRangeInstanceLength() == 1234);

	//All except for the first 500 bytes:
	httpReq.setContentRange(500, 1233, 1234);
	CPPUNIT_ASSERT(httpReq.getContentRangeFirstPosition() == 500);
	CPPUNIT_ASSERT(httpReq.getContentRangeLastPosition() == 1233);
	CPPUNIT_ASSERT(httpReq.getContentRangeInstanceLength() == 1234);

	//All except for the first 500 bytes:
	httpReq.setContentRange(734, 1233, 1234);
	CPPUNIT_ASSERT(httpReq.getContentRangeFirstPosition() == 734);
	CPPUNIT_ASSERT(httpReq.getContentRangeLastPosition() == 1233);
	CPPUNIT_ASSERT(httpReq.getContentRangeInstanceLength() == 1234);

	//All except for the first 500 bytes:
	httpReq.setContentRange(734, 1233, 0);
	CPPUNIT_ASSERT(httpReq.getContentRangeFirstPosition() == 734);
	CPPUNIT_ASSERT(httpReq.getContentRangeLastPosition() == 1233);
	CPPUNIT_ASSERT(httpReq.getContentRangeInstanceLength() == 0);
}

////////////////////////////////////////
// testHTTPContentRange
////////////////////////////////////////
	
void UPnPTestCase::testHTTPConnection() 
{
	HTTPRequest httpReq;

	httpReq.setConnection(HTTP::CLOSE);
	CPPUNIT_ASSERT(httpReq.isCloseConnection() == true);

	httpReq.setConnection(HTTP::KEEP_ALIVE);
	CPPUNIT_ASSERT(httpReq.isKeepAliveConnection() == true);
}

////////////////////////////////////////
// testHTTPServer
////////////////////////////////////////
	
void UPnPTestCase::doContentRangeTest(HTTPRequest *httpReq, const char *host, int port, const char *postUri, bool keepAlive, const char *content, int firstPos, int lastPos)
{
	// CONTENT_RANGE Test	
	httpReq->setMethod(HTTP::GET);
	httpReq->setURI(postUri);
	httpReq->setContentRange(firstPos, lastPos, strlen(content));
	HTTPResponse *httpRes = httpReq->post(host, port, keepAlive);
	CPPUNIT_ASSERT(httpRes->isSuccessful() == true);
	string resContent = httpRes->getContent();
	long resContentLen = httpRes->getContentLength();
	long contentLen = lastPos - firstPos + 1;
	string contentStr = content;
	string rangeContent = contentStr.substr(firstPos, (int)contentLen);
	CPPUNIT_ASSERT(resContent.compare(rangeContent) == 0);
	CPPUNIT_ASSERT(resContentLen == contentLen);
}
	
void UPnPTestCase::doHTTPServerTest(const char *postUri, bool keepAlive)
{
	NetworkInterfaceList netfiList;
	static int port = 0;
	string content = "123456789abcedfghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int contentLen;
	String rangeContent;
	
	// Change port number to execute this test continuous.
	if (port == 0)
		port = (int)(Random() * 10000.0f) + 30000;
	port++;
	
	// Get First Interface
	CPPUNIT_ASSERT(0 < GetHostAddresses(netfiList));
	NetworkInterface *netIf = netfiList.getNetworkInterface(0);
	const char *host = netIf->getAddress();
	
	// Start HTTP Server	
	TestHTTPServer httpServer;
	httpServer.setContent(content.c_str());
	CPPUNIT_ASSERT(httpServer.open(host, port) == true);
	CPPUNIT_ASSERT(httpServer.start() == true);

	// GET Test	
	HTTPResponse *httpRes;
	string resContent;
	long resContentLen;
	HTTPRequest httpReq;
	httpReq.setMethod(HTTP::GET);
	httpReq.setURI(postUri);
	httpRes = httpReq.post(host, port, keepAlive);
	CPPUNIT_ASSERT(httpRes->isSuccessful() == true);
	resContent = httpRes->getContent();
	resContentLen = httpRes->getContentLength();
	CPPUNIT_ASSERT(content.compare(resContent) == 0);
	CPPUNIT_ASSERT(resContentLen == content.length());

	// HEAD Test	
	httpReq.setMethod(HTTP::HEAD);
	httpReq.setURI(postUri);
	httpRes = httpReq.post(host, port, keepAlive);
	CPPUNIT_ASSERT(httpRes->isSuccessful() == true);
	resContent = httpRes->getContent();
	resContentLen = httpRes->getContentLength();
	contentLen = content.length();
	CPPUNIT_ASSERT(resContent.length() == 0);
	CPPUNIT_ASSERT(resContentLen == content.length());
	
	// CONTENT_RANGE Test	
	doContentRangeTest(&httpReq, host, port, postUri, keepAlive, content.c_str(), 0, 19);
	doContentRangeTest(&httpReq, host, port, postUri, keepAlive, content.c_str(), 10, 26);
	
	// Stop HTTP Server
	CPPUNIT_ASSERT(httpServer.stop() == true);
	CPPUNIT_ASSERT(httpServer.close() == true);
}
	
void UPnPTestCase::testHTTPServer()
{
	// None keep alive test
	doHTTPServerTest(TestHTTPServer::TEST_URI, false);
	doHTTPServerTest(TestHTTPServer::TEST_INPUTSTREAM_URI,false);
	doHTTPServerTest(TestHTTPServer::TEST_CHUNKED_URI,false);
	
	// Keep alive test
	doHTTPServerTest(TestHTTPServer::TEST_URI, true);
	doHTTPServerTest(TestHTTPServer::TEST_INPUTSTREAM_URI,true);
	doHTTPServerTest(TestHTTPServer::TEST_CHUNKED_URI, true);
}
	
//////////////////////////////////////////////////////////////////////
// testStringParse
//////////////////////////////////////////////////////////////////////

void UPnPTestCase::testStringParse()
{
	string valueStr;
	
	//UINT_MAX : 4294967295U
	// INT_MAX : 2147483647
	Integer2String(1, valueStr);
	CPPUNIT_ASSERT(strcmp("1", valueStr.c_str()) == 0);
	Integer2String(INT_MAX, valueStr);
	CPPUNIT_ASSERT(strcmp("2147483647", valueStr.c_str()) == 0);
	Integer2String(-1, valueStr);
	CPPUNIT_ASSERT(strcmp("-1", valueStr.c_str()) == 0);
	Integer2String(-INT_MAX, valueStr);
	CPPUNIT_ASSERT(strcmp("-2147483647", valueStr.c_str()) == 0);
	
	// UINT_LONG : 18446744073709551615UL
	// LONG_MAX :	9223372036854775807L
	Long2String(1, valueStr);
	CPPUNIT_ASSERT(strcmp("1", valueStr.c_str()) == 0);
	Long2String(INT_MAX, valueStr);
	CPPUNIT_ASSERT(strcmp("2147483647", valueStr.c_str()) == 0);
	Long2String(-1, valueStr);
	CPPUNIT_ASSERT(strcmp("-1", valueStr.c_str()) == 0);
	Long2String(-INT_MAX, valueStr);
	CPPUNIT_ASSERT(strcmp("-2147483647", valueStr.c_str()) == 0);
}

//////////////////////////////////////////////////////////////////////
// testStringTokenizer
//////////////////////////////////////////////////////////////////////

void UPnPTestCase::testStringTokenizer()
{
	StringTokenizer *strToken;
	char *token[] = { "abcde", "test", "skonno" };
	char tokenStr[128];
	int tokenCnt;

	sprintf(tokenStr, "%s", token[0]);
	strToken = new StringTokenizer(tokenStr, ",");
	tokenCnt = 0;
	while( strToken->hasMoreTokens() == true) {
		const char *tstr = strToken->nextToken();
		CPPUNIT_ASSERT(strcmp(tstr, token[tokenCnt]) == 0);
		tokenCnt++;
	}
	CPPUNIT_ASSERT(tokenCnt == 1);
	delete strToken;

	sprintf(tokenStr, "%s,%s,%s", token[0], token[1], token[2]);
	strToken = new StringTokenizer(tokenStr, ",");
	tokenCnt = 0;
	while( strToken->hasMoreTokens() == true) {
		const char *tstr = strToken->nextToken();
		CPPUNIT_ASSERT(strcmp(tstr, token[tokenCnt]) == 0);
		tokenCnt++;
	}
	CPPUNIT_ASSERT(tokenCnt == 3);
	delete strToken;

	sprintf(tokenStr, "%s,%s,%s,", token[0], token[1], token[2]);
	strToken = new StringTokenizer(tokenStr, ",");
	tokenCnt = 0;
	while( strToken->hasMoreTokens() == true) {
		const char *tstr = strToken->nextToken();
		CPPUNIT_ASSERT(strcmp(tstr, token[tokenCnt]) == 0);
		tokenCnt++;
	}
	CPPUNIT_ASSERT(tokenCnt == 3);
	delete strToken;

	sprintf(tokenStr, ",%s,%s,%s,", token[0], token[1], token[2]);
	strToken = new StringTokenizer(tokenStr, ",");
	tokenCnt = 0;
	while( strToken->hasMoreTokens() == true) {
		const char *tstr = strToken->nextToken();
		CPPUNIT_ASSERT(strcmp(tstr, token[tokenCnt]) == 0);
		tokenCnt++;
	}
	CPPUNIT_ASSERT(tokenCnt == 3);
	delete strToken;

	strToken = new StringTokenizer("*", ",");
	tokenCnt = 0;
	while( strToken->hasMoreTokens() == true) {
		const char *tstr = strToken->nextToken();
		CPPUNIT_ASSERT(strcmp(tstr, "*") == 0);
		tokenCnt++;
	}
	CPPUNIT_ASSERT(tokenCnt == 1);
	delete strToken;

	sprintf(tokenStr, "%s", token[0]);
	strToken = new StringTokenizer(tokenStr, ", \n\t");
	tokenCnt = 0;
	while( strToken->hasMoreTokens() == true) {
		const char *tstr = strToken->nextToken();
		CPPUNIT_ASSERT(strcmp(tstr, token[tokenCnt]) == 0);
		tokenCnt++;
	}
	CPPUNIT_ASSERT(tokenCnt == 1);
	delete strToken;

	sprintf(tokenStr, "%s,,%s,,%s", token[0], token[1], token[2]);
	strToken = new StringTokenizer(tokenStr, ", \n\t");
	tokenCnt = 0;
	while( strToken->hasMoreTokens() == true) {
		const char *tstr = strToken->nextToken();
		CPPUNIT_ASSERT(strcmp(tstr, token[tokenCnt]) == 0);
		tokenCnt++;
	}
	CPPUNIT_ASSERT(tokenCnt == 3);
	delete strToken;

	sprintf(tokenStr, "  %s,  %s,  %s,  ", token[0], token[1], token[2]);
	strToken = new StringTokenizer(tokenStr, ", \n\t");
	tokenCnt = 0;
	while( strToken->hasMoreTokens() == true) {
		const char *tstr = strToken->nextToken();
		CPPUNIT_ASSERT(strcmp(tstr, token[tokenCnt]) == 0);
		tokenCnt++;
	}
	CPPUNIT_ASSERT(tokenCnt == 3);
	delete strToken;

	strToken = new StringTokenizer("*", ", \n\t");
	tokenCnt = 0;
	while( strToken->hasMoreTokens() == true) {
		const char *tstr = strToken->nextToken();
		CPPUNIT_ASSERT(strcmp(tstr, "*") == 0);
		tokenCnt++;
	}
	CPPUNIT_ASSERT(tokenCnt == 1);
	delete strToken;
}

//////////////////////////////////////////////////////////////////////
// testST
//////////////////////////////////////////////////////////////////////

void UPnPTestCase::testST()
{
	CPPUNIT_ASSERT(ST::IsAllDevice("ssdp:all") == true);
	CPPUNIT_ASSERT(ST::IsRootDevice("upnp:rootdevice") == true);
	CPPUNIT_ASSERT(ST::IsUUIDDevice("uuid:fdfasdfaf") == true);
	CPPUNIT_ASSERT(ST::IsURNDevice("urn:schemas-upnp-org:device:clock:1") == true);
	CPPUNIT_ASSERT(ST::IsURNService("urn:schemas-upnp-org:service:timer:1") == true);
}

//////////////////////////////////////////////////////////////////////
// testSSDP
//////////////////////////////////////////////////////////////////////

char *UPNP_TEST_MAXAGE_STR = "max-age=60";
int UPNP_TEST_MAXAGE = 60;

void UPnPTestCase::testSSDP()
{
	int mx = SSDP::GetLeaseTime(UPNP_TEST_MAXAGE_STR);
	CPPUNIT_ASSERT(UPNP_TEST_MAXAGE = mx);
}

//////////////////////////////////////////////////////////////////////
// testDevice
//////////////////////////////////////////////////////////////////////
char *UPNP_TEST_DEVICE_DESCR = 
"<?xml version=\"1.0\" ?>" 
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\">"
"	<specVersion>"
"		<major>1</major> "
"		<minor>0</minor> "
"	</specVersion>"
"	<device>"
"		<deviceType>urn:schemas-upnp-org:device:clock:1</deviceType> "
"		<friendlyName>CyberGarage Clock Device</friendlyName> "
"		<manufacture>CyberGarage</manufacture> "
"		<manufactureURL>http://www.cybergarage.org</manufactureURL> "
"		<modelDescription>CyberUPnP Clock Device</modelDescription> "
"		<modelName>Clock</modelName> "
"		<modelNumber>1.0</modelNumber> "
"		<modelURL>http://www.cybergarage.org</modelURL> "
"		<serialNumber>1234567890</serialNumber> "
"		<UDN>uuid:cybergarageClockDevice</UDN> "
"		<UPC>123456789012</UPC> "
"		<iconList>"
"			<icon>"
"				<mimetype>image/gif</mimetype> "
"				<width>48</width> "
"				<height>32</height>" 
"				<depth>8</depth> "
"				<url>icon.gif</url> "
"			</icon>"
"		</iconList>"
"		<serviceList>"
"			<service>"
"				<serviceType>urn:schemas-upnp-org:service:timer:1</serviceType> "
"				<serviceId>urn:schemas-upnp-org:serviceId:timer:1</serviceId> "
"				<SCPDURL>/service/timer/description.xml</SCPDURL> "
"				<controlURL>/service/timer/control</controlURL> "
"				<eventSubURL>/service/timer/eventSub</eventSubURL> "
"			</service>"
"		</serviceList>"
"		<presentationURL>http://www.cybergarage.org</presentationURL> "
"	</device>"
"</root>";

char *UPNP_TEST_SERVICE_DESCR = 
"<?xml version=\"1.0\"?>"
"<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\" >"
"	<specVersion>"
"		<major>1</major>"
"		<minor>0</minor>"
"	</specVersion>"
"	<actionList>"
"		<action>"
"			<name>SetTime</name>"
"			<argumentList>"
"				<argument>"
"					<name>NewTime</name>"
"					<relatedStateVariable>Time</relatedStateVariable>"
"					<direction>in</direction>"
"				</argument>"
"				<argument>"
"					<name>Result</name>"
"					<relatedStateVariable>Result</relatedStateVariable>"
"					<direction>out</direction>"
"				</argument>"
"			</argumentList>"
"		</action>"
"		<action>"
"			<name>GetTime</name>"
"			<argumentList>"
"				<argument>"
"					<name>CurrentTime</name>"
"					<relatedStateVariable>Time</relatedStateVariable>"
"					<direction>out</direction>"
"				</argument>"
"			</argumentList>"
"		</action>"
"	</actionList>"
"	<serviceStateTable>"
"		<stateVariable sendEvents=\"yes\">"
"			<name>Time</name>"
"			<dataType>string</dataType>"
"		</stateVariable>"
"		<stateVariable sendEvents=\"no\">"
"			<name>Result</name>"
"			<dataType>string</dataType>"
"		</stateVariable>"
"	</serviceStateTable>"
"</scpd>";

char *UPNP_TEST_DEVICE_TYPE = "urn:schemas-upnp-org:device:test:1";

void UPnPTestCase::testMemoryDevice()
{
	Device *dev = new Device();
	
	//// parse device description ////

	CPPUNIT_ASSERT(dev->loadDescription(UPNP_TEST_DEVICE_DESCR));

	CPPUNIT_ASSERT(strcmp(dev->getDeviceType(), "urn:schemas-upnp-org:device:clock:1") == 0);
	//cg_upnp_device_setdevicetype(dev, UPNP_TEST_DEVICE_TYPE);
	//CPPUNIT_ASSERT(strcmp(dev->getDeviceType(), UPNP_TEST_DEVICE_TYPE) == 0);
/*
	CPPUNIT_ASSERT(cg_upnp_device_isdevicetype(dev, UPNP_TEST_DEVICE_TYPE) == TRUE);
	
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getfriendlyname(dev), "CyberGarage Clock Device") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getmanufacture(dev), "CyberGarage") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getmanufactureurl(dev), "http://www.cybergarage.org") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getmodeldescription(dev), "CyberUPnP Clock Device") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getmodelname(dev), "Clock") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getmodelnumber(dev), "1.0") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getmodelurl(dev), "http://www.cybergarage.org") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getserialnumber(dev), "1234567890") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getudn(dev), "uuid:cybergarageClockDevice") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getupc(dev), "123456789012") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_device_getpresentationurl(dev), "http://www.cybergarage.org") == 0);

	CgUpnpService *service = cg_upnp_device_getservicebyname(dev, "urn:schemas-upnp-org:serviceId:timer:1");
	CPPUNIT_ASSERT(service != NULL);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_service_getservicetype(service), "urn:schemas-upnp-org:service:timer:1") == 0);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_service_getserviceid(service), "urn:schemas-upnp-org:serviceId:timer:1") == 0);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_service_getscpdurl(service), "/service/timer/description.xml") == 0);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_service_getcontrolurl(service), "/service/timer/control") == 0);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_service_geteventsuburl(service), "/service/timer/eventSub") == 0);
	
	CgUpnpIcon *icon = cg_upnp_device_geticon(dev, 0);
	CPPUNIT_ASSERT(icon != NULL);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_icon_getmimetype(icon), "image/gif") == 0);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_icon_getwidth(icon), "48") == 0);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_icon_getheight(icon), "32") == 0);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_icon_getdepth(icon), "8") == 0);
	CPPUNIT_ASSERT(cg_strcmp(cg_upnp_icon_geturl(icon), "icon.gif") == 0);
	
	//// parse service description ////
	CgUpnpService *timeService = cg_upnp_device_getservicebyname(dev, "urn:schemas-upnp-org:serviceId:timer:1");
	CPPUNIT_ASSERT(timeService != NULL);
	CPPUNIT_ASSERT(cg_upnp_service_getdevice(timeService) == dev);
	CPPUNIT_ASSERT(cg_upnp_service_getrootdevice(timeService) == dev);
	CgXmlNode *timeServiceNode = cg_upnp_service_getservicenode(timeService);
	CPPUNIT_ASSERT(timeServiceNode != NULL);
	CPPUNIT_ASSERT(cg_upnp_service_parsedescription(timeService, UPNP_TEST_SERVICE_DESCR, strlen(UPNP_TEST_SERVICE_DESCR)) == TRUE);
	
	CgUpnpAction *setAction = cg_upnp_service_getactionbyname(service, "SetTime");
	CPPUNIT_ASSERT(setAction != NULL);
	CgUpnpArgument *newArg = cg_upnp_action_getargumentbyname(setAction, "NewTime");
	CPPUNIT_ASSERT(cg_upnp_argument_isindirection(newArg) == TRUE);
	cg_upnp_argument_setvalue(newArg, "123456");
	CPPUNIT_ASSERT(cg_streq(cg_upnp_argument_getvalue(newArg), "123456") == TRUE);
	
	CgUpnpStateVariable *timeVar = cg_upnp_service_getstatevariablebyname(service, "Time");
	CPPUNIT_ASSERT(timeVar != NULL);
	CPPUNIT_ASSERT(strcmp(cg_upnp_statevariable_getdatatype(timeVar), "string") == 0);
	CPPUNIT_ASSERT(strcmp(cg_upnp_statevariable_getsendevents(timeVar), "yes") == 0);
	CPPUNIT_ASSERT(cg_upnp_statevariable_issendevents(timeVar) == TRUE);

	//// start ////
	
	cg_upnp_device_start(dev);
	
	//// stop ////
	
	cg_upnp_device_stop(dev);
	
	//// exit ////
	
	cg_upnp_device_delete(dev);
*/

	delete dev;
}

//////////////////////////////////////////////////////////////////////
// testDevice
//////////////////////////////////////////////////////////////////////

void UPnPTestCase::testDevice()
{
	/////////////////////////////
	// Init Device
	/////////////////////////////

	TestDevice *testDev = NULL;
	testDev = new TestDevice();
	CPPUNIT_ASSERT(testDev != NULL);
	testDev->start();

	/////////////////////////////
	// VariableTest
	/////////////////////////////
		
	StateVariable *statVal = testDev->getStateVariable("Count");
	CPPUNIT_ASSERT(statVal != NULL);
	statVal->setValue(10);
	CPPUNIT_ASSERT(atoi(statVal->getValue()) == 10);
	statVal->setValue((const char *)NULL);
	statVal->setValue(10);
	CPPUNIT_ASSERT(atoi(statVal->getValue()) == 10);

	/////////////////////////////
	// Init ControlPoint
	/////////////////////////////

	TestCtrlPoint *ctrlp = new TestCtrlPoint();
	ctrlp->start();

	Wait(20 * 1000);

	Device *ctrlpDev = ctrlp->getDevice("CyberGarageCountDevice");
	CPPUNIT_ASSERT(ctrlpDev != NULL);

	/////////////////////////////
	// Action Test
	/////////////////////////////
		
	Action *ctrlpSetCountAction = ctrlpDev->getAction("SetCount");
	CPPUNIT_ASSERT(ctrlpSetCountAction != NULL);
	ctrlpSetCountAction->setArgumentValue("NewCount", 12);
	CPPUNIT_ASSERT(ctrlpSetCountAction->postControlAction() == true);
		
	Action *ctrlpGetCountAction = ctrlpDev->getAction("GetCount");
	CPPUNIT_ASSERT(ctrlpGetCountAction != NULL);
	CPPUNIT_ASSERT(ctrlpGetCountAction->postControlAction() == true);
	CPPUNIT_ASSERT(ctrlpGetCountAction->getArgumentIntegerValue("CurrentCount") == 12);

	/////////////////////////////
	// Event Test
	/////////////////////////////

	Service *ctrlpCountService = ctrlpDev->getService("urn:schemas-upnp-org:service:count:1");
	CPPUNIT_ASSERT(ctrlpCountService != NULL);
	CPPUNIT_ASSERT(ctrlp->subscribe(ctrlpCountService) == true);
	CPPUNIT_ASSERT(ctrlp->unsubscribe(ctrlpCountService) == true);

	/////////////////////////////
	// Exit
	/////////////////////////////

	ctrlp->stop();
	delete ctrlp;

	testDev->stop();
	delete testDev;
}

//////////////////////////////////////////////////////////////////////
// testST
//////////////////////////////////////////////////////////////////////

void UPnPTestCase::testControlPoint()
{
	CPPUNIT_ASSERT(ST::IsAllDevice("ssdp:all") == true);
	CPPUNIT_ASSERT(ST::IsRootDevice("upnp:rootdevice") == true);
	CPPUNIT_ASSERT(ST::IsUUIDDevice("uuid:fdfasdfaf") == true);
	CPPUNIT_ASSERT(ST::IsURNDevice("urn:schemas-upnp-org:device:clock:1") == true);
	CPPUNIT_ASSERT(ST::IsURNService("urn:schemas-upnp-org:service:timer:1") == true);
}

//////////////////////////////////////////////////////////////////////
// testMediaServer
//////////////////////////////////////////////////////////////////////

void UPnPTestCase::testMediaServer()
{
/*
	TestMediaServer *mserver = NULL;
	mserver = new TestMediaServer();
	CPPUNIT_ASSERT(mserver != NULL);
	mserver->start();

	TestCtrlPoint *ctrlp = new TestCtrlPoint();
	ctrlp->start();

	Wait(20 * 1000);

	Device *mdev = ctrlp->getDevice("urn:schemas-upnp-org:device:MediaServer:1");
	CPPUNIT_ASSERT(mdev != NULL);

	ctrlp->stop();
	delete ctrlp;

	mserver->stop();
	delete mserver;
*/
}

//////////////////////////////////////////////////////////////////////
// testContentDirectory
//////////////////////////////////////////////////////////////////////

void UPnPTestCase::testContentDirectory()
{
	int n;

	ContentDirectory *condir = new ContentDirectory(NULL);
	char *searchStr;
	SearchCriteriaList searchList;
	int searchListCnt;

	searchStr = "*"; 
	searchList.clear();
	searchListCnt = condir->getSearchCriteriaList(searchStr, searchList);
	CPPUNIT_ASSERT(searchListCnt == 0);

	char *property[] = { "@id", "av:filmrollURI@av:codec", "av:filmrollURI@av:resolution" };
	char *value[] = { "2", "CLUT8", "80x60" };

	searchStr = "@id = \"2\"";
	searchList.clear();
	searchListCnt = condir->getSearchCriteriaList(searchStr, searchList);
	CPPUNIT_ASSERT(searchListCnt == 1);
	for (n=0; n<searchListCnt; n++) {
		SearchCriteria *searchCri = searchList.getSearchCriteria(n);
		CPPUNIT_ASSERT(strcmp(searchCri->getProperty(), property[n]) == 0);
		CPPUNIT_ASSERT(strcmp(searchCri->getValue(), value[n]) == 0);
	}

	searchStr = "@id = \"2\" and av:filmrollURI@av:codec = \"CLUT8\" and av:filmrollURI@av:resolution = \"80x60\""; 
	searchList.clear();
	searchListCnt = condir->getSearchCriteriaList(searchStr, searchList);
	CPPUNIT_ASSERT(searchListCnt == 3);
	for (n=0; n<searchListCnt; n++) {
		SearchCriteria *searchCri = searchList.getSearchCriteria(n);
		CPPUNIT_ASSERT(strcmp(searchCri->getProperty(), property[n]) == 0);
		CPPUNIT_ASSERT(strcmp(searchCri->getValue(), value[n]) == 0);
	}

	delete condir;
}

//////////////////////////////////////////////////////////////////////
// testST
//////////////////////////////////////////////////////////////////////

#ifdef SUPPORT_ITUNES

void UPnPTestCase::testITunesLibrary()
{
	iTunesLibrary iTunesLib;

	CPPUNIT_ASSERT(iTunesLib.update() == true);

}

#endif

////////////////////////////////////////
// endif TENGINE
////////////////////////////////////////

#endif
