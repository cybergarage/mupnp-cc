/******************************************************************
*
*	CyberUPnP for Java
*
*	Copyright (C) Satoshi Konno 2002
*
*	File : TVDevice.java
*
******************************************************************/

#ifndef _CLINK_TVDEVICE_H_
#define _CLINK_TVDEVICE_H_

#include <cybergarage/upnp/CyberLink.h>

using namespace CyberLink;

const char DESCRIPTION_FILE_NAME[] = "description/description.xml";
const char CLOCK_DEVICE_TYPE[] = "urn:schemas-upnp-org:device:clock:1";
const char CLOCK_SERVICE_TYPE[] = "urn:schemas-upnp-org:service:timer:1";
	
const char LIGHT_DEVICE_TYPE[] = "urn:schemas-upnp-org:device:light:1";
const char LIGHT_SERVICE_TYPE[] = "urn:schemas-upnp-org:service:power:1";

const char AIRCON_DEVICE_TYPE[] = "urn:schemas-upnp-org:device:aircon:1";
const char AIRCON_SERVICE_TYPE[] = "urn:schemas-upnp-org:service:temp:1";
	
const char WASHER_DEVICE_TYPE[] = "urn:schemas-upnp-org:device:washer:1";
const char WASHER_SERVICE_TYPE[] = "urn:schemas-upnp-org:service:state:1";

class TVDevice : public ActionListener, public QueryListener, public NotifyListener, public EventListener, public SearchResponseListener
{
	ControlPoint *ctrlPoint;
	Device *tvDev;
public:

	TVDevice();
	virtual ~TVDevice();

	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////

public:

	void update();

	////////////////////////////////////////////////
	//	start/stop
	////////////////////////////////////////////////

public:

	void start();
	void stop();

	////////////////////////////////////////////////
	//	Clock
	////////////////////////////////////////////////


	std::string clockTime; 
	
	const char *getClockTime()
	{
		return clockTime.c_str();	
	}
	
	////////////////////////////////////////////////
	//	Aircon
	////////////////////////////////////////////////

	std::string airconTemp; 
	
	const char *getAirconTempture()
	{
		return airconTemp.c_str();	
	}

	////////////////////////////////////////////////
	//	Device (Common)
	////////////////////////////////////////////////
	
	bool isDevice(SSDPPacket *packet, const char * deviceType);
	Service *getDeviceService(const char * deviceType, const char * serviceType);
	bool subscribeService(SSDPPacket *packet, const char * deviceType, const char * serviceType);

	////////////////////////////////////////////////
	//	SSDP Listener
	////////////////////////////////////////////////
	
	void checkNewDevices(SSDPPacket *packet);
	void checkRemoveDevices(SSDPPacket *packet);

	////////////////////////////////////////////////
	//	Device Listener
	////////////////////////////////////////////////

public:

	bool actionControlReceived(Action *action);
	bool queryControlReceived(StateVariable *stateVar);

	////////////////////////////////////////////////
	//	Listener
	////////////////////////////////////////////////
	
public:

	void deviceNotifyReceived(SSDPPacket *packet);
	void deviceSearchResponseReceived(SSDPPacket *packet);
	void eventNotifyReceived(const std::string &uuid, long seq, const std::string &name, const std::string &value);
};

#endif

