<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: MAN.h
*
*	Revision;
*
*	07/08/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_MAN_H_
#define _CLINK_MAN_H_

#include <sstream>

namespace CyberLink {

namespace MAN {

const char DISCOVER[] = "ssdp:discover";
	
bool IsDiscover(const std::string &value);

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
*	File: MAN.h
*
*	Revision;
*
*	07/08/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_MAN_H_
#define _CLINK_MAN_H_

#include <sstream>

namespace CyberLink {

namespace MAN {

const char DISCOVER[] = "ssdp:discover";
	
bool IsDiscover(const char *value);

}

}

#endif

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
