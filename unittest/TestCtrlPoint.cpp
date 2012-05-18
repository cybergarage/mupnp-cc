/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: upnpdump.cpp
*
*	Revision;
*
*	08/22/03
*		- first revision
*	03/25/04
*		- Added print().
*
******************************************************************/

#include "TestCtrlPoint.h"
#include <uhttp/util/Debug.h>
#include <iostream>

using namespace std;
using namespace uHTTP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

TestCtrlPoint::TestCtrlPoint()
{
	addNotifyListener(this);
	addSearchResponseListener(this);
	addEventListener(this);
}
	
////////////////////////////////////////////////
// deviceNotifyReceived
////////////////////////////////////////////////

void TestCtrlPoint::deviceNotifyReceived(SSDPPacket *packet)
{
	if (packet->isDiscover() == true) {
		string stBuf;
		const char *st = packet->getST(stBuf);
		if (Debug::isOn() == true)
			cout << "ssdp:discover : ST = " << st << endl; 
	}
	else if (packet->isAlive() == true) {
		string usnBuf;
		string ntBuf;
		string locationBuf;
		const char *usn = packet->getUSN(usnBuf);
		const char *nt = packet->getNT(ntBuf);
		const char *url = packet->getLocation(locationBuf);
		if (Debug::isOn() == true)
			cout << "ssdp:alive : uuid = " << usn << ", NT = " << nt << ", location = " << url << endl; 
	}
	else if (packet->isByeBye() == true) {
		string usnBuf;
		string ntBuf;
		const char *usn = packet->getUSN(usnBuf);
		const char *nt = packet->getNT(ntBuf);
		if (Debug::isOn() == true)
			cout << "ssdp:byebye : uuid = " << usn << ", NT = " << nt << endl; 
	}
}
	
////////////////////////////////////////////////
// deviceSearchResponseReceived
////////////////////////////////////////////////

void TestCtrlPoint::deviceSearchResponseReceived(SSDPPacket *packet)
{
	string usnBuf;
	string stBuf;
	string locationBuf;
	const char *uuid = packet->getUSN(usnBuf);
	const char *st = packet->getST(stBuf);
	const char *url = packet->getLocation(locationBuf);
	if (Debug::isOn() == true)
		cout << "device search res : uuid = " << uuid << ", ST = " << st << ", location = " << url << endl; 
}
	
////////////////////////////////////////////////
// eventNotifyReceived
////////////////////////////////////////////////

void TestCtrlPoint::eventNotifyReceived(const std::string &uuid, long seq, const std::string &name, const std::string &value)
{
	if (Debug::isOn() == true)
		cout << "event notify : uuid = " << uuid << ", seq = " << seq << ", name = " << name << ", value =" << value << endl; 
}

////////////////////////////////////////////////
// print
////////////////////////////////////////////////

void GetIndentString(int indent, string &buf)
{
	buf = "";
	for (int n=0; n<indent; n++)
		buf.append("    ");
}

void PrintDeviceInfo(Device *dev, int indent)
{
	string indentStr;
	GetIndentString(indent, indentStr);
	const char *devName = dev->getFriendlyName();
	cout << indentStr << devName << endl;

	int i, n, j;
	ServiceList *serviceList = dev->getServiceList();
	int serviceCnt = serviceList->size();
	for (n=0; n<serviceCnt; n++) {
		Service *service = serviceList->getService(n);
		cout << indentStr << " service[" << n << "] = "<< service->getServiceType() << endl;
		ActionList *actionList = service->getActionList();
		int actionCnt = actionList->size();
		for (i=0; i<actionCnt; i++) {
			Action *action = actionList->getAction(i);
			cout << indentStr << "  action[" << i << "] = "<< action->getName() << endl;
			ArgumentList *argList = action->getArgumentList();
			int argCnt = argList->size();
			for (j=0; j<argCnt; j++) {
					Argument *arg = argList->getArgument(j);
					cout << indentStr << "    arg[" << j << "] = " << arg->getName() << "("  << arg->getDirection() << ")";
					StateVariable *stateVar = arg->getRelatedStateVariable();
					if (stateVar != NULL)
						cout << " - " << stateVar->getName();
					cout << endl;
			}
		}
		ServiceStateTable *stateTable = service->getServiceStateTable();
		int varCnt = stateTable->size();
		for (i=0; i<varCnt; i++) {
			StateVariable *stateVar = stateTable->getStateVariable(i);
			cout << indentStr << "  stateVar[" << i << "] = " << stateVar->getName() << endl;
			AllowedValueList *valueList = stateVar->getAllowedValueList();
			int valueListCnt = valueList->size();
			if (0 < valueListCnt) {
				for (j=0; j<valueListCnt; j++)
					cout << indentStr << "    AllowedValueList[" << j << "] = " << valueList->getAllowedValue(j) << endl;
			}
			AllowedValueRange *valueRange = stateVar->getAllowedValueRange();
			if (valueRange != NULL) {
					cout << indentStr << "    AllowedRange[minimum] = " << valueRange->getMinimum() << endl;
					cout << indentStr << "    AllowedRange[maximum] = " << valueRange->getMaximum() << endl;
					cout << indentStr << "    AllowedRange[step] = " << valueRange->getStep() << endl;
			}
		}
	}
}

void PrintDevice(Device *dev, int indent)
{
	PrintDeviceInfo(dev, indent);

	DeviceList *childDevList = dev->getDeviceList();
	int nChildDevs = childDevList->size();
	for (int n=0; n<nChildDevs; n++) {
		Device *childDev = childDevList->getDevice(n);
		PrintDevice(childDev, indent);
	}
}

void TestCtrlPoint::print()
{
	DeviceList *rootDevList = getDeviceList();
	int nRootDevs = rootDevList->size();
	cout << "Device Num = " << nRootDevs << endl;
	for (int n=0; n<nRootDevs; n++) {
		Device *dev = rootDevList->getDevice(n);
		const char *devName = dev->getFriendlyName();
		cout << "[" << n << "] = " << devName << endl;
		PrintDevice(dev, 1);
	}
}
