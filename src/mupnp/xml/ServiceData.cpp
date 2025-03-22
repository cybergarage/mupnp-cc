/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/Service.h>
#include <mupnp/xml/ServiceData.h>

using namespace mUPnP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

ServiceData::ServiceData()
{
  service = nullptr;
  scpdNode = mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
}
