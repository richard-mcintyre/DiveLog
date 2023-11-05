// reprtdlgcpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "divedata.h"
#include "reports.h"
#include "reprtdlg.h"
#include "repdoc.h"
#include "filtdlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportsDlg dialog

CReportsDlg::CReportsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportsDlg)
	m_repName = _T("");
	m_repWidth = 10;
	//}}AFX_DATA_INIT
	m_pDiveSet = NULL;
	m_pCurCol = NULL;
	m_pReport = new CReport;
	m_pReport->SetDiveSet( m_pDiveSet );
	m_pReport->NewCol( "Location",	CColumn::Text, 300 );
	m_pReport->NewCol( "Notes",		CColumn::Text, 300 );
	m_pReport->NewCol( "PG Before Dive",	CColumn::Text, 60 );
	m_pReport->NewCol( "PG After Dive",		CColumn::Text, 60 );
	m_pReport->NewCol( "Fresh",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Shore",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Waves",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Surf",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Salt",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Boat",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Current",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Surge",		CColumn::Bool, 60 );
	m_pReport->NewCol( "Wet Suit",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Under Suit",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Semi Dry Suit",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Dry Suit",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Gloves",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Mittens",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Hood",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Socks",	CColumn::Bool, 60 );
	m_pReport->NewCol( "Date",	CColumn::Date, 300 );
	m_pReport->NewCol( "Time In",	CColumn::Time, 100 );
	m_pReport->NewCol( "Time Out",	CColumn::Time, 100 );
	m_pReport->NewCol( "Surface Interval",	CColumn::Time, 100 );
	m_pReport->NewCol( "Air Start",	CColumn::Integer, 120 );
	m_pReport->NewCol( "Air End",	CColumn::Integer, 120 );
	m_pReport->NewCol( "Weight",	CColumn::Integer, 60 );
	m_pReport->NewCol( "Bottom Time",	CColumn::Integer, 60 );
	m_pReport->NewCol( "Decompression Stop",	CColumn::Integer, 100 );
	m_pReport->NewCol( "R.N.T.",	CColumn::Integer, 80 );
	m_pReport->NewCol( "A.B.T.",	CColumn::Integer, 80 );
	m_pReport->NewCol( "T.B.T.",	CColumn::Integer, 80 );
	m_pReport->NewCol( "Air Temperature",		CColumn::Temperature, 100 );
	m_pReport->NewCol( "Surface Temperature",	CColumn::Temperature, 100 );
	m_pReport->NewCol( "Bottom Temperature",	CColumn::Temperature, 100 );
	m_pReport->NewCol( "Visibility Distance",	CColumn::Real, 100 );
	m_pReport->NewCol( "Depth",					CColumn::Real, 120 );
	m_pReport->NewCol( "Visibility Type",		CColumn::VisStyle, 120 );
}


void CReportsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportsDlg)
	DDX_Control(pDX, IDC_REPWIDTH, m_ctlRepWidth);
	DDX_Control(pDX, IDC_REPNAME, m_ctlRepName);
	DDX_Control(pDX, IDC_REPCOLS_LIST, m_ctlRepCols);
	DDX_Control(pDX, IDC_COLS_LIST, m_ctlCols);
	DDX_Text(pDX, IDC_REPNAME, m_repName);
	DDX_Text(pDX, IDC_REPWIDTH, m_repWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportsDlg, CDialog)
	//{{AFX_MSG_MAP(CReportsDlg)
	ON_LBN_DBLCLK(IDC_COLS_LIST, OnDblclkColsList)
	ON_LBN_DBLCLK(IDC_REPCOLS_LIST, OnDblclkRepcolsList)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_REMOVE_ALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_INSERT_ALL, OnInsertAll)
	ON_BN_CLICKED(IDC_FILTER, OnFilter)
	ON_LBN_SELCHANGE(IDC_REPCOLS_LIST, OnSelchangeRepcolsList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReportsDlg message handlers

BOOL CReportsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();

	for( int i=0; i<=m_pReport->GetColUpperBound(); i++ )
	{
		CColumn* pCol = m_pReport->GetCol( i );
		m_ctlCols.AddString( pCol->GetName( ) );
	}

	OnSelchangeRepcolsList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportsDlg::OnDblclkColsList() 
{
	CString str;
	int nCurSel = m_ctlCols.GetCurSel();
	m_ctlCols.GetText( nCurSel, str );
	m_ctlRepCols.InsertString( m_ctlRepCols.GetCurSel(), str );
	m_ctlCols.DeleteString( nCurSel );
}

void CReportsDlg::OnDblclkRepcolsList() 
{
	CString str;
	int nCurSel = m_ctlRepCols.GetCurSel();
	m_ctlRepCols.GetText( nCurSel, str );
	m_ctlCols.AddString( str );
	m_ctlRepCols.DeleteString( nCurSel );
	OnSelchangeRepcolsList();
}

void CReportsDlg::OnInsert() 
{
	if( m_ctlCols.GetCurSel() != LB_ERR )
		OnDblclkColsList();
}

void CReportsDlg::OnRemove() 
{
	if( m_ctlRepCols.GetCurSel() != LB_ERR )
		OnDblclkRepcolsList();
}

void CReportsDlg::OnCancel() 
{
	delete m_pReport;
	
	CDialog::OnCancel();
}

void CReportsDlg::OnOK() 
{
	UpdateData( TRUE );
	if( m_repWidth < 5 || m_repWidth > 2000 )
	{
		OnSelchangeRepcolsList();
		return;
	}
	for( int i=0; i<=m_ctlRepCols.GetCount()-1; i++ )
	{
		CString colName;
		m_ctlRepCols.GetText( i, colName );
										 
		for( int loop=0; loop<=m_pReport->GetColUpperBound(); loop++ )
		{
			CColumn* pCol = (CColumn*)m_pReport->GetCol( loop );
			if( colName == pCol->GetName() )
			{
				m_pReport->m_repColumns.Add( pCol );
				break;
			}
		}
	}
	

	CDiveApp* pApp = (CDiveApp*)AfxGetApp();
	CReportDoc* pDoc = (CReportDoc*)pApp->NewReportWindow( );
	OnSelchangeRepcolsList();

	CDialog::OnOK();

	pDoc->DoReport( m_pReport, m_pDiveSet );
}

void CReportsDlg::OnRemoveAll() 
{
	m_ctlCols.SetRedraw( FALSE );
	m_ctlRepCols.SetRedraw( FALSE );
	while( m_ctlRepCols.GetCount() != 0 )
	{
		m_ctlRepCols.SetCurSel( 0 );
		OnRemove();
	}			
	m_ctlCols.SetRedraw( TRUE );
	m_ctlRepCols.SetRedraw( TRUE );
	OnSelchangeRepcolsList();
}

void CReportsDlg::OnInsertAll() 
{
	m_ctlCols.SetRedraw( FALSE );
	m_ctlRepCols.SetRedraw( FALSE );
	while( m_ctlCols.GetCount() != 0 )
	{
		m_ctlCols.SetCurSel( 0 );
		OnInsert();
	}
	m_ctlCols.SetRedraw( TRUE );
	m_ctlRepCols.SetRedraw( TRUE );
}

void CReportsDlg::OnFilter() 
{
	CFilterDlg dlg;
	dlg.m_pReport = m_pReport;

	for( int i=0; i<=m_pReport->m_strCols.GetUpperBound(); i++ )	
		dlg.m_strCols.Add( m_pReport->m_strCols.GetAt( i ) );
	for( i=0; i<=m_pReport->m_strOpers.GetUpperBound(); i++ )
		dlg.m_strOpers.Add( m_pReport->m_strOpers.GetAt( i ) );
	for( i=0; i<=m_pReport->m_strValue.GetUpperBound(); i++ )
		dlg.m_strValue.Add( m_pReport->m_strValue.GetAt( i ) );
	for( i=0; i<=m_pReport->m_strJoins.GetUpperBound(); i++ )
		dlg.m_strJoins.Add( m_pReport->m_strJoins.GetAt( i ) );
	
	dlg.m_nFilterDepth = m_pReport->m_nFilterDepth;

	if( dlg.DoModal()==IDOK )
	{
		m_pReport->m_strCols.RemoveAll();	m_pReport->m_strOpers.RemoveAll();
		m_pReport->m_strValue.RemoveAll();	m_pReport->m_strJoins.RemoveAll();
		for( i=0; i<=dlg.m_strCols.GetUpperBound(); i++ )	
			m_pReport->m_strCols.Add( dlg.m_strCols.GetAt( i ) );
		for( i=0; i<=dlg.m_strOpers.GetUpperBound(); i++ )
			m_pReport->m_strOpers.Add( dlg.m_strOpers.GetAt( i ) );
		for( i=0; i<=dlg.m_strValue.GetUpperBound(); i++ )
			m_pReport->m_strValue.Add( dlg.m_strValue.GetAt( i ) );
		for( i=0; i<=dlg.m_strJoins.GetUpperBound(); i++ )
			m_pReport->m_strJoins.Add( dlg.m_strJoins.GetAt( i ) );

		m_pReport->m_nFilterDepth = dlg.m_nFilterDepth;
		return;
	}	
}

void CReportsDlg::OnSelchangeRepcolsList() 
{
	CColumn* pCol;
	CString colName;
	int i = m_ctlRepCols.GetCurSel( );

	if( m_pCurCol != NULL )
	{
		UpdateData( TRUE );
		if( m_repWidth < 5 || m_repWidth > 2000 )
		{
			AfxMessageBox( "Column widths must be between 5 and 2000" );
			m_repWidth = m_pCurCol->GetWidth();
		}
		m_pCurCol->SetRepName( m_repName );
		m_pCurCol->SetWidth( m_repWidth );
		AfxGetApp()->WriteProfileString( "Reports", m_pCurCol->GetName(), m_pCurCol->GetRepName() );
		AfxGetApp()->WriteProfileInt( "Reports", m_pCurCol->GetName()+"W", m_pCurCol->GetWidth() );
	}

	if( i == LB_ERR )
	{
		m_repName = "No Selection";
		m_repWidth = 5;
		UpdateData( FALSE );
		m_pCurCol = NULL;
		m_ctlRepName.EnableWindow( FALSE );
		m_ctlRepWidth.EnableWindow( FALSE );
		return;
	}

	m_ctlRepCols.GetText( i, colName ); 
	for( int loop=0; loop<=m_pReport->GetColUpperBound(); loop++ )
	{
		pCol = (CColumn*)m_pReport->GetCol( loop );
		if( colName == pCol->GetName() )
			break;
	}

	m_pCurCol = pCol;
	m_repName = pCol->GetRepName( );
	m_repWidth = pCol->GetWidth( );
	m_ctlRepName.EnableWindow( TRUE );
	m_ctlRepWidth.EnableWindow( TRUE );
	UpdateData( FALSE );
}
