// divedoc.cpp : implementation of the CDiveDoc class
//

#include "stdafx.h"
#include "divelog.h"

#include "divedoc.h"
#include "divevw.h"
#include "divedata.h"
#include "buddata.h"
#include "defset.h"
#include "divepg.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc

IMPLEMENT_DYNCREATE(CDiveDoc, CDocument)

BEGIN_MESSAGE_MAP(CDiveDoc, CDocument)
	//{{AFX_MSG_MAP(CDiveDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc construction/destruction

CDiveDoc::CDiveDoc()
{
	m_pDiveSet = new CDiveSet;
	m_pCurDive = NULL; //new CDiveData;
	m_curIndex = CPoint( 0, 0 );
	m_pBudSet = new CBudSet;
	m_pCurBud = NULL;
	m_nBudIndex = 0;
	m_frontText = "";
}

CDiveDoc::~CDiveDoc()
{
	delete m_pDiveSet;
	delete m_pBudSet;
	for( int i=0; i<=m_defDives.GetUpperBound(); i++ )
		delete (CDefDive*)m_defDives.GetAt( i );
	m_defDives.RemoveAll();
}

BOOL CDiveDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	delete m_pDiveSet;
	delete m_pBudSet;
	m_pDiveSet = new CDiveSet;
	m_pCurDive = new CDiveData;
	m_pBudSet = new CBudSet;
	m_pCurBud = new CBudData;
	m_curIndex = m_pDiveSet->AddDive( m_pCurDive );
	m_nBudIndex = m_pBudSet->AddRec( m_pCurBud );
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc serialization

BOOL CDiveDoc::OnOpenDocument(const char* pszPathName)
{
	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document\n");

	CFile file;
	CFileException fe;
	if (!file.Open(pszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		ReportSaveLoadException(pszPathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}

	DeleteContents();
	SetModifiedFlag(TRUE);  // dirty during de-serialize

	CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	BYTE ident1, ident2, ident3, fileVer;
	loadArchive >> ident1;	loadArchive >> ident2;	loadArchive >> ident3;	loadArchive >> fileVer;
	if( ident1!='D' || ident2!='V' || ident3!='L' )
	{
		AfxMessageBox( "Not a dive log file!" );
		return FALSE;
	}
	if( fileVer > 0x03 )
	{
		AfxMessageBox( "File version not supported!" );
		return FALSE;
	}
	else
		m_pDiveSet->SetFileVersion( fileVer );

	loadArchive.m_pDocument = this;
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		BeginWaitCursor();
		Serialize(loadArchive);     // load me
		loadArchive.Close();
		file.Close();
	}
	CATCH_ALL(e)
	{
		file.Abort(); // will not throw an exception
		DeleteContents();   // remove failed contents
		EndWaitCursor();

		TRY
			ReportSaveLoadException(pszPathName, e,
				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		END_TRY
		return FALSE;
	}
	END_CATCH_ALL

	EndWaitCursor();
	SetModifiedFlag(FALSE);     // start off with unmodified
	return TRUE;
}

BOOL CDiveDoc::OnSaveDocument(const char* pszPathName)
{
	if( m_pDiveSet->GetFileVersion() < 0x03 ) 
	{
		CString text;	text.LoadString( IDS_OLDVER );
		if( AfxMessageBox( text, MB_YESNO )==IDNO )
			return FALSE;
	}

	CFile file;
	CFileException fe;

	if (!file.Open(pszPathName, CFile::modeCreate |
	  CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
		ReportSaveLoadException(pszPathName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		return FALSE;
	}

	CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_pDocument = this;
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		BeginWaitCursor();
		Serialize(saveArchive);     // save me
		saveArchive.Close();
		file.Close();
	}
	CATCH_ALL(e)
	{
		file.Abort(); // will not throw an exception
		EndWaitCursor();

		TRY
			ReportSaveLoadException(pszPathName, e,
				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		END_TRY
		return FALSE;
	}
	END_CATCH_ALL

	EndWaitCursor();
	SetModifiedFlag(FALSE);     // back to unmodified

	return TRUE;        // success
}

void CDiveDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		m_pDiveSet->SetFileVersion( 0x03 );
		ar << (BYTE)'D';	ar << (BYTE)'V';	ar << (BYTE)'L';
		ar << (BYTE)m_pDiveSet->GetFileVersion( );
		ar << m_frontText;
	}
	else
	{
		if( m_pDiveSet->GetFileVersion() == 0x02 || m_pDiveSet->GetFileVersion() == 0x03 )
			ar >> m_frontText;
	}
	m_pDiveSet->Serialize( ar );
	if( m_pDiveSet->GetFileVersion( ) == 0x02 ||
					m_pDiveSet->GetFileVersion( ) == 0x03 )
	{
		if( ar.IsStoring() )
		{
			ar << (WORD)m_defDives.GetUpperBound();
			for( int i=0; i<=m_defDives.GetUpperBound(); i++ )
			{														
				CDefDive* pDefDive = (CDefDive*)m_defDives.GetAt ( i );
				pDefDive->Serialize( ar );
			}								
		}							
		else
		{ 			
			WORD wTmp;	int nTmp;
			ar >> wTmp;	nTmp = (int)wTmp;
			if( nTmp == 65535 )
				nTmp = -1;
			for( int i=0; i<=nTmp; i++ )
			{
				CDefDive* pDefDive = new CDefDive;
				pDefDive->Serialize( ar );	
				m_defDives.Add( pDefDive );
			}
		}									
	}
	
	if( m_pDiveSet->GetFileVersion( ) == 0x03 )
		m_pBudSet->Serialize( ar );
	else
	{
		m_pBudSet = new CBudSet;
		m_pCurBud = new CBudData;
		m_nBudIndex = m_pBudSet->AddRec( m_pCurBud );
	}

	if( m_pDiveSet->GetFileVersion( ) == 0x01 )
		CalcAll();

	if( !ar.IsStoring() )
		DiveFirst();
}

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc diagnostics

#ifdef _DEBUG
void CDiveDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDiveDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc commands

void CDiveDoc::CalcAll()
{
	AfxGetApp()->DoWaitCursor( 1 );

	CDiveData* pData = DiveFirst( );

	do
	{
		CalcDiveTables();
		pData = DiveNext( );
	} while( m_curIndex != CPoint( 9999, 9999 ) );

	AfxGetApp()->DoWaitCursor( 0 );
}

CDiveData* CDiveDoc::NewDive( )
{
	CDiveData* pPrevDive = m_pCurDive;
	m_pCurDive = new CDiveData;
	m_pCurDive->TransInfo( pPrevDive );
	m_curIndex = m_pDiveSet->AddDive( m_pCurDive );
	return m_pCurDive;
}

CDiveData* CDiveDoc::RemoveDive( )
{
	m_curIndex = m_pDiveSet->RemoveDive( m_curIndex );
	if( m_curIndex == CPoint( -1, -1 ) )
		return NewDive( );
	else
		return m_pDiveSet->GetDiveData( m_curIndex );
}

CDiveData* CDiveDoc::DivePrev( )
{
	m_curIndex = m_pDiveSet->DivePrev( m_curIndex, &m_pCurDive );
	return m_pCurDive;
}

CDiveData* CDiveDoc::DiveNext( )
{
	m_curIndex = m_pDiveSet->DiveNext( m_curIndex, &m_pCurDive );
	return m_pCurDive;
}

CDiveData* CDiveDoc::DiveFirst( )
{
	m_curIndex = m_pDiveSet->DiveFirst( m_curIndex, &m_pCurDive );
	return m_pCurDive;
}

CDiveData* CDiveDoc::DiveLast( )
{
	m_curIndex = m_pDiveSet->DiveLast( m_curIndex, &m_pCurDive );
	return m_pCurDive;
}

BOOL CDiveDoc::IsFirstDive( ) const
{
	return (m_curIndex == CPoint( 0, 0 )) ? TRUE : FALSE;
}

BOOL CDiveDoc::IsLastDive( ) const
{
	return m_pDiveSet->IsLastDive( m_curIndex );
}
	
void CDiveDoc::DateChanged( )
{
	CPoint oldIndex = m_curIndex;
	m_curIndex = m_pDiveSet->DateChanged( m_curIndex, &m_pCurDive );
	POSITION pos = GetFirstViewPosition( );
	CDiveView* pView = (CDiveView*)GetNextView( pos );
	pView->GetDivePage2()->DisplayABTTimes( m_pCurDive );
	m_pDiveSet->CalcRNTDay( oldIndex );
	m_pDiveSet->CalcRNTDay( m_curIndex );
	//pView->GetDivePage1()->UpdateControls( m_pCurDive );
	if( CMainFrame::bVGA )
		pView->GetDivePage1()->InvalidateRect( CRect( 0, 320, 200, 335 ) );
	else
		pView->GetDivePage1()->InvalidateRect( CRect( 0, 420, 270, 435 ) );

	pView->GetDivePage2()->UpdateControls( m_pCurDive );
}

void CDiveDoc::DateFinished( )
{					   /*
	CPoint oldIndex = m_curIndex;
	m_curIndex = m_pDiveSet->DateChanged( m_curIndex, &m_pCurDive );
	POSITION pos = GetFirstViewPosition( );
	CDiveView* pView = (CDiveView*)GetNextView( pos );
	pView->GetDivePage2()->DisplayABTTimes( m_pCurDive );
	m_pDiveSet->CalcRNTDay( oldIndex );
	m_pDiveSet->CalcRNTDay( m_curIndex );
	pView->GetDivePage1()->UpdateControls( m_pCurDive );
	pView->GetDivePage2()->UpdateControls( m_pCurDive );*/
}

BOOL CDiveDoc::IsDiveBegin( ) const
{
	return (m_curIndex.y==0) ? TRUE : FALSE;
}

CDiveData* CDiveDoc::GetDiveData( CPoint index ) const
{
	return m_pDiveSet->GetDiveData( index );
}

int CDiveDoc::GetNoOfDayDives( int nDay ) const
{
	return m_pDiveSet->GetNoOfDayDives( nDay );
}

CBudData* CDiveDoc::NewBud( )
{
	m_pCurBud = new CBudData;
	m_nBudIndex = m_pBudSet->AddRec( m_pCurBud );
	return m_pCurBud;
}

CBudData* CDiveDoc::RemoveBud( )
{
	m_nBudIndex = m_pBudSet->RemoveRec( m_nBudIndex );
	if( m_nBudIndex == -1 )
	{
		m_pCurBud = NewBud();
		return m_pCurBud;
	}
	else
	{
		m_pCurBud = m_pBudSet->GetBudData( m_nBudIndex );
		return m_pCurBud;
	}
}

CBudData* CDiveDoc::BudPrev( )
{
	m_nBudIndex = m_pBudSet->BudPrev( m_nBudIndex, &m_pCurBud );
	return m_pCurBud;
}
	
CBudData* CDiveDoc::BudNext( )
{
	m_nBudIndex = m_pBudSet->BudNext( m_nBudIndex, &m_pCurBud );
	return m_pCurBud;
}

CBudData* CDiveDoc::BudFirst( )
{
	m_nBudIndex = m_pBudSet->BudFirst( &m_pCurBud );
	return m_pCurBud;
}

CBudData* CDiveDoc::BudLast( )
{
	m_nBudIndex = m_pBudSet->BudLast( &m_pCurBud );
	return m_pCurBud;
}

CBudData* CDiveDoc::FindBud( CString let )
{
	m_nBudIndex = m_pBudSet->FindBud( let, &m_pCurBud );
	return m_pCurBud;
}

BOOL CDiveDoc::IsFirstBud( ) const
{
	return ( m_nBudIndex==0 ) ? TRUE : FALSE;
}

BOOL CDiveDoc::IsLastBud( ) const
{
	return ( m_nBudIndex==m_pBudSet->GetNoOfRecs() ) ? TRUE : FALSE;
}

void CDiveDoc::CalcDiveTables()
{
	// calculate this day dives
	CStatusBar* pBar = (CStatusBar*)AfxGetMainWnd()->GetDescendantWindow( AFX_IDW_STATUS_BAR );
	if( pBar != NULL )
	{	pBar->SetWindowText( "Calculating dive..." );	pBar->UpdateWindow();	}

	CTimeSpan ABTtoDate( 0, 0, 0, 0 );
	CDiveDoc* pDoc = this;
	CDiveData* pCurData = GetCurRecord();	
	CPoint index = GetCurIndex();	index.y=0;
	CDiveData* pData = GetDiveData( index );

	float depth = pData->GetDepth();
	// if the depth is a fraction round it up
	if( (depth-(int)depth)!=0 )
	{	depth = (float)((int)depth);	depth++;	}
	// if the surface temp is cold then add 4m to the depth
	if( pData->GetSurfaceTemp()==CDiveData::Cold || pData->GetBottomTemp()==CDiveData::Cold )
	{
		if( pData->GetDepthMts() )
			depth += 4;
		else
			depth += (float)13.1;
	}

	// Must make sure that the depth is not too deep otherwise the calculations will fail
	if( pData->GetDepthMts() )
		depth = (depth<0 || depth>42) ? 42 : depth;
	else
		depth = (depth<0 || depth>140) ? 140 : depth;

	// index.y==0 so this is the first dive of the day
	pData->SetLastPG( 0 );
	pData->SetPGBeforeDive( 'A' );
	
	int nPG;
	if( pData->GetDepthMts() )
		nPG = CDiveApp::table1M.FindMtrs( (int)depth, pData->GetBottomTime() );
	else
		nPG = CDiveApp::table1F.FindFt( (int)depth, pData->GetBottomTime() );
	if( nPG > 25 )	// exceeded padi table
		nPG = '?' - 'A';
		
	int nOffset = 'A';	char PG = nOffset + nPG;
		
	pData->SetRNT( 0 );	pData->SetABT( 0 );	pData->SetABT( 0 );
	if( nPG=='?' - 'A' )	// exceeded padi table so find the highest PG 
	{						// by adjusting the bottom time
		int nBT = pData->GetBottomTime();
		nPG = 999;
		while( nPG > 25 )
		{
			nBT--;
			if( pData->GetDepthMts() )
				nPG = CDiveApp::table1M.FindMtrs( (int)depth, nBT );
			else
				nPG = CDiveApp::table1F.FindFt( (int)depth, nBT );
		}
	}
	pData->SetPGAfterDive( PG );
	
	int lastPG = nPG;
	
	pData->SetABTtoDate( CTime( 1970, 1, 1, ABTtoDate.GetHours(), ABTtoDate.GetMinutes(), 0 ) );
	int nHours = pData->GetBottomTime() / 60;
	int nMins = pData->GetBottomTime() - (nHours*60);
	pData->IncABTtoDate( CTimeSpan( 0, nHours, nMins, 0 ) );
	pData->SetABTDive( CTime( 1970, 1, 1, nHours, nMins, 0 ) );
	ABTtoDate = CTimeSpan( 0, pData->GetABTtoDate().GetHour(), pData->GetABTtoDate().GetMinute(), 0 );
	CTime tm = GetDiveSet()->GetTotalABT(  );
	GetDiveSet()->SetTotalABT( CTime( 1970, 1, 1, (tm.GetHour()+ABTtoDate.GetHours()),
												(tm.GetMinute()+ABTtoDate.GetMinutes())-pData->GetBottomTime(), 0 ) );
	
	// now calculate the rest of the dives
	for( int loop=1; loop<=pDoc->GetNoOfDayDives( index.x ); loop++ )
	{
		pData = pDoc->GetDiveData( CPoint( index.x, loop ) );
		depth = pData->GetDepth();
		// if the depth is a fraction round it up
		if( (depth-(int)depth)!=0 )
		{	depth = (float)((int)depth);	depth++;	}
		// if the surface temp is cold then add 4m to the depth
		if( pData->GetSurfaceTemp()==CDiveData::Cold || pData->GetBottomTemp()==CDiveData::Cold )
			depth += 4;
	
		// Must make sure that the depth is not too deep otherwise the calculations will fail
		if( pData->GetDepthMts() )
			depth = (depth<0 || depth>42) ? 42 : depth;
		else
			depth = (depth<0 || depth>140) ? 140 : depth;

		pData->SetLastPG( lastPG );
		
		CString si = pData->GetSI().Format( "%H%M" );
		const char* pszSI = si;
		int nSI = (int)strtol( pszSI, (char**)&pszSI, 10 );
		int nPG = CDiveApp::table2.Find( lastPG, nSI );
		int nOffset = 'A';	char PG = nOffset + nPG;
		pData->SetPGBeforeDive( PG );
		
		WORD wTmp;
		if( pData->GetDepthMts() )
			wTmp = CDiveApp::table3M.FindMtrs( nPG, (int)depth );
		else
			wTmp = CDiveApp::table3F.FindFt( nPG, (int)depth );
		int nRNT = LOBYTE( wTmp );
		int nANDL = HIBYTE( wTmp );
		
		// The ABT should not be greater than the ANDL
		if( pData->GetBottomTime() > nANDL )
			nPG = '?' - 'A';
		
		pData->SetRNT( nRNT );
		pData->SetABT( pData->GetBottomTime() );
		pData->SetTBT( nRNT + pData->GetABT() );
		
		if( nPG=='?' - 'A' )	// exceeded padi table so find the highest PG 
		{						// by adjusting the bottom time
			int nBT = pData->GetTBT();  // Bottom Time
			nPG = 999;
			while( nPG > 25 )
			{
				nBT--;
				if( pData->GetDepthMts() )
					nPG = CDiveApp::table1M.FindMtrs( (int)depth, nBT );
				else
					nPG = CDiveApp::table1F.FindFt( (int)depth, nBT );
			}
			lastPG = nPG;
			pData->SetPGAfterDive( '?' );
		}
		else
		{
			// Now calculate the pressure group at the end of the dive using TBT
			if( pData->GetDepthMts() )
				nPG = CDiveApp::table1M.FindMtrs( (int)depth, pData->GetTBT() );
			else
				nPG = CDiveApp::table1F.FindFt( (int)depth, pData->GetTBT() );
			lastPG = nPG;
			pData->SetPGAfterDive( nOffset + nPG );
		}
		
		pData->SetABTtoDate( CTime( 1970, 1, 1, ABTtoDate.GetHours(), ABTtoDate.GetMinutes(), 0 ) );
		int nHours = pData->GetBottomTime() / 60;
		int nMins = pData->GetBottomTime() - (nHours*60);
		pData->IncABTtoDate( CTimeSpan( 0, nHours, nMins, 0 ) );
		pData->SetABTDive( CTime( 1970, 1, 1, nHours, nMins, 0 ) );
		ABTtoDate = CTimeSpan( 0, pData->GetABTtoDate().GetHour(), pData->GetABTtoDate().GetMinute(), 0 );
		CTime tm = GetDiveSet()->GetTotalABT(  );
		GetDiveSet()->SetTotalABT( CTime( 1970, 1, 1, (tm.GetHour()+ABTtoDate.GetHours()),
												(tm.GetMinute()+ABTtoDate.GetMinutes())-pData->GetBottomTime(), 0 ) );
	}

    if( pBar != NULL )
    {
		CString str;
		str.LoadString( AFX_IDS_IDLEMESSAGE );
		pBar->SetWindowText( str );
		pBar->UpdateWindow();
	}
}
