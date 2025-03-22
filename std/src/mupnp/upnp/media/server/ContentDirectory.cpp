/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2002
 *
 *	File : ContentDirectory.cpp
 *
 *	Revision:
 *
 *	04/03/04
 *		- first revision.
 *	05/19/04
 *		- Changed the header include order for Cygwin.
 *	06/20/04
 *		- Changed contentExportRequestRecieved() to set the ConnectionInfo.
 *	07/12/04
 *		- Changed getSortCriteriaArray() to use StringTokenizer instead of strtok().
 *	08/07/04
 *		- Implemented for GetSearchCapabilities request.
 *
 ******************************************************************/

#include <string.h>

#include <mupnp/upnp/media/server/ContentDirectory.h>
#include <mupnp/upnp/media/server/MediaServer.h>
#include <mupnp/upnp/media/server/object/DIDLLite.h>
#include <mupnp/upnp/media/server/object/SearchCriteriaList.h>
#include <mupnp/upnp/media/server/object/SortCriteriaList.h>
#include <mupnp/upnp/media/server/object/item/ItemNode.h>

#include <mupnp/http/HTTPStatus.h>
#include <mupnp/util/Debug.h>
#include <mupnp/util/StringTokenizer.h>
#include <mupnp/util/StringUtil.h>
#include <mupnp/util/TimeUtil.h>

#include <mupnp/upnp/media/server/object/SortCap.h>
#include <mupnp/upnp/media/server/object/sort/DCDateSortCap.h>
#include <mupnp/upnp/media/server/object/sort/DCTitleSortCap.h>
#include <mupnp/upnp/media/server/object/sort/UPnPClassSortCap.h>

#include <mupnp/upnp/media/server/object/SearchCap.h>
#include <mupnp/upnp/media/server/object/search/IdSearchCap.h>

#include <sstream>

using namespace std;
using namespace CyberLink;
using namespace CyberUtil;
using namespace CyberHTTP;
using namespace CyberIO;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char* ContentDirectory::DESCRIPTION = "<?xml version=\"1.0\" encoding=\"utf-8\"?> \n"
                                            "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\"> \n"
                                            "   <specVersion> \n"
                                            "      <major>1</major> \n"
                                            "      <minor>0</minor> \n"
                                            "   </specVersion> \n"
                                            "   <actionList> \n"
                                            "      <action> \n"
                                            "         <name>ExportResource</name> \n"
                                            "         <argumentList> \n"
                                            "            <argument> \n"
                                            "               <name>SourceURI</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_URI</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>DestinationURI</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_URI</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>TransferID</name> \n"
                                            "               <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_TransferID</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "         </argumentList> \n"
                                            "      </action> \n"
                                            "      <action> \n"
                                            "         <name>StopTransferResource</name> \n"
                                            "         <argumentList> \n"
                                            "            <argument> \n"
                                            "               <name>TransferID</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_TransferID</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "         </argumentList> \n"
                                            "      </action> \n"
                                            "      <action> \n"
                                            "         <name>DestroyObject</name> \n"
                                            "         <argumentList> \n"
                                            "            <argument> \n"
                                            "               <name>ObjectID</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_ObjectID</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "         </argumentList> \n"
                                            "      </action> \n"
                                            "      <action> \n"
                                            "         <name>DeleteResource</name> \n"
                                            "         <argumentList> \n"
                                            "            <argument> \n"
                                            "               <name>ResourceURI</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_URI</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "         </argumentList> \n"
                                            "      </action> \n"
                                            "      <action> \n"
                                            "         <name>UpdateObject</name> \n"
                                            "         <argumentList> \n"
                                            "            <argument> \n"
                                            "               <name>ObjectID</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_ObjectID</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>CurrentTagValue</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_TagValueList</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>NewTagValue</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_TagValueList</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "         </argumentList> \n"
                                            "      </action> \n"
                                            "      <action> \n"
                                            "         <name>Browse</name> \n"
                                            "         <argumentList> \n"
                                            "            <argument> \n"
                                            "               <name>ObjectID</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_ObjectID</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>BrowseFlag</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_BrowseFlag</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>Filter</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_Filter</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>StartingIndex</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_Index</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>RequestedCount</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_Count</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>SortCriteria</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_SortCriteria</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>Result</name> \n"
                                            "               <direction>out</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_Result</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>NumberReturned</name> \n"
                                            "               <direction>out</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_Count</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>TotalMatches</name> \n"
                                            "               <direction>out</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_Count</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>UpdateID</name> \n"
                                            "               <direction>out</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_UpdateID</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "         </argumentList> \n"
                                            "      </action> \n"
                                            "      <action> \n"
                                            "         <name>GetTransferProgress</name> \n"
                                            "         <argumentList> \n"
                                            "            <argument> \n"
                                            "               <name>TransferID</name> \n"
                                            "               <direction>in</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_TransferID</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>TransferStatus</name> \n"
                                            "               <direction>out</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_TransferStatus</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "            <argument> \n"
                                            "               <name>TransferLength</name> \n"
                                            "               <direction>out</direction> \n"
                                            "               <relatedStateVariable>A_ARG_TYPE_TransferLength</relatedStateVariable> \n"
                                            "            </argument> \n"
                                            "             <argument> \n"
                                            "                <name>TransferTotal</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_TransferTotal</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "          </argumentList> \n"
                                            "       </action> \n"
                                            "       <action> \n"
                                            "          <name>GetSearchCapabilities</name> \n"
                                            "          <argumentList> \n"
                                            "             <argument> \n"
                                            "                <name>SearchCaps</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>SearchCapabilities</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "          </argumentList> \n"
                                            "       </action> \n"
                                            "       <action> \n"
                                            "          <name>CreateObject</name> \n"
                                            "          <argumentList> \n"
                                            "             <argument> \n"
                                            "                <name>ContainerID</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_ObjectID</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>Elements</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_Result</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>ObjectID</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_ObjectID</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>Result</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_Result</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "          </argumentList> \n"
                                            "       </action> \n"
                                            "       <action> \n"
                                            "          <name>Search</name> \n"
                                            "          <argumentList> \n"
                                            "             <argument> \n"
                                            "                <name>ContainerID</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_ObjectID</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>SearchCriteria</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_SearchCriteria</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>Filter</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_Filter</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>StartingIndex</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_Index</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>RequestedCount</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_Count</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>SortCriteria</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_SortCriteria</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>Result</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_Result</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>NumberReturned</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_Count</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>TotalMatches</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_Count</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>UpdateID</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_UpdateID</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "          </argumentList> \n"
                                            "       </action> \n"
                                            "       <action> \n"
                                            "          <name>GetSortCapabilities</name> \n"
                                            "          <argumentList> \n"
                                            "             <argument> \n"
                                            "                <name>SortCaps</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>SortCapabilities</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "          </argumentList> \n"
                                            "       </action> \n"
                                            "       <action> \n"
                                            "          <name>ImportResource</name> \n"
                                            "          <argumentList> \n"
                                            "             <argument> \n"
                                            "                <name>SourceURI</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_URI</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>DestinationURI</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_URI</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>TransferID</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_TransferID</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "          </argumentList> \n"
                                            "       </action> \n"
                                            "       <action> \n"
                                            "          <name>CreateReference</name> \n"
                                            "          <argumentList> \n"
                                            "             <argument> \n"
                                            "                <name>ContainerID</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_ObjectID</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>ObjectID</name> \n"
                                            "                <direction>in</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_ObjectID</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "             <argument> \n"
                                            "                <name>NewID</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>A_ARG_TYPE_ObjectID</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "          </argumentList> \n"
                                            "       </action> \n"
                                            "       <action> \n"
                                            "          <name>GetSystemUpdateID</name> \n"
                                            "          <argumentList> \n"
                                            "             <argument> \n"
                                            "                <name>Id</name> \n"
                                            "                <direction>out</direction> \n"
                                            "                <relatedStateVariable>SystemUpdateID</relatedStateVariable> \n"
                                            "             </argument> \n"
                                            "          </argumentList> \n"
                                            "       </action> \n"
                                            "    </actionList> \n"
                                            "    <serviceStateTable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_SortCriteria</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_TransferLength</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"yes\"> \n"
                                            "          <name>TransferIDs</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_UpdateID</name> \n"
                                            "          <dataType>ui4</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_SearchCriteria</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_Filter</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"yes\"> \n"
                                            "          <name>ContainerUpdateIDs</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_Result</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_Index</name> \n"
                                            "          <dataType>ui4</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_TransferID</name> \n"
                                            "          <dataType>ui4</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_TagValueList</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_URI</name> \n"
                                            "          <dataType>uri</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_ObjectID</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>SortCapabilities</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>SearchCapabilities</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_Count</name> \n"
                                            "          <dataType>ui4</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_BrowseFlag</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "          <allowedValueList> \n"
                                            "             <allowedValue>BrowseMetadata</allowedValue> \n"
                                            "             <allowedValue>BrowseDirectChildren</allowedValue> \n"
                                            "          </allowedValueList> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"yes\"> \n"
                                            "          <name>SystemUpdateID</name> \n"
                                            "          <dataType>ui4</dataType> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_TransferStatus</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "          <allowedValueList> \n"
                                            "             <allowedValue>COMPLETED</allowedValue> \n"
                                            "             <allowedValue>ERROR</allowedValue> \n"
                                            "             <allowedValue>IN_PROGRESS</allowedValue> \n"
                                            "             <allowedValue>STOPPED</allowedValue> \n"
                                            "          </allowedValueList> \n"
                                            "       </stateVariable> \n"
                                            "       <stateVariable sendEvents=\"no\"> \n"
                                            "          <name>A_ARG_TYPE_TransferTotal</name> \n"
                                            "          <dataType>string</dataType> \n"
                                            "       </stateVariable> \n"
                                            "    </serviceStateTable> \n"
                                            " </scpd> \n";

const char* ContentDirectory::SERVICE_TYPE = "urn:schemas-upnp-org:service:ContentDirectory:1";

const char* ContentDirectory::BROWSE = "Browse";

const char* ContentDirectory::SEARCH = "Search";

const char* ContentDirectory::GET_SEARCH_CAPABILITIES = "GetSearchCapabilities";
const char* ContentDirectory::SEARCH_CAPS = "SearchCaps";

const char* ContentDirectory::GET_SORT_CAPABILITIES = "GetSortCapabilities";
const char* ContentDirectory::SORT_CAPS = "SortCaps";

const char* ContentDirectory::GET_SYSTEM_UPDATE_ID = "GetSystemUpdateID";
const char* ContentDirectory::ID = "Id";

const char* ContentDirectory::SYSTEM_UPDATE_ID = "SystemUpdateID";

const char* ContentDirectory::CONTENT_EXPORT_URI = "/ExportContent";
const char* ContentDirectory::CONTENT_IMPORT_URI = "/ImportContent";
const char* ContentDirectory::CONTENT_ID = "id";

const int ContentDirectory::DEFAULT_SYSTEMUPDATEID_INTERVAL = 2000;
const int ContentDirectory::DEFAULT_CONTENTUPDATE_INTERVAL = 60000;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

ContentDirectory::ContentDirectory(MediaServer* mserver)
{
  setMediaServer(mserver);

  systemUpdateID = 0;
  maxContentID = 0;

  setSystemUpdateInterval(DEFAULT_SYSTEMUPDATEID_INTERVAL);
  setContentUpdateInterval(DEFAULT_CONTENTUPDATE_INTERVAL);

  initRootNode();
  initSortCaps();
  initSearchCaps();
}

ContentDirectory::~ContentDirectory()
{
}

////////////////////////////////////////////////
// ContentID
////////////////////////////////////////////////

void ContentDirectory::updateSystemUpdateID()
{
  lock();
  systemUpdateID++;
  unlock();
}

int ContentDirectory::getSystemUpdateID()
{
  lock();
  int id = systemUpdateID;
  unlock();
  return id;
}

////////////////////////////////////////////////
// ContentID
////////////////////////////////////////////////

int ContentDirectory::getNextContentID()
{
  lock();
  maxContentID++;
  int id = maxContentID;
  unlock();
  return id;
}

////////////////////////////////////////////////
// Root Node
////////////////////////////////////////////////

void ContentDirectory::initRootNode()
{
  rootNode.setContentDirectory(this);
}

/*
        ////////////////////////////////////////////////
        // Container/Item Node
        ////////////////////////////////////////////////

        private ContainerNode createContainerNode()
        {
                ContainerNode node = new ContainerNode();
                return node;
        }
*/

////////////////////////////////////////////////
// SortCap
////////////////////////////////////////////////

void ContentDirectory::initSortCaps()
{
  addSortCap(new UPnPClassSortCap());
  addSortCap(new DCTitleSortCap());
  addSortCap(new DCDateSortCap());
}

const char* ContentDirectory::getSortCapabilities(string& sortCapsStr)
{
  sortCapsStr = "";
  int nSortCaps = getNSortCaps();
  for (int n = 0; n < nSortCaps; n++) {
    SortCap* sortCap = getSortCap(n);
    string type = sortCap->getType();
    if (0 < n)
      sortCapsStr += ",";
    sortCapsStr += type;
  }
  return sortCapsStr.c_str();
}

////////////////////////////////////////////////
// SearchCap
////////////////////////////////////////////////

void ContentDirectory::initSearchCaps()
{
  addSearchCap(new IdSearchCap());
}

const char* ContentDirectory::getSearchCapabilities(string& searchCapsStr)
{
  searchCapsStr = "";
  int nSearchCaps = getNSearchCaps();
  for (int n = 0; n < nSearchCaps; n++) {
    SearchCap* searchCap = getSearchCap(n);
    string type = searchCap->getPropertyName();
    if (0 < n)
      searchCapsStr += ",";
    searchCapsStr += type;
  }
  return searchCapsStr.c_str();
}

////////////////////////////////////////////////
// Directory
////////////////////////////////////////////////

bool ContentDirectory::addDirectory(Directory* dir)
{
  dir->setContentDirectory(this);
  dir->setID(getNextContainerID());
  dir->update();
  dirList.add(dir);
  rootNode.addContentNode(dir);

  // Update SysteUpdateID
  updateSystemUpdateID();

  return true;
}

bool ContentDirectory::removeDirectory(Directory* dir)
{
  if (dir == NULL)
    return false;
  dirList.remove(dir);
  rootNode.removeNode(dir);

  // Update SysteUpdateID
  updateSystemUpdateID();

  return true;
}

bool ContentDirectory::removeDirectory(const char* name)
{
  Directory* dir = dirList.getDirectory(name);
  if (dir == NULL)
    return false;
  removeDirectory(dir);
  delete dir;
  return true;
}

bool ContentDirectory::removeDirectory(int n)
{
  Directory* dir = dirList.getDirectory(n);
  if (dir == NULL)
    return false;
  removeDirectory(dir);
  delete dir;
  return true;
}

////////////////////////////////////////////////
// ActionListener
////////////////////////////////////////////////

bool ContentDirectory::actionControlReceived(Action* action)
{
  string actionName = action->getName();

  if (actionName.compare(BROWSE) == 0) {
    BrowseAction browseAct(action);
    return browseActionReceived(&browseAct);
  }

  if (actionName.compare(SEARCH) == 0) {
    SearchAction searchAct(action);
    return searchActionReceived(&searchAct);
  }

  //@id,@parentID,dc:title,dc:date,upnp:class,res@protocolInfo
  if (actionName.compare(GET_SEARCH_CAPABILITIES) == 0) {
    Argument* searchCapsArg = action->getArgument(SEARCH_CAPS);
    string searchCapsStr;
    getSearchCapabilities(searchCapsStr);
    searchCapsArg->setValue(searchCapsStr.c_str());
    return true;
  }

  // dc:title,dc:date,upnp:class
  if (actionName.compare(GET_SORT_CAPABILITIES) == 0) {
    Argument* sortCapsArg = action->getArgument(SORT_CAPS);
    string sortCapsStr;
    getSortCapabilities(sortCapsStr);
    sortCapsArg->setValue(sortCapsStr.c_str());
    return true;
  }

  if (actionName.compare(GET_SYSTEM_UPDATE_ID) == 0) {
    Argument* idArg = action->getArgument(ID);
    idArg->setValue(getSystemUpdateID());
    return true;
  }

  return false;
}

////////////////////////////////////////////////
// Browse
////////////////////////////////////////////////

bool ContentDirectory::browseActionReceived(BrowseAction* action)
{
  if (action->isMetadata() == true)
    return browseMetadataActionReceived(action);
  if (action->isDirectChildren() == true)
    return browseDirectChildrenActionReceived(action);
  return false;
}

////////////////////////////////////////////////
// Browse (MetaData)
////////////////////////////////////////////////

bool ContentDirectory::browseMetadataActionReceived(BrowseAction* action)
{
  const char* objID = action->getObjectID();
  ContentNode* node = findContentNodeByID(objID);
  if (node == NULL)
    return false;

  DIDLLite didlLite(false);
  didlLite.setContentNode(node);
  string result;
  didlLite.toString(result);

  action->setResult(result.c_str());
  action->setNumberReturned(1);
  action->setTotalMaches(1);
  action->setUpdateID(getSystemUpdateID());

  return true;
}

////////////////////////////////////////////////
// Browse (DirectChildren/Sort)
////////////////////////////////////////////////

void ContentDirectory::sortContentNodeList(ContentNode* conNode[], int nConNode, SortCap* sortCap, bool ascSeq)
{
  // Selection Sort
  for (int i = 0; i < (nConNode - 1); i++) {
    int selIdx = i;
    for (int j = (i + 1); j < nConNode; j++) {
      int cmpRet = sortCap->compare(conNode[selIdx], conNode[j]);
      if (ascSeq == true && cmpRet < 0)
        selIdx = j;
      if (ascSeq == false && 0 < cmpRet)
        selIdx = j;
    }
    ContentNode* conTmp = conNode[i];
    conNode[i] = conNode[selIdx];
    conNode[selIdx] = conTmp;
  }
}

int ContentDirectory::getSortCriteriaArray(const char* sortCriteria, SortCriteriaList& sortCriList)
{
  sortCriList.clear();
  if (sortCriteria == NULL)
    return 0;
  int sortCriteriaLen = (int)strlen(sortCriteria);
  char* sortCriteriaBuf = new char[sortCriteriaLen + 1];
  strcpy(sortCriteriaBuf, sortCriteria);
  char* seps = ", ";
  StringTokenizer toknizer(sortCriteriaBuf, seps);
  while (toknizer.hasMoreTokens() == true) {
    const char* token = toknizer.nextToken();
    string* sortCrit = new string(token);
    sortCriList.add(sortCrit);
  }
  delete[] sortCriteriaBuf;
  return sortCriList.size();
}

ContentNodeList* ContentDirectory::sortContentNodeList(ContentNodeList* contentNodeList, const char* sortCriteria, ContentNodeList& sortedContentNodeList)
{
  if (sortCriteria == NULL)
    return contentNodeList;
  string sortCriteriaStr = sortCriteria;
  if (sortCriteriaStr.length() <= 0)
    return contentNodeList;

  int n;

  int nChildNodes = contentNodeList->size();
  ContentNode** conNode = new ContentNode*[nChildNodes];
  for (n = 0; n < nChildNodes; n++)
    conNode[n] = contentNodeList->getContentNode(n);

  SortCriteriaList sortCriList;
  int nSortCrit = getSortCriteriaArray(sortCriteria, sortCriList);
  for (n = 0; n < nSortCrit; n++) {
    string sortStr = sortCriList.getSortCriteria(n);
    // Debug.message("[" + n + "] = " + sortStr);
    bool ascSeq = true;
    char firstSortChar = sortStr.at(0);
    if (firstSortChar == '-')
      ascSeq = false;
    if (firstSortChar == '+' || firstSortChar == '-')
      sortStr = sortStr.substr(1);
    SortCap* sortCap = getSortCap(sortStr.c_str());
    if (sortCap == NULL)
      continue;
    // Debug.message("  ascSeq = " + ascSeq);
    // Debug.message("  sortCap = " + sortCap.getType());
    sortContentNodeList(conNode, nChildNodes, sortCap, ascSeq);
  }

  for (n = 0; n < nChildNodes; n++)
    sortedContentNodeList.add(conNode[n]);
  return &sortedContentNodeList;
}

////////////////////////////////////////////////
// Browse (DirectChildren)
////////////////////////////////////////////////

bool ContentDirectory::browseDirectChildrenActionReceived(BrowseAction* action)
{
  const char* objID = action->getObjectID();
  ContentNode* node = findContentNodeByID(objID);
  if (node == NULL)
    return false;

  int n;

  ContentNodeList contentNodeList(false);
  int nChildNodes = node->getNContentNodes();
  for (n = 0; n < nChildNodes; n++) {
    ContentNode* cnode = node->getContentNode(n);
    contentNodeList.add(cnode);
  }

  // Sort Content Node Lists
  string sortCriteria = action->getSortCriteria();
  ContentNodeList sortedContentNodeBufList(false);
  ContentNodeList* sortedContentNodeList = sortContentNodeList(&contentNodeList, sortCriteria.c_str(), sortedContentNodeBufList);

  int startingIndex = action->getStartingIndex();
  if (startingIndex <= 0)
    startingIndex = 0;
  int requestedCount = action->getRequestedCount();
  if (requestedCount == 0)
    requestedCount = nChildNodes;

  DIDLLite didlLite(false);
  int numberReturned = 0;
  for (n = startingIndex; (n < nChildNodes && numberReturned < requestedCount); n++) {
    ContentNode* cnode = sortedContentNodeList->getContentNode(n);
    didlLite.addContentNode(cnode);
    numberReturned++;
  }

  string result;
  didlLite.toString(result);
  action->setResult(result.c_str());
  action->setNumberReturned(numberReturned);
  action->setTotalMaches(nChildNodes);
  action->setUpdateID(getSystemUpdateID());

  return true;
}

////////////////////////////////////////////////
// Search
////////////////////////////////////////////////

int ContentDirectory::getSearchCriteriaList(const char* searchStr, SearchCriteriaList& searchList)
{
  if (searchStr == NULL)
    return searchList.size();
  if (strcmp(searchStr, "*") == 0)
    return searchList.size();

  StringTokenizer searchCriTokenizer(searchStr, SearchCriteria::WCHARS);
  while (searchCriTokenizer.hasMoreTokens() == true) {
    string prop = searchCriTokenizer.nextToken();
    if (searchCriTokenizer.hasMoreTokens() == false)
      break;
    string binOp = searchCriTokenizer.nextToken();
    if (searchCriTokenizer.hasMoreTokens() == false)
      break;
    string value = searchCriTokenizer.nextToken();
    StringTrim(value.c_str(), "\"", value);
    string logOp;
    if (searchCriTokenizer.hasMoreTokens() == true)
      logOp = searchCriTokenizer.nextToken();
    SearchCriteria* searchCri = new SearchCriteria();
    searchCri->setProperty(prop.c_str());
    searchCri->setOperation(binOp.c_str());
    searchCri->setValue(value.c_str());
    searchCri->setLogic(logOp.c_str());
    searchList.add(searchCri);
  }

  return searchList.size();
}

int ContentDirectory::getSearchContentList(ContentNode* node, SearchCriteriaList* searchCriList, SearchCapList* searchCapList, ContentNodeList& contentNodeList)
{
  if (searchCriList->compare(node, searchCapList) == true)
    contentNodeList.add(node);

  int nChildNodes = node->getNContentNodes();
  for (int n = 0; n < nChildNodes; n++) {
    ContentNode* cnode = node->getContentNode(n);
    getSearchContentList(cnode, searchCriList, searchCapList, contentNodeList);
  }
  return contentNodeList.size();
}

bool ContentDirectory::searchActionReceived(SearchAction* action)
{
  const char* contaierID = action->getContainerID();
  ContentNode* node = findContentNodeByID(contaierID);
  if (node == NULL)
    return false;

  SearchCriteriaList searchCriList;
  const char* searchCriteria = action->getSearchCriteria();
  int searchListCount = getSearchCriteriaList(searchCriteria, searchCriList);
  SearchCapList* searchCapList = getSearchCapList();

  int n;
  ContentNodeList contentNodeList(false);
  int nChildNodes = node->getNContentNodes();
  for (n = 0; n < nChildNodes; n++) {
    ContentNode* cnode = node->getContentNode(n);
    getSearchContentList(cnode, &searchCriList, searchCapList, contentNodeList);
  }
  nChildNodes = contentNodeList.size();

  // Sort Content Node Lists
  string sortCriteria = action->getSortCriteria();
  ContentNodeList sortedContentNodeBufList(false);
  ContentNodeList* sortedContentNodeList = sortContentNodeList(&contentNodeList, sortCriteria.c_str(), sortedContentNodeBufList);

  int startingIndex = action->getStartingIndex();
  if (startingIndex <= 0)
    startingIndex = 0;
  int requestedCount = action->getRequestedCount();
  if (requestedCount == 0)
    requestedCount = nChildNodes;

  DIDLLite didlLite(false);
  int numberReturned = 0;
  for (n = startingIndex; (n < nChildNodes && numberReturned < requestedCount); n++) {
    ContentNode* cnode = sortedContentNodeList->getContentNode(n);
    didlLite.addContentNode(cnode);
    numberReturned++;
  }

  string result;
  didlLite.toString(result);
  action->setResult(result.c_str());
  action->setNumberReturned(numberReturned);
  action->setTotalMaches(nChildNodes);
  action->setUpdateID(getSystemUpdateID());

  return true;
}

////////////////////////////////////////////////
// QueryListener
////////////////////////////////////////////////

bool ContentDirectory::queryControlReceived(StateVariable* stateVar)
{
  return false;
}

////////////////////////////////////////////////
//	HTTP Server
////////////////////////////////////////////////

void ContentDirectory::contentExportRequestRecieved(CyberHTTP::HTTPRequest* httpReq)
{
  if (Debug::isOn())
    httpReq->print();

  string uri;
  httpReq->getURI(uri);
  if (uri.find(CONTENT_EXPORT_URI) == string::npos) {
    httpReq->returnBadRequest();
    return;
  }

  ParameterList paramList;
  httpReq->getParameterList(paramList);

  ////////////////////////////////////////
  // Getting item ID
  ////////////////////////////////////////

  const char* id = paramList.getValue(CONTENT_ID);

  if (Debug::isOn())
    cout << "id = " << id << endl;

  ////////////////////////////////////////
  // Has Item Node ?
  ////////////////////////////////////////

  ContentNode* node = findContentNodeByID(id);
  if (node == NULL) {
    httpReq->returnBadRequest();
    return;
  }
  if (node->isItemNode() == false) {
    httpReq->returnBadRequest();
    return;
  }

  ////////////////////////////////////////
  // Return item content
  ////////////////////////////////////////

  ItemNode* itemNode = (ItemNode*)node;

  long contentLen = itemNode->getContentLength();
  string contentType = itemNode->getMimeType();
  InputStream* contentIn = itemNode->getContentInputStream();

  if (Debug::isOn()) {
    cout << "itemNode = " << itemNode << endl;
    cout << "contentLen = " << contentLen << endl;
    cout << "contentTypeIn = " << contentType << endl;
    cout << "contentIn = " << contentIn << endl;
  }

  if (contentLen <= 0 || contentType.length() <= 0 || contentIn == NULL) {
    httpReq->returnBadRequest();
    return;
  }

  MediaServer* mserver = getMediaServer();
  ConnectionManager* conMan = mserver->getConnectionManager();
  int conID = conMan->getNextConnectionID();
  ConnectionInfo* conInfo = new ConnectionInfo(conID);
  conInfo->setProtocolInfo(contentType.c_str());
  conInfo->setDirection(ConnectionInfo::OUTPUT);
  conInfo->setStatus(ConnectionInfo::OK);
  conMan->addConnectionInfo(conInfo);

  // Thanks for Robert Johansson <robert.johansson@kreatel.se>
  HTTPResponse httpRes;
  httpRes.setContentType(contentType.c_str());
  httpRes.setStatusCode(HTTP::OK_REQUEST);
  httpRes.setContentLength(contentLen);
  httpRes.setContentInputStream(contentIn);

  httpReq->post(&httpRes);
  contentIn->close();

  conMan->removeConnectionInfo(conID);

  delete contentIn;
}

////////////////////////////////////////////////
// Content URL
////////////////////////////////////////////////

const char* ContentDirectory::getInterfaceAddress()
{
  return getMediaServer()->getInterfaceAddress();
}

int ContentDirectory::getHTTPPort()
{
  return getMediaServer()->getHTTPPort();
}

const char* ContentDirectory::getContentExportURL(const char* id, std::string& url)
{
  ostringstream urlBuf;
  urlBuf << "http://" << getInterfaceAddress() << ":" << getHTTPPort() << CONTENT_EXPORT_URI << "?" << CONTENT_ID << "=" << id;
  url = urlBuf.str();
  return url.c_str();
}

const char* ContentDirectory::getContentImportURL(const char* id, std::string& url)
{
  ostringstream urlBuf;
  urlBuf << "http://" << getInterfaceAddress() << ":" << getHTTPPort() << CONTENT_IMPORT_URI << "?" << CONTENT_ID << "=" << id;
  url = urlBuf.str();
  return url.c_str();
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void ContentDirectory::run()
{
  MediaServer* mserver = getMediaServer();
  StateVariable* varSystemUpdateID = mserver->getStateVariable(SYSTEM_UPDATE_ID);

  int lastSystemUpdateID = 0;
  long lastContentUpdateTime = GetCurrentSystemTime();

  while (isRunnable() == true) {
    Wait(getSystemUpdateIDInterval());

    // WUpdate SystemUpdateID
    int currSystemUpdateID = getSystemUpdateID();
    if (lastSystemUpdateID != currSystemUpdateID) {
      varSystemUpdateID->setValue(currSystemUpdateID);
      lastSystemUpdateID = currSystemUpdateID;
    }

    // Update Content Directory
    long currTime = GetCurrentSystemTime();
    if (getContentUpdateInterval() < (currTime - lastContentUpdateTime)) {
      getDirectoryList()->update();
      lastContentUpdateTime = currTime;
    }
  }
}

////////////////////////////////////////////////
// print
////////////////////////////////////////////////

void ContentDirectory::print()
{
  RootNode* rootNode = getRootNode();
  if (rootNode == NULL)
    return;
  rootNode->print();
}
