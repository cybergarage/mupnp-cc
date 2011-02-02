/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Thread.h
*
*	Revision;
*
*	04/02/03
*		- first revision
*
******************************************************************/

#ifndef _CUTIL_THREAD_H_
#define _CUTIL_THREAD_H_

#if defined(WIN32) && !defined(ITRON)
#include <windows.h>
#elif defined(BTRON)
#include <btron/proctask.h>
#elif defined(ITRON)
#if defined(WIN32) && defined(ITRON) && defined (_AFXDLL)
#include <afxwin.h>
#endif
#include <kernel.h>
#elif defined(TENGINE) && !defined(PROCESS_BASE)
#include <tk/tkernel.h>
#elif defined(TENGINE) && defined(PROCESS_BASE)
#include <btron/proctask.h>
#else
#include <pthread.h>
#endif

namespace CyberUtil {

class Thread
{
#if defined(WIN32) && !defined(ITRON)
	HANDLE	hThread;
	DWORD	threadID;
#elif defined(BTRON)
	W taskID;
#elif defined(ITRON)
	ER_ID	taskID;
#elif defined(TENGINE) && !defined(PROCESS_BASE)
	ID taskID;
#elif defined(TENGINE) && defined(PROCESS_BASE)
	WERR taskID;
#else
	pthread_t thread;
#endif
	bool runnableFlag;

private:

	void setRunnableFlag(bool flag);

public:

	Thread();
	virtual ~Thread();

	virtual bool start();
	virtual void run() = 0;
	bool isRunnable();
	virtual bool stop();

	bool restart()
	{
		stop();
		start();
		return true;
	}
};

}

#endif
