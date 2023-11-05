// repview.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "repdoc.h"
#include "repview.h"
#include "divedata.h"
#include "reports.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportView

IMPLEMENT_DYNCREATE(CReportView, CScrollView)

CReportView::CReportView()
{  
#ifdef WIN32
	CClientDC dc( NULL );
#else
	CClientDC dc( this );
#endif

	//----- Create a 9 point Sans Serif Font
	m_textFont.CreateFont (-9 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 400, 0, 0, 0,
					   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
					   DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");

	m_boldFont.CreateFont (-9 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 700, 0, 0, 0,
					   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
					   DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");

	//----- Create a 9 point Sans Serif Font
	m_prnTextFont.CreateFont (-30, 0, 0, 0, 400, 0, 0, 0,
					   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
					   DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");

	m_prnBoldFont.CreateFont (-30, 0, 0, 0, 700, 0, 0, 0,
					   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
					   DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");

	m_bPrinting = FALSE;
	m_prnIndex = CPoint( 32767, 32767 );
	m_nPrnRecs = 0;
}

CReportView::~CReportView()
{
}


BEGIN_MESSAGE_MAP(CReportView, CScrollView)
	//{{AFX_MSG_MAP(CReportView)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReportView drawing

void CReportView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_LOMETRIC, sizeTotal);
}

void CReportView::CorrectScrollSize()
{
	int nX = GetDocument()->GetColsWidth()+10;
	int nY = ((GetDocument()->GetNoOfRecs()+2)*40);
	SetScrollSizes( MM_LOMETRIC, CSize( nX, 1500 ) );
}

void CReportView::OnDraw(CDC* pDC)
{
	CReportDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	BeginWaitCursor();  /*
	CStatusBar* pBar = (CStatusBar*)AfxGetMainWnd()->GetDescendantWindow( AFX_IDW_STATUS_BAR );
	if( pBar != NULL )
	{	pBar->SetWindowText( "Redrawing report..." );	pBar->UpdateWindow();	}

	CRect wndRect;
	GetWindowRect( &wndRect );
	int nTotLines = (wndRect.Height() / 15 ) + 1;

	CPoint curPt = GetScrollPosition();

	CFont* pOldFont = pDC->SelectObject( &m_boldFont );
	int nTmp = abs(curPt.y)/20;

 	for( int loop=nTmp; loop<=nTmp+(nTotLines-1); loop++ )
	{
  		char buf[100];
		wsprintf( buf, "Line %d, curPt.y = %d, height = %d, displaying lines = %d - %d",
										 loop, curPt.y, wndRect.Height(), nTmp, nTmp+(nTotLines-1) );
//		if( loop <= 100 )
//			pDC->TextOut( 10, -(curPt.y+(loop*40)), buf );
	}

	// move to the first record that is to be displayed
	if( pBar != NULL )
	{	pBar->SetWindowText( "Looking for records to display..." );	pBar->UpdateWindow();	}
																				 
	CDiveSet* pSet = pDoc->GetRepSet( );
	CDiveData* pData = NULL;
	CPoint index = pSet->DiveFirst( CPoint( 0, 0 ), &pData );
	int nRecs = 0;
	
	while( index != CPoint( 9999, 9999 ) && nRecs != nTmp )
	{
		nRecs++;
		index = pSet->DiveNext( index, &pData );
	}

	CColumn* pCol = NULL;
  	int nColsWidth = 0;
	CReport* pReport = pDoc->GetReport();
	BOOL bCount = FALSE;

	for( int loop=nTmp; loop<=nTmp+(nTotLines-1); loop++ )
	{
		if( loop == 0 )	// display header
		{
			for( int i=0; i<=pReport->GetRepColUpperBound( ); i++ )
			{
				pCol = (CColumn*)pReport->GetRepCol( i );
				pDC->DrawText( pCol->GetRepName( ), -1, CRect( nColsWidth+10, -(curPt.y+(loop*40)),
													nColsWidth+pCol->GetWidth( ), -((curPt.y+(loop*40))+40) ), DT_LEFT );
				nColsWidth += pCol->GetWidth()+30;
			}
		}
		else if( loop >= 1 && index != CPoint( 9999, 9999 ) )	// draw data
		{
			pDC->SelectObject( &m_textFont );
			nColsWidth = 0;
			for( int i=0; i<=pReport->GetRepColUpperBound( ); i++ )
			{
				pCol = (CColumn*)pReport->GetRepCol( i );
				pDC->DrawText( pCol->GetString( pData ), -1, CRect( nColsWidth+10, -(curPt.y+(loop*40)),
												(nColsWidth+10)+pCol->GetWidth(), -((curPt.y+(loop*40))+40) ), DT_LEFT );
				nColsWidth += pCol->GetWidth()+30;
			}
			index = pSet->DiveNext( index, &pData );
		}
		else if( index == CPoint( 9999, 9999 ) && !bCount )
			bCount = TRUE;
		else if( loop>=GetDocument()->GetNoOfRecs()+1 )
		{
			int nRecs = GetDocument()->GetNoOfRecs();
			char buf[50];
			wsprintf( buf, "Report Count: %d", nRecs );

			pDC->SelectObject( &m_boldFont );
			pDC->TextOut( 10, -(curPt.y+((nRecs+1)*40)), buf );
		}
	}


																				
	pDC->SelectObject( pOldFont );

    if( pBar != NULL )
    {
		CString str;
		str.LoadString( AFX_IDS_IDLEMESSAGE );
		pBar->SetWindowText( str );
		pBar->UpdateWindow();
	}
				   */


	CStatusBar* pBar = (CStatusBar*)AfxGetMainWnd()->GetDescendantWindow( AFX_IDW_STATUS_BAR );
	if( pBar != NULL )
	{	pBar->SetWindowText( "Redrawing report..." );	pBar->UpdateWindow();	}

	CFont* pOldFont = NULL;

	if( m_bPrinting )
		pOldFont = pDC->SelectObject( &m_prnBoldFont );
	else
		pOldFont = pDC->SelectObject( &m_boldFont );

	CColumn* pCol = NULL;
  	int nColsWidth = 0;

	CReport* pReport = pDoc->GetReport();
	if( pReport->GetRepColUpperBound() > -1 )
	{
		for( int i=0; i<=pReport->GetRepColUpperBound( ); i++ )
		{
			pCol = (CColumn*)pReport->GetRepCol( i );
			pDC->DrawText( pCol->GetRepName( ), -1, CRect( nColsWidth+10, -10,
												nColsWidth+pCol->GetWidth( ), -50 ), DT_LEFT );
			nColsWidth += pCol->GetWidth()+30;
		}
	}
	else
	{
		pDC->TextOut( 10, -10, "No columns defined!", 19 );
		return;
	}
		
	if( !pDoc->IsRepRecords() )
		return;

	if( m_bPrinting )
		pDC->SelectObject( &m_prnTextFont );
	else
		pDC->SelectObject( &m_textFont );

	CDiveSet* pSet = pDoc->GetRepSet( );
	CDiveData* pData = NULL;
	CPoint index = pSet->DiveFirst( CPoint( 0, 0 ), &pData );
	int nOffSet = 0;	int nCol = 0;	nColsWidth = 0;	int nRecs=0;

	do
	{
		nColsWidth = 0;
		for( int i=0; i<=pReport->GetRepColUpperBound( ); i++ )
		{
			pCol = (CColumn*)pReport->GetRepCol( i );
			pDC->DrawText( pCol->GetString( pData ), -1, CRect( nColsWidth+10, -((nOffSet*45)+70),
											(nColsWidth+10)+pCol->GetWidth(), -((nOffSet*45)+110) ), DT_LEFT );
			nColsWidth += pCol->GetWidth()+30;
		}
		nRecs++;
		nOffSet++;
		index = pSet->DiveNext( index, &pData );
	} while( index != CPoint( 9999, 9999 ) );


	if( m_bPrinting )
		pDC->SelectObject( &m_prnBoldFont );
	else
		pDC->SelectObject( &m_boldFont );

	char buf[50];
	wsprintf( buf, "Report Count: %d", GetDocument()->GetNoOfRecs() );

	pDC->TextOut( 10, -((nOffSet*45)+130), buf );

	SetScrollSizes( MM_LOMETRIC, CSize( nColsWidth+10, ((nOffSet*45)+170) ) );

	pDC->SelectObject( pOldFont );
    if( pBar != NULL )
    {
		CString str;
		str.LoadString( AFX_IDS_IDLEMESSAGE );
		pBar->SetWindowText( str );
		pBar->UpdateWindow();
	}
		 
	EndWaitCursor();
}

BOOL CReportView::OnPreparePrinting(CPrintInfo* pInfo)
{
	//pInfo->SetMaxPage( 1 );
	pInfo->m_pPD->m_pd.Flags |= PD_NOPAGENUMS;

	pInfo->m_nNumPreviewPages = 1;
	//pInfo->SetMinPage( 1 );
	/*
	int nPages = abs(pInfo->m_rectDraw.bottom) / (((GetDocument()->GetNoOfRecs()*45)+((abs(pInfo->m_rectDraw.top)+110))));
	pInfo->SetMaxPage( nPages );
	  */
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReportView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if( pInfo->m_bPreview )
	{
		CDlgBar* pDlgBar = (CDlgBar*)AfxGetMainWnd()->GetDescendantWindow( IDD_DIALOG_BAR );
		if( pDlgBar!=NULL )
			pDlgBar->ShowWindow( SW_HIDE );
	}

	m_bPrinting = TRUE;
	 /*
	CFont* pOldFont = pDC->SelectObject( &m_prnTextFont );
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nRowHeight = tm.tmHeight;
	pDC->SelectObject( pOldFont );
	   */
	int nPages = 0;
	int nRecs = GetDocument()->GetNoOfRecs();
	int nReport = (nRecs*55)+110;
	int nTmp = pDC->GetDeviceCaps(VERTRES); //abs(pInfo->m_rectDraw.Height());
	while( TRUE )
	{
		nReport -= nTmp;
		nPages++;
		if( nReport < 0 )
			break;
	}

	pInfo->SetMaxPage( nPages );

	//pInfo->m_nCurPage = 1;	// start at page #1
 	pInfo->m_nNumPreviewPages = 1;

	CScrollView::OnBeginPrinting( pDC, pInfo );
}

void CReportView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_bPrinting = FALSE;

	if( pInfo->m_bPreview )
	{
		CDlgBar* pDlgBar = (CDlgBar*)AfxGetMainWnd()->GetDescendantWindow( IDD_DIALOG_BAR );
		if( pDlgBar!=NULL )
			pDlgBar->ShowWindow( SW_SHOW );
	}

	m_nPrnRecs = 0;

	CScrollView::OnEndPrinting( pDC, pInfo );
}

void CReportView::OnPrint( CDC* pDC, CPrintInfo* pInfo )
{
	CRect rectDraw = pInfo->m_rectDraw;
	CReportDoc* pDoc = GetDocument();
	CReport* pReport = pDoc->GetReport();
	CColumn* pCol;

	CFont* pOldFont = pDC->SelectObject( &m_prnBoldFont );
	int nColsWidth=0;

	if( pReport->GetRepColUpperBound() > -1 )
	{
		for( int i=0; i<=pReport->GetRepColUpperBound( ); i++ )
		{
			pCol = (CColumn*)pReport->GetRepCol( i );
			pDC->DrawText( pCol->GetRepName( ), -1, CRect( nColsWidth+10, -(abs(rectDraw.top)+10),
												nColsWidth+pCol->GetWidth( ), -(abs(rectDraw.top)+50) ), DT_LEFT );
			nColsWidth += pCol->GetWidth()+30;
		}
	}
	else
	{
		pDC->TextOut( 10, -10, "No columns defined!", 19 );
		return;
	}				

	if( !pDoc->IsRepRecords() )
		return;

	pDC->SelectObject( &m_prnTextFont );

	CDiveSet* pSet = pDoc->GetRepSet( );
	CDiveData* pData = NULL;  int nQaz = 0;
	int nOffSet = 0;	int nCol = 0;	nColsWidth = 0;	int nRecs=0;

	m_prnIndex = pSet->DiveFirst( CPoint( 0, 0 ), &pData );
	while( m_prnIndex != CPoint( 9999, 9999 ) && nQaz != (int)(m_nPrnRecs*(pInfo->m_nCurPage-1)) )
	{
		nQaz++;
		m_prnIndex = pSet->DiveNext( m_prnIndex, &pData );
	}
	
	int nRectHeight = abs(rectDraw.Height());

	do
	{
		if( m_prnIndex != CPoint( 9999, 9999 ) ) // already at last record
		{
			nColsWidth = 0;
			for( int i=0; i<=pReport->GetRepColUpperBound( ); i++ )
			{
				pCol = (CColumn*)pReport->GetRepCol( i );
				pDC->DrawText( pCol->GetString( pData ), -1, CRect( nColsWidth+10, -((nOffSet*45)+((abs(rectDraw.top)+70))),
												(nColsWidth+10)+pCol->GetWidth(), -((nOffSet*45)+((abs(rectDraw.top)+110))) ), DT_LEFT );
				nColsWidth += pCol->GetWidth()+30;
			}
			nRecs++;
			nOffSet++;
		
			m_prnIndex = pSet->DiveNext( m_prnIndex, &pData );
		}
	} while( m_prnIndex != CPoint( 9999, 9999 ) && rectDraw.bottom < -((nOffSet*45)+((abs(rectDraw.top)+110))) );

	if( m_prnIndex == CPoint( 9999, 9999 ) )	// rendering the last page
	{
		char buf[50];
		wsprintf( buf, "Report Count: %d", GetDocument()->GetNoOfRecs() );
		pDC->SelectObject( &m_prnBoldFont );
		pDC->TextOut( 10, -((nOffSet*45)+(abs(rectDraw.top)+115)), buf );
	}
	
	if( m_nPrnRecs == 0 )
		m_nPrnRecs = nRecs;

	nRecs = 0;

	//if( !(m_prnIndex != CPoint( 9999, 9999 ) && abs(rectDraw.bottom) < ((nOffSet*45)+((abs(rectDraw.top)+110)))) )
	//	m_nPrnRecs = 0;

	pDC->SelectObject( pOldFont );

	//CScrollView::OnPrint( pDC, pInfo );
}

/////////////////////////////////////////////////////////////////////////////
// CReportView diagnostics

#ifdef _DEBUG
void CReportView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CReportView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CReportDoc* CReportView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReportDoc)));
	return (CReportDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportView message handlers
/*
void CReportView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	char buf[50];
	wsprintf( buf, "Pos: %d\n", nPos );
	
	TRACE( buf );
		
	//CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

	pScrollBar->SetScrollPos( 10 );
}

				   */


void CReportView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	//Invalidate( FALSE );
	
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CReportView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
/*	int nX = GetDocument()->GetColsWidth()+10;
	int nY = ((GetDocument()->GetNoOfRecs()+2)*40);
	SetScrollSizes( MM_LOMETRIC, CSize( nX, nY ) );
								*/
}							   
