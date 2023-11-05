// notesdlg.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "notesdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotesDlg dialog


CNotesDlg::CNotesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNotesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNotesDlg)
	m_strNotes = _T("");
	//}}AFX_DATA_INIT
}


void CNotesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNotesDlg)
	DDX_Text(pDX, IDC_NOTES, m_strNotes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNotesDlg, CDialog)
	//{{AFX_MSG_MAP(CNotesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNotesDlg message handlers

BOOL CNotesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
