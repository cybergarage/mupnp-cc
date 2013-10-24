/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File : Debug.cpp
*
*	Revision;
*
*	08/16/03
*		- first revision
*	05/19/04
*		- Added message(s,fname) and warning(s,fname);
*
******************************************************************/

#include <cybergarage/util/Debug.h>

using namespace CyberUtil;

bool Debug::enabled = false;
