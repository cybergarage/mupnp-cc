/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ControlPoint.cpp
*
*	Revision:
*
*	07/15/03
*		- first revision
*	09/08/03
*		- Giordano Sassaroli <sassarol@cefriel.it>
*		- Problem : when an event notification message is received and the message
*		            contains updates on more than one variable, only the first variable update
*		            is notified.
*		- Error :  the other xml nodes of the message are ignored
*		- Fix : add two methods to the NotifyRequest for extracting the property array
*                and modify the httpRequestRecieved method in ControlPoint
*	01/06/04
*		- Added the following methods to remove expired devices automatically
*		  removeExpiredDevices()
*		  setExpiredDeviceMonitoringInterval()/getExpiredDeviceMonitoringInterval()
*		  setDeviceDisposer()/getDeviceDisposer()
*	04/20/04
*		- Added the following methods.
*		  start(const char *target, int mx) and start(const char *target).
*	04/28/04
*		- Added a remove node list and clean() to delete removed devices..
*		- Added lockDeviceList() and unlockDeviceList().
*		- Added lockSubscriberList() and unlockSubscriberList().
*	06/23/04
*		- Added setNMPRMode() and isNMPRMode().
*	07/08/04
*		- Added renewSubscriberService().
*		- Changed start() to create renew subscriber thread when the NMPR mode is true.
*	08/17/04
*		- Fixed removeExpiredDevices() to remove using the device array.
*	10/16/04
*		- Oliver Newell <newell@media-rush.com>
*		- Added this class to allow ControlPoint applications to be notified when 
*		  the ControlPoint base class adds/removes a UPnP device
*
******************************************************************/

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/util/Debug.h>
#include <cybergarage/xml/Parser.h>

#include <iostream>

using namespace std;
using namespace CyberLink;
using namespace CyberXML;
using namespace CyberNet;
using namespace CyberHTTP;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

const int ControlPoint::DEFAULT_EVENTSUB_PORT = 8058;
const int ControlPoint::DEFAULT_SSDP_PORT = 8008;
const char *ControlPoint::DEFAULT_EVENTSUB_URI = "/evetSub";
const int ControlPoint::DEFAULT_EXPIRED_DEVICE_MONITORING_INTERVAL = 60;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

ControlPoint::ControlPoint(int ssdpPort, int httpPort)
{
	setSSDPPort(ssdpPort);
	setHTTPPort(httpPort);
	setSearchMx(SSDP::DEFAULT_MSEARCH_MX);
	setEventSubURI(DEFAULT_EVENTSUB_URI);
	deviceDisposer = NULL;
	setExpiredDeviceMonitoringInterval(DEFAULT_EXPIRED_DEVICE_MONITORING_INTERVAL);
	setNMPRMode(false);
	renewSubscriber = NULL;

}

ControlPoint::~ControlPoint()
{
	stop();
}

////////////////////////////////////////////////
//	Device List
////////////////////////////////////////////////

Device *ControlPoint::getDevice(Node *rootNode)
{
	if (rootNode == NULL)
			return NULL;
	Node *devNode = rootNode->getNode(Device::ELEM_NAME);
	if (devNode == NULL)
			return NULL;
	return new Device(rootNode, devNode);
}

void ControlPoint::initDeviceList()
{
	lock();
	deviceList.clear();
	int nRoots = devNodeList.size();
	for (int n=0; n<nRoots; n++) {
		Node *rootNode = devNodeList.getNode(n);
		Device *dev = getDevice(rootNode);
		if (dev == NULL)
			continue;
		deviceList.add(dev);
	} 
	unlock();
 }

Device *ControlPoint::getDevice(const char *name)
{
	DeviceList *devList = getDeviceList();
	int nDevs = devList->size();
	for (int n=0; n<nDevs; n++) {
		Device *dev = devList->getDevice(n);
		if (dev->isDevice(name) == true)
			return dev;
		Device *cdev = dev->getDevice(name);
		if (cdev != NULL)
			return cdev;
	} 
	return NULL;
}

////////////////////////////////////////////////
//	add
////////////////////////////////////////////////

void ControlPoint::addDevice(CyberXML::Node *rootNode)
{
	lock();
	devNodeList.add(rootNode);
	unlock();
}

void ControlPoint::addDevice(SSDPPacket *ssdpPacket)
{
	if (ssdpPacket->isRootDevice() == false)
		return;
	
	lock();
	
	string usnBuf;
	string udnBuf;
	const char *usn = ssdpPacket->getUSN(usnBuf);
	const char *udn = USN::GetUDN(usn, udnBuf);
	Device *dev = getDevice(udn);
	if (dev != NULL) {
		dev->setSSDPPacket(ssdpPacket);
		unlock();
		return;
	}

	string locationBuf;
	const char *location = ssdpPacket->getLocation(locationBuf);
	URL locationURL(location);
	Parser parser;
	Node *rootNode = parser.parse(&locationURL);
	Device *rootDev = getDevice(rootNode);
	if (rootDev == NULL) {
		unlock();
		return;
	}
	rootDev->setSSDPPacket(ssdpPacket);

	unlock();

	addDevice(rootNode);

	initDeviceList();

	// Thanks for Oliver Newell (2004/10/16)
	performAddDeviceListener( rootDev );
}

////////////////////////////////////////////////
//	remove
////////////////////////////////////////////////

void ControlPoint::removeDevice(CyberXML::Node *rootNode)
{
	lock();
	devNodeList.remove(rootNode);
	removedDevNodeList.add(rootNode);
	unlock();

	initDeviceList();
}

void ControlPoint::removeDevice(Device *dev)
{
	if (dev == NULL)
		return;
	// Thanks for Oliver Newell (2004/10/16)
	if(dev->isRootDevice() == true)
		performRemoveDeviceListener(dev);
	removeDevice(dev->getRootNode());
}

void ControlPoint::removeDevice(const char *name)
{
	Device *dev = getDevice(name);
	removeDevice(dev);
}

void ControlPoint::removeDevice(SSDPPacket *packet)
{
	if (packet->isByeBye() == false)
		return;
	string usnBuf;
	string udnBuf;
	const char *usn = packet->getUSN(usnBuf);
	const char *udn = USN::GetUDN(usn, udnBuf);
	removeDevice(udn);
}

////////////////////////////////////////////////
//	Expired Device
////////////////////////////////////////////////
	
void ControlPoint::removeExpiredDevices()
{
	int n;
	DeviceList *devList = getDeviceList();
	int devCnt = devList->size();
	Device **dev = new (Device(*[devCnt]));
	for (n=0; n<devCnt; n++)
		dev[n] = devList->getDevice(n);
	for (n=0; n<devCnt; n++) {
		if (dev[n]->isExpired() == true) {
			string msg = "Expired device = ";
			msg += dev[n]->getFriendlyName();
			Debug::message(msg.c_str());
			Node *rootNode = dev[n]->getRootNode();
			removeDevice(rootNode);
		}
	}
	delete []dev;
	initDeviceList();
}

void ControlPoint::clean()
{
	removedDevNodeList.clear();
}

////////////////////////////////////////////////
//	Notify
////////////////////////////////////////////////
		
void ControlPoint::performNotifyListener(SSDPPacket *ssdpPacket)
{
	int listenerSize = deviceNotifyListenerList.size();
	for (int n=0; n<listenerSize; n++) {
		NotifyListener *listener = (NotifyListener *)deviceNotifyListenerList.get(n);
		listener->deviceNotifyReceived(ssdpPacket);
	}
}

////////////////////////////////////////////////
//	SearchResponse
////////////////////////////////////////////////

void ControlPoint::performSearchResponseListener(SSDPPacket *ssdpPacket)
{
	int listenerSize = deviceSearchResponseListenerList.size();
	for (int n=0; n<listenerSize; n++) {
		SearchResponseListener *listener = (SearchResponseListener *)deviceSearchResponseListenerList.get(n);
		listener->deviceSearchResponseReceived(ssdpPacket);
	}
}


////////////////////////////////////////////////
//	DeviceChangeListener
//  Thanks for Oliver Newell (2004/10/16)
////////////////////////////////////////////////

void ControlPoint::performAddDeviceListener(Device *dev)
{
	int listenerSize = deviceChangeListenerList.size();
	for (int n=0; n<listenerSize; n++) {
		DeviceChangeListener *listener = (DeviceChangeListener *)deviceChangeListenerList.get(n);
		listener->deviceAdded(dev);
	}
}

void ControlPoint::performRemoveDeviceListener(Device *dev)
{
	int listenerSize = deviceChangeListenerList.size();
	for (int n=0; n<listenerSize; n++) {
		DeviceChangeListener *listener = (DeviceChangeListener *)deviceChangeListenerList.get(n);
		listener->deviceRemoved( dev );
	}
}

////////////////////////////////////////////////
//	SSDPPacket
////////////////////////////////////////////////
	
void ControlPoint::notifyReceived(SSDPPacket *packet)
{
	if (packet->isRootDevice() == true) {
		if (packet->isAlive() == true)
			addDevice(packet);
		if (packet->isByeBye() == true)
			removeDevice(packet);
	}
	performNotifyListener(packet);
}

void ControlPoint::searchResponseReceived(SSDPPacket *packet)
{
	if (packet->isRootDevice() == true)
		addDevice(packet);
	performSearchResponseListener(packet);
}

////////////////////////////////////////////////
//	M-SEARCH
////////////////////////////////////////////////

void ControlPoint::search(const char *target, int mx)
{
	SSDPSearchRequest msReq(target, mx);
	SSDPSearchResponseSocketList *ssdpSearchResponseSocketList = getSSDPSearchResponseSocketList();
	ssdpSearchResponseSocketList->post(&msReq);
}

////////////////////////////////////////////////
//	EventSub HTTPServer
////////////////////////////////////////////////

void ControlPoint::httpRequestRecieved(HTTPRequest *httpReq)
{
	if (Debug::isOn() == true)
		httpReq->print();
		
	// Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/08/03)
	if (httpReq->isNotifyRequest() == true) {
		NotifyRequest notifyReq(httpReq);
		string uuidBuf;
		const char *uuid = notifyReq.getSID(uuidBuf);
		long seq = notifyReq.getSEQ();
		PropertyList *props = notifyReq.getPropertyList();
		int propCnt = props->size();
		for (int n = 0; n < propCnt; n++) {
			Property *prop = props->getProperty(n);
			const char *varName = prop->getName();
			const char *varValue = prop->getValue();
			performEventListener(uuid, seq, varName, varValue);
		}
		httpReq->returnOK();
		return;
	}
		
	httpReq->returnBadRequest();
}

////////////////////////////////////////////////
//	Subscription 
////////////////////////////////////////////////

bool ControlPoint::subscribe(Service *service, long timeout)
{
	if (service->isSubscribed() == true) {
		const char *sid = service->getSID();
		return subscribe(service, sid, timeout);
	}
	
	Device *rootDev = service->getRootDevice();
	if (rootDev == NULL)
		return false;
	
	lock();
	
	const char *ifAddress = rootDev->getInterfaceAddress();		 
	SubscriptionRequest subReq;
	string callbackURLBuf;
	subReq.setSubscribeRequest(service, getEventSubCallbackURL(ifAddress, callbackURLBuf), timeout);
	if (Debug::isOn() == true)
		subReq.print();	
	SubscriptionResponse *subRes = subReq.post();
	if (Debug::isOn() == true)
		subRes->print();	
	bool ret = false;
	if (subRes->isSuccessful() == true) {
		string sidBuf;
		service->setSID(subRes->getSID(sidBuf));
		service->setTimeout(subRes->getTimeout());
		ret = true;
	}
	else
		service->clearSID();
	
	unlock();
	
	return ret;
}

bool ControlPoint::subscribe(Service *service, const char *uuid, long timeout)
{
	SubscriptionRequest subReq;
	subReq.setRenewRequest(service, uuid, timeout);
	if (Debug::isOn() == true)
		subReq.print();	
	SubscriptionResponse *subRes = subReq.post();
	if (Debug::isOn() == true)
		subRes->print();	
	if (subRes->isSuccessful() == true) {
		string sidBuf;
		service->setSID(subRes->getSID(sidBuf));
		service->setTimeout(subRes->getTimeout());
		return true;
	}
	service->clearSID();
	return false;
}

bool ControlPoint::isSubscribed(Service *service)
{
	if (service == NULL)
		return false;
	return service->isSubscribed();
}

bool ControlPoint::unsubscribe(Service *service)
{
	SubscriptionRequest subReq;
	subReq.setUnsubscribeRequest(service);
	if (Debug::isOn() == true)
		subReq.print();	
	SubscriptionResponse *subRes = subReq.post();
	if (Debug::isOn() == true)
		subRes->print();	
	if (subRes->isSuccessful() == true) {
		service->clearSID();
		return true;
	}
	return false;
}

void ControlPoint::unsubscribe(Device *device)
{
	int n;

	ServiceList *serviceList = device->getServiceList();
	int serviceCnt = serviceList->size();
	for (n=0; n<serviceCnt; n++) {
		Service *service = serviceList->getService(n);
		if (service->hasSID() == true)
			unsubscribe(service);
	}

	DeviceList *childDevList = device->getDeviceList();
	int childDevCnt = childDevList->size();
	for (n=0; n<childDevCnt; n++) {
		Device *cdev = childDevList->getDevice(n);
		unsubscribe(cdev);
	}		
}

////////////////////////////////////////////////
//	getSubscriberService	
////////////////////////////////////////////////

void ControlPoint::renewSubscriberService(Device *dev, long timeout)
{
	int n;

	ServiceList *serviceList = dev->getServiceList();
	int serviceCnt = serviceList->size();
	for (n=0; n<serviceCnt; n++) {
		Service *service = serviceList->getService(n);
		if (service->isSubscribed() == false)
			continue;
		const char *sid = service->getSID();
		bool isRenewed = subscribe(service, sid, timeout);
		if (isRenewed == false)
			subscribe(service, timeout);
	}
		
	DeviceList *cdevList = dev->getDeviceList();
	int cdevCnt = cdevList->size();
	for (n=0; n<cdevCnt; n++) {
		Device *cdev = cdevList->getDevice(n);
		renewSubscriberService(cdev, timeout);
	}
}
	
void ControlPoint::renewSubscriberService(long timeout)
{
	lock();
	DeviceList *devList = getDeviceList();
	int devCnt = devList->size();
	for (int n=0; n<devCnt; n++) {
		Device *dev = devList->getDevice(n);
		renewSubscriberService(dev, timeout);
	}
	unlock();
}
	
void ControlPoint::renewSubscriberService()
{
	renewSubscriberService(Subscription::INFINITE_VALUE);
}

////////////////////////////////////////////////
//	run	
////////////////////////////////////////////////

bool ControlPoint::start(const char *target, int mx)
{
	stop();

	////////////////////////////////////////
	// HTTP Server
	////////////////////////////////////////
		
	int retryCnt = 0;
	int bindPort = getHTTPPort();
	HTTPServerList *httpServerList = getHTTPServerList();
	while (httpServerList->open(bindPort) == false) {
		retryCnt++;
		if (UPnP::SERVER_RETRY_COUNT < retryCnt)
			return false;
		setHTTPPort(bindPort + 1);
		bindPort = getHTTPPort();
	}
	httpServerList->addRequestListener(this);
	httpServerList->start();
		
	////////////////////////////////////////
	// Notify Socket
	////////////////////////////////////////
		
	SSDPNotifySocketList *ssdpNotifySocketList = getSSDPNotifySocketList();
	if (ssdpNotifySocketList->open() == false)
		return false;
	ssdpNotifySocketList->setControlPoint(this);			
	ssdpNotifySocketList->start();
		
	////////////////////////////////////////
	// SeachResponse Socket
	////////////////////////////////////////
		
	int ssdpPort = getSSDPPort();
	retryCnt = 0;
	SSDPSearchResponseSocketList *ssdpSearchResponseSocketList = getSSDPSearchResponseSocketList();
	while (ssdpSearchResponseSocketList->open(ssdpPort) == false) {
		retryCnt++;
		if (UPnP::SERVER_RETRY_COUNT < retryCnt)
			return false;
		setSSDPPort(ssdpPort + 1);
		ssdpPort = getSSDPPort();
	}
	ssdpSearchResponseSocketList->setControlPoint(this);
	ssdpSearchResponseSocketList->start();

	////////////////////////////////////////
	// search root devices
	////////////////////////////////////////
		
	search(target, mx);

	////////////////////////////////////////
	// Disposer
	////////////////////////////////////////

	Disposer *disposer = new Disposer(this);
	setDeviceDisposer(disposer);
	disposer->start();

	////////////////////////////////////////
	// Subscriber
	////////////////////////////////////////
		
	if (isNMPRMode() == true) {
		RenewSubscriber *renewSub = new RenewSubscriber(this);
		setRenewSubscriber(renewSub);
		renewSub->start();
	}

	return true;
}
	
bool ControlPoint::stop()
{
	unsubscribe();
		
	SSDPNotifySocketList *ssdpNotifySocketList = getSSDPNotifySocketList();
	ssdpNotifySocketList->stop();
	ssdpNotifySocketList->close();
	ssdpNotifySocketList->clear();
		
	SSDPSearchResponseSocketList *ssdpSearchResponseSocketList = getSSDPSearchResponseSocketList();
	ssdpSearchResponseSocketList->stop();
	ssdpSearchResponseSocketList->close();

	SSDPSearchResponseSocket *ssdpSearchResponseSocket = getSSDPSearchResponseSocket();
	ssdpSearchResponseSocket->stop();
	ssdpSearchResponseSocket->close();
	ssdpSearchResponseSocketList->clear();

	HTTPServerList *httpServerList = getHTTPServerList();
	httpServerList->stop();
	httpServerList->close();
	httpServerList->clear();

	////////////////////////////////////////
	// Disposer
	////////////////////////////////////////

	Disposer *disposer = getDeviceDisposer();
	if (disposer != NULL) {
		disposer->stop();
		setDeviceDisposer(NULL);
	}
	
	////////////////////////////////////////
	// Subscriber
	////////////////////////////////////////
		
	RenewSubscriber *renewSub = getRenewSubscriber();
	if (renewSub != NULL) {
		renewSub->stop();
		setRenewSubscriber(NULL);
	}

	return true;
}

////////////////////////////////////////////////
//	print
////////////////////////////////////////////////

void ControlPoint::print()
{
		DeviceList *devList = getDeviceList();
		int devCnt = devList->size();
		cout << "Device Num = " << devCnt << endl;
		for (int n=0; n<devCnt; n++) {
			Device *dev = devList->getDevice(n);
			cout << "[" << n <<  "] " << dev->getFriendlyName() << ", " << dev->getLeaseTime() << ", " << dev->getElapsedTime() << endl;
		}		
}

