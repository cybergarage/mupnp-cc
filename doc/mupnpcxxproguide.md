# Programming Guide

The programming guide describes how to create your UPnP™ devices and control points using mUPnP for C++. The guide is divided into the following sections.

# 1 Introduction

UPnP™*[^1] architecture is based on open networking to enable discovery and control of networked devices and services, such as media servers and players at home.

UPnP™ architecture is based on many standard protocols, such as GENA, SSDP, SOAP, HTTPU and HTTP. Therefore you have to understand and implement these protocols to create your devices of UPnP™.

mUPnP for C is a development package for UPnP™ developers. The mUPnP controls these protocols automatically, and supports to create your devices and control points quickly.

Please see the following site and documents to know about UPnP™ in more detail.

| Document                                               | URL                                                                       |
|----------------------------------------------------------|---------------------------------------------------------------------------|
| UPnP™ Forum                                            | http://www.upnp.org/                                                      |
| Universal Plug and Play Device Architecture            | http://www.upnp.org/download/UPnPDA10_20000613.htm                        |
| Universal Plug and Play Vendor\'s Implementation Guide | http://www.upnp.org/download/UPnP_Vendor_Implementation_Guide_Jan2001.htm |

# 2 Setup

This section describes how to build and install the mUPnP package.

## 2.1 Package Contents

The mUPnP package has the header files, the source files, the project files to build the package and the some samples. The files are included the following directories.

| File Type     |                         | Directory             |
|---------------|-------------------------|-----------------------|
| Source files  |                         | mupnp/src            |
| Header Files  |                         | mupnp/include        |
| Sample files  |                         | mupnp/sample         |
| Project files | Unix (Automake)         | mupnp                |
|               | WindowsXP (VisualC 6.0) | mupnp/*/win32/vc60  |
|               | T-Engine (GNU)          | mupnp/*/tengine/gnu |
|               | uITRON                  | mupnp/*/itron       |
|               | MacOSX                  | mupnp/*/macosx      |

## 2.2 System Requirements

mUPnP supports the following XML parsers for UPnP SOAP requests. To compile mUPnP, you need to install the following packages on your platform.

| Package               | URL                                 |
|-----------------------|-------------------------------------|
| libxml2               | https://github.com/GNOME/libxml2    |
| Expat                 | https://libexpat.github.io/         |
| Xerces-C++ XML Parser | https://xerces.apache.org/xerces-c/ |

mUPnP uses libxml2 as the default parser, but you can use Expat as the parser by using a compiler option.

### 2.2.1 WindowsXP

On Windows platform, you have to install latest Platform SDK and build on WindowsXP if you can. Please get the SDK and install in your platform.

<table>
<colgroup>
<col style="width: 25%" />
<col style="width: 74%" />
</colgroup>
<thead>
<tr>
<th>Package</th>
<th><blockquote>
<p>URL</p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr>
<td>Platform SDK</td>
<td><blockquote>
<p>http://www.microsoft.com/msdownload/platformsdk/sdkupdate/</p>
</blockquote></td>
</tr>
</tbody>
</table>

### 2.2.2 T-Engine

On T-Engine platform, you have to use the following development kit based on GNU GCC and TCP/IP protocol stack that supports the multicast protocol. The mUPnP uses the multicast protocol to search and announce UPnP devices and you have to use the protocol stack because the old package doesn’t support the multicast protocol.

<table>
<colgroup>
<col style="width: 30%" />
<col style="width: 69%" />
</colgroup>
<thead>
<tr>
<th>Package</th>
<th><blockquote>
<p>URL</p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr>
<td>T-Engine Development Kit</td>
<td><blockquote>
<p>http://www.personal-media.co.jp/te/welcome.html</p>
</blockquote></td>
</tr>
<tr>
<td>KASAGO for T-Engine</td>
<td><blockquote>
<p>http://www.elwsc.co.jp/japanese/products/kasago_tengine.html</p>
</blockquote></td>
</tr>
</tbody>
</table>

The mUPnP supports the following TCP/IP protocol stack for T-Engine too, but the protocol stack doesn’t support the multicast protocol and the functions are not implemented yet.

<table>
<colgroup>
<col style="width: 30%" />
<col style="width: 69%" />
</colgroup>
<thead>
<tr>
<th>Package</th>
<th><blockquote>
<p>URL</p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr>
<td>PMC T-Shell Kit</td>
<td><blockquote>
<p>http://www.personal-media.co.jp/te/welcome.html</p>
</blockquote></td>
</tr>
</tbody>
</table>

On T-Engile, the mUPnP needs the following package as the default XML parser. Please get the parser package and install in your platform.

<table>
<colgroup>
<col style="width: 25%" />
<col style="width: 74%" />
</colgroup>
<thead>
<tr>
<th>Package</th>
<th><blockquote>
<p>URL</p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr>
<td>Expat</td>
<td><blockquote>
<p>http://expat.sourceforge.net/</p>
</blockquote></td>
</tr>
</tbody>
</table>

On MacOSX platform you have to install latest Project Builder and gcc. Please get the tools and install in your platform.

<table>
<colgroup>
<col style="width: 25%" />
<col style="width: 74%" />
</colgroup>
<thead>
<tr>
<th>Package</th>
<th><blockquote>
<p>URL</p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr>
<td>Developer Connection</td>
<td><blockquote>
<p>http://developer.apple.com/tools/macosxtools.html</p>
</blockquote></td>
</tr>
</tbody>
</table>

## 2.3 Building library and samples

#### 2.4.1 Unix

On Unix platforms, you can build the library and samples using the following steps. Use use the –enable-libxml2 option of the configure script instead of the compiler option. to use libxml2.
>
cd mUPnP
>
./boostrap
>
./configure make

### 2.4.2 Windows

The mUPnP has the platform projects for Visual C++ 6.0. Please check the platform directories, mUPnPC/\*/win32/vc60, to use the projects. On WindowsCE, the mUPnP has no the platform projects, but a contributer have been
>
checked to compile the source codes normally.

### 2.4.3 MacOSX

On MacOSX, you can buuld the library and samples using same steps of Unix platform or using Xcode or Project Bulider projects. Please check the platform directories to use the projects, mUPnPC/\*/macx.

### 2.4.4 T-Engine

On T-Engine platforms, you have to set the following compiler options. The mUPnP supports the process based and T-
>
Kernel based program. Use PROCESS_BASE option to compile the process based program. Please see the development manual of your T-Engine development kit.

| Option              | URL                                 |
|---------------------|-------------------------------------|
| TENGINE             | Enable the platform option.         |
| TENGINE_NET_KASAGO  | Enable KASAGO for T-Engine option.. |
| USE_XMLPARSER_EXPAT | Use Expat as the XML parser         |

The mUPnP is compiled using the functions for PMC T-Shell Kit as the TCP/IP protocol stack, but it is no good because the protocol stack doesn’t support the multicast protocol and the functions are not implemented yet.
>
To run applications using the mUPnP, the driver of the TCP/IP protocol stack has to be loaded and the network address has to be determined. Please see the manual of the protocol stack how to set the network interface.
>
You have to set EXPATROOT environment to an installed top directory of Expat on your shell as the following.
>
The source codes of Expat have to be included the “lib” directory.
>
export EXPATROOT=/usr/local/expat-1.95.8
>
I have built the library with T-Engine/SH7727 development kit with KASAGO for T-Engine. Please check the platform directories, mUPnPC/\*/tengine/gnu , for the sample projects. To compile the samples, run configure script in the directory at first. Please see the development manual of your T-Engine development kit if you want to use on other TEngine platforms.

# Device

**3.1 Class Overview**
>
The following static structure diagram is related classes of mUPnP to create your device of UPnP™. The device has some embedded devices and services, and the services have some actions and state variables.
>
<img src="medi/media/image1.png" style="width:6.61667in;height:6.87in" />
>
The above static structure diagram is modified simplify to explain.
>
**3.2 Description**
>
At first, you have to make some description files of your devices and the services when you want to create your
>
UPnP™ device. The URLs in the device description should be relative locations from the directory of the device description file.

<table>
<colgroup>
<col style="width: 30%" />
<col style="width: 69%" />
</colgroup>
<thead>
<tr>
<th rowspan="2"><p>&gt;</p>
<p>&lt;</p>
<p>?xml version="1.0" ?</p>
<p>&lt;</p>
<p>root xmlns="urn:schemas-upnp-org:device-1-0"</p>
<p>&gt;</p>
<p>........</p>
<p>&lt;device&gt;</p>
<p>........</p>
<p>&lt;serviceList&gt;</p>
<p>........</p>
<p>&lt;service&gt;</p>
<p>........</p>
<p>&lt;SCPDURL&gt;</p>
<p><u>/service/name/description.xml</u></p>
<p>&gt;</p>
<p>/SCPDURL</p>
<p>&lt;</p>
<p>&lt;/service&gt;</p>
<p>&lt;/serviceList&gt;</p>
<p>&lt;presentationURL&gt;</p>
<p><u>/presentation.html</u></p>
<p>&lt;</p>
<p>/presentationURL</p>
<p>&gt;</p>
<p>&lt;iconList&gt;</p>
<p>&lt;icon&gt;</p>
<p>........</p>
<p>&lt;url&gt;</p>
<p><u>/icon.gif</u></p>
<p>&lt;</p>
<p>/url</p>
<p>&gt;</p>
<p>&lt;/icon&gt;</p>
<p>&lt;/iconList&gt;</p>
<p>&lt;/device&gt;</p>
<p>&lt;</p>
<p>/root</p>
<p>&gt;</p>
<p>filename : /yourdevice/descripton/descriptoin.xml</p></th>
<th><table>
<colgroup>
<col style="width: 93%" />
<col style="width: 6%" />
</colgroup>
<thead>
<tr>
<th>filename : /yourdevice/descripton/service/name/descriptoin.xml</th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<td colspan="2"><p>&lt;?xml version="1.0"?&gt;</p>
<p>&lt;scpd xmlns="urn:schemas-upnp-org:service-1-0" &gt;</p>
<p>........</p>
<p>&lt;actionList&gt;</p>
<p>........</p>
<p>&lt;action&gt;</p>
<p>........</p>
<p>&lt;/action&gt;</p>
<p>&lt;/actionList&gt; &lt;serviceStateTable&gt;</p>
<p>........</p>
<p>&lt;stateVariable&gt;</p>
<p>........</p>
<p>&lt;/stateVariable&gt;</p>
<p>&lt;/serviceStateTable&gt;</p>
<p>&lt;/scpd&gt;</p></td>
</tr>
</tbody>
</table></th>
</tr>
<tr>
<th rowspan="2"><table>
<colgroup>
<col style="width: 90%" />
<col style="width: 9%" />
</colgroup>
<thead>
<tr>
<th>filename : /yourdevice/presentation.html</th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<td colspan="2"><p>&lt;html&gt;</p>
<p>&lt;head&gt;</p>
<p>........</p>
<p>&lt;/head&gt; &lt;body&gt;</p>
<p>........</p>
<p>&lt;/body&gt;</p>
<p>&lt;/html&gt;</p></td>
</tr>
</tbody>
</table></th>
</tr>
<tr>
<th><table>
<colgroup>
<col style="width: 90%" />
<col style="width: 9%" />
</colgroup>
<thead>
<tr>
<th>filename : /yourdevice/icon.gif</th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<td colspan="2"></td>
</tr>
</tbody>
</table></th>
</tr>
</thead>
<tbody>
</tbody>
</table>

The description of the root device should not have URLBase element because the element is added automatically when the device is created using the description.
>
The service descriptions are required to create a device, but the presentationURL and the iconList are recommended option. Please see UPnP™ specifications about the description format in more detail.
>
**3.3 Initiating**
>
To create a UPnP™ device, create a instance of Device class with the root description file. The created device is a root device, and only root device can be active using Device::start(). The device is announced to the UPnP™
>
network when the device is started. The following shows an example of the initiating device.
>
\#include \<cybergarage/upnp/mUPnP.h\using namespace mUPnP;
>
……
>
const char \*descriptionFileName = "description/description.xml";
>
Try {
>
Device \*upnpDev = new Device(descriptionFileName);
>
……
>
upnpDev-\>start();
>
}
>
catch (InvalidDescriptionException e){
>
const char \*errMsg = e.getMessage();
>
cout \<\< “InvalidDescriptionException = ” \<\< errMsg \<\< endl;
>
}
>
The InvalidDescriptionException is occurred when the description is invalid. Use the getMessage() to know the exception reason in more detail.
>
Alternatively, you can load the descriptions using Device::loadDescription() and Service::loadSCPD() instead of the description files as the following. The loading methods doesn’t occur the exception.
>
const char DEVICE_DESCRIPTION\[\] =
>
"\<?xml version=\\1.0\\ ?\>\n"
>
"\<root xmlns=\\urn:schemas-upnp-org:device-1-0\\\>\n"
>
. . . .
>
"\</root\>";
>
const char SERVICE_DESCRIPTION\[\] =
>
"\<?xml version=\\1.0\\?\>\n"
>
"\<scpd xmlns=\\urn:schemas-upnp-org:service-1-0\\ \>\n"
>
. . . .
>
“\</scpd\>”;
>
Device \*upnpDev = new Device(); bool descSuccess = upnpDev-\>loadDescription(DEVICE_DESCRIPTION); Service \*upnpService = getService("urn:schemas-upnp-org:service:\*\*\*\*:1"); bool scpdSuccess = upnpService-\>loadSCPD(SERVICE_DESCRIPTION\[);
>
The active root device has some server processes, and returns the responses automatically when a control points sends a request to the device. For example, the device has a HTTP server to return the description files when a
>
control point gets the description file. The device searches an available port for the HTTP server automatically on the machine when the device is started.

HTTP

HTTPMU

HTTPU

GENA

SOAP

Device

Control Point

Control

Description

Notify/Search

Event

Search Response

The root device is created with the following default parameters, you can change the parameters using the following methods before the root device is started.

<table>
<colgroup>
<col style="width: 3%" />
<col style="width: 17%" />
<col style="width: 16%" />
<col style="width: 19%" />
<col style="width: 43%" />
</colgroup>
<thead>
<tr>
<th></th>
<th><blockquote>
<p>Parameter</p>
</blockquote></th>
<th>Default</th>
<th><blockquote>
<p>Method</p>
</blockquote></th>
<th>Detail</th>
</tr>
</thead>
<tbody>
<tr>
<td><blockquote>
<p>1</p>
</blockquote></td>
<td><blockquote>
<p>HTTP port</p>
</blockquote></td>
<td>4004</td>
<td><blockquote>
<p>setHTTPPort()</p>
</blockquote></td>
<td>The http server uses the port in the root device.</td>
</tr>
<tr>
<td><blockquote>
<p>2</p>
</blockquote></td>
<td><blockquote>
<p>Description URI</p>
</blockquote></td>
<td>/description.xml</td>
<td><blockquote>
<p>setDescriptionURI()</p>
</blockquote></td>
<td>The description URI of the root device.</td>
</tr>
<tr>
<td><blockquote>
<p>3</p>
</blockquote></td>
<td><blockquote>
<p>Lease time</p>
</blockquote></td>
<td>1800</td>
<td><blockquote>
<p>setLeaseTime()</p>
</blockquote></td>
<td>The lease time of the root device.</td>
</tr>
</tbody>
</table>

## Notify

Your device is announced using Device::start() to the UPnP™ network using a notify message with ssdp::alive automatically when the device is started. When device is stopped using Device::stop(), a notify message is posted with ssdp::byebye. You can announce the notify messages using Device::announce() and Device::byebye().

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr>
<th><p>NOTIFY * HTTP/1.1</p>
<p>HOST: 239.255.255.250:1900</p>
<p>CACHE-CONTROL: max-age = seconds until advertisement expires</p>
<p>LOCATION: URL for UPnP description for root device</p>
<p>NT: search target</p>
<p>NTS: ssdp:alive</p>
<p>SERVER: OS/version UPnP/1.0 product/version</p>
<p>USN: advertisement UUID</p></th>
</tr>
</thead>
<tbody>
</tbody>
</table>

Device dev ....
>
.....

dev.start();

.....

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr>
<th><p>NOTIFY * HTTP/1.1</p>
<p>HOST: 239.255.255.250:1900</p>
<p>NT: search target</p>
<p>NTS: ssdp:byebye</p>
<p>USN: advertisement UUID</p></th>
</tr>
</thead>
<tbody>
</tbody>
</table>

dev.stop();

When a control point sends a search request with M-SEARCH to the UPnP™ network, the active device send the search response to the control point automatically. The device repeats the announcement in the lease time automatically.

## Embedded Devices

The devices may have some embedded devices. Use Device::getDeviceList() to get the embedded device list.
>
The following example outputs friendly names of all embedded devices in the device.
>
void printDevice(Device \*dev)
>
{
>
counst char \*devName = dev-\>getFriendlyName();
>
cout \<\< devName \<\< endl;
>
DeviceList \*childDevList = dev-\>getDeviceList(); int nChildDevs = childDevList-\>size();
>
for (int ｎ =0; ｎ \<nChildDevs; ｎ ++) {
>
Device \*childDev = childDevList -\>getDevice(n); printDevice(childDev);
>
}
>
}
>
......
>
Dev \*rootDev = ....;
>
……
>
DeviceList \*childDevList = rootDev-\>getDeviceList(); int childDevs = childDevList-\>size();
>
for (int n=0; n\< childDevs; n++) {
>
Device \*childDev = rootDevList-\>getDevice(n); printDevice(childDev);
>
}
>
You can find a embedded device by the friendly name or UDN using Device::getDevice(). The following example gets a embedded device by the friendly name.
>
Device \*homeServerDev ....
>
Device \*musicDev = homeServerDev-\>getDevice(“music”);

## Service

Use Device::getServiceList() to access embedded services of the device. The service may has some actions and state variables. Use Service::getActionList() to get the actions, and use Service::getServiceStateTable() to the state variables by the name. The following example outputs the all actions and state variables in a device.
>
Device \*dev ....
>
ServiceList \*serviceList = dev-\>getServiceList(); int serviceCnt = serviceList-\>size();
>
for (int n=0; n\<serviceCnt; n++) {
>
Service \*service = serviceList-\>getService(n); ActionList \*actionList = service-\>getActionList(); int actionCnt = actionList-\>size();
>
for (int i=0; i\<actionCnt; i++) {
>
Action \*action = actionList-\>getAction(i); cout \<\< “action \[“ \<\< i \<\< “\] = “\<\< action-\>getName() \<\< endl;
>
}
>
ServiceStateTable \*stateTable = service-\getServiceStateTable ();
>
int varCnt = stateTable-\>size();
>
for (int i=0; i\<actionCnt; i++) {
>
StateVariable \*stateVar = stateTable-\>getServiceStateVariable(i); cout \<\< “stateVar \[“ \<\< i \<\< “\] = “ \<\< stateVar-\>getName() \<\< endl;
>
}
>
}
>
You can find a service in the device by the service ID using Device::getService(), and you can find an action or state variable in the service by name too. Use Device::getAction() or Service::getAction() to find the action, and use Device::getStateariable() or Service::getStateVariable() to find the state variable. The following example gets a service, a action and a state variable in a device by name.
>
Device \*clockDev ....
>
Service \*timerSev = clockDev-\>getService(“timer”);
>
Action \*getTimeAct = clockDev-\>getAction(“GetTime”);
>
StateVariable \*timeStat = clockDev-\>getStateVariable(“time”);

## Control

To receive action control events from control points, the device needs to implement the ActionListener interface. The listener have to implement a actionControlReceived() that has the action and argument list parameter. The input arguments has the passed values from the control point, set the response values in the output arguments and return true when the request is valid. Otherwise return a false when the request is invalid. UPnPError response is returned to the control point automatically when the returned value is false or the device has no the interface. The UPnPError is INVALID_ACTION as default, but use Action::setSetStatus() to return other UPnP errors.
>
To receive query control events from control points, the device needs to implement the QueryListener interface.
>
The listener have to implement a queryControlReceived() that has the service variable parameter and return a true when the request is valid. Otherwise return a false when the request is invalid. UPnPError response is returned to the control point automatically when the returned value is false or the device has no the interface. The UPnPError is INVALID_ACTION as default, but use ServiceVariable::setSetStatus() to return other UPnP errors.
>
The following sample is a clock device. The device executes two action control requests and a query control request.
>
class ClockDevice : public Device, public ActionListener, public QueryListener
>
{ public:
>
ClockDevice() : Device(“/clock/www/description.xml”)
>
{
>
Action \*setTimeAction = getAction(“SetTime”); setTimeAction-\>setActionListener(this);
>
Action \*getTimeAction = getAction(“GetTime”);
>
getTimeAction-\>setActionListener(this);
>
StateVariable \*timeVar = getStateVariable(“Timer”); timeVar-\>setQueryListener(this);
>
}
>
bool actionControlRecieved(Action \*action)
>
{
>
ArgumentList \*argList = action-\>getArgumentList(); const char \*actionName = action-\>getName();
>
if (strcmp(actionName, "SetTime") == 0 {
>
Argument \*inTime = argList-\>getArgument(“time”); const char \*timeValue = inTime-\>getValue();
>
If (timeValue == NULL \|\| strlen(timeValue) \<= 0) return false;
>
……..
>
Argument \*outResult = argList-\>getArgument(“result”); arg-\>setValue(“TRUE”);
>
return true;
>
}
>
else if (strcmp(actionName, “GetTime”) == 0) {
>
const char \*currTimeStr = …..
>
Argument \*currTimeArg = argList-\>getArgument(“currTime”); currTimeArg-\>setValue(currTimeStrs);
>
return true;
>
}
>
action-\>setStatus(UPnP::INVALID_ACTION, “…..”); return false;
>
}
>
bool queryControlReceived(StatusVariable \*stateVar)
>
{
>
if (strcmp(varName, “Time”) == 0) {
>
cont char \*currTimeStr = ….; stateVar.setValue(currTimeStr); return true;
>
}
>
stateVar-\>setStatus(UPnP::INVALID_VAR, “…..”); return false;
>
}
>
}
>
Use Device::setActionListner() or Service::setActionListnerer() to add a listener into all control actions in a device or a service. Use Device::setQueryListner() or Service::setQueryListner() to add a listener into all query
>
actions in a device or a service. The following sample sets a listener into all actions in a device.
>
class ClockDevice : public Device, public ActionListener, public QueryListener
>
{ public:
>
ClockDevice() : Device(“/clock/www/description.xml”)
>
{
>
setActionListner(this);
>
setQueryListener (this);
>
}
>
bool actionControlRecieved(Action \*action) { ……. }
>
bool queryControlReceived(StateVariable \*stateVar) { ……. }
>
}

## Event

The control point may subscribe some events of the device. You don’t need manage the subscription messages from control points because the device manages the subscription messages automatically. For example, the device adds a control point into the subscriber list when the control point sends a subscription message to the device, or the device removes the control point from the subscriber list when the control point sends a unsubscription message.
>
Use ServiceStateVariable::setValue() when you want to send the state to the subscribers. The event is sent to the subscribers automatically when the state variable is updated using ServiceStateVariable::setValue(). The following example updates a state variable, and the updated state is distributed to the subscribers automatically.
>
Device \*clockDevice = ....
>
StateVariable timeVar = clockDevice-\>getStateVariable("Time"); const char \*timeStr = ..... timeVar-\>setValue(timeStr);

# Control Point

**4.1 Class Overview**
>
The following static structure diagram is related classes of mUPnP to create your control point of UPnP™. The control point has some root devices in the UPnP™ network.
>
<img src="medi/media/image2.png" style="width:6.66667in;height:6.37333in" />
>
**4.2 Initiating**

To create a UPnP™ control point, create a instance of ControlPoint class. Use ControlPoint::start() to active the contol point. The control point multicasts a discovery message searching for all devices to the UPnP™ network

automatically when the control point is active.
>
\#include \<cybergarage/upnp/mUPnP.h\using namespace mUPnP;
>
……
>
ControlPoint \*ctrlPoint = new ControlPoint();
>
……
>
ctrlPoint-\>start();
>
The active control point has some server processes, and returns the responses automatically when other UPnP™ devices send the messages to the control point. For example, the control point has a SSDP server to get M-
>
SEARCH responses, and the control point searches a available port for the SSDP server automatically on the machine when the control point is started.
>
The control point is created with the following default parameters. You can change the parameters using the following methods before the control point is started.

<table>
<colgroup>
<col style="width: 3%" />
<col style="width: 17%" />
<col style="width: 16%" />
<col style="width: 1%" />
<col style="width: 10%" />
<col style="width: 8%" />
<col style="width: 43%" />
</colgroup>
<thead>
<tr>
<th></th>
<th><blockquote>
<p>Parameter</p>
</blockquote></th>
<th><blockquote>
<p>Default</p>
</blockquote></th>
<th colspan="3"><blockquote>
<p>Method</p>
</blockquote></th>
<th><blockquote>
<p>Detail</p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr>
<td><blockquote>
<p>1</p>
</blockquote></td>
<td><blockquote>
<p>HTTP port</p>
</blockquote></td>
<td><blockquote>
<p>8058</p>
</blockquote></td>
<td colspan="3"><blockquote>
<p>setHTTPPort()</p>
</blockquote></td>
<td><blockquote>
<p>The port is used to receive subscription events.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>2</p>
</blockquote></td>
<td><blockquote>
<p>SSDP port</p>
</blockquote></td>
<td><blockquote>
<p>8008</p>
</blockquote></td>
<td colspan="3"><blockquote>
<p>setSSDPPort()</p>
</blockquote></td>
<td><blockquote>
<p>The port is used to receive search responses.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>3</p>
</blockquote></td>
<td><blockquote>
<p>Subscription URI</p>
</blockquote></td>
<td><blockquote>
<p>/eventSub</p>
</blockquote></td>
<td colspan="3"><blockquote>
<p>setEventSubURI()</p>
</blockquote></td>
<td><blockquote>
<p>The URI is used to receive subscription events.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>4</p>
</blockquote></td>
<td><blockquote>
<p>Search Response</p>
</blockquote></td>
<td><blockquote>
<p>3</p>
</blockquote></td>
<td></td>
<td style="text-align: left;">setSerchMx</td>
<td>()</td>
<td><blockquote>
<p>Maximum wait for device searching</p>
</blockquote></td>
</tr>
</tbody>
</table>

**4.3 Notify**
>
The control point receives notify events from devices in the UPnP™ network, and the devices are added or removed form the control point automatically. The expired device is removed from the device list of the control point automatically too. You don’t manage the notify events, but you can receive the event to implement the NotifyListener interface. The following sample receives the notify messages.
>
class MyCtrlPoint : public ControlPoint, public NotifyListener
>
{ public:
>
MyCtrlPoint()
>
{
>
........
>
addNotifyListener(this);
>
start();
>
}
>
void deviceNotifyReceived(SSDPPacket \*ssdpPacket)
>
{ string use, nt, nts, location; const char \*uuid = ssdpPacket.getUSN(usn); const char \*target = ssdpPacket.getNT(nt);
>
const char \*subType = ssdpPacket.getNTS(nts);
>
const char \*where = ssdpPacket.getLocation(location);
>
.......
>
}
>
To know only the added and removed device, you may use the following interface, DeviceChangeListener.
>
class MyCtrlPoint : public ControlPoint, public DeviceChangeListener
>
{ public:
>
MyCtrlPoint()
>
{
>
........
>
addDeviceChangeListener (this); start();
>
}
>
void deviceAdded (Device \*dev)
>
{
>
……..
>
}
>
void deviceRemoved(Device \*dev)
>
{
>
……..
>
}
>
}

## Search

You can update the device lists using ControlPoint::search(). The discovered root devices are added to the control point automatically, and you can receive the response to implement the SearchResponseListener interface. The following sample receives the notify messages.
>
class MyCtrlPoint : public ControlPoint, public SearchResponseListener
>
{ public:
>
MyCtrlPoint()
>
{
>
........
>
addSearchResponseListener(this); start();
>
........
>
search(“upnp:rootdevice”);
>
}
>
void deviceSearchResponseReceived(SSDPPacket \*ssdpPacket)
>
{ string usn, st, location; const char \*uuid = ssdpPacket.getUSN(usn);
>
const char \*target = ssdpPacket.getST(st);
>
const char \*where = ssdpPacket.getLocation(location);
>
........
>
}

## Root Devices

Use ControlPoint::getDeviceList() that returns only root devices to get the discovered device list. The following example outputs friendly names of the root devices.
>
ControlPoint \*ctrlPoint = new ControlPoint();
>
……
>
ctrlPoint-\>start();
>
……
>
DeviceList \*rootDevList = ctrlPoint-\>getDeviceList(); int nRootDevs = rootDevList-\>size();
>
for (int n=0; n\<nRootDevs; n++) {
>
Device \*dev = rootDevList-\>getDevice(n); const char \*devName = dev-\>getFriendlyName(); cout \<\< “\[“ \<\< n \<\< “\] = ” \<\< devName \<\< endl;
>
}
>
You can find a root device by the friendly name, the device type, or the UDN using ControlPoint::getDevice().
>
The following example gets a root device by the friendly name.
>
ControlPoint \*ctrlPoint = new ControlPoint();
>
……
>
ctrlPoint-\>start();
>
……
>
Device \*homeServerDev = ctrlPoint-\>getDevice(“xxxx-home-server”);

## Control

The control point can send action or query control messages to the discovered devices. To send the action control message, use Action::setArgumentValue() and Action::postControlAction (). You should set the action values to the all input arguments, and the output argument values is ignored if you set. The following sample posts a action control request that sets a new time, and output the response result.
>
Device \*clockDev = ....
>
Action \*setTimeAct = clockDev-\>getAction(“SetTime”); char \*newTime = ....
>
setTimeAct-\>setArgumentValue(“time”, newTime); // setTimeAct-\>getArgument(“time”)-\>setValue(newTime);
>
if (setTimeAct-\>postControlAction() == true) {
>
ArgumentList \*outArgList = setTimeAct-\>getOutputArgumentList(); int nOutArgs = outArgList-\>size();
>
for (int n=0; n\<nOutArgs; n++) {
>
Argument \*outArg = outArgList-\>getArgument(n); const char \*name = outArg-\>getName(); const char \*value = outArg-\>getValue();
>
......
>
}
>
} else {
>
UPnPStatus \*err = setTimeAct-\>getUPnPStatus();
>
System.out.println("Error Code = " + err-\>getCode());
>
System.out.println("Error Desc = " + err-\>getDescription());
>
}
>
To send the query control message, use StateVariable::postQueryControl(). The following sample posts a query control request, and output the return value.
>
Device \*clockDev = ....
>
StateVariable \*timeStateVar = clockDev-\>getStateVariable(“time”); if (timeStateVar-\>postQueryControl() == true) { String value = timeStateVar.getValue();
>
......
>
} else {
>
UPnPStatus \*err = timeStateVar-\>getUPnPStatus();
>
System.out.println("Error Code = " + err-\>getCode());
>
System.out.println("Error Desc = " + err-\>getDescription());
>
}
>
Use Argument::getRelatedStateVariable() to get the related StatiVariable of the argument, and use StateVariable:: getAllowedValueRange() or getAllowedValueList() to get the the allowed value range or list.
>
Device \*clockDev = ....
>
Action \*timeAct = clockDev-\>getAction(“SetTime”);
>
Argument \*timeArg = timeAct-\>getArgument(“time”);
>
StataVariable \*stateVar = timeArg-\>getRelatedStateVariable(); if (stateVar != NULL) {
>
if (stateVar-\>hasAllowedValueRange() == true) {
>
AllowedValueRange \*valRange = stateVar-\>getAllowedValueRange();
>
......
>
}
>
if (stateVar-\>hasAllowedValueList() == true) {
>
AllowedValueList \*valList = stateVar-\>getAllowedValueList ();
>
......
>
}
>
}

## Event

The control point can subscribe events of the discovered devices, get the state changes of the services Use
>
ControlPoint::subscribe() and implement the EventListener interface. The listener have to implement a eventNotifyReceived().
>
MyControlPoint : public ControlPoint, public EventListener
>
{ public:
>
MyControlPoint()
>
{
>
.....
>
addEventListener(this);
>
}
>
.....
>
void eventNotifyReceived(const char \*uuid, long seq, const char \*name, const char \*value)
>
{
>
....
>
}
>
}
>
The ControlPoint::subscribe() returns true when the subscription is accepted from the service, and you can get the subscription id and timeout.
>
ControlPoint \*ctrlPoint = .....
>
Device \*clockDev = ctrlPoint-\>getDevice(“xxxx-clock”);
>
Service \*timeService = clockDev-\>getService(“time:1”); bool subRet = ctrlPoint-\>subscribe(timeService);
>
if (subRet == true) {
>
const char \*sid = timeService-\>getSID();
>
long timeout = timeService-\>getTimeout();
>
}

5.  **Networked Media Product Requirements**

The Intel Networked Media Product Requirements (NMPR) is a implementation guidelins for digital networked devices. Please see the following page about NMPR in more detail.

<table>
<colgroup>
<col style="width: 43%" />
<col style="width: 56%" />
</colgroup>
<thead>
<tr>
<th>Home</th>
<th><blockquote>
<p>URL</p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr>
<td>Intel Develper Network for Digital Home</td>
<td><blockquote>
<p>http://www.intel.com/technology/dhdevnet/</p>
</blockquote></td>
</tr>
</tbody>
</table>

1.  **NMPR Mode**

<table style="width:100%;">
<colgroup>
<col style="width: 35%" />
<col style="width: 8%" />
<col style="width: 8%" />
<col style="width: 8%" />
<col style="width: 7%" />
<col style="width: 30%" />
</colgroup>
<thead>
<tr>
<th><blockquote>
<p>UPnP Technology Requirements</p>
</blockquote></th>
<th style="text-align: center;"><blockquote>
<p>M/S/O</p>
</blockquote></th>
<th style="text-align: center;"><blockquote>
<p>Support</p>
</blockquote></th>
<th style="text-align: center;"><blockquote>
<p>Default</p>
</blockquote></th>
<th style="text-align: center;"><blockquote>
<p>NMPR</p>
</blockquote></th>
<th style="text-align: left;">Detail</th>
</tr>
</thead>
<tbody>
<tr>
<td><blockquote>
<p>&lt;Device Discovery and Control&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: left;">The NMPR tag is added automatically when the NMPR mode is true.</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP iNMPR’03 Description Tag&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: left;"></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Discovery Flood Control&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: left;"></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP SSDP Default Port&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: left;"></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Device Advertisement Frequency&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: left;">Use Device::setWirelessMode() too.</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Discovery over Wireless&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: left;">T h e s u b s c r i p t i o n i s u p d a t e automatically when the NMPR mode is true.</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Device Sync Rules&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: left;">Depend on your platform and device implemenation.</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Auto-IP Support&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: left;">Not support to the dynamic changes in network configuration.</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Device Reset&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;">N</td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: left;">The inavtivity connection close and HTTP HEAD request are not supported yet.</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP HTTP Support and General Rules&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;">N</td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: left;"></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP HTTP1.0 Rules&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: left;">Only HTTP1.0 is supported.</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP HTTP 1.1 Rules&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;">N</td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: left;">The HTTP pipelining is not supported yet.</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP HTTP Pipelining General Rules&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;">N</td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: left;"></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Unknown Tag/Field Decoding&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: left;"></td>
</tr>
</tbody>
</table>

The NMPR features are include Device and ControlPoint class of the mUPnP, but the features are not available as default. Please use Device::setNMPRMode() and ControlPoint::setNMPRMode() as the following.
>
ControlPoint \*ctrlPoint = ..... ctrlPoint-\>setNMPRMode(true); ctrlPoint-\>start();
>
Device \*device = … device-\>setNMPRMode(true);
>
device-\>setWirelessMode(true); // if your device is on wireless network. device-\>start().;

2.  **Implementaion Status**

<table>
<colgroup>
<col style="width: 35%" />
<col style="width: 8%" />
<col style="width: 8%" />
<col style="width: 8%" />
<col style="width: 7%" />
<col style="width: 15%" />
<col style="width: 15%" />
</colgroup>
<thead>
<tr>
<th><blockquote>
<p>&lt;UPnP Error Codes&gt;</p>
</blockquote></th>
<th style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></th>
<th style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></th>
<th style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></th>
<th style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></th>
<th colspan="2"><blockquote>
<p>D e p e n d o n y o u r d e v i c e implementation.</p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr>
<td><blockquote>
<p>&lt;UPnP Device Responsiveness&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td colspan="2"><blockquote>
<p>D e p e n d o n y o u r d e v i c e implementation.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP SOAP Packet Size&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>S</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td colspan="2"><blockquote>
<p>There is no limitation for the embedded devices.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Embedded Device Support&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>N</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td colspan="2"></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Multi-Homing Rules&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td colspan="2" style="text-align: left;"><blockquote>
<p>D e p e n d o n y o u r d e v i c e implementation. The UPnP errors are returned automatically when the services are defined and not implemented.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Service Descriptions Rules&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td></td>
<td></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Subscription Handling&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td></td>
<td></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Event Notification Handling&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td><blockquote>
<p>D e p e n d o n implementation.</p>
</blockquote></td>
<td>y o u r d e v i c e</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Device Icons&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td><blockquote>
<p>D e p e n d o n implementation.</p>
</blockquote></td>
<td>y o u r d e v i c e</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP PNG Icon Recommendations&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td><blockquote>
<p>D e p e n d o n implementation.</p>
</blockquote></td>
<td>y o u r d e v i c e</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Device Icon Support for .ICO&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>S</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td></td>
<td></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP UTF-8 Support&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td></td>
<td></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP XML Comments&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td><blockquote>
<p>D e p e n d o n implementation.</p>
</blockquote></td>
<td>y o u r d e v i c e</td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Boolean Type&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td colspan="2" style="text-align: left;"><blockquote>
<p>D e p e n d o n y o u r d e v i c e implementation. To not implement the</p>
<p>QuaryStateVariable, don't use</p>
<p>Device::setQueryListner.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>&lt; UPnP QueryStateVariable&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>-</p>
</blockquote></td>
<td colspan="2"></td>
</tr>
<tr>
<td><blockquote>
<p>&lt; UPnP Action Arguments Encoding&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td colspan="2" style="text-align: left;"><blockquote>
<p>The BaseURL is removed only when the NMPR mode is true. The service descriptions must be relative in the device description.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP URI Rules&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O/X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td colspan="2" style="text-align: left;"><blockquote>
<p>There is no limitation for he UDN length. To change the device descriptions and the services, create the new device and start it.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP UDN Usage&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td colspan="2" style="text-align: left;"><blockquote>
<p>The control point is not renew the subscriptions automatically.</p>
</blockquote></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Subscription Renewals&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>X</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td colspan="2"></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP Device Handling of Subscription</p>
<p>Renewals&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td colspan="2"></td>
</tr>
<tr>
<td><blockquote>
<p>&lt;UPnP IP Address Rules&gt;</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>M</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>Y</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td style="text-align: center;"><blockquote>
<p>O</p>
</blockquote></td>
<td colspan="2"></td>
</tr>
</tbody>
</table>

**XML Parser**
>
mUPnP supports the following XML parsers to read device descriptions or execute actions of UPnP.

<table>
<colgroup>
<col style="width: 31%" />
<col style="width: 34%" />
<col style="width: 34%" />
</colgroup>
<thead>
<tr>
<th><blockquote>
<p>XML Parser</p>
</blockquote></th>
<th>URL</th>
<th>Compiler Option</th>
</tr>
</thead>
<tbody>
<tr>
<td><blockquote>
<p>Apache Xerces</p>
</blockquote></td>
<td>http://xml.apache.org/xerces-c/</td>
<td></td>
</tr>
<tr>
<td><blockquote>
<p>Expat</p>
</blockquote></td>
<td>http://expat.sourceforge.net/</td>
<td>USE_XMLPARSER_EXPAT</td>
</tr>
<tr>
<td><blockquote>
<p>libxml2</p>
</blockquote></td>
<td>http://xmlsoft.org/</td>
<td style="text-align: left;">USE_XMLPARSER_LIBXML2</td>
</tr>
</tbody>
</table>

mUPnP uses Xerces as the default XML parser. Use the compiler options to your compiler to use Expat or libxml2 instead of the Xerces.
>
On Unix platform, use –enable-expat, or –enable-libxml2 to the configure script instead of the compiler options as the following.
>
./configure --enable-expat
>
**IPv6**
>
mUPnP binds all interfaces in the platform when the devices or control points are created, and the IPv6 sockets are created automatically if the interfaces have IPv6 addresses.
>
mUPnP supports IPv4 and IPv6 both as default. If you want to use only IPv6 interfaces, call the following
>
method before the devices or control points are created.
>
UPnP::SetEnable(UPnP::USE_ONLY_IPV6_ADDR)
>
Link local is the default scope for multicasting of mUPnP. Use UPnP::SetEnable() to change the scope. The following example changes the scope to the site local.
>
UPnP::SetEnable(UPnP::USE_IPV6_SITE_LOCAL_SCOPE)
>
On Unix platform, mUPnP get the local interfaces IPv4 and IPv6 using getifaddrs(). If you want to use mUPnP with IPv6, please check the function supports IPv6 on your platform. I know that the function doesn’t support IPv6 yet on Redhat 9 and MacOSX 10.2.6.
>
**Inside mUPnP**

**8.1 Overriding HTTP Service**

The Device class of mUPnP implements a HTTPRequestListner interface of CyberHTTP package to handle some HTTP requests from the control points. The HTTPRequestListener interface is bellow.
>
class HTTPRequestListener
>
{ public: virtual void httpRequestRecieved(HTTPRequest \*httpReq) = 0;
>
};
>
To overide the interface, use CyberHTTP namespace and override the httpRequestRecieved method in your device that is a sub class of the Device class. The following example is a clock device using mUPnP, and adds
>
the override method to return the presentation page.
>
using namespace CyberHTTP;
>
const char PRESENTATION_URI\[\] = "/presentation";
>
……
>
class ClockDevice : public Device, public ActionListener, public QueryListener
>
{
>
……
>
void httpRequestRecieved(HTTPRequest \*httpReq) { string uri = httpReq-\>getURI();
>
if (uri.find(PRESENTATION_URI) == string::npos) { Device::httpRequestRecieved(httpReq); return;
>
}
>
string clockStr = …….;
>
string contents;
>
contents = "\<HTML\>\<BODY\>\<H1\>"; contents += clockStr;
>
contents += "\</H1\>\</BODY\>\</HTML\>";
>
HTTPResponse httpRes; httpRes.setStatusCode(HTTP::OK_REQUEST); httpRes.setContent(contents); httpReq-\>post(&httpRes);

}

}

9.  **Transitioning From Version 1.2**

**9.1 QueryListner**

mUPnP v1.3 has changed the QueryListner interface to return user error infomation and set the listener to the StateVariable instance instead of the Service instance. The difference is bellow.

<table>
<colgroup>
<col style="width: 11%" />
<col style="width: 88%" />
</colgroup>
<thead>
<tr>
<th>Version</th>
<th><blockquote>
<p>Interface</p>
</blockquote></th>
</tr>
</thead>
<tbody>
<tr>
<td>1.2</td>
<td><blockquote>
<p>bool queryControlReceived(Service *service, const char *varName, std::string &amp;result)</p>
</blockquote></td>
</tr>
<tr>
<td>1.3</td>
<td><blockquote>
<p>bool queryControlReceived(StateVariable *stateVar)</p>
</blockquote></td>
</tr>
</tbody>
</table>

Use StateVariable::getName() to know the variable name, and use StateVariable::setValue() to return the result value. The following sample shows the difference between v1.2 and v1.3.
>
v1.2:
>
bool queryControlReceived(Service \*service, const char \*varName, string &result) { result = Clock::GetCurrentTimeString();
>
return true;
>
}
>
v1.3:
>
bool queryControlReceived(StateVariable \*stateVar) { const char \*varName = stateVar-\>getName();
>
stateVar-\>setValue(Clock::GetCurrentTimeString());
>
return true;
>
}
>
To set the query listener, use StateVariable:: setQueryListener() instead of Service::setQueryListner().
>
However, Service::setQueryListner() that sets the specifed listener to all state variables in the service is not deprecated to ensure the compatibility. The implematation is bellow.
>
void Service::setQueryListener(QueryListener \*listener)
>
{
>
ServiceStateTable \*stateTable = getServiceStateTable(); for (int n=0; n\< stateTable-\>size(); n++)
>
StateVariable \*var = stateTable-\>getStateVariable(n); var-\>setQueryListener(listener);
>
}
>
}

10. **ChangeLog**

<table>
<colgroup>
<col style="width: 90%" />
<col style="width: 9%" />
</colgroup>
<thead>
<tr>
<th><blockquote>
<p>v.1.7</p>
</blockquote></th>
<th>2005-05-29</th>
</tr>
</thead>
<tbody>
<tr>
<td><ul>
<li><p>Changed some headers to compile normally on cygwin and mingw. * Added support for Expat XML parser.</p></li>
<li><p>Added support for HTTP chunked stream to CyberHTTP.</p></li>
<li><p>Fixed StateVariable::setValue() to set blank value when a null value is specified.</p></li>
<li><p>Fixed XML::EscapeXMLChars() to convert from "'" to "&amp;apos;" instead of "\".</p></li>
<li><p>Changed Socket::send() to retry when the packet is not sent normally.</p></li>
<li><p>Changed StateVariable::getAllowedValueList() and AllowedValueList::getAllowedValue() to use AllowedValue instead of std::string as the member.</p></li>
<li><p>Fixed Device::getNotifyDeviceNT() to return the UDN when the device is not root device.</p></li>
<li><p>Changed httpPostRequestRecieved() to return the bad request when the post request isn't the SOAP action.</p></li>
<li><p>Added Device::loadDescription(const char *) to load the description from memory.</p></li>
<li><p>Added Service::loadSCPD() to load the description from memory.</p></li>
<li><p>Added a exclusive access control to Device::getDescriptionData().</p></li>
<li><p>Removed Service::setDescriptionURL() and Service::getDescriptionURL().</p></li>
<li><p>Changed httpGetRequestRecieved() to return the description stream using Device::getDescriptionData() and</p></li>
</ul>
<blockquote>
<p>Service::getSCPDData() at first</p>
</blockquote>
<ul>
<li><p>Changed Thread::start() and stop() to virtual method for overriding in the sub class.</p></li>
<li><p>Changed Device::deviceSearchResponse() answer with USN:UDN::&lt;device-type&gt; when request ST is device type.</p></li>
<li><p>Changed Device::getDescriptionData() and Service::getSCPDData() to add a XML declaration at first line.</p></li>
<li><p>Added a new Device::setActionListener() and serQueryListner() to include the sub devices.</p></li>
<li><p>Changed ActionRequest::getActionName() to return when the delimiter is not found.</p></li>
<li><p>Added support for gcc 4.0.</p></li>
</ul></td>
<td></td>
</tr>
</tbody>
</table>

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr>
<th>v.1.6 2004-11-1</th>
</tr>
</thead>
<tbody>
<tr>
<td><ul>
<li><p>Added support for HTTP v1.1 connection.</p></li>
<li><p>Added support for HEAD and Content-Range headers.</p></li>
<li><p>Fixed ControlPoint::removeExpiredDevices() to remove using the device array.</p></li>
<li><p>Fixed HTTPRequest::getHeader() and getHTTPVersion() no to return "HTTP/HTTP/version"* Added HTTPRequest::isHeadRequest().</p></li>
<li><p>Added HTTPPacket::setContentRange() and getContentRange().</p></li>
<li><p>Changed HTTPRequest::post(HTTPResponse*) not to close the connection.</p></li>
<li><p>Changed HTTPRequest::post(const char *, int) to add a connection header to close.</p></li>
<li><p>Added a isOnlyHeader parameter to HTTPSocket::post().</p></li>
<li><p>Added a updateWithContentLength parameter to HTTPPacket::setContent().</p></li>
<li><p>Changed to HTTPPacket::set() not to change the header of Content-Length.</p></li>
<li><p>Changed HTTPServer::accept() to set a default timeout, HTTP.DEFAULT_TIMEOUT, to the socket.</p></li>
<li><p>Added SocketImp::setTimeout().</p></li>
<li><p>Added HTTPPacket::init() and read().</p></li>
<li><p>Added HTTPRequest::isKeepAlive().</p></li>
<li><p>Added skip() to IntputStream, SocketInputStrean and FileInputStream.</p></li>
<li><p>Added HTTPStatus::isSuccessful() and HTTPRequest::isSuccessfule().</p></li>
<li><p>Added some patches for FreeBSD.</p></li>
<li><p>Removed a SOAP header from DIDLite::output()</p></li>
<li><p>Added support for Range header to HTTPPacket::getContentRange().</p></li>
<li><p>Added a MYNAME header to SSDP messages.</p></li>
<li><p>Changed socket functions to ignore SIGPIPE signal</p></li>
<li><p>Added a fix to HTTPRequest::post() when the last position of Content-Range header is 0.</p></li>
<li><p>Added a Content-Range header to the response in HTTPRequest::post().</p></li>
<li><p>Changed the status code for the Content-Range request in HTTPRequest::post().</p></li>
<li><p>Added to check the range of Content-Range request in HTTPRequest::post().</p></li>
<li><p>Added support the intinite time and fixed a bug in Subscriber::isExpired().</p></li>
<li><p>Fixed a bug when Service::notify() removes the expired devices()* Fixed SSDPPacket::isRootDevice() to check the ST header.</p></li>
<li><p>Added Device::getStateVariable(serviceType, name).</p></li>
<li><p>Changed XML::output() to use short notation when the tag value is null.</p></li>
<li><p>Changed SSDP message to set the TTL as four.</p></li>
<li><p>Changed StateVariable::setValue() to update and send the event when the value is not equal to the current value.</p></li>
</ul></td>
</tr>
</tbody>
</table>

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr>
<th>v.1.5 2004-08-10</th>
</tr>
</thead>
<tbody>
<tr>
<td><ul>
<li><p>Added support for Intel NMPR.</p></li>
<li><p>Added Device::setNMPRMode() and isNMPRMode().</p></li>
<li><p>Changed to advertise every 25%-50% of the periodic notification cycle for NMPR.</p></li>
<li><p>Added Device::setWirelessMode() and isWirelessMode().</p></li>
<li><p>Changed Device::start() to send a bye-bye before the announce for NMPR.</p></li>
<li><p>Changed Device::annouce(), byebye() and deviceSearchReceived() to send the SSDP messsage four times whenthe NMPR and the Wireless mode are true.</p></li>
<li><p>Fixed Device::announce() and byebye() to send the upnp::rootdevice message despite embedded devices.</p></li>
<li><p>Fixed Device::getRootNode() to return the root node when the device is embedded.</p></li>
<li><p>Fixed Service::announce() to set the root device URL to the LOCATION field.</p></li>
<li><p>Added ControlPoint::renewSubscriberService().</p></li>
<li><p>Changed ControlPoint::start() to create renew subscriber thread when the NMPR mode is true.</p></li>
<li><p>Changed Action::postControlAction() to set the status code to the UPnPStatus.* Changed StateVariable::postQuerylAction() to set the status code to the UPnPStatus.</p></li>
<li><p>Added Device::getParentDevice();</p></li>
<li><p>Changed Service::notify() to remove the expired subscribers and not to remove the invalid response subscribersfor NMPR.</p></li>
</ul></td>
</tr>
<tr>
<td>v1.4.1 2004-06-13</td>
</tr>
<tr>
<td><ul>
<li><p>Added a sample for AV MediaServer, CyberMediaGate.</p></li>
<li><p>Changed HTTPRequest::post(HTTPResponse *) to close the socket stream from the server.</p></li>
<li><p>Changed HTTPPacket::getHeader() to compare using string::equals().</p></li>
<li><p>Added I18N support for SORPRequest and SOAPResponse classes.</p></li>
<li><p>Fixed invalide SERVER field of SSDP and HTTP response on Unix Plathome.</p></li>
<li><p>Changed SubscriptionRequest::setServie() to get the host address from the SSDP Location field when the URLBase is null.</p></li>
</ul></td>
</tr>
</tbody>
</table>

<table>
<colgroup>
<col style="width: 90%" />
<col style="width: 9%" />
</colgroup>
<thead>
<tr>
<th><blockquote>
<p>v1.4</p>
</blockquote></th>
<th>2004-05-12</th>
</tr>
</thead>
<tbody>
<tr>
<td><ul>
<li><p>Fixed to set HTTP v1.1 to SSDPRequest and SSDPResponse class.</p></li>
<li><p>Fixed setRequestHost() for Sony's UPnP stack when the URLBase has the path.</p></li>
<li><p>Changed to update the UDN only when the field is null.</p></li>
<li><p>Fixed Service::getDeviceList() to public method.</p></li>
<li><p>Fixed URI::getProtocol() to retuen the name without "://".</p></li>
<li><p>Added some methods for StateVariable to get the AlloedValueList and the AllowedValueRange.</p></li>
<li><p>Changed the upnpdump sample to pring all descovered devices.</p></li>
<li><p>Fixed Praser::parse() to read under the buffer size.</p></li>
<li><p>Fixed Subscription::GetTimeout() to return the valid value.</p></li>
<li><p>Fixed Subscription::toTimeoutHeaderString() to set the valid value instead of the invalid URL value.</p></li>
<li><p>Fixed to initialize members of ActionData such as the action listener and the control response.</p></li>
<li><p>Added start(const char *target, int mx) and start(const char *target) to ControlPoint.</p></li>
<li><p>Added Device::isDeviceType().</p></li>
<li><p>Fixed Argument::initArgumentList() to share a argument node in three Argument when the argument lists are initialized.</p></li>
<li><p>Fixed Argument::getArgument(name) to return the valid pointer.</p></li>
<li><p>Added StateVariable::hasAllowedValueList() and hasAllowedValueRange().</p></li>
</ul></td>
<td></td>
</tr>
<tr>
<td><blockquote>
<p>v1.3.2</p>
</blockquote></td>
<td>2004-03-11</td>
</tr>
<tr>
<td><ul>
<li><p>Fixed a HTTP server bug to return v1.1 instead of v1.0.</p></li>
<li><p>Added a null line to SSDP messages for Intel UPnP tools.</p></li>
<li><p>Added a header of xml version to setConetent() in SOAPRequest and SOPAResponse.</p></li>
<li><p>Changed to use the control URL when it is absolute.</p></li>
<li><p>Changed to get URLBase from the SSDP packet when the URLBase is null and the control URL is not absolute.</p></li>
<li><p>Fixed a interval time of the advertiser on Unix Platform.</p></li>
<li><p>Added Xcode projects on MacOSX.</p></li>
</ul></td>
<td></td>
</tr>
<tr>
<td><blockquote>
<p>v1.3</p>
</blockquote></td>
<td>2004-01-13</td>
</tr>
<tr>
<td><ul>
<li><p>Improved the HTTP server using multithreading.</p></li>
<li><p>Updated a udn field by a generated uuid automatically.</p></li>
<li><p>Added Device::setActionListener() and Device::setQueryListener().</p></li>
<li><p>Added Service::setActionListener().</p></li>
<li><p>Added a Content-Length header to subscription responces.</p></li>
<li><p>Added Action::setAgumentValue(String name, int value).</p></li>
<li><p>Added Agument::setValue(int value).</p></li>
<li><p>Added Action::getAgumentIntegerValue().</p></li>
<li><p>Added Agument::getIntegerValue().</p></li>
<li><p>Added automatic device advertiser</p></li>
<li><p>Added automatic device disposer that remove expired devices from the control point.</p></li>
<li><p>Changed action listener and query listener to return user error messages.</p></li>
</ul></td>
<td></td>
</tr>
<tr>
<td><blockquote>
<p>v1.0</p>
</blockquote></td>
<td>2003-10-02</td>
</tr>
<tr>
<td><blockquote>
<p>The first release.</p>
</blockquote></td>
<td></td>
</tr>
</tbody>
</table>

11. **License**

Copyright (C) 2002-2005 Satoshi Konno All rights reserved.
>
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1.  Redistributions of source code must retain the above copyright notice, this list of conditions and thefollowing disclaimer.

2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and thefollowing disclaimer in the documentation and/or other materials provided with the distribution.

3.  The name of the author may not be used to endorse or promote products derived from this software withoutspecific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR \`\`AS IS'' AND ANY EXPRESS OR IMPLIED
>
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
>
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
>
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
>
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
>
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
>
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
>
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
>
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

[^1]: UPnP™ is a certification mark of the UPnP™ Implementers Corporation.　
