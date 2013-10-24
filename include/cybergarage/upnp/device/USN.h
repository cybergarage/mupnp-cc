<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: USN.h
*
*	Revision;
*
*	07/07/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_USN_H_
#define _CLINK_USN_H_

#include <string>

namespace CyberLink {

namespace USN {

const char ROOTDEVICE[] = "upnp:rootdevice";
	
bool IsRootDevice(const std::string &usnValue);
const char *GetUDN(const std::string &usnValue, std::string &udn);

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
*	File: USN.h
*
*	Revision;
*
*	07/07/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_USN_H_
#define _CLINK_USN_H_

#include <string>

namespace CyberLink {

namespace USN {

const char ROOTDEVICE[] = "upnp:rootdevice";
	
bool IsRootDevice(const char *usnValue);
const char *GetUDN(const char *usnValue, std::string &udn);

}

}

#endif


>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
