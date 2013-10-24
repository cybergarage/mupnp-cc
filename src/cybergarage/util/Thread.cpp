/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Thread.cpp
*
*	Revision;
*
*	04/02/03
*		- first revision
*	06/16/04
*		- Added pthread_detach() to stop() for Unix platform.
*	09/19/04
*		- Changed start() to set the PTHREAD_CREATE_DETACHED attribure on Unix platform.
*
******************************************************************/

#include <cybergarage/util/Thread.h>

#include <stdio.h>

using namespace CyberUtil;

////////////////////////////////////////////////
// Thread Func
////////////////////////////////////////////////

#if defined(WIN32) && !defined(ITRON)
static DWORD WINAPI Win32ThreadProc(LPVOID lpParam)
{
	Thread *thread = (Thread *)lpParam;
	thread->run();
	return 0;
}
#elif defined(BTRON) 
static VOID BTronTaskProc(W param)
{
	Thread *thread = (Thread *)param;
	thread->run();
	ext_tsk();
}
#elif defined(ITRON)
static TASK ITronTaskProc(int param)
{
	T_RTSK rtsk;
	if (ref_tsk(TSK_SELF, &rtsk) != E_OK)
		return;
	Thread *thread = (Thread *)rtsk.exinf;
	thread->run();
	exd_tsk();
}
#elif defined(TENGINE) && !defined(PROCESS_BASE)
static VOID TEngineTaskProc(INT stacd, VP param)
{
	Thread *thread = (Thread *)param;
	thread->run();
	tk_exd_tsk();
}
#elif defined(TENGINE) && defined(PROCESS_BASE)
static VOID TEngineProcessBasedTaskProc(W param)
{
	Thread *thread = (Thread *)param;
	thread->run();
	b_ext_tsk();
}
#else
static void *PosixThreadProc(void *param)
{
	Thread *thread = (Thread *)param;
	thread->run();
	return 0;
}
#endif

////////////////////////////////////////////////
// Thread
////////////////////////////////////////////////

Thread::Thread()
{
	setRunnableFlag(false);
}

bool Thread::start()
{
	setRunnableFlag(true);
#if defined(WIN32) && !defined(ITRON)
	hThread = CreateThread(NULL, 0, Win32ThreadProc, (LPVOID)this, 0, &threadID);
#elif defined(BTRON)
	P_STATE pstate;
	prc_sts(0, &pstate, NULL);
	taskID = cre_tsk(BTronTaskProc, pstate.priority, (W)this);
	if (taskID < 0) {
		setRunnableFlag(false);
		return false;
	}
	if (wup_tsk(taskID) != 0) {
		setRunnableFlag(false);
		return false;
	}
#elif defined(ITRON)
	T_CTSK ctsk = {TA_HLNG,  (VP_INT)this, (FP)ITronTaskProc, 6, 512, NULL, NULL};
	taskID = acre_tsk(&ctsk);
	if (taskID < 0) {
		setRunnableFlag(false);
		return false;
	}
	if (sta_tsk(taskID, 0) != E_OK) {
		setRunnableFlag(false);
		del_tsk(taskID);
		return FALSE;
	}
#elif defined(TENGINE) && !defined(PROCESS_BASE)
	T_CTSK ctsk = {(VP)this, TA_HLNG, TEngineTaskProc,10, 2048};
	taskID = tk_cre_tsk(&ctsk);
	if (taskID < E_OK) {
		setRunnableFlag(false);
		return false;
	}
	if (tk_sta_tsk(taskID, 0) < E_OK) {
		setRunnableFlag(false);
		tk_del_tsk(thread->taskID);
		return false;
	}
#elif defined(TENGINE) && defined(PROCESS_BASE)
	P_STATE pstate;
	b_prc_sts(0, &pstate, NULL);
	taskID = b_cre_tsk(TEngineProcessBasedTaskProc, pstate.priority, (W)this);
	if (taskID < 0) {
		setRunnableFlag(false);
		return false;
	}
#else
	pthread_attr_t thread_attr;
	pthread_attr_init(&thread_attr);
	pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
	if (pthread_create(&thread, &thread_attr, PosixThreadProc, this) != 0) {
		setRunnableFlag(false);
		pthread_attr_destroy(&thread_attr);
	}
	pthread_attr_destroy(&thread_attr);
#endif
	return true;
}

Thread::~Thread()
{
	stop();
}

bool Thread::stop()
{
	if (isRunnable() == true) {
		setRunnableFlag(false);
#if defined(WIN32) && !defined(ITRON)
		TerminateThread(hThread, 0);
		WaitForSingleObject(hThread, INFINITE);
#elif defined(BTRON)
		ter_tsk(taskID);
#elif defined(ITRON)
		ter_tsk(taskID);
		del_tsk(taskID);
#elif defined(TENGINE) && !defined(PROCESS_BASE)
		tk_ter_tsk(taskID);
		tk_del_tsk(taskID);
#elif defined(TENGINE) && defined(PROCESS_BASE)
		b_ter_tsk(taskID);
#else
		pthread_cancel(thread);
		pthread_detach(thread);
#endif
	}
	return true;
}

void Thread::setRunnableFlag(bool flag)
{
	runnableFlag = flag;
}

bool Thread::isRunnable()
{
	return runnableFlag;
}

