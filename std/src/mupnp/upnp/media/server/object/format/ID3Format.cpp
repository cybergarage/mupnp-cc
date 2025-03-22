/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2002
*
*	File : ID3Format.cpp
*
*	Revision:
*
*	12/03/03
*		- first revision.
*
******************************************************************/

#include <string.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#include <mupnp/io/FileInputStream.h>
#include <mupnp/upnp/media/server/object/item/ItemNode.h>
#include <mupnp/upnp/media/server/object/format/ID3Format.h>

using namespace std;
using namespace CyberIO;
using namespace CyberXML;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *ID3Format::HEADER_ID = "ID3";
const int ID3Format::HEADER_SIZE = 10;
const int ID3Format::EXT_HEADER_SIZE = 4;
const int ID3Format::FRAME_HEADER_SIZE = 10;
const int ID3Format::FRAME_ID_SIZE = 4;

////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////
	
ID3Format::ID3Format()
{
	setFile(NULL);
	header = new unsigned char[HEADER_SIZE];
	extHeader = new unsigned char[EXT_HEADER_SIZE];
	frameHeader = new unsigned char[FRAME_HEADER_SIZE];
}
	
ID3Format::ID3Format(CyberIO::File *file)
{
	setFile(file);
	header = new unsigned char[HEADER_SIZE];
	extHeader = new unsigned char[EXT_HEADER_SIZE];
	frameHeader = new unsigned char[FRAME_HEADER_SIZE];
	loadHeader(file);
}

ID3Format::~ID3Format()
{
	delete []header;
	delete []extHeader;
	delete []frameHeader;
}

////////////////////////////////////////////////
// loadHeader
////////////////////////////////////////////////

bool ID3Format::loadHeader(CyberIO::InputStream *in)
{
	// Reading a main header
	in->read(header, HEADER_SIZE);

	// Reading a extended header
	if (hasExtendedHeader() == true) {
		in->read(extHeader, EXT_HEADER_SIZE);
		int extHeaderSize = getExtHeaderSize();
		// Ignoring extended header infos
		int extHeaderLen = extHeaderSize-EXT_HEADER_SIZE;
		char c;
		for (int n=0; n<extHeaderLen; n++)
			in->read(&c, 1);
	}

	// Reading frame infos
	frameList.clear();
	int frameDataSize = getHeaderSize() - HEADER_SIZE;
	if (hasExtendedHeader() == true)
		frameDataSize -= getExtHeaderSize();
	int frameDataCnt = 0;
	while (frameDataCnt < frameDataSize) {
		in->read(frameHeader, FRAME_HEADER_SIZE);
		string frameID;
		getFrameID(frameHeader, frameID);
		int frameSize = getFrameSize(frameHeader);
		int frameFlag = getFrameFlag(frameHeader);
		unsigned char *frameData = new unsigned char[frameSize];
		in->read(frameData, frameSize);
		ID3Frame *frame = new ID3Frame();
		frame->setID(frameID.c_str());
		frame->setSize(frameSize);
		frame->setFlag(frameFlag);
		frame->setData(frameData, frameSize);
		frameList.add(frame);
		frameDataCnt += frameSize + FRAME_HEADER_SIZE;
		delete frameData;
	}

	in->close();

	return true;
}
	
bool ID3Format::loadHeader(CyberIO::File *file)
{
	FileInputStream *fin = new FileInputStream(file, File::O_BINARY);
	bool ret = loadHeader(fin);
	delete fin;
	return ret;
}

int ID3Format::getHeaderSize()
{
	int size = 0;
	for (int n=0; n<4; n++)
		size += (header[9-n] & 0xFF ) << n;		
	return size;
}

////////////////////////////////////////////////
// Extended Header
////////////////////////////////////////////////
	
int ID3Format::getExtHeaderSize()
{
	int size = 0;
	for (int n=0; n<4; n++)
		size += (extHeader[3-n] & 0xFF ) << n;		
	return size;
}


////////////////////////////////////////////////
// Header
////////////////////////////////////////////////
	
const char *ID3Format::getFrameID(unsigned char *frameHeader, std::string &buf)
{
	char *frameID = new char[FRAME_ID_SIZE+1];
	memcpy(frameID, frameHeader, FRAME_ID_SIZE);
	frameID[FRAME_ID_SIZE] = '\0';
	buf = frameID;
	delete []frameID;
	return buf.c_str();
}

int ID3Format::getFrameSize(unsigned char *frameHeader)
{
	int size = 0;
	for (int n=0; n<4; n++)
		size += (frameHeader[7-n] & 0xFF ) << n;		
	return size;
}

int ID3Format::getFrameFlag(unsigned char *frameHeader)
{
	return ((frameHeader[8] & 0xFF) << 8) + (frameHeader[9] & 0xFF);		
}

////////////////////////////////////////////////
// Abstract Methods
////////////////////////////////////////////////

bool ID3Format::equals(CyberIO::File *file)
{
	if (file == NULL)
		return false;

	const char *filename = file->getName();
	if (filename == NULL)
		return false;

	FILE *fp = fopen(filename, "rb");
	if (!fp)	
		return false;
	unsigned char signature[5];
	if (fread(signature, 5, 1, fp) != 1) {
		fclose(fp);
		return false;
	}
	fclose(fp);

	if (!strncmp(HEADER_ID, (char *)signature, 3))
		return true;

	return false;
}

////////////////////////////////////////////////
// Abstract Methods
////////////////////////////////////////////////

int ID3Format::getAttributeList(CyberXML::AttributeList &attrList)
{
	File *file = getFile();
	if (file == NULL)
		return attrList.size();

	ostringstream os;
	os << file->length();
	Attribute *sizeStr = new Attribute(ItemNode::SIZE, os.str().c_str());
	attrList.add(sizeStr);

	return attrList.size();
}

const char *ID3Format::getTitle(std::string &title)
{
	getFrameStringData(ID3Frame::TIT2, title);
	if (0 < title.length())
		return title.c_str();
	getFrameStringData(ID3Frame::TIT1, title);
	if (0 < title.length())
		return title.c_str();
	return getFrameStringData(ID3Frame::TIT2, title);
}

const char *ID3Format::getCreator(std::string &creator)
{
	getFrameStringData(ID3Frame::TPE1, creator);
	if (0 < creator.length())
		return creator.c_str();
	getFrameStringData(ID3Frame::TPE2, creator);
	if (0 < creator.length())
		return creator.c_str();
	getFrameStringData(ID3Frame::TPE3, creator);
	if (0 < creator.length())
		return creator.c_str();
	return getFrameStringData(ID3Frame::TPE4, creator);
}

////////////////////////////////////////////////
// print
////////////////////////////////////////////////

void ID3Format::print()
{
/*
  String headerStr = new String(header);
	System.out.println("header = " + headerStr);
	System.out.println("ID = " + getHeaderID());
	System.out.println("Size = " + getHeaderSize());
	System.out.println("isUnsynchronisation = " + isUnsynchronisation());
	System.out.println("hasExtendedHeader = " + hasExtendedHeader());
	System.out.println("isExperimental = " + isExperimental());
	System.out.println("hasFooter = " + hasFooter());
	int frameCnt = frameList.size();
	for (int n=0; n<frameCnt; n++) {
		ID3Frame frame = frameList.getFrame(n);
		System.out.println("[" + n + "] : " + frame.getID());
		System.out.println("     " + frame.getData());
	}
*/
}
