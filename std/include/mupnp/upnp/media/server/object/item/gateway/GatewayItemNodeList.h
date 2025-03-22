/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2003
 **
 *	File: GatewayItemNodeList.h
 *
 *	Revision;
 *
 *	11/15/05
 *		- first revision.
 *
 ******************************************************************/

#ifndef _CLINK_MEDIA_GATEWAYITEMNODELIST_H_
#define _CLINK_MEDIA_GATEWAYITEMNODELIST_H_

#include <mupnp/upnp/media/server/object/item/gateway/GatewayItemNode.h>
#include <mupnp/util/Vector.h>

namespace CyberLink {

class GatewayItemNodeList : public CyberUtil::Vector {
  ////////////////////////////////////////////////
  //	Constructor
  ////////////////////////////////////////////////

  public:
  GatewayItemNodeList()
  {
  }

  ~GatewayItemNodeList()
  {
    clear();
  }

  ////////////////////////////////////////////////
  //	Methods
  ////////////////////////////////////////////////

  public:
  GatewayItemNode* getGatewayItemNode(int n)
  {
    return (GatewayItemNode*)Vector::get(n);
  }

  ////////////////////////////////////////////////
  //	clear
  ////////////////////////////////////////////////

  public:
  void clear();
};

}

#endif
