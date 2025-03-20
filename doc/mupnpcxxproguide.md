# Programming Guide

The programming guide describes how to create your UPnP™ devices and control points using mUPnP for C++. The guide is divided into the following sections.

# Introduction

UPnP™*[^1] architecture is based on open networking to enable discovery and control of networked devices and services, such as media servers and players at home.

UPnP™ architecture is based on many standard protocols, such as GENA, SSDP, SOAP, HTTPU and HTTP. Therefore you have to understand and implement these protocols to create your devices of UPnP™.

mUPnP for C++ is a development package for UPnP™ developers. The mUPnP controls these protocols automatically, and supports to create your devices and control points quickly.

Please see the following site and documents to know about UPnP™ in more detail.

| Document                                               | URL                                                                       |
|----------------------------------------------------------|---------------------------------------------------------------------------|
| UPnP™ Forum                                            | http://www.upnp.org/                                                      |
| Universal Plug and Play Device Architecture            | http://www.upnp.org/download/UPnPDA10_20000613.htm                        |
| Universal Plug and Play Vendor\'s Implementation Guide | http://www.upnp.org/download/UPnP_Vendor_Implementation_Guide_Jan2001.htm |

# Setup

This section describes how to build and install the mUPnP package.

## Package Contents

The mUPnP package has the header files, the source files, the project files to build the package and the some samples. The files are included the following directories.

| File Type     |                                  | Directory              |
|---------------|----------------------------------|------------------------|
| Source files  |                                  | mupnp-cc/src           |
| Header Files  |                                  | mupnp-cc/include       |
| Example files |                                  | mupnp-cc/examples      |
| Project files | Unix (Automake)                  | mupnp-cc               |
|               | WindowsXP (Visual C / Sudio)     | mupnp-cc/*/win32/      |
|               | MacOSX (XCode)                   | mupnp-cc/*/macosx      |

## System Requirements

mUPnP supports the following XML parsers for UPnP SOAP requests. To compile mUPnP, you need to install the following packages on your platform.

| Package               | URL                                 |
|-----------------------|-------------------------------------|
| libxml2               | https://github.com/GNOME/libxml2    |
| Expat                 | https://libexpat.github.io/         |
| Xerces-C++ XML Parser | https://xerces.apache.org/xerces-c/ |

mUPnP uses libxml2 as the default XML parser, but you can use Expat as the parser by using a compiler option.

### WindowsXP

On Windows platform, you have to install latest Platform SDK and build on WindowsXP if you can. Please get the SDK and install in your platform.

| Package      | URL                                                        |
|--------------|------------------------------------------------------------|
| Platform SDK | http://www.microsoft.com/msdownload/platformsdk/sdkupdate/ |

## Building library and samples

This sction describes how to build the mUPnP library and samples.

#### Unix

On Unix platforms, you can build the library and samples using the following steps.

```
cd mupnp-cc
./configure
make
```

For more information about configure options, please use `configure --help`.

### Windows

The mUPnP has platform projects for Visual C++ 6.0. Please check the platform directories, `mupnp-cc/*/win32/vc60`, to use the projects. On WindowsCE, mUPnP does not have platform projects, but a contributor has verified that the source code compiles normally.

### MacOSX

On MacOSX, you can build the library and samples using the same steps as the Unix platform or using Xcode or Project Builder projects. Please check the platform directories to use the projects, `mupnp-cc/*/macosx`.

# Device

UPnP™ device is a networked device that supports the UPnP™ architecture. The device has some embedded devices and services, and the services have some actions and state variables. The device is created as a root device, and the root device is active using mUPnP for C. 

This section describes how to create your UPnP™ device using mUPnP for C.

## Class Overview

The following static structure diagram is related classes of mUPnP to create your device of UPnP™. The device has some embedded devices and services, and the services have some actions and state variables.

![](img/device-class-overview.png)

The above static structure diagram is modified simplify to explain.

## Description

At first, you have to make some description files of your devices and the services when you want to create your UPnP™ device..

![](img/device-description.png)

The description of the root device should not have URLBase element because the element is added automatically when the device is created using the description.

The service descriptions are required to create a device, but the presentationURL and the iconList are recommended option. Please see UPnP™ specifications about the description format in more detail.

## Initiating

To create a UPnP™ device, create a instance of Device class with the root description file. The created device is a root device, and only root device can be active using `Device::start()`. The device is announced to the UPnP™ network when the device is started. The following shows an example of the initiating device.

```
#include <cybergarage/upnp/mUPnP.h>
using namespace mUPnP;
....
const char *descriptionFileName = "description/description.xml";
Try {
    Device *upnpDev = new Device(descriptionFileName);
    ....
    upnpDev->start();
}
catch (InvalidDescriptionException e){
    const char *errMsg = e.getMessage();
    cout << “InvalidDescriptionException = ” << errMsg << endl;
}
```

The InvalidDescriptionException is occurred when the description is invalid. Use the getMessage() to know the exception reason in more detail.

Alternatively, you can load the descriptions using Device::loadDescription() and Service::loadSCPD() instead of the description files as the following. The loading methods doesn’t occur the exception.

```
const char DEVICE_DESCRIPTION[] =
    "<?xml version=\"1.0\" ?>\n"
    "<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n"
    ....
    "</root>";

const char SERVICE_DESCRIPTION[] =
    "<?xml version=\"1.0\"?>\n"
    "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\" >\n"
    ....
    “</scpd>”;

Device *upnpDev = new Device();
bool descSuccess = upnpDev->loadDescription(DEVICE_DESCRIPTION);
Service *upnpService = getService("urn:schemas-upnp-org:service-1-0");
bool scpdSuccess = upnpService->loadSCPD(SERVICE_DESCRIPTION);
```

The active root device has some server processes, and returns the responses automatically when a control points sends a request to the device. For example, the device has a HTTP server to return the description files when a control point gets the description file. The device searches an available port for the HTTP server automatically on the machine when the device is started.

![](img/device-ports.png)

The root device is created with the following default parameters, you can change the parameters using the following methods before the root device is started.

|   | Parameter       | Default          | Method                           |
|---|-----------------|------------------|------------------------------------|
| 1 | HTTP port       | 4004             | Device::setHTTPPort()       |
| 2 | Description URI | /description.xml | Device::setDescriptionURI() |
| 3 | Lease time      | 1800             | Device::setLeaseTime        |

## Notify

Your device is announced using `Device::start()` to the UPnP™ network using a notify message with ssdp::alive automatically when the device is started. When device is stopped using `Device::stop()`, a notify message is posted with ssdp::byebye. You can announce the notify messages using `Device::announce()` and Device::byebye().

![](img/device-notify.png)

When a control point sends a search request with M-SEARCH to the UPnP™ network, the active device send the search response to the control point automatically. The device repeats the announcement in the lease time automatically.

## Embedded Devices

The devices may have some embedded devices. Use `Device::getDeviceList()` to get the embedded device list. The following example outputs friendly names of all embedded devices in the device.

```
void printDevice(Device *dev)
{
    counst char *devName = dev->getFriendlyName();
    cout << devName << endl;
    DeviceList *childDevList = dev->getDeviceList();
    int nChildDevs = childDevList->size();
    for (int ｎ =0; ｎ <nChildDevs; ｎ ++) {
        Device *childDev = childDevList ->getDevice(n);
        printDevice(childDev);
    }
}
....
Dev *rootDev = ....;
....
DeviceList *childDevList = rootDev->getDeviceList();
int childDevs = childDevList->size();
for (int n=0; n< childDevs; n++) {
    Device *childDev = rootDevList->getDevice(n);
    printDevice(childDev);
}
```

You can find a embedded device by the friendly name or UDN using `Device::getDevice()`. The following example gets a embedded device by the friendly name.

```
Device *homeServerDev ....
Device *musicDev = homeServerDev->getDevice(“music”);
```

## Service

Use `Device::getServiceList()` to access embedded services of the device. The service may has some actions and state variables. Use `Service::getActionList()` to get the actions, and use `Service::getServiceStateTable()` to the state variables by the name. The following example outputs the all actions and state variables in a device.

```
Device *dev ....
ServiceList *serviceList = dev->getServiceList();
int serviceCnt = serviceList->size();
for (int n=0; n<serviceCnt; n++) {
    Service *service = serviceList->getService(n);
    ActionList *actionList = service->getActionList();
    int actionCnt = actionList->size();
    for (int i=0; i<actionCnt; i++) {
        Action *action = actionList->getAction(i);
        cout << “action [“ << i << “] = “<< action->getName() << endl;
    }
    ServiceStateTable *stateTable = service-> getServiceStateTable ();
    int varCnt = stateTable->size();
    for (int i=0; i<actionCnt; i++) {
        StateVariable *stateVar = stateTable->getServiceStateVariable(i);
        cout << “stateVar [“ << i << “] = “ << stateVar->getName() << endl;
    }
}
```

You can find a service in the device by the service ID using `Device::getService()`, and you can find an action or state variable in the service by name too. Use `Device::getAction()` or `Service::getAction()` to find the action, and use `Device::getStateariable()` or `Service::getStateVariable()` to find the state variable. The following example gets a service, a action and a state variable in a device by name.

```
Device *clockDev ....
Service *timerSev = clockDev->getService(“timer”);
Action *getTimeAct = clockDev->getAction(“GetTime”);
StateVariable *timeStat = clockDev->getStateVariable(“time”);
```

## Control

To receive action control events from control points, the device needs to implement the ActionListener interface. The listener have to implement a actionControlReceived() that has the action and argument list parameter. The input arguments has the passed values from the control point, set the response values in the output arguments and return true when the request is valid. Otherwise return a false when the request is invalid. UPnPError response is returned to the control point automatically when the returned value is false or the device has no the interface. The UPnPError is INVALID_ACTION as default, but use `Action::setSetStatus()` to return other UPnP errors.

To receive query control events from control points, the device needs to implement the QueryListener interface.

The listener have to implement a `queryControlReceived()` that has the service variable parameter and return a true when the request is valid. Otherwise return a false when the request is invalid. UPnPError response is returned to the control point automatically when the returned value is false or the device has no the interface. The UPnPError is INVALID_ACTION as default, but use `ServiceVariable::setSetStatus()` to return other UPnP errors.

The following sample is a clock device. The device executes two action control requests and a query control request.

```
class ClockDevice : public Device, public ActionListener, public QueryListener
{
public:
    ClockDevice() : Device(“/clock/www/description.xml”) {
        Action *setTimeAction = getAction(“SetTime”);
        setTimeAction->setActionListener(this);
        Action *getTimeAction = getAction(“GetTime”);
        getTimeAction->setActionListener(this);
        StateVariable *timeVar = getStateVariable(“Timer”);
        timeVar->setQueryListener(this);
    }

    bool actionControlRecieved(Action *action) {
        ArgumentList *argList = action->getArgumentList();
        const char *actionName = action->getName();
        if (strcmp(actionName, "SetTime") == 0) {
            Argument *inTime = argList->getArgument(“time”);
            const char *timeValue = inTime->getValue();
            If (timeValue == NULL || strlen(timeValue) <= 0)
            return false;
            ....
            Argument *outResult = argList->getArgument(“result”);
            arg->setValue(“TRUE”);
            return true;
        }
        else if (strcmp(actionName, “GetTime”) == 0) {
            const char *currTimeStr = …
            Argument *currTimeArg = argList->getArgument(“currTime”);
            currTimeArg->setValue(currTimeStrs);
            return true;
        }
        action->setStatus(UPnP::INVALID_ACTION, “…..”);
        return false;
    }

    bool queryControlReceived(StatusVariable *stateVar) {
        if (strcmp(varName, “Time”) == 0) {
            cont char *currTimeStr = ….;
            stateVar.setValue(currTimeStr);
            return true;
        }
        stateVar->setStatus(UPnP::INVALID_VAR, “…..”);
        return false;
    }
}
```

Use `Device::setActionListner()` or `Service::setActionListnerer()` to add a listener into all control actions in a device or a service. Use `Device::setQueryListner()` or `Service::setQueryListner()` to add a listener into all query actions in a device or a service. The following sample sets a listener into all actions in a device.

```
class ClockDevice : public Device, public ActionListener, public QueryListener {
public:
    ClockDevice() : Device(“/clock/www/description.xml”) {
        setActionListner(this);
        setQueryListener (this);
    }
    bool actionControlRecieved(Action *action) {
        ....
    }
    bool queryControlReceived(StateVariable *stateVar) {
        ....
    }
}
```

## Event

The control point may subscribe some events of the device. You don’t need manage the subscription messages from control points because the device manages the subscription messages automatically. For example, the device adds a control point into the subscriber list when the control point sends a subscription message to the device, or the device removes the control point from the subscriber list when the control point sends a unsubscription message.

Use `ServiceStateVariable::setValue()` when you want to send the state to the subscribers. The event is sent to the subscribers automatically when the state variable is updated using `ServiceStateVariable::setValue()`. The following example updates a state variable, and the updated state is distributed to the subscribers automatically.

```
Device *clockDevice = ....
StateVariable timeVar = clockDevice->getStateVariable("Time");
const char *timeStr = ....
timeVar->setValue(timeStr);
```

# Control Point

UPnP™ control point is a networked device that controls the UPnP™ devices in the UPnP™ network. The control point has some root devices in the UPnP™ network, and the control point can send action or query control messages to the discovered devices. The control point is created as a root device, and the root device is active using mUPnP for C++.

This section describes how to create your UPnP™ control point using mUPnP for C.

## Class Overview

The following static structure diagram is related classes of mUPnP to create your control point of UPnP™. The control point has some root devices in the UPnP™ network.

![](img/ctrlpoint-class-overview.png)

To create a UPnP™ control point, create a instance of ControlPoint class. Use ControlPoint::start() to active the contol point. The control point multicasts a discovery message searching for all devices to the UPnP™ network automatically when the control point is active.

```
#include <cybergarage/upnp/mUPnP.h>
using namespace mUPnP;
....
ControlPoint *ctrlPoint = new ControlPoint();
....
ctrlPoint->start();
```

The active control point has some server processes, and returns the responses automatically when other UPnP™ devices send the messages to the control point. For example, the control point has a SSDP server to get M-

SEARCH responses, and the control point searches a available port for the SSDP server automatically on the machine when the control point is started.

The control point is created with the following default parameters. You can change the parameters using the following methods before the control point is started.

|   | Parameter        | Default   | Function                                   |
|---|------------------|-----------|--------------------------------------------|
| 1 | HTTP port        | 39500     | CotrolPoint::setHTTPPort()        |
| 2 | SSDP port        | 39400     | CotrolPoint::setSSDPPort() |
| 3 | Subscription URI | /eventSub | CotrolPoint::setEventSubURI()      |
| 4 | Search Response  | 3         | CotrolPoint::setSerchMx()     |

4.3 Notify

The control point receives notify events from devices in the UPnP™ network, and the devices are added or removed form the control point automatically. The expired device is removed from the device list of the control point automatically too. You don’t manage the notify events, but you can receive the event to implement the NotifyListener interface. The following sample receives the notify messages.

```
class MyCtrlPoint : public ControlPoint, public NotifyListener {
public:
    MyCtrlPoint() {
        ....
        addNotifyListener(this);
        start();
    }

    void deviceNotifyReceived(SSDPPacket *ssdpPacket)
    {
        string use, nt, nts, location;
        const char *uuid = ssdpPacket.getUSN(usn);
        const char *target = ssdpPacket.getNT(nt);
        const char *subType = ssdpPacket.getNTS(nts);
        const char *where = ssdpPacket.getLocation(location);
        ....
    }
}
```

To know only the added and removed device, you may use the following interface, DeviceChangeListener.

```
class MyCtrlPoint : public ControlPoint, public DeviceChangeListener {
public:
    MyCtrlPoint() {
        ....
        addDeviceChangeListener (this);
        start();
    }
    void deviceAdded (Device *dev) {
        ....
    }
    void deviceRemoved(Device *dev) {
        ....
    }
}
```

## Search

You can update the device lists using `ControlPoint::search()`. The discovered root devices are added to the control point automatically, and you can receive the response to implement the SearchResponseListener interface. The following sample receives the notify messages.

```
class MyCtrlPoint : public ControlPoint, public SearchResponseListener {
public:
    MyCtrlPoint() {
        ....
        addSearchResponseListener(this);
        start();
        ....
        search(“upnp:rootdevice”);
    }
    void deviceSearchResponseReceived(SSDPPacket *ssdpPacket)
    {
        string usn, st, location;
        const char *uuid = ssdpPacket.getUSN(usn);
        const char *target = ssdpPacket.getST(st);
        const char *where = ssdpPacket.getLocation(location);
        ....
    }
}
```

## Root Devices

Use `ControlPoint::getDeviceList()` that returns only root devices to get the discovered device list. The following example outputs friendly names of the root devices.

```
ControlPoint *ctrlPoint = new ControlPoint();
....
ctrlPoint->start();
....
DeviceList *rootDevList = ctrlPoint->getDeviceList();
int nRootDevs = rootDevList->size();
for (int n=0; n<nRootDevs; n++) {
    Device *dev = rootDevList->getDevice(n);
    const char *devName = dev->getFriendlyName();
    cout << “[“ << n << “] = ” << devName << endl;
}
```

You can find a root device by the friendly name, the device type, or the UDN using ControlPoint::getDevice(). The following example gets a root device by the friendly name.

```
ControlPoint *ctrlPoint = new ControlPoint();
....
ctrlPoint->start();
....
Device *homeServerDev = ctrlPoint->getDevice(“xxxx-home-server”);
```

## Control

The control point can send action or query control messages to the discovered devices. To send the action control message, use `Action::setArgumentValue()` and `Action::postControlAction()`. You should set the action values to the all input arguments, and the output argument values is ignored if you set. The following sample posts a action control request that sets a new time, and output the response result.

```
Device *clockDev = ....
Action *setTimeAct = clockDev->getAction(“SetTime”);
char *newTime = ....
setTimeAct->setArgumentValue(“time”, newTime);
if (setTimeAct->postControlAction() == true) {
    ArgumentList *outArgList = setTimeAct->getOutputArgumentList();
    int nOutArgs = outArgList->size();
    for (int n=0; n<nOutArgs; n++) {
        Argument *outArg = outArgList->getArgument(n);
        const char *name = outArg->getName();
        const char *value = outArg->getValue();
        ....
    }
}
else {
    UPnPStatus *err = setTimeAct->getUPnPStatus();
    System.out.println("Error Code = " + err->getCode());
    System.out.println("Error Desc = " + err->getDescription());
}
```

To send the query control message, use `StateVariable::postQueryControl()`. The following sample posts a query control request, and output the return value.

```
Device *clockDev = ....
StateVariable *timeStateVar = clockDev->getStateVariable(“time”);
if (timeStateVar->postQueryControl() == true) {
    String value = timeStateVar.getValue();
    ....
}
else {
    UPnPStatus *err = timeStateVar->getUPnPStatus();
    System.out.println("Error Code = " + err->getCode());
    System.out.println("Error Desc = " + err->getDescription());
}
```

Use `Argument::getRelatedStateVariable()` to get the related StatiVariable of the argument, and use `StateVariable::getAllowedValueRange()` or `getAllowedValueList()` to get the the allowed value range or list.

```
Device *clockDev = ....
Action *timeAct = clockDev->getAction(“SetTime”);
Argument *timeArg = timeAct->getArgument(“time”);
StataVariable *stateVar = timeArg->getRelatedStateVariable();
if (stateVar != NULL) {
    if (stateVar->hasAllowedValueRange() == true) {
        AllowedValueRange *valRange = stateVar->getAllowedValueRange();
        ....
    }
    if (stateVar->hasAllowedValueList() == true) {
        AllowedValueList *valList = stateVar->getAllowedValueList ();
        ....
    }
}
```

## Event

The control point can subscribe events of the discovered devices, get the state changes of the services Use `ControlPoint::subscribe()` and implement the EventListener interface. The listener have to implement a eventNotifyReceived().

```
MyControlPoint : public ControlPoint, public EventListener {
public:
    MyControlPoint() {
        ....
        addEventListener(this);
    }

    void eventNotifyReceived(const char *uuid, long seq, const char *name, const char *value) {
        ....
    }
}
```

The `ControlPoint::subscribe()` returns true when the subscription is accepted from the service, and you can get the subscription id and timeout.

```
ControlPoint *ctrlPoint = .....
Device *clockDev = ctrlPoint->getDevice(“xxxx-clock”);
Service *timeService = clockDev->getService(“time:1”);
bool subRet = ctrlPoint->subscribe(timeService);
if (subRet == true) {
    const char *sid = timeService->getSID();
    long timeout = timeService->getTimeout();
}
```

# Networked Media Product Requirements

The Intel Networked Media Product Requirements (NMPR) is a implementation guidelins for digital networked devices. Please see the following page about NMPR in more detail.

- [Intel Develper Network for Digital Home](http://www.intel.com/technology/dhdevnet/)

## NMPR Mode

The NMPR features are include Device and ControlPoint class of the mUPnP, but the features are not available
as default. Please use `Device::setNMPRMode()` and `ControlPoint::setNMPRMode()` as the following

```
ControlPoint *ctrlPoint = .....
ctrlPoint->setNMPRMode(true);
ctrlPoint->start();

Device *device = …
device->setNMPRMode(true);
device->setWirelessMode(true); // if your device is on wireless network.
device->start().;
```

## Implementaion Status

| UPnP Technology Requirements | M/S/O | Support | Default | NMPR | Detail |
| --- | --- | --- | --- | --- | --- |
| \<Device Discovery and Control\> | M | Y | O | O | The NMPR tag is added automatically when the NMPR mode is true. |
| \<UPnP iNMPR’03 Description Tag\> | M | Y | X | O | |
| \<UPnP Discovery Flood Control\> | M | Y | O | O | |
| \<UPnP SSDP Default Port\> | M | Y | O | O | |
| \<UPnP Device Advertisement Frequency\> | M | Y | O | O | Use Device::setWirelessMode() too. |
| \<UPnP Discovery over Wireless\> | M | Y | X | O | The subscription is update automatically when the NMPR mode is true. |
| \<UPnP Device Sync Rules\> | M | Y | X | O | Depend on your platform and device implemenation. |
| \<UPnP Auto-IP Support\> | M | - | - | - | Not support to the dynamic changes in network configuration. |
| \<UPnP Device Reset\> | M | N | X | X | The inavtivity connection close and HTTP HEAD request are not supported yet. |
| \<UPnP HTTP Support and General Rules\> | M | N | X | X | |
| \<UPnP HTTP 1.0 Rules\> | M | Y | O | O | Only HTTP 1.0 is supported. |
| \<UPnP HTTP 1.1 Rules\> | M | N | X | X | The HTTP pipelining is not supported yet. |
| \<UPnP HTTP Pipelining General Rules\> | M | N | X | X | |
| \<UPnP Unknown Tag/Field Decoding\> | M | Y | O | O | |
| \<UPnP Error Codes\> | M | - | - | - | Depend on your device implementation. |
| \<UPnP Device Responsiveness\> | M | - | - | - | Depend on your device implementation. |
| \<UPnP SOAP Packet Size\> | S | Y | O | O | There is no limitation for the embedded devices. |
| \<UPnP Embedded Device Support\> | M | N | X | X | |
| \<UPnP Multi-Homing Rules\> | M | Y | O | O | Depend on your device implementation. The UPnP errors are returned automatically when the services are defined and not implemented. |
| \<UPnP Service Descriptions Rules\> | M | - | - | - | |
| \<UPnP Subscription Handling\> | M | Y | O | O | |
| \<UPnP Event Notification Handling\> | M | Y | O | O | Depend on implementation. |
| \<UPnP Device Icons\> | M | - | - | - | Depend on implementation. |
| \<UPnP PNG Icon Recommendations\> | M | - | - | - | Depend on implementation. |
| \<UPnP Device Icon Support for .ICO\> | S | - | - | - | |
| \<UPnP UTF-8 Support\> | M | Y | O | O | |
| \<UPnP XML Comments\> | M | Y | O | O | Depend on implementation. |
| \<UPnP Boolean Type\> | M | - | - | - | Depend on your device implementation. |
| \<UPnP QueryStateVariable\> | M | - | - | - | |
| \<UPnP Action Arguments Encoding\> | M | Y | O | O | The BaseURL is removed only when the NMPR mode is true. The service descriptions must be relative in the device description. |
| \<UPnP URI Rules\> | M | Y | O/X | O | There is no limitation for he UDN length. To change the device descriptions and the services, create the new device and start it. |
| \<UPnP UDN Usage\> | M | Y | O | O | The control point is not renew the subscriptions automatically. |
| \<UPnP Subscription Renewals\> | O | Y | X | O | |
| \<UPnP Device Handling of SubscriptionRenewals\> | M | Y | O | O | |
| \<UPnP IP Address Rules\> | M | Y | O | O | |

# IPv6

mUPnP binds all interfaces in the platform when the devices or control points are created, and the IPv6 sockets are created automatically if the interfaces have IPv6 addresses.mUPnP supports IPv4 and IPv6 both as default. If you want to use only IPv6 interfaces, call the following

method before the devices or control points are created.

```
UPnP::SetEnable(UPnP::USE_ONLY_IPV6_ADDR)
```

Link local is the default scope for multicasting of mUPnP. Use UPnP::SetEnable() to change the scope. The following example changes the scope to the site local.

```
UPnP::SetEnable(UPnP::USE_IPV6_SITE_LOCAL_SCOPE)
```

On Unix platform, mUPnP get the local interfaces IPv4 and IPv6 using getifaddrs(). If you want to use mUPnP with IPv6, please check the function supports IPv6 on your platform. I know that the function doesn’t support IPv6 yet on Redhat 9 and MacOSX 10.2.6.

# Inside mUPnP

This section describes the inside of mUPnP for C++.

## Overriding HTTP Service

The Device class of mUPnP implements a HTTPRequestListner interface of CyberHTTP package to handle some HTTP requests from the control points. The HTTPRequestListener interface is bellow.

```
class HTTPRequestListener
{
public:
    virtual void httpRequestRecieved(HTTPRequest *httpReq) = 0;
}
```

To overide the interface, use CyberHTTP namespace and override the httpRequestRecieved method in your device that is a sub class of the Device class. The following example is a clock device using mUPnP, and adds the override method to return the presentation page.

```
using namespace CyberHTTP;
const char PRESENTATION_URI[] = "/presentation";
....
class ClockDevice : public Device, public ActionListener, public QueryListener {
    ....
    void httpRequestRecieved(HTTPRequest *httpReq) {
        string uri = httpReq->getURI();
        if (uri.find(PRESENTATION_URI) == string::npos) {
            Device::httpRequestRecieved(httpReq);
            return;
        }
        string clockStr = ....;
        string contents;
        contents = "<HTML><BODY><H1>";
        contents += clockStr;
        contents += "</H1></BODY></HTML>";
        HTTPResponse httpRes;
        httpRes.setStatusCode(HTTP::OK_REQUEST);
        httpRes.setContent(contents);
        httpReq->post(&httpRes);
    }
}
```

# Transitioning From Version 1.2

## QueryListner

mUPnP v1.3 has changed the QueryListner interface to return user error infomation and set the listener to the StateVariable instance instead of the Service instance. The difference is bellow.

| Version | Interface |
| --- | --- |
| 1.2 | bool queryControlReceived(Service *service, const char *varName, std::string &result) |
| 1.3 | bool queryControlReceived(StateVariable *stateVar) |

Use StateVariable::getName() to know the variable name, and use StateVariable::setValue() to return the result value. The following sample shows the difference between v1.2 and v1.3.

v1.2:
```
bool queryControlReceived(Service *service, const char *varName, string &result) {
    result = Clock::GetCurrentTimeString();
    return true;
}
```

v1.3:
```
bool queryControlReceived(StateVariable *stateVar) {
    const char *varName = stateVar->getName();
    stateVar->setValue(Clock::GetCurrentTimeString());
    return true;
}
```

To set the query listener, use StateVariable:: setQueryListener() instead of `Service::setQueryListner()`.

However, `Service::setQueryListner()` that sets the specifed listener to all state variables in the service is not deprecated to ensure the compatibility. The implematation is bellow.

```
void Service::setQueryListener(QueryListener *listener)
{
    ServiceStateTable *stateTable = getServiceStateTable();
    for (int n=0; n< stateTable->size(); n++) {
        StateVariable *var = stateTable->getStateVariable(n);
        var->setQueryListener(listener);
    }
}
```
