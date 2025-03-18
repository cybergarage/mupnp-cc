/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Mutex.h
*
*	Revision;
*
*	08/14/03
*		- first revision
*
******************************************************************/

#ifndef _CUTIL_MUTEX_H_
#define _CUTIL_MUTEX_H_

#if defined(WIN32) && defined(ITRON) && defined (_AFXDLL)
#include <afxwin.h>
#endif

#if defined(WIN32) && !defined(ITRON)
#include <winsock2.h>
#elif defined(BTRON)
#include <btron/taskcomm.h>
#elif defined(ITRON)
#include <kernel.h>
#elif defined(TENGINE) && !defined(PROCESS_BASE)
#include <tk/tkernel.h>
#elif defined(TENGINE) && defined(PROCESS_BASE)
#include <btron/taskcomm.h>
#else
#include <pthread.h>
#endif

namespace CyberUtil {

class Mutex
{

#if defined(WIN32) && !defined(ITRON)
	HANDLE	mutexID;
#elif defined(BTRON)
	WERR	mutexID;
#elif defined(ITRON)
	ER_ID	mutexID;
#elif defined(TENGINE) && !defined(PROCESS_BASE)
	ID mutexID;
#elif defined(TENGINE) && defined(PROCESS_BASE)
	WERR	mutexID;
#else
	pthread_mutex_t mutexID;
#endif

public:

	Mutex();
	~Mutex();

	bool lock();
	bool unlock();
};

}

#endif
