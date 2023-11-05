// COMMENTS.CPP - implementation of the CCommentsDlg class

#include "stdafx.h"
#include "divelog.h"
#include "comments.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommentsDlg dialog


CCommentsDlg::CCommentsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommentsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommentsDlg)
	m_Comments = "";
	//}}AFX_DATA_INIT
}

void CCommentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommentsDlg)
	DDX_Text(pDX, IDDC_COMMENTS, m_Comments);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCommentsDlg, CDialog)
	//{{AFX_MSG_MAP(CCommentsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCommentsDlg message handlers

BOOL CCommentsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	int scrX = ::GetSystemMetrics( SM_CXFULLSCREEN );
	int scrY = ::GetSystemMetrics( SM_CYFULLSCREEN );
	SetWindowPos( NULL, (scrX - 347)/2, (scrY - 270)/2, 347, 270, SWP_NOZORDER );

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
