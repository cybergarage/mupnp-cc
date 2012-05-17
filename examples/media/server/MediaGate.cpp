/******************************************************************
*
*	MediaGate for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File : MediaServer.h
*
*	04/15/04
*		- first revision.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "MediaGate.h"

#include <uhttp/io/File.h>
#include <uhttp/util/StringUtil.h>
#include <cybergarage/xml/Parser.h>
#include <cybergarage/upnp/media/server/object/format/GIFFormat.h>
#include <cybergarage/upnp/media/server/object/format/JPEGFormat.h>
#include <cybergarage/upnp/media/server/object/format/PNGFormat.h>
#include <cybergarage/upnp/media/server/object/format/ID3Format.h>
#include <cybergarage/upnp/media/server/object/format/MPEGFormat.h>
#include <cybergarage/upnp/media/server/directory/mythtv/MythDirectory.h>

#include <fstream>

using namespace std;
using namespace CyberXML;
using namespace uHTTP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *MediaGate::VER = "1.0";

const int MediaGate::MODE_OPT_MASK = 0x00FF;
const int MediaGate::FILESYS_MODE = 0x0000;
const int MediaGate::MYTHTV_MODE = 0x0001;

const int MediaGate::SUPPORT_OPT_MASK = 0xFF00;
const int MediaGate::FLASH_SUPPORT= 0x0100;

const char *MediaGate::MYTHTV_OPT_STRING_OLD = "-mythtv";
const char *MediaGate::MYTHTV_OPT_STRING = "--mythtv";
const char *MediaGate::FLASH_OPT_STRING = "--flash";

const char *MediaGate::DEFAULT_PREFERENCE_FILENAME = "MediaGate.xml";

const char *MediaGate::PREFERENCE_CYBERGARAGE = "CyberGarage";
const char *MediaGate::PREFERENCE_MEDIASERVER = "MediaServer";
const char *MediaGate::PREFERENCE_CONTENT_DIRECTORY = "ContentDirectory";
const char *MediaGate::PREFERENCE_DIRECTORY_LIST = "DirectoryList";
const char *MediaGate::PREFERENCE_DIRECTORY = "Directory";
const char *MediaGate::PREFERENCE_NAME = "Name";
const char *MediaGate::PREFERENCE_PATH = "Path";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
	
MediaGate::MediaGate(int mode)
{
	//UPnP::SetEnable(UPnP::USE_ONLY_IPV6_ADDR);

	mediaServ = new MediaServer();
	setOption(mode);

	switch (mode){
	case FILESYS_MODE:
		{
			mediaServ->addPlugIn(new ID3Format());
			mediaServ->addPlugIn(new GIFFormat());
			mediaServ->addPlugIn(new JPEGFormat());
			mediaServ->addPlugIn(new PNGFormat());
			mediaServ->addPlugIn(new MPEGFormat());
		}
		break;
	case MYTHTV_MODE:
		{
#ifdef SUPPORT_MYTHTV
			mediaServ->addPlugIn(new DefaultFormat());
			MythDirectory *mythDir = new MythDirectory();
			mediaServ->addContentDirectory(mythDir);
#endif
		}
		break;
	}
}

MediaGate::~MediaGate()
{
	stop();
}

////////////////////////////////////////////////
// Preferences (FileSystem)
////////////////////////////////////////////////

bool MediaGate::loadPreferences(const char *fname)
{
	File file(fname);
	Parser xmlParser;
	Node *rootNode = xmlParser.parse(&file);
	if (rootNode == NULL)
		return false;

	if (rootNode->isName(PREFERENCE_CYBERGARAGE) == false)
		return false;

	Node *msNode = rootNode->getNode(PREFERENCE_MEDIASERVER);
	if (msNode == NULL)
		return false;

	Node *conNode = msNode->getNode(PREFERENCE_CONTENT_DIRECTORY);
	if (conNode == NULL)
		return false;

	Node *dirListNode = conNode->getNode(PREFERENCE_DIRECTORY_LIST);
	if (dirListNode == NULL)
		return false;

	int dirCnt = dirListNode->getNNodes();
	for (int n=0; n<dirCnt; n++) {
		Node *dirNode = dirListNode->getNode(n);
		if (dirNode->isName(PREFERENCE_DIRECTORY) == false)
			continue;
		Node *nameNode = dirNode->getNode(PREFERENCE_NAME);
		Node *pathNode = dirNode->getNode(PREFERENCE_PATH);
		if (nameNode == NULL || pathNode == NULL)
			continue;
		const char *name = nameNode->getValue();
		const char *path = pathNode->getValue();
#ifdef WIN32
		string pathStr = path;
		path = StringReplaceChars(pathStr, "'", "\\");
#endif
		FileDirectory *fileDir = new FileDirectory(name, path);
		getMediaServer()->addContentDirectory(fileDir);
	}

	delete rootNode;

	return true;
}

bool MediaGate::savePreferences(const char *fname)
{
	Node *rootNode = new Node(PREFERENCE_CYBERGARAGE);
	Node *msNode = new Node(PREFERENCE_MEDIASERVER);
	Node *conDirNode = new Node(PREFERENCE_CONTENT_DIRECTORY);
	Node *dirListNode = new Node(PREFERENCE_DIRECTORY_LIST);

	rootNode->addNode(msNode);
	msNode->addNode(conDirNode);
	conDirNode->addNode(dirListNode);

	int dirCnt = getMediaServer()->getNContentDirectories();
	for (int n=0; n<dirCnt; n++) {
		Node *dirNode = new Node(PREFERENCE_DIRECTORY);
		FileDirectory *dir = (FileDirectory *)getMediaServer()->getContentDirectory(n);
		Node *nameNode = new Node(PREFERENCE_NAME);
		nameNode->setValue(dir->getFriendlyName());
		Node *pathNode = new Node(PREFERENCE_PATH);
		pathNode->setValue(dir->getPath());
		dirListNode->addNode(dirNode);
		dirNode->addNode(nameNode);
		dirNode->addNode(pathNode);
	}

	string buf;
	rootNode->toUnicodeString(buf);

	fstream fout(fname, ios::out);
	if (fout.fail())
		return false;
	fout << XML::VERSION_HEADER << endl;
	fout << buf;
	fout.close();

	delete rootNode;

	return true;
}

////////////////////////////////////////////////
// start/stop
////////////////////////////////////////////////

void MediaGate::start()
{
	getMediaServer()->start();
}

void MediaGate::stop()
{
	getMediaServer()->stop();
}

////////////////////////////////////////////////
// print
////////////////////////////////////////////////

void MediaGate::print()
{
	getMediaServer()->getContentDirectory()->print();
}

