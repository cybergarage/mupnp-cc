# Microsoft Developer Studio Project File - Name="CyberLinkMedia" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CyberLinkMedia - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "CyberLinkMedia.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "CyberLinkMedia.mak" CFG="CyberLinkMedia - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "CyberLinkMedia - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "CyberLinkMedia - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CyberLinkMedia - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CyberLinkMedia___Win32_Release"
# PROP BASE Intermediate_Dir "CyberLinkMedia___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../../include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "USE_XMLPARSER_EXPAT" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CyberLinkMedia - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CyberLinkMedia___Win32_Debug"
# PROP BASE Intermediate_Dir "CyberLinkMedia___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "../../../include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "USE_XMLPARSER_EXPAT" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "CyberLinkMedia - Win32 Release"
# Name "CyberLinkMedia - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\action\BrowseAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\ConnectionInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\ConnectionInfoList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\ConnectionManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\container\ContainerNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\ContentDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\ContentNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\ContentNodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\ContentPropertyList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\sort\DCDateSortCap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\sort\DCTitleSortCap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\format\DefaultFormat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\DIDLLite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\DirectoryList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\file\FileDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\file\FileItemNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\file\FileItemNodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\FormatList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\gateway\GatewayDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\gateway\GatewayItemNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\gateway\GatewayItemNodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\format\GIFFormat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\format\ID3Format.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\format\ID3Frame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\format\ID3FrameList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\search\IdSearchCap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\ItemNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\ItemNodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\itunes\iTunesDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\itunes\iTunesItemNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\itunes\iTunesItemNodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\itunes\iTunesLibrary.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\itunes\iTunesNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\itunes\iTunesPlaylist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\itunes\iTunesPlaylistItemList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\itunes\iTunesPlaylistList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\itunes\iTunesTrack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\itunes\iTunesTrackList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\format\JPEGFormat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\player\MediaPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\MediaServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\format\MPEGFormat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\mythtv\MythDatabase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\mythtv\MythDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\mythtv\MythRecordedInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\directory\mythtv\MythRecordedInfoList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\mythtv\MythRecordedItemNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\item\mythtv\MythRecordedItemNodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\format\PNGFormat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\action\SearchAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\SearchCapList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\SearchCriteria.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\SearchCriteriaList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\SortCapList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\SortCriteriaList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\search\TitleSearchCap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\media\server\object\sort\UPnPClassSortCap.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\action\BrowseAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\player\action\BrowseResult.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\player\action\BrowseResultNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\ConnectionInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\ConnectionInfoList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\ConnectionManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\container\ContainerNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\ContentDirectory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\ContentNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\ContentNodeList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\ContentProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\ContentPropertyList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\sort\DCDateSortCap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\sort\DCTitleSortCap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\format\DefaultFormat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\DIDLLite.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\DIDLLiteNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\Directory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\DirectoryList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\file\FileDirectory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\file\FileItemNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\file\FileItemNodeList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\Format.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\FormatList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\FormatObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\gateway\GatewayDirectory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\gateway\GatewayItemNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\gateway\GatewayItemNodeList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\format\GIFFormat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\format\ID3Format.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\format\ID3Frame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\format\ID3FrameList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\search\IdSearchCap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\format\ImageFormat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\ItemNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\ItemNodeList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\itunes\iTunesDirectory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\itunes\iTunesItemNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\itunes\iTunesItemNodeList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\itunes\iTunesLibrary.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\itunes\iTunesNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\itunes\iTunesPlaylist.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\itunes\iTunesPlaylistItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\itunes\iTunesPlaylistItemList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\itunes\iTunesPlaylistList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\itunes\iTunesTrack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\itunes\iTunesTrackList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\format\JPEGFormat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\player\MediaPlayer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\MediaServer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\format\MPEGFormat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\mythtv\MythDatabase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\mythtv\MythDirectory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\mythtv\MythRecordedInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\directory\mythtv\MythRecordedInfoList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\mythtv\MythRecordedItemNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\item\mythtv\MythRecordedItemNodeList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\format\PNGFormat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\container\RootNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\action\SearchAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\SearchCap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\SearchCapList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\SearchCriteria.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\SearchCriteriaList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\SortCap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\SortCapList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\SortCriteriaList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\search\TitleSearchCap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\UPnP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\media\server\object\sort\UPnPClassSortCap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\USN.h
# End Source File
# End Group
# End Target
# End Project
