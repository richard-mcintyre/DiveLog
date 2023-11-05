// divepg.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "divepg.h"
#include "divedoc.h"
#include "divevw.h"
#include "editdate.h"
#include "divedata.h"
#include "mainfrm.h"
#include "defset.h"
#include "notesdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDivePg1 dialog


CDivePg1::CDivePg1(CDiveView* pParent)
	: CDialog(CDivePg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDivePg1)
	m_editVis = "0";
	m_editAirStart = "0";
	m_meaAirStart = "bar";
	m_meaVis = "ft.";
	m_editAirEnd = "0";
	m_meaAirEnd = "bar";
	m_editTimeIn = "00:00";
	m_editTimeOut = "00:00";
	m_radioVis = 0;
	m_radioAir = 1;
	m_radioBottom = 1;
	m_radioSurface = 1;
	//}}AFX_DATA_INIT
	m_pView = pParent;
	m_pDateCtrl = new CEditDate;
	m_tmpPoint = CPoint( 0, 0 );
	m_bCaptured = FALSE;
}

CDivePg1::~CDivePg1()
{
	delete m_pDateCtrl;
}

void CDivePg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDivePg1)
	DDX_Control(pDX, IDC_LOCATION_COMBO, m_ctlLocation);
	DDX_Text(pDX, IDC_EDIT_VIS, m_editVis);
	DDX_Text(pDX, IDC_EDIT_AIR_START, m_editAirStart);
	DDX_Text(pDX, IDC_MEASURE_AIR_START, m_meaAirStart);
	DDX_Text(pDX, IDC_MEASURE_VIS, m_meaVis);
	DDX_Text(pDX, IDC_EDIT_AIR_END, m_editAirEnd);
	DDX_Text(pDX, IDC_MEASURE_AIR_END, m_meaAirEnd);
	DDX_Text(pDX, IDC_EDIT_TIME_IN, m_editTimeIn);
	DDX_Text(pDX, IDC_EDIT_TIME_OUT, m_editTimeOut);
	DDX_Radio(pDX, IDC_RADIO_VIS, m_radioVis);
	DDX_Radio(pDX, IDC_RADIO_AIR, m_radioAir);
	DDX_Radio(pDX, IDC_RADIO_BOTTOM, m_radioBottom);
	DDX_Radio(pDX, IDC_RADIO_SURFACE, m_radioSurface);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDivePg1, CDialog)
	//{{AFX_MSG_MAP(CDivePg1)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_EDIT_VIS, OnKillfocusEditVis)
	ON_EN_KILLFOCUS(IDC_EDIT_AIR_START, OnKillfocusEditAirStart)
	ON_EN_KILLFOCUS(IDC_EDIT_AIR_END, OnKillfocusEditAirEnd)
	ON_EN_KILLFOCUS(IDC_EDIT_TIME_IN, OnKillfocusEditTimeIn)
	ON_EN_KILLFOCUS(IDC_EDIT_TIME_OUT, OnKillfocusEditTimeOut)
	ON_BN_CLICKED(IDC_RADIO_VIS, OnRadioVis)
	ON_BN_CLICKED(IDC_RADIO_AIR, OnRadioAir)
	ON_BN_CLICKED(IDC_RADIO_SURFACE, OnRadioSurface)
	ON_BN_CLICKED(IDC_RADIO_BOTTOM, OnRadioBottom)
	ON_EN_CHANGE(IDC_EDIT_DATE, OnChangeEditDate)
	ON_CBN_EDITCHANGE(IDC_LOCATION_COMBO, OnEditchangeLocationCombo)
	ON_CBN_SELENDOK(IDC_LOCATION_COMBO, OnSelendokLocationCombo)
	ON_EN_CHANGE(IDC_EDIT_VIS, OnChangeEditVis)
	ON_EN_CHANGE(IDC_EDIT_AIR_START, OnChangeEditAirStart)
	ON_EN_CHANGE(IDC_EDIT_AIR_END, OnChangeEditAirEnd)
	ON_EN_CHANGE(IDC_EDIT_TIME_IN, OnChangeEditTimeIn)
	ON_EN_CHANGE(IDC_EDIT_TIME_OUT, OnChangeEditTimeOut)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO_SURFACE_WARM, OnRadioSurfaceWarm)
	ON_BN_CLICKED(IDC_RADIO_SURFACE_HOT, OnRadioSurfaceHot)
	ON_BN_CLICKED(IDC_RADIO_BOTTOM_HOT, OnRadioBottomHot)
	ON_BN_CLICKED(IDC_RADIO_BOTTOM_WARM, OnRadioBottomWarm)
	ON_BN_CLICKED(IDC_RADIO_AIR_HOT, OnRadioAirHot)
	ON_BN_CLICKED(IDC_RADIO_AIR_WARM, OnRadioAirWarm)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_VIS_MEDIUM, OnRadioVis)
	ON_BN_CLICKED(IDC_VIS_POOR, OnRadioVis)
	//}}AFX_MSG_MAP
	ON_MESSAGE( PPC_DATECHANGED, OnDateTest )
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDivePg1 message handlers

LRESULT CDivePg1::OnDateTest(WPARAM WParam, LPARAM LParam)
{
	//AfxMessageBox( "OK" );
	return 0L;
}

BOOL CDivePg1::Create( CDiveView* pParent, UINT nDlg )
{
	m_pView = pParent;
	return CDialog::Create( nDlg, pParent );
}

BOOL CDivePg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	CClientDC dc( this );
	m_textFont.CreateFont (-9 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 400, 0, 0, 0,
				   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
				   DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");
	m_smallFont.CreateFont (-7 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 400, 0, 0, 0,
				   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
				   DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "Arial");
    
    m_ctlLocation.SetFont( &m_textFont);
    m_pDateCtrl->SubclassDlgItem( IDC_EDIT_DATE, this );
	m_pDateCtrl->AttachCombo();
	m_pDateCtrl->SetFont( &m_textFont );
	CTime curDate = CTime::GetCurrentTime();
	CString date = curDate.Format( "%d/%m/%y" );
	m_pDateCtrl->InitDate( date ); 

	m_ctlLocation.ResetContent();
	for( int loop=0; loop<=CDiveApp::m_locations.GetUpperBound(); loop++ )
		m_ctlLocation.AddString( CDiveApp::m_locations.GetAt( loop ) );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDivePg1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CDC* pDisplayMemDC = new CDC;
	CBitmap* pTanks = new CBitmap;
	pTanks->LoadBitmap( IDB_DIVEPG1 );
	pDisplayMemDC->CreateCompatibleDC( &dc );
	
	CBitmap* pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject( pTanks );
	if( CMainFrame::bVGA )
	{
		dc.BitBlt( 20, 135, 10, 31, pDisplayMemDC, 0, 0, SRCCOPY );		// Full tank
		dc.BitBlt( 105, 135, 10, 31, pDisplayMemDC, 10, 0, SRCCOPY );	// Empty tank
		dc.BitBlt( 9, 260, 39, 6, pDisplayMemDC, 20, 0, SRCCOPY );		// Half circles
		dc.BitBlt( 48, 260, 39, 6, pDisplayMemDC, 20, 0, SRCCOPY );
		dc.BitBlt( 87, 260, 39, 6, pDisplayMemDC, 20, 0, SRCCOPY );
		dc.BitBlt( 126, 260, 39, 6, pDisplayMemDC, 20, 0, SRCCOPY );
		dc.BitBlt( 165, 260, 26, 6, pDisplayMemDC, 20, 0, SRCCOPY );
		dc.BitBlt( 15, 220, 37, 22, pDisplayMemDC, 0, 31, SRCCOPY );		// 32-50f / 0-10c
		dc.BitBlt( 60, 220, 37, 22, pDisplayMemDC, 0, 53, SRCCOPY );		// 50-70f / 10-21c
		dc.BitBlt( 105, 220, 23, 22, pDisplayMemDC, 0, 75, SRCCOPY );		// 70+f / 21+c
	}
	else
	{
		dc.BitBlt( 50, 177, 10, 31, pDisplayMemDC, 0, 0, SRCCOPY );		// Full tank
		dc.BitBlt( 135, 177, 10, 31, pDisplayMemDC, 10, 0, SRCCOPY );	// Empty tank
		dc.BitBlt( 39, 332, 39, 6, pDisplayMemDC, 20, 0, SRCCOPY );		// Half circles
		dc.BitBlt( 78, 332, 39, 6, pDisplayMemDC, 20, 0, SRCCOPY );
		dc.BitBlt( 117, 332, 39, 6, pDisplayMemDC, 20, 0, SRCCOPY );
		dc.BitBlt( 156, 332, 39, 6, pDisplayMemDC, 20, 0, SRCCOPY );
		dc.BitBlt( 195, 332, 26, 6, pDisplayMemDC, 20, 0, SRCCOPY );
		dc.BitBlt( 45, 292, 37, 22, pDisplayMemDC, 0, 31, SRCCOPY );		// 32-50f / 0-10c
		dc.BitBlt( 90, 292, 37, 22, pDisplayMemDC, 0, 53, SRCCOPY );		// 50-70f / 10-21c
		dc.BitBlt( 135, 292, 23, 22, pDisplayMemDC, 0, 75, SRCCOPY );		// 70+f / 21+c
	}
		
	delete pDisplayMemDC->SelectObject( pOldBitmap );	// deletes pTanks
	delete pDisplayMemDC;
	
	CFont* pOldFont = dc.SelectObject( &m_smallFont );
	
	CPoint curIndex = m_pView->GetDocument()->GetCurIndex( );
	char buf[50];
	wsprintf( buf, "Dive %d / %d\0", curIndex.x+1, curIndex.y+1 );
	if( CMainFrame::bVGA )
		dc.DrawText( buf, -1, CRect( 0, 320, 200, 335 ), DT_CENTER );
	else
		dc.DrawText( buf, -1, CRect( 0, 420, 270, 435 ), DT_CENTER );
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDivePg1::OnKillfocusEditVis()
{	UpdateData( FALSE );	}

void CDivePg1::OnChangeEditVis()
{
	UpdateData( TRUE );	m_editVis.MakeUpper();
	if( m_editVis.Right( 1 )=="M" )
	{	m_meaVis = "mts.";	m_pView->GetDocument()->GetCurRecord()->SetVisFt( FALSE );	}
	else if( m_editVis.Right( 1 )=="F" )
	{	m_meaVis = "ft.";	m_pView->GetDocument()->GetCurRecord()->SetVisFt( TRUE );	}
	
	if( m_editVis.Right( 1 )=="M" || m_editVis.Right( 1 )=="F" )
		m_editVis = m_editVis.Left( m_editVis.GetLength()-1 );
	
	float dist = (float)atof( m_editVis );	// value to be stored in record
	char buf[10];	_gcvt( dist, 3, buf );
	m_pView->GetDocument()->GetCurRecord()->SetVisDist( dist );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnKillfocusEditAirStart()
{	UpdateData( FALSE );	}

void CDivePg1::OnChangeEditAirStart()
{
	UpdateData( TRUE );	m_editAirStart.MakeUpper();
	if( m_editAirStart.Right( 1 )=="B" )
	{
		m_meaAirStart = "bar";	m_meaAirEnd = "bar";
		m_pView->GetDocument()->GetCurRecord()->SetAirPSI( FALSE );
		m_editAirStart = m_editAirStart.Left( m_editAirStart.GetLength()-1 );
	}
	else if( m_editAirStart.Right( 1 )=="P" )
	{
		m_meaAirStart = "psi.";	m_meaAirEnd = "psi.";
		m_pView->GetDocument()->GetCurRecord()->SetAirPSI( TRUE );
		m_editAirStart = m_editAirStart.Left( m_editAirStart.GetLength()-1 );
	}

	const char* pszText = m_editAirStart;
	int nAirStart = (int)strtol( pszText, (char**)&pszText, 10 );
	char buf[5];	wsprintf( buf, "%d", nAirStart );	m_editAirStart = buf;
	m_pView->GetDocument()->GetCurRecord()->SetAirStart( nAirStart );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnKillfocusEditAirEnd()
{	UpdateData( FALSE );	}

void CDivePg1::OnChangeEditAirEnd()
{
	UpdateData( TRUE );	m_editAirEnd.MakeUpper();
	if( m_editAirEnd.Right( 1 )=="B" )
	{
		m_meaAirStart = "bar";	m_meaAirEnd = "bar";
		m_pView->GetDocument()->GetCurRecord()->SetAirPSI( FALSE );
		m_editAirEnd = m_editAirEnd.Left( m_editAirEnd.GetLength()-1 );
	}
	else if( m_editAirEnd.Right( 1 )=="P" )
	{
		m_meaAirStart = "psi.";	m_meaAirEnd = "psi.";
		m_pView->GetDocument()->GetCurRecord()->SetAirPSI( TRUE );
		m_editAirEnd = m_editAirEnd.Left( m_editAirEnd.GetLength()-1 );
	}

	const char* pszText = m_editAirEnd;
	int nAirEnd = (int)strtol( pszText, (char**)&pszText, 10 );
	char buf[5];	wsprintf( buf, "%d", nAirEnd );	m_editAirEnd = buf;
	m_pView->GetDocument()->GetCurRecord()->SetAirEnd( nAirEnd );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnKillfocusEditTimeIn()
{	UpdateData( FALSE );	}

void CDivePg1::OnChangeEditTimeIn()
{
	UpdateData( TRUE );
	CString hour = m_editTimeIn.Left( 2 );	const char* pszHour = hour;
	CString mins = m_editTimeIn.Right( 2 );	const char* pszMins = mins;
	int nHour = (int)strtol( pszHour, (char**)&pszHour, 10 );
	int nMins = (int)strtol( pszMins, (char**)&pszMins, 10 );
	CTime timeIn = CTime( 1970, 1, 1, nHour, nMins, 0 );
	m_editTimeIn = timeIn.Format( "%H:%M" );
	m_pView->GetDocument()->GetCurRecord()->SetTimeIn( timeIn );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnKillfocusEditTimeOut()
{	UpdateData( FALSE );	}

void CDivePg1::OnChangeEditTimeOut()
{
	UpdateData( TRUE );
	CString hour = m_editTimeOut.Left( 2 );		const char* pszHour = hour;
	CString mins = m_editTimeOut.Right( 2 );	const char* pszMins = mins;
	int nHour = (int)strtol( pszHour, (char**)&pszHour, 10 );
	int nMins = (int)strtol( pszMins, (char**)&pszMins, 10 );
	CTime timeOut = CTime( 1970, 1, 1, nHour, nMins, 0 );
	m_editTimeOut = timeOut.Format( "%H:%M" );
	m_pView->GetDocument()->GetCurRecord()->SetTimeOut( timeOut );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioVis()
{
	UpdateData( TRUE );
	switch( m_radioVis )
	{
		case 0:	m_pView->GetDocument()->GetCurRecord()->SetVis( CDiveData::Good );		break;
		case 1:	m_pView->GetDocument()->GetCurRecord()->SetVis( CDiveData::Medium );	break;
		case 2:	m_pView->GetDocument()->GetCurRecord()->SetVis( CDiveData::Poor );		break;
	}
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioAir()
{
	m_pView->GetDocument()->GetCurRecord()->SetAirTemp( CDiveData::Cold );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioAirHot()
{
	m_pView->GetDocument()->GetCurRecord()->SetAirTemp( CDiveData::Hot );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioAirWarm()
{
	m_pView->GetDocument()->GetCurRecord()->SetAirTemp( CDiveData::Warm );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioSurface()
{
	m_pView->GetDocument()->GetCurRecord()->SetSurfaceTemp( CDiveData::Cold );
	m_pView->GetDivePage2()->CalcDiveTables();
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioSurfaceWarm()
{                                              
	m_pView->GetDocument()->GetCurRecord()->SetSurfaceTemp( CDiveData::Warm );
	m_pView->GetDivePage2()->CalcDiveTables();
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioSurfaceHot()
{                                              
	m_pView->GetDocument()->GetCurRecord()->SetSurfaceTemp( CDiveData::Hot );
	m_pView->GetDivePage2()->CalcDiveTables();
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioBottom()
{
	m_pView->GetDocument()->GetCurRecord()->SetBottomTemp( CDiveData::Cold );
	m_pView->GetDivePage2()->CalcDiveTables();
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioBottomHot()
{
	m_pView->GetDocument()->GetCurRecord()->SetBottomTemp( CDiveData::Hot );
	m_pView->GetDivePage2()->CalcDiveTables();
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnRadioBottomWarm()
{
	m_pView->GetDocument()->GetCurRecord()->SetBottomTemp( CDiveData::Warm );
	m_pView->GetDivePage2()->CalcDiveTables();
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::UpdateControls( CDiveData* pData )
{
	ASSERT_VALID( pData );
	m_ctlLocation.SetWindowText( pData->GetLoc( ) );
	CString date = pData->GetDate().Format( "%d/%m/%y" );	m_pDateCtrl->InitDate( date );
	switch( pData->GetVis( ) )
	{
		case CDiveData::Good:	m_radioVis = 0;	break;
		case CDiveData::Medium:	m_radioVis = 1;	break;
		case CDiveData::Poor:	m_radioVis = 2;	break;
	}
	char buf[10];	_gcvt( pData->GetVisDist(), 3, buf );
	m_editVis = buf;
	m_meaVis = pData->GetVisFt() ? "ft." : "mts.";
	wsprintf( buf, "%d", pData->GetAirStart() );
	m_editAirStart = buf;
    wsprintf( buf, "%d", pData->GetAirEnd() );
	m_editAirEnd = buf;
	m_meaAirStart = m_meaAirEnd = pData->GetAirPSI() ? "psi." : "bar";
	m_editTimeIn = pData->GetTimeIn().Format( "%H:%M" );
	m_editTimeOut = pData->GetTimeOut().Format( "%H:%M" );
	switch( pData->GetAirTemp( ) )
	{
		case CDiveData::Cold:	m_radioAir = 0;	break;
		case CDiveData::Warm:	m_radioAir = 1;	break;
		case CDiveData::Hot:	m_radioAir = 2;	break;
	}
	switch( pData->GetSurfaceTemp( ) )
	{
		case CDiveData::Cold:	m_radioSurface = 0;	break;
		case CDiveData::Warm:	m_radioSurface = 1;	break;
		case CDiveData::Hot:	m_radioSurface = 2;	break;
	}
	switch( pData->GetBottomTemp( ) )
	{
		case CDiveData::Cold:	m_radioBottom = 0;	break;
		case CDiveData::Warm:	m_radioBottom = 1;	break;
		case CDiveData::Hot:	m_radioBottom = 2;	break;
	}
	
	UpdateData( FALSE );
	//InvalidateRect( CRect( 20, 320, 180, 335 ) );
	if( CMainFrame::bVGA )
		InvalidateRect( CRect( 0, 320, 200, 335 ) );
	else
		InvalidateRect( CRect( 0, 420, 270, 435 ) );
}

void CDivePg1::OnChangeEditDate()
{       
	if( m_pDateCtrl->IsWindowVisible() )
	{
		CString dateStr;
		m_pDateCtrl->GetWindowText( dateStr );
		int nMonth, nDay, nYear;
		if( m_pDateCtrl->ParseDate ( dateStr, nMonth, nDay, nYear)==FALSE )
			return;
		CTime tmpDate (nYear, nMonth, nDay, 0, 0, 0);
		CTime oldDate = m_pView->GetDocument()->GetCurRecord()->GetDate();
		if( oldDate != tmpDate )
		{
			m_pView->GetDocument()->GetCurRecord()->SetDate( tmpDate );
			m_pView->GetDocument()->DateChanged();
		}
	}
		
	m_pView->GetDocument()->SetModifiedFlag( ); 
}
	/*
void CDivePg1::OnKillfocusEditDate()
{	
	if( !m_pDateCtrl->IsWindowVisible() )
	{
		AfxMessageBox( "Kill focus" );
		CString dateStr;
		m_pDateCtrl->GetWindowText( dateStr );
		int nMonth, nDay, nYear;
		m_pDateCtrl->ParseDate ( dateStr, nMonth, nDay, nYear);
		CTime tmpDate (nYear, nMonth, nDay, 0, 0, 0);
		CTime oldDate = m_pView->GetDocument()->GetCurRecord()->GetDate();
		if( oldDate != tmpDate )
		{
			m_pView->GetDocument()->GetCurRecord()->SetDate( tmpDate );
			m_pView->GetDocument()->DateChanged();
		}
		m_pView->GetDocument()->SetModifiedFlag( ); 
	}
}	  */

void CDivePg1::OnEditchangeLocationCombo()
{
	UpdateData( TRUE );
	CString locStr;		m_ctlLocation.GetWindowText( locStr );
	m_pView->GetDocument()->GetCurRecord()->SetLoc( locStr );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnSelendokLocationCombo()
{
	UpdateData( TRUE );
	CString locStr;
	m_ctlLocation.GetLBText( m_ctlLocation.GetCurSel(), locStr );
	m_pView->GetDocument()->GetCurRecord()->SetLoc( locStr );

	// Go through the list of defaults
	for( int i=0; i <=m_pView->GetDocument()->m_defDives.GetUpperBound(); i++ )
	{
		CDefDive* pDefDive = (CDefDive*)m_pView->GetDocument()->m_defDives.GetAt( i );
		if( pDefDive->GetLocation() == locStr && !pDefDive->IsNoDefaults() )
		{
			CDivePg2* pPage2 = m_pView->GetDivePage2( );
			CDiveData* pData = m_pView->GetDocument()->GetCurRecord();
			pData->SetBoat( pDefDive->GetCBState( DEF_BOAT ) );
			pData->SetCurrent( pDefDive->GetCBState( DEF_CURRENT ) );
			pData->SetDrySuit( pDefDive->GetCBState( DEF_DRYSUIT ) );
			pData->SetFresh( pDefDive->GetCBState( DEF_FRESH ) );
			pData->SetGloves( pDefDive->GetCBState( DEF_GLOVES ) );
			pData->SetHood( pDefDive->GetCBState( DEF_HOOD ) );
			pData->SetMittens( pDefDive->GetCBState( DEF_MITTENS ) );
			pData->SetSalt( pDefDive->GetCBState( DEF_SALT ) );
			pData->SetSDrySuit( pDefDive->GetCBState( DEF_SDRYSUIT ) );
			pData->SetShore( pDefDive->GetCBState( DEF_SHORE ) );
			pData->SetSocks( pDefDive->GetCBState( DEF_SOCKS ) );
			pData->SetSurf( pDefDive->GetCBState( DEF_SURF ) );
			pData->SetSurge( pDefDive->GetCBState( DEF_SURGE ) );
			pData->SetUSuit( pDefDive->GetCBState( DEF_USUIT ) );
			pData->SetWaves( pDefDive->GetCBState( DEF_WAVES ) );
			pData->SetWetSuit( pDefDive->GetCBState( DEF_WETSUIT ) );
			pData->SetWeight( pDefDive->GetWeight() );
			pData->SetWeightKG( pDefDive->IsWeightKgs() );

			pPage2->UpdateControls( pData );
			break;
		}
	}
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg1::OnOK()
{
	//AfxMessageBox( "CDivePg1::OnOK - trapped!" );
}

void CDivePg1::OnCancel()
{
	//AfxMessageBox( "CDivePg1::OnCancel - trapped!" );
}

/////////////////////////////////////////////////////////////////////////////
// CDivePg2 dialog


CDivePg2::CDivePg2(CDiveView* pParent /*=NULL*/)
	: CDialog(CDivePg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDivePg2)
	m_editSI = "00:00";
	m_meaDepth = "mts.";
	m_editStop = 0;
	m_editBottomTime = 0;
	m_editWeight = "0";
	m_meaWeight = "lbs.";
	m_bBoat = FALSE;
	m_bCurrent = FALSE;
	m_bDrySuit = FALSE;
	m_bFresh = FALSE;
	m_bGloves = FALSE;
	m_bHood = FALSE;
	m_bMittens = FALSE;
	m_bSalt = FALSE;
	m_bSDrySuit = FALSE;
	m_bShore = FALSE;
	m_bSocks = FALSE;
	m_bSurf = FALSE;
	m_bSurge = FALSE;
	m_bUnderSuit = FALSE;
	m_bWaves = FALSE;
	m_bWetSuit = FALSE;
	m_pgAfter = "A";
	m_pgBefore = "A";
	m_strABT = _T("");
	m_strRNT = _T("");
	m_strTBT = _T("");
	m_editDepth = "";
	//}}AFX_DATA_INIT
	m_pView = pParent;
}

void CDivePg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDivePg2)
	DDX_Text(pDX, IDC_EDIT_SI, m_editSI);
	DDX_Text(pDX, IDC_MEASURE_DEPTH, m_meaDepth);
	DDX_Text(pDX, IDC_EDIT_STOP, m_editStop);
	DDV_MinMaxUInt(pDX, m_editStop, 0, 3000);
	DDX_Text(pDX, IDC_EDIT_BOTTOM_TIME, m_editBottomTime);
	DDV_MinMaxUInt(pDX, m_editBottomTime, 0, 3000);
	DDX_Text(pDX, IDC_EDIT_WEIGHT, m_editWeight);
	DDX_Text(pDX, IDC_MEASURE_WEIGHT, m_meaWeight);
	DDX_Check(pDX, IDC_CHECK_BOAT, m_bBoat);
	DDX_Check(pDX, IDC_CHECK_CURRENT, m_bCurrent);
	DDX_Check(pDX, IDC_CHECK_DRYSUIT, m_bDrySuit);
	DDX_Check(pDX, IDC_CHECK_FRESH, m_bFresh);
	DDX_Check(pDX, IDC_CHECK_GLOVES, m_bGloves);
	DDX_Check(pDX, IDC_CHECK_HOOD, m_bHood);
	DDX_Check(pDX, IDC_CHECK_MITTENS, m_bMittens);
	DDX_Check(pDX, IDC_CHECK_SALT, m_bSalt);
	DDX_Check(pDX, IDC_CHECK_SEMI_DRYSUIT, m_bSDrySuit);
	DDX_Check(pDX, IDC_CHECK_SHORE, m_bShore);
	DDX_Check(pDX, IDC_CHECK_SOCKS, m_bSocks);
	DDX_Check(pDX, IDC_CHECK_SURF, m_bSurf);
	DDX_Check(pDX, IDC_CHECK_SURGE, m_bSurge);
	DDX_Check(pDX, IDC_CHECK_UNDERSUIT, m_bUnderSuit);
	DDX_Check(pDX, IDC_CHECK_WAVES, m_bWaves);
	DDX_Check(pDX, IDC_CHECK_WETSUIT, m_bWetSuit);
	DDX_Text(pDX, IDC_PG_AFTER, m_pgAfter);
	DDX_Text(pDX, IDC_PG_BEFORE, m_pgBefore);
	DDX_Text(pDX, IDC_ABT, m_strABT);
	DDX_Text(pDX, IDC_RNT, m_strRNT);
	DDX_Text(pDX, IDC_TBT, m_strTBT);
	DDX_Text(pDX, IDC_EDIT_DEPTH, m_editDepth);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDivePg2, CDialog)
	//{{AFX_MSG_MAP(CDivePg2)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_EDIT_SI, OnKillfocusEditSI)
	ON_EN_KILLFOCUS(IDC_EDIT_DEPTH, OnKillfocusEditDepth)
	ON_EN_KILLFOCUS(IDC_EDIT_BOTTOM_TIME, OnKillfocusEditBottomTime)
	ON_EN_KILLFOCUS(IDC_EDIT_STOP, OnKillfocusEditStop)
	ON_BN_CLICKED(IDC_NOTES, OnNotes)
	ON_EN_KILLFOCUS(IDC_EDIT_WEIGHT, OnKillfocusEditWeight)
	ON_BN_CLICKED(IDC_CHECK_BOAT, OnCheckBoxClicked)
	ON_EN_CHANGE(IDC_EDIT_SI, OnChangeEditSi)
	ON_EN_CHANGE(IDC_EDIT_DEPTH, OnChangeEditDepth)
	ON_EN_CHANGE(IDC_EDIT_BOTTOM_TIME, OnChangeEditBottomTime)
	ON_EN_CHANGE(IDC_EDIT_STOP, OnChangeEditStop)
	ON_EN_CHANGE(IDC_EDIT_WEIGHT, OnChangeEditWeight)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_CHECK_CURRENT, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_DRYSUIT, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_FRESH, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_GLOVES, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_HOOD, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_MITTENS, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_SALT, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_SEMI_DRYSUIT, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_SHORE, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_SOCKS, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_SURF, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_SURGE, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_UNDERSUIT, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_WAVES, OnCheckBoxClicked)
	ON_BN_CLICKED(IDC_CHECK_WETSUIT, OnCheckBoxClicked)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDivePg2 message handlers

BOOL CDivePg2::Create( CDiveView* pParent, UINT nDlg )
{
	m_pView = pParent;
	return CDialog::Create( nDlg, pParent );
}

void CDivePg2::OnOK()
{
	//AfxMessageBox( "CDivePg2::OnOK - trapped!" );
}

void CDivePg2::OnCancel()
{
	//AfxMessageBox( "CDivePg2::OnCancel - trapped!" );
}

void CDivePg2::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CDC* pDisplayMemDC = new CDC;
	CBitmap* pTanks = new CBitmap;
	pTanks->LoadBitmap( IDB_DIVEPG2 );
	pDisplayMemDC->CreateCompatibleDC( &dc );
	
	CBitmap* pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject( pTanks );
	if( CMainFrame::bVGA )
		dc.BitBlt( 100, 10, 21, 51, pDisplayMemDC, 0, 0, SRCCOPY );		// Tank
	else
		dc.BitBlt( 130, 30, 21, 51, pDisplayMemDC, 0, 0, SRCCOPY );		// Tank
	
	delete pDisplayMemDC->SelectObject( pOldBitmap );	// deletes pTanks
	delete pDisplayMemDC;
	
	CFont* pOldFont = dc.SelectObject( &m_smallFont );

	CPoint curIndex = m_pView->GetDocument()->GetCurIndex( );
	char buf[50];
	wsprintf( buf, "Dive %d / %d\0", curIndex.x+1, curIndex.y+1 );

	if( CMainFrame::bVGA )
		dc.DrawText( buf, -1, CRect( 20, 320, 180, 335 ), DT_CENTER );
	else
		dc.DrawText( buf, -1, CRect( 0, 420, 260, 435 ), DT_CENTER );

	dc.SelectObject( pOldFont );
		
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CDivePg2::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CClientDC dc( this );
	
	m_smallFont.CreateFont (-7 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 400, 0, 0, 0,
				   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
				   DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "Arial");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDivePg2::OnNotes()
{
	CNotesDlg dlg;

	dlg.m_strNotes = m_pView->GetDocument()->GetCurRecord()->GetNotes();
	if( dlg.DoModal()==IDOK )
	{
		m_pView->GetDocument()->GetCurRecord()->SetNotes( dlg.m_strNotes );
		m_pView->GetDocument()->SetModifiedFlag( );
	}
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg2::OnKillfocusEditSI()
{
	CalcDiveTables();
	UpdateData( FALSE );
}

void CDivePg2::OnChangeEditSi()
{
	UpdateData( TRUE );
	CString hour = m_editSI.Left( 2 );	const char* pszHour = hour;
	CString mins = m_editSI.Right( 2 );	const char* pszMins = mins;
	int nHour = (int)strtol( pszHour, (char**)&pszHour, 10 );
	int nMins = (int)strtol( pszMins, (char**)&pszMins, 10 );
	CTime siTime = CTime( 1970, 1, 1, nHour, nMins, 0 );
	m_editSI = siTime.Format( "%H:%M" );
	m_pView->GetDocument()->GetCurRecord()->SetSI( siTime );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg2::OnKillfocusEditDepth()
{
	float depth = m_pView->GetDocument()->GetCurRecord()->GetDepth( );

	if( m_pView->GetDocument()->GetCurRecord()->GetDepthMts() && (depth < 0 || depth >42) )
	{	
		AfxMessageBox( "Depth must be between 1m and 42m!" );
		m_pView->GetDocument()->GetCurRecord()->SetDepth( (float)42 );
	}
	else if( depth < 0 || depth > 140 )
	{	
		AfxMessageBox( "Depth must be between 1ft and 140f!" );
		m_pView->GetDocument()->GetCurRecord()->SetDepth( (float)140 );
	}

	CalcDiveTables();
	UpdateData( FALSE );

}

void CDivePg2::OnChangeEditDepth()
{
	UpdateData( TRUE );	m_editDepth.MakeUpper();
	if( m_editDepth.Right( 1 )=="M" )
	{	m_meaDepth = "mts.";	m_pView->GetDocument()->GetCurRecord()->SetDepthMts( TRUE );	}
	else if( m_editDepth.Right( 1 )=="F" )
	{	m_meaDepth = "ft.";		m_pView->GetDocument()->GetCurRecord()->SetDepthMts( FALSE );	}

	if( m_editDepth.Right( 1 )=="M" || m_editDepth.Right( 1 )=="F" )
		m_editDepth = m_editDepth.Left( m_editDepth.GetLength()-1 );
	
	float depth = (float)atof( m_editDepth );	// value to be stored in record
	char buf[10];	_gcvt( depth, 3, buf );	m_editDepth = buf;
	m_pView->GetDocument()->GetCurRecord()->SetDepth( depth );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg2::OnKillfocusEditBottomTime()
{	
	CalcDiveTables();
	UpdateData( FALSE );
}

void CDivePg2::OnChangeEditBottomTime()
{
	UpdateData( TRUE );
	m_pView->GetDocument()->GetCurRecord()->SetBottomTime( m_editBottomTime );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg2::OnKillfocusEditStop()
{	UpdateData( FALSE );	}

void CDivePg2::OnChangeEditStop()
{
	UpdateData( TRUE );
	m_pView->GetDocument()->GetCurRecord()->SetDecompStop( m_editStop );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg2::OnKillfocusEditWeight()
{	UpdateData( FALSE );	}

void CDivePg2::OnChangeEditWeight()
{
	UpdateData( TRUE );	m_editWeight.MakeUpper();
	if( m_editWeight.Right( 1 )=="L" )
	{	m_meaWeight = "lbs.";	m_pView->GetDocument()->GetCurRecord()->SetWeightKG( FALSE );	}
	else if( m_editWeight.Right( 1 )=="K" )
	{	m_meaWeight = "kg";	m_pView->GetDocument()->GetCurRecord()->SetWeightKG( TRUE );	}

	if( m_editWeight.Right( 1 )=="L" || m_editWeight.Right( 1 )=="K" )
		m_editWeight = m_editWeight.Left( m_editWeight.GetLength()-1 );
	
	const char* pszText = m_editWeight;
	int nWeight = (int)strtol( pszText, (char**)&pszText, 10 );
	char buf[5];	wsprintf( buf, "%d", nWeight );	m_editWeight = buf;
	m_pView->GetDocument()->GetCurRecord()->SetWeight( nWeight );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CDivePg2::OnCheckBoxClicked()
{
	UpdateData( TRUE );
	CDiveData* pData = m_pView->GetDocument()->GetCurRecord();
	pData->SetBoat( m_bBoat );
	pData->SetCurrent( m_bCurrent );
	pData->SetDrySuit( m_bDrySuit );
	pData->SetFresh( m_bFresh );
	pData->SetGloves( m_bGloves );
	pData->SetHood( m_bHood );
	pData->SetMittens( m_bMittens );
	pData->SetSalt( m_bSalt );
	pData->SetSDrySuit( m_bSDrySuit );
	pData->SetShore( m_bShore );
	pData->SetSocks( m_bSocks );
	pData->SetSurf( m_bSurf );
	pData->SetSurge( m_bSurge );
	pData->SetUSuit( m_bUnderSuit );
	pData->SetWaves( m_bWaves );
	pData->SetWetSuit( m_bWetSuit );
}

void CDivePg2::UpdateControls( CDiveData* pData )
{
	ASSERT_VALID( pData );
	
	m_editSI = pData->GetSurfaceInt().Format( "%H:%M" );
	char buf[10];	_gcvt( pData->GetDepth(), 3, buf );
	m_editDepth = buf;
	m_meaDepth = pData->GetDepthMts() ? "mts." : "ft.";
	m_editBottomTime = pData->GetBottomTime();
	m_editStop = pData->GetDecompStop();

	m_bBoat		= pData->GetBoat( );
	m_bCurrent	= pData->GetCurrent( );
	m_bDrySuit	= pData->GetDrySuit( );
	m_bFresh	= pData->GetFresh( );
	m_bGloves	= pData->GetGloves( );
	m_bHood		= pData->GetHood( );
	m_bMittens	= pData->GetMittens( );
	m_bSalt		= pData->GetSalt( );
	m_bSDrySuit	= pData->GetSDrySuit( );
	m_bShore	= pData->GetShore( );
	m_bSocks	= pData->GetSocks( );
	m_bSurf		= pData->GetSurf( );
	m_bSurge	= pData->GetSurge( );
	m_bUnderSuit= pData->GetUSuit( );
	m_bWaves	= pData->GetWaves( );
	m_bWetSuit	= pData->GetWetSuit( );
	
	wsprintf( buf, "%d", pData->GetWeight( ) );
	m_editWeight = buf;
	m_meaWeight = pData->GetWeightKG() ? "kg" : "lbs.";
	m_pgBefore = pData->GetPGBeforeDive();
	m_pgAfter = pData->GetPGAfterDive();

	wsprintf( buf, "%d", pData->GetRNT( ) );	m_strRNT = buf;
	wsprintf( buf, "%d", pData->GetABT( ) );	m_strABT = buf;
	wsprintf( buf, "%d", pData->GetTBT( ) );	m_strTBT = buf;

	UpdateData( FALSE );
	//InvalidateRect( CRect( 20, 320, 180, 335 ) );
	if( CMainFrame::bVGA )
		InvalidateRect( CRect( 20, 320, 180, 335 ) );
	else
		InvalidateRect( CRect( 0, 420, 260, 435 ) );

	// Update dialog bar
	DisplayABTTimes( pData );

}
void CDivePg2::DisplayABTTimes( CDiveData* pData )
{
	CDlgBar* pDlgBar = (CDlgBar*)AfxGetMainWnd()->GetDescendantWindow( IDD_DIALOG_BAR );
	if( pDlgBar!=NULL )
	{
		CDiveSet* pSet = m_pView->GetDocument()->GetDiveSet();
		CTime ABTtoDate = pSet->GetABTtoDate( pData );
		CStatic* pStatic = (CStatic*)pDlgBar->GetDlgItem( IDC_ABT_TO_DATE );
		int nDays = ABTtoDate.GetDay() - 1;
		int nHrs = ABTtoDate.GetHour();
		int nMins = ABTtoDate.GetMinute();
		nHrs += (nDays * 24 );
		char buf[10];
		wsprintf( buf, (nMins <=9) ? "%d:0%d" : "%d:%d", nHrs, nMins );
		pStatic->SetWindowText( buf );

		pSet = m_pView->GetDocument()->GetDiveSet();
		ABTtoDate = pSet->GetABTtoDate( NULL );
		pStatic = (CStatic*)pDlgBar->GetDlgItem( IDC_ABT_ALL_DIVES );
		nDays = ABTtoDate.GetDay() - 1;
		nHrs = ABTtoDate.GetHour();
		nMins = ABTtoDate.GetMinute();
		nHrs += (nDays * 24 );
		wsprintf( buf, (nMins <=9) ? "%d:0%d" : "%d:%d", nHrs, nMins );
		pStatic->SetWindowText( buf );
	}

}

void CDivePg2::CalcDiveTables()
{
	// calculate this day dives
	CStatusBar* pBar = (CStatusBar*)AfxGetMainWnd()->GetDescendantWindow( AFX_IDW_STATUS_BAR );
	if( pBar != NULL )
	{	pBar->SetWindowText( "Calculating dive..." );	pBar->UpdateWindow();	}

	CTimeSpan ABTtoDate( 0, 0, 0, 0 );
	CDiveDoc* pDoc = m_pView->GetDocument();
	CDiveData* pCurData = pDoc->GetCurRecord();	
	CPoint index = pDoc->GetCurIndex();	index.y=0;
	CDiveData* pData = pDoc->GetDiveData( index );

	float depth = pData->GetDepth();
	// if the depth is a fraction round it up
	if( (depth-(int)depth)!=0 )
	{	depth = (float)((int)depth);	depth++;	}
	// if the surface temp is cold then add 4m to the depth
	if( pData->GetSurfaceTemp()==CDiveData::Cold || pData->GetBottomTemp()==CDiveData::Cold )
	{
		if( pData->GetDepthMts() )
			depth += 4;
		else
			depth += (float)13.1;
	}

	// Must make sure that the depth is not too deep otherwise the calculations will fail
	if( pData->GetDepthMts() )
		depth = (depth<0 || depth>42) ? 42 : depth;
	else
		depth = (depth<0 || depth>140) ? 140 : depth;

	// index.y==0 so this is the first dive of the day
	pData->SetLastPG( 0 );
	pData->SetPGBeforeDive( 'A' );
	
	int nPG;
	if( pData->GetDepthMts() )
		nPG = CDiveApp::table1M.FindMtrs( (int)depth, pData->GetBottomTime() );
	else
		nPG = CDiveApp::table1F.FindFt( (int)depth, pData->GetBottomTime() );
	if( nPG > 25 )	// exceeded padi table
		nPG = '?' - 'A';
		
	int nOffset = 'A';	char PG = nOffset + nPG;
	
	pData->SetRNT( 0 );	pData->SetABT( 0 );	pData->SetTBT( 0 );
	if( nPG=='?' - 'A' )	// exceeded padi table so find the highest PG 
	{						// by adjusting the bottom time
		int nBT = pData->GetBottomTime();
		nPG = 999;
		while( nPG > 25 )
		{
			nBT--;
			if( pData->GetDepthMts() )
				nPG = CDiveApp::table1M.FindMtrs( (int)depth, nBT );
			else
				nPG = CDiveApp::table1F.FindFt( (int)depth, nBT );
		}
	}
	
	//AfxMessageBox( "1" );
	
	pData->SetPGAfterDive( PG );
		
	int lastPG = nPG;
	
	pData->SetABTtoDate( CTime( 1970, 1, 1, ABTtoDate.GetHours(), ABTtoDate.GetMinutes(), 0 ) );
	int nHours = pData->GetBottomTime() / 60;
	int nMins = pData->GetBottomTime() - (nHours*60);
	pData->IncABTtoDate( CTimeSpan( 0, nHours, nMins, 0 ) );
	pData->SetABTDive( CTime( 1970, 1, 1, nHours, nMins, 0 ) );
	ABTtoDate = CTimeSpan( 0, pData->GetABTtoDate().GetHour(), pData->GetABTtoDate().GetMinute(), 0 );
	CTime tm = m_pView->GetDocument()->GetDiveSet()->GetTotalABT(  );
	
	CDiveSet* pTmpSet = m_pView->GetDocument()->GetDiveSet();
	
	CTime tmpTime( 1970, 1, 1, (tm.GetHour()+ABTtoDate.GetHours()),
												(tm.GetMinute()+ABTtoDate.GetMinutes())-pData->GetBottomTime(), 0 );
	pTmpSet->SetTotalABT( tmpTime );
	/*
	pTmpSet->SetTotalABT( CTime( 1970, 1, 1, (tm.GetHour()+ABTtoDate.GetHours()),
												(tm.GetMinute()+ABTtoDate.GetMinutes())-pData->GetBottomTime(), 0 ) );
	*/
	//AfxMessageBox( "2" );
	
	// now calculate the rest of the dives
	for( int loop=1; loop<=pDoc->GetNoOfDayDives( index.x ); loop++ )
	{
		pData = pDoc->GetDiveData( CPoint( index.x, loop ) );
		depth = pData->GetDepth();
		// if the depth is a fraction round it up
		if( (depth-(int)depth)!=0 )
		{	depth = (float)((int)depth);	depth++;	}
		// if the surface temp is cold then add 4m to the depth
		if( pData->GetSurfaceTemp()==CDiveData::Cold || pData->GetBottomTemp()==CDiveData::Cold )
			depth += 4;
	
		// Must make sure that the depth is not too deep otherwise the calculations will fail
		if( pData->GetDepthMts() )
			depth = (depth<0 || depth>42) ? 42 : depth;
		else
			depth = (depth<0 || depth>140) ? 140 : depth;

		pData->SetLastPG( lastPG );
		
		CString si = pData->GetSI().Format( "%H%M" );
		const char* pszSI = si;
		int nSI = (int)strtol( pszSI, (char**)&pszSI, 10 );
		int nPG = CDiveApp::table2.Find( lastPG, nSI );
		int nOffset = 'A';	char PG = nOffset + nPG;
		pData->SetPGBeforeDive( PG );
		
		WORD wTmp;
		if( pData->GetDepthMts() )
			wTmp = CDiveApp::table3M.FindMtrs( nPG, (int)depth );
		else
			wTmp = CDiveApp::table3F.FindFt( nPG, (int)depth );
		int nRNT = LOBYTE( wTmp );
		int nANDL = HIBYTE( wTmp );
		
		// The ABT should not be greater than the ANDL
		if( pData->GetBottomTime() > nANDL )
			nPG = '?' - 'A';
		
		pData->SetRNT( nRNT );
		pData->SetABT( pData->GetBottomTime() );
		pData->SetTBT( nRNT + pData->GetABT() );
		
		if( nPG=='?' - 'A' )	// exceeded padi table so find the highest PG 
		{						// by adjusting the bottom time
			int nBT = pData->GetTBT();  // Bottom Time
			nPG = 999;
			while( nPG > 25 )
			{
				nBT--;
				if( pData->GetDepthMts() )
					nPG = CDiveApp::table1M.FindMtrs( (int)depth, nBT );
				else
					nPG = CDiveApp::table1F.FindFt( (int)depth, nBT );
			}
			lastPG = nPG;
			pData->SetPGAfterDive( '?' );
		}
		else
		{
			// Now calculate the pressure group at the end of the dive using TBT
			if( pData->GetDepthMts() )
				nPG = CDiveApp::table1M.FindMtrs( (int)depth, pData->GetTBT() );
			else
				nPG = CDiveApp::table1F.FindFt( (int)depth, pData->GetTBT() );
			lastPG = nPG;
			pData->SetPGAfterDive( nOffset + nPG );
		}
	
		CTime tmpTime2( 1970, 1, 1, ABTtoDate.GetHours(), ABTtoDate.GetMinutes(), 0 );
		pData->SetABTtoDate( tmpTime2 );
//	AfxMessageBox( "a" );
		int nHours = pData->GetBottomTime() / 60;
		int nMins = pData->GetBottomTime() - (nHours*60);
		pData->IncABTtoDate( CTimeSpan( 0, nHours, nMins, 0 ) );
		pData->SetABTDive( CTime( 1970, 1, 1, nHours, nMins, 0 ) );
		ABTtoDate = CTimeSpan( 0, pData->GetABTtoDate().GetHour(), pData->GetABTtoDate().GetMinute(), 0 );
		CTime tm = m_pView->GetDocument()->GetDiveSet()->GetTotalABT(  );
		
//		AfxMessageBox( "b" );
		
		CDiveSet* pTmp = m_pView->GetDocument()->GetDiveSet();
		
		//CTime tmpTime( 1970, 1, 1, (tm.GetHour()+ABTtoDate.GetHours()),
		//						(tm.GetMinute()+ABTtoDate.GetMinutes())-pData->GetBottomTime(), 0 );
		//pTmp->SetTotalABT( tmpTime );
	}

	UpdateControls( pCurData );
    if( pBar != NULL )
    {
		CString str;
		str.LoadString( AFX_IDS_IDLEMESSAGE );
		pBar->SetWindowText( str );
		pBar->UpdateWindow();
	}
}


void CDivePg1::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	::SetCursor( AfxGetApp()->LoadCursor( IDC_DIVEREC ) );
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDivePg1::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( GetCapture() == this )
	{
		ReleaseCapture();
		::SetCursor( AfxGetApp()->LoadStandardCursor( IDC_ARROW ) );
	}

	CDlgBar* pDlgBar = (CDlgBar*)AfxGetMainWnd()->GetDescendantWindow( IDD_DIALOG_BAR );
	if( pDlgBar!=NULL )
	{
		CRect wndRect;
		pDlgBar->GetWindowRect( wndRect );
		ClientToScreen( &point );

		int nTmp;
		if( CMainFrame::bVGA )
			nTmp = 335;
		else
			nTmp = 435;

		if( point.y > wndRect.top + nTmp && point.y < wndRect.bottom 
									&& point.x > wndRect.left && point.x < wndRect.right )
		{
			pDlgBar->AnimateBin();
			m_pView->RemoveCurDive();
			m_pView->GetDocument()->SetModifiedFlag( );
		} 
	}
	else
		ASSERT( FALSE );	// Can't find dialog bar!

	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDivePg2::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( CMainFrame::bVGA )
	{
		CRect rect;
		GetWindowRect( &rect );
		ScreenToClient( &rect );
		if( point.x >= rect.right-10 && point.y >= rect.bottom-10 )
		{
			m_pView->OnNextpage();
			return;
		}
	}

	SetCapture();
	::SetCursor( AfxGetApp()->LoadCursor( IDC_DIVEREC ) );
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDivePg2::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( GetCapture() == this )
	{
		ReleaseCapture();
		::SetCursor( AfxGetApp()->LoadStandardCursor( IDC_ARROW ) );
	}

	CDlgBar* pDlgBar = (CDlgBar*)AfxGetMainWnd()->GetDescendantWindow( IDD_DIALOG_BAR );
	if( pDlgBar!=NULL )
	{
		CRect wndRect;
		pDlgBar->GetWindowRect( wndRect );
		ClientToScreen( &point );

		int nTmp;
		if( CMainFrame::bVGA )
			nTmp = 335;
		else
			nTmp = 435;

		if( point.y > wndRect.top + nTmp && point.y < wndRect.bottom
											&& point.x > wndRect.left && point.x < wndRect.right )
		{
			pDlgBar->AnimateBin();
			m_pView->RemoveCurDive();
			m_pView->GetDocument()->SetModifiedFlag( );
		} 
	}
	else
		ASSERT( FALSE );	// Can't find dialog bar!
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDivePg1::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( GetCapture() != this )
		return;

	CRect wndRect;
	GetWindowRect( &wndRect );
	CRect dlgBarRect;	dlgBarRect.SetRectEmpty();
	CDlgBar* pDlgBar = (CDlgBar*)AfxGetMainWnd()->GetDescendantWindow( IDD_DIALOG_BAR );
	if( pDlgBar!=NULL )
		pDlgBar->GetWindowRect( &dlgBarRect );

	ClientToScreen( &point );

	if( wndRect.PtInRect( point ) || dlgBarRect.PtInRect( point ) )
		::SetCursor( AfxGetApp()->LoadCursor( IDC_DIVEREC ) );
	else
		::SetCursor( AfxGetApp()->LoadCursor( IDC_NODROP ) );
			
	CDialog::OnMouseMove(nFlags, point);
}

void CDivePg2::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( GetCapture() != this )
		return;

	CRect wndRect;
	GetWindowRect( &wndRect );
	CRect dlgBarRect;	dlgBarRect.SetRectEmpty();
	CDlgBar* pDlgBar = (CDlgBar*)AfxGetMainWnd()->GetDescendantWindow( IDD_DIALOG_BAR );
	if( pDlgBar!=NULL )
		pDlgBar->GetWindowRect( &dlgBarRect );
	
	ClientToScreen( &point );

	if( wndRect.PtInRect( point ) || dlgBarRect.PtInRect( point ) )
		::SetCursor( AfxGetApp()->LoadCursor( IDC_DIVEREC ) );
	else
		::SetCursor( AfxGetApp()->LoadCursor( IDC_NODROP ) );
		
	CDialog::OnMouseMove(nFlags, point);
}


void CDivePg1::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//AfxMessageBox( "Char" );
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CDivePg1::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//AfxMessageBox( "KeyDown" );
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

