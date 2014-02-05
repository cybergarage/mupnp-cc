/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ControlRequest.cpp
*
*  Revision;
*
*  08/13/03
*    - first revision
*  09/02/03
*    - Giordano Sassaroli <sassarol@cefriel.it>
*    - Problem : NullpointerException thrown for devices whose description use absolute urls
*    - Error : the presence of a base url is not mandatory, the API code makes the assumption that control and event subscription urls are relative. If the baseUrl is not present, the request host and port should be extracted from the control/subscription url
*    - Description: The method setRequestHost/setService should be changed as follows
*  02/27/04
*    - Tino <firefly@ms60.url.com.tw>
*    - Fixed setRequestHost() to get the host infomation from SSDP packet when 
*      the control URL is not absolute and the URLBase is NULL.
*  03/20/04
*    - Thanks for Thomas Schulz <tsroyale at users.sourceforge.net>
*    - Fixed setRequestHost() for Sony's UPnP stack when the URLBase has the path.
*  05/19/04
*    - Changed the header include order for Cygwin.
*
******************************************************************/

#include <cybergarage/upnp/control/ControlRequest.h>
#include <uhttp/net/URL.h>
#include <uhttp/http/HTTP.h>
#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/Service.h>

using namespace std;
using namespace CyberLink;
using namespace CyberXML;
using namespace uHTTP;

////////////////////////////////////////////////
//  setRequest
////////////////////////////////////////////////

void ControlRequest::setRequestHost(Service *service) {
  string ctrlURL = service->getControlURL();

  // Thanks for Thomas Schulz (2004/03/20)
  string urlBase = service->getRootDevice()->getURLBase();
  if (0 < urlBase.length()){
    URL url(urlBase.c_str());
    string basePath = url.getPath();
    size_t baseLen = basePath.length();
    if (0 < baseLen) {
      if (1 < baseLen || (basePath.at(0) != '/'))
        ctrlURL = basePath + ctrlURL;
    }
  }

  string relativeURL;
  HTTP::GetRelativeURL(ctrlURL, relativeURL);
  setURI(relativeURL);

  std::string reqHostBuf;
  std::string requestHostBuf;
  std::string postURLStr;
    
  // Thanks for Giordano Sassaroli <sassarol@cefriel.it> and Suzan Foster (09/02/03)
  // Thanks for Andre <andre@antiheld.net> (02/18/04)
  if (HTTP::IsAbsoluteURL(ctrlURL.c_str()) == true)
    postURLStr = ctrlURL;
    
  if (postURLStr.length() <= 0)
    postURLStr = service->getRootDevice()->getURLBase();

  // Thanks for Rob van den Boomen <rob.van.den.boomen@philips.com> (02/17/04)
  // Thanks for Tino <firefly@ms60.url.com.tw> (02/27/04)
  if (postURLStr.length() <= 0)
    postURLStr = service->getRootDevice()->getLocation();

  const char *reqHost = HTTP::GetHost(postURLStr.c_str(), reqHostBuf);
  int reqPort = HTTP::GetPort(postURLStr.c_str());
  HTTPRequest::setHost(reqHost, reqPort);
  HTTPRequest::setRequestHost(reqHost);
  HTTPRequest::setRequestPort(reqPort);
}

