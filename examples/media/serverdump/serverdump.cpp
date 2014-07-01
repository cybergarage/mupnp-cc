/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002
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

#include <cybergarage/upnp/media/player/MediaPlayer.h>
#include <cybergarage/upnp/media/server/MediaServer.h>
#include <cybergarage/util/Debug.h>

#include <iostream>

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

/////////////////////////////////////////////////////////////////////////////////
// PrintMessage
/////////////////////////////////////////////////////////////////////////////////

void PrintMessage()
{
	cout << "serverdump" << endl;
	cout << "'p' : Print" << endl;
	cout << "'q' : Quit" << endl;
}

/////////////////////////////////////////////////////////////////////////////////
// PrintContentDirectory
/////////////////////////////////////////////////////////////////////////////////

void PrintContentNode(ContentNode *node, int indentLevel)
{
		int n;
		
		for (n=0; n<indentLevel; n++)
			cout << "  ";
		cout << node->getTitle();
		if (node->isItemNode() == true) {
			ItemNode *itemNode = (ItemNode *)node;
			const char *res = itemNode->getResource();
			const char *protocolInfo = itemNode->getProtocolInfo();
			cout << " (" << res << ")";
		}
		cout << endl;
		
		int nContentNodes = node->getNContentNodes();
		for (n=0; n<nContentNodes; n++) {
			ContentNode *cnode = node->getContentNode(n);
			PrintContentNode(cnode, indentLevel+1);
		}
}

void PrintContentDirectory(MediaPlayer *mplayer, Device *dev)
{
		ContentNode *node = mplayer->getContentDirectory(dev);
		if (node == NULL)
			return;
		//node->print();
		PrintContentNode(node, 1);
		delete node;
}

/////////////////////////////////////////////////////////////////////////////////
// PrintMediaServers
/////////////////////////////////////////////////////////////////////////////////

void PrintMediaServers(MediaPlayer *mplayer)
{
		DeviceList *devList = mplayer->getDeviceList();
		int devCnt = devList->size();
		int mediaServerCnt = 0;
		for (int n=0; n<devCnt; n++) {
			Device *dev = devList->getDevice(n);
			if (dev->isDeviceType(MediaServer::DEVICE_TYPE) == false)
				continue;
			cout << "[" << n <<  "] " << dev->getFriendlyName() << ", " << dev->getLeaseTime() << ", " << dev->getElapsedTime() << endl;
			PrintContentDirectory(mplayer, dev);
			mediaServerCnt++;
		}		
		if (mediaServerCnt == 0) {
			cout << "MediaServer is not found" << endl;
		}
}

/////////////////////////////////////////////////////////////////////////////////
// main
/////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	Debug::on();

	PrintMessage();

	MediaPlayer mplayer;
	mplayer.start();

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
			PrintMediaServers(&mplayer);
	} while( ch != 'Q');

#if !defined(WIN32) || defined(__CYGWIN__)
	kbexit();
#endif

	mplayer.stop();

	return 0;
}
