// divevw.cpp : implementation of the CDiveView class
//

#include "stdafx.h"
#include "divelog.h"
#include "form.h"
#include "comments.h"
#include "checkbox.h"
#include "divedata.h"
#include "field.h"

#include "divedoc.h"
#include "divevw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiveView

IMPLEMENT_DYNCREATE(CDiveView, CView)

BEGIN_MESSAGE_MAP(CDiveView, CView)
	//{{AFX_MSG_MAP(CDiveView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_RECORD_ADD, OnRecordAdd)
	ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
	ON_COMMAND(IDM_RECORD_FIRST, OnRecordFirst)
	ON_COMMAND(IDM_RECORD_LAST, OnRecordLast)
	ON_COMMAND(IDM_RECORD_NEXT, OnRecordNext)
	ON_COMMAND(IDM_RECORD_PREV, OnRecordPrev)
	ON_UPDATE_COMMAND_UI(IDM_RECORD_FIRST, OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(IDM_RECORD_LAST, OnUpdateRecordLast)
	ON_UPDATE_COMMAND_UI(IDM_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(IDM_RECORD_PREV, OnUpdateRecordPrev)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED( ID_COMMENTS_ZOOM, OnCommentsZoomClicked )
	ON_BN_CLICKED( ID_VISBUT_GOOD, OnVisGoodClicked )
	ON_BN_CLICKED( ID_VISBUT_OK, OnVisOkClicked )
	ON_BN_CLICKED( ID_VISBUT_POOR, OnVisPoorClicked )
	ON_BN_CLICKED( ID_CHECK_FRESH, OnCheckFreshClicked )
	ON_BN_CLICKED( ID_CHECK_SALT, OnCheckSaltClicked )
	ON_BN_CLICKED( ID_CHECK_SHORE, OnCheckShoreClicked )
	ON_BN_CLICKED( ID_CHECK_BOAT, OnCheckBoatClicked )
	ON_BN_CLICKED( ID_CHECK_WAVES, OnCheckWavesClicked )
	ON_BN_CLICKED( ID_CHECK_CURRENT, OnCheckCurrentClicked )
	ON_BN_CLICKED( ID_CHECK_SURF, OnCheckSurfClicked )
	ON_BN_CLICKED( ID_CHECK_SURGE, OnCheckSurgeClicked )
	ON_BN_CLICKED( ID_CHECK_SOCKS, OnCheckSocksClicked )
	ON_BN_CLICKED( ID_CHECK_HOOD, OnCheckHoodClicked )
	ON_BN_CLICKED( ID_CHECK_MITTENS, OnCheckMittensClicked )
	ON_BN_CLICKED( ID_CHECK_GLOVES, OnCheckGlovesClicked )
	ON_BN_CLICKED( ID_CHECK_USUIT, OnCheckUSuitClicked )
	ON_BN_CLICKED( ID_CHECK_DSUIT, OnCheckDSuitClicked )
	ON_BN_CLICKED( ID_CHECK_SEMIDSUIT, OnCheckSemiDSuitClicked )
	ON_BN_CLICKED( ID_CHECK_WETSUIT, OnCheckWetSuitClicked )
	ON_BN_CLICKED( ID_CHECK_COSTUME, OnCheckCostumeClicked )
	ON_BN_CLICKED( ID_TEMP_AIR_LOW, OnTempAirLowClicked )
	ON_BN_CLICKED( ID_TEMP_AIR_MED, OnTempAirMedClicked )
	ON_BN_CLICKED( ID_TEMP_AIR_HIGH, OnTempAirHighClicked )
	ON_BN_CLICKED( ID_TEMP_SURFACE_LOW, OnTempSurfaceLowClicked )
	ON_BN_CLICKED( ID_TEMP_SURFACE_MED, OnTempSurfaceMedClicked )
	ON_BN_CLICKED( ID_TEMP_SURFACE_HIGH, OnTempSurfaceHighClicked )
	ON_BN_CLICKED( ID_TEMP_BOTTOM_LOW, OnTempBottomLowClicked )
	ON_BN_CLICKED( ID_TEMP_BOTTOM_MED, OnTempBottomMedClicked )
	ON_BN_CLICKED( ID_TEMP_BOTTOM_HIGH, OnTempBottomHighClicked )
	ON_CBN_DBLCLK( ID_CUR_FIELD, OnComboDblClick )
	ON_EN_CHANGE( IDC_COMMENTS, OnCommentsChange )
	ON_MESSAGE( BF_FINISHED, OnEditFldFinished )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiveView construction/destruction

CDiveView::CDiveView()
{
	m_pArialFont = m_pArialBoldFont = NULL;
	m_pComments = NULL;
	m_pCommentsZoom = NULL;
}

CDiveView::~CDiveView()
{
	delete m_pArialFont;	delete m_pArialBoldFont;
	delete m_pComments;
	delete m_pCommentsZoom;
	for( int loop=0; loop<=m_fldList.GetUpperBound(); loop++ )
		delete m_fldList.GetAt( loop );
	m_fldList.RemoveAll();
	for( loop=0; loop<=m_checkBoxes.GetUpperBound(); loop++ )
		delete m_checkBoxes.GetAt( loop );
	m_checkBoxes.RemoveAll();

}


void CDiveView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	CDiveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDiveData* pData = GetDocument()->m_pDiveSet->GetCurRecord();

/*	CSize sizeTotal;
	sizeTotal.cx = 632;	sizeTotal.cy = 388;
	SetScrollSizes(MM_TEXT, sizeTotal);
	*/
	if( m_pArialFont == NULL )
	{
		// Progamme has just started
		CClientDC dc( this );
		m_pArialFont = new CFont();
		m_pArialFont->CreateFont(	-9 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 400, 0, 0, 0,
									ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
									DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "Arial" );
		m_pArialBoldFont = new CFont();
		m_pArialBoldFont->CreateFont(	-10 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 700, 0, 0, 0,
										ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
										DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "Arial" );
		m_pComments = new CEdit();
		m_pComments->Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_AUTOVSCROLL|ES_WANTRETURN|ES_MULTILINE,
								CRect( 18, 325, 203, 373 ), this, IDC_COMMENTS );
		m_pComments->SetFont( m_pArialFont );
		m_pCommentsZoom  = new CButton();
		m_pCommentsZoom->Create( "Zoom", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
									CRect( 150, 303, 203, 323 ), this, ID_COMMENTS_ZOOM );
									
		CCheckBox::m_pDoc = pDoc;
		// Visibility
		CreateChkBox( CRect( 20, 90, 69, 105 ), "IDB_VIS_GOODD", "IDB_VIS_GOODU", ID_VISBUT_GOOD );
		CreateChkBox( CRect( 20, 110, 86, 125 ), "IDB_VIS_OKD", "IDB_VIS_OKU", ID_VISBUT_OK );
		CreateChkBox( CRect( 20, 130, 66, 145 ), "IDB_VIS_POORD", "IDB_VIS_POORU", ID_VISBUT_POOR );
		// Other check boxes
        CreateChkBox( CRect( 380, 70, 428, 83 ),   "IDB_FRESHD", "IDB_FRESHU", ID_CHECK_FRESH );
		CreateChkBox( CRect( 380, 88, 419, 101 ),  "IDB_SALTD",  "IDB_SALTU",  ID_CHECK_SALT );
		CreateChkBox( CRect( 380, 106, 431, 119 ), "IDB_SHORED", "IDB_SHOREU", ID_CHECK_SHORE );
		CreateChkBox( CRect( 380, 124, 423, 137 ), "IDB_BOATD",  "IDB_BOATU",  ID_CHECK_BOAT );
		CreateChkBox( CRect( 456, 70, 513, 83 ),   "IDB_WAVESD", "IDB_WAVESU", ID_CHECK_WAVES );
		CreateChkBox( CRect( 456, 88, 517, 101 ),  "IDB_CURRENTD", "IDB_CURRENTU", ID_CHECK_CURRENT );
		CreateChkBox( CRect( 456, 106, 497, 119 ), "IDB_SURFD",  "IDB_SURFU",  ID_CHECK_SURF );
		CreateChkBox( CRect( 456, 124, 507, 138 ), "IDB_SURGED", "IDB_SURGEU", ID_CHECK_SURGE );
		CreateChkBox( CRect( 557, 256, 608, 269 ), "IDB_SOCKSD", "IDB_SOCKSU", ID_CHECK_SOCKS );
		CreateChkBox( CRect( 557, 238, 603, 251 ), "IDB_HOODD",  "IDB_HOODU",  ID_CHECK_HOOD );
	   	CreateChkBox( CRect( 557, 220, 616, 233 ), "IDB_MITTENSD", "IDB_MITTENSU", ID_CHECK_MITTENS );
		CreateChkBox( CRect( 557, 202, 614, 215 ), "IDB_GLOVESD", "IDB_GLOVESU", ID_CHECK_GLOVES );
		CreateChkBox( CRect( 557, 175, 609, 197 ), "IDB_USUITD",  "IDB_USUITU",  ID_CHECK_USUIT );
		CreateChkBox( CRect( 557, 156, 621, 170 ), "IDB_DSUITD",  "IDB_DSUITU",  ID_CHECK_DSUIT );
		CreateChkBox( CRect( 557, 126, 621, 151 ), "IDB_SEMIDSUITD", "IDB_SEMIDSUITU", ID_CHECK_SEMIDSUIT );
		CreateChkBox( CRect( 557, 108, 626, 121 ), "IDB_WETSUITD", "IDB_WETSUITU", ID_CHECK_WETSUIT );
		CreateChkBox( CRect( 557, 90, 625, 103 ),  "IDB_COSTUMED", "IDB_COSTUMEU", ID_CHECK_COSTUME );
		// Temperature
		CreateChkBox( CRect( 27, 223, 41, 236 ), "IDB_CHECKD", "IDB_CHECKU", ID_TEMP_AIR_LOW );
		CreateChkBox( CRect( 77, 223, 91, 236 ), "IDB_CHECKD", "IDB_CHECKU", ID_TEMP_AIR_MED );
		CreateChkBox( CRect( 122, 223, 136, 236 ), "IDB_CHECKD", "IDB_CHECKU", ID_TEMP_AIR_HIGH );
		CreateChkBox( CRect( 27, 252, 41, 265 ), "IDB_CHECKD", "IDB_CHECKU", ID_TEMP_SURFACE_LOW );
		CreateChkBox( CRect( 77, 252, 91, 265 ), "IDB_CHECKD", "IDB_CHECKU", ID_TEMP_SURFACE_MED );
		CreateChkBox( CRect( 122, 252, 136, 265 ), "IDB_CHECKD", "IDB_CHECKU", ID_TEMP_SURFACE_HIGH );
		CreateChkBox( CRect( 27, 272, 41, 285 ), "IDB_CHECKD", "IDB_CHECKU", ID_TEMP_BOTTOM_LOW );
		CreateChkBox( CRect( 77, 272, 91, 285 ), "IDB_CHECKD", "IDB_CHECKU", ID_TEMP_BOTTOM_MED );
		CreateChkBox( CRect( 122, 272, 136, 285 ), "IDB_CHECKD", "IDB_CHECKU", ID_TEMP_BOTTOM_HIGH );

		// Create the fields
		CEditDateFld* pEditDateFld = new CEditDateFld();	// date
		pEditDateFld->Create( CRect( 189, 17, 318, 35 ), this, pDoc->m_pDiveSet, pDoc );
		m_fldList.Add( pEditDateFld );
		
		CComboFld* pComboFld = new CComboFld();	// Location
		pComboFld->Create( CRect( 392, 17, 618, 35 ), this, pDoc->m_pDiveSet, pDoc );
		m_fldList.Add( pComboFld );
		
		CEditFld* pEditFld = new CEditFld();	// Visibility
		pEditFld->Create( CRect( 104, 124, 133, 142 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::Visibility );	m_fldList.Add( pEditFld );
		pEditFld = new CEditFld();	// Air Start
		pEditFld->Create( CRect( 193, 81, 228, 99 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::AirStart );	m_fldList.Add( pEditFld );
		pEditFld = new CEditFld();	// Air End
		pEditFld->Create( CRect( 277, 80, 312, 97 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::AirEnd );	m_fldList.Add( pEditFld );
		pEditFld = new CEditFld();	// Time In
		pEditFld->Create( CRect( 195, 125, 237, 142 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::TimeIn );	m_fldList.Add( pEditFld );
		pEditFld = new CEditFld();	// Time Out
		pEditFld->Create( CRect( 274, 125, 316, 142 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::TimeOut );	m_fldList.Add( pEditFld );
		
		pEditFld = new CEditFld();	// Surface Interval
		pEditFld->Create( CRect( 237, 188, 277, 206 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::SI );	m_fldList.Add( pEditFld );
		pEditFld = new CEditFld();	// Depth
		pEditFld->Create( CRect( 250, 235, 279, 252 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::Depth );	m_fldList.Add( pEditFld );
		pEditFld = new CEditFld();	// Bottom Time
		pEditFld->Create( CRect( 318, 281, 362, 297 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::BottomTime );	m_fldList.Add( pEditFld );
		pEditFld = new CEditFld();	// Decompression Stop
		pEditFld->Create( CRect( 391, 235, 420, 253 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::Stop );	m_fldList.Add( pEditFld );
		pEditFld = new CEditFld();	// Weight
		pEditFld->Create( CRect( 565, 302, 594, 320 ), this, pDoc->m_pDiveSet, pDoc );
		pEditFld->SetFldName( CEditFld::Weight );	m_fldList.Add( pEditFld );

	}

	ChangeChkBoxState( ID_TEMP_AIR_LOW,	pData->m_air == CDiveData::Cold );
	ChangeChkBoxState( ID_TEMP_AIR_MED,	pData->m_air == CDiveData::Warm );
	ChangeChkBoxState( ID_TEMP_AIR_HIGH, pData->m_air == CDiveData::Hot );
	ChangeChkBoxState( ID_TEMP_SURFACE_LOW, pData->m_surface == CDiveData::Cold );
	ChangeChkBoxState( ID_TEMP_SURFACE_MED, pData->m_surface == CDiveData::Warm );
	ChangeChkBoxState( ID_TEMP_SURFACE_HIGH, pData->m_surface == CDiveData::Hot );
	ChangeChkBoxState( ID_TEMP_BOTTOM_LOW, pData->m_bottom == CDiveData::Cold );
	ChangeChkBoxState( ID_TEMP_BOTTOM_MED, pData->m_bottom == CDiveData::Warm );
	ChangeChkBoxState( ID_TEMP_BOTTOM_HIGH, pData->m_bottom == CDiveData::Hot );
	
	switch( pData->m_Visibility )
	{
		case CDiveData::Good:	OnVisGoodClicked();	break;
		case CDiveData::OK:		OnVisOkClicked();	break;
		case CDiveData::Poor:	OnVisPoorClicked();	break;
	}

	pDoc->SetModifiedFlag( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// CDiveView drawing

void CDiveView::OnDraw(CDC* pDC)
{
	CDiveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClientDC dc(this);
	OnPrepareDC(&dc);
	
	CDC* m_pMemDC = pDC;
	
      /*
	CDC* m_pMemDC = new CDC();
	CBitmap* m_pBitmap = new CBitmap();
	
    m_pMemDC->CreateCompatibleDC( pDC );
    m_pBitmap->CreateCompatibleBitmap( pDC, 640, 480 );
    
    CRect updateRect;
    pDC->GetClipBox( &updateRect );
    CBitmap* pOldBitmap2 = (CBitmap*)m_pMemDC->SelectObject( m_pBitmap );
    m_pMemDC->SelectClipRgn( NULL );
    m_pMemDC->IntersectClipRect( &updateRect );
    CBrush bgBrush( (COLORREF)::GetSysColor( COLOR_WINDOW ) );
    CBrush* pOldBrush = m_pMemDC->SelectObject( &bgBrush );
    // m_pMemDC->PatBlt( updateRect.left, updateRect.top, updateRect.Width(), updateRect.Height(), PATCOPY );
	*/

	pDoc->DrawForm( m_pMemDC );
	
	CDiveData* pData = pDoc->m_pDiveSet->GetCurRecord();
	
	CDC* pDisplayMemDC = new CDC;
	CBitmap* pBitmap = new CBitmap;
	pBitmap->LoadBitmap( IDB_TANKS );
	pDisplayMemDC->CreateCompatibleDC( m_pMemDC );
	CBitmap* pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject( pBitmap );
	m_pMemDC->BitBlt( 175, 65, 10, 31, pDisplayMemDC, 0, 0, SRCCOPY );	// Full tank
	m_pMemDC->BitBlt( 190, 65, 50, 10, pDisplayMemDC, 20, 0, SRCCOPY );	// START word
	m_pMemDC->BitBlt( 260, 65, 10, 31, pDisplayMemDC, 10, 0, SRCCOPY );	// Empty tank
	m_pMemDC->BitBlt( 275, 65, 30, 10, pDisplayMemDC, 20, 10, SRCCOPY );	// END word
	CBitmap* pPicture = new CBitmap();
	pPicture->LoadBitmap( IDB_PICTURE );
	delete pDisplayMemDC->SelectObject( pPicture );		// deletes pBitmap
	m_pMemDC->BitBlt( 325, 195, 21, 63, pDisplayMemDC, 0, 0, SRCCOPY );
	delete pDisplayMemDC->SelectObject( pOldBitmap );	// deletes pPicture
	delete pDisplayMemDC;        
    
	// Draw the fields
	CFont* pOldFont = m_pMemDC->SelectObject( m_pArialBoldFont );
	int oldBkMode = m_pMemDC->SetBkMode( TRANSPARENT );
	
	// Dive No  ( DiveNo / DiveNo done that day )
	int nDiveNo = pDoc->m_pDiveSet->GetCurIndex() + 1;
	m_pMemDC->DrawText( intToStr( nDiveNo ) + " / " + intToStr( pData->m_nDiveNo ),
									-1, CRect( 75, 16, 145, 37 ), DT_VCENTER|DT_CENTER|DT_SINGLELINE );
	
	CString date = pData->m_date.Format( "%d %B %Y" );
	if( pData->m_date.GetDay() < 10 )
		date = date.Right( date.GetLength()-1 ); // lose to leading zero
	m_pMemDC->DrawText( date, -1, CRect( 189, 17, 319, 35 ), DT_SINGLELINE|DT_BOTTOM );
	m_pMemDC->DrawText( pData->m_location, -1, CRect( 392, 17, 618, 35 ), DT_SINGLELINE|DT_BOTTOM );
	m_pMemDC->DrawText( intToStr( pData->m_VisDist ), -1, CRect( 104, 124, 133, 142 ), DT_SINGLELINE|DT_BOTTOM );
	if( pData->m_bVisFeet )	m_pMemDC->TextOut( 138, 127, "ft." );
	else m_pMemDC->TextOut( 138, 127, "m" );
	
	m_pMemDC->DrawText( intToStr( pData->m_nAirStart ), -1, CRect( 193, 81, 228, 99 ), DT_SINGLELINE|DT_BOTTOM );
	if( pData->m_bPSIStart )	m_pMemDC->TextOut( 236, 82, "psi" );
	else m_pMemDC->TextOut( 236, 82, "bar" );
	
	m_pMemDC->DrawText( intToStr( pData->m_nAirEnd ), -1, CRect( 277, 80, 312, 97 ), DT_SINGLELINE|DT_BOTTOM );
	if( pData->m_bPSIEnd )	m_pMemDC->TextOut( 320, 82, "psi" );	
	else m_pMemDC->TextOut( 320, 82, "bar" );	
	
	m_pMemDC->DrawText( pData->m_timeIn.Format( "%H:%M" ), -1, CRect( 198, 125, 238, 142 ), DT_SINGLELINE|DT_BOTTOM );
	m_pMemDC->DrawText( pData->m_timeOut.Format( "%H:%M" ), -1, CRect( 277, 125, 316, 142 ), DT_SINGLELINE|DT_BOTTOM );

	m_pMemDC->DrawText( intToStr( pData->m_nWeight ), -1, CRect( 565, 302, 594, 320 ), DT_SINGLELINE|DT_BOTTOM );
	if( pData->m_bKG )	m_pMemDC->TextOut( 603, 307, "kg" );
	else m_pMemDC->TextOut( 603, 307, "lbs." );		// Weight
	
	m_pMemDC->DrawText( pData->m_PGBeforeDive, -1, CRect( 282, 187, 308, 208 ), DT_VCENTER|DT_CENTER|DT_SINGLELINE );
	m_pMemDC->DrawText( pData->m_PGAfterDive, -1, CRect( 375, 187, 401, 208 ), DT_VCENTER|DT_CENTER|DT_SINGLELINE );

	if( pData->m_PGAfterDive == "?" )
	{
		CFont warnFont;
		warnFont.CreateFont(	-6 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 0, 0, 0, 0,
								ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
								DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "Arial" );
		CFont* pTmpFont = m_pMemDC->SelectObject( &warnFont );
		COLORREF oldCR = m_pMemDC->GetTextColor();
		m_pMemDC->SetTextColor( RGB( 255, 0, 0 ) );
		m_pMemDC->DrawText( "Unable to calculate ending pressure group."
								" Dive is outside of PADI dive table!",
									 -1, CRect( 384, 300, 542, 321 ), DT_CENTER|DT_WORDBREAK );
		m_pMemDC->SetTextColor( oldCR );
		m_pMemDC->SelectObject( pTmpFont );
	}
	
	m_pMemDC->DrawText( pData->m_surfaceInt.Format( "%H:%M" ), -1, CRect( 238, 188, 277, 205 ), DT_SINGLELINE|DT_BOTTOM );
	
	char bufDepth[10];
	_gcvt( pData->m_nDepth, 3, bufDepth );	CString depth = bufDepth;
	if( pData->m_nDepth - (int)pData->m_nDepth == 0 ) depth = depth.Left( depth.GetLength() );
	m_pMemDC->DrawText( depth, -1, CRect( 251, 235, 279, 251 ), DT_SINGLELINE|DT_BOTTOM );
	
	m_pMemDC->DrawText( intToStr( pData->m_nBottomTime ), -1, CRect( 319, 281, 362, 296 ), DT_SINGLELINE|DT_BOTTOM );
	m_pMemDC->DrawText( intToStr( pData->m_nStop ), -1, CRect( 392, 235, 420, 252 ), DT_SINGLELINE|DT_BOTTOM );
		
	m_pMemDC->TextOut( 508, 198, intToStr( pData->m_nRNT ) );	// RNT
	m_pMemDC->TextOut( 508, 224, intToStr( pData->m_nABT ) );	// +ABT
	m_pMemDC->TextOut( 508, 268, intToStr( pData->m_nTBT ) );	// TBT
    
    CTimeSpan tsABTDive( 0, pData->m_ABTDive.GetHour(), pData->m_ABTDive.GetMinute(), 0 );
    CTimeSpan tsABTtoDate( 0, pData->m_ABTtoDate.GetHour(), pData->m_ABTtoDate.GetMinute(), 0 );
    CTime time( 1970, 1, 1, 0, 0, 0 );
    CTimeSpan ts( 0, pData->m_pDiveSet->m_totalABT.GetHour(), 
    							pData->m_pDiveSet->m_totalABT.GetMinute(), 0 );
    
    if( pData->m_pDiveSet->m_totalABT != 0 || pData->m_pDiveSet->m_totalABT.GetMinute() != 0 )
    	ts = tsABTtoDate - tsABTDive;
    
    time = CTime( 1970, 1, 1, ts.GetHours(), ts.GetMinutes(), 0 );
    
	m_pMemDC->DrawText( time.Format( "%H:%M" ), -1,
					 CRect( 264, 358, 309, 374 ), DT_VCENTER|DT_CENTER|DT_SINGLELINE );
	m_pMemDC->DrawText( pData->m_ABTDive.Format( "%H:%M" ), -1,
					 CRect( 370, 358, 415, 374 ), DT_VCENTER|DT_CENTER|DT_SINGLELINE );
	m_pMemDC->DrawText( pData->m_ABTtoDate.Format( "%H:%M" ), -1,
					 CRect( 457, 358, 502, 374 ), DT_VCENTER|DT_CENTER|DT_SINGLELINE );
	
	int nDays = pData->m_pDiveSet->m_totalABT.GetDay() - 1;
	int nHrs = pData->m_pDiveSet->m_totalABT.GetHour();
	int nMins = pData->m_pDiveSet->m_totalABT.GetMinute();
	nHrs += (nDays * 24 );
	char buf[10];
	wsprintf( buf, (nMins <=9) ? "%d:0%d" : "%d:%d", nHrs, nMins );
	
	m_pMemDC->DrawText( pData->m_pDiveSet->m_totalABT.Format( buf ), -1,
					 CRect( 528, 360, 623, 376 ), DT_VCENTER|DT_CENTER|DT_SINGLELINE );
		                                       
	m_pMemDC->TextOut( 283, 238, "m" );	// Depth
	m_pMemDC->SetBkMode( oldBkMode );
	m_pMemDC->SelectObject( pOldFont );
	                    /*
	pDC->BitBlt( updateRect.left, updateRect.top, updateRect.Width(), updateRect.Height(), 
					m_pMemDC, updateRect.left, updateRect.top, SRCCOPY );
	m_pMemDC->SelectObject( pOldBitmap2 );
	m_pMemDC->SelectObject( pOldBrush );
	delete m_pBitmap;
	delete m_pMemDC;      */
}

/////////////////////////////////////////////////////////////////////////////
// CDiveView diagnostics

#ifdef _DEBUG
void CDiveView::AssertValid() const
{
	CView::AssertValid();
}

void CDiveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDiveDoc* CDiveView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiveDoc)));
	return (CDiveDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiveView message handlers

void CDiveView::OnCommentsZoomClicked()
{
	CCommentsDlg dlg;
	
	m_pComments->GetWindowText( dlg.m_Comments );

	if( dlg.DoModal()==IDOK )
	{
		m_pComments->SetWindowText( dlg.m_Comments );
		OnCommentsChange();		// updates CDiveData
	}
}

void CDiveView::OnCommentsChange()
{                                                              
	m_pComments->GetWindowText( GetDocument()->m_pDiveSet->GetCurRecord()->m_comments );	
	GetDocument()->SetModifiedFlag();
}

void CDiveView::OnComboDblClick()
{
	// A double click has happend on the location combo box, so we will call LButtonDown
	// which will get the infomation and delete the control
	OnLButtonDown( NULL, CPoint( 0, 0 ) );
}

LRESULT CDiveView::OnEditFldFinished( WPARAM wParam, LPARAM lParam )
{
	// Called when tab or return has been pressed in a edit control
	// wParam = a CBaseFld::fldName
	OnLButtonDown( NULL, CPoint( 0, 0 ) );	// remove the active control
	
	wParam++;	// goto next fld
	for( int loop=0; loop<=m_fldList.GetUpperBound(); loop++ )
	{
		CBaseFld* pBaseFld = (CBaseFld*)m_fldList.GetAt( loop );
		if( pBaseFld->GetFieldName() == (CBaseFld::fldName) wParam )
		{
			pBaseFld->DisplayFld( GetDocument()->m_pDiveSet->GetCurRecord() );
			break;
		}
	}    
    
	return (LRESULT) 0;
}

CString CDiveView::intToStr( int nVal )
{
	char buf[5];
	wsprintf( buf, "%d", nVal );
	return CString( buf );
}

void CDiveView::CreateChkBox( const CRect rect, const CString checked,
								const CString Unchecked, const UINT nID )
{
	CCheckBox*	pChkBox = new CCheckBox( rect, checked, Unchecked, this, nID );
	m_checkBoxes.Add( pChkBox );
}

void CDiveView::OnVisGoodClicked()
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_VISBUT_GOOD );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_VISBUT_OK );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_VISBUT_POOR );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_Visibility = CDiveData::Good;
}                                                     

void CDiveView::OnVisOkClicked()
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_VISBUT_OK );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_VISBUT_GOOD );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_VISBUT_POOR );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_Visibility = CDiveData::OK;
}

void CDiveView::OnVisPoorClicked()
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_VISBUT_POOR );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_VISBUT_GOOD );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_VISBUT_OK );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_Visibility = CDiveData::Poor;
}

void CDiveView::OnTempAirLowClicked( )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_AIR_LOW );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_AIR_MED );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_AIR_HIGH );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_air = CDiveData::Cold;
}

void CDiveView::OnTempAirMedClicked( )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_AIR_MED );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_AIR_LOW );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_AIR_HIGH );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_air = CDiveData::Warm;
}

void CDiveView::OnTempAirHighClicked( )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_AIR_HIGH );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_AIR_LOW );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_AIR_MED );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_air = CDiveData::Hot;
}	

void CDiveView::OnTempSurfaceLowClicked( )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_SURFACE_LOW );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_SURFACE_MED );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_SURFACE_HIGH );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_surface = CDiveData::Cold;
	GetDocument()->m_pDiveSet->RecalcDiveInfo();
	InvalidateRect( CRect( 375, 187, 401, 208 ),	FALSE );	// PG after dive
	InvalidateRect( CRect( 384, 300, 542, 321 ),	FALSE );	// Warning message
}

void CDiveView::OnTempSurfaceMedClicked( )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_SURFACE_MED );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_SURFACE_LOW );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_SURFACE_HIGH );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_surface = CDiveData::Warm;
	GetDocument()->m_pDiveSet->RecalcDiveInfo();
	InvalidateRect( CRect( 375, 187, 401, 208 ),	FALSE );	// PG after dive
	InvalidateRect( CRect( 384, 300, 542, 321 ),	FALSE );	// Warning message
}

void CDiveView::OnTempSurfaceHighClicked( )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_SURFACE_HIGH );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_SURFACE_LOW );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_SURFACE_MED );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_surface = CDiveData::Hot;
	GetDocument()->m_pDiveSet->RecalcDiveInfo();
	InvalidateRect( CRect( 375, 187, 401, 208 ),	FALSE );	// PG after dive
	InvalidateRect( CRect( 384, 300, 542, 321 ),	FALSE );	// Warning message
}

void CDiveView::OnTempBottomLowClicked( )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_BOTTOM_LOW );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_BOTTOM_MED );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_BOTTOM_HIGH );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bottom = CDiveData::Cold;
	GetDocument()->m_pDiveSet->RecalcDiveInfo();
	InvalidateRect( CRect( 375, 187, 401, 208 ),	FALSE );	// PG after dive  
	InvalidateRect( CRect( 384, 300, 542, 321 ),	FALSE );	// Warning message
}

void CDiveView::OnTempBottomMedClicked( )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_BOTTOM_MED );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_BOTTOM_LOW );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_BOTTOM_HIGH );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bottom = CDiveData::Warm;
	GetDocument()->m_pDiveSet->RecalcDiveInfo();
	InvalidateRect( CRect( 375, 187, 401, 208 ),	FALSE );	// PG after dive
	InvalidateRect( CRect( 384, 300, 542, 321 ),	FALSE );	// Warning message
}

void CDiveView::OnTempBottomHighClicked( )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_BOTTOM_HIGH );
	if( pCheckBox->GetState() )	return;
	pCheckBox->ChangeState();
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_BOTTOM_LOW );	pCheckBox->SetState( FALSE );
	pCheckBox = (CCheckBox*)GetCheckBox( ID_TEMP_BOTTOM_MED );	pCheckBox->SetState( FALSE );
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bottom = CDiveData::Hot;
	GetDocument()->m_pDiveSet->RecalcDiveInfo();
	InvalidateRect( CRect( 375, 187, 401, 208 ),	FALSE );	// PG after dive
	InvalidateRect( CRect( 384, 300, 542, 321 ),	FALSE );	// Warning message
}

void CDiveView::OnCheckFreshClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_FRESH );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bFresh = pCheckBox->GetState();	}
void CDiveView::OnCheckSaltClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_SALT );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bSalt = pCheckBox->GetState();		}
void CDiveView::OnCheckShoreClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_SHORE );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bShore = pCheckBox->GetState();	}
void CDiveView::OnCheckBoatClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_BOAT );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bBoat = pCheckBox->GetState();		}
void CDiveView::OnCheckWavesClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_WAVES );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bWaves = pCheckBox->GetState();	}
void CDiveView::OnCheckCurrentClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_CURRENT );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bCurrent = pCheckBox->GetState();	}
void CDiveView::OnCheckSurfClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_SURF );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bSurf = pCheckBox->GetState();		}
void CDiveView::OnCheckSurgeClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_SURGE );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bSurge = pCheckBox->GetState();	}
void CDiveView::OnCheckSocksClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_SOCKS );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bSocks = pCheckBox->GetState();	}
void CDiveView::OnCheckHoodClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_HOOD );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bHood = pCheckBox->GetState();		}
void CDiveView::OnCheckMittensClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_MITTENS );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bMittens = pCheckBox->GetState();	}
void CDiveView::OnCheckGlovesClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_GLOVES );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bGloves = pCheckBox->GetState();	}
void CDiveView::OnCheckUSuitClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_USUIT );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bUnderSuit = pCheckBox->GetState();}
void CDiveView::OnCheckDSuitClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_DSUIT );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bDrySuit = pCheckBox->GetState();	}
void CDiveView::OnCheckSemiDSuitClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_SEMIDSUIT );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bSemiDrySuit = pCheckBox->GetState();}
void CDiveView::OnCheckWetSuitClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_WETSUIT );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bWetSuit = pCheckBox->GetState();	}
void CDiveView::OnCheckCostumeClicked()
{	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_COSTUME );	pCheckBox->ChangeState();
	GetDocument()->m_pDiveSet->GetCurRecord()->m_bSwimmingCost = pCheckBox->GetState();}

CCheckBox* CDiveView::GetCheckBox( UINT nID )
{
	for( int loop=0; loop<=m_checkBoxes.GetUpperBound(); loop++ )
	{
		CCheckBox* pCheckBox = (CCheckBox*)m_checkBoxes.GetAt( loop );
		if( pCheckBox->GetID() == nID )
			return pCheckBox;
	}
	return NULL;
}

void CDiveView::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_pComments->EnableWindow( FALSE );   m_pComments->EnableWindow( TRUE );
    
    BOOL bResult;
    for( int loop=0; loop<=m_fldList.GetUpperBound(); loop++ )
	{
		CBaseFld* pBaseFld = (CBaseFld*)m_fldList.GetAt( loop );
		bResult = pBaseFld->RemoveFld( GetDocument()->m_pDiveSet->GetCurRecord() );
		if( bResult )
		{
			GetDocument()->m_pDiveSet->RecalcDiveInfo();
			InvalidateRect( CRect( 508, 198, 525, 213 ),	FALSE );	// RNT
			InvalidateRect( CRect( 508, 224, 525, 238 ),	FALSE );	// +ABT
			InvalidateRect( CRect( 508, 268, 525, 283 ),	FALSE );	// TBT
			InvalidateRect( CRect( 282, 187, 308, 208 ),	FALSE );	// PG before dive
			InvalidateRect( CRect( 375, 187, 401, 208 ),	FALSE );	// PG after dive
			InvalidateRect( CRect( 528, 360, 623, 376 ),	FALSE );	// TBT for all dives
			InvalidateRect( CRect( 264, 358, 309, 374 ),	FALSE );	// ABT to date
			InvalidateRect( CRect( 370, 358, 415, 374 ),	FALSE );	// ABT this dive
			InvalidateRect( CRect( 457, 358, 502, 374 ),	FALSE );	// ABT to date + ABT this dive
			InvalidateRect( CRect( 528, 360, 623, 376 ),	FALSE );	// Total ABT
			InvalidateRect( CRect( 319, 281, 362, 296 ),	FALSE );	// Bottom time
			
			InvalidateRect( CRect( 384, 300, 542, 321 ),	FALSE );	// Warning message
			
			GetDocument()->SetModifiedFlag();
		}                                          
	}
    
   	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_FRESH );  	pCheckBox->Enable( TRUE );
   	pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_WAVES );  	pCheckBox->Enable( TRUE );

	CView::OnLButtonDown(nFlags, point);
}

void CDiveView::OnLButtonUp(UINT nFlags, CPoint point)
{
	BOOL bHit = FALSE;
	
	for( int loop=0; loop<=m_fldList.GetUpperBound(); loop++ )
	{
		CBaseFld* pBaseFld = (CBaseFld*)m_fldList.GetAt( loop );
		if( pBaseFld->HitTest( point ) )
		{
			pBaseFld->DisplayFld( GetDocument()->m_pDiveSet->GetCurRecord() );
			// Check if it was the location combo box
			if( CRect( 392, 17, 618, 35 ).PtInRect( point ) )
				bHit = TRUE;
			break;
		}
	}
        
    // if the location combo box was made active then disable the two check boxes
    if( bHit )
    {
    	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_FRESH );  	pCheckBox->Enable( FALSE );
    	pCheckBox = (CCheckBox*)GetCheckBox( ID_CHECK_WAVES );  	pCheckBox->Enable( FALSE );
    }
	
	CView::OnLButtonUp(nFlags, point);
}

void CDiveView::ChangeChkBoxState( UINT nID, BOOL bState )
{
	CCheckBox* pCheckBox = (CCheckBox*)GetCheckBox( nID );
	pCheckBox->SetState( bState );
}

void CDiveView::InvalidateFlds( )
{
	CDiveData* pData = GetDocument()->m_pDiveSet->GetCurRecord();
	
	ChangeChkBoxState( ID_CHECK_FRESH,	pData->m_bFresh );
	ChangeChkBoxState( ID_CHECK_SALT,	pData->m_bSalt );
	ChangeChkBoxState( ID_CHECK_SHORE,	pData->m_bShore );
	ChangeChkBoxState( ID_CHECK_BOAT,	pData->m_bBoat );
	ChangeChkBoxState( ID_CHECK_WAVES,	pData->m_bWaves );
	ChangeChkBoxState( ID_CHECK_CURRENT,	pData->m_bCurrent );
	ChangeChkBoxState( ID_CHECK_SURF,	pData->m_bSurf );
	ChangeChkBoxState( ID_CHECK_SURGE,	pData->m_bSurge );
	ChangeChkBoxState( ID_CHECK_SOCKS,	pData->m_bSocks );
	ChangeChkBoxState( ID_CHECK_HOOD,	pData->m_bHood );
	ChangeChkBoxState( ID_CHECK_MITTENS,	pData->m_bMittens );
	ChangeChkBoxState( ID_CHECK_GLOVES,	pData->m_bGloves );
	ChangeChkBoxState( ID_CHECK_USUIT,	pData->m_bUnderSuit );
	ChangeChkBoxState( ID_CHECK_DSUIT,	pData->m_bDrySuit );
	ChangeChkBoxState( ID_CHECK_SEMIDSUIT,	pData->m_bSemiDrySuit );
	ChangeChkBoxState( ID_CHECK_WETSUIT,	pData->m_bWetSuit );
	ChangeChkBoxState( ID_CHECK_COSTUME,	pData->m_bSwimmingCost );
	ChangeChkBoxState( ID_TEMP_AIR_LOW,	pData->m_air == CDiveData::Cold );
	ChangeChkBoxState( ID_TEMP_AIR_MED,	pData->m_air == CDiveData::Warm );
	ChangeChkBoxState( ID_TEMP_AIR_HIGH, pData->m_air == CDiveData::Hot );
	ChangeChkBoxState( ID_TEMP_SURFACE_LOW, pData->m_surface == CDiveData::Cold );
	ChangeChkBoxState( ID_TEMP_SURFACE_MED, pData->m_surface == CDiveData::Warm );
	ChangeChkBoxState( ID_TEMP_SURFACE_HIGH, pData->m_surface == CDiveData::Hot );
	ChangeChkBoxState( ID_TEMP_BOTTOM_LOW, pData->m_bottom == CDiveData::Cold );
	ChangeChkBoxState( ID_TEMP_BOTTOM_MED, pData->m_bottom == CDiveData::Warm );
	ChangeChkBoxState( ID_TEMP_BOTTOM_HIGH, pData->m_bottom == CDiveData::Hot );
	
	switch( pData->m_Visibility )
	{
		case CDiveData::Good:	OnVisGoodClicked();	break;
		case CDiveData::OK:		OnVisOkClicked();	break;
		case CDiveData::Poor:	OnVisPoorClicked();	break;
	}
                               
	InvalidateRect( CRect( 75, 16, 145, 37 ),	FALSE );		// DiveNo
	InvalidateRect( CRect( 104, 124, 133, 142 ),	FALSE );	// Visibility
	InvalidateRect( CRect( 189, 17, 318, 35 ),	FALSE );		// Date
	InvalidateRect( CRect( 392, 17, 618, 35 ),	FALSE );		// Location
	InvalidateRect( CRect( 193, 81, 228, 99 ),	FALSE );		// AirStart
	InvalidateRect( CRect( 277, 80, 312, 97 ),	FALSE );		// AirEnd
	InvalidateRect( CRect( 195, 125, 237, 142 ),	FALSE );	// TimeIn
	InvalidateRect( CRect( 274, 125, 316, 142 ),	FALSE );	// TimeOut
	InvalidateRect( CRect( 237, 188, 277, 206 ),	FALSE );	// SI
	InvalidateRect( CRect( 250, 235, 279, 252 ),	FALSE );	// Depth
	InvalidateRect( CRect( 318, 281, 362, 297 ),	FALSE );	// BottomTime
	InvalidateRect( CRect( 391, 235, 420, 253 ),	FALSE );	// Decomp. Stop
	InvalidateRect( CRect( 565, 302, 594, 320 ),	FALSE );	// Weight
	
	InvalidateRect( CRect( 508, 198, 525, 213 ),	FALSE );	// RNT
	InvalidateRect( CRect( 508, 224, 525, 238 ),	FALSE );	// +ABT
	InvalidateRect( CRect( 508, 268, 525, 283 ),	FALSE );	// TBT

	InvalidateRect( CRect( 282, 187, 308, 208 ),	FALSE );	// PG before dive
	InvalidateRect( CRect( 375, 187, 401, 208 ),	FALSE );	// PG after dive
	InvalidateRect( CRect( 528, 360, 623, 376 ),	FALSE );	// TBT for all dives
	InvalidateRect( CRect( 264, 358, 309, 374 ),	FALSE );	// ABT to date
	InvalidateRect( CRect( 370, 358, 415, 374 ),	FALSE );	// ABT this dive
	InvalidateRect( CRect( 457, 358, 502, 374 ),	FALSE );	// ABT to date + ABT this dive
	InvalidateRect( CRect( 528, 360, 623, 376 ),	FALSE );	// Total ABT
	
	InvalidateRect( CRect( 384, 300, 542, 321 ),	FALSE );	// Warning message
	                                     
	// Comments
	m_pComments->SetWindowText( pData->m_comments );	
}

void CDiveView::OnRecordAdd()
{
	OnLButtonDown( NULL, CPoint( 0, 0 ) );	// remove any active edit controls
	CDiveData* pOldRec = GetDocument()->m_pDiveSet->GetCurRecord();
	CDiveData* pData = new CDiveData();
	GetDocument()->m_pDiveSet->Add( pData );
	pData->TransferInfo( pOldRec );
	InvalidateFlds( );
}

void CDiveView::OnRecordDelete()
{
	OnLButtonDown( NULL, CPoint( 0, 0 ) );	// remove any active edit controls
	if( AfxMessageBox( "Delete this dive?", MB_YESNO )==IDYES )
		GetDocument()->m_pDiveSet->Delete();
	// int nTmp = GetDocument()->m_pDiveSet->GetNoOfRecs();
	if( GetDocument()->m_pDiveSet->GetNoOfRecs()==-1 )
	{
		CDiveData* pData = new CDiveData();
		GetDocument()->m_pDiveSet->Add( pData );
	}
    else
    GetDocument()->m_pDiveSet->ChangeDiveNos( 0 );
	InvalidateFlds( );
}

void CDiveView::OnRecordFirst()
{
	BOOL bModified = GetDocument()->IsModified();
	OnLButtonDown( NULL, CPoint( 0, 0 ) );	// remove any active edit controls
	GetDocument()->m_pDiveSet->FirstRecord();
	InvalidateFlds( );
	GetDocument()->SetModifiedFlag( bModified );
} 

void CDiveView::OnRecordLast()
{
	BOOL bModified = GetDocument()->IsModified();
	OnLButtonDown( NULL, CPoint( 0, 0 ) );	// remove any active edit controls
	GetDocument()->m_pDiveSet->LastRecord();
	InvalidateFlds( );
	GetDocument()->SetModifiedFlag( bModified );
}
void CDiveView::OnRecordNext()
{
	BOOL bModified = GetDocument()->IsModified();
	OnLButtonDown( NULL, CPoint( 0, 0 ) );	// remove any active edit controls
	GetDocument()->m_pDiveSet->NextRecord();
	InvalidateFlds( );
	GetDocument()->SetModifiedFlag( bModified );
}

void CDiveView::OnRecordPrev()
{
	BOOL bModified = GetDocument()->IsModified();
	OnLButtonDown( NULL, CPoint( 0, 0 ) );	// remove any active edit controls
	GetDocument()->m_pDiveSet->PrevRecord();
	InvalidateFlds( );
	GetDocument()->SetModifiedFlag( bModified );
}

void CDiveView::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{	pCmdUI->Enable( GetDocument()->m_pDiveSet->GetCurIndex() != 0 ? TRUE : FALSE );	}

void CDiveView::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( GetDocument()->m_pDiveSet->GetCurIndex() != 
						GetDocument()->m_pDiveSet->GetNoOfRecs() ? TRUE : FALSE );
}

void CDiveView::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( GetDocument()->m_pDiveSet->GetCurIndex() < 
						GetDocument()->m_pDiveSet->GetNoOfRecs() ? TRUE : FALSE );
}
	
void CDiveView::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{	pCmdUI->Enable( GetDocument()->m_pDiveSet->GetCurIndex() > 0 ? TRUE : FALSE );	}
