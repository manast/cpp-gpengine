# Microsoft Developer Studio Project File - Name="gpengine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=gpengine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gpengine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gpengine.mak" CFG="gpengine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gpengine - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gpengine - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gpengine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "gpengine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "gpengine - Win32 Release"
# Name "gpengine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\ASTCreator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\ASTNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\CGTFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\CharacterSetTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\DFA.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\DFAStateTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Error.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\GrammarInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LALR.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LALRStateTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\misc.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Reduction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\RuleTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\SymbolTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Token.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\ASTCreator.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ASTNode.h
# End Source File
# Begin Source File

SOURCE=..\..\src\CGTFile.h
# End Source File
# Begin Source File

SOURCE=..\..\src\CharacterSetTable.h
# End Source File
# Begin Source File

SOURCE=..\..\src\DFA.h
# End Source File
# Begin Source File

SOURCE=..\..\src\DFAStateTable.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Error.h
# End Source File
# Begin Source File

SOURCE=..\..\src\GrammarInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LALR.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LALRStateTable.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Reduction.h
# End Source File
# Begin Source File

SOURCE=..\..\src\RuleTable.h
# End Source File
# Begin Source File

SOURCE=..\..\src\SymbolTable.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Token.h
# End Source File
# End Group
# End Target
# End Project
