# Microsoft Developer Studio Project File - Name="LightShow" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LightShow - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "LightShow.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "LightShow.mak" CFG="LightShow - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "LightShow - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "LightShow - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LightShow - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\wx\lib\vc_lib\mswu" /I "..\..\include" /I "C:\wx\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__WXMSW__" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib winmm.lib advapi32.lib wsock32.lib wxbase26u.lib wxmsw26u_core.lib wxmsw26u_adv.lib wxpng.lib wxtiff.lib wxjpeg.lib wxzlib.lib /nologo /subsystem:windows /machine:I386 /libpath:"C:\wx\lib\vc_lib"

!ELSEIF  "$(CFG)" == "LightShow - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\wx\lib\vc_lib\mswud" /I "..\..\include" /I "C:\wx\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__WXMSW__" /D "__WXDEBUG__" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib winmm.lib advapi32.lib wsock32.lib wxbase26ud.lib wxmsw26ud_core.lib wxmsw26ud_adv.lib wxpngd.lib wxtiffd.lib wxjpegd.lib wxzlibd.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"C:\wx\lib\vc_lib"

!ENDIF 

# Begin Target

# Name "LightShow - Win32 Release"
# Name "LightShow - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\ChannelDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\channelitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\configitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\deskitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\DeskSetupToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\DMXPatchDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\FaderDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\faderitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\FunctionDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functionitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\FunctionThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\GroupDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\groupitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\GroupSelectDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\groupselectitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\IOSetupDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LibraryDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\main.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MainDrawWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MainToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mywxGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mywxGridCellAttrProvider.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mywxGridCellEditors.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mywxGridTableBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\OutputDrawWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\patchitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\plugin_interface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\PosSelectWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\projectorchannelitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\projectoritem.cpp
# End Source File
# Begin Source File

SOURCE=.\Resource.rc
# End Source File
# Begin Source File

SOURCE=..\..\src\stateitem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\storage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\storage_item.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\valueitem.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\ChannelDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\include\channelitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\configitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\dataitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\deskitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\DeskSetupToolBar.h
# End Source File
# Begin Source File

SOURCE=..\..\include\DMXPatchDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\include\FaderDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\include\faderitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\FunctionDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\include\functionitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\FunctionThread.h
# End Source File
# Begin Source File

SOURCE=..\..\include\GroupDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\include\groupitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\GroupSelectDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\include\groupselectitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\IOSetupDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\include\LibraryDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\include\main.h
# End Source File
# Begin Source File

SOURCE=..\..\include\MainDrawWindow.h
# End Source File
# Begin Source File

SOURCE=..\..\include\MainFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\include\MainToolBar.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mywxGrid.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mywxGridCellAttrProvider.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mywxGridCellEditors.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mywxGridTableBase.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OutputDrawWindow.h
# End Source File
# Begin Source File

SOURCE=..\..\include\patchitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\plugin_interface.h
# End Source File
# Begin Source File

SOURCE=..\..\include\PosSelectWidget.h
# End Source File
# Begin Source File

SOURCE=..\..\include\prec.h
# End Source File
# Begin Source File

SOURCE=..\..\include\projectorchannelitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\projectoritem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\stateitem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\storage.h
# End Source File
# Begin Source File

SOURCE=..\..\include\storage_item.h
# End Source File
# Begin Source File

SOURCE=..\..\include\valueitem.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# End Group
# End Target
# End Project
