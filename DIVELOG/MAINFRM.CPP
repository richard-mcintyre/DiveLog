// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "divelog.h"
#include "toolbar.h"

#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CFrameWnd* CMainFrame::m_pthis = NULL;
	
/////////////////////////////////////////////////////////////////////////////
// CMainFrame


IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_TOOLBAR_PROP, OnToolbarProp)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_INDEX, CFrameWnd::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, CFrameWnd::OnHelpUsing)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpIndex)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_RECORD_ADD,
	ID_RECORD_DELETE,
		ID_SEPARATOR,
	IDM_RECORD_FIRST,
	IDM_RECORD_PREV,
	IDM_RECORD_NEXT,
	IDM_RECORD_LAST,
		ID_SEPARATOR,
	ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pWndToolBar = new CLSToolBar;
}

CMainFrame::~CMainFrame()
{
	delete m_pWndToolBar;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_pWndToolBar->Create(this) ||
		!m_pWndToolBar->LoadBitmap(IDR_MAINFRAME) ||
		!m_pWndToolBar->SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	else
	{
		m_toolTips.Add( "New" );		m_toolTips.Add( "Open" );
		m_toolTips.Add( "Save" );		m_toolTips.Add( "" );
		m_toolTips.Add( "Add Dive" );	m_toolTips.Add( "Remove Dive" );
		m_toolTips.Add( "" );			m_toolTips.Add( "First Dive" );
		m_toolTips.Add( "Previous Dive" );		m_toolTips.Add( "Next Dive" );
		m_toolTips.Add( "Last Dive" );	m_toolTips.Add( "" );
		m_toolTips.Add( "About" );
		
		m_pWndToolBar->SetTipsText( &m_toolTips );
		m_pWndToolBar->SetNoOfButtons( sizeof(buttons)/sizeof(UINT) );
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	// Center the main window
	SetWindowPos( NULL, 0, 0, 648, 480, SWP_NOZORDER|SWP_NOMOVE );
	CenterWindow();
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMaxSize = CPoint( 640, 480 );
	lpMMI->ptMaxTrackSize = CPoint( 640, 480 );
	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
	CMainFrame::m_pthis = this;
}


void CMainFrame::OnToolbarProp()
{
	m_pWndToolBar->ShowProperties();
}
