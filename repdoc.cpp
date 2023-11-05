// repdoc.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "divedata.h"
#include "reports.h"
#include "repdoc.h"
#include "repview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportDoc

IMPLEMENT_DYNCREATE(CReportDoc, CDocument)

CReportDoc::CReportDoc()
{
	m_pReport = NULL;
	m_pRepSet = NULL;
	m_bRecords = FALSE;
	m_nRecs = 0;
	m_nColsWidth = 0;
}

BOOL CReportDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

CReportDoc::~CReportDoc()
{
}


BEGIN_MESSAGE_MAP(CReportDoc, CDocument)
	//{{AFX_MSG_MAP(CReportDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CReportDoc diagnostics

#ifdef _DEBUG
void CReportDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CReportDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportDoc serialization

void CReportDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CReportDoc commands
	
void CReportDoc::DoReport( CReport* pReport, CDiveSet* pSet )
{
	ASSERT_VALID( pReport );
	ASSERT_VALID( pSet );

	SetReport( pReport );
	SetDiveSet( pSet );
	pReport->SetDiveSet( pSet );

	m_pRepSet = new CDiveSet;
	m_pDiveSet->m_bReport = TRUE;

	// Create an array of columns in filter
	CObArray	filterCols;

	for( int i=0; i<=m_pReport->m_nFilterDepth-1; i++ )
	{
		CString colName;
		colName = m_pReport->m_strCols.GetAt( i );
		for( int loop=0; loop<=m_pReport->GetColUpperBound(); loop++ )
		{
			CColumn* pCol = (CColumn*)m_pReport->GetCol( loop );
			if( colName == pCol->GetName() )
			{
				filterCols.Add( pCol );
				break;
			}
		}
	}

/*	char buf[100];
	wsprintf( buf, "%d - filter columns", filterCols.GetUpperBound()+1 );
	AfxMessageBox( buf );*/

	//CString loc = pReport->GetLocation();

	CDiveData* pData = NULL;
	CPoint index = m_pDiveSet->DiveFirst( CPoint( 0, 0 ), &pData );

	do
	{
		BOOL bAdd1, bAdd2, bAdd3, bAdd;
		bAdd1 = bAdd2 = bAdd3 = bAdd = TRUE;

		if( filterCols.GetUpperBound() > -1 )
		{
			CColumn* pCol = (CColumn*)filterCols.GetAt( 0 );
			bAdd = bAdd1 = pCol->TestColumn( m_pReport->m_strValue.GetAt( 0 ), m_pReport->m_strOpers.GetAt( 0 ), pData );
		}				
		if( filterCols.GetUpperBound() > 0 )
		{
			CColumn* pCol = (CColumn*)filterCols.GetAt( 1 );
			bAdd2 = pCol->TestColumn( m_pReport->m_strValue.GetAt( 1 ), m_pReport->m_strOpers.GetAt( 1 ), pData );
			if( m_pReport->m_strJoins.GetAt( 0 ) == "AND" && bAdd1 && bAdd2 )
				bAdd = TRUE;
			else if( m_pReport->m_strJoins.GetAt( 0 )=="OR" && !bAdd1 && bAdd2 ||
								 m_pReport->m_strJoins.GetAt( 0 )=="OR" && bAdd1 && !bAdd2 )
				bAdd = TRUE;
			else
				bAdd = FALSE;
		}				
		if( filterCols.GetUpperBound() > 1 )
		{
			CColumn* pCol = (CColumn*)filterCols.GetAt( 2 );
			bAdd3 = pCol->TestColumn( m_pReport->m_strValue.GetAt( 2 ), m_pReport->m_strOpers.GetAt( 2 ), pData );
			if( m_pReport->m_strJoins.GetAt( 1 ) == "AND" && bAdd )
				bAdd = TRUE;
			else if( m_pReport->m_strJoins.GetAt( 1 )=="OR" && !bAdd && bAdd3 ||
							m_pReport->m_strJoins.GetAt( 1 )=="OR" && !bAdd3 && bAdd )
				bAdd = TRUE;
			else 
				bAdd = FALSE;
		}

		if( bAdd )
		{
			m_bRecords = TRUE;
			m_pRepSet->AddDive( pData );
			m_nRecs++;
		}
		index = m_pDiveSet->DiveNext( index, &pData );
	} while( index != CPoint( 9999, 9999 ) );

	for( i=0; i<=pReport->GetRepColUpperBound( ); i++ )
	{
		CColumn* pCol = (CColumn*)pReport->GetRepCol( i );
		m_nColsWidth += pCol->GetWidth()+30;
	}

	POSITION pos = GetFirstViewPosition();
	CReportView* pView = (CReportView*)GetNextView( pos );
	pView->CorrectScrollSize();

		   /*
	char buf[100];
	wsprintf( buf, "%d - records", nRecs );
	AfxMessageBox( buf );  */
};


void CReportDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( FALSE );	
}
