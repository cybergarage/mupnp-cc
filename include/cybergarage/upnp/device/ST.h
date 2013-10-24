<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ST.h
*
*	Revision;
*
*	07/08/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_ST_H_
#define _CLINK_ST_H_

#include <sstream>

namespace CyberLink {

namespace ST {

const char ALL_DEVICE[] = "ssdp:all";
const char ROOT_DEVICE[] = "upnp:rootdevice";
const char UUID_DEVICE[] = "uuid";
const char URN_DEVICE[] = "urn:schemas-upnp-org:device:";
const char URN_SERVICE[] = "urn:schemas-upnp-org:service:";

bool IsAllDevice(const std::string &value);
bool IsRootDevice(const std::string &value);
bool IsUUIDDevice(const std::string &value);
bool IsURNDevice(const std::string &value);
bool IsURNService(const std::string &value);

}

}

#endif


=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ST.h
*
*	Revision;
*
*	07/08/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_ST_H_
#define _CLINK_ST_H_

#include <sstream>

namespace CyberLink {

namespace ST {

const char ALL_DEVICE[] = "ssdp:all";
const char ROOT_DEVICE[] = "upnp:rootdevice";
const char UUID_DEVICE[] = "uuid";
const char URN_DEVICE[] = "urn:schemas-upnp-org:device:";
const char URN_SERVICE[] = "urn:schemas-upnp-org:service:";

bool IsAllDevice(const char *value);
bool IsRootDevice(const char *value);
bool IsUUIDDevice(const char *value);
bool IsURNDevice(const char *value);
bool IsURNService(const char *value);

}

}

#endif


>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
