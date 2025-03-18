/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
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

#include <mupnp/util/Debug.h>

using namespace std;
using namespace uHTTP;
using namespace mUPnP;

/////////////////////////////////////////////////////////////////////////////////
// main
/////////////////////////////////////////////////////////////////////////////////

void PrintKeyMessage()
{
	cout << "'p' : Print" << endl;
	cout << "'q' : Quit" << endl;
}

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
