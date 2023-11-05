// filtdlg.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "filtdlg.h"
#include "divedata.h"
#include "reports.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterDlg dialog


CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilterDlg)
	//}}AFX_DATA_INIT
}


void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterDlg)
	DDX_Control(pDX, IDC_VALUE3, m_ctlValue3);
	DDX_Control(pDX, IDC_VALUE2, m_ctlValue2);
	DDX_Control(pDX, IDC_VALUE1, m_ctlValue1);
	DDX_Control(pDX, IDC_OPER3, m_ctlOper3);
	DDX_Control(pDX, IDC_OPER2, m_ctlOper2);
	DDX_Control(pDX, IDC_OPER1, m_ctlOper1);
	DDX_Control(pDX, IDC_JOIN2, m_ctlJoin2);
	DDX_Control(pDX, IDC_JOIN1, m_ctlJoin1);
	DDX_Control(pDX, IDC_COLUMN3, m_ctlCol3);
	DDX_Control(pDX, IDC_COLUMN2, m_ctlCol2);
	DDX_Control(pDX, IDC_COLUMN1, m_ctlCol1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialog)
	//{{AFX_MSG_MAP(CFilterDlg)
	ON_CBN_EDITCHANGE(IDC_JOIN1, OnEditchangeJoin1)
	ON_CBN_CLOSEUP(IDC_JOIN1, OnCloseupJoin1)
	ON_CBN_CLOSEUP(IDC_JOIN2, OnCloseupJoin2)
	ON_CBN_EDITCHANGE(IDC_JOIN2, OnEditchangeJoin2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFilterDlg message handlers

BOOL CFilterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow( );

	for( int i=0; i<=m_pReport->GetColUpperBound(); i++ )
	{
		CColumn* pCol = m_pReport->GetCol( i );
		m_ctlCol1.AddString( pCol->GetName( ) );
		m_ctlCol2.AddString( pCol->GetName( ) );
		m_ctlCol3.AddString( pCol->GetName( ) );
	}
	
	m_ctlCol1.SetCurSel( 0 );
	m_ctlCol2.SetCurSel( 0 );
	m_ctlCol3.SetCurSel( 0 );

	m_ctlOper1.SetCurSel( 0 );
	m_ctlOper2.SetCurSel( 0 );
	m_ctlOper3.SetCurSel( 0 );

	if( m_strCols.GetUpperBound() > -1 )
		m_ctlCol1.SetCurSel( m_ctlCol1.FindStringExact( -1, m_strCols.GetAt( 0 ) ) );
	if( m_strCols.GetUpperBound() > 0 )
		m_ctlCol2.SetCurSel( m_ctlCol2.FindStringExact( -1, m_strCols.GetAt( 1 ) ) );
	if( m_strCols.GetUpperBound() > 1 )
		m_ctlCol3.SetCurSel( m_ctlCol3.FindStringExact( -1, m_strCols.GetAt( 2 ) ) );

	if( m_strOpers.GetUpperBound() > -1 )
		m_ctlOper1.SetCurSel( m_ctlOper1.FindStringExact( -1, m_strOpers.GetAt( 0 ) ) );
	if( m_strOpers.GetUpperBound() > 0 )
		m_ctlOper2.SetCurSel( m_ctlOper2.FindStringExact( -1, m_strOpers.GetAt( 1 ) ) );
	if( m_strOpers.GetUpperBound() > 1 )
		m_ctlOper3.SetCurSel( m_ctlOper3.FindStringExact( -1, m_strOpers.GetAt( 2 ) ) );

	if( m_strValue.GetUpperBound() > -1 )
		m_ctlValue1.SetWindowText( m_strValue.GetAt( 0 ) );
	if( m_strValue.GetUpperBound() > 0 )
		m_ctlValue2.SetWindowText( m_strValue.GetAt( 1 ) );
	if( m_strValue.GetUpperBound() > 1 )
		m_ctlValue3.SetWindowText( m_strValue.GetAt( 2 ) );

	if( m_strJoins.GetUpperBound() > -1 )
		m_ctlJoin1.SetCurSel( m_ctlJoin1.FindStringExact( -1, m_strJoins.GetAt( 0 ) ) );
	if( m_strJoins.GetUpperBound() > 0 )
		m_ctlJoin2.SetCurSel( m_ctlJoin2.FindStringExact( -1, m_strJoins.GetAt( 1 ) ) );

	OnCloseupJoin1();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFilterDlg::OnCloseupJoin1() 
{
	CString str;
	if( m_ctlJoin1.GetCurSel() != CB_ERR )
		m_ctlJoin1.GetLBText( m_ctlJoin1.GetCurSel(), str );
	m_ctlJoin1.SetWindowText( str );
	OnEditchangeJoin1( );
	//OnEditchangeJoin2( );
}

void CFilterDlg::OnEditchangeJoin1() 
{
	OnEditchangeJoin2( );

	CString str;
	m_ctlJoin1.GetWindowText( str );	str.MakeUpper( );
	if( str == "AND" || str == "OR" )
	{
		m_ctlCol2.EnableWindow();	m_ctlOper2.EnableWindow();
		m_ctlValue2.EnableWindow();	m_ctlJoin2.EnableWindow();
	}
	else
	{
		m_ctlCol2.EnableWindow( FALSE );	m_ctlOper2.EnableWindow( FALSE );
		m_ctlValue2.EnableWindow( FALSE );	m_ctlJoin2.EnableWindow( FALSE );
		m_ctlCol3.EnableWindow( FALSE );	m_ctlOper3.EnableWindow( FALSE );
		m_ctlValue3.EnableWindow( FALSE );
	}
}

void CFilterDlg::OnCloseupJoin2() 
{
	CString str;
	m_ctlJoin2.GetLBText( m_ctlJoin2.GetCurSel(), str );
	m_ctlJoin2.SetWindowText( str );
	OnEditchangeJoin2( );
}

void CFilterDlg::OnEditchangeJoin2() 
{
	CString str;
	m_ctlJoin2.GetWindowText( str );	str.MakeUpper( );
	if( str == "AND" || str == "OR" )
	{
		m_ctlCol3.EnableWindow();	m_ctlOper3.EnableWindow();
		m_ctlValue3.EnableWindow();
	}
	else
	{
		m_ctlCol3.EnableWindow( FALSE );	m_ctlOper3.EnableWindow( FALSE );
		m_ctlValue3.EnableWindow( FALSE );
	}
}

void CFilterDlg::OnOK() 
{
	CString strTmp;
	m_strCols.RemoveAll();	m_strOpers.RemoveAll();
	m_strValue.RemoveAll();	m_strJoins.RemoveAll();
	if( m_ctlCol1.GetCurSel()!=CB_ERR )	{	m_ctlCol1.GetLBText( m_ctlCol1.GetCurSel(), strTmp );	m_strCols.Add( strTmp );	}
	if( m_ctlCol2.GetCurSel()!=CB_ERR )	{	m_ctlCol2.GetLBText( m_ctlCol2.GetCurSel(), strTmp );	m_strCols.Add( strTmp );	}
	if( m_ctlCol3.GetCurSel()!=CB_ERR )	{	m_ctlCol3.GetLBText( m_ctlCol3.GetCurSel(), strTmp );	m_strCols.Add( strTmp );	}
	if( m_ctlOper1.GetCurSel()!=CB_ERR )	{	m_ctlOper1.GetLBText( m_ctlOper1.GetCurSel(), strTmp );	m_strOpers.Add( strTmp );	}
	if( m_ctlOper2.GetCurSel()!=CB_ERR )	{	m_ctlOper2.GetLBText( m_ctlOper2.GetCurSel(), strTmp );	m_strOpers.Add( strTmp );	}
	if( m_ctlOper3.GetCurSel()!=CB_ERR )	{	m_ctlOper3.GetLBText( m_ctlOper3.GetCurSel(), strTmp );	m_strOpers.Add( strTmp );	}
	m_ctlValue1.GetWindowText( strTmp );	m_strValue.Add( strTmp );
	m_ctlValue2.GetWindowText( strTmp );	m_strValue.Add( strTmp );
	m_ctlValue3.GetWindowText( strTmp );	m_strValue.Add( strTmp );

	CString strJoin1;	CString strJoin2;
	if( m_ctlJoin1.GetCurSel()!=CB_ERR )
	{	m_ctlJoin1.GetLBText( m_ctlJoin1.GetCurSel(), strJoin1 );	m_strJoins.Add( strJoin1 );	}
	else
	{	m_ctlJoin1.GetWindowText( strJoin1 );	m_strJoins.Add( strJoin1 );	}
	if( m_ctlJoin2.GetCurSel()!=CB_ERR )
	{	m_ctlJoin2.GetLBText( m_ctlJoin2.GetCurSel(), strJoin2 );	m_strJoins.Add( strJoin2 );	}
	else
	{	m_ctlJoin2.GetWindowText( strJoin2 );	m_strJoins.Add( strJoin2 );	}

	m_nFilterDepth = 1;

	if( strJoin1=="AND" || strJoin1=="OR" )
		m_nFilterDepth = 2;
	if( (strJoin2=="AND" || strJoin2=="OR") && (strJoin1=="AND" || strJoin1=="OR") )
		m_nFilterDepth = 3;
	
	CDialog::OnOK();
}
