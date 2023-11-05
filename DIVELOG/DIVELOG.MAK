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
PROJPATH = E:\CPROJE~1\DIVERS\DIVELOG\
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
LIBS_D_WEXE = lafxcwd oldnames libw llibcew ctl3dv2.lib commdlg.lib shell.lib 
LIBS_R_WEXE = lafxcw oldnames libw llibcew ctl3dv2.lib commdlg.lib shell.lib 
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
		CALENDLG.SBR \
		CHECKBOX.SBR \
		COMMENTS.SBR \
		DIAGDLG.SBR \
		DIAGSCRL.SBR \
		DIVEDATA.SBR \
		DIVEDOC.SBR \
		DIVELOG.SBR \
		DIVEVW.SBR \
		DRWTOOLS.SBR \
		EDITDATE.SBR \
		FAUXCMB.SBR \
		FAUXDLG.SBR \
		FIELD.SBR \
		FORM.SBR \
		LOCATION.SBR \
		MAINFRM.SBR \
		CALENDER.SBR \
		TABLES.SBR \
		TOOLBAR.SBR \
		THGHTDLG.SBR


STDAFX_DEP = e:\cproje~1\divers\divelog\stdafx.h


CALENDLG_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\calender.h \
	e:\cproje~1\divers\divelog\calendlg.h


CHECKBOX_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\checkbox.h


COMMENTS_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\divelog.h \
	e:\cproje~1\divers\divelog\comments.h


DIAGDLG_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\diagscrl.h \
	e:\cproje~1\divers\divelog\diagdlg.h


DIAGSCRL_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\diagscrl.h


DIVEDATA_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\divedata.h \
	e:\cproje~1\divers\divelog\divedoc.h \
	e:\cproje~1\divers\divelog\tables.h


DIVEDOC_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\divelog.h \
	e:\cproje~1\divers\divelog\form.h \
	e:\cproje~1\divers\divelog\tables.h \
	e:\cproje~1\divers\divelog\location.h \
	e:\cproje~1\divers\divelog\divedata.h \
	e:\cproje~1\divers\divelog\divedoc.h


DIVELOG_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\divelog.h \
	e:\cproje~1\divers\divelog\mainfrm.h \
	e:\cproje~1\divers\divelog\divedoc.h \
	e:\cproje~1\divers\divelog\divevw.h \
	e:\cproje~1\divers\divelog\thghtdlg.h


DIVEVW_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\divelog.h \
	e:\cproje~1\divers\divelog\form.h \
	e:\cproje~1\divers\divelog\comments.h \
	e:\cproje~1\divers\divelog\checkbox.h \
	e:\cproje~1\divers\divelog\divedata.h \
	e:\cproje~1\divers\divelog\field.h \
	e:\cproje~1\divers\divelog\divedoc.h \
	e:\cproje~1\divers\divelog\divevw.h


DRWTOOLS_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\drwtools.h


EDITDATE_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\calender.h \
	e:\cproje~1\divers\divelog\fauxcmb.h \
	e:\cproje~1\divers\divelog\diagscrl.h \
	e:\cproje~1\divers\divelog\editdate.h


FAUXCMB_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\fauxcmb.h


FAUXDLG_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\fauxcmb.h \
	e:\cproje~1\divers\divelog\fauxdlg.h


FIELD_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\divedata.h \
	e:\cproje~1\divers\divelog\field.h \
	e:\cproje~1\divers\divelog\calender.h \
	e:\cproje~1\divers\divelog\calendlg.h \
	e:\cproje~1\divers\divelog\fauxcmb.h \
	e:\cproje~1\divers\divelog\diagscrl.h \
	e:\cproje~1\divers\divelog\editdate.h \
	e:\cproje~1\divers\divelog\divedoc.h


FORM_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\form.h \
	e:\cproje~1\divers\divelog\drwtools.h


LOCATION_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\divelog.h \
	e:\cproje~1\divers\divelog\location.h


MAINFRM_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\divelog.h \
	e:\cproje~1\divers\divelog\toolbar.h \
	e:\cproje~1\divers\divelog\mainfrm.h


CALENDER_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\calender.h


TABLES_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\tables.h


TOOLBAR_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\toolbar.h


DIVELOG_RCDEP = e:\cproje~1\divers\divelog\res\divelog.ico \
	e:\cproje~1\divers\divelog\res\picture.bmp \
	e:\cproje~1\divers\divelog\res\tank_ful.bmp \
	e:\cproje~1\divers\divelog\res\combo3.bmp \
	e:\cproje~1\divers\divelog\res\wetsuitu.bmp \
	e:\cproje~1\divers\divelog\res\wetsuitd.bmp \
	e:\cproje~1\divers\divelog\res\wavesu.bmp \
	e:\cproje~1\divers\divelog\res\wavesd.bmp \
	e:\cproje~1\divers\divelog\res\vis_poor.bmp \
	e:\cproje~1\divers\divelog\res\bmp00002.bmp \
	e:\cproje~1\divers\divelog\res\vis_ok.bmp \
	e:\cproje~1\divers\divelog\res\vis_okd.bmp \
	e:\cproje~1\divers\divelog\res\vis_good.bmp \
	e:\cproje~1\divers\divelog\res\bmp00001.bmp \
	e:\cproje~1\divers\divelog\res\usuitu.bmp \
	e:\cproje~1\divers\divelog\res\usuitd.bmp \
	e:\cproje~1\divers\divelog\res\surgeu.bmp \
	e:\cproje~1\divers\divelog\res\surged.bmp \
	e:\cproje~1\divers\divelog\res\surfd1.bmp \
	e:\cproje~1\divers\divelog\res\surfd.bmp \
	e:\cproje~1\divers\divelog\res\socksu.bmp \
	e:\cproje~1\divers\divelog\res\socksd.bmp \
	e:\cproje~1\divers\divelog\res\shoreu.bmp \
	e:\cproje~1\divers\divelog\res\shored.bmp \
	e:\cproje~1\divers\divelog\res\bmp00003.bmp \
	e:\cproje~1\divers\divelog\res\semidsui.bmp \
	e:\cproje~1\divers\divelog\res\semidryu.bmp \
	e:\cproje~1\divers\divelog\res\semidryd.bmp \
	e:\cproje~1\divers\divelog\res\saltu.bmp \
	e:\cproje~1\divers\divelog\res\saltd.bmp \
	e:\cproje~1\divers\divelog\res\mittensu.bmp \
	e:\cproje~1\divers\divelog\res\mittensd.bmp \
	e:\cproje~1\divers\divelog\res\hoodu.bmp \
	e:\cproje~1\divers\divelog\res\hoodd.bmp \
	e:\cproje~1\divers\divelog\res\glovesu.bmp \
	e:\cproje~1\divers\divelog\res\glovesd.bmp \
	e:\cproje~1\divers\divelog\res\freshu.bmp \
	e:\cproje~1\divers\divelog\res\freshd.bmp \
	e:\cproje~1\divers\divelog\res\dsuitu.bmp \
	e:\cproje~1\divers\divelog\res\dsuitd.bmp \
	e:\cproje~1\divers\divelog\res\currentu.bmp \
	e:\cproje~1\divers\divelog\res\currentd.bmp \
	e:\cproje~1\divers\divelog\res\costumeu.bmp \
	e:\cproje~1\divers\divelog\res\costumed.bmp \
	e:\cproje~1\divers\divelog\res\boatu.bmp \
	e:\cproje~1\divers\divelog\res\boatd.bmp \
	e:\cproje~1\divers\divelog\res\checkd.bmp \
	e:\cproje~1\divers\divelog\res\checku.bmp \
	e:\cproje~1\divers\divelog\res\splash.bmp \
	e:\cproje~1\divers\divelog\res\divelog.rc2


THGHTDLG_DEP = e:\cproje~1\divers\divelog\stdafx.h \
	e:\cproje~1\divers\divelog\divelog.h \
	e:\cproje~1\divers\divelog\thghtdlg.h


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

CALENDLG.OBJ:	CALENDLG.CPP $(CALENDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CALENDLG.CPP

CHECKBOX.OBJ:	CHECKBOX.CPP $(CHECKBOX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CHECKBOX.CPP

COMMENTS.OBJ:	COMMENTS.CPP $(COMMENTS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COMMENTS.CPP

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

DIVEVW.OBJ:	DIVEVW.CPP $(DIVEVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIVEVW.CPP

DRWTOOLS.OBJ:	DRWTOOLS.CPP $(DRWTOOLS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRWTOOLS.CPP

EDITDATE.OBJ:	EDITDATE.CPP $(EDITDATE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EDITDATE.CPP

FAUXCMB.OBJ:	FAUXCMB.CPP $(FAUXCMB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FAUXCMB.CPP

FAUXDLG.OBJ:	FAUXDLG.CPP $(FAUXDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FAUXDLG.CPP

FIELD.OBJ:	FIELD.CPP $(FIELD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FIELD.CPP

FORM.OBJ:	FORM.CPP $(FORM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FORM.CPP

LOCATION.OBJ:	LOCATION.CPP $(LOCATION_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LOCATION.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

CALENDER.OBJ:	CALENDER.CPP $(CALENDER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CALENDER.CPP

TABLES.OBJ:	TABLES.CPP $(TABLES_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TABLES.CPP

TOOLBAR.OBJ:	TOOLBAR.CPP $(TOOLBAR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TOOLBAR.CPP

DIVELOG.RES:	DIVELOG.RC $(DIVELOG_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DIVELOG.RC

THGHTDLG.OBJ:	THGHTDLG.CPP $(THGHTDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c THGHTDLG.CPP


$(PROJ).EXE::	DIVELOG.RES

$(PROJ).EXE::	STDAFX.OBJ CALENDLG.OBJ CHECKBOX.OBJ COMMENTS.OBJ DIAGDLG.OBJ DIAGSCRL.OBJ \
	DIVEDATA.OBJ DIVEDOC.OBJ DIVELOG.OBJ DIVEVW.OBJ DRWTOOLS.OBJ EDITDATE.OBJ FAUXCMB.OBJ \
	FAUXDLG.OBJ FIELD.OBJ FORM.OBJ LOCATION.OBJ MAINFRM.OBJ CALENDER.OBJ TABLES.OBJ TOOLBAR.OBJ \
	THGHTDLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
CALENDLG.OBJ +
CHECKBOX.OBJ +
COMMENTS.OBJ +
DIAGDLG.OBJ +
DIAGSCRL.OBJ +
DIVEDATA.OBJ +
DIVEDOC.OBJ +
DIVELOG.OBJ +
DIVEVW.OBJ +
DRWTOOLS.OBJ +
EDITDATE.OBJ +
FAUXCMB.OBJ +
FAUXDLG.OBJ +
FIELD.OBJ +
FORM.OBJ +
LOCATION.OBJ +
MAINFRM.OBJ +
CALENDER.OBJ +
TABLES.OBJ +
TOOLBAR.OBJ +
THGHTDLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
e:\msvc\lib\+
e:\msvc\mfc\lib\+
g:\msvc\lib\+
g:\msvc\mfc\lib\+
d:\odbcsdk\lib\+
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
