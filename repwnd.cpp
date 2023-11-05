// repwnd.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "repwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportWnd

IMPLEMENT_DYNCREATE(CReportWnd, CMDIChildWnd)

CReportWnd::CReportWnd()
{
}

CReportWnd::~CReportWnd()
{
}


BEGIN_MESSAGE_MAP(CReportWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CReportWnd)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

		  /*
// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_REPORT_OPEN,
	ID_REPORT_SAVE,
		ID_SEPARATOR,
	ID_FILE_PRINT_PREVIEW,
	ID_FILE_PRINT,
};	   */

/////////////////////////////////////////////////////////////////////////////
// CReportWnd message handlers

int CReportWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	 /*
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_REPORT) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("Failed to create report toolbar\n");
		return -1;      // fail to create
	}

#ifdef WIN32
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
#endif
		*/	
	return 0;
}
