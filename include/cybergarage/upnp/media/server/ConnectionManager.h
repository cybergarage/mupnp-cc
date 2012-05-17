/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : ConnectionManager.h
*
*	Revision:
*
*	04/03/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_CONNECTIONMANAGER_H_
#define _CLINK_MEDIA_CONNECTIONMANAGER_H_

#include <cybergarage/upnp/control/ActionListener.h>
#include <cybergarage/upnp/control/QueryListener.h>
#include <cybergarage/upnp/media/server/ConnectionInfoList.h>
#include <uhttp/util/Mutex.h>

namespace CyberLink {

class MediaServer;
class ContentDirectory;

class ConnectionManager : public ActionListener, public QueryListener
{
	MediaServer *mediaServer;
	uHTTP::Mutex mutex;
	int maxConnectionID;
	ConnectionInfoList conInfoList;
	
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////

public:

	static const char *DESCRIPTION;

	static const char *SERVICE_TYPE;

	static const char *HTTP_GET;
	
	static const char *GET_PROTOCOL_INFO;
	static const char *SOURCE;
	static const char *SINK;

	static const char *PREPARE_FOR_CONNECTION;
	static const char *REMOTE_PROTOCOL_INFO;
	static const char *PEER_CONNECTION_MANAGER;
	static const char *PEER_CONNECTION_ID;
	static const char *DIRECTION;
	static const char *CONNECTION_ID;
	static const char *AV_TRNSPORT_ID;
	static const char *RCS_ID;
	
	static const char *CONNECTION_COMPLETE;

	static const char *GET_CURRENT_CONNECTION_IDS;
	static const char *CONNECTION_IDS;

	static const char *GET_CURRENT_CONNECTION_INFO;
	static const char *PROTOCOL_INFO;
	static const char *STATUS;
	static const char *INPUT;
	static const char *OUTPUT;
	static const char *OK;
	
	////////////////////////////////////////////////
	// Constructor 
	////////////////////////////////////////////////
	
public:

	ConnectionManager(MediaServer *mserver);
	
	virtual ~ConnectionManager();
	
	////////////////////////////////////////////////
	// Media Server
	////////////////////////////////////////////////


private:

	void setMediaServer(MediaServer *mserver)
	{
		mediaServer = mserver;	
	}
	
public:

	MediaServer *getMediaServer()
	{
		return mediaServer;	
	}

	ContentDirectory *getContentDirectory();
	
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
	// ConnectionID
	////////////////////////////////////////////////

public:

	int getNextConnectionID();
	
	////////////////////////////////////////////////
	// ConnectionInfoList
	////////////////////////////////////////////////

public:

	ConnectionInfoList *getConnectionInfoList()
	{
		return &conInfoList;
	}
	
	ConnectionInfo *getConnectionInfo(int conId);
	void addConnectionInfo(ConnectionInfo *conInfo);
	void removeConnectionInfo(int conId);
	void removeConnectionInfo(ConnectionInfo *conInfo);
	
	////////////////////////////////////////////////
	// ActionListener
	////////////////////////////////////////////////

public:

	bool actionControlReceived(Action *action);

	////////////////////////////////////////////////
	// GetCurrentConnectionIDs
	////////////////////////////////////////////////
	
private:

	bool getCurrentConnectionIDs(Action *action);
	
	////////////////////////////////////////////////
	// GetCurrentConnectionInfo
	////////////////////////////////////////////////
	
private:

	bool getCurrentConnectionInfo(Action *action);
	
	////////////////////////////////////////////////
	// QueryListener
	////////////////////////////////////////////////

public:

	bool queryControlReceived(StateVariable *stateVar);

};

}

#endif


