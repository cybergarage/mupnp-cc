/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: MediaGateMain.cpp
*
*	Revision;
*
*	06/09/04
*		- first revision
*
******************************************************************/

#include <string.h>
#include <string>
#include <iostream>

#include "MediaGate.h"
#include <cybergarage/util/Debug.h>


#include <stdio.h>
#include <stdio.h>
#if defined(WIN32) && !defined(__CYGWIN__)
#include <conio.h>
#else
#include <ctype.h>
#endif

#if !defined(WIN32) || defined(__CYGWIN__)
#include "InputUtil.h"
#endif

using namespace std;
using namespace CyberLink;
using namespace CyberXML;
using namespace CyberUtil;

static const char *VERBOSE_ARG = "-v";

MediaGate *gMediaGate;

/////////////////////////////////////////////////////////////////////////////////
// PrintMessage
/////////////////////////////////////////////////////////////////////////////////

void PrintMessage(const char *msg)
{
	cout << msg << endl;
}

void PrintKeyMessage()
{
	cout << "'p' : Print" << endl;
	cout << "'q' : Quit" << endl;
}

/////////////////////////////////////////////////////////////////////////////////
//  InitApp
/////////////////////////////////////////////////////////////////////////////////

void InitApp(int argc, char* argv[])
{
	int option = MediaGate::FILESYS_MODE;
	int n;

	for (n=1; n<argc; n++) {
#ifdef SUPPORT_MYTHTV
		if (strcmp(MediaGate::MYTHTV_OPT_STRING, argv[n]) == 0)
			mode = MediaGate::MYTHTV_MODE;
		if (strcmp(MediaGate::MYTHTV_OPT_STRING_OLD, argv[n]) == 0)
			mode = MediaGate::MYTHTV_MODE;
#endif
		if (strcmp(VERBOSE_ARG, argv[n]) == 0)
			Debug::on();
	}

	gMediaGate = new MediaGate(option);

	int mode = gMediaGate->getModeOption();
	if (mode == MediaGate::FILESYS_MODE) {
		string prefFileName = MediaGate::DEFAULT_PREFERENCE_FILENAME;
		if (1 < argc)
			prefFileName = argv[argc-1];
		cout << "preference : " << prefFileName << endl;
		bool ret = gMediaGate->loadPreferences(prefFileName.c_str());
		if (ret == false)
			cout << "Couldn't load " << prefFileName << endl;
	}

	cout << "mode : " << (mode == MediaGate::FILESYS_MODE ? "FileSystem" : "MythTV") << endl;
	cout << "verbose : " << (Debug::isOn() ? "yes" : "no") << endl;

	gMediaGate->start();
}

void ExitApp()
{
	gMediaGate->stop();
	delete gMediaGate;
}

/////////////////////////////////////////////////////////////////////////////////
// main
/////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	cout << "Cyber Media Gate " << endl;
	cout << "version : " << MediaGate::VER << endl;

	InitApp(argc, argv);

	PrintKeyMessage();

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
		switch (ch) {
		case 'P':
			gMediaGate->print();
			break;
		case 'Q':
			break;
		default :
			PrintKeyMessage();
		}
	} while( ch != 'Q');

#if !defined(WIN32) || defined(__CYGWIN__)
	kbexit();
#endif

	ExitApp();

	return 0;
}
