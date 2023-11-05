# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DIVE32.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/DIVE32.exe $(OUTDIR)/DIVE32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /Fp$(OUTDIR)/"DIVE32.pch" /Yu"STDAFX.H" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"DIVELOG.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DIVE32.bsc" 

$(OUTDIR)/DIVE32.bsc : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ctl3dv2.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 oldnames.lib ctl3d32.lib /NOLOGO /STACK:0x10240 /MACHINE:IX86 /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=oldnames.lib ctl3d32.lib /NOLOGO /STACK:0x10240 /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"DIVE32.pdb" /MACHINE:IX86 /OUT:$(OUTDIR)/"DIVE32.exe"\
 /SUBSYSTEM:windows,4.0  
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/DIVELOG.res \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/divelog.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/DIVEDOC.OBJ \
	$(INTDIR)/divevw.obj \
	$(INTDIR)/frontpg.obj \
	$(INTDIR)/BACKPG.OBJ \
	$(INTDIR)/locdlg.obj \
	$(INTDIR)/defset.obj \
	$(INTDIR)/toolbarx.obj \
	$(INTDIR)/thghtdlg.obj \
	$(INTDIR)/Calendar.obj \
	$(INTDIR)/Calendlg.obj \
	$(INTDIR)/Diagdlg.obj \
	$(INTDIR)/Diagscrl.obj \
	$(INTDIR)/Editdate.obj \
	$(INTDIR)/Fauxcmb.obj \
	$(INTDIR)/Fauxdlg.obj \
	$(INTDIR)/repdoc.obj \
	$(INTDIR)/repview.obj \
	$(INTDIR)/repwnd.obj \
	$(INTDIR)/reports.obj \
	$(INTDIR)/reprtdlg.obj \
	$(INTDIR)/filtdlg.obj \
	$(INTDIR)/buddata.obj \
	$(INTDIR)/buddypg.obj \
	$(INTDIR)/DIVEDATA.OBJ \
	$(INTDIR)/divepg.obj \
	$(INTDIR)/notesdlg.obj \
	$(INTDIR)/TABLES.OBJ

$(OUTDIR)/DIVE32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/DIVE32.exe $(OUTDIR)/DIVE32.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /Fp$(OUTDIR)/"DIVE32.pch" /Yu"STDAFX.H" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DIVE32.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo$(INTDIR)/"DIVELOG.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"DIVE32.bsc" 

$(OUTDIR)/DIVE32.bsc : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ctl3dv2.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 oldnames.lib ctl3d32.lib /NOLOGO /STACK:0x10240 /DEBUG /MACHINE:IX86 /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=oldnames.lib ctl3d32.lib /NOLOGO /STACK:0x10240 /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"DIVE32.pdb" /DEBUG /MACHINE:IX86 /OUT:$(OUTDIR)/"DIVE32.exe"\
 /SUBSYSTEM:windows,4.0  
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/DIVELOG.res \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/divelog.obj \
	$(INTDIR)/mainfrm.obj \
	$(INTDIR)/DIVEDOC.OBJ \
	$(INTDIR)/divevw.obj \
	$(INTDIR)/frontpg.obj \
	$(INTDIR)/BACKPG.OBJ \
	$(INTDIR)/locdlg.obj \
	$(INTDIR)/defset.obj \
	$(INTDIR)/toolbarx.obj \
	$(INTDIR)/thghtdlg.obj \
	$(INTDIR)/Calendar.obj \
	$(INTDIR)/Calendlg.obj \
	$(INTDIR)/Diagdlg.obj \
	$(INTDIR)/Diagscrl.obj \
	$(INTDIR)/Editdate.obj \
	$(INTDIR)/Fauxcmb.obj \
	$(INTDIR)/Fauxdlg.obj \
	$(INTDIR)/repdoc.obj \
	$(INTDIR)/repview.obj \
	$(INTDIR)/repwnd.obj \
	$(INTDIR)/reports.obj \
	$(INTDIR)/reprtdlg.obj \
	$(INTDIR)/filtdlg.obj \
	$(INTDIR)/buddata.obj \
	$(INTDIR)/buddypg.obj \
	$(INTDIR)/DIVEDATA.OBJ \
	$(INTDIR)/divepg.obj \
	$(INTDIR)/notesdlg.obj \
	$(INTDIR)/TABLES.OBJ

$(OUTDIR)/DIVE32.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\DIVELOG.RC
DEP_DIVEL=\
	.\RES\DIVELOG.ICO\
	.\RES\DIVEDOC.ICO\
	.\RES\BIN.ICO\
	.\RES\IDR_REPO.ICO\
	.\RES\TOOLBAR.BMP\
	.\RES\NEXTPAGE.BMP\
	.\RES\PREVPAGE.BMP\
	.\RES\TANK_FUL.BMP\
	.\RES\PICTURE.BMP\
	.\RES\FRONT_PG.BMP\
	.\RES\BMP00001.BMP\
	.\RES\BIN.BMP\
	.\RES\IDR_MAIN.BMP\
	.\RES\BITMAP1.BMP\
	.\RES\CURSOR1.CUR\
	.\RES\CUR00001.CUR\
	.\RES\DIVELOG.RC2

$(INTDIR)/DIVELOG.res :  $(SOURCE)  $(DEP_DIVEL) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_STDAF=\
	.\STDAFX.H\
	.\toolbarx.h

!IF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /Fp$(OUTDIR)/"DIVE32.pch" /Yc"STDAFX.H" /Fo$(INTDIR)/ /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /Fp$(OUTDIR)/"DIVE32.pch" /Yc"STDAFX.H" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"DIVE32.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\divelog.cpp
DEP_DIVELO=\
	.\STDAFX.H\
	.\DIVEDATA.H\
	.\reports.h\
	.\divelog.h\
	.\mainfrm.h\
	.\DIVEDOC.H\
	.\divevw.h\
	.\repwnd.h\
	.\repdoc.h\
	.\repview.h\
	.\thghtdlg.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/divelog.obj :  $(SOURCE)  $(DEP_DIVELO) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_MAINF=\
	.\STDAFX.H\
	.\divelog.h\
	.\mainfrm.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/mainfrm.obj :  $(SOURCE)  $(DEP_MAINF) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIVEDOC.CPP
DEP_DIVED=\
	.\STDAFX.H\
	.\divelog.h\
	.\DIVEDOC.H\
	.\divevw.h\
	.\DIVEDATA.H\
	.\defset.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/DIVEDOC.OBJ :  $(SOURCE)  $(DEP_DIVED) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\divevw.cpp
DEP_DIVEV=\
	.\STDAFX.H\
	.\divelog.h\
	.\DIVEDOC.H\
	.\divevw.h\
	.\frontpg.h\
	.\BACKPG.H\
	.\divepg.h\
	.\Editdate.h\
	.\locdlg.h\
	.\defset.h\
	.\mainfrm.h\
	.\DIVEDATA.H\
	.\reprtdlg.h\
	.\toolbarx.h\
	.\TABLES.H\
	.\Calendar.h\
	.\Fauxcmb.h\
	.\Diagscrl.h

$(INTDIR)/divevw.obj :  $(SOURCE)  $(DEP_DIVEV) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\frontpg.cpp
DEP_FRONT=\
	.\STDAFX.H\
	.\divelog.h\
	.\frontpg.h\
	.\DIVEDOC.H\
	.\divevw.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/frontpg.obj :  $(SOURCE)  $(DEP_FRONT) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BACKPG.CPP
DEP_BACKP=\
	.\STDAFX.H\
	.\divelog.h\
	.\BACKPG.H\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/BACKPG.OBJ :  $(SOURCE)  $(DEP_BACKP) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\locdlg.cpp
DEP_LOCDL=\
	.\STDAFX.H\
	.\divelog.h\
	.\locdlg.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/locdlg.obj :  $(SOURCE)  $(DEP_LOCDL) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\defset.cpp
DEP_DEFSE=\
	.\STDAFX.H\
	.\divelog.h\
	.\defset.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/defset.obj :  $(SOURCE)  $(DEP_DEFSE) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\toolbarx.cpp
DEP_TOOLB=\
	.\STDAFX.H\
	.\toolbarx.h

$(INTDIR)/toolbarx.obj :  $(SOURCE)  $(DEP_TOOLB) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\thghtdlg.cpp
DEP_THGHT=\
	.\STDAFX.H\
	.\divelog.h\
	.\thghtdlg.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/thghtdlg.obj :  $(SOURCE)  $(DEP_THGHT) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
# End Group
################################################################################
# Begin Group "Calendar Files"

################################################################################
# Begin Source File

SOURCE=.\Calendar.cpp
DEP_CALEN=\
	.\STDAFX.H\
	.\Calendar.h\
	.\toolbarx.h

$(INTDIR)/Calendar.obj :  $(SOURCE)  $(DEP_CALEN) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Calendlg.cpp
DEP_CALEND=\
	.\STDAFX.H\
	.\Calendlg.h\
	.\toolbarx.h\
	.\Calendar.h

$(INTDIR)/Calendlg.obj :  $(SOURCE)  $(DEP_CALEND) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Diagdlg.cpp
DEP_DIAGD=\
	.\STDAFX.H\
	.\Diagdlg.h\
	.\toolbarx.h\
	.\Diagscrl.h

$(INTDIR)/Diagdlg.obj :  $(SOURCE)  $(DEP_DIAGD) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Diagscrl.cpp
DEP_DIAGS=\
	.\STDAFX.H\
	.\Diagscrl.h\
	.\toolbarx.h

$(INTDIR)/Diagscrl.obj :  $(SOURCE)  $(DEP_DIAGS) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Editdate.cpp
DEP_EDITD=\
	.\STDAFX.H\
	.\Editdate.h\
	.\toolbarx.h\
	.\Calendar.h\
	.\Fauxcmb.h\
	.\Diagscrl.h

$(INTDIR)/Editdate.obj :  $(SOURCE)  $(DEP_EDITD) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fauxcmb.cpp
DEP_FAUXC=\
	.\STDAFX.H\
	.\Fauxcmb.h\
	.\toolbarx.h

$(INTDIR)/Fauxcmb.obj :  $(SOURCE)  $(DEP_FAUXC) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fauxdlg.cpp
DEP_FAUXD=\
	.\STDAFX.H\
	.\Fauxdlg.h\
	.\toolbarx.h\
	.\Fauxcmb.h

$(INTDIR)/Fauxdlg.obj :  $(SOURCE)  $(DEP_FAUXD) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
# End Group
################################################################################
# Begin Group "Report Files"

################################################################################
# Begin Source File

SOURCE=.\repdoc.cpp
DEP_REPDO=\
	.\STDAFX.H\
	.\divelog.h\
	.\DIVEDATA.H\
	.\reports.h\
	.\repdoc.h\
	.\repview.h\
	.\toolbarx.h\
	.\TABLES.H

!IF  "$(CFG)" == "Win32 Release"

$(INTDIR)/repdoc.obj :  $(SOURCE)  $(DEP_REPDO) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP Exclude_From_Build 0

$(INTDIR)/repdoc.obj :  $(SOURCE)  $(DEP_REPDO) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\repview.cpp
DEP_REPVI=\
	.\STDAFX.H\
	.\divelog.h\
	.\repdoc.h\
	.\repview.h\
	.\DIVEDATA.H\
	.\reports.h\
	.\mainfrm.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/repview.obj :  $(SOURCE)  $(DEP_REPVI) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\repwnd.cpp
DEP_REPWN=\
	.\STDAFX.H\
	.\divelog.h\
	.\repwnd.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/repwnd.obj :  $(SOURCE)  $(DEP_REPWN) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\reports.cpp
DEP_REPOR=\
	.\STDAFX.H\
	.\divelog.h\
	.\DIVEDATA.H\
	.\reports.h\
	.\Editdate.h\
	.\toolbarx.h\
	.\TABLES.H\
	.\Calendar.h\
	.\Fauxcmb.h\
	.\Diagscrl.h

$(INTDIR)/reports.obj :  $(SOURCE)  $(DEP_REPOR) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\reprtdlg.cpp
DEP_REPRT=\
	.\STDAFX.H\
	.\divelog.h\
	.\DIVEDATA.H\
	.\reports.h\
	.\reprtdlg.h\
	.\repdoc.h\
	.\filtdlg.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/reprtdlg.obj :  $(SOURCE)  $(DEP_REPRT) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\filtdlg.cpp
DEP_FILTD=\
	.\STDAFX.H\
	.\divelog.h\
	.\filtdlg.h\
	.\DIVEDATA.H\
	.\reports.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/filtdlg.obj :  $(SOURCE)  $(DEP_FILTD) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
# End Group
################################################################################
# Begin Group "Buddies Page Files"

################################################################################
# Begin Source File

SOURCE=.\buddata.cpp
DEP_BUDDA=\
	.\STDAFX.H\
	.\divelog.h\
	.\buddata.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/buddata.obj :  $(SOURCE)  $(DEP_BUDDA) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\buddypg.cpp
DEP_BUDDY=\
	.\STDAFX.H\
	.\divelog.h\
	.\buddypg.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/buddypg.obj :  $(SOURCE)  $(DEP_BUDDY) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
# End Group
################################################################################
# Begin Group "Diving Page Files"

################################################################################
# Begin Source File

SOURCE=.\DIVEDATA.CPP
DEP_DIVEDA=\
	.\STDAFX.H\
	.\DIVEDATA.H\
	.\toolbarx.h

$(INTDIR)/DIVEDATA.OBJ :  $(SOURCE)  $(DEP_DIVEDA) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\divepg.cpp
DEP_DIVEP=\
	.\STDAFX.H\
	.\divelog.h\
	.\divepg.h\
	.\DIVEDOC.H\
	.\divevw.h\
	.\Editdate.h\
	.\DIVEDATA.H\
	.\mainfrm.h\
	.\defset.h\
	.\notesdlg.h\
	.\toolbarx.h\
	.\TABLES.H\
	.\Calendar.h\
	.\Fauxcmb.h\
	.\Diagscrl.h

$(INTDIR)/divepg.obj :  $(SOURCE)  $(DEP_DIVEP) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\notesdlg.cpp
DEP_NOTES=\
	.\STDAFX.H\
	.\divelog.h\
	.\notesdlg.h\
	.\toolbarx.h\
	.\TABLES.H

$(INTDIR)/notesdlg.obj :  $(SOURCE)  $(DEP_NOTES) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TABLES.CPP
DEP_TABLE=\
	.\STDAFX.H\
	.\TABLES.H\
	.\toolbarx.h

$(INTDIR)/TABLES.OBJ :  $(SOURCE)  $(DEP_TABLE) $(INTDIR) $(INTDIR)/STDAFX.OBJ

# End Source File
# End Group
# End Project
################################################################################
