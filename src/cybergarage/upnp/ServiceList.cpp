/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: DeviceList.cpp
*
*  Revision;
*
*  08/13/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/ServiceList.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *ServiceList::ELEM_NAME = "serviceList";

////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////

 void ServiceList::clear()  {
  int nService = size();
  for (int n = 0; n < nService; n++) {
    Service *service = getService(n);
    delete service;
  }
  Vector::clear();
}
