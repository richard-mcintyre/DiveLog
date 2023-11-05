// divevw.cpp : implementation of the CDiveView class
//

#include "stdafx.h"
#include "divelog.h"

#include "divedoc.h"
#include "divevw.h"
#include "frontpg.h"
#include "backpg.h"
#include "divepg.h"
#include "buddypg.h"
#include "editdate.h"
#include "locdlg.h"
#include "defset.h"
#include "mainfrm.h"
#include "divedata.h"
#include "buddata.h"
#include "reprtdlg.h"
#include <afxext.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
									   /*
CLIPFORMAT CDiveView::m_cbDive = 
		(CLIPFORMAT)::RegisterClipboardFormat( "Dive Log V2.0" );
									 */
/////////////////////////////////////////////////////////////////////////////
// CDiveView

IMPLEMENT_DYNCREATE(CDiveView, CScrollView)

#define new DEBUG_NEW

BEGIN_MESSAGE_MAP(CDiveView, CScrollView)
	//{{AFX_MSG_MAP(CDiveView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(IDM_DIVE_NEW, OnDiveNew)
	ON_COMMAND(IDM_RECORD_PREV, OnRecordPrev)
	ON_COMMAND(IDM_RECORD_NEXT, OnRecordNext)
	ON_COMMAND(IDM_RECORD_FIRST, OnRecordFirst)
	ON_COMMAND(IDM_RECORD_LAST, OnRecordLast)
	ON_UPDATE_COMMAND_UI(IDM_RECORD_FIRST, OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(IDM_RECORD_PREV, OnUpdateRecordPrev)
	ON_UPDATE_COMMAND_UI(IDM_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(IDM_RECORD_LAST, OnUpdateRecordLast)
	ON_COMMAND(IDM_EDIT_LOCATIONS, OnEditLocations)
	ON_COMMAND(IDM_DEF_SETTTINGS, OnDefSetttings)
	ON_COMMAND(IDM_REPORTS, OnReports)
	ON_COMMAND(IDM_DIVE_REMOVE, OnDiveRemove)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_FILE_PRINT_BLANK, OnFilePrintBlank)
	ON_UPDATE_COMMAND_UI(IDM_DEF_SETTTINGS, OnUpdateDefSetttings)
	ON_UPDATE_COMMAND_UI(IDM_DIVE_NEW, OnUpdateDiveNew)
	ON_UPDATE_COMMAND_UI(IDM_DIVE_REMOVE, OnUpdateDiveRemove)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_BN_CLICKED( IDC_NEXTPAGE, OnNextPageClicked )
	ON_BN_CLICKED( IDC_PREVPAGE, OnPrevPageClicked )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiveView construction/destruction

CDiveView::CDiveView()
{
	m_curSection = CDiveView::Front;
	m_pFrontPg = new CFrontPg;
	m_pBackPg = new CBackPg;
	m_pDivePg1 = new CDivePg1;
	m_pDivePg2 = new CDivePg2;
	m_pBuddyPg1 = new CBuddyP1;
	m_pBuddyPg2 = new CBuddyP2;
	m_rightPgRect.SetRectEmpty();
	m_leftPgRect.SetRectEmpty();
	m_tmpPoint = CPoint( 0, 0 );
	m_leftDiveTab.SetRectEmpty();
	m_rightDiveTab.SetRectEmpty();
	m_leftBuddyTab.SetRectEmpty();
	m_rightBuddyTab.SetRectEmpty();
	m_coverRect.SetRectEmpty();
	m_bLDiveTab = m_bRDiveTab = FALSE;
	m_rectDraw.SetRectEmpty();
	m_size = CSize( 0, 0 );
	m_bBlank = FALSE;
	m_bLBuddyTab = m_bRBuddyTab = FALSE;
}

CDiveView::~CDiveView()
{
	m_pFrontPg->DestroyWindow();
	m_pBackPg->DestroyWindow();
	m_pDivePg1->DestroyWindow();
	m_pDivePg2->DestroyWindow();
	m_pBuddyPg1->DestroyWindow();
	m_pBuddyPg2->DestroyWindow();
	delete m_pFrontPg;
	delete m_pBackPg;
	delete m_pDivePg1;
	delete m_pDivePg2;
	delete m_pBuddyPg1;
	delete m_pBuddyPg2;
}

void CDiveView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	//SetScrollSizes( MM_TEXT, CSize( 387, 378 ) );
#ifdef WIN32
	SetScrollSizes( MM_TEXT, CSize( 562, 382 ) );
	m_pFrontPg->Create( this, IDD_WIN95_FRONT_PAGE );
	m_pBackPg->Create( this, IDD_WIN95_BACK_PAGE );
	m_pDivePg1->Create( this, IDD_WIN95_DIVE_PAGE1 );
	m_pDivePg2->Create( this, IDD_WIN95_DIVE_PAGE2 );
	m_pBuddyPg1->Create( this, IDD_WIN95_BUDDY_PAGE1 );
	m_pBuddyPg2->Create( this, IDD_WIN95_BUDDY_PAGE2 );
#else
	if( CMainFrame::bVGA )
	{
		SetScrollSizes( MM_TEXT, CSize( 556, 388 ) );
		m_pFrontPg->Create( this, IDD_FRONT_PAGE );
		m_pBackPg->Create( this, IDD_BACK_PAGE );
		m_pDivePg1->Create( this, IDD_DIVE_PAGE1 );
		m_pDivePg2->Create( this, IDD_DIVE_PAGE2 );
		m_pBuddyPg1->Create( this, IDD_BUDDY_PAGE1 );
		m_pBuddyPg2->Create( this, IDD_BUDDY_PAGE2 );
	}
	else
	{
		SetScrollSizes( MM_TEXT, CSize( 716, 508 ) );
		m_pFrontPg->Create( this, IDD_FRONT_PAGE_800 );
		m_pBackPg->Create( this, IDD_BACK_PAGE_800 );
		m_pDivePg1->Create( this, IDD_DIVE_PAGE1_800 );
		m_pDivePg2->Create( this, IDD_DIVE_PAGE2_800 );
		m_pBuddyPg1->Create( this, IDD_BUDDY_PAGE1_800 );
		m_pBuddyPg2->Create( this, IDD_BUDDY_PAGE2_800 );
	}
#endif

	int l, r;
	if( CMainFrame::bVGA )
	{	l = 38;	r = 315;	}
	else
	{	l = 38;	r = 395;	}

	m_pFrontPg->SetWindowPos( NULL, r, 27, 0, 0, SWP_NOZORDER|SWP_NOSIZE );
	m_pFrontPg->ShowWindow( TRUE );
		
	m_pBackPg->SetWindowPos( NULL, l, 27, 0, 0, SWP_NOZORDER|SWP_NOSIZE );
	m_pDivePg1->SetWindowPos( NULL, l, 27, 0, 0, SWP_NOZORDER|SWP_NOSIZE );
	m_pDivePg2->SetWindowPos( NULL, r, 27, 0, 0, SWP_NOZORDER|SWP_NOSIZE );

	m_pBuddyPg1->SetWindowPos( NULL, l, 27, 0, 0, SWP_NOZORDER|SWP_NOSIZE );
	m_pBuddyPg2->SetWindowPos( NULL, r, 27, 0, 0, SWP_NOZORDER|SWP_NOSIZE );

	m_bLDiveTab = FALSE;	m_bRDiveTab = TRUE;
	m_bLBuddyTab = FALSE;	m_bRBuddyTab = TRUE;
#ifdef WIN32
	m_nextPage.Create( "", BS_OWNERDRAW|WS_CHILD|WS_VISIBLE, CRect( 510, 346, 528, 364 ), this, IDC_NEXTPAGE );
	m_prevPage.Create( "", BS_OWNERDRAW|WS_CHILD, CRect( 30, 346, 48, 364 ), this, IDC_PREVPAGE );
#else
	CRect prevPagePos;	CRect nextPagePos;
	if( CMainFrame::bVGA )
	{	prevPagePos = CRect( 30, 347, 48, 365 );	nextPagePos = CRect( 500, 347, 518, 365 );	}
	else
	{	prevPagePos = CRect( 30, 467, 48, 485 );	nextPagePos = CRect( 660, 467, 678, 485 );	}
	
	m_nextPage.Create( "", BS_OWNERDRAW|WS_CHILD|WS_VISIBLE, nextPagePos, this, IDC_NEXTPAGE );
	m_prevPage.Create( "", BS_OWNERDRAW|WS_CHILD, prevPagePos, this, IDC_PREVPAGE );
#endif
	m_nextPage.LoadBitmaps( "IDB_NEXTPAGE" );
	m_prevPage.LoadBitmaps( "IDB_PREVPAGE" );
	
	m_pFrontPg->m_ctlEdit.SetWindowText( GetDocument()->GetFrontText( ) );
//	if( m_bUpdate )
//		AfxMessageBox( "Need to update controls" );

	// Calculate the tab rectangles
	CRect viewRect( 0, 0, m_size.cx, m_size.cy );	//( 0, 0, 556, 388 );
	viewRect.InflateRect( -viewRect.left, -viewRect.top );	viewRect.left = 0;	viewRect.top = 0;
	CRect coverRect = viewRect;		//coverRect.InflateRect( -10, -10 );
#ifdef WIN32
	CRect rightPgRect( (coverRect.Width()/2)+15, coverRect.top+10,
							(coverRect.Width()/2)+(coverRect.Width()/2)-20, coverRect.bottom-15 );
	CRect leftPgRect( coverRect.left+20, coverRect.top+10,
							(coverRect.Width()/2)-5, coverRect.bottom-15 );
#else
	CRect rightPgRect( (coverRect.Width()/2)+15, coverRect.top+10,
							(coverRect.Width()/2)+(coverRect.Width()/2)-130, coverRect.bottom-20 );
	CRect leftPgRect( coverRect.left+20, coverRect.top+10,
							(coverRect.Width()/2)-5, coverRect.bottom-20 );
#endif

	CClientDC dc( this );
	m_rightDiveTab = DrawTab( CPoint( rightPgRect.right-1, m_rightPgRect.top ),
												"DIVING", FALSE, TRUE, RGB( 0, 255, 0 ), &dc, FALSE );
	m_leftDiveTab = DrawTab( CPoint( leftPgRect.left, m_leftPgRect.top ),
												"DIVING", TRUE, FALSE, RGB( 0, 255, 0 ), &dc, FALSE );
	m_rightBuddyTab = DrawTab( CPoint( rightPgRect.right-1, rightPgRect.top + 70 ), 
													"BUDDIES", FALSE, TRUE, RGB( 255, 255, 128 ), &dc, FALSE  );
	m_leftBuddyTab = DrawTab( CPoint( leftPgRect.left, leftPgRect.top + 70 ),
													"BUDDIES", FALSE, FALSE, RGB( 255, 255, 128 ), &dc, FALSE  );
}

/////////////////////////////////////////////////////////////////////////////
// CDiveView drawing

void CDiveView::OnDraw(CDC* pDC)
{
	CDiveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	                      
	// Draw the background
	CBrush redBrush;	redBrush.CreateSolidBrush( RGB( 128, 0, 0 ) );
	CBrush grayBrush;	grayBrush.CreateSolidBrush( RGB( 192, 192, 192 ) );
	CPen nullPen;	nullPen.CreatePen( PS_NULL, 1, RGB( 0, 0, 0 ) );
	CBrush* pOldBrush = pDC->SelectObject( &redBrush );
	CPen* pOldPen = pDC->SelectObject( &nullPen );

	//CRect viewRect;	GetWindowRect( viewRect );
	//CRect viewRect( 0, 0, 563, 389 );
	CRect viewRect( 0, 0, m_size.cx, m_size.cy );

	viewRect.InflateRect( -viewRect.left, -viewRect.top );
	viewRect.left = 0;	viewRect.top = 0;
	pDC->Rectangle( 0, 0, viewRect.Width(), viewRect.Height() );

	// Draw the cover
	CBrush dkGrayBrush;	dkGrayBrush.CreateSolidBrush( RGB( 128, 128, 128 ) );
	CBrush blkBrush;	blkBrush.CreateSolidBrush( RGB( 0, 0, 0 ) );
	CPen grayPen;		grayPen.CreatePen( PS_SOLID, 1, RGB( 192, 192, 192 ) );
	CPen blkPen;		blkPen.CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	CRect coverRect = viewRect;	coverRect.InflateRect( -10, -10 );
	pDC->SelectObject( &blkBrush );
	pDC->RoundRect( 12, 12, coverRect.Width() + 10, coverRect.Height() + 10, 20, 20 );
	pDC->SelectObject( &dkGrayBrush );
	pDC->SelectObject( &blkPen );
	pDC->RoundRect( 7, 7, coverRect.Width() + 5, coverRect.Height() + 5, 20, 20 );
	pDC->SelectObject( &grayPen );
	pDC->MoveTo( 17, coverRect.Height()+4 );	pDC->LineTo( coverRect.Width()-5, coverRect.Height()+4 );
	pDC->MoveTo( coverRect.Width()+4, 17 );	pDC->LineTo( coverRect.Width()+4, coverRect.Height()-5 );
	
	m_coverRect = coverRect;
	
	// Draw the centre of the cover
	CBrush whtBrush;	whtBrush.CreateSolidBrush( RGB( 255, 255, 255 ) );
	int nOffset = (coverRect.Width()/2)-40;
	pDC->MoveTo( 5+nOffset, 8 );	pDC->LineTo( 5+nOffset, coverRect.Height()+4 );
	pDC->MoveTo( 5+coverRect.Width()-nOffset, 8 );	pDC->LineTo( 5+coverRect.Width()-nOffset, coverRect.Height()+4 );
	pDC->SelectObject( &blkPen );
	CRect centerRect( 5+nOffset, 8, 5+coverRect.Width()-nOffset, coverRect.Height()+4 );
	centerRect.InflateRect( -10, -40 );	//centerRect.OffsetRect( 10, 30 );
	pDC->RoundRect( centerRect, CPoint( centerRect.Width(), centerRect.Width() ) );
	pDC->SelectObject( &whtBrush );	pDC->SelectObject( &nullPen );
	pDC->RoundRect( centerRect.left+10, centerRect.top+30, centerRect.left+15, centerRect.bottom-30, 5, 5 );

	// Draw the right hand blank page
#ifdef WIN32
	CRect rightPgRect( (coverRect.Width()/2)+15, coverRect.top+10,
							(coverRect.Width()/2)+(coverRect.Width()/2)-14, coverRect.bottom-15 );
#else
	CRect rightPgRect( (coverRect.Width()/2)+15, coverRect.top+10,
							(coverRect.Width()/2)+(coverRect.Width()/2)-26, coverRect.bottom-22 );
#endif
	pDC->SelectObject( &grayBrush );	pDC->SelectObject( &blkPen );
	
	if( m_curSection==CDiveView::Front || m_curSection==CDiveView::Dive || m_curSection==CDiveView::Buddy )
		pDC->Rectangle( rightPgRect );
	
	// Draw the left hand blank page
	CRect leftPgRect( coverRect.left+20, coverRect.top+10,
							(coverRect.Width()/2)-5, coverRect.bottom-22/*-15*/ );
	pDC->SelectObject( &grayBrush );	pDC->SelectObject( &blkPen );
	if( m_curSection==CDiveView::Back || m_curSection==CDiveView::Dive || m_curSection==CDiveView::Buddy )
		pDC->Rectangle( leftPgRect );


	BOOL bDiveBold = m_curSection == CDiveView::Dive ? TRUE : FALSE;
	BOOL bBuddyBold = m_curSection == CDiveView::Buddy ? TRUE : FALSE;

	if( m_bRBuddyTab )
		m_rightBuddyTab = DrawTab( CPoint( rightPgRect.right-1, rightPgRect.top + 70 ),
																"BUDDIES", bBuddyBold, TRUE, RGB( 255, 255, 128 ), pDC );
	else
		m_leftBuddyTab = DrawTab( CPoint( leftPgRect.left, leftPgRect.top + 70 ),
																"BUDDIES", bBuddyBold, FALSE, RGB( 255, 255, 128 ), pDC );
	
	if( m_bRDiveTab )
		m_rightDiveTab = DrawTab( CPoint( rightPgRect.right-1, rightPgRect.top ), 
																"DIVING", bDiveBold, TRUE, RGB( 0, 128, 0 ), pDC );
    else
		m_leftDiveTab = DrawTab( CPoint( leftPgRect.left, leftPgRect.top ),
																"DIVING", bDiveBold, FALSE, RGB( 0, 128, 0 ), pDC );
	
	m_rightPgRect = rightPgRect;
	m_leftPgRect = leftPgRect;
                                                                                        	
	// Draw the binding rings
	DrawBindingRing( CPoint( centerRect.left-5, (coverRect.Height()/2)-60 ), centerRect.Width(), pDC );
	DrawBindingRing( CPoint( centerRect.left-5, (coverRect.Height()/2)+60 ), centerRect.Width(), pDC );

	pDC->SelectObject( pOldPen );
	pDC->SelectObject( pOldBrush );
}

void CDiveView::DrawBindingRing( CPoint pt, int nWidth, CDC* pDC )
{
	CBrush grayBrush;	grayBrush.CreateSolidBrush( RGB( 192, 192, 192 ) );
	CPen whtPen;		whtPen.CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
	CPen blkPen;		blkPen.CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	CBrush blkBrush;	blkBrush.CreateSolidBrush( RGB( 0, 0, 0 ) );

	// right page holes	
	pDC->SelectObject( &blkPen );
	pDC->SelectObject( &blkBrush );
	if( m_curSection==CDiveView::Front || m_curSection==CDiveView::Dive || m_curSection==CDiveView::Buddy )
		pDC->Ellipse( (nWidth+pt.x), pt.y-2, (nWidth+pt.x)+11, pt.y+10 );

	// left page holes	
	if( m_curSection==CDiveView::Back || m_curSection==CDiveView::Dive || m_curSection==CDiveView::Buddy )
		pDC->Ellipse( pt.x-1, pt.y-2, pt.x+10, pt.y+10 );
	
	pDC->SelectObject( &grayBrush );	pDC->SelectObject( &blkPen );
	pDC->RoundRect( pt.x, pt.y, nWidth+pt.x+10, pt.y+8, 8, 8 );
	pDC->SelectObject( &whtPen );
	pDC->MoveTo( pt.x+5, pt.y+2 );	pDC->LineTo( (nWidth/2)+pt.x+10, pt.y+2 );
	pDC->SelectObject( &blkPen );
	pDC->MoveTo( (nWidth/2)+pt.x, pt.y );
	pDC->LineTo( (nWidth/2)+pt.x+4, pt.y+4 );
	pDC->LineTo( (nWidth/2)+pt.x, pt.y+8 );
}

CRect CDiveView::DrawTab( CPoint tabOffset, CString m_text, BOOL bBold, BOOL bRight, COLORREF cr, CDC* pDC , BOOL bDraw )
{
	CBrush brush;	brush.CreateSolidBrush( cr );	
	CBrush* pOldBrush = pDC->SelectObject( &brush );
	pDC->SelectStockObject( BLACK_PEN );
	int nOldBkMode = pDC->SetBkMode( TRANSPARENT );

	int nBold = bBold ? 700 : 400;
	int nOrientation = bRight ? 2700 : 900;
	CFont font;
	font.CreateFont (-9 * pDC->GetDeviceCaps (LOGPIXELSY) / 72, 0, nOrientation, 0, nBold, 0, 0, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "Arial");
    CFont* pOldFont = pDC->SelectObject( &font );
    CRect textRect;	textRect.SetRectEmpty();
	pDC->DrawText( m_text, -1, textRect, DT_CALCRECT );
		            
	int nTabHeight = textRect.Width() + 20;
	
	POINT tabPoints[6];		CRect boundRect;
	if( bRight )
	{
		tabPoints[0].x = tabOffset.x;		tabPoints[0].y = tabOffset.y;
		tabPoints[1].x = tabOffset.x + 5;	tabPoints[1].y = tabOffset.y + 5;
		tabPoints[2].x = tabOffset.x + 15;	tabPoints[2].y = tabOffset.y + 10;
		tabPoints[3].x = tabOffset.x + 15;	tabPoints[3].y = tabOffset.y + nTabHeight + 10;
		tabPoints[4].x = tabOffset.x + 5;	tabPoints[4].y = tabOffset.y + nTabHeight + 15;
		tabPoints[5].x = tabOffset.x;		tabPoints[5].y = tabOffset.y + nTabHeight + 20;
		boundRect = CRect( tabPoints[0].x, tabPoints[0].y, tabPoints[2].x+1, tabPoints[5].y );
	}
	else
	{
		tabPoints[0].x = tabOffset.x;		tabPoints[0].y = tabOffset.y;
		tabPoints[1].x = tabOffset.x - 5;	tabPoints[1].y = tabOffset.y + 5;
		tabPoints[2].x = tabOffset.x - 15;	tabPoints[2].y = tabOffset.y + 10;
		tabPoints[3].x = tabOffset.x - 15;	tabPoints[3].y = tabOffset.y + nTabHeight + 10;
		tabPoints[4].x = tabOffset.x - 5;	tabPoints[4].y = tabOffset.y + nTabHeight + 15;
		tabPoints[5].x = tabOffset.x;		tabPoints[5].y = tabOffset.y + nTabHeight + 20;
		boundRect = CRect( tabPoints[2].x, tabPoints[0].y, tabPoints[0].x, tabPoints[5].y );
	}
	
	if( bDraw )
	{
		pDC->Polygon( tabPoints, sizeof( tabPoints ) / sizeof( POINT ) );
		if( bRight )
			pDC->TextOut( tabPoints[2].x - 1, tabPoints[2].y + 10, m_text );
		else
			pDC->TextOut( tabPoints[3].x + 1, tabPoints[3].y - 10, m_text );		
	}
		
	pDC->SetBkMode( nOldBkMode );
	pDC->SelectObject( pOldFont );
	pDC->SelectObject( pOldBrush );
	return boundRect;
}

/////////////////////////////////////////////////////////////////////////////
// CDiveView printing

BOOL CDiveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage( 1 );
	pInfo->m_pPD->m_pd.Flags |= PD_NOPAGENUMS;

	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDiveView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	SetRedraw( FALSE );

	pDC->SetMapMode( MM_LOMETRIC );
	if( pInfo->m_bPreview )
	{
		CDlgBar* pDlgBar = (CDlgBar*)AfxGetMainWnd()->GetDescendantWindow( IDD_DIALOG_BAR );
		if( pDlgBar!=NULL )
			pDlgBar->ShowWindow( SW_HIDE );
	}
}

void CDiveView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	SetRedraw( TRUE );
	
	pDC->SetMapMode( MM_TEXT );
		if( pInfo->m_bPreview )
	{
		CDlgBar* pDlgBar = (CDlgBar*)AfxGetMainWnd()->GetDescendantWindow( IDD_DIALOG_BAR );
		if( pDlgBar!=NULL )
			pDlgBar->ShowWindow( SW_SHOW );
	}
}

void CDiveView::OnPrint( CDC* pDC, CPrintInfo* pInfo )
{
	CDiveData* pData = GetDocument()->GetCurRecord();
	ASSERT_VALID( pData );

	char buf[100];

	m_rectDraw = pInfo->m_rectDraw;
	pDC->DPtoLP( m_rectDraw );
		
	CFont thinFont;
	thinFont.CreateFont (-20, 0, 0, 0, 0, 0, 0, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS San Serf");
	CFont boldFont;
	boldFont.CreateFont (-20, 0, 0, 0, FW_BOLD, 0, 0, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS San Serf");
	CFont tempFont;
	tempFont.CreateFont(-25, 0, 0, 0, 0, 0, 0, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS San Serf");
	CFont medFont;
	medFont.CreateFont(-30, 0, 0, 0, 0, 0, 0, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS San Serf");
	CFont bigFont;
	bigFont.CreateFont(-40, 0, 0, 0, 0, 0, 0, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS San Serf");

	CFont notesFont;
	notesFont.CreateFont(-20, 0, 0, 0, 0, 0, 0, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS San Serf");
	
	pDC->SetMapMode( MM_ANISOTROPIC );
	pDC->SetWindowExt( 1050, 1485 );	// 1050 x 1485	// A4
	pDC->SetViewportExt( m_rectDraw.Width(), m_rectDraw.Height() );

	CMetaFileDC dc;		dc.Create();
	
	dc.SetAttribDC( pDC->m_hAttribDC );

	CPen	thickPen( PS_SOLID, 3, RGB( 0, 0, 0 ) );
	CPen	vThickPen( PS_SOLID, 8, RGB( 0, 0, 0 ) );
	CBrush	whtBrush( RGB( 255, 255, 255 ) );
	CPen	nullPen( PS_NULL, 1, RGB( 0, 0, 0 ) );
	CPen	blkPen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	
	CPen* pOldPen = dc.SelectObject( &thickPen );
	dc.MoveTo( 0, 0 );	dc.LineTo( 1100, 0 );
	dc.MoveTo( 0, 100 );	dc.LineTo( 1100, 100 );
	
	CFont* pOldFont = dc.SelectObject( &thinFont );

	{
		CPoint curIndex = GetDocument()->GetCurIndex( );
		wsprintf( buf, "Dive No.: %d / %d\0", curIndex.x+1, curIndex.y+1 );
		CString str = buf;
		if( m_bBlank )	str = "Dive No.:";
		dc.TextOut( 10, 20, str, str.GetLength() );
	}
	{
		CString date = pData->GetDate().Format( "%d %B %Y" );
		if( pData->GetDate().GetDay() < 10 )
			date = date.Right( date.GetLength()-1 ); // lose to leading zero
		date = "Date: " + date;
		if( m_bBlank )	date = "Date:";
		dc.TextOut( 550, 20, date, date.GetLength() );
	}
	{
		CString loc = "Location: " + pData->GetLoc();
		if( m_bBlank )	loc = "Location:";
		dc.TextOut( 10, 50, loc, loc.GetLength() );
	}
	DrawShadowedRect( CRect( 10, 150, 410, 350 ), &dc );	

	CBrush* pOldBrush = dc.SelectObject( &whtBrush );
	dc.SelectObject( &nullPen );

	dc.Rectangle( 25, 140, 190, 160 );
	dc.TextOut( 30, 140, "Average Visibility", 18 );
	dc.SelectObject( &bigFont );
	dc.TextOut( 80, 180, "Good", 4 );
	dc.TextOut( 80, 230, "Medium", 6 );
	dc.TextOut( 80, 280, "Poor", 4 );

	dc.SelectObject( &blkPen );
	dc.Rectangle( 30, 180, 70, 220 );
	dc.Rectangle( 30, 230, 70, 270 );
	dc.Rectangle( 30, 280, 70, 320 );
	
	dc.SelectObject( &thickPen );
	if( !m_bBlank )
	{
		if( pData->GetVis() == CDiveData::Good )
		{	dc.MoveTo( 40, 195 );	dc.LineTo( 55, 210 );	dc.LineTo( 75, 175 );	}
		else if( pData->GetVis() == CDiveData::Medium )
		{	dc.MoveTo( 40, 245 );	dc.LineTo( 55, 260 );	dc.LineTo( 75, 225 );	}
		else if( pData->GetVis() == CDiveData::Poor )
		{	dc.MoveTo( 40, 295 );	dc.LineTo( 55, 310 );	dc.LineTo( 75, 275 );	}
	}
	dc.SelectObject( &blkPen );
	_gcvt( pData->GetVisDist(), 3, buf );
	{
		CString str = buf;	
		if( str.GetAt( str.GetLength()-1 )=='.' )
			str = str.Left( str.GetLength()-1 );
		if( pData->GetVisFt() )
			str += " ft.";
		else
			str += " m";
		if( !m_bBlank )
			dc.TextOut( 220, 280, str, str.GetLength() );	// VisDist
	}
	dc.MoveTo( 215, 325 );	dc.LineTo( 385, 325 );

	DrawShadowedRect( CRect( 450, 150, 1000, 350 ), &dc );
	dc.SelectObject( &thinFont );	dc.SelectObject( &nullPen );
	dc.Rectangle( 465, 140, 700, 160 );
	dc.TextOut( 470, 140, "Tank Pressures & Time", 21 );

	dc.SelectObject( &medFont );
	dc.TextOut( 495, 180, "S", 1 );	dc.TextOut( 495, 210, "T", 1 );	dc.TextOut( 495, 240, "A", 1 );
	dc.TextOut( 495, 270, "R", 1 );	dc.TextOut( 495, 300, "T", 1 );
	dc.TextOut( 755, 210, "E", 1 );	dc.TextOut( 755, 240, "N", 1 );	dc.TextOut( 755, 270, "D", 1 );

	{
		BOOL bPSI = pData->GetAirPSI( );
		wsprintf( buf, "%d", pData->GetAirStart() );
		CString str = buf;	str += bPSI ? " psi" : " bar";
		if( !m_bBlank )
			dc.TextOut( 560, 215, str, str.GetLength() );	// start bar	
		dc.SelectObject( &blkPen );
		dc.MoveTo( 555, 250 );	dc.LineTo( 685, 250 );
	}
	{
		BOOL bPSI = pData->GetAirPSI( );
		wsprintf( buf, "%d", pData->GetAirEnd() );
		CString str = buf;	str += bPSI ? " psi" : " bar";
		if( !m_bBlank )
			dc.TextOut( 820, 215, str, str.GetLength() );	// end bar		
		dc.SelectObject( &blkPen );
		dc.MoveTo( 815, 250 );	dc.LineTo( 945, 250 );
	}
	{
		CString time = "In: " + pData->GetTimeIn().Format( "%H:%M" );
		if( m_bBlank )	time = "In:";
		dc.TextOut( 550, 270, time, time.GetLength() );	// Time In
		dc.SelectObject( &blkPen );
		dc.MoveTo( 545, 305 );	dc.LineTo( 675, 305 );
	}
	{
		CString time = "Out: " + pData->GetTimeOut().Format( "%H:%M" );
		if( m_bBlank )	time = "Out:";
		dc.TextOut( 810, 270, time, time.GetLength() );	// Time out
		dc.SelectObject( &blkPen );
		dc.MoveTo( 805, 305 );	dc.LineTo( 960, 305 );
	}

	dc.SelectObject( &vThickPen );
	dc.MoveTo( 50, 450 );	dc.LineTo( 280, 450 );	dc.LineTo( 230, 650 );
	dc.LineTo( 430, 650 );	dc.LineTo( 480, 450 );	dc.LineTo( 650, 450 );

	{
		CString time = "SI: " + pData->GetSI().Format( "%H:%M" );
		if( m_bBlank )	time = "SI:";
		dc.TextOut( 60, 400, time, time.GetLength() );	// si
		dc.SelectObject( &blkPen );
		dc.MoveTo( 100, 435 );	dc.LineTo( 185, 435 );
	}
	{
		CString strPG = "PG: " + pData->GetPGBeforeDive();
		if( m_bBlank )	strPG = "PG:";
		dc.TextOut( 200, 400, strPG, strPG.GetLength() );		// PG before dive
		dc.SelectObject( &blkPen );
		dc.MoveTo( 255, 435 );	dc.LineTo( 290, 435 );
	}
	{
		CString strPG = "PG: " + pData->GetPGAfterDive( );
		if( m_bBlank )	strPG = "PG:";
		dc.TextOut( 500, 400, strPG, strPG.GetLength() );		// PG after dive
		dc.SelectObject( &blkPen );
		dc.MoveTo( 555, 435 );	dc.LineTo( 590, 435 );
	}
	_gcvt( pData->GetDepth(), 3, buf );
	{
		CString str = buf;	
		if( str.GetAt( str.GetLength()-1 )=='.' )
			str = str.Left( str.GetLength()-1 );
		if( pData->GetDepthMts() )
			str += " m";
		else
			str += " ft.";
	
		if( !m_bBlank )
			dc.TextOut(	95, 530, str, str.GetLength() );		// depth	
	}
	{
		wsprintf( buf, "%d", pData->GetDecompStop( ) );
		CString str = buf;
		if( !m_bBlank )
			dc.TextOut(	540, 530, str, str.GetLength() );			// stop
	}
	{
		wsprintf( buf, "%d mins", pData->GetBottomTime( ) );
		CString str = buf;
		if( !m_bBlank )
			dc.TextOut( 280, 670, str, str.GetLength() );	// bottom time
	}

	dc.SelectObject( &thinFont );	dc.SelectObject( &blkPen );
	dc.MoveTo( 90, 560 );	dc.LineTo( 185, 560 );	dc.TextOut( 100, 565, "DEPTH", 5 );
	dc.MoveTo( 510, 560 );	dc.LineTo( 605, 560 );
	dc.TextOut( 520, 565, "15ft/5m", 7 );	dc.TextOut( 535, 590, "stop", 4 );
	dc.MoveTo( 230, 700 );	dc.LineTo( 430, 700 );
	dc.TextOut( 260, 710, "BOTTOM TIME", 11 );

  	DrawShadowedRect( CRect( 750, 435, 950, 605 ), &dc );
	dc.SelectObject( &medFont );
	dc.TextOut( 785, 450, "RNT", 3 );
	dc.TextOut( 760, 500, "+ ABT", 5 );
	dc.TextOut( 785, 560, "TBT", 3 );
	dc.MoveTo( 860, 480 );	dc.LineTo( 930, 480 );
	dc.MoveTo( 860, 530 );	dc.LineTo( 930, 530 );
	dc.MoveTo( 860, 590 );	dc.LineTo( 930, 590 );
	dc.SelectObject( &thickPen );
	dc.MoveTo( 750, 550 );	dc.LineTo( 950, 550 );
	{
		wsprintf( buf, "%d", pData->GetRNT() );		CString str = buf;
		if( !m_bBlank )
			dc.TextOut( 880, 445, str, str.GetLength() );		// RNT
	}
	{
		wsprintf( buf, "%d", pData->GetABT() );		CString str = buf;
		if( !m_bBlank )
			dc.TextOut( 880, 495, str, str.GetLength() );		// ABT
	}
	{
		wsprintf( buf, "%d", pData->GetTBT() );		CString str = buf;
		if( !m_bBlank )
			dc.TextOut( 880, 555, str, str.GetLength() );		// TBT
	}

	dc.SelectObject( &medFont );
	{
		wsprintf( buf, "%d", pData->GetWeight() );
		CString str = "Weight: ";	str += buf;
		str += ((pData->GetWeightKG()) ? "kgs" : "lbs" );
		if( m_bBlank )	str = "Weight:";
		dc.TextOut( 700, 670, str, str.GetLength() ); 		// Weight
	}

	dc.SelectObject( &blkPen );
	dc.MoveTo( 810, 705 );	dc.LineTo( 910, 705 );

	DrawShadowedRect( CRect( 10, 770, 510, 1070 ), &dc );
	dc.SelectObject( &thinFont );	dc.SelectObject( &nullPen );
	dc.Rectangle( 25, 760, 160, 780 );
	dc.TextOut( 30, 760, "Temperature", 11 );
							
	dc.SelectObject( &blkPen );
	for( int loop=0; loop<=19; loop++ )
		dc.Arc( 10+(25*loop), 900, 35+(25*loop), 930, 10+(25*loop), 915, 35+(25*loop), 915 );
	dc.SelectObject( &nullPen );
	dc.Rectangle( 11, 900, 510, 919 );

	dc.SelectObject( &tempFont );
	dc.TextOut( 40, 790, "32 - 50f", 8 );	dc.TextOut( 45, 825, "0 - 10c", 7 );
	dc.TextOut( 160, 790, "50 - 70f", 8 );	dc.TextOut( 160, 825, "10 - 21c", 8 );
	dc.TextOut( 300, 790, "70f+", 4 );		dc.TextOut( 300, 825, "21c+", 4 );
	dc.TextOut( 390, 870, "Air", 3 );	dc.TextOut( 390, 960, "Surface", 7 );	dc.TextOut( 390, 1010, "Bottom", 6 );

 	DrawCheckBox( &dc, CRect( 70, 860, 110, 900 ), !m_bBlank ? (pData->GetAirTemp()==CDiveData::Cold) : FALSE );	// Air
	DrawCheckBox( &dc, CRect( 190, 860, 230, 900 ), !m_bBlank ? (pData->GetAirTemp()==CDiveData::Warm) : FALSE );
	DrawCheckBox( &dc, CRect( 310, 860, 350, 900 ), !m_bBlank ? (pData->GetAirTemp()==CDiveData::Hot) : FALSE );

	DrawCheckBox( &dc, CRect( 70, 950, 110, 990 ), !m_bBlank ? (pData->GetSurfaceTemp()==CDiveData::Cold) : FALSE );	// Surface
	DrawCheckBox( &dc, CRect( 190, 950, 230, 990 ), !m_bBlank ? (pData->GetSurfaceTemp()==CDiveData::Warm) : FALSE );
	DrawCheckBox( &dc, CRect( 310, 950, 350, 990 ), !m_bBlank ? (pData->GetSurfaceTemp()==CDiveData::Hot) : FALSE );

	DrawCheckBox( &dc, CRect( 70, 1000, 110, 1040 ), !m_bBlank ? (pData->GetBottomTemp()==CDiveData::Cold) : FALSE );	// Bottom
	DrawCheckBox( &dc, CRect( 190, 1000, 230, 1040 ), !m_bBlank ? (pData->GetBottomTemp()==CDiveData::Warm) : FALSE );
	DrawCheckBox( &dc, CRect( 310, 1000, 350, 1040 ), !m_bBlank ? (pData->GetBottomTemp()==CDiveData::Hot) : FALSE );

	DrawShadowedRect( CRect( 10, 1100, 510, 1430 ), &dc );
	dc.SelectObject( &thinFont );	dc.SelectObject( &nullPen );
	dc.Rectangle( 25, 1090, 225, 1120 );
	dc.TextOut( 30, 1090, "Exposure Protection", 19 );
	
	DrawCheckBox( &dc, CRect( 40, 1150, 80, 1190 ), !m_bBlank ? pData->GetDrySuit() : FALSE, "Dry Suit" );
	DrawCheckBox( &dc, CRect( 40, 1220, 80, 1260 ), !m_bBlank ? pData->GetWetSuit() : FALSE, "Wet Suit" );
	DrawCheckBox( &dc, CRect( 40, 1290, 80, 1330 ), !m_bBlank ? pData->GetSDrySuit() : FALSE, "Semi-Dry Suit" );
	DrawCheckBox( &dc, CRect( 40, 1360, 80, 1400 ), !m_bBlank ? pData->GetUSuit() : FALSE, "Under Suit" );

	DrawCheckBox( &dc, CRect( 300, 1150, 340, 1190 ), !m_bBlank ? pData->GetGloves() : FALSE, "Gloves" );
	DrawCheckBox( &dc, CRect( 300, 1220, 340, 1260 ), !m_bBlank ? pData->GetMittens() : FALSE, "Mittens" );
	DrawCheckBox( &dc, CRect( 300, 1290, 340, 1330 ), !m_bBlank ? pData->GetHood() : FALSE, "Hood" );
	DrawCheckBox( &dc, CRect( 300, 1360, 340, 1400 ), !m_bBlank ? pData->GetSocks() : FALSE, "Socks" );

	DrawShadowedRect( CRect( 530, 770, 1000, 1070 ), &dc );
	dc.SelectObject( &thinFont );	dc.SelectObject( &nullPen );
	dc.Rectangle( 545, 760, 650, 780 );
	dc.TextOut( 550, 760, "Dive Type", 9 );

	DrawCheckBox( &dc, CRect( 590, 820, 630, 860 ), !m_bBlank ? pData->GetFresh() : FALSE, "Fresh" );
	DrawCheckBox( &dc, CRect( 590, 880, 630, 920 ), !m_bBlank ? pData->GetSalt() : FALSE, "Salt" );
	DrawCheckBox( &dc, CRect( 590, 940, 630, 980 ), !m_bBlank ? pData->GetShore() : FALSE, "Shore" );
	DrawCheckBox( &dc, CRect( 590, 1000, 630, 1040 ), !m_bBlank ? pData->GetBoat() : FALSE, "Boat" );

	DrawCheckBox( &dc, CRect( 770, 820, 810, 860 ), !m_bBlank ? pData->GetWaves() : FALSE, "Waves" );
	DrawCheckBox( &dc, CRect( 770, 880, 810, 920 ), !m_bBlank ? pData->GetCurrent() : FALSE, "Current" );
	DrawCheckBox( &dc, CRect( 770, 940, 810, 980 ), !m_bBlank ? pData->GetSurf() : FALSE, "Surf" );
	DrawCheckBox( &dc, CRect( 770, 1000, 810, 1040 ), !m_bBlank ? pData->GetSurge() : FALSE, "Surge" );

	dc.SelectObject( &thickPen );
	dc.MoveTo( 530, 1320 );	dc.LineTo( 1000, 1320 );
	dc.MoveTo( 530, 1430 );	dc.LineTo( 1000, 1430 );

	dc.SelectObject( &thinFont );
	dc.TextOut( 590, 1350, "ABT to", 6 );
	dc.TextOut( 600, 1380, "Date", 4 );
	dc.SelectObject( &blkPen );
	dc.MoveTo( 660, 1400 );	dc.LineTo( 760, 1400 );
	
	dc.TextOut( 816, 1350, "All", 3 );
	dc.TextOut( 800, 1380, "Dives", 5 );
	dc.MoveTo( 860, 1400 );	dc.LineTo( 960, 1400 );

	dc.SelectObject( &medFont );							  /*
	{
		CString time = pData->GetABTtoDate().Format( "%H:%M" );
		if( !m_bBlank )
			dc.TextOut( 680, 1360, time, time.GetLength() );
	}
	{
		CString time = GetDocument()->GetDiveSet()->GetTotalABT().Format( "%H:%M" );
		if( !m_bBlank )
			dc.TextOut( 870, 1360, time, time.GetLength() );
	}														*/

	{
		CDiveSet* pSet = GetDocument()->GetDiveSet();
		CTime ABTtoDate = pSet->GetABTtoDate( pData );
		int nDays = ABTtoDate.GetDay() - 1;
		int nHrs = ABTtoDate.GetHour();
		int nMins = ABTtoDate.GetMinute();
		nHrs += (nDays * 24 );
		char buf[10];
		wsprintf( buf, (nMins <=9) ? "%d:0%d" : "%d:%d", nHrs, nMins );
		CString tmpStr = buf;
		dc.TextOut( 680, 1360, tmpStr, tmpStr.GetLength() );

		ABTtoDate = pSet->GetABTtoDate( NULL );
		nDays = ABTtoDate.GetDay() - 1;
		nHrs = ABTtoDate.GetHour();
		nMins = ABTtoDate.GetMinute();
		nHrs += (nDays * 24 );
		wsprintf( buf, (nMins <=9) ? "%d:0%d" : "%d:%d", nHrs, nMins );
		tmpStr = buf;
		dc.TextOut( 870, 1360, tmpStr, tmpStr.GetLength() );
	}

	DrawShadowedRect( CRect( 530, 1100, 1000, 1300 ), &dc );
	dc.SelectObject( &thinFont );	dc.SelectObject( &nullPen );
	dc.Rectangle( 545, 1090, 640, 1110 );
	dc.TextOut( 550, 1090, "Comments", 8 );

	CString comments = pData->GetNotes();
	
	//if( !m_bBlank )
	//	dc.ExtTextOut( 550, 1120, ETO_CLIPPED, CRect( 550, 1120, 990, 1290 ), comments, comments.GetLength(), NULL );

//	dc.SelectObject( &notesFont );
//		pDC->DrawText( comments, comments.GetLength(), CRect( 550, 1120, 990, 1290 ), DT_WORDBREAK );
	
	
	RECT rect;
	rect.left = 550;	rect.top = 1120;	rect.right = 990;	rect.bottom = 1290;

	//::DrawText( dc.m_hAttribDC, "111 222 333 444 555 666 777 888 999 000", 39, &rect, DT_LEFT );							   

	dc.SelectObject( pOldBrush );
	dc.SelectObject( pOldFont );	
	dc.SelectObject( pOldPen );

	HMETAFILE hmf = dc.Close();

	pDC->SetWindowOrg( -25, -20 );	
	pDC->PlayMetaFile( hmf );

	pDC->SelectObject( &notesFont );
		pDC->DrawText( comments, comments.GetLength(), CRect( 550, 1120, 990, 1290 ), DT_WORDBREAK );


	::DeleteMetaFile( hmf );
}

void CDiveView::DrawCheckBox( CDC* pDC, CRect rect, BOOL bChecked, CString str )
{
	CBrush	whtBrush( RGB( 255, 255, 255 ) );
	CPen	thinPen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	CPen	thickPen( PS_SOLID, 3, RGB( 0, 0, 0 ) );
	CBrush* pOldBrush = pDC->SelectObject( &whtBrush );
	CPen* pOldPen = pDC->SelectObject( &thinPen );

	pDC->Rectangle( rect );
	if( bChecked )
	{
		pDC->SelectObject( &thickPen );
		rect.OffsetRect( 5, -5 );
		pDC->MoveTo( rect.left+10, (rect.top+((rect.bottom-rect.top)/2))+10 );
		pDC->LineTo( rect.right-20, rect.bottom );
		pDC->LineTo( rect.right, rect.top );
	}

	if( str.GetLength() != 0 )
	{
		CFont tempFont;
		tempFont.CreateFont(-25, 0, 0, 0, 0, 0, 0, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS San Serf");
		CFont* pOldFont = pDC->SelectObject( &tempFont );
		pDC->TextOut( rect.right+10, rect.bottom-20, str );
		pDC->SelectObject( pOldFont );	
	}

	pDC->SelectObject( pOldPen );
	pDC->SelectObject( pOldBrush );
}
 
void CDiveView::DrawShadowedRect( CRect rect, CDC* pDC )
{
	CBrush	blkBrush( RGB( 0, 0, 0 ) );
	CBrush	whtBrush( RGB( 255, 255, 255 ) );
	CPen	thinPen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	CBrush*	pOldBrush = pDC->SelectObject( &blkBrush );
	CPen* pOldPen = pDC->SelectObject( &thinPen );
	
	CRect newRect = rect;	newRect.OffsetRect( 5, 5 );
	pDC->Rectangle( newRect );
	pDC->SelectObject( &whtBrush );
	pDC->Rectangle( rect );

	pDC->SelectObject( pOldPen );
	pDC->SelectObject( pOldBrush );
}

/////////////////////////////////////////////////////////////////////////////
// CDiveView diagnostics

#ifdef _DEBUG
void CDiveView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDiveView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDiveDoc* CDiveView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiveDoc)));
	return (CDiveDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiveView message handlers

void CDiveView::OnNextPageClicked()
{	OnNextpage();	}

void CDiveView::OnPrevPageClicked()
{	OnPrevpage();	}

void CDiveView::OnNextpage()
{
	if( m_curSection==CDiveView::Back )
		return;
	CClientDC dc( this );
	m_rightDiveTab = DrawTab( CPoint( m_rightPgRect.right-1, m_rightPgRect.top ),
												"DIVING", FALSE, TRUE, RGB( 0, 255, 0 ), &dc, FALSE );
	m_leftDiveTab = DrawTab( CPoint( m_leftPgRect.left, m_leftPgRect.top ),
												"DIVING", TRUE, FALSE, RGB( 0, 255, 0 ), &dc, FALSE );

	m_rightBuddyTab = DrawTab( CPoint( m_rightPgRect.right-1, m_rightPgRect.top + 70 ), 
													"BUDDIES", FALSE, TRUE, RGB( 255, 255, 128 ), &dc, FALSE );
	m_leftBuddyTab = DrawTab( CPoint( m_leftPgRect.left, m_leftPgRect.top + 70 ),
													"BUDDIES", FALSE, TRUE, RGB( 255, 255, 128 ), &dc, FALSE  );

	switch( m_curSection )
	{
		case CDiveView::Front:
				m_curSection = CDiveView::Dive;
				m_prevPage.ShowWindow( SW_SHOW );
				m_nextPage.ShowWindow( SW_SHOW );
				m_pFrontPg->ShowWindow( SW_HIDE );
				m_pBackPg->ShowWindow( SW_HIDE );
				m_pDivePg1->ShowWindow( SW_SHOW );
				m_pDivePg2->ShowWindow( SW_SHOW );
				m_pBuddyPg1->ShowWindow( SW_HIDE );
				m_pBuddyPg2->ShowWindow( SW_HIDE );
				m_bLDiveTab = TRUE;	m_bRDiveTab = FALSE;
				m_bLBuddyTab = FALSE;	m_bRBuddyTab = TRUE;
				OnRecordFirst();
				break;
		case CDiveView::Dive:
				m_curSection = CDiveView::Buddy;
				m_prevPage.ShowWindow( SW_SHOW );
				m_nextPage.ShowWindow( SW_SHOW );
				m_pFrontPg->ShowWindow( SW_HIDE );
				m_pBackPg->ShowWindow( SW_HIDE );
				m_pDivePg1->ShowWindow( SW_HIDE );
				m_pDivePg2->ShowWindow( SW_HIDE );
				m_pBuddyPg1->ShowWindow( SW_SHOW );
				m_pBuddyPg2->ShowWindow( SW_SHOW );
				m_bLDiveTab = TRUE;	m_bRDiveTab = FALSE;
				m_bLBuddyTab = TRUE;	m_bRBuddyTab = FALSE;
				OnRecordFirst();
				break;
		case CDiveView::Buddy:
				m_curSection = CDiveView::Back;
				m_prevPage.ShowWindow( SW_SHOW );
				m_nextPage.ShowWindow( SW_HIDE );
				m_pFrontPg->ShowWindow( SW_HIDE );
				m_pBackPg->ShowWindow( SW_SHOW );
				m_pDivePg1->ShowWindow( SW_HIDE );
				m_pDivePg2->ShowWindow( SW_HIDE );
				m_pBuddyPg1->ShowWindow( SW_HIDE );
				m_pBuddyPg2->ShowWindow( SW_HIDE );
				m_bLDiveTab = TRUE;	m_bRDiveTab = FALSE;
				m_bLBuddyTab = TRUE;	m_bRBuddyTab = FALSE;
				OnRecordFirst();
			break;
	}
	
	InvalidateRect( m_rightPgRect, FALSE );
	InvalidateRect( m_leftPgRect, FALSE );
	InvalidateRect( m_leftDiveTab, FALSE );
	InvalidateRect( m_rightDiveTab, FALSE );
	InvalidateRect( m_leftBuddyTab, FALSE );
	InvalidateRect( m_rightBuddyTab, FALSE );

	Invalidate( FALSE );

	m_nextPage.SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE );
}

void CDiveView::OnPrevpage()
{
	if( m_curSection==CDiveView::Front )
		return;
	CClientDC dc( this );
	m_rightDiveTab = DrawTab( CPoint( m_rightPgRect.right-1, m_rightPgRect.top ),
												"DIVING", FALSE, TRUE, RGB( 0, 255, 0 ), &dc, FALSE );
	m_leftDiveTab = DrawTab( CPoint( m_leftPgRect.left, m_leftPgRect.top ),
												"DIVING", TRUE, FALSE, RGB( 0, 255, 0 ), &dc, FALSE );
	m_rightBuddyTab = DrawTab( CPoint( m_rightPgRect.right-1, m_rightPgRect.top + 70 ), 
													"BUDDIES", FALSE, TRUE, RGB( 255, 255, 128 ), &dc, FALSE );
	m_leftBuddyTab = DrawTab( CPoint( m_leftPgRect.left, m_leftPgRect.top + 70 ),
													"BUDDIES", FALSE, FALSE, RGB( 255, 255, 128 ), &dc, FALSE  );

	switch( m_curSection )
	{
		case CDiveView::Back:
				m_curSection = CDiveView::Buddy;
				m_prevPage.ShowWindow( SW_SHOW );
				m_nextPage.ShowWindow( SW_SHOW );
				m_pFrontPg->ShowWindow( SW_HIDE );
				m_pBackPg->ShowWindow( SW_HIDE );
				m_pDivePg1->ShowWindow( SW_HIDE );
				m_pDivePg2->ShowWindow( SW_HIDE );
				m_pBuddyPg1->ShowWindow( SW_SHOW );
				m_pBuddyPg2->ShowWindow( SW_SHOW );
				m_bLDiveTab = TRUE;	m_bRDiveTab = FALSE;
				m_bLBuddyTab = TRUE;	m_bRBuddyTab = FALSE;
				OnRecordFirst();
				break;
		case CDiveView::Dive:
				m_curSection = CDiveView::Front;
				m_prevPage.ShowWindow( SW_HIDE );
				m_nextPage.ShowWindow( SW_SHOW );
				m_pFrontPg->ShowWindow( SW_SHOW );
				m_pBackPg->ShowWindow( SW_HIDE );
				m_pDivePg1->ShowWindow( SW_HIDE );
				m_pDivePg2->ShowWindow( SW_HIDE );
				m_pBuddyPg1->ShowWindow( SW_HIDE );
				m_pBuddyPg2->ShowWindow( SW_HIDE );
				m_bLDiveTab = FALSE;	m_bRDiveTab = TRUE;
				m_bLBuddyTab = FALSE;	m_bRBuddyTab = TRUE;
				OnRecordFirst();
				break;
		case CDiveView::Buddy:
				m_curSection = CDiveView::Dive;
				m_prevPage.ShowWindow( SW_SHOW );
				m_nextPage.ShowWindow( SW_SHOW );
				m_pFrontPg->ShowWindow( SW_HIDE );
				m_pBackPg->ShowWindow( SW_HIDE );
				m_pDivePg1->ShowWindow( SW_SHOW );
				m_pDivePg2->ShowWindow( SW_SHOW );
				m_pBuddyPg1->ShowWindow( SW_HIDE );
				m_pBuddyPg2->ShowWindow( SW_HIDE );
				m_bLDiveTab = TRUE;	m_bRDiveTab = FALSE;
				m_bLBuddyTab = FALSE;	m_bRBuddyTab = TRUE;
				OnRecordFirst();
				break;
	}
	InvalidateRect( m_rightPgRect, FALSE );
	InvalidateRect( m_leftPgRect, FALSE );
	InvalidateRect( m_leftDiveTab, FALSE );
	InvalidateRect( m_rightDiveTab, FALSE );
	InvalidateRect( m_leftBuddyTab, FALSE );
	InvalidateRect( m_rightBuddyTab, FALSE );

	Invalidate( FALSE );

	m_nextPage.SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE );
}

void CDiveView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_tmpPoint = point;	    	

	CScrollView::OnLButtonDown(nFlags, point);
}

void CDiveView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if( m_leftDiveTab.PtInRect( m_tmpPoint ) && m_leftDiveTab.PtInRect( point ) && m_bLDiveTab )
	{
		if( m_curSection == CDiveView::Back )
		{	OnPrevpage();	OnPrevpage();	}
		else if( m_curSection == CDiveView::Buddy )
			OnPrevpage();
	}
	else if( m_rightDiveTab.PtInRect( m_tmpPoint ) && m_rightDiveTab.PtInRect( point ) && m_bRDiveTab )
		OnNextpage();
	else if( m_leftBuddyTab.PtInRect( m_tmpPoint ) && m_leftBuddyTab.PtInRect( point ) && m_bLBuddyTab )
	{
		if( m_curSection == CDiveView::Back )
			OnPrevpage();
	}
	else if( m_rightBuddyTab.PtInRect( m_tmpPoint ) && m_rightBuddyTab.PtInRect( point ) && m_bRBuddyTab )
	{
		m_curSection = CDiveView::Dive;
		OnNextpage();
	}
	else
	{   
		CRect left = m_coverRect;	left.right = (left.left+(left.Width()/2))-15;
		CRect right = m_coverRect;	right.left = (right.Width()/2)+15;
		if( left.PtInRect( m_tmpPoint ) && left.PtInRect( point ) && m_curSection != CDiveView::Front )
		{
			m_curSection = CDiveView::Dive;
			OnPrevpage();
		}
		if( right.PtInRect( m_tmpPoint ) && right.PtInRect( point ) && m_curSection != CDiveView::Back )
		{
			m_curSection = CDiveView::Buddy;
			OnNextpage();
		}
	}	
	
	CScrollView::OnLButtonUp(nFlags, point);
}


void CDiveView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

#ifdef WIN32
	m_size = CSize( (cx < 562) ? 562 : cx, (cy < 382) ? 382 : cy );
	CRect viewRect( 0, 0, 562, 382 );
#else    // 556, 388
	CRect viewRect;
	if( CMainFrame::bVGA )
	{
		m_size = CSize( (cx < 565) ? 565 : cx, (cy < 397) ? 397 : cy );
		viewRect = CRect( 0, 0, 565, 397 );
	}
	else
	{
		m_size = CSize( (cx < 725) ? 725 : cx, (cy < 517) ? 517 : cy );
		viewRect = CRect( 0, 0, 725, 517 );
	}
#endif
    
	// Calculate the tab rectangles
	viewRect.InflateRect( -viewRect.left, -viewRect.top );	viewRect.left = 0;	viewRect.top = 0;
	CRect coverRect = viewRect;		coverRect.InflateRect( -10, -10 );
#ifdef WIN32
	CRect rightPgRect( (coverRect.Width()/2)+15, coverRect.top+10,
							(coverRect.Width()/2)+(coverRect.Width()/2)-20, coverRect.bottom-15 );
	CRect leftPgRect( coverRect.left+20, coverRect.top+10,
							(coverRect.Width()/2)-5, coverRect.bottom-15 );
#else
	CRect rightPgRect( (coverRect.Width()/2)+15, coverRect.top+10,
							(coverRect.Width()/2)+(coverRect.Width()/2)-128, coverRect.bottom-10 );
	CRect leftPgRect( coverRect.left+20, coverRect.top+10,
							(coverRect.Width()/2)-5, coverRect.bottom-20 );
#endif

	CClientDC dc( this );
	m_rightDiveTab = DrawTab( CPoint( rightPgRect.right-1, m_rightPgRect.top ),
												"DIVING", FALSE, TRUE, RGB( 0, 255, 0 ), &dc, FALSE );
	m_leftDiveTab = DrawTab( CPoint( leftPgRect.left, m_leftPgRect.top ),
												"DIVING", TRUE, FALSE, RGB( 0, 255, 0 ), &dc, FALSE );
	m_rightBuddyTab = DrawTab( CPoint( rightPgRect.right-1, rightPgRect.top + 70 ), 
													"BUDDIES", FALSE, TRUE, RGB( 255, 255, 128 ), &dc, FALSE  );
	m_leftBuddyTab = DrawTab( CPoint( leftPgRect.left, leftPgRect.top + 70 ),
													"BUDDIES", FALSE, FALSE, RGB( 255, 255, 128 ), &dc, FALSE  );
}

void CDiveView::OnDiveNew()
{
	if( m_curSection == CDiveView::Dive )
	{
		CDiveData* pData = GetDocument()->NewDive();
		m_pDivePg1->UpdateControls( pData );	m_pDivePg2->UpdateControls( pData );
	}
	else if( m_curSection == CDiveView::Buddy )
	{
		CBudData* pData = GetDocument()->NewBud();
		m_pBuddyPg1->UpdateControls( pData );	m_pBuddyPg2->UpdateControls( pData );
	}
	GetDocument()->SetModifiedFlag( );
}

void CDiveView::RemoveDive()
{
	if( m_curSection == CDiveView::Dive )
	{
		CDiveData* pData = GetDocument()->RemoveDive();
		m_pDivePg1->UpdateControls( pData );	m_pDivePg2->UpdateControls( pData );
		m_pDivePg2->DisplayABTTimes( GetDocument()->GetCurRecord() );
	}
	else if( m_curSection == CDiveView::Buddy )
	{
		CBudData* pData = GetDocument()->RemoveBud();
		m_pBuddyPg1->UpdateControls( pData );	m_pBuddyPg2->UpdateControls( pData );
		m_pBuddyPg2->UpdateButtons( );
	}
}

void CDiveView::OnRecordPrev()
{
	if( m_curSection == CDiveView::Dive )
	{
		CDiveData* pData = GetDocument()->DivePrev();
		m_pDivePg1->UpdateControls( pData );	m_pDivePg2->UpdateControls( pData );	
	}
	else if( m_curSection == CDiveView::Buddy )
	{
		CBudData* pData = GetDocument()->BudPrev();
		m_pBuddyPg1->UpdateControls( pData );	m_pBuddyPg2->UpdateControls( pData );	
	}
}

void CDiveView::OnRecordNext()
{
	if( m_curSection == CDiveView::Dive )
	{
		CDiveData* pData = GetDocument()->DiveNext();
		m_pDivePg1->UpdateControls( pData );	m_pDivePg2->UpdateControls( pData );	
	}
	else if( m_curSection == CDiveView::Buddy )
	{
		CBudData* pData = GetDocument()->BudNext();
		m_pBuddyPg1->UpdateControls( pData );	m_pBuddyPg2->UpdateControls( pData );	
	}
}

void CDiveView::OnRecordFirst()
{
	if( m_curSection == Dive )
	{
		CDiveData* pData = GetDocument()->DiveFirst();
		m_pDivePg1->UpdateControls( pData );	m_pDivePg2->UpdateControls( pData );	
	}
	else
	{
		CBudData* pData = GetDocument()->BudFirst();
		m_pBuddyPg1->UpdateControls( pData );	m_pBuddyPg2->UpdateControls( pData );	
	}
}

void CDiveView::OnRecordLast()
{
	if( m_curSection == Dive )
	{
		CDiveData* pData = GetDocument()->DiveLast();
		m_pDivePg1->UpdateControls( pData );	m_pDivePg2->UpdateControls( pData );
	}
	else
	{
		CBudData* pData = GetDocument()->BudLast();
		m_pBuddyPg1->UpdateControls( pData );	m_pBuddyPg2->UpdateControls( pData );
	}
}

void CDiveView::FindBud( CString let )
{
	CBudData* pData = GetDocument()->FindBud( let );
	m_pBuddyPg1->UpdateControls( pData );	m_pBuddyPg2->UpdateControls( pData );
}

void CDiveView::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{	
	if( m_curSection == CDiveView::Dive )
		pCmdUI->Enable( !GetDocument()->IsFirstDive() );
	else if( m_curSection == CDiveView::Buddy )
		pCmdUI->Enable( !GetDocument()->IsFirstBud() );
	else
		pCmdUI->Enable( FALSE );
}

void CDiveView::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{	
	if( m_curSection == CDiveView::Dive )
		pCmdUI->Enable( !GetDocument()->IsFirstDive() );
	else if( m_curSection == CDiveView::Buddy )
		pCmdUI->Enable( !GetDocument()->IsFirstBud() );
	else
		pCmdUI->Enable( FALSE );
}

void CDiveView::OnUpdateRecordNext(CCmdUI* pCmdUI)
{	
	if( m_curSection == CDiveView::Dive )
		pCmdUI->Enable( !GetDocument()->IsLastDive() );
	else if( m_curSection == CDiveView::Buddy )
		pCmdUI->Enable( !GetDocument()->IsLastBud() );
	else
		pCmdUI->Enable( FALSE );
}

void CDiveView::OnUpdateRecordLast(CCmdUI* pCmdUI)
{	
	if( m_curSection == CDiveView::Dive )
		pCmdUI->Enable( !GetDocument()->IsLastDive() );
	else if( m_curSection == CDiveView::Buddy )
		pCmdUI->Enable( !GetDocument()->IsLastBud() );
	else
		pCmdUI->Enable( FALSE );
}

void CDiveView::UpdateDivePageControls()
{
	//m_curSection = CDiveView::Front;
	//OnNextpage();
	//OnRecordFirst();
}

void CDiveView::OnEditLocations() 
{
	CLocDlg dlg;

	dlg.DoModal();
	CDiveApp::ReadLocations();	// re-read ini file

	CString strTmp;
	m_pDivePg1->m_ctlLocation.GetWindowText( strTmp );

	m_pDivePg1->m_ctlLocation.ResetContent();
	for( int loop=0; loop<=CDiveApp::m_locations.GetUpperBound(); loop++ )
		m_pDivePg1->m_ctlLocation.AddString( CDiveApp::m_locations.GetAt( loop ) );

	m_pDivePg1->m_ctlLocation.SetWindowText( strTmp );
}



void CDiveView::OnDefSetttings() 
{
	CDefaultDlg dlg;
	
	for( int i=0; i <= GetDocument()->m_defDives.GetUpperBound(); i++ )
	{
		CDefDive* pDive = new CDefDive;
		CDefDive* pOld = (CDefDive*)GetDocument()->m_defDives.GetAt( i );

		pDive->SetLocation( pOld->GetLocation() );
		pDive->SetWeight( pOld->GetWeight() );
		pDive->SetLocation( pOld->GetLocation() );
		pDive->SetCheck( pOld->GetCheck() );
		pDive->SetMea( pOld->GetMea() );

		dlg.m_defDives.Add( pDive );
	}
	// make sure there is a record for every location
	for( int loop=0; loop<=CDiveApp::m_locations.GetUpperBound(); loop++ )
	{
		BOOL bFound = FALSE;
		CString str1;	CString str2;
		int nTmp = dlg.m_defDives.GetUpperBound();
		for( int i=0; i <= nTmp; i++ )
		{
			CDefDive* pDive = (CDefDive*)dlg.m_defDives.GetAt( i );
			if( pDive->GetLocation() == CDiveApp::m_locations.GetAt( loop ) )
			{
				bFound = TRUE;
				break;
			}
		}
		if( !bFound )
		{
			CDefDive* pDive = new CDefDive;
			pDive->SetLocation( CDiveApp::m_locations.GetAt( loop ) );
			dlg.m_defDives.Add( pDive );
		}
	}
		
	if( dlg.DoModal() == IDOK )
	{
		for( int i=0; i <= GetDocument()->m_defDives.GetUpperBound(); i++ )
			delete (CDefDive*)GetDocument()->m_defDives.GetAt( i );
		GetDocument()->m_defDives.RemoveAll( );
		
		for( i=0; i <= dlg.m_defDives.GetUpperBound(); i++ )
		{
			CDefDive* pOld = (CDefDive*)dlg.m_defDives.GetAt( i );
			if( !pOld->IsDiveEmpty() )
			{
				CDefDive* pDive = new CDefDive;
			
				pDive->SetLocation( pOld->GetLocation() );
				pDive->SetWeight( pOld->GetWeight() );
				pDive->SetCheck( pOld->GetCheck() );
				pDive->SetMea( pOld->GetMea() );

				GetDocument()->m_defDives.Add( pDive );
			}
		}
		GetDocument()->SetModifiedFlag( );
	}		

	// delete the dialogs default dives
	for( i=0; i <= dlg.m_defDives.GetUpperBound(); i++ )
		delete (CDefDive*)dlg.m_defDives.GetAt( i );
}

void CDiveView::OnReports() 
{
	CReportsDlg dlg;

	dlg.m_pDiveSet = GetDocument()->GetDiveSet( );
	dlg.DoModal( );
}						

void CDiveView::OnDiveRemove() 
{
	if( AfxMessageBox( "Delete this record?", MB_YESNO|MB_ICONQUESTION )==IDYES )
		RemoveDive();
}

void CDiveView::OnEditCopy()			 
{			 /*
	CSharedFile file;
	
	CArchive ar( &file, CArchive::store );
	//GetDocument()->m_pFormData->SerializeSelObjs( ar );
	ar.Close();
	
	COleDataSource* pDataSource = NULL;
	pDataSource = new COleDataSource;
	
	pDataSource->CacheGlobalData( m_cbDive, file.Detach() );
	pDataSource->SetClipboard();    */                                                                                                                                                                                                      
};

void CDiveView::OnFilePrintBlank() 
{
	m_bBlank = TRUE;
	CScrollView::OnFilePrint();
	m_bBlank = FALSE;
}

void CDiveView::OnUpdateDefSetttings(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (CDiveApp::m_locations.GetUpperBound() > -1) ? TRUE : FALSE );
}

void CDiveView::OnUpdateDiveNew(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_curSection == CDiveView::Dive ||
						m_curSection == CDiveView::Buddy ) ? TRUE : FALSE );
}

void CDiveView::OnUpdateDiveRemove(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_curSection == CDiveView::Dive ||
						m_curSection == CDiveView::Buddy ) ? TRUE : FALSE );
}



void CDiveView::OnSetFocus(CWnd* pOldWnd)
{
	CScrollView::OnSetFocus(pOldWnd);
	
	//AfxMessageBox( "SetFocus" );
	
	m_pDivePg2->DisplayABTTimes( GetDocument()->GetCurRecord() );
	
}
