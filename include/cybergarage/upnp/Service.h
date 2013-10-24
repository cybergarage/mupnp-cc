/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Service.h
*
*	Revision;
*
*	07/22/03
*		- first revision
*	03/30/05
*		- Removed setDescriptionURL() and getDescriptionURL().
*
******************************************************************/

#ifndef _CLINK_SERVICE_H_
#define _CLINK_SERVICE_H_

<<<<<<< HEAD
#include <uhttp/net/HostInterface.h>
#include <uhttp/io/File.h>
#include <uhttp/net/URL.h>

=======
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#include <cybergarage/upnp/xml/DeviceData.h>
#include <cybergarage/upnp/ActionList.h>
#include <cybergarage/upnp/StateVariable.h>
#include <cybergarage/upnp/ServiceStateTable.h>
#include <cybergarage/upnp/xml/ServiceData.h>
#include <cybergarage/upnp/event/NotifyRequest.h>
#include <cybergarage/upnp/event/SubscriberList.h>
#include <cybergarage/upnp/control/QueryRequest.h>
#include <cybergarage/upnp/control/ActionListener.h>
<<<<<<< HEAD
#include <uhttp/util/Mutex.h>
#include <uhttp/util/Vector.h>
#include <uhttp/util/StringUtil.h>
#include <cybergarage/xml/Node.h>
=======
#include <cybergarage/net/HostInterface.h>
#include <cybergarage/util/Mutex.h>
#include <cybergarage/util/Vector.h>
#include <cybergarage/util/StringUtil.h>
#include <cybergarage/xml/Node.h>
#include <cybergarage/io/File.h>
#include <cybergarage/net/URL.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

namespace CyberLink {

class Device;

class Service
{
	CyberXML::Node *serviceNode;
	
	ActionList actionList;
	ServiceStateTable serviceStateTable;

<<<<<<< HEAD
	uHTTP::Mutex mutex;
=======
	CyberUtil::Mutex mutex;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

public:
	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////
	
	static const char *ELEM_NAME;
	static const char *SERVICE_TYPE;
	static const char *SERVICE_ID;
	static const char *SCPDURL;
	static const char *CONTROL_URL;
	static const char *EVENT_SUB_URL;

public:

	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

	CyberXML::Node *getServiceNode()
	{
		return serviceNode;
	}

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	Service(CyberXML::Node *node);

	~Service();

private:

	void initServiceData()
	{
		ServiceData *data = getServiceData();
		if (data != NULL)
			data->setService(this);
	}

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
	//	isServiceNode
	////////////////////////////////////////////////

public:

	static bool isServiceNode(CyberXML::Node *node)
	{
		return node->isName(Service::ELEM_NAME);
	}
	
	////////////////////////////////////////////////
	//	Device/Root Node
	////////////////////////////////////////////////

private:

	CyberXML::Node *getDeviceNode()
	{
		CyberXML::Node *node = getServiceNode()->getParentNode();
		if (node == NULL)
			return NULL;
		return node->getParentNode();
	}

	CyberXML::Node *getRootNode()
	{
		return getServiceNode()->getRootNode();
	}

	////////////////////////////////////////////////
	//	Device
	////////////////////////////////////////////////

public:

	Device *getDevice()
	{
		CyberXML::Node *node = getDeviceNode();
		DeviceData *data = (DeviceData *)node->getUserData();
		if (data == NULL)
			return NULL;
		return data->getDevice();
	}

	Device *getRootDevice();

	////////////////////////////////////////////////
	//	serviceType
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	void setServiceType(const std::string &value)
=======
	void setServiceType(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getServiceNode()->setNode(SERVICE_TYPE, value);
	}

	const char *getServiceType()
	{
		return getServiceNode()->getNodeValue(SERVICE_TYPE);
	}

	////////////////////////////////////////////////
	//	serviceID
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	void setServiceID(const std::string &value)
=======
	void setServiceID(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getServiceNode()->setNode(SERVICE_ID, value);
	}

	const char *getServiceID()
	{
		return getServiceNode()->getNodeValue(SERVICE_ID);
	}

	////////////////////////////////////////////////
	//	isURL
	////////////////////////////////////////////////

private:

<<<<<<< HEAD
	bool isURL(const std::string &referenceUrl, const std::string &url);
=======
	bool isURL(const char *referenceUrl, const char *url);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	SCPDURL
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	void setSCPDURL(const std::string &value)
=======
	void setSCPDURL(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getServiceNode()->setNode(SCPDURL, value);
	}

	const char *getSCPDURL()
	{
		return getServiceNode()->getNodeValue(SCPDURL);
	}

<<<<<<< HEAD
	bool isSCPDURL(const std::string &url)
=======
	bool isSCPDURL(const char *url)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return isURL(getSCPDURL(), url);
	}
	
<<<<<<< HEAD
	const char *getSCPDData(std::string &buf);

=======
	const char *getSCPDData(std::string &buf);

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	////////////////////////////////////////////////
	//	controlURL
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	void setControlURL(const std::string &value)
=======
	void setControlURL(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getServiceNode()->setNode(CONTROL_URL, value);
	}

	const char *getControlURL()
	{
		return getServiceNode()->getNodeValue(CONTROL_URL);
	}

<<<<<<< HEAD
	bool isControlURL(const std::string &url)
=======
	bool isControlURL(const char *url)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return isURL(getControlURL(), url);
	}

	////////////////////////////////////////////////
	//	eventSubURL
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	void setEventSubURL(const std::string &value)
=======
	void setEventSubURL(const char *value)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getServiceNode()->setNode(EVENT_SUB_URL, value);
	}

	const char *getEventSubURL()
	{
		return getServiceNode()->getNodeValue(EVENT_SUB_URL);
	}

<<<<<<< HEAD
	bool isEventSubURL(const std::string &url)
=======
	bool isEventSubURL(const char *url)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return isURL(getEventSubURL(), url);
	}

	////////////////////////////////////////////////
	//	SCPD node
	////////////////////////////////////////////////

public:

<<<<<<< HEAD
	bool loadSCPD(const std::string &descString);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	bool loadSCPD(uHTTP::File *file);
#endif

private:
	CyberXML::Node *getSCPDNode(uHTTP::URL *url);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	CyberXML::Node *getSCPDNode(uHTTP::File *file);
#endif
	CyberXML::Node *getSCPDNode(const std::string &description);
=======
	bool loadSCPD(const char *descString);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	bool loadSCPD(CyberIO::File *file);
#endif

private:
	CyberXML::Node *getSCPDNode(CyberNet::URL *url);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	CyberXML::Node *getSCPDNode(CyberIO::File *file);
#endif
	CyberXML::Node *getSCPDNode(const char *description);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	CyberXML::Node *getSCPDNode();

public:
	////////////////////////////////////////////////
	//	actionList
	////////////////////////////////////////////////

private:

	void initActionList();

public:

	ActionList *getActionList()
	{
		return &actionList;
	}

<<<<<<< HEAD
	Action *getAction(const std::string &actionName);
=======
	Action *getAction(const char *actionName);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	
	////////////////////////////////////////////////
	//	serviceStateTable
	////////////////////////////////////////////////

private:

	void initServiceStateTable();

public:

	ServiceStateTable *getServiceStateTable()
	{
		return &serviceStateTable;
	}

<<<<<<< HEAD
	StateVariable *getStateVariable(const std::string &name);
	
	bool hasStateVariable(const std::string &name)
=======
	StateVariable *getStateVariable(const char *name);
	
	bool hasStateVariable(const char *name)
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		return (getStateVariable(name) != NULL) ? true : false;
	}

	////////////////////////////////////////////////
	//	isService
	////////////////////////////////////////////////
	
<<<<<<< HEAD
	bool isService(const std::string &name)
	{
		uHTTP::String nameStr(name);
=======
	bool isService(const char *name)
	{
		if (name == NULL)
				return false;
		CyberUtil::String nameStr = name;
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
		if (nameStr.endsWith(getServiceType()) == true)
			return true;
		if (nameStr.endsWith(getServiceID()) == true)
			return true;
		return false;
	}
	 
	////////////////////////////////////////////////
	//	UserData
	////////////////////////////////////////////////

	ServiceData *getServiceData()
	{
		CyberXML::Node *node = getServiceNode();
		if (node == NULL)
			return NULL;
		ServiceData *userData = (ServiceData *)node->getUserData();
		if (userData == NULL) {
			userData = new ServiceData();
			node->setUserData(userData);
		}
		return userData;
	}

	////////////////////////////////////////////////
	//	Notify
	////////////////////////////////////////////////

private:

	const char *getNotifyServiceTypeNT(std::string &buf);
	const char *getNotifyServiceTypeUSN(std::string &buf);

public:

<<<<<<< HEAD
	void announce(const std::string &bindAddr);
	void byebye(const std::string &bindAddr);
=======
	void announce(const char *bindAddr);
	void byebye(const char *bindAddr);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

	////////////////////////////////////////////////
	//	serviceSearchResponse	
	////////////////////////////////////////////////

public:

	bool serviceSearchResponse(SSDPPacket *ssdpPacket);

	////////////////////////////////////////////////
	//	queryAction
	////////////////////////////////////////////////

public:

	void setQueryListener(QueryListener *listener);

	////////////////////////////////////////////////
	//	Subscription
	////////////////////////////////////////////////

public:

	SubscriberList *getSubscriberList() 
	{
		return getServiceData()->getSubscriberList();
	}

	void addSubscriber(Subscriber *sub);
	void removeSubscriber(Subscriber *sub);

<<<<<<< HEAD
	Subscriber *getSubscriberBySID(const std::string &name);
	Subscriber *getSubscriberByDeliveryURL(const std::string &name);
=======
	Subscriber *getSubscriberBySID(const char *name);
	Subscriber *getSubscriberByDeliveryURL(const char *name);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

private:
	
	bool notify(Subscriber *sub, StateVariable *stateVar);

public:

	void notify(StateVariable *stateVar);
	void notifyAllStateVariables();
	
	////////////////////////////////////////////////
	// SID
	////////////////////////////////////////////////

	const char *getSID() 
	{
		return getServiceData()->getSID();
	}

<<<<<<< HEAD
	void setSID(const std::string &sid) 
=======
	void setSID(const char *sid) 
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	{
		getServiceData()->setSID(sid);
	}

	void clearSID()
	{
		setSID("");
		setTimeout(0);
	}
	
	bool hasSID()
	{
<<<<<<< HEAD
		return uHTTP::StringHasData(getSID());
=======
		return CyberUtil::StringHasData(getSID());
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}		

	bool isSubscribed()
	{
		return hasSID();
	}
	
	////////////////////////////////////////////////
	// Timeout
	////////////////////////////////////////////////

public:

	long getTimeout() 
	{
		return getServiceData()->getTimeout();
	}

	void setTimeout(long value) 
	{
		getServiceData()->setTimeout(value);
	}

	////////////////////////////////////////////////
	// AcionListener
	////////////////////////////////////////////////
	
public:
	
	void setActionListener(ActionListener *listener);

};

}

#endif

