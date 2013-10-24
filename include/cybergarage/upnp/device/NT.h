<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: NT.h
*
*	Revision;
*
*	07/07/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_NT_H_
#define _CLINK_NT_H_

#include <string>

namespace CyberLink {

namespace NT {

const char ROOTDEVICE[] = "upnp:rootdevice";
const char EVENT[] = "upnp:event";
	
bool IsRootDevice(const std::string &usnValue);

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
*	File: NT.h
*
*	Revision;
*
*	07/07/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_NT_H_
#define _CLINK_NT_H_

namespace CyberLink {

namespace NT {

const char ROOTDEVICE[] = "upnp:rootdevice";
const char EVENT[] = "upnp:event";
	
bool IsRootDevice(const char *usnValue);

}

}

#endif

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
