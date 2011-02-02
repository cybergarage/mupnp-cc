/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Mutex.cpp
*
*	Revision;
*
*	08/14/03
*		- first revision
*	12/16/04
*		- Added support for BTRON
*
******************************************************************/

#include <cybergarage/util/Mutex.h>

using namespace CyberUtil;

////////////////////////////////////////////////
//	Mutex
////////////////////////////////////////////////

Mutex::Mutex()
{
#if defined(WIN32) && !defined(ITRON)
	mutexID = CreateMutex(NULL, FALSE, NULL);
#elif defined(BTRON)
	mutexID = cre_sem(1, SEM_EXCL);
#elif defined(ITRON)
	T_CSEM	csem;
	csem.sematr = TA_TFIFO;
	csem.isemcnt = 1;
	csem.maxsem = 1;
	csem.name = NULL;
	mutexID = acre_sem(&csem);
#elif defined(TENGINE) && !defined(PROCESS_BASE)
	T_CSEM	csem;
	csem.exinf = 0;
	csem.sematr = TA_TFIFO | TA_FIRST;
	csem.isemcnt = 0;
	csem.maxsem = 1;
	mutexID = tk_cre_sem(&csem);
#elif defined(TENGINE) && defined(PROCESS_BASE)
	mutexID = b_cre_sem(1, SEM_EXCL);
#else
	pthread_mutex_init(&mutexID, NULL);
#endif
}

Mutex::~Mutex()
{
#if defined(WIN32) && !defined(ITRON)
	CloseHandle(mutexID);
#elif defined(BTRON)
	del_sem(mutexID);
#elif defined(ITRON)
	del_sem(mutexID);
#elif defined(TENGINE) && !defined(PROCESS_BASE)
	tk_del_sem(mutexID);
#elif defined(TENGINE) && defined(PROCESS_BASE)
	b_del_sem(mutexID);
#else
	pthread_mutex_destroy(&mutexID);
#endif
}

bool Mutex::lock()
{
#if defined(WIN32) && !defined(ITRON)
	WaitForSingleObject(mutexID, INFINITE);
#elif defined(BTRON)
	wai_sem(mutexID, T_FOREVER);
#elif defined(ITRON)
	twai_sem(mutexID, TMO_FEVR);
#elif defined(TENGINE) && !defined(PROCESS_BASE)
	tk_wai_sem(mutexID, 1, TMO_FEVR);
#elif defined(TENGINE) && defined(PROCESS_BASE)
	b_wai_sem(mutexID, T_FOREVER);
#else
	pthread_mutex_lock(&mutexID);
#endif
	return true;
}

bool Mutex::unlock()
{
#if defined(WIN32) && !defined(ITRON)
	ReleaseMutex(mutexID);
#elif defined(BTRON)
	sig_sem(mutexID);
#elif defined(ITRON)
	sig_sem(mutexID);
#elif defined(TENGINE) && !defined(PROCESS_BASE)
	tk_sig_sem(mutexID, 1);
#elif defined(TENGINE) && defined(PROCESS_BASE)
	b_sig_sem(mutexID);
#else
	pthread_mutex_unlock(&mutexID);
#endif
	return true;
}
