/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Device.cpp
*
*	Revision:
*
*	08/13/03
*		- first revision
*	09/03/03
*		- Giordano Sassaroli <sassarol@cefriel.it>
*		- Problem : The device does not accepts request for services when control or subscription urls are absolute
*		- Error : device methods, when requests are received, search for services that have a controlUrl (or eventSubUrl) equal to the request URI
*		          but request URI must be relative, so they cannot equal absolute urls
*	09/03/03
*		- Steven Yen
*		- description: to retrieve service information based on information in URLBase and SCPDURL
*		- problem: not able to retrieve service information when URLBase is missing and SCPDURL is relative
*		- fix: modify to retrieve host information from Header's Location (required) field and update the
*		       BaseURL tag in the xml so subsequent information retrieval can be done (Steven Yen, 8.27.2003)
*		- note: 1. in the case that Header's Location field combine with SCPDURL is not able to retrieve proper 
*		          information, updating BaseURL would not hurt, since exception will be thrown with or without update.
*		        2. this problem was discovered when using PC running MS win XP with ICS enabled (gateway). 
*		          It seems that  root device xml file does not have BaseURL and SCPDURL are all relative.
*		        3. UPnP device architecture states that BaseURL is optional and SCPDURL may be relative as 
*		          specified by UPnP vendor, so MS does not seem to violate the rule.
*	10/22/03
*		- Added setActionListener().
*	01/05/04
*		- Changed about new QueryListener interface.
*	01/06/04
*		- Moved the following methods to StateVariable class.
*		  getQueryListener() 
*		  setQueryListener() 
*		  performQueryListener()
*		- Added new setQueryListener() to set a listner to all state variables.
*	03/26/04
*		- Jay Deen <j2deen_ca@yahoo.ca>
*		- Fixed Service::getDeviceList() to public method.
*	05/19/04
*		- Changed the header include order for Cygwin.
*	07/02/04
*		- Added serviceSearchResponse().
*		- Deleted getLocationURL().
*		- Fixed announce() to set the root device URL to the LOCATION field.
*	07/31/04
*		- Changed notify() to remove the expired subscribers and not to remove the invalid response subscribers for NMPR.
*	10/29/04
*		- Fixed a bug when notify() removes the expired devices().
*	03/30/05
*		- Added Service::isSCPDURL.
*	03/31/05
*		- Added getSCPDData().
* 	04/25/05
*		- Thanks for Mikael Hakman <mhakman@dkab.net>
* 		- Changed getSCPDData() to add a XML declaration at first line.
* 	06/21/05
*		- Changed notify() to continue when the subscriber is null.
*	08/21/05
*		- Changed getSCPDNode() using string instead of ostringstream.
*
******************************************************************/

#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/Action.h>
#include <cybergarage/upnp/UPnPStatus.h>
#include <cybergarage/upnp/device/ST.h>
#include <cybergarage/upnp/ssdp/SSDPNotifySocket.h>
#include <cybergarage/upnp/ssdp/SSDPNotifyRequest.h>
#include <cybergarage/upnp/control/QueryRequest.h>
#include <cybergarage/upnp/control/QueryListener.h>
#include <cybergarage/xml/Parser.h>
#include <cybergarage/util/Debug.h>
#include <string>

using namespace CyberLink;
using namespace CyberXML;
using namespace CyberNet;
using namespace CyberIO;
using namespace CyberHTTP;
using namespace CyberUtil;
using namespace std;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

const char *Service::ELEM_NAME = "service";
const char *Service::SERVICE_TYPE = "serviceType";
const char *Service::SERVICE_ID = "serviceId";
const char *Service::SCPDURL = "SCPDURL";
const char *Service::CONTROL_URL = "controlURL";
const char *Service::EVENT_SUB_URL = "eventSubURL";

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

Service::Service(CyberXML::Node *node)
{
	serviceNode = node;
	
	initServiceData();
	initActionList();
	initServiceStateTable();
}

Service::~Service()
{
}

////////////////////////////////////////////////
//	Device
////////////////////////////////////////////////

Device *Service::getRootDevice()
{
	return getDevice()->getRootDevice();
}

////////////////////////////////////////////////
//	deviceList
////////////////////////////////////////////////

void Service::initActionList()
{
	actionList.clear();
	Node *scdpNode = getSCPDNode();
	if (scdpNode == NULL)
		return;
	Node *actionListNode = scdpNode->getNode(ActionList::ELEM_NAME);
	if (actionListNode == NULL)
		return;
	Node *serviceNode = getServiceNode();
	int nNode = actionListNode->getNNodes();
	for (int n=0; n<nNode; n++) {
		Node *node = actionListNode->getNode(n);
		if (Action::isActionNode(node) == false)
			continue;
		Action *action = new Action(serviceNode, node);
		actionList.add(action);
	} 
}

CyberLink::Action *Service::getAction(const char *actionName)
{
	ActionList *actionList = getActionList();
	int nActions = actionList->size();
	for (int n=0; n<nActions; n++) {
		Action *action = actionList->getAction(n);
		const char *name = action->getName();
		if (name == NULL)
			continue;
		string nameStr = name;
		if (nameStr.compare(actionName) == 0)
			return action;
	}
	return NULL;
}

////////////////////////////////////////////////
//	serviceStateTable
////////////////////////////////////////////////

void Service::initServiceStateTable()
{
	serviceStateTable.clear();
	Node *scpdNode = getSCPDNode();
	if (scpdNode == NULL)
		return;
	Node *stateTableNode = scpdNode->getNode(ServiceStateTable::ELEM_NAME);
	if (stateTableNode == NULL)
		return;
	Node *serviceNode = getServiceNode();
	int nNode = stateTableNode->getNNodes();
	for (int n=0; n<nNode; n++) {
		Node *node = stateTableNode->getNode(n);
		if (StateVariable::isStateVariableNode(node) == false)
			continue;
		StateVariable *serviceVar = new StateVariable(serviceNode, node);
		serviceStateTable.add(serviceVar);
	} 
}

StateVariable *Service::getStateVariable(const char *name)
{
	ServiceStateTable *stateTable = getServiceStateTable();
	int tableSize = stateTable->size();
	for (int n=0; n<tableSize; n++) {
		StateVariable *var = stateTable->getStateVariable(n);
		const char *varName = var->getName();
		if (varName == NULL)
			continue;
		string varNameStr = varName;
		if (varNameStr.compare(name) == 0)
			return var;
	}
	return NULL;
}

////////////////////////////////////////////////
//	SCPD node
////////////////////////////////////////////////

CyberXML::Node *Service::getSCPDNode(CyberNet::URL *url)
{
	CyberXML::Parser parser;
	return parser.parse(url);
}

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 

CyberXML::Node *Service::getSCPDNode(CyberIO::File *file)
{
	CyberXML::Parser parser;
	return parser.parse(file);
}

#endif

CyberXML::Node *Service::getSCPDNode(const char *description)
{
	CyberXML::Parser parser;
	return parser.parse(description);
}

Node *Service::getSCPDNode()
{
	ServiceData *data = getServiceData();
	Node *scpdNode = data->getSCPDNode();
	if (scpdNode != NULL)
		return scpdNode;
	
	const char *scpdURLStr = getSCPDURL();
	URL scpdURL(scpdURLStr);
	scpdNode = getSCPDNode(&scpdURL);
	if (scpdNode != NULL) {
		data->setSCPDNode(scpdNode);
		return scpdNode;
	}

	Device *rootDev = getRootDevice();
	if (rootDev == NULL)
		return NULL;

	string urlBaseStr = rootDev->getURLBase();
	// Thanks for Steven Yen (2003/09/03)
	if (urlBaseStr.length() <= 0) {
			const char *location = rootDev->getLocation();
			string locationHost;
			HTTP::GetHost(location, locationHost);
			int locationPort = HTTP::GetPort(location);
			HTTP::GetRequestHostURL(locationHost.c_str(), locationPort, urlBaseStr);
	}
	string scpdURLStrBuf;
	scpdURLStr = HTTP::GetRelativeURL(scpdURLStr, scpdURLStrBuf);
	string newScpdURLStr;
	newScpdURLStr = urlBaseStr;
	newScpdURLStr.append(scpdURLStr);
	URL newScpdURL(newScpdURLStr.c_str());
	scpdNode = getSCPDNode(&newScpdURL);
	if (scpdNode != NULL) {
		data->setSCPDNode(scpdNode);
		return scpdNode;
	}

	string newScpdURLStrBuf;
	newScpdURLStr = HTTP::GetAbsoluteURL(urlBaseStr.c_str(), scpdURLStr, newScpdURLStrBuf);
	newScpdURL.setString(newScpdURLStr.c_str());
	scpdNode = getSCPDNode(&newScpdURL);
	if (scpdNode != NULL) {
		data->setSCPDNode(scpdNode);
		return scpdNode;
	}

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
	string descrFilePathBuf;
	string newScpdFileStr;
	newScpdFileStr = rootDev->getDescriptionFilePath(descrFilePathBuf);
	newScpdFileStr.append(scpdURLStr);
	File newScpdFile(newScpdFileStr.c_str());
	scpdNode = getSCPDNode(&newScpdFile);
	if (scpdNode != NULL) {
		data->setSCPDNode(scpdNode);
		return scpdNode;
	}
#endif

	return NULL;
}

const char *Service::getSCPDData(string &buf)
{
	Node *scpdNode = getSCPDNode();
	buf = "";
	if (scpdNode != NULL) {
		string nodeBuf;
		// Thanks for Mikael Hakman (04/25/05)
		buf = UPnP::XML_DECLARATION;
		buf += "\n";
		buf += scpdNode->toString(nodeBuf);
	}
	return buf.c_str();
}

////////////////////////////////////////////////
//	Load SCPD
////////////////////////////////////////////////

bool Service::loadSCPD(const char *description)
{
	Node *scpdNode = NULL;

	try {
		scpdNode = getSCPDNode(description);
	}
	catch (ParserException e) {
		string msg;
		msg = "Couldn't load description";
		Debug::warning(msg);
		Debug::warning(e);
		//throw InvalidDescriptionException(msg.c_str()); 
		return false;
	}

	if (scpdNode == NULL)
		return false;

	ServiceData *data = getServiceData();
	data->setSCPDNode(scpdNode);

	initServiceData();
	initActionList();
	initServiceStateTable();

	return true;
}

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 

bool Service::loadSCPD(CyberIO::File *file)
{
	string description;

	if (file->load(description) == false) {
		string msg;
		msg += "Couldn't load description file (";
		msg += file->getName();
		msg += ")";
		Debug::warning(msg);
		//throw InvalidDescriptionException(msg.c_str()); 
		return false;
	}

	if (loadSCPD(description.c_str()) == false)
		return false;

	return true;
}

#endif

////////////////////////////////////////////////
//	Notify
////////////////////////////////////////////////

bool Service::notify(Subscriber *sub, StateVariable *stateVar)
{
	const char *varName = stateVar->getName();
	const char *value = stateVar->getValue();
		
	const char *host = sub->getDeliveryHost();
	int port = sub->getDeliveryPort();
		
	NotifyRequest notifyReq;
	notifyReq.setRequest(sub, varName, value);
	
	CyberHTTP::HTTPResponse *res = notifyReq.post(host, port);
	if (res->isSuccessful() == false)
		return false;
			
	sub->incrementNotifyCount();		
		
	return true;
}

void Service::notify(StateVariable *stateVar)
{
	SubscriberList *subList = getSubscriberList();

	Subscriber **subArray;
	int subArrayCnt, n;

	// Remove expired subArraycribers.
	subArrayCnt = subList->size();
	subArray = new (Subscriber(*[subArrayCnt]));
	for (n=0; n<subArrayCnt; n++)
		subArray[n] = subList->getSubscriber(n);
	for (n=0; n<subArrayCnt; n++) {
		Subscriber *sub = subArray[n];
		if (sub == NULL)
			continue;
		if (sub->isExpired() == true)
			removeSubscriber(sub);
	}
	delete []subArray;
		
	// Notify to subArraycribers.
	subArrayCnt = subList->size();
	subArray = new (Subscriber(*[subArrayCnt]));
	for (n=0; n<subArrayCnt; n++)
		subArray[n] = subList->getSubscriber(n);
	for (n=0; n<subArrayCnt; n++) {
		Subscriber *sub = subArray[n];
		if (sub == NULL)
			continue;
		if (notify(sub, stateVar) == false) {
			/* Don't remove for NMPR specification.
			removeSubscriber(sub);
			*/
		}
	}
	delete []subArray;
}

void Service::notifyAllStateVariables()
{
	ServiceStateTable *stateTable = getServiceStateTable();
	int tableSize = stateTable->size();
	for (int n=0; n<tableSize; n++) {
		StateVariable *var = stateTable->getStateVariable(n);
		if (var->isSendEvents() == true)
			notify(var);
	}
}

////////////////////////////////////////////////
//	annouce
////////////////////////////////////////////////

const char *Service::getNotifyServiceTypeNT(std::string &buf)
{
	buf = getServiceType();
	return buf.c_str();
}

const char *Service::getNotifyServiceTypeUSN(string &buf)
{
	Device *dev = getDevice();
	buf = dev->getUDN();
	buf.append("::");
	buf.append(getServiceType());
	return  buf.c_str();
}

void Service::announce(const char *bindAddr)
{
	// uuid:device-UUID::urn:schemas-upnp-org:service:serviceType:v 
	
	string devLocation;
	Device *rootDev = getRootDevice();
	rootDev->getLocationURL(bindAddr, devLocation);

	string devNT, devUSN;
	getNotifyServiceTypeNT(devNT);			
	getNotifyServiceTypeUSN(devUSN);

	Device *dev = getDevice();
		
	SSDPNotifyRequest ssdpReq;
	string serverName;
	ssdpReq.setServer(UPnP::GetServerName(serverName));
	ssdpReq.setLeaseTime(dev->getLeaseTime());
	ssdpReq.setLocation(devLocation.c_str());
	ssdpReq.setNTS(NTS::ALIVE);
	ssdpReq.setNT(devNT.c_str());
	ssdpReq.setUSN(devUSN.c_str());

	SSDPNotifySocket ssdpSock(bindAddr);
	Device::notifyWait();
	ssdpSock.post(&ssdpReq);
}

void Service::byebye(const char *bindAddr)
{
	// uuid:device-UUID::urn:schemas-upnp-org:service:serviceType:v 
		
	string devNT, devUSN;
	getNotifyServiceTypeNT(devNT);			
	getNotifyServiceTypeUSN(devUSN);
		
	SSDPNotifyRequest ssdpReq;
	ssdpReq.setNTS(NTS::BYEBYE);
	ssdpReq.setNT(devNT.c_str());
	ssdpReq.setUSN(devUSN.c_str());

	SSDPNotifySocket ssdpSock(bindAddr);
	Device::notifyWait();
	ssdpSock.post(&ssdpReq);
}

////////////////////////////////////////////////
//	queryAction
////////////////////////////////////////////////

void Service::setQueryListener(QueryListener *listener)
{
	ServiceStateTable *stateTable = getServiceStateTable();
	int tableSize = stateTable->size();
	for (int n=0; n<tableSize; n++) {
		StateVariable *var = stateTable->getStateVariable(n);
		var->setQueryListener(listener);
	}
}

////////////////////////////////////////////////
//	isURL
////////////////////////////////////////////////
	
// Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/03/03)
bool Service::isURL(const char *referenceUrl, const char *url)
{
	if (referenceUrl == NULL || url == NULL)
		return false;
	bool ret = StringEquals(referenceUrl, url);
	if (ret == true)
		return true;
	string relativeRefUrl;
	HTTP::GetRelativeURL(referenceUrl, relativeRefUrl, false);
	ret = StringEquals(relativeRefUrl.c_str(), url);
	if (ret == true)
		return true;
	return false;
}

////////////////////////////////////////////////
//	Subscription
////////////////////////////////////////////////

void Service::addSubscriber(Subscriber *sub) 
{
	lock();
	SubscriberList *subList = getSubscriberList();
	subList->add(sub);
	unlock();
}

void Service::removeSubscriber(Subscriber *sub) 
{
	lock();
	getSubscriberList()->remove(sub);
	unlock();
}

Subscriber *Service::getSubscriberBySID(const char *name)
{
	SubscriberList *subList = getSubscriberList();
	Subscriber *findSub = NULL;
	lock();
	int subListCnt = subList->size();
	cout << "subListCnt = " << subListCnt << endl;
	for (int n=0; n<subListCnt; n++) {
		Subscriber *sub = subList->getSubscriber(n);
		const char *sid = sub->getSID();
		cout << "[" << n << "] = " << sid << endl;
		if (sid == NULL)
			continue;
		string sidStr = sid;
		if (sidStr.compare(name) == 0) {
			findSub = sub;
			break;
		}
	}
	unlock();
	return findSub;
}

Subscriber *Service::getSubscriberByDeliveryURL(const char *name)
{
	SubscriberList *subList = getSubscriberList();
	Subscriber *findSub = NULL;
	lock();
	int subListCnt = subList->size();
	for (int n=0; n<subListCnt; n++) {
		Subscriber *sub = subList->getSubscriber(n);
		if (sub == NULL)
			continue;
		const char *url = sub->getDeliveryURL();
		if (url == NULL)
			continue;
		string urlStr = url;
		if (urlStr.compare(name) == 0) {
			findSub = sub;
			break;
		}
	}
	unlock();
	return findSub;
}

////////////////////////////////////////////////
//	serviceSearchResponse
////////////////////////////////////////////////

bool Service::serviceSearchResponse(SSDPPacket *ssdpPacket)
{
	string ssdpST;
	ssdpPacket->getST(ssdpST);
	
	if (ssdpST.length() <= 0)
		return false;
		
	Device *dev = getDevice();
			
	string serviceNT, serviceUSN;
	getNotifyServiceTypeNT(serviceNT);			
	getNotifyServiceTypeUSN(serviceUSN);
	
	if (ST::IsAllDevice(ssdpST.c_str()) == true) {
		dev->postSearchResponse(ssdpPacket, serviceNT.c_str(), serviceUSN.c_str());
	}
	else if (ST::IsURNService(ssdpST.c_str()) == true) {
		const char *serviceType = getServiceType();
		if (ssdpST.compare(serviceType) == 0)
			dev->postSearchResponse(ssdpPacket, serviceType, serviceUSN.c_str());
	}
	
	return true;
}

////////////////////////////////////////////////
//	ActionListener
////////////////////////////////////////////////

void Service::setActionListener(ActionListener *listener)
{
	lock();
	ActionList *actionList = getActionList();
	int nActions = actionList->size();
	for (int n=0; n<nActions; n++) {
		Action *action = actionList->getAction(n);
		action->setActionListener(listener);
	}
	unlock();
}
