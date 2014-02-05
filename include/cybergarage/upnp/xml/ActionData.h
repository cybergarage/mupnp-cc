/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ActionData.h
*
*  Revision;
*
*  07/20/03
*    - first revision
*  04/19/04
*    - Fixed to initialize the action listener and the control responce member.
*
******************************************************************/

#ifndef _CLINK_ACTONDATA_H_
#define _CLINK_ACTONDATA_H_

#include <string>
#include <cybergarage/xml/NodeData.h>

namespace CyberLink {
class ActionListener;
class ControlResponse;

class ActionData : public CyberXML::NodeData {
  ActionListener *actionListener;
  ControlResponse *ctrlRes;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  ActionData();

  ~ActionData();

  ////////////////////////////////////////////////
  // ActionListener
  ////////////////////////////////////////////////

 public:
  ActionListener *getActionListener() 
  {
    return actionListener;
  }

  void setActionListener(ActionListener *listener) 
  {
    actionListener = listener;
  }

  ////////////////////////////////////////////////
  // ControlResponse
  ////////////////////////////////////////////////

 public:
  ControlResponse *getControlResponse() 
  {
    return ctrlRes;
  }

  void setControlResponse(ControlResponse *res);
};

}

#endif


