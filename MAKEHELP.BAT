@echo off
REM -- First make map file from App Studio generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DIVELOG.HPJ. >hlp\divelog.hm
echo. >>hlp\divelog.hm
echo // Commands (ID_* and IDM_*) >>hlp\divelog.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\divelog.hm
echo. >>hlp\divelog.hm
echo // Prompts (IDP_*) >>hlp\divelog.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\divelog.hm
echo. >>hlp\divelog.hm
echo // Resources (IDR_*) >>hlp\divelog.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\divelog.hm
echo. >>hlp\divelog.hm
echo // Dialogs (IDD_*) >>hlp\divelog.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\divelog.hm
echo. >>hlp\divelog.hm
echo // Frame Controls (IDW_*) >>hlp\divelog.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\divelog.hm
REM -- Make help for Project DIVELOG
call hc31 divelog.hpj
echo.
