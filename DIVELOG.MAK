# Microsoft Visual C++ generated build script - Do not modify

PROJ = DIVELOG
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\PROJECTS\DIVE20\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /GA /Fd"DIVELOG.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AL /O1 /D "NDEBUG" /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = lafxcwd mfco250d oldnames libw llibcew compobj storage ole2 ole2disp ole2nls mfcoleui ctl3dv2 commdlg.lib shell.lib 
LIBS_R_WEXE = lafxcw oldnames libw llibcew ctl3dv2 commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = DIVELOG.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		BUDDATA.SBR \
		BUDDYPG.SBR \
		CALENDAR.SBR \
		CALENDLG.SBR \
		DEFSET.SBR \
		DIAGDLG.SBR \
		DIAGSCRL.SBR \
		DIVEDATA.SBR \
		DIVEDOC.SBR \
		DIVELOG.SBR \
		DIVEPG.SBR \
		DIVEVW.SBR \
		EDITDATE.SBR \
		FAUXCMB.SBR \
		FAUXDLG.SBR \
		FILTDLG.SBR \
		FRONTPG.SBR \
		LOCDLG.SBR \
		MAINFRM.SBR \
		NOTESDLG.SBR \
		REPDOC.SBR \
		REPORTS.SBR \
		REPRTDLG.SBR \
		REPVIEW.SBR \
		REPWND.SBR \
		BACKPG.SBR \
		TABLES.SBR \
		THGHTDLG.SBR \
		TOOLBARX.SBR


STDAFX_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h


BUDDATA_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\buddata.h


BUDDYPG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\buddypg.h \
	d:\projects\dive20\mainfrm.h \
	d:\projects\dive20\divedoc.h \
	d:\projects\dive20\divevw.h \
	d:\projects\dive20\buddata.h


CALENDAR_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\calendar.h


CALENDLG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\calendlg.h \
	d:\projects\dive20\calendar.h


DEFSET_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\defset.h


DIAGDLG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\diagdlg.h \
	d:\projects\dive20\diagscrl.h


DIAGSCRL_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\diagscrl.h


DIVEDATA_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divedata.h


DIVEDOC_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\divedoc.h \
	d:\projects\dive20\divevw.h \
	d:\projects\dive20\divedata.h \
	d:\projects\dive20\buddata.h \
	d:\projects\dive20\defset.h \
	d:\projects\dive20\divepg.h


DIVELOG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divedata.h \
	d:\projects\dive20\reports.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\mainfrm.h \
	d:\projects\dive20\divedoc.h \
	d:\projects\dive20\divevw.h \
	d:\projects\dive20\repwnd.h \
	d:\projects\dive20\repdoc.h \
	d:\projects\dive20\repview.h \
	d:\projects\dive20\thghtdlg.h \
	d:\msvc\include\ctl3d.h


DIVEPG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\divepg.h \
	d:\projects\dive20\divedoc.h \
	d:\projects\dive20\divevw.h \
	d:\projects\dive20\editdate.h \
	d:\projects\dive20\calendar.h \
	d:\projects\dive20\fauxcmb.h \
	d:\projects\dive20\diagscrl.h \
	d:\projects\dive20\divedata.h \
	d:\projects\dive20\mainfrm.h \
	d:\projects\dive20\defset.h \
	d:\projects\dive20\notesdlg.h


DIVEVW_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\divedoc.h \
	d:\projects\dive20\divevw.h \
	d:\projects\dive20\frontpg.h \
	d:\projects\dive20\backpg.h \
	d:\projects\dive20\divepg.h \
	d:\projects\dive20\buddypg.h \
	d:\projects\dive20\editdate.h \
	d:\projects\dive20\calendar.h \
	d:\projects\dive20\fauxcmb.h \
	d:\projects\dive20\diagscrl.h \
	d:\projects\dive20\locdlg.h \
	d:\projects\dive20\defset.h \
	d:\projects\dive20\mainfrm.h \
	d:\projects\dive20\divedata.h \
	d:\projects\dive20\buddata.h \
	d:\projects\dive20\reprtdlg.h


EDITDATE_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\editdate.h \
	d:\projects\dive20\calendar.h \
	d:\projects\dive20\fauxcmb.h \
	d:\projects\dive20\diagscrl.h


FAUXCMB_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\fauxcmb.h


FAUXDLG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\fauxdlg.h \
	d:\projects\dive20\fauxcmb.h


FILTDLG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\filtdlg.h \
	d:\projects\dive20\divedata.h \
	d:\projects\dive20\reports.h


FRONTPG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\frontpg.h \
	d:\projects\dive20\divedoc.h \
	d:\projects\dive20\divevw.h \
	d:\projects\dive20\mainfrm.h


LOCDLG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\locdlg.h


MAINFRM_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\mainfrm.h


NOTESDLG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\notesdlg.h


REPDOC_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\divedata.h \
	d:\projects\dive20\reports.h \
	d:\projects\dive20\repdoc.h \
	d:\projects\dive20\repview.h


REPORTS_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\divedata.h \
	d:\projects\dive20\reports.h \
	d:\projects\dive20\editdate.h \
	d:\projects\dive20\calendar.h \
	d:\projects\dive20\fauxcmb.h \
	d:\projects\dive20\diagscrl.h


REPRTDLG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\divedata.h \
	d:\projects\dive20\reports.h \
	d:\projects\dive20\reprtdlg.h \
	d:\projects\dive20\repdoc.h \
	d:\projects\dive20\filtdlg.h


REPVIEW_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\repdoc.h \
	d:\projects\dive20\repview.h \
	d:\projects\dive20\divedata.h \
	d:\projects\dive20\reports.h \
	d:\projects\dive20\mainfrm.h


REPWND_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\repwnd.h


BACKPG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\backpg.h


TABLES_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\tables.h


THGHTDLG_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h \
	d:\projects\dive20\divelog.h \
	d:\projects\dive20\tables.h \
	d:\projects\dive20\thghtdlg.h


TOOLBARX_DEP = d:\projects\dive20\stdafx.h \
	d:\projects\dive20\toolbarx.h


DIVELOG_RCDEP = d:\projects\dive20\res\divelog.ico \
	d:\projects\dive20\res\divedoc.ico \
	d:\projects\dive20\res\bin.ico \
	d:\projects\dive20\res\idr_repo.ico \
	d:\projects\dive20\res\tank_ful.bmp \
	d:\projects\dive20\res\picture.bmp \
	d:\projects\dive20\res\front_pg.bmp \
	d:\projects\dive20\res\bmp00001.bmp \
	d:\projects\dive20\res\bin.bmp \
	d:\projects\dive20\res\bitmap1.bmp \
	d:\projects\dive20\res\cursor1.cur \
	d:\projects\dive20\res\cur00001.cur \
	d:\projects\dive20\res\divelog.rc2


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

BUDDATA.OBJ:	BUDDATA.CPP $(BUDDATA_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BUDDATA.CPP

BUDDYPG.OBJ:	BUDDYPG.CPP $(BUDDYPG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BUDDYPG.CPP

CALENDAR.OBJ:	CALENDAR.CPP $(CALENDAR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CALENDAR.CPP

CALENDLG.OBJ:	CALENDLG.CPP $(CALENDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CALENDLG.CPP

DEFSET.OBJ:	DEFSET.CPP $(DEFSET_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DEFSET.CPP

DIAGDLG.OBJ:	DIAGDLG.CPP $(DIAGDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIAGDLG.CPP

DIAGSCRL.OBJ:	DIAGSCRL.CPP $(DIAGSCRL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIAGSCRL.CPP

DIVEDATA.OBJ:	DIVEDATA.CPP $(DIVEDATA_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIVEDATA.CPP

DIVEDOC.OBJ:	DIVEDOC.CPP $(DIVEDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIVEDOC.CPP

DIVELOG.OBJ:	DIVELOG.CPP $(DIVELOG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIVELOG.CPP

DIVEPG.OBJ:	DIVEPG.CPP $(DIVEPG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIVEPG.CPP

DIVEVW.OBJ:	DIVEVW.CPP $(DIVEVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIVEVW.CPP

EDITDATE.OBJ:	EDITDATE.CPP $(EDITDATE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EDITDATE.CPP

FAUXCMB.OBJ:	FAUXCMB.CPP $(FAUXCMB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FAUXCMB.CPP

FAUXDLG.OBJ:	FAUXDLG.CPP $(FAUXDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FAUXDLG.CPP

FILTDLG.OBJ:	FILTDLG.CPP $(FILTDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FILTDLG.CPP

FRONTPG.OBJ:	FRONTPG.CPP $(FRONTPG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FRONTPG.CPP

LOCDLG.OBJ:	LOCDLG.CPP $(LOCDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LOCDLG.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

NOTESDLG.OBJ:	NOTESDLG.CPP $(NOTESDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c NOTESDLG.CPP

REPDOC.OBJ:	REPDOC.CPP $(REPDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REPDOC.CPP

REPORTS.OBJ:	REPORTS.CPP $(REPORTS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REPORTS.CPP

REPRTDLG.OBJ:	REPRTDLG.CPP $(REPRTDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REPRTDLG.CPP

REPVIEW.OBJ:	REPVIEW.CPP $(REPVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REPVIEW.CPP

REPWND.OBJ:	REPWND.CPP $(REPWND_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REPWND.CPP

BACKPG.OBJ:	BACKPG.CPP $(BACKPG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BACKPG.CPP

TABLES.OBJ:	TABLES.CPP $(TABLES_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TABLES.CPP

THGHTDLG.OBJ:	THGHTDLG.CPP $(THGHTDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c THGHTDLG.CPP

TOOLBARX.OBJ:	TOOLBARX.CPP $(TOOLBARX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TOOLBARX.CPP

DIVELOG.RES:	DIVELOG.RC $(DIVELOG_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DIVELOG.RC


$(PROJ).EXE::	DIVELOG.RES

$(PROJ).EXE::	STDAFX.OBJ BUDDATA.OBJ BUDDYPG.OBJ CALENDAR.OBJ CALENDLG.OBJ DEFSET.OBJ \
	DIAGDLG.OBJ DIAGSCRL.OBJ DIVEDATA.OBJ DIVEDOC.OBJ DIVELOG.OBJ DIVEPG.OBJ DIVEVW.OBJ \
	EDITDATE.OBJ FAUXCMB.OBJ FAUXDLG.OBJ FILTDLG.OBJ FRONTPG.OBJ LOCDLG.OBJ MAINFRM.OBJ \
	NOTESDLG.OBJ REPDOC.OBJ REPORTS.OBJ REPRTDLG.OBJ REPVIEW.OBJ REPWND.OBJ BACKPG.OBJ \
	TABLES.OBJ THGHTDLG.OBJ TOOLBARX.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
BUDDATA.OBJ +
BUDDYPG.OBJ +
CALENDAR.OBJ +
CALENDLG.OBJ +
DEFSET.OBJ +
DIAGDLG.OBJ +
DIAGSCRL.OBJ +
DIVEDATA.OBJ +
DIVEDOC.OBJ +
DIVELOG.OBJ +
DIVEPG.OBJ +
DIVEVW.OBJ +
EDITDATE.OBJ +
FAUXCMB.OBJ +
FAUXDLG.OBJ +
FILTDLG.OBJ +
FRONTPG.OBJ +
LOCDLG.OBJ +
MAINFRM.OBJ +
NOTESDLG.OBJ +
REPDOC.OBJ +
REPORTS.OBJ +
REPRTDLG.OBJ +
REPVIEW.OBJ +
REPWND.OBJ +
BACKPG.OBJ +
TABLES.OBJ +
THGHTDLG.OBJ +
TOOLBARX.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\msvc\lib\+
d:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) DIVELOG.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	DIVELOG.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DIVELOG.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
