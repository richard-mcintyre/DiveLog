// LOCATION.CPP - implementation of the CLocationDlg class

#include "stdafx.h"
#include "divelog.h"
#include "location.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocationDlg dialog


CLocationDlg::CLocationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLocationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLocationDlg)
	m_strEdit = "";
	//}}AFX_DATA_INIT
}

void CLocationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocationDlg)
	DDX_Control(pDX, IDC_LIST, m_ctlList);
	DDX_CBString(pDX, IDC_LIST, m_strEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLocationDlg, CDialog)
	//{{AFX_MSG_MAP(CLocationDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLocationDlg message handlers

BOOL CLocationDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLocationDlg::OnAdd()
{
	// First check if the string is already in the list
	UpdateData();	// update member varibles
	
	if( m_ctlList.FindStringExact( -1, m_strEdit )!=CB_ERR )
		m_ctlList.SelectString( -1, m_strEdit );
	else
	{
		// Add it to the list
		m_ctlList.SetCurSel( m_ctlList.AddString( m_strEdit ) );
	}
	
}

void CLocationDlg::OnDelete()
{
	int curSel = m_ctlList.GetCurSel();
	
	if( curSel != CB_ERR )
		m_ctlList.DeleteString( curSel );
}

void CLocationDlg::OnOK()
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
