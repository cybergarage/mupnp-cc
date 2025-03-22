/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2006
 *
 *	File : iTunesLibrary.cpp
 *
 *	Revision:
 *
 *	02/22/06
 *		- first revision.
 *
 ******************************************************************/

#ifdef SUPPORT_ITUNES

#include <mupnp/upnp/media/server/directory/itunes/iTunesLibrary.h>

#include <sstream>
#include <typeinfo>

#if defined(WIN32)
#include <shlobj.h>
#endif

using namespace std;
using namespace CyberIO;
using namespace CyberXML;
using namespace CyberLink;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

const char* iTunesLibrary::DICT_TAG = "dict";
const char* iTunesLibrary::KEY_TAG = "key";
const char* iTunesLibrary::ARRAY_TAG = "array";
const char* iTunesLibrary::KEY_TRACKS = "Tracks";
const char* iTunesLibrary::KEY_PLAYLISTS = "Playlists";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

iTunesLibrary::iTunesLibrary()
{
  itunesTrackList = new iTunesTrackList();
  itunesPlaylistList = new iTunesPlaylistList();

  rootNode = NULL;
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

iTunesLibrary::~iTunesLibrary()
{
  clear();
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

void iTunesLibrary::clear()
{
  delete itunesTrackList;
  delete itunesPlaylistList;

  if (rootNode != NULL) {
    delete rootNode;
    rootNode = NULL;
  }
}

////////////////////////////////////////////////
// Music Library
////////////////////////////////////////////////

const char* ITUNES_XML_DIR_NAME = "iTunes";
const char* ITUNES_XML_FILE_NAME = "iTunes Music Library.xml";

const char* iTunesLibrary::GetMusicLibraryXMLFileName(std::string& buf)
{
#if defined(WIN32)
  TCHAR szPath[_MAX_PATH];
  LPITEMIDLIST pidl;
  IMalloc* pMalloc;

  szPath[0] = '\0';
  SHGetMalloc(&pMalloc);
  if (SHGetSpecialFolderLocation(NULL, CSIDL_MYMUSIC, &pidl) == S_OK) {
    SHGetPathFromIDList(pidl, szPath);
    pMalloc->Free(pidl);
  }
  pMalloc->Release();

  buf = szPath;
  buf += "\\";
  buf += ITUNES_XML_DIR_NAME;
  buf += "\\";
  buf += ITUNES_XML_FILE_NAME;
#else
#endif
  return buf.c_str();
}

////////////////////////////////////////////////
// updateTracks
////////////////////////////////////////////////

bool iTunesLibrary::updateTracks()
{
  Node* rootNode = getRootNode();
  if (rootNode == NULL)
    return false;

  // Root Dict Node
  Node* rootDictNode = rootNode->getNode(DICT_TAG);
  if (rootDictNode == NULL)
    return false;

  // Tracks Dict Node
  Node* tracksDictNode = NULL;
  int rootDictNodeCnt = rootDictNode->getNNodes();
  for (int n = 0; n < rootDictNodeCnt; n++) {
    Node* node = rootDictNode->getNode(n);
    if (node == NULL)
      continue;
    if (node->isName(KEY_TAG) == false)
      continue;
    if (node->isValue(KEY_TRACKS) == false)
      continue;
    if ((rootDictNodeCnt - 1) <= n)
      continue;
    tracksDictNode = rootDictNode->getNode(n + 1);
    break;
  }
  if (tracksDictNode == NULL)
    return false;

  // Track Dict Node
  int tracksDictNodeCnt = tracksDictNode->getNNodes();
  for (int n = 0; n < tracksDictNodeCnt; n++) {
    Node* node = rootDictNode->getNode(n);
    if (node == NULL)
      continue;
    if (node->isName(KEY_TAG) == false)
      continue;
    if ((rootDictNodeCnt - 1) <= n)
      continue;
    Node* trackDictNode = tracksDictNode->getNode(n + 1);
    if (trackDictNode == NULL)
      continue;
    iTunesTrack* track = new iTunesTrack(node);
    itunesTrackList->add(track);
  }

  return true;
}

////////////////////////////////////////////////
// updatePlaylists
////////////////////////////////////////////////

bool iTunesLibrary::updatePlaylists()
{
  Node* rootNode = getRootNode();
  if (rootNode == NULL)
    return false;

  // Root Dict Node
  Node* rootDictNode = rootNode->getNode(DICT_TAG);
  if (rootDictNode == NULL)
    return false;

  // Playlists Array Node
  Node* playlistArrayNode = NULL;
  int rootDictNodeCnt = rootDictNode->getNNodes();
  for (int n = 0; n < rootDictNodeCnt; n++) {
    Node* node = rootDictNode->getNode(n);
    if (node == NULL)
      continue;
    if (node->isName(KEY_TAG) == false)
      continue;
    if (node->isValue(KEY_PLAYLISTS) == false)
      continue;
    if ((rootDictNodeCnt - 1) <= n)
      continue;
    playlistArrayNode = rootDictNode->getNode(n + 1);
    break;
  }
  if (playlistArrayNode == NULL)
    return false;

  // Playlist
  int playlistArrayNodeCnt = playlistArrayNode->getNNodes();
  for (int n = 0; n < playlistArrayNodeCnt; n++) {

    // Playlist
    Node* node = playlistArrayNode->getNode(n);
    if (node == NULL)
      continue;
    if (node->isName(DICT_TAG) == false)
      continue;
    iTunesPlaylist* playList = new iTunesPlaylist(node);
    itunesTrackList->add(playList);

    // Playlist Items

    Node* playlistItemArrayNode = node->getNode(ARRAY_TAG);
    if (playlistItemArrayNode == NULL)
      continue;

    iTunesPlaylistItemList* playlistItemList = playList->getPlaylistItemList();
    if (playlistItemList == NULL)
      continue;

    int playlistItemArrayNodeCnt = playlistItemArrayNode->getNNodes();
    for (int i = 0; i < playlistItemArrayNodeCnt; i++) {
      Node* cnode = playlistItemArrayNode->getNode(n);
      if (cnode == NULL)
        continue;
      if (cnode->isName(DICT_TAG) == false)
        continue;
      iTunesPlaylistItem* playlistItem = new iTunesPlaylistItem(cnode);
      playlistItemList->add(playlistItem);
    }
  }

  return true;
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////

bool iTunesLibrary::equals(iTunesLibrary* otherLib)
{
  // Tracks
  iTunesTrackList* thisTrackList = getTrackList();
  iTunesTrackList* otherTrackList = otherLib->getTrackList();

  return false;
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////

bool iTunesLibrary::update()
{
  string musicLibFileName;

  GetMusicLibraryXMLFileName(musicLibFileName);
  if (musicLibFileName.length() <= 0)
    return false;

  File musicLibFile;
  musicLibFile.setName(musicLibFileName.c_str());

  Parser parser;
  Node* newRootNode = parser.parse(&musicLibFile);
  if (newRootNode == NULL)
    return false;

  clear();

  rootNode = newRootNode;

  if (updateTracks() == false)
    return false;
  if (updatePlaylists() == false)
    return false;

  return true;
}

#endif
