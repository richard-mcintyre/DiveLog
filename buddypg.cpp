// buddypg.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "buddypg.h"
#include "mainfrm.h"
#include "divedoc.h"
#include "divevw.h"
#include "buddata.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuddyP1 dialog


CBuddyP1::CBuddyP1(CWnd* pParent /*=NULL*/)
	: CDialog(CBuddyP1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuddyP1)
	m_strTitle = _T("");
	m_strAddress = _T("");
	m_strFAX = _T("");
	m_strFirstName = _T("");
	m_strLastName = _T("");
	m_strPhone = _T("");
	//}}AFX_DATA_INIT
}


void CBuddyP1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuddyP1)
	DDX_Text(pDX, IDC_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_FAX, m_strFAX);
	DDX_Text(pDX, IDC_FIRSTNAME, m_strFirstName);
	DDX_Text(pDX, IDC_LASTNAME, m_strLastName);
	DDX_Text(pDX, IDC_PHONE, m_strPhone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuddyP1, CDialog)
	//{{AFX_MSG_MAP(CBuddyP1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_EN_KILLFOCUS(IDC_TITLE, OnKillfocusTitle)
	ON_EN_CHANGE(IDC_TITLE, OnChangeTitle)
	ON_EN_CHANGE(IDC_FIRSTNAME, OnChangeFirstname)
	ON_EN_KILLFOCUS(IDC_FIRSTNAME, OnKillfocusFirstname)
	ON_EN_CHANGE(IDC_LASTNAME, OnChangeLastname)
	ON_EN_KILLFOCUS(IDC_LASTNAME, OnKillfocusLastname)
	ON_EN_CHANGE(IDC_ADDRESS, OnChangeAddress)
	ON_EN_KILLFOCUS(IDC_ADDRESS, OnKillfocusAddress)
	ON_EN_CHANGE(IDC_PHONE, OnChangePhone)
	ON_EN_KILLFOCUS(IDC_PHONE, OnKillfocusPhone)
	ON_EN_CHANGE(IDC_FAX, OnChangeFax)
	ON_EN_KILLFOCUS(IDC_FAX, OnKillfocusFax)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBuddyP1 message handlers

BOOL CBuddyP1::Create( CDiveView* pParent, UINT nDlg )
{
	m_pView = pParent;
	return CDialog::Create( nDlg, pParent );
}

void CBuddyP1::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	::SetCursor( AfxGetApp()->LoadCursor( IDC_DIVEREC ) );
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CBuddyP1::OnLButtonUp(UINT nFlags, CPoint point) 
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
			m_pView->RemoveCurBud();
			m_pView->GetDocument()->SetModifiedFlag( );
		} 
	}
	else
		ASSERT( FALSE );	// Can't find dialog bar!

	CDialog::OnLButtonUp(nFlags, point);
}

void CBuddyP1::OnMouseMove(UINT nFlags, CPoint point) 
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

void CBuddyP1::OnOK()
{
	//AfxMessageBox( "CBuddyP1::OnOK - trapped!" );
}

void CBuddyP1::OnCancel()
{
	//AfxMessageBox( "CBuddyP1::OnCancel - trapped!" );
}

void CBuddyP1::UpdateControls( CBudData* pData )
{
	ASSERT_VALID( pData );

	m_strTitle = pData->GetTitle();
	m_strFirstName = pData->GetFirstName();
	m_strLastName = pData->GetLastName();
	m_strAddress = pData->GetAddress();
	m_strPhone = pData->GetPhone();
	m_strFAX = pData->GetFAX();

	UpdateData( FALSE );
}

void CBuddyP1::OnChangeTitle() 
{
	UpdateData( TRUE );
	m_pView->GetDocument()->GetBudCurRecord()->SetTitle( m_strTitle );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CBuddyP1::OnChangeFirstname() 
{
	UpdateData( TRUE );
	m_pView->GetDocument()->GetBudCurRecord()->SetFirstName( m_strFirstName );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CBuddyP1::OnChangeLastname() 
{
	CString oldName = m_strLastName;
	UpdateData( TRUE );
	m_pView->GetDocument()->GetBudCurRecord()->SetLastName( m_strLastName );
	if( oldName.GetLength() != -1 )
		//if( oldName.GetAt( 0 ) != m_strLastName.GetAt( 0 ) )
			m_pView->GetDocument()->GetBudSet()->LastNameChanged( 
								oldName, m_strLastName, m_pView->GetDocument()->GetBudIndex() );
	m_pView->GetDocument()->SetModifiedFlag( );
	UpdateButtons( );
}

void CBuddyP1::OnChangeAddress() 
{
	UpdateData( TRUE );
	m_pView->GetDocument()->GetBudCurRecord()->SetAddress( m_strAddress );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CBuddyP1::OnChangePhone() 
{
	UpdateData( TRUE );
	m_pView->GetDocument()->GetBudCurRecord()->SetPhone( m_strPhone );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CBuddyP1::OnChangeFax() 
{
	UpdateData( TRUE );
	m_pView->GetDocument()->GetBudCurRecord()->SetFAX( m_strFAX );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CBuddyP1::OnKillfocusTitle() 
{	UpdateData( TRUE );	}
void CBuddyP1::OnKillfocusFirstname() 
{	UpdateData( TRUE );	}
void CBuddyP1::OnKillfocusLastname() 
{	UpdateData( TRUE );	}
void CBuddyP1::OnKillfocusAddress() 
{	UpdateData( TRUE );	}
void CBuddyP1::OnKillfocusPhone() 
{	UpdateData( TRUE );	}
void CBuddyP1::OnKillfocusFax() 
{	UpdateData( TRUE );	}

void CBuddyP1::UpdateButtons( )
{	m_pView->GetBudPage2()->UpdateButtons();	}

/////////////////////////////////////////////////////////////////////////////
// CBuddyP2 dialog


CBuddyP2::CBuddyP2(CWnd* pParent /*=NULL*/)
	: CDialog(CBuddyP2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuddyP2)
	m_strNotes = _T("");
	//}}AFX_DATA_INIT
}


void CBuddyP2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuddyP2)
	DDX_Control(pDX, IDC_BUTTON_Z, m_ctlButZ);
	DDX_Control(pDX, IDC_BUTTON_Y, m_ctlButY);
	DDX_Control(pDX, IDC_BUTTON_X, m_ctlButX);
	DDX_Control(pDX, IDC_BUTTON_W, m_ctlButW);
	DDX_Control(pDX, IDC_BUTTON_V, m_ctlButV);
	DDX_Control(pDX, IDC_BUTTON_U, m_ctlButU);
	DDX_Control(pDX, IDC_BUTTON_T, m_ctlButT);
	DDX_Control(pDX, IDC_BUTTON_S, m_ctlButS);
	DDX_Control(pDX, IDC_BUTTON_R, m_ctlButR);
	DDX_Control(pDX, IDC_BUTTON_Q, m_ctlButQ);
	DDX_Control(pDX, IDC_BUTTON_P, m_ctlButP);
	DDX_Control(pDX, IDC_BUTTON_O, m_ctlButO);
	DDX_Control(pDX, IDC_BUTTON_N, m_ctlButN);
	DDX_Control(pDX, IDC_BUTTON_M, m_ctlButM);
	DDX_Control(pDX, IDC_BUTTON_L, m_ctlButL);
	DDX_Control(pDX, IDC_BUTTON_K, m_ctlButK);
	DDX_Control(pDX, IDC_BUTTON_J, m_ctlButJ);
	DDX_Control(pDX, IDC_BUTTON_I, m_ctlButI);
	DDX_Control(pDX, IDC_BUTTON_H, m_ctlButH);
	DDX_Control(pDX, IDC_BUTTON_G, m_ctlButG);
	DDX_Control(pDX, IDC_BUTTON_F, m_ctlButF);
	DDX_Control(pDX, IDC_BUTTON_E, m_ctlButE);
	DDX_Control(pDX, IDC_BUTTON_D, m_ctlButD);
	DDX_Control(pDX, IDC_BUTTON_C, m_ctlButC);
	DDX_Control(pDX, IDC_BUTTON_B, m_ctlButB);
	DDX_Control(pDX, IDC_BUTTON_A, m_ctlButA);
	DDX_Text(pDX, IDC_NOTES, m_strNotes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuddyP2, CDialog)
	//{{AFX_MSG_MAP(CBuddyP2)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_EN_CHANGE(IDC_NOTES, OnChangeNotes)
	ON_EN_KILLFOCUS(IDC_NOTES, OnKillfocusNotes)
	ON_BN_CLICKED(IDC_BUTTON_A, OnButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B, OnButtonB)
	ON_BN_CLICKED(IDC_BUTTON_C, OnButtonC)
	ON_BN_CLICKED(IDC_BUTTON_D, OnButtonD)
	ON_BN_CLICKED(IDC_BUTTON_E, OnButtonE)
	ON_BN_CLICKED(IDC_BUTTON_F, OnButtonF)
	ON_BN_CLICKED(IDC_BUTTON_G, OnButtonG)
	ON_BN_CLICKED(IDC_BUTTON_H, OnButtonH)
	ON_BN_CLICKED(IDC_BUTTON_I, OnButtonI)
	ON_BN_CLICKED(IDC_BUTTON_J, OnButtonJ)
	ON_BN_CLICKED(IDC_BUTTON_K, OnButtonK)
	ON_BN_CLICKED(IDC_BUTTON_L, OnButtonL)
	ON_BN_CLICKED(IDC_BUTTON_M, OnButtonM)
	ON_BN_CLICKED(IDC_BUTTON_N, OnButtonN)
	ON_BN_CLICKED(IDC_BUTTON_O, OnButtonO)
	ON_BN_CLICKED(IDC_BUTTON_P, OnButtonP)
	ON_BN_CLICKED(IDC_BUTTON_Q, OnButtonQ)
	ON_BN_CLICKED(IDC_BUTTON_R, OnButtonR)
	ON_BN_CLICKED(IDC_BUTTON_S, OnButtonS)
	ON_BN_CLICKED(IDC_BUTTON_T, OnButtonT)
	ON_BN_CLICKED(IDC_BUTTON_U, OnButtonU)
	ON_BN_CLICKED(IDC_BUTTON_V, OnButtonV)
	ON_BN_CLICKED(IDC_BUTTON_W, OnButtonW)
	ON_BN_CLICKED(IDC_BUTTON_X, OnButtonX)
	ON_BN_CLICKED(IDC_BUTTON_Y, OnButtonY)
	ON_BN_CLICKED(IDC_BUTTON_Z, OnButtonZ)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBuddyP2 message handlers

BOOL CBuddyP2::Create( CDiveView* pParent, UINT nDlg )
{
	m_pView = pParent;
	return CDialog::Create( nDlg, pParent );
}


void CBuddyP2::OnLButtonDown(UINT nFlags, CPoint point) 
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

void CBuddyP2::OnLButtonUp(UINT nFlags, CPoint point) 
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
			m_pView->RemoveCurBud();
			m_pView->GetDocument()->SetModifiedFlag( );
		} 
	}
	else
		ASSERT( FALSE );	// Can't find dialog bar!
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CBuddyP2::OnMouseMove(UINT nFlags, CPoint point) 
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

void CBuddyP2::OnOK()
{
	//AfxMessageBox( "CBuddyP2::OnOK - trapped!" );
}

void CBuddyP2::OnCancel()
{
	//AfxMessageBox( "CBuddyP2::OnCancel - trapped!" );
}

void CBuddyP2::UpdateControls( CBudData* pData )
{
	ASSERT_VALID( pData );

	m_strNotes = pData->GetNotes();
	UpdateButtons( );

	UpdateData( FALSE );
}


void CBuddyP2::OnChangeNotes() 
{
	UpdateData( TRUE );
	m_pView->GetDocument()->GetBudCurRecord()->SetNotes( m_strNotes );
	m_pView->GetDocument()->SetModifiedFlag( );
}

void CBuddyP2::OnKillfocusNotes() 
{	UpdateData( TRUE );	}

void CBuddyP2::UpdateButtons( )
{
	CBudSet* pSet = m_pView->GetDocument()->GetBudSet( );
	m_ctlButA.EnableWindow( pSet->GetQuickIndex( CBudSet::A ) > 0 ? TRUE : FALSE );
	m_ctlButB.EnableWindow( pSet->GetQuickIndex( CBudSet::B ) > 0 ? TRUE : FALSE );
	m_ctlButC.EnableWindow( pSet->GetQuickIndex( CBudSet::C ) > 0 ? TRUE : FALSE );
	m_ctlButD.EnableWindow( pSet->GetQuickIndex( CBudSet::D ) > 0 ? TRUE : FALSE );
	m_ctlButE.EnableWindow( pSet->GetQuickIndex( CBudSet::E ) > 0 ? TRUE : FALSE );
	m_ctlButF.EnableWindow( pSet->GetQuickIndex( CBudSet::F ) > 0 ? TRUE : FALSE );
	m_ctlButG.EnableWindow( pSet->GetQuickIndex( CBudSet::G ) > 0 ? TRUE : FALSE );
	m_ctlButH.EnableWindow( pSet->GetQuickIndex( CBudSet::H ) > 0 ? TRUE : FALSE );
	m_ctlButI.EnableWindow( pSet->GetQuickIndex( CBudSet::I ) > 0 ? TRUE : FALSE );
	m_ctlButJ.EnableWindow( pSet->GetQuickIndex( CBudSet::J ) > 0 ? TRUE : FALSE );
	m_ctlButK.EnableWindow( pSet->GetQuickIndex( CBudSet::K ) > 0 ? TRUE : FALSE );
	m_ctlButL.EnableWindow( pSet->GetQuickIndex( CBudSet::L ) > 0 ? TRUE : FALSE );
	m_ctlButM.EnableWindow( pSet->GetQuickIndex( CBudSet::M ) > 0 ? TRUE : FALSE );
	m_ctlButN.EnableWindow( pSet->GetQuickIndex( CBudSet::N ) > 0 ? TRUE : FALSE );
	m_ctlButO.EnableWindow( pSet->GetQuickIndex( CBudSet::O ) > 0 ? TRUE : FALSE );
	m_ctlButP.EnableWindow( pSet->GetQuickIndex( CBudSet::P ) > 0 ? TRUE : FALSE );
	m_ctlButQ.EnableWindow( pSet->GetQuickIndex( CBudSet::Q ) > 0 ? TRUE : FALSE );
	m_ctlButR.EnableWindow( pSet->GetQuickIndex( CBudSet::R ) > 0 ? TRUE : FALSE );
	m_ctlButS.EnableWindow( pSet->GetQuickIndex( CBudSet::S ) > 0 ? TRUE : FALSE );
	m_ctlButT.EnableWindow( pSet->GetQuickIndex( CBudSet::T ) > 0 ? TRUE : FALSE );
	m_ctlButU.EnableWindow( pSet->GetQuickIndex( CBudSet::U ) > 0 ? TRUE : FALSE );
	m_ctlButV.EnableWindow( pSet->GetQuickIndex( CBudSet::V ) > 0 ? TRUE : FALSE );
	m_ctlButW.EnableWindow( pSet->GetQuickIndex( CBudSet::W ) > 0 ? TRUE : FALSE );
	m_ctlButX.EnableWindow( pSet->GetQuickIndex( CBudSet::X ) > 0 ? TRUE : FALSE );
	m_ctlButY.EnableWindow( pSet->GetQuickIndex( CBudSet::Y ) > 0 ? TRUE : FALSE );
	m_ctlButZ.EnableWindow( pSet->GetQuickIndex( CBudSet::Z ) > 0 ? TRUE : FALSE );
}

void CBuddyP2::OnButtonA() 
{	m_pView->FindBud( "A" );	}
void CBuddyP2::OnButtonB() 
{	m_pView->FindBud( "B" );	}
void CBuddyP2::OnButtonC() 
{	m_pView->FindBud( "C" );	}
void CBuddyP2::OnButtonD() 
{	m_pView->FindBud( "D" );	}
void CBuddyP2::OnButtonE() 
{	m_pView->FindBud( "E" );	}
void CBuddyP2::OnButtonF() 
{	m_pView->FindBud( "F" );	}
void CBuddyP2::OnButtonG() 
{	m_pView->FindBud( "G" );	}
void CBuddyP2::OnButtonH() 
{	m_pView->FindBud( "H" );	}
void CBuddyP2::OnButtonI() 
{	m_pView->FindBud( "I" );	}
void CBuddyP2::OnButtonJ() 
{	m_pView->FindBud( "J" );	}
void CBuddyP2::OnButtonK() 
{	m_pView->FindBud( "K" );	}
void CBuddyP2::OnButtonL() 
{	m_pView->FindBud( "L" );	}
void CBuddyP2::OnButtonM() 
{	m_pView->FindBud( "M" );	}
void CBuddyP2::OnButtonN() 
{	m_pView->FindBud( "N" );	}
void CBuddyP2::OnButtonO() 
{	m_pView->FindBud( "O" );	}
void CBuddyP2::OnButtonP() 
{	m_pView->FindBud( "P" );	}
void CBuddyP2::OnButtonQ() 
{	m_pView->FindBud( "Q" );	}
void CBuddyP2::OnButtonR() 
{	m_pView->FindBud( "R" );	}
void CBuddyP2::OnButtonS() 
{	m_pView->FindBud( "S" );	}
void CBuddyP2::OnButtonT() 
{	m_pView->FindBud( "T" );	}
void CBuddyP2::OnButtonU() 
{	m_pView->FindBud( "U" );	}
void CBuddyP2::OnButtonV() 
{	m_pView->FindBud( "V" );	}
void CBuddyP2::OnButtonW() 
{	m_pView->FindBud( "W" );	}
void CBuddyP2::OnButtonX() 
{	m_pView->FindBud( "X" );	}
void CBuddyP2::OnButtonY() 
{	m_pView->FindBud( "Y" );	}
void CBuddyP2::OnButtonZ() 
{	m_pView->FindBud( "Z" );	}
