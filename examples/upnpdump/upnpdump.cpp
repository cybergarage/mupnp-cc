/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: upnpdump.cpp
*
*	Revision;
*
*	08/10/03
*		- first revision
*	03/25/04
*		- Added print().
*
******************************************************************/

#include "CtrlPoint.h"
#if !defined(WIN32) || defined(__CYGWIN__)
#include "InputUtil.h"
#endif

#include <iostream>

#include <stdio.h>
#include <stdio.h>
#if defined(WIN32) && !defined(__CYGWIN__)
#include <conio.h>
#else
#include <ctype.h>
#endif

#include <uhttp/util/Debug.h>

using namespace std;
using namespace uHTTP;

/////////////////////////////////////////////////////////////////////////////////
// main
/////////////////////////////////////////////////////////////////////////////////

void PrintKeyMessage()
{
	cout << "'p' : Print" << endl;
	cout << "'q' : Quit" << endl;
}

#include <cybergarage/xml/XML.h>
using namespace CyberXML;

int main(int argc, char* argv[])
{
	//UPnP::SetEnable(UPnP::USE_ONLY_IPV6_ADDR);

	Debug::on();

	PrintKeyMessage();

	CtrlPoint ctrlPoint;
	ctrlPoint.start();

#if !defined(WIN32) || defined(__CYGWIN__)
	kbinit();
#endif
	int ch;
	do
	{
#if defined(WIN32) && !defined(__CYGWIN__)
		ch = getch();
#else
		ch = getchar();
#endif
		ch = toupper( ch );
		if (ch == 'P')
			ctrlPoint.print();
		else if (ch != 'Q')
			PrintKeyMessage();
	} while( ch != 'Q');

#if !defined(WIN32) || defined(__CYGWIN__)
	kbexit();
#endif

	ctrlPoint.stop();

	return 0;
}
