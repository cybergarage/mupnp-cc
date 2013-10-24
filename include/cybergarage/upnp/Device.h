/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Device.h
*
*	Revision;
*
*	07/10/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_DEVICE_H_
#define _CLINK_DEVICE_H_

<<<<<<< HEAD
#include <uhttp/http/HTTPRequestListener.h>
#include <uhttp/util/StringUtil.h>
#include <uhttp/util/TimeUtil.h>
#include <cybergarage/xml/Node.h>
#include <uhttp/io/File.h>
=======
#include <cybergarage/http/HTTPRequestListener.h>
#include <cybergarage/util/StringUtil.h>
#include <cybergarage/util/TimeUtil.h>
#include <cybergarage/xml/Node.h>
#include <cybergarage/io/File.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#include <cybergarage/upnp/UPnP.h>
#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/DeviceList.h>
#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/ServiceList.h>
#include <cybergarage/upnp/Action.h>
#include <cybergarage/upnp/StateVariable.h>
#include <cybergarage/upnp/IconList.h>
#include <cybergarage/upnp/ssdp/SSDPResponse.h>
#include <cybergarage/upnp/device/SearchListener.h>
#include <cybergarage/upnp/device/InvalidDescriptionException.h>
#include <cybergarage/upnp/xml/DeviceData.h>
#include <cybergarage/upnp/event/SubscriptionRequest.h>
#include <cybergarage/upnp/event/SubscriptionResponse.h>
#include <cybergarage/upnp/device/Advertiser.h>
<<<<<<< HEAD
#include <uhttp/util/Mutex.h>
=======
#include <cybergarage/util/Mutex.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

#include <sstream>

namespace CyberLink {

<<<<<<< HEAD
class Device : public uHTTP::HTTPRequestListener, public SearchListener
=======
class Device : public CyberHTTP::HTTPRequestListener, public SearchListener
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
{
	CyberXML::Node *rootNode;
	CyberXML::Node *deviceNode;

	Device *rootDevice;
	Device *parentDevice;

	DeviceList deviceList;
	ServiceList serviceList;
	IconList iconList;

	bool localRootDeviceFlag;

	std::string devUUID;

<<<<<<< HEAD
	uHTTP::Mutex mutex;
=======
	CyberUtil::Mutex mutex;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	bool wirelessMode;

	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////
	
<<<<<<< HEAD
public:

=======
public:

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	static const char *ELEM_NAME;
	static const char *UPNP_ROOTDEVICE;
	static const int DEFAULT_STARTUP_WAIT_TIME;
	static const int DEFAULT_DISCOVERY_WAIT_TIME;
	static const int DEFAULT_LEASE_TIME;
	static const int HTTP_DEFAULT_PORT;
	static const char *DEFAULT_DESCRIPTION_URI;
	static const char *URLBASE_NAME;
	static const char *DEVICE_TYPE;
	static const char *FRIENDLY_NAME;
	static const char *MANUFACTURER;
	static const char *MANUFACTURER_URL;
	static const char *MODEL_DESCRIPTION;
	static const char *MODEL_NAME;
	static const char *MODEL_NUMBER;
	static const char *MODEL_URL;
	static const char *SERIAL_NUMBER;
	static const char *UDN;
	static const char *UPC;
	static const char *presentationURL;
	
	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

<<<<<<< HEAD
public:

=======
public:

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	CyberXML::Node *getRootNode();

	CyberXML::Node *getDeviceNode()
	{
		return deviceNode;
	}

	void setRootNode(CyberXML::Node *node)
	{
		rootNode = node;
	}

	void setDeviceNode(CyberXML::Node *node)
	{
		deviceNode = node;
	}
				
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	Device();
	Device(CyberXML::Node *root, CyberXML::Node *device);
	Device(CyberXML::Node *device);
<<<<<<< HEAD
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	Device(uHTTP::File *descriptionFile);
	Device(const std::string &descriptionFileName);
#endif
=======
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	Device(CyberIO::File *descriptionFile);
	Device(const char *descriptionFileName);
#endif
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

private:

	void initUUID();
	void initDeviceData();
	void initChildList();

public:

	virtual ~Device();

	////////////////////////////////////////////////
	// Mutex
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
	//	NMPR
	////////////////////////////////////////////////

public:

	void setNMPRMode(bool flag);
	bool isNMPRMode();

	////////////////////////////////////////////////
	//	Wireless
	////////////////////////////////////////////////
	
public:

	void setWirelessMode(bool flag)
	{
		wirelessMode = flag;
	}

	bool isWirelessMode()
	{
		return wirelessMode;
	}
	
	int getSSDPAnnounceCount()
	{
		if (isNMPRMode() == true && isWirelessMode() == true)
			return UPnP::INMPR03_DISCOVERY_OVER_WIRELESS_COUNT;
		return 1;
	}

	////////////////////////////////////////////////
	//	Device UUID
	////////////////////////////////////////////////

private:

<<<<<<< HEAD
	void setUUID(const std::string &uuid)
=======
	void setUUID(const char *uuid)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		devUUID = uuid;
	}

	const char *getUUID()
	{
		return devUUID.c_str();
	}

	void updateUDN()
	{
		std::string uuid;
		uuid.append("uuid:");
		uuid.append(getUUID());
		setUDN(uuid.c_str());
	}
	
	//////////////////////////////////////////////
	//	Root Device
	////////////////////////////////////////////////

private:

	void setLocalRootDeviceFlag(bool flag)
	{
		localRootDeviceFlag = flag;
	}

	bool isLocalRootDevice()
	{
		return localRootDeviceFlag;
	}

	 ////////////////////////////////////////////////
	//	Root Device
	////////////////////////////////////////////////

public:

	Device *getRootDevice();

	 ////////////////////////////////////////////////
	//	Parent Device
	////////////////////////////////////////////////

public:

	Device *getParentDevice();

	////////////////////////////////////////////////
	//	UserData
	////////////////////////////////////////////////

public:
	
	DeviceData *getDeviceData();

<<<<<<< HEAD
	bool hasDeviceData() {
        return (getDeviceData() ? true : false);
    }

=======
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	////////////////////////////////////////////////
	//	Description
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	void setDescriptionFile(const std::string &file)
=======
	void setDescriptionFile(const char *file)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceData()->setDescriptionFile(file);
	}

	const char *getDescriptionFile()
	{
		return getDeviceData()->getDescriptionFile();
	}

<<<<<<< HEAD
	void setDescriptionURI(const std::string &uri)
=======
	void setDescriptionURI(const char *uri)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceData()->setDescriptionURI(uri);
	}

	const char *getDescriptionURI()
	{
		return getDeviceData()->getDescriptionURI();
	}

<<<<<<< HEAD
	bool isDescriptionURI(const std::string &uri)
	{
		const char *descriptionURI = getDescriptionURI();
		if (descriptionURI == NULL)
			return false;
		uHTTP::String descriptionURIStr(descriptionURI);
=======
	bool isDescriptionURI(const char *uri)
	{
		const char *descriptionURI = getDescriptionURI();
		if (uri == NULL || descriptionURI == NULL)
			return false;
		CyberUtil::String descriptionURIStr = descriptionURI;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		return descriptionURIStr.equals(uri);
	}

	const char *getDescriptionFilePath(std::string &buf)
	{
		const char *descriptionFileName = getDescriptionFile();
		if (descriptionFileName == NULL)
			return "";
<<<<<<< HEAD
		uHTTP::File descriptionFile(descriptionFileName);
=======
		CyberIO::File descriptionFile(descriptionFileName);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		buf = descriptionFile.getAbsoluteFile()->getParent();
		return buf.c_str();
	}

<<<<<<< HEAD
	bool loadDescription(const std::string &descString);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	bool loadDescription(uHTTP::File *file);
#endif
=======
	bool loadDescription(const char *descString);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	bool loadDescription(CyberIO::File *file);
#endif
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

private:

	bool initializeLoadedDescription();

	////////////////////////////////////////////////
	//	isDeviceNode
	////////////////////////////////////////////////

public:

	static bool isDeviceNode(CyberXML::Node *node)
	{
		return node->isName(Device::ELEM_NAME);
	}
	
	////////////////////////////////////////////////
	//	Root Device
	////////////////////////////////////////////////

	bool isRootDevice()
	{
		return (getRootNode() != NULL) ? true : false;
	}
	
	////////////////////////////////////////////////
	//	Root Device
	////////////////////////////////////////////////

	void setSSDPPacket(SSDPPacket *packet)
	{
		getDeviceData()->setSSDPPacket(packet);
	}

	SSDPPacket *getSSDPPacket()
	{
		if (isRootDevice() == false)
			return NULL;
		return getDeviceData()->getSSDPPacket();
	}
	
	////////////////////////////////////////////////
	//	Location 
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setLocation(const std::string &value)
=======
	void setLocation(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceData()->setLocation(value);
	}

	const char *getLocation()
	{
		SSDPPacket *packet = getSSDPPacket();
		if (packet != NULL) {
			std::string buf;
			setLocation(packet->getLocation(buf));
		}
		return getDeviceData()->getLocation();
	}

	////////////////////////////////////////////////
	//	LeaseTime 
	////////////////////////////////////////////////

public:

	void setLeaseTime(int value);
	int getLeaseTime();

	////////////////////////////////////////////////
	//	TimeStamp 
	////////////////////////////////////////////////

public:

	long getTimeStamp();
	long getElapsedTime()
	{
		return time(NULL) - getTimeStamp();
	}

	bool isExpired();
	
	////////////////////////////////////////////////
	//	URL Base
	////////////////////////////////////////////////

private:

<<<<<<< HEAD
	void setURLBase(const std::string &value);

	void updateURLBase(const std::string &host);
=======
	void setURLBase(const char *value);

	void updateURLBase(const char *host);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

public:

	const char *getURLBase();

	////////////////////////////////////////////////
	//	deviceType
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setDeviceType(const std::string &value)
=======
	void setDeviceType(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(DEVICE_TYPE, value);
	}

	const char *getDeviceType()
	{
		return getDeviceNode()->getNodeValue(DEVICE_TYPE);
	}

<<<<<<< HEAD
	bool isDeviceType(const std::string &value);
=======
	bool isDeviceType(const char *value);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	friendlyName
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setFriendlyName(const std::string &value)
=======
	void setFriendlyName(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(FRIENDLY_NAME, value);
	}

	const char *getFriendlyName()
	{
		return getDeviceNode()->getNodeValue(FRIENDLY_NAME);
	}

	////////////////////////////////////////////////
	//	manufacture
	////////////////////////////////////////////////
	
<<<<<<< HEAD
	void setManufacturer(const std::string &value)
=======
	void setManufacturer(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(MANUFACTURER, value);
	}

	const char *getManufacturer()
	{
		return getDeviceNode()->getNodeValue(MANUFACTURER);
	}

	////////////////////////////////////////////////
	//	manufactureURL
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setManufacturerURL(const std::string &value)
=======
	void setManufacturerURL(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(MANUFACTURER_URL, value);
	}

	const char *getManufacturerURL()
	{
		return getDeviceNode()->getNodeValue(MANUFACTURER_URL);
	}

	////////////////////////////////////////////////
	//	modelDescription
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setModelDescription(const std::string &value)
=======
	void setModelDescription(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(MODEL_DESCRIPTION, value);
	}

	const char *getModelDescription()
	{
		return getDeviceNode()->getNodeValue(MODEL_DESCRIPTION);
	}

	////////////////////////////////////////////////
	//	modelName
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setModelName(const std::string &value)
=======
	void setModelName(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(MODEL_NAME, value);
	}

	const char *getModelName()
	{
		return getDeviceNode()->getNodeValue(MODEL_NAME);
	}

	////////////////////////////////////////////////
	//	modelNumber
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setModelNumber(const std::string &value)
=======
	void setModelNumber(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(MODEL_NUMBER, value);
	}

	const char *getModelNumber()
	{
		return getDeviceNode()->getNodeValue(MODEL_NUMBER);
	}

	////////////////////////////////////////////////
	//	modelURL
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setModelURL(const std::string &value)
=======
	void setModelURL(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(MODEL_URL, value);
	}

	const char *getModelURL()
	{
		return getDeviceNode()->getNodeValue(MODEL_URL);
	}

	////////////////////////////////////////////////
	//	serialNumber
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setSerialNumber(const std::string &value)
=======
	void setSerialNumber(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(SERIAL_NUMBER, value);
	}

	const char *getSerialNumber()
	{
		return getDeviceNode()->getNodeValue(SERIAL_NUMBER);
	}

	////////////////////////////////////////////////
	//	UDN
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setUDN(const std::string &value)
=======
	void setUDN(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(UDN, value);
	}

	const char *getUDN()
	{
		return getDeviceNode()->getNodeValue(UDN);
	}

	bool hasUDN()
	{
		const char *udn = getUDN();
		if (udn == NULL)
			return false;
		std::string udnStr = udn;
		if (udnStr.length() <= 0)
			return false;
		return true;
	}

	////////////////////////////////////////////////
	//	UPC
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setUPC(const std::string &value)
=======
	void setUPC(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(UPC, value);
	}

	const char *getUPC()
	{
		return getDeviceNode()->getNodeValue(UPC);
	}

	////////////////////////////////////////////////
	//	presentationURL
	////////////////////////////////////////////////

<<<<<<< HEAD
	void setPresentationURL(const std::string &value)
=======
	void setPresentationURL(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getDeviceNode()->setNode(presentationURL, value);
	}

	const char *getPresentationURL()
	{
		return getDeviceNode()->getNodeValue(presentationURL);
	}

	////////////////////////////////////////////////
	//	deviceList
	////////////////////////////////////////////////

private:

	void initDeviceList();

public:

	DeviceList *getDeviceList()
	{
		return &deviceList;
	}

<<<<<<< HEAD
	bool isDevice(const std::string &name);
	
	Device *getDevice(const std::string &name);
	Device *getDeviceByDescriptionURI(const std::string &uri);
=======
	bool isDevice(const char *name);
	
	Device *getDevice(const char *name);
	Device *getDeviceByDescriptionURI(const char *uri);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	
	////////////////////////////////////////////////
	//	serviceList
	////////////////////////////////////////////////

private:

	void initServiceList();

public:

	ServiceList *getServiceList()
	{
		return &serviceList;
	}

<<<<<<< HEAD
	Service *getService(const std::string &name);
	Service *getSubscriberService(const std::string &uuid);

public:

	Service *getServiceBySCPDURL(const std::string &searchUrl);
	Service *getServiceByControlURL(const std::string &searchUrl);
	Service *getServiceByEventSubURL(const std::string &searchUrl);
=======
	Service *getService(const char *name);
	Service *getSubscriberService(const char *uuid);

public:

	Service *getServiceBySCPDURL(const char *searchUrl);
	Service *getServiceByControlURL(const char *searchUrl);
	Service *getServiceByEventSubURL(const char *searchUrl);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	StateVariable
	////////////////////////////////////////////////

public:
	
<<<<<<< HEAD
	StateVariable *getStateVariable(const std::string &serviceType, const std::string &name);
	StateVariable *getStateVariable(const std::string &name);
=======
	StateVariable *getStateVariable(const char *serviceType, const char *name);
	StateVariable *getStateVariable(const char *name);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	Action
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	Action *getAction(const std::string &name);
=======
	Action *getAction(const char *name);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	iconList
	////////////////////////////////////////////////

private:

	void initIconList();

public:

	IconList *getIconList()
	{
		return &iconList;
	}
	
	Icon *getIcon(int n)
	{
		IconList *iconList = getIconList();
		if (n < 0 && ((int)iconList->size()-1) < n)
			return NULL;
		return iconList->getIcon(n);
	}

	////////////////////////////////////////////////
	//	Notify
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	const char *getLocationURL(const std::string &host, std::string &buf);
=======
	const char *getLocationURL(const char *host, std::string &buf);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

private:

	const char *getNotifyDeviceNT(std::string &buf);
	const char *getNotifyDeviceUSN(std::string &buf);
	const char *getNotifyDeviceTypeNT(std::string &buf);
	const char *getNotifyDeviceTypeUSN(std::string &buf);

public:

	static void notifyWait();

<<<<<<< HEAD
	void announce(const std::string &bindAddr);
	void announce();
	
	void byebye(const std::string &bindAddr);
=======
	void announce(const char *bindAddr);
	void announce();
	
	void byebye(const char *bindAddr);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	void byebye();

	////////////////////////////////////////////////
	//	Search
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	bool postSearchResponse(SSDPPacket *ssdpPacket, const std::string &st, const std::string &usn);
=======
	bool postSearchResponse(SSDPPacket *ssdpPacket, const char *st, const char *usn);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	void deviceSearchResponse(SSDPPacket *ssdpPacket);
	void deviceSearchReceived(SSDPPacket *ssdpPacket);

	////////////////////////////////////////////////
	//	HTTP Server	
	////////////////////////////////////////////////

public:

	void setHTTPPort(int port)
	{
		getDeviceData()->setHTTPPort(port);
	}
	
	int getHTTPPort()
	{
		return getDeviceData()->getHTTPPort();
	}

<<<<<<< HEAD
	void httpRequestRecieved(uHTTP::HTTPRequest *httpReq);

private:

	const char *getDescriptionData(const std::string &host, std::string &buf);
	void httpGetRequestRecieved(uHTTP::HTTPRequest *httpReq);
	void httpPostRequestRecieved(uHTTP::HTTPRequest *httpReq);
=======
	void httpRequestRecieved(CyberHTTP::HTTPRequest *httpReq);

private:

	const char *getDescriptionData(const char *host, std::string &buf);
	void httpGetRequestRecieved(CyberHTTP::HTTPRequest *httpReq);
	void httpPostRequestRecieved(CyberHTTP::HTTPRequest *httpReq);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	SOAP
	////////////////////////////////////////////////

private:

<<<<<<< HEAD
	void soapBadActionRecieved(uHTTP::HTTPRequest *soapReq);
	void soapActionRecieved(uHTTP::HTTPRequest *soapReq);
=======
	void soapBadActionRecieved(CyberHTTP::HTTPRequest *soapReq);
	void soapActionRecieved(CyberHTTP::HTTPRequest *soapReq);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	controlAction
	////////////////////////////////////////////////

private:

	void invalidActionControlRecieved(ControlRequest *ctlReq);
	void deviceControlRequestRecieved(ControlRequest *ctlReq, Service *service);
	void deviceActionControlRecieved(ActionRequest *ctlReq, Service *service);
	void deviceQueryControlRecieved(QueryRequest *ctlReq, Service *service);

	////////////////////////////////////////////////
	//	eventSubscribe
	////////////////////////////////////////////////

private:

	void upnpBadSubscriptionRecieved(SubscriptionRequest *subReq, int code);
	void deviceEventSubscriptionRecieved(SubscriptionRequest *subReq);
	void deviceEventNewSubscriptionRecieved(Service *service, SubscriptionRequest *subReq);
	void deviceEventRenewSubscriptionRecieved(Service *service, SubscriptionRequest *subReq);
	void deviceEventUnsubscriptionRecieved(Service *service, SubscriptionRequest *subReq);
	
	////////////////////////////////////////////////
	//	Thread	
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	uHTTP::HTTPServerList *getHTTPServerList() 
=======
	CyberHTTP::HTTPServerList *getHTTPServerList() 
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return getDeviceData()->getHTTPServerList();
	}

	SSDPSearchSocketList *getSSDPSearchSocketList() 
	{
		return getDeviceData()->getSSDPSearchSocketList();
	}

	void setAdvertiser(Advertiser *adv)
	{
		getDeviceData()->setAdvertiser(adv);
	}

	Advertiser *getAdvertiser()
	{
		return getDeviceData()->getAdvertiser();
	}

public:
	
	bool start();
	bool stop()
	{
		return stop(true);
	}

private:
	
	bool stop(bool doByeBye);

	////////////////////////////////////////////////
	// Interface Address
	////////////////////////////////////////////////

public:

	const char *getInterfaceAddress() 
	{
		SSDPPacket *ssdpPacket = getSSDPPacket();
		if (ssdpPacket == NULL)
			return "";
		return ssdpPacket->getLocalAddress();
	}

	////////////////////////////////////////////////
	// AcionListener
	////////////////////////////////////////////////
	
public:
	
	void setActionListener(ActionListener *listener);
	void setQueryListener(QueryListener *listener);

<<<<<<< HEAD
	////////////////////////////////////////////////
	// AcionListener (includeSubDevices)
	////////////////////////////////////////////////
	
public:
	
	void setActionListener(ActionListener *listener, bool includeSubDevices);
	void setQueryListener(QueryListener *listener, bool includeSubDevices);

=======
	////////////////////////////////////////////////
	// AcionListener (includeSubDevices)
	////////////////////////////////////////////////
	
public:
	
	void setActionListener(ActionListener *listener, bool includeSubDevices);
	void setQueryListener(QueryListener *listener, bool includeSubDevices);

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	////////////////////////////////////////////////
	//	output
	////////////////////////////////////////////////

/*
	public void output(PrintWriter ps) 
	{
		ps.println("deviceType = " + getDeviceType());
		ps.println("freindlyName = " + getFriendlyName());
		ps.println("presentationURL = " + getPresentationURL());

		DeviceList devList = getDeviceList();
		ps.println("devList = " + devList.size());
		
		ServiceList serviceList = getServiceList();
		ps.println("serviceList = " + serviceList.size());

		IconList iconList = getIconList();
		ps.println("iconList = " + iconList.size());
	}

	public void print()
	{
		PrintWriter pr = new PrintWriter(System.out);
		output(pr);
		pr.flush();
	}
*/
};

}

#endif
