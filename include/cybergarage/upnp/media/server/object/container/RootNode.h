/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : RootNode.h
*
*	Revision:
*
*	04/04/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ROOTNODE_H_
#define _CLINK_MEDIA_ROOTNODE_H_

#include <uhttp/util/Mutex.h>
#include <uhttp/util/Thread.h>
#include <cybergarage/upnp/control/ActionListener.h>
#include <cybergarage/upnp/control/QueryListener.h>
#include <cybergarage/upnp/media/server/object/container/ContainerNode.h>

namespace CyberLink {

class RootNode : public ContainerNode
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	RootNode()
	{
		setID(0);
		setParentID(-1);
		setTitle("Root");
	}

};

}

#endif


