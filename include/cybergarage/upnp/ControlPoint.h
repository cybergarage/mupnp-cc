/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ControlPoint.h
*
*	Revision;
*
*	07/11/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_CONTROLPOINT_H_
#define _CLINK_CONTROLPOINT_H_

<<<<<<< HEAD
#include <uhttp/net/HostInterface.h>
#include <uhttp/util/ListenerList.h>
#include <uhttp/util/Mutex.h>
#include <cybergarage/xml/NodeList.h>
#include <uhttp/http/HTTPRequestListener.h>
#include <uhttp/http/HTTPServerList.h>
=======
#include <cybergarage/net/HostInterface.h>
#include <cybergarage/util/ListenerList.h>
#include <cybergarage/util/Mutex.h>
#include <cybergarage/xml/NodeList.h>
#include <cybergarage/http/HTTPRequestListener.h>
#include <cybergarage/http/HTTPServerList.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#include <cybergarage/upnp/ssdp/SSDPPacket.h>
#include <cybergarage/upnp/ssdp/SSDPNotifySocketList.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponseSocketList.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponseSocket.h>
#include <cybergarage/upnp/device/SearchResponseListener.h>
#include <cybergarage/upnp/device/NotifyListener.h>
#include <cybergarage/upnp/device/Disposer.h>
<<<<<<< HEAD
#include <cybergarage/upnp/device/DeviceChangeListener.h>
#include <cybergarage/upnp/event/EventListener.h>
#include <cybergarage/upnp/control/RenewSubscriber.h>

namespace CyberLink {

class ControlPoint : public uHTTP::HTTPRequestListener
=======
#include <cybergarage/upnp/device/DeviceChangeListener.h>
#include <cybergarage/upnp/event/EventListener.h>
#include <cybergarage/upnp/control/RenewSubscriber.h>

namespace CyberLink {

class ControlPoint : public CyberHTTP::HTTPRequestListener
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	SSDPNotifySocketList ssdpNotifySocketList;
	SSDPSearchResponseSocketList ssdpSearchResponseSocketList;
	SSDPSearchResponseSocket ssdpSearchResponseSocket;

	int ssdpPort;
	int httpPort;
	
	CyberXML::NodeList  devNodeList;
	CyberXML::NodeList  removedDevNodeList;

<<<<<<< HEAD
	uHTTP::ListenerList deviceNotifyListenerList;
	uHTTP::ListenerList deviceSearchResponseListenerList;
	uHTTP::ListenerList deviceChangeListenerList;

	uHTTP::Mutex mutex;
=======
	CyberUtil::ListenerList deviceNotifyListenerList;
	CyberUtil::ListenerList deviceSearchResponseListenerList;
	CyberUtil::ListenerList deviceChangeListenerList;

	CyberUtil::Mutex mutex;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	DeviceList deviceList;

	int searchMx;

<<<<<<< HEAD
	uHTTP::HTTPServerList httpServerList;
	uHTTP::ListenerList eventListenerList;
=======
	CyberHTTP::HTTPServerList httpServerList;
	CyberUtil::ListenerList eventListenerList;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	std::string eventSubURI;

	Disposer *deviceDisposer;
	long expiredDeviceMonitoringInterval;
<<<<<<< HEAD

	bool nmprMode;
	RenewSubscriber *renewSubscriber;
=======

	bool nmprMode;
	RenewSubscriber *renewSubscriber;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

public:

	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////

	static const int DEFAULT_EVENTSUB_PORT;
	static const int DEFAULT_SSDP_PORT;
	static const char *DEFAULT_EVENTSUB_URI;
	static const int DEFAULT_EXPIRED_DEVICE_MONITORING_INTERVAL;

private:

	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

	SSDPNotifySocketList *getSSDPNotifySocketList()
	{
		return &ssdpNotifySocketList;
	}
	
	SSDPSearchResponseSocketList *getSSDPSearchResponseSocketList()
	{
		return &ssdpSearchResponseSocketList;
	}

	SSDPSearchResponseSocket *getSSDPSearchResponseSocket()
	{
		return &ssdpSearchResponseSocket;
	}
	
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

<<<<<<< HEAD
public:

=======
public:

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	ControlPoint(int ssdpPort = DEFAULT_SSDP_PORT, int httpPort = DEFAULT_EVENTSUB_PORT);
	virtual ~ControlPoint();

	////////////////////////////////////////////////
	//	Port (SSDP)
	////////////////////////////////////////////////

<<<<<<< HEAD
public:

=======
public:

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	int getSSDPPort() {
		return ssdpPort;
	}

	void setSSDPPort(int port) {
		ssdpPort = port;
	}

	////////////////////////////////////////////////
	//	Port (EventSub)
	////////////////////////////////////////////////

<<<<<<< HEAD
public:

=======
public:

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	int getHTTPPort() {
		return httpPort;
	}

	void setHTTPPort(int port) {
		httpPort = port;
	}
	
<<<<<<< HEAD
	////////////////////////////////////////////////
	//	NMPR
	////////////////////////////////////////////////

public:

	void setNMPRMode(bool flag)
	{
		nmprMode = flag;
	}

	bool isNMPRMode()
	{
		return nmprMode;
	}

=======
	////////////////////////////////////////////////
	//	NMPR
	////////////////////////////////////////////////

public:

	void setNMPRMode(bool flag)
	{
		nmprMode = flag;
	}

	bool isNMPRMode()
	{
		return nmprMode;
	}

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	////////////////////////////////////////////////
	//	Device List
	////////////////////////////////////////////////

private:

	void addDevice(CyberXML::Node *rootNode);
	void addDevice(SSDPPacket *ssdpPacket);

private:
	
	void initDeviceList();

public:

	Device *getDevice(CyberXML::Node *rootNode);

	DeviceList *getDeviceList()
	{
		return &deviceList;
	}

<<<<<<< HEAD
	Device *getDevice(const std::string &name);

	bool hasDevice(const std::string &name)
=======
	Device *getDevice(const char *name);

	bool hasDevice(const char *name)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return (getDevice(name) != NULL) ? true : false;
	}

private:

	void removeDevice(CyberXML::Node *rootNode);
	void removeDevice(Device *device);
<<<<<<< HEAD
	void removeDevice(const std::string &name);
=======
	void removeDevice(const char *name);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	void removeDevice(SSDPPacket *packet);

	////////////////////////////////////////////////
	//	Expired Device
	////////////////////////////////////////////////

public:

	void setExpiredDeviceMonitoringInterval(long interval)
	{
		expiredDeviceMonitoringInterval = interval;
	}

	long getExpiredDeviceMonitoringInterval()
	{
		return expiredDeviceMonitoringInterval;
	}
	
	void setDeviceDisposer(Disposer *disposer)
	{
		if (deviceDisposer != NULL)
			delete deviceDisposer;
		deviceDisposer = disposer;
	}
	
	Disposer *getDeviceDisposer()
	{
		return deviceDisposer;
	}

	void removeExpiredDevices();

	void clean();

	////////////////////////////////////////////////
	//	Notify
	////////////////////////////////////////////////

public:

	void addNotifyListener(NotifyListener *listener)
	{
		deviceNotifyListenerList.add(listener);
	}		

	void removeNotifyListener(NotifyListener *listener)
	{
		deviceNotifyListenerList.remove(listener);
	}		

	void performNotifyListener(SSDPPacket *ssdpPacket);

	////////////////////////////////////////////////
	//	SearchResponse
	////////////////////////////////////////////////

<<<<<<< HEAD
public:

=======
public:

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	void addSearchResponseListener(SearchResponseListener *listener)
	{
		deviceSearchResponseListenerList.add(listener);
	}		

	void removeSearchResponseListener(SearchResponseListener *listener)
	{
		deviceSearchResponseListenerList.remove(listener);
	}		

	void performSearchResponseListener(SSDPPacket *ssdpPacket);

<<<<<<< HEAD
	////////////////////////////////////////////////
	//  DeviceChangeListener
	//  Thanks for Oliver Newell (2004/10/16)
	////////////////////////////////////////////////

public:

	void addDeviceChangeListener(DeviceChangeListener *listener)
	{
		deviceChangeListenerList.add(listener);
	}		

	void removeDeviceChangeListener(DeviceChangeListener *listener)
	{
		deviceChangeListenerList.remove(listener);
	}		

	void performAddDeviceListener(Device *dev);
	void performRemoveDeviceListener(Device *dev);

=======
	////////////////////////////////////////////////
	//  DeviceChangeListener
	//  Thanks for Oliver Newell (2004/10/16)
	////////////////////////////////////////////////

public:

	void addDeviceChangeListener(DeviceChangeListener *listener)
	{
		deviceChangeListenerList.add(listener);
	}		

	void removeDeviceChangeListener(DeviceChangeListener *listener)
	{
		deviceChangeListenerList.remove(listener);
	}		

	void performAddDeviceListener(Device *dev);
	void performRemoveDeviceListener(Device *dev);

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	////////////////////////////////////////////////
	//	SSDPPacket
	////////////////////////////////////////////////
	
<<<<<<< HEAD
public:

=======
public:

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	void notifyReceived(SSDPPacket *packet);
	void searchResponseReceived(SSDPPacket *packet);

	////////////////////////////////////////////////
	//	M-SEARCH
	////////////////////////////////////////////////

public:

	int getSearchMx()
	{
		return searchMx;
	}

	void setSearchMx(int mx) 
	{
		searchMx = mx;
	}

<<<<<<< HEAD
	void search(const std::string &target, int mx);

	void search(const std::string &target)
=======
	void search(const char *target, int mx);

	void search(const char *target)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		search(target, SSDP::DEFAULT_MSEARCH_MX);
	}

	void search()
	{
		search(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
	}

	////////////////////////////////////////////////
	//	EventSub HTTPServer
	////////////////////////////////////////////////

private:

<<<<<<< HEAD
	uHTTP::HTTPServerList *getHTTPServerList()
=======
	CyberHTTP::HTTPServerList *getHTTPServerList()
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return &httpServerList;
	}

<<<<<<< HEAD
	void httpRequestRecieved(uHTTP::HTTPRequest *httpReq);
=======
	void httpRequestRecieved(CyberHTTP::HTTPRequest *httpReq);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	Event Listener 
	////////////////////////////////////////////////

public:

	void addEventListener(EventListener *listener)
	{
		eventListenerList.add(listener);
	}		

	void removeEventListener(EventListener *listener)
	{
		eventListenerList.remove(listener);
	}		

<<<<<<< HEAD
	void performEventListener(const std::string &uuid, long seq, const std::string &name, const std::string &value)
=======
	void performEventListener(const char *uuid, long seq, const char *name, const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		int listenerSize = eventListenerList.size();
		for (int n=0; n<listenerSize; n++) {
			EventListener *listener = (EventListener *)eventListenerList.get(n);
			listener->eventNotifyReceived(uuid, seq, name, value);
		}
	}

	////////////////////////////////////////////////
	//	Subscription 
	////////////////////////////////////////////////

public:	
	
	const char *getEventSubURI()
	{
		return eventSubURI.c_str();
	}

<<<<<<< HEAD
	void setEventSubURI(const std::string &url)
=======
	void setEventSubURI(const char *url)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		eventSubURI = url;
	}

private:

<<<<<<< HEAD
	const char *getEventSubCallbackURL(const std::string &host, std::string &buf)
	{
		return uHTTP::GetHostURL(host, getHTTPPort(), getEventSubURI(), buf);
=======
	const char *getEventSubCallbackURL(const char *host, std::string &buf)
	{
		return CyberNet::GetHostURL(host, getHTTPPort(), getEventSubURI(), buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}

public:

	bool subscribe(Service *service, long timeout);

	bool subscribe(Service *service)
	{
		return subscribe(service, Subscription::INFINITE_VALUE);
	}

<<<<<<< HEAD
	bool subscribe(Service *service, const std::string &uuid, long timeout);

	bool subscribe(Service *service, const std::string &uuid)
=======
	bool subscribe(Service *service, const char *uuid, long timeout);

	bool subscribe(Service *service, const char *uuid)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return subscribe(service, uuid, Subscription::INFINITE_VALUE);
	}

	bool isSubscribed(Service *service);
	
	bool unsubscribe(Service *service);
	void unsubscribe(Device *device);

	void unsubscribe()
	{
		DeviceList *devList = getDeviceList();
		int devCnt = devList->size();
		for (int n=0; n<devCnt; n++) {
			Device *dev = devList->getDevice(n);
			unsubscribe(dev);
		}		
	}

	////////////////////////////////////////////////
	//	getSubscriberService	
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	Service *getSubscriberService(const std::string &uuid)
=======
	Service *getSubscriberService(const char *uuid)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		DeviceList *devList = getDeviceList();
		int devCnt = devList->size();
		for (int n=0; n<devCnt; n++) {
			Device *dev = devList->getDevice(n);
			Service *service = dev->getSubscriberService(uuid);
			if (service != NULL)
				return service;
		}		
		return NULL;
	}
	
<<<<<<< HEAD
	////////////////////////////////////////////////
	//	getSubscriberService	
	////////////////////////////////////////////////

public:

	void renewSubscriberService(Device *dev, long timeout);
	void renewSubscriberService(long timeout);
	void renewSubscriberService();
	
	////////////////////////////////////////////////
	//	Subscriber
	////////////////////////////////////////////////
	
public:

	void setRenewSubscriber(RenewSubscriber *sub)
	{
		if (renewSubscriber != NULL)
			delete renewSubscriber;
		renewSubscriber = sub;
	}
	
	RenewSubscriber *getRenewSubscriber()
	{
		return renewSubscriber;	
	}

=======
	////////////////////////////////////////////////
	//	getSubscriberService	
	////////////////////////////////////////////////

public:

	void renewSubscriberService(Device *dev, long timeout);
	void renewSubscriberService(long timeout);
	void renewSubscriberService();
	
	////////////////////////////////////////////////
	//	Subscriber
	////////////////////////////////////////////////
	
public:

	void setRenewSubscriber(RenewSubscriber *sub)
	{
		if (renewSubscriber != NULL)
			delete renewSubscriber;
		renewSubscriber = sub;
	}
	
	RenewSubscriber *getRenewSubscriber()
	{
		return renewSubscriber;	
	}

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	////////////////////////////////////////////////
	//	run	
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	bool start(const std::string &target, int mx);

	bool start(const std::string &target)
=======
	bool start(const char *target, int mx);

	bool start(const char *target)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return start(target, SSDP::DEFAULT_MSEARCH_MX);
	}

	bool start()
	{
		return start(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
	}

	bool stop();

	////////////////////////////////////////////////
	//	lock
	////////////////////////////////////////////////

public:

	void lock()
	{
		mutex.lock();
	}

	void unlock()
	{
		mutex.unlock();
	}

	////////////////////////////////////////////////
	//	print
	////////////////////////////////////////////////

public:

	void print();
};

}

#endif

