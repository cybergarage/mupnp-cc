/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
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
// Constants
////////////////////////////////////////////////

const char *ServiceList::ELEM_NAME = "serviceList";

////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////

 void ServiceList::clear()  {
  size_t nService = size();
  for (size_t n = 0; n < nService; n++) {
    Service *service = getService(n);
    delete service;
  }
  Vector::clear();
}
