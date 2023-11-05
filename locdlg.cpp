// locdlg.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "locdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocDlg dialog


CLocDlg::CLocDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLocDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLocDlg)
	m_strEdit = _T("");
	//}}AFX_DATA_INIT
}


void CLocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocDlg)
	DDX_Control(pDX, IDC_LOCATIONS, m_ctlList);
	DDX_CBString(pDX, IDC_LOCATIONS, m_strEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocDlg, CDialog)
	//{{AFX_MSG_MAP(CLocDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLocDlg message handlers

BOOL CLocDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	
	// Read in the locations
	int nEntries = AfxGetApp()->GetProfileInt( "Location", "Entries", -1 );
	for( int loop = 1; loop<=nEntries; loop++ )
	{
		char buf[50];
		wsprintf( buf, "String%d", loop );
		m_ctlList.AddString( AfxGetApp()->GetProfileString( "Location", buf ) );
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLocDlg::OnAdd() 
{
	// First check if the string is already in the list
	UpdateData();	// update member varibles
	
	if( m_strEdit == "" )
		return;

	if( m_ctlList.FindStringExact( -1, m_strEdit )!=CB_ERR )
		m_ctlList.SelectString( -1, m_strEdit );
	else
	{
		// Add it to the list
		m_ctlList.SetCurSel( m_ctlList.AddString( m_strEdit ) );
	}
}

void CLocDlg::OnRemove() 
{
	int curSel = m_ctlList.GetCurSel();
	
	if( curSel != CB_ERR )
		m_ctlList.DeleteString( curSel );
}

void CLocDlg::OnOK() 
{
	AfxGetApp()->WriteProfileInt( "Location", "Entries", m_ctlList.GetCount() );
	for( int loop = 1; loop<=m_ctlList.GetCount(); loop++ )
	{
		char buf[50];
		wsprintf( buf, "String%d", loop );
		CString str;	m_ctlList.GetLBText( loop - 1, str );
		AfxGetApp()->WriteProfileString( "Location", buf, str );
	}
	
	CDialog::OnOK();
}
