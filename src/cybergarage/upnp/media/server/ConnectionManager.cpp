/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : ConnectionManager.cpp
*
*	Revision:
*
*	04/03/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/MediaServer.h>
#include <cybergarage/upnp/media/server/ConnectionManager.h>
#include <cybergarage/upnp/media/server/object/Format.h>

#include <string>
#include <sstream>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *ConnectionManager::DESCRIPTION = 
"<?xml version=\"1.0\" encoding=\"utf-8\"?> \n"
"<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\"> \n"
"   <specVersion> \n"
"      <major>1</major> \n"
"      <minor>0</minor> \n"
"   </specVersion> \n"
"   <actionList> \n"
"      <action> \n"
"         <name>GetCurrentConnectionInfo</name> \n"
"          <argumentList> \n"
"             <argument> \n"
"                <name>ConnectionID</name> \n"
"                <direction>in</direction> \n"
"                <relatedStateVariable>A_ARG_TYPE_ConnectionID</relatedStateVariable> \n"
"             </argument> \n"
"             <argument> \n"
"                <name>RcsID</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>A_ARG_TYPE_RcsID</relatedStateVariable> \n"
"             </argument> \n"
"             <argument> \n"
"                <name>AVTransportID</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>A_ARG_TYPE_AVTransportID</relatedStateVariable> \n"
"             </argument> \n"
"             <argument> \n"
"                <name>ProtocolInfo</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>A_ARG_TYPE_ProtocolInfo</relatedStateVariable> \n"
"             </argument> \n"
"             <argument> \n"
"                <name>PeerConnectionManager</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>A_ARG_TYPE_ConnectionManager</relatedStateVariable> \n"
"             </argument> \n"
"             <argument> \n"
"                <name>PeerConnectionID</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>A_ARG_TYPE_ConnectionID</relatedStateVariable> \n"
"             </argument> \n"
"             <argument> \n"
"                <name>Direction</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>A_ARG_TYPE_Direction</relatedStateVariable> \n"
"             </argument> \n"
"             <argument> \n"
"                <name>Status</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>A_ARG_TYPE_ConnectionStatus</relatedStateVariable> \n"
"             </argument> \n"
"          </argumentList> \n"
"       </action> \n"
"       <action> \n"
"          <name>GetProtocolInfo</name> \n"
"          <argumentList> \n"
"             <argument> \n"
"                <name>Source</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>SourceProtocolInfo</relatedStateVariable> \n"
"             </argument> \n"
"             <argument> \n"
"                <name>Sink</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>SinkProtocolInfo</relatedStateVariable> \n"
"             </argument> \n"
"          </argumentList> \n"
"       </action> \n"
"       <action> \n"
"          <name>GetCurrentConnectionIDs</name> \n"
"          <argumentList> \n"
"             <argument> \n"
"                <name>ConnectionIDs</name> \n"
"                <direction>out</direction> \n"
"                <relatedStateVariable>CurrentConnectionIDs</relatedStateVariable> \n"
"             </argument> \n"
"          </argumentList> \n"
"       </action> \n"
"    </actionList> \n"
"    <serviceStateTable> \n"
"       <stateVariable sendEvents=\"no\"> \n"
"          <name>A_ARG_TYPE_ProtocolInfo</name> \n"
"          <dataType>string</dataType> \n"
"       </stateVariable> \n"
"       <stateVariable sendEvents=\"no\"> \n"
"          <name>A_ARG_TYPE_ConnectionStatus</name> \n"
"          <dataType>string</dataType> \n"
"          <allowedValueList> \n"
"             <allowedValue>OK</allowedValue> \n"
"             <allowedValue>ContentFormatMismatch</allowedValue> \n"
"             <allowedValue>InsufficientBandwidth</allowedValue> \n"
"             <allowedValue>UnreliableChannel</allowedValue> \n"
"             <allowedValue>Unknown</allowedValue> \n"
"          </allowedValueList> \n"
"       </stateVariable> \n"
"       <stateVariable sendEvents=\"no\"> \n"
"          <name>A_ARG_TYPE_AVTransportID</name> \n"
"          <dataType>i4</dataType> \n"
"       </stateVariable> \n"
"       <stateVariable sendEvents=\"no\"> \n"
"          <name>A_ARG_TYPE_RcsID</name> \n"
"          <dataType>i4</dataType> \n"
"       </stateVariable> \n"
"       <stateVariable sendEvents=\"no\"> \n"
"          <name>A_ARG_TYPE_ConnectionID</name> \n"
"          <dataType>i4</dataType> \n"
"       </stateVariable> \n"
"       <stateVariable sendEvents=\"no\"> \n"
"          <name>A_ARG_TYPE_ConnectionManager</name> \n"
"          <dataType>string</dataType> \n"
"       </stateVariable> \n"
"       <stateVariable sendEvents=\"yes\"> \n"
"          <name>SourceProtocolInfo</name> \n"
"          <dataType>string</dataType> \n"
"       </stateVariable> \n"
"       <stateVariable sendEvents=\"yes\"> \n"
"          <name>SinkProtocolInfo</name> \n"
"          <dataType>string</dataType> \n"
"       </stateVariable> \n"
"       <stateVariable sendEvents=\"no\"> \n"
"          <name>A_ARG_TYPE_Direction</name> \n"
"          <dataType>string</dataType> \n"
"          <allowedValueList> \n"
"             <allowedValue>Input</allowedValue> \n"
"             <allowedValue>Output</allowedValue> \n"
"          </allowedValueList> \n"
"       </stateVariable> \n"
"       <stateVariable sendEvents=\"yes\"> \n"
"          <name>CurrentConnectionIDs</name> \n"
"          <dataType>string</dataType> \n"
"       </stateVariable> \n"
"    </serviceStateTable> \n"
" </scpd> \n";

const char *ConnectionManager::SERVICE_TYPE = "urn:schemas-upnp-org:service:ConnectionManager:1";		

const char *ConnectionManager::HTTP_GET = "http-get";
	
const char *ConnectionManager::GET_PROTOCOL_INFO = "GetProtocolInfo";
const char *ConnectionManager::SOURCE = "Source";
const char *ConnectionManager::SINK = "Sink";

const char *ConnectionManager::PREPARE_FOR_CONNECTION = "PrepareForConnection";
const char *ConnectionManager::REMOTE_PROTOCOL_INFO= "RemoteProtocolInfo";
const char *ConnectionManager::PEER_CONNECTION_MANAGER = "PeerConnectionManager";
const char *ConnectionManager::PEER_CONNECTION_ID = "PeerConnectionID";
const char *ConnectionManager::DIRECTION = "Direction";
const char *ConnectionManager::CONNECTION_ID = "ConnectionID";
const char *ConnectionManager::AV_TRNSPORT_ID = "AVTransportID";
const char *ConnectionManager::RCS_ID = "RcsID";
	
const char *ConnectionManager::CONNECTION_COMPLETE = "ConnectionComplete";

const char *ConnectionManager::GET_CURRENT_CONNECTION_IDS = "GetCurrentConnectionIDs";
const char *ConnectionManager::CONNECTION_IDS = "ConnectionIDs";

const char *ConnectionManager::GET_CURRENT_CONNECTION_INFO = "GetCurrentConnectionInfo";
const char *ConnectionManager::PROTOCOL_INFO= "ProtocolInfo";
const char *ConnectionManager::STATUS = "Status";
const char *ConnectionManager::INPUT = "Input";
const char *ConnectionManager::OUTPUT = "Output";
const char *ConnectionManager::OK = "OK";
	
////////////////////////////////////////////////
// Constructor 
////////////////////////////////////////////////
	
ConnectionManager::ConnectionManager(MediaServer *mserver)
{
	setMediaServer(mserver);
}

ConnectionManager::~ConnectionManager()
{
}
	
////////////////////////////////////////////////
// Media Server
////////////////////////////////////////////////

ContentDirectory *ConnectionManager::getContentDirectory()
{
	return getMediaServer()->getContentDirectory();	
}

////////////////////////////////////////////////
// ConnectionID
////////////////////////////////////////////////
	
int ConnectionManager::getNextConnectionID()
{
	lock();
	maxConnectionID++;
	unlock();
	return maxConnectionID;
}
	
////////////////////////////////////////////////
// ConnectionInfoList
////////////////////////////////////////////////
	
ConnectionInfo *ConnectionManager::getConnectionInfo(int id)
{
	int size = conInfoList.size();
	for (int n=0; n<size; n++) {
		ConnectionInfo *info = conInfoList.getConnectionInfo(n);
		if (info->getID() == id)
			return info;
	}
	return NULL;
}

void ConnectionManager::addConnectionInfo(ConnectionInfo *info)
{
	lock();
	conInfoList.add(info);
	unlock();
}
	
void ConnectionManager::removeConnectionInfo(int id)
{
	lock();
	int size = conInfoList.size();
	for (int n=0; n<size; n++) {
		ConnectionInfo *info = conInfoList.getConnectionInfo(n);
		if (info->getID() == id) {
			conInfoList.remove(info);
			delete info;
			break;
		}
	}
	unlock();
}
	
void ConnectionManager::removeConnectionInfo(ConnectionInfo *info)
{
	lock();
	conInfoList.remove(info);
	unlock();
}

////////////////////////////////////////////////
// ActionListener
////////////////////////////////////////////////

bool ConnectionManager::actionControlReceived(Action *action)
{
	//action->print();
		
	string actionName = action->getName();
	if (actionName.compare(GET_PROTOCOL_INFO) == 0) {
		// Source
		ostringstream sourceValueBuf;
		int mimeTypeCnt = getContentDirectory()->getNFormats();
		for (int n=0; n<mimeTypeCnt; n++) {
			if (0 < n)
				sourceValueBuf << ",";
			Format *format = getContentDirectory()->getFormat(n);
			string mimeType = format->getMimeType();
			sourceValueBuf << HTTP_GET << ":*:" << mimeType << ":*";
		}
		string sourceValue = sourceValueBuf.str();
		action->getArgument(SOURCE)->setValue(sourceValue.c_str());
		// Sink
		action->getArgument(SINK)->setValue("");
		return true;
	}

	if (actionName.compare(PREPARE_FOR_CONNECTION) == 0) {
		action->getArgument(CONNECTION_ID)->setValue(-1);
		action->getArgument(AV_TRNSPORT_ID)->setValue(-1);
		action->getArgument(RCS_ID)->setValue(-1);
		return true;
	}
		
	if (actionName.compare(CONNECTION_COMPLETE) == 0) {
		return true;
	}
		
	if (actionName.compare(GET_CURRENT_CONNECTION_INFO) == 0)
		return getCurrentConnectionInfo(action);
		
	if (actionName.compare(GET_CURRENT_CONNECTION_IDS) == 0)
		return getCurrentConnectionIDs(action);

	return false;
}

////////////////////////////////////////////////
// GetCurrentConnectionIDs
////////////////////////////////////////////////
	
bool ConnectionManager::getCurrentConnectionIDs(Action *action)
{
	ostringstream conIDs;
	lock();
	int size = conInfoList.size();
	for (int n=0; n<size; n++) {
		ConnectionInfo *info = conInfoList.getConnectionInfo(n);
		if (0 < n)
			conIDs << ",";
		conIDs << info->getID();
	}
	action->getArgument(CONNECTION_IDS)->setValue(conIDs.str().c_str());
	unlock();
	return true;
}
	
////////////////////////////////////////////////
// GetCurrentConnectionInfo
////////////////////////////////////////////////
	
bool ConnectionManager::getCurrentConnectionInfo(Action *action)
{
	int id = action->getArgument(RCS_ID)->getIntegerValue();
	lock();
	ConnectionInfo *info = getConnectionInfo(id);
	if (info != NULL) {
		action->getArgument(RCS_ID)->setValue(info->getRcsID());
		action->getArgument(AV_TRNSPORT_ID)->setValue(info->getAVTransportID());
		action->getArgument(PEER_CONNECTION_MANAGER)->setValue(info->getPeerConnectionManager());
		action->getArgument(PEER_CONNECTION_ID)->setValue(info->getPeerConnectionID());
		action->getArgument(DIRECTION)->setValue(info->getDirection());
		action->getArgument(STATUS)->setValue(info->getStatus());
	}
	else {
		action->getArgument(RCS_ID)->setValue(-1);
		action->getArgument(AV_TRNSPORT_ID)->setValue(-1);
		action->getArgument(PEER_CONNECTION_MANAGER)->setValue("");
		action->getArgument(PEER_CONNECTION_ID)->setValue(-1);
		action->getArgument(DIRECTION)->setValue(ConnectionInfo::OUTPUT);
		action->getArgument(STATUS)->setValue(ConnectionInfo::UNKNOWN);
	}
	unlock();
	return true;
}

////////////////////////////////////////////////
// QueryListener
////////////////////////////////////////////////

bool ConnectionManager::queryControlReceived(StateVariable *stateVar)
{
	return false;
}


