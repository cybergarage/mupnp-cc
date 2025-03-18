/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File : TimeUtil.h
*
*	Revision;
*
*	04/04/03
*		- first revision
*
******************************************************************/

#ifndef _CUTIL_TIMERUTIL_H_
#define _CUTIL_TIMERUTIL_H_

namespace CyberUtil {

void Wait(long mtime);
void WaitRandom(long mtime);
long GetCurrentSystemTime();
float Random();

}

#endif
