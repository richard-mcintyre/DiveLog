// frontpg.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "frontpg.h"
#include "divedoc.h"
#include "divevw.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrontPg dialog


CFrontPg::CFrontPg(CDiveView* pParent /*=NULL*/)
	: CDialog(CFrontPg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrontPg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pView = pParent;
}

void CFrontPg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrontPg)
	DDX_Control(pDX, IDC_EDIT_FRONT, m_ctlEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFrontPg, CDialog)
	//{{AFX_MSG_MAP(CFrontPg)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_FRONT, OnChangeEditFront)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFrontPg message handlers

BOOL CFrontPg::Create( CDiveView* pParent, UINT nDlg )
{
	m_pView = pParent;
	return CDialog::Create( nDlg, pParent );
}
void CFrontPg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CDC* pDisplayMemDC = new CDC;
	CBitmap* pPic = new CBitmap;
	pPic->LoadBitmap( IDB_FRONT_PG );
	pDisplayMemDC->CreateCompatibleDC( &dc );
	
	CBitmap* pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject( pPic );
	if( CMainFrame::bVGA )
		dc.BitBlt( 1, 20, 185, 115, pDisplayMemDC, 0, 0, SRCCOPY );
	else
		dc.BitBlt( 45, 20, 185, 115, pDisplayMemDC, 0, 0, SRCCOPY );
	
	delete pDisplayMemDC->SelectObject( pOldBitmap );
	delete pDisplayMemDC;

	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CFrontPg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFrontPg::OnOK( )
{
	AfxMessageBox( "CFrontPg::OnOK" );
}

void CFrontPg::OnCancel( )
{
	AfxMessageBox( "CFrontPg::OnCancel" );
}


void CFrontPg::OnChangeEditFront() 
{
	CString str;
	m_ctlEdit.GetWindowText( str );	
	m_pView->GetDocument()->SetFrontText( str );
}
