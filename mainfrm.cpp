// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "divelog.h"

#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BOOL CMainFrame::bVGA = TRUE;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_INDEX, CMDIFrameWnd::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, CMDIFrameWnd::OnHelpUsing)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpIndex)
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
	ID_FILE_PRINT_PREVIEW,
	ID_FILE_PRINT,
		ID_SEPARATOR,
	IDM_DIVE_NEW,
	IDM_DIVE_REMOVE,
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
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if( !m_wndDlgBar.Create( this, IDD_DIALOG_BAR, CBRS_LEFT, IDD_DIALOG_BAR ) )
	{
		TRACE( "Failed to create dialog bar\n" );
		return -1;		// fail to create
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
#ifdef WIN32
	lpMMI->ptMaxSize = CPoint( 640, 490 );
	lpMMI->ptMaxTrackSize = CPoint( 640, 480 );
#else
	int xBorder, yBorder, xScreen, yScreen, x, y;
	xScreen = ::GetSystemMetrics( SM_CXSCREEN );
	yScreen = ::GetSystemMetrics( SM_CYSCREEN );
	xBorder = ::GetSystemMetrics( SM_CXDLGFRAME );
	yBorder = ::GetSystemMetrics( SM_CYDLGFRAME );

	if( xScreen > 800 )	xScreen = 800;
	if( yScreen > 600 )	yScreen = 600;
	
	x = xScreen+(xBorder*2);
	y = yScreen+(yBorder*2);
	
	lpMMI->ptMaxSize = CPoint( x, y );
	lpMMI->ptMaxTrackSize = CPoint( x, y );

	if( xScreen == 640 ) CMainFrame::bVGA = TRUE;
	if( xScreen == 800 ) CMainFrame::bVGA = FALSE;
	
	//char buf[20];
	//wsprintf( buf, "x = %d, y = %d", x, y );
	//AfxMessageBox( buf );
#endif

	CMDIFrameWnd::OnGetMinMaxInfo(lpMMI);
}
/////////////////////////////////////////////////////////////////////////////
// CDlgBar

CDlgBar::CDlgBar()
{
	m_nBinFrame = 0;
}

CDlgBar::~CDlgBar()
{
}


BEGIN_MESSAGE_MAP(CDlgBar, CDialogBar)
	//{{AFX_MSG_MAP(CDlgBar)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgBar message handlers

void CDlgBar::AnimateBin() 
{
	BeginWaitCursor();
	SetTimer( ID_BINTIMER, 25, NULL );
}

void CDlgBar::OnTimer( UINT nIDEvent )
{
	CDialogBar::OnPaint();

	if( nIDEvent==ID_BINTIMER )
	{
		m_nBinFrame++;
		DrawBin( m_nBinFrame );
		if( m_nBinFrame==13 )
		{
			KillTimer( ID_BINTIMER );
			m_nBinFrame=0;
			EndWaitCursor();
		}
	}
}

void CDlgBar::DrawBin( int nFrame )
{
	ASSERT( nFrame>=0 && nFrame<=13 );
	CClientDC dc(this); // device context for painting
	
	nFrame = (nFrame==13) ? 0 : nFrame;

	CDC* pDisplayMemDC = new CDC;
	CBitmap* pBin = new CBitmap;
	pBin->LoadBitmap( IDB_BIN );
	pDisplayMemDC->CreateCompatibleDC( &dc );
	
	CBitmap* pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject( pBin );

	if( CMainFrame::bVGA )
		dc.BitBlt( 15, 315, 38, 68, pDisplayMemDC, 38*nFrame, 0, SRCCOPY );
	else
		dc.BitBlt( 15, 435, 38, 68, pDisplayMemDC, 38*nFrame, 0, SRCCOPY );

	delete pDisplayMemDC->SelectObject( pOldBitmap );	// deletes pTanks	38*nFrame
	delete pDisplayMemDC;
	//InvalidateRect( CRect( 15, 315, 53, 383 ), FALSE );
}

void CDlgBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	DrawBin( 0 );
	// Do not call CDialogBar::OnPaint() for painting messages
}
