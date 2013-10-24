/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File : MPEGFormat.cpp
*
*	Revision:
*
*	06/08/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/format/MPEGFormat.h>
#include <cybergarage/upnp/media/server/object/item/ItemNode.h>
#include <sstream>

using namespace std;
using namespace CyberIO;
using namespace CyberXML;
using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

MPEGFormat::MPEGFormat()
{
}
	
MPEGFormat::MPEGFormat(CyberIO::File *file)
{
	setFile(file);
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////
	
bool MPEGFormat::equals(CyberIO::File *file)
{
	if (file == NULL)
		return false;

	string ext;
	file->getSuffix(ext);
	if (ext.compare("mpeg") == 0 || ext.compare("mpg") == 0)
		return true;
	return false;
}

////////////////////////////////////////////////
// getAttributeList
////////////////////////////////////////////////

int MPEGFormat::getAttributeList(CyberXML::AttributeList &attrList)
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

