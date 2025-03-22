/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2003
 *
 *	File : ContentDirectory.h
 *
 *	Revision:
 *
 *	04/03/04
 *		- first revision.
 *
 ******************************************************************/

#ifndef _CLINK_MEDIA_CONTENTDIRECTORY_H_
#define _CLINK_MEDIA_CONTENTDIRECTORY_H_

#include <mupnp/upnp/control/ActionListener.h>
#include <mupnp/upnp/control/QueryListener.h>
#include <mupnp/upnp/media/server/DirectoryList.h>
#include <mupnp/upnp/media/server/action/BrowseAction.h>
#include <mupnp/upnp/media/server/action/SearchAction.h>
#include <mupnp/upnp/media/server/object/ContentNodeList.h>
#include <mupnp/upnp/media/server/object/FormatList.h>
#include <mupnp/upnp/media/server/object/SearchCapList.h>
#include <mupnp/upnp/media/server/object/SortCapList.h>
#include <mupnp/upnp/media/server/object/container/RootNode.h>
#include <mupnp/upnp/media/server/object/item/ItemNodeList.h>
#include <mupnp/util/Mutex.h>
#include <mupnp/util/Thread.h>

#include <string>

namespace CyberLink {

class MediaServer;
class RootNode;
class SortCriteriaList;
class SearchCriteriaList;

class ContentDirectory : public CyberUtil::Thread, public ActionListener, public QueryListener {
  MediaServer* mediaServer;

  CyberUtil::Mutex mutex;

  int systemUpdateID;
  int maxContentID;

  long systemUpdateIDInterval;
  long contentUpdateInterval;

  RootNode rootNode;

  FormatList formatList;
  SortCapList sortCapList;
  SearchCapList searchCapList;
  DirectoryList dirList;

  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  public:
  static const char* DESCRIPTION;

  static const char* SERVICE_TYPE;

  static const char* BROWSE;

  static const char* SEARCH;

  static const char* GET_SEARCH_CAPABILITIES;
  static const char* SEARCH_CAPS;

  static const char* GET_SORT_CAPABILITIES;
  static const char* SORT_CAPS;

  static const char* GET_SYSTEM_UPDATE_ID;
  static const char* ID;

  static const char* SYSTEM_UPDATE_ID;

  static const char* CONTENT_EXPORT_URI;
  static const char* CONTENT_IMPORT_URI;
  static const char* CONTENT_ID;

  static const int DEFAULT_SYSTEMUPDATEID_INTERVAL;
  static const int DEFAULT_CONTENTUPDATE_INTERVAL;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  public:
  ContentDirectory(MediaServer* mserver);

  virtual ~ContentDirectory();

  ////////////////////////////////////////////////
  // Media Server
  ////////////////////////////////////////////////

  private:
  void setMediaServer(MediaServer* mserver)
  {
    mediaServer = mserver;
  }

  public:
  MediaServer* getMediaServer()
  {
    return mediaServer;
  }

  ////////////////////////////////////////////////
  // Mutex
  ////////////////////////////////////////////////

  public:
  void lock()
  {
    mutex.lock();
  }

  void unlock()
  {
    mutex.unlock();
  }

  ////////////////////////////////////////////////
  // ContentID
  ////////////////////////////////////////////////

  public:
  void updateSystemUpdateID();
  int getSystemUpdateID();

  ////////////////////////////////////////////////
  // ContentID
  ////////////////////////////////////////////////

  private:
  int getNextContentID();

  public:
  int getNextItemID()
  {
    return getNextContentID();
  }

  int getNextContainerID()
  {
    return getNextContentID();
  }

  ////////////////////////////////////////////////
  // Root Node
  ////////////////////////////////////////////////

  private:
  void initRootNode();

  public:
  RootNode* getRootNode()
  {
    return &rootNode;
  }

  ////////////////////////////////////////////////
  // Container/Item Node
  ////////////////////////////////////////////////

  /*
          private ContainerNode createContainerNode()
          {
                  ContainerNode node = new ContainerNode();
                  return node;
          }
  */

  ////////////////////////////////////////////////
  // Format
  ////////////////////////////////////////////////

  public:
  bool addPlugIn(Format* format)
  {
    formatList.add(format);
    return true;
  }

  Format* getFormat(CyberIO::File* file)
  {
    return formatList.getFormat(file);
  }

  Format* getFormat(int n)
  {
    return formatList.getFormat(n);
  }

  int getNFormats()
  {
    return formatList.size();
  }

  ////////////////////////////////////////////////
  // SortCap
  ////////////////////////////////////////////////

  public:
  bool addSortCap(SortCap* sortCap)
  {
    sortCapList.add(sortCap);
    return true;
  }

  int getNSortCaps()
  {
    return sortCapList.size();
  }

  SortCap* getSortCap(int n)
  {
    return sortCapList.getSortCap(n);
  }

  SortCap* getSortCap(const char* type)
  {
    return sortCapList.getSortCap(type);
  }

  private:
  void initSortCaps();

  const char* getSortCapabilities(std::string& sortCap);

  ////////////////////////////////////////////////
  // SearchCap
  ////////////////////////////////////////////////

  public:
  SearchCapList* getSearchCapList()
  {
    return &searchCapList;
  }

  bool addSearchCap(SearchCap* searchCap)
  {
    searchCapList.add(searchCap);
    return true;
  }

  int getNSearchCaps()
  {
    return searchCapList.size();
  }

  SearchCap* getSearchCap(int n)
  {
    return searchCapList.getSearchCap(n);
  }

  SearchCap* getSearchCap(const char* type)
  {
    return searchCapList.getSearchCap(type);
  }

  private:
  void initSearchCaps();

  const char* getSearchCapabilities(std::string& searchCap);

  ////////////////////////////////////////////////
  // Directory
  ////////////////////////////////////////////////

  private:
  DirectoryList* getDirectoryList()
  {
    return &dirList;
  }

  public:
  bool addDirectory(Directory* dir);

  bool removeDirectory(Directory* dir);
  bool removeDirectory(const char* name);
  bool removeDirectory(int n);

  int getNDirectories()
  {
    return dirList.size();
  }

  Directory* getDirectory(int n)
  {
    return dirList.getDirectory(n);
  }

  ////////////////////////////////////////////////
  // findContentNodeBy*
  ////////////////////////////////////////////////

  public:
  ContentNode* findContentNodeByID(const char* conId)
  {
    return getRootNode()->findContentNodeByID(conId);
  }

  ////////////////////////////////////////////////
  // ActionListener
  ////////////////////////////////////////////////

  public:
  bool actionControlReceived(Action* action);

  ////////////////////////////////////////////////
  // Browse
  ////////////////////////////////////////////////

  private:
  bool browseActionReceived(BrowseAction* action);

  ////////////////////////////////////////////////
  // Browse (MetaData)
  ////////////////////////////////////////////////

  private:
  bool browseMetadataActionReceived(BrowseAction* action);

  ////////////////////////////////////////////////
  // Browse (DirectChildren/Sort)
  ////////////////////////////////////////////////

  private:
  void sortContentNodeList(ContentNode* conNode[], int nConNode, SortCap* sortCap, bool ascSeq);

  int getSortCriteriaArray(const char* sortCriteria, SortCriteriaList& sortCriList);

  ContentNodeList* sortContentNodeList(ContentNodeList* contentNodeList, const char* sortCriteria, ContentNodeList& sortedContentNodeList);

  ////////////////////////////////////////////////
  // Browse (DirectChildren)
  ////////////////////////////////////////////////

  private:
  bool browseDirectChildrenActionReceived(BrowseAction* action);

  ////////////////////////////////////////////////
  // Search
  ////////////////////////////////////////////////

  public:
  int getSearchCriteriaList(const char* searchStr, SearchCriteriaList& searchList);
  int getSearchContentList(ContentNode* node, SearchCriteriaList* searchCriList, SearchCapList* searchCapList, ContentNodeList& contentNodeList);
  bool searchActionReceived(SearchAction* action);

  ////////////////////////////////////////////////
  // QueryListener
  ////////////////////////////////////////////////

  public:
  bool queryControlReceived(StateVariable* stateVar);

  ////////////////////////////////////////////////
  //	HTTP Server
  ////////////////////////////////////////////////

  public:
  void contentExportRequestRecieved(CyberHTTP::HTTPRequest* httpReq);

  ////////////////////////////////////////////////
  // Content URL
  ////////////////////////////////////////////////

  public:
  const char* getInterfaceAddress();

  int getHTTPPort();

  const char* getContentExportURL(const char* conId, std::string& url);

  const char* getContentImportURL(const char* conId, std::string& url);

  ////////////////////////////////////////////////
  // run
  ////////////////////////////////////////////////

  public:
  void setSystemUpdateInterval(long itime)
  {
    systemUpdateIDInterval = itime;
  }

  long getSystemUpdateIDInterval()
  {
    return systemUpdateIDInterval;
  }

  void setContentUpdateInterval(long itime)
  {
    contentUpdateInterval = itime;
  }

  long getContentUpdateInterval()
  {
    return contentUpdateInterval;
  }

  void run();

  ////////////////////////////////////////////////
  // print
  ////////////////////////////////////////////////

  public:
  void print();
};

}

#endif
