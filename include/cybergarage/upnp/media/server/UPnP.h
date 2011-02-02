/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File: UPnP.h
*
*	Revision;
*
*	03/14/04
*		- first revision
*
******************************************************************/

#ifndef _CLINK_MEDIA_UPNP_H_
#define _CLINK_MEDIA_UPNP_H_

namespace CyberLink {

namespace UPnP {

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char CLASS[] = "upnp:class";
const char WRITE_STATUS[] = "upnp:writeStatus";
const char STORAGE_MEDIUM[] = "upnp:storageMedium";
const char STORAGE_USED[] = "upnp:storageUsed";

const char OBJECT_ITEM_IMAGEITEM_PHOTO[] = "object.item.imageItem.photo";
const char OBJECT_ITEM_VIDEOITEM_MOVIE[] = "object.item.videoItem.movie";
	
}

}

#endif


