// backpg.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "backpg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackPg dialog


CBackPg::CBackPg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackPg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackPg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CBackPg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackPg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBackPg, CDialog)
	//{{AFX_MSG_MAP(CBackPg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBackPg message handlers

BOOL CBackPg::Create( CWnd* pParent, UINT nDlg )
{	return CDialog::Create( nDlg, pParent );	}
