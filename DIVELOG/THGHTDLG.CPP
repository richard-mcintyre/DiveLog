// thghtdlg.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "thghtdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThoughtDlg dialog


CThoughtDlg::CThoughtDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThoughtDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CThoughtDlg)
	m_bShow = FALSE;
	//}}AFX_DATA_INIT
//	m_bShow = TRUE;
}

void CThoughtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThoughtDlg)
	DDX_Check(pDX, IDC_SHOW, m_bShow);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CThoughtDlg, CDialog)
	//{{AFX_MSG_MAP(CThoughtDlg)
	ON_BN_CLICKED(IDC_SHOW, OnShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CThoughtDlg message handlers

BOOL CThoughtDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	
	int nIndex = AfxGetApp()->GetProfileInt( "Thoughts", "Index", 0 );
	m_bShow = AfxGetApp()->GetProfileInt( "Thoughts", "Show", TRUE );
    
	if( m_bShow )
    {
		CStringArray thoughts;
		CStringArray authors;
	
		CFile file;
		if( file.Open( "THOUGHTS.THG", CFile::modeRead ) )
		{
			CArchive ar( &file, CArchive::load );
			CString str;
			WORD wTmp;
			
			ar >> wTmp;
			for( int loop=0; loop<=(int)wTmp; loop++ )
			{
				ar >> str;
				thoughts.Add( str );
				ar >> str;
				authors.Add( str );
			}
		
			ar.Close();
			file.Close();
			
			if( nIndex > thoughts.GetUpperBound() )
				nIndex = 0;
			
			CString thought = thoughts.GetAt( nIndex );
			CString author = authors.GetAt( nIndex );
			
			CWnd* pThought = (CStatic*)GetDlgItem( IDC_THOUGHT );
			pThought->SetWindowText( thought );
			
			CWnd* pAuthor = (CStatic*)GetDlgItem( IDC_AUTHOR );
			pAuthor->SetWindowText( "- " + author );
			
			nIndex++;
			AfxGetApp()->WriteProfileInt( "Thoughts", "Index", nIndex );
		}
		CButton* pBut = (CButton*)GetDlgItem( IDC_SHOW );
		pBut->SetCheck( 1 );
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThoughtDlg::OnOK()
{
	CDialog::OnOK();
	AfxGetApp()->WriteProfileInt( "Thoughts", "Show", m_bShow );
}

void CThoughtDlg::OnShow()
{
	CButton* pBut = (CButton*)GetDlgItem( IDC_SHOW );
	if( m_bShow )
	{
		pBut->SetCheck( 0 );
		m_bShow = FALSE;
	}
	else
	{
		pBut->SetCheck( 1 );
		m_bShow = TRUE;
	}
}
