// DIVEDATA.CPP : implementation of the CDiveData class
//

#include "stdafx.h"
#include "divedata.h"
#include "divelog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////
// CDiveSet

IMPLEMENT_DYNCREATE( CDiveSet, CObject )

CDiveSet::CDiveSet( )
{
	m_fileVersion = 0x03;
	m_totalABT = CTime( 1970, 1, 1, 0, 0, 0 );
	m_bReport = FALSE;
}

CDiveSet::~CDiveSet()
{
	if( !m_bReport )
	{
		for( int loop=0; loop<=m_diveDay.GetUpperBound(); loop++ )
		{
			CDiveDay* pDay = (CDiveDay*)m_diveDay.GetAt( loop );
			delete pDay;
		}
	}
}

CTime CDiveSet::GetABTtoDate( CDiveData* pData )
{
	CTime time( 1970, 1, 1, 0, 0, 0 );
	for( int i=0; i<=m_diveDay.GetUpperBound(); i++ )
	{
		CDiveDay* pDay = (CDiveDay*)m_diveDay.GetAt( i );
		CTimeSpan ts( 0, 0, 0, 0 );
		BOOL bFound = pDay->GetTotalABT( ts, pData );
		time += ts;
		if( bFound )
			break;
	}

	return time;
}

CPoint CDiveSet::AddDive( CDiveData* pData )
{
	ASSERT_VALID( pData );
	// first check if there is a CDiveDay object in this dive set
	CTime date = pData->GetDate();
	CDiveDay* pDiveDay = NULL;
	
	for( int loop=0; loop<=m_diveDay.GetUpperBound(); loop++ )
	{
		CDiveDay* pDay = (CDiveDay*)m_diveDay.GetAt( loop );
		if( pDay->GetDate() == date )
		{
			pDiveDay = pDay;
			break;
		}
	}
	
	if( pDiveDay == NULL )
	{
		// Construct a new CDiveDay object
		CDiveDay* pNewDay = new CDiveDay( date );
		// Calculate where we should put pNewDay into the array
		for( loop=0; loop<=m_diveDay.GetUpperBound(); loop++ )
		{
			CDiveDay* pDay = (CDiveDay*)m_diveDay.GetAt( loop );
			if( pDay->GetDate() > date )
				break;
		}				
		m_diveDay.InsertAt( loop, pNewDay );
		return CPoint( loop, pNewDay->AddDive( pData ) );
	}

	int nIndex = pDiveDay->AddDive( pData );
	return CPoint( loop, nIndex );
}

CPoint CDiveSet::RemoveDive( const CPoint index )
{
	CDiveDay* pDay = GetDay( index.x );
	pDay->RemoveEntry( index.y );
	if( pDay->GetNoOfDives() == -1 )
	{
		m_diveDay.RemoveAt( index.x );
		delete pDay;
	}

	if( index == CPoint( 0, 0 ) )
	{
		if( m_diveDay.GetUpperBound() == -1 )	// No more records
			return CPoint( -1, -1 );
		else
		{
			CDiveData* pTmp = new CDiveData;
			CPoint newIndex = DiveNext( index, &pTmp );
			//delete pTmp;
			return newIndex;
		}
	}
	else
	{
		CDiveData* pTmp = new CDiveData;
		CPoint newIndex = DivePrev( index, &pTmp );
		//delete pTmp;
		return newIndex;
	}
}

CPoint CDiveSet::DateChanged( CPoint oldIndex, CDiveData** pData )
{
	CDiveDay* pDay = GetDay( oldIndex.x );
	pDay->RemoveEntry( oldIndex.y );
	if( pDay->GetNoOfDives( ) == -1 )
	{
		m_diveDay.RemoveAt( oldIndex.x );
		delete pDay;
	}
	return AddDive( *pData );
}

CPoint CDiveSet::DivePrev( CPoint index, CDiveData** pData )
{
	ASSERT( index != CPoint( 0, 0 ) );
	if( index.y==0 )
	{
		index.x--;
		CDiveDay* pDay = GetDay( index.x );
		int nInd = pDay->GetNoOfDives( );
		*pData = pDay->GetDive( nInd );
		return CPoint( index.x, nInd );
	}
	else
	{
		CDiveDay* pDay = GetDay( index.x );
		*pData = pDay->GetDive( index.y-1 );	
		return CPoint( index.x, index.y-1 );
	}
}

CPoint CDiveSet::DiveNext( CPoint index, CDiveData** pData )
{
	CDiveDay* pDay = GetDay( index.x );
	if( index.y > pDay->GetNoOfDives() )
	{
		pData = NULL;
		return CPoint( 9999, 9999 );
	}

	//ASSERT( index.y <= pDay->GetNoOfDives() );
	if( pDay->GetNoOfDives( )==index.y )
	{
		if( index.x+1 > m_diveDay.GetUpperBound() )
			return CPoint( 9999, 9999 );

		ASSERT( index.x+1 <= m_diveDay.GetUpperBound() );	// EOF
		pDay = GetDay( index.x + 1 );
		*pData = pDay->GetDive( 0 );
		return CPoint( index.x+1, 0 );
	}
	else
	{
		*pData = pDay->GetDive( index.y + 1 );
		return CPoint( index.x, index.y + 1 );
	}
}	

CPoint CDiveSet::DiveFirst( CPoint index, CDiveData** pData )
{
	ASSERT( m_diveDay.GetUpperBound() >= 0 );
	CDiveDay* pDay = GetDay( 0 );
	
	ASSERT( pDay->GetNoOfDives() >= 0 );
	*pData = pDay->GetDive( 0 );
	return CPoint( 0, 0 );
}

CPoint CDiveSet::DiveLast( CPoint index, CDiveData** pData )
{
	ASSERT( m_diveDay.GetUpperBound() >= 0 );
	CDiveDay* pDay = GetDay( m_diveDay.GetUpperBound() );
	ASSERT( pDay->GetNoOfDives() >= 0 );
	*pData = pDay->GetDive( pDay->GetNoOfDives() );
	return CPoint( m_diveDay.GetUpperBound(), pDay->GetNoOfDives() );
}

CDiveData* CDiveSet::GetDiveData( CPoint index ) const
{
	ASSERT( m_diveDay.GetUpperBound() >= index.x );
	CDiveDay* pDay = GetDay( index.x );
	ASSERT( pDay->GetNoOfDives() >= index.y );
	CDiveData* pData = (CDiveData*)pDay->GetDive( index.y );

	ASSERT_VALID( pData );
	return pData;
}

int CDiveSet::GetNoOfDayDives( int nDay ) const
{
	ASSERT( m_diveDay.GetUpperBound() >= nDay );
	CDiveDay* pDay = GetDay( nDay );
	return pDay->GetNoOfDives();
}

BOOL CDiveSet::IsLastDive( CPoint index )
{
	if( index.x != m_diveDay.GetUpperBound() )
		return FALSE;
	else
	{
		CDiveDay* pDay = GetDay( index.x );
		if( index.y != pDay->GetNoOfDives() )
			return FALSE;
	}
	return TRUE;
}

void CDiveSet::CalcRNTDay( CPoint index )
{
	index.y=0;
	CDiveDay* pDay = GetDay( index.x );
	CDiveData* pData = pDay->GetDive( index.y );
     
	// calculate this day dives
	CStatusBar* pBar = (CStatusBar*)AfxGetMainWnd()->GetDescendantWindow( AFX_IDW_STATUS_BAR );
	if( pBar != NULL )
	{	pBar->SetWindowText( "Calculating dive..." );	pBar->UpdateWindow();	}

	CTimeSpan ABTtoDate( 0, 0, 0, 0 );
	//CDiveDoc* pDoc = m_pView->GetDocument();
	//CDiveData* pCurData = pDoc->GetCurRecord();	
	//CPoint index = pDoc->GetCurIndex();	index.y=0;
	//CDiveData* pData = pDoc->GetDiveData( index );
	
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
	
	pData->SetRNT( 0 );	pData->SetABT( 0 );	pData->SetTBT( 0 );
	
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
	CTime tm = GetTotalABT(  );
	
	CDiveSet* pTmpSet = this;
	
	CTime tmpTime( 1970, 1, 1, (tm.GetHour()+ABTtoDate.GetHours()),
												(tm.GetMinute()+ABTtoDate.GetMinutes())-pData->GetBottomTime(), 0 );
	pTmpSet->SetTotalABT( tmpTime );
	
	// now calculate the rest of the dives
	for( int loop=1; loop<=pDay->GetNoOfDives( ); loop++ )
	{
		pData = GetDiveData( CPoint( index.x, loop ) );
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
	
		CTime tmpTime2( 1970, 1, 1, ABTtoDate.GetHours(), ABTtoDate.GetMinutes(), 0 );
		pData->SetABTtoDate( tmpTime2 );

		int nHours = pData->GetBottomTime() / 60;
		int nMins = pData->GetBottomTime() - (nHours*60);
		pData->IncABTtoDate( CTimeSpan( 0, nHours, nMins, 0 ) );
		pData->SetABTDive( CTime( 1970, 1, 1, nHours, nMins, 0 ) );
		ABTtoDate = CTimeSpan( 0, pData->GetABTtoDate().GetHour(), pData->GetABTtoDate().GetMinute(), 0 );
		CTime tm = GetTotalABT(  );
		
		CDiveSet* pTmp = this;
	}

	if( pBar != NULL )
    {
		CString str;
		str.LoadString( AFX_IDS_IDLEMESSAGE );
		pBar->SetWindowText( str );
		pBar->UpdateWindow();
	}
}

int	CDiveSet::AddDay( CDiveDay* pDay )
{
	return m_diveDay.Add( pDay );
}

CDiveDay* CDiveSet::GetDay( int nIndex ) const
{
	ASSERT( m_diveDay.GetUpperBound() >= nIndex );
	return (CDiveDay*)m_diveDay.GetAt( nIndex );
}

void CDiveSet::Serialize(CArchive& ar)
{
	if( GetFileVersion( )==0x01 )
	{
		SerializeVer1( ar );
		return;
	}
	if (ar.IsStoring())
	{
		ar << m_totalABT;
		ar << (WORD)m_diveDay.GetUpperBound();
		for( int loop=0; loop<=m_diveDay.GetUpperBound(); loop++ )
		{
			CDiveDay* pDay = (CDiveDay*)m_diveDay.GetAt( loop );
			pDay->Serialize( ar );
		}
	}
	else
	{
		WORD wTmp;
		ar >> m_totalABT;
		ar >> wTmp;
		for( int loop=0; loop<=(int)wTmp; loop++ )
		{
			CDiveDay* pDay = new CDiveDay;
			pDay->Serialize( ar );	m_diveDay.Add( pDay );
		}
	}
}

void CDiveSet::SerializeVer1(CArchive& ar)	// file version 1
{
	if (ar.IsStoring())
	{
	}
	else
	{
		WORD wTmp;
		ar >> wTmp;
		for( int loop=0; loop<=(int)wTmp; loop++ )
		{
			CDiveData* pData = new CDiveData;
			pData->SerializeVer1( ar, this );
			AddDive( pData );
		}
	}
}

///////////////////////////////////////////////////////////////////////////
// CDiveDay

IMPLEMENT_DYNCREATE( CDiveDay, CObject )

CDiveDay::CDiveDay( CTime date )
{
	m_date = date;
}

CDiveDay::~CDiveDay()
{
	for( int loop=0; loop<=m_diveData.GetUpperBound(); loop++ )
	{
		CDiveData* pData = (CDiveData*)m_diveData.GetAt( loop );
		delete pData;
	}
}

BOOL CDiveDay::GetTotalABT( CTimeSpan& ts, CDiveData* pEndData )
{
	for( int i=0; i<=m_diveData.GetUpperBound(); i++ )
	{
		CDiveData* pData = (CDiveData*)m_diveData.GetAt( i );
		int nHours = pData->GetBottomTime() / 60;
		int nMins = pData->GetBottomTime() - (nHours*60);
		CTimeSpan ts2( 0, nHours, nMins, 0 );
		ts += ts2;
		if( pEndData != NULL )
			if( pData == pEndData )
				return TRUE;
	}
	return FALSE;
}

int CDiveDay::AddDive( CDiveData* pData )
{
	ASSERT_VALID( pData );
	return m_diveData.Add( pData );
}

CDiveData* CDiveDay::GetDive( int nIndex )
{
	ASSERT( nIndex <= m_diveData.GetUpperBound() );
	return (CDiveData*)m_diveData.GetAt( nIndex );
}

void CDiveDay::RemoveEntry( int nIndex )
{
	ASSERT( nIndex <= m_diveData.GetUpperBound() );
	m_diveData.RemoveAt( nIndex );
}
	
void CDiveDay::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_date;
		ar << (WORD)m_diveData.GetUpperBound();
		for( int loop=0; loop<=m_diveData.GetUpperBound(); loop++ )
		{
			CDiveData* pData = (CDiveData*)m_diveData.GetAt( loop );
			pData->Serialize( ar );
		}
	}
	else
	{
		WORD wTmp;
		ar >> m_date;
		ar >> wTmp;
		for( int loop=0; loop<=(int)wTmp; loop++ )
		{
			CDiveData* pData = new CDiveData;
			pData->Serialize( ar );	m_diveData.Add( pData );
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// CDiveData

IMPLEMENT_DYNCREATE( CDiveData, CObject )

CDiveData::CDiveData()
{
	CTime date = CTime::GetCurrentTime();
	m_date = CTime( date.GetYear(), date.GetMonth(), date.GetDay(), 0, 0, 0 );
	SetLoc( "" );
	SetVis( CDiveData::Good );	SetVisDist( (float)0 );	SetVisFt( TRUE );
	SetAirStart( 0 );	SetAirEnd( 0 );	SetAirPSI( FALSE );	
	SetTimeIn( CTime( 1970, 1, 1, 0, 0, 0 ) );
	SetTimeOut( CTime( 1970, 1, 1, 0, 0, 0 ) );
	SetAirTemp( CDiveData::Warm );	SetSurfaceTemp( CDiveData::Warm );	SetBottomTemp( CDiveData::Warm );
	SetSurfaceInt( CTime( 1970, 1, 1, 0, 0, 0 ) );
	SetDepth( (float)0 );		SetDepthMts( TRUE );
	SetBottomTime( 0 );	SetDecompStop( 0 );
	m_btDiveType = m_btExpPro = 0;
	m_btCostume = 0;
	SetWeight( 0 );	SetWeightKG( FALSE );
	SetNotes( "" );	SetSurfaceInt( CTime( 1970, 1, 1, 0, 0, 0 ) );
	SetLastPG( 'A' );	SetSI( CTime( 1970, 1, 1, 0, 0, 0 ) );
	SetPGBeforeDive( "A" );
	SetDepthMts( TRUE );	SetBottomTime( 0 );
	SetDecompStop( 0 );	SetPGAfterDive( "A" );
	SetABTtoDate( CTime( 1970, 1, 1, 0, 0, 0 ) );	SetABTDive( CTime( 1970, 1, 1, 0, 0, 0 ) );
	SetRNT( 0 );	SetABT( 0 );	SetTBT( 0 );
}
	
CDiveData::~CDiveData()
{

}

void CDiveData::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
		ar << (WORD)GetDiveNo();		ar << GetDate();			ar << GetLoc();
		ar << (WORD)GetVis();			ar << (BYTE)GetVisFt();		ar << GetVisDist();
		ar << (WORD)GetAirStart();		ar << (WORD)GetAirEnd();	ar << (BYTE)GetAirPSI();
		ar << GetTimeIn();				ar << GetTimeOut();			ar << (WORD)GetAirTemp();
		ar << (WORD)GetSurfaceTemp();	ar << (WORD)GetBottomTemp();
		ar << (BYTE)GetDiveType();		ar << (BYTE)GetExpPro();	ar << (BYTE)GetCostume();
		ar << (WORD)GetWeight();		ar << (BYTE)GetWeightKG();	ar << GetNotes();
		ar << (WORD)GetLastPG();		ar << GetSurfaceInt();
		ar << GetPGBeforeDive();		ar << GetDepth();			ar << (BYTE)GetDepthMts();
		ar << (WORD)GetBottomTime();	ar << (WORD)GetDecompStop();	ar << GetPGAfterDive();
		ar << GetABTtoDate();			ar << GetABTDive();				ar << (WORD)GetRNT();
		ar << (WORD)GetABT();			ar << (WORD)GetTBT();		
	}
	else
	{
		WORD wTmp;	CTime tmpTime;	CString tmpStr;	BYTE tmpBte;	float fTmp;
		ar >> wTmp;	SetDiveNo( wTmp );	ar >> tmpTime;	SetDate( tmpTime );	ar >> tmpStr;	SetLoc( tmpStr );
		ar >> wTmp;	SetVis( (VisStyle)wTmp );	ar >> tmpBte;	SetVisFt( (BOOL)tmpBte );
		ar >> fTmp;	SetVisDist( fTmp );	ar >> wTmp;	SetAirStart( wTmp );	ar >> wTmp;	SetAirEnd( wTmp );
		ar >> tmpBte;	SetAirPSI( (BOOL)tmpBte );	ar >> tmpTime;	SetTimeIn( tmpTime );
		ar >> tmpTime;	SetTimeOut( tmpTime );	ar >> wTmp;	SetAirTemp( (Temperature)wTmp );
		ar >> wTmp;	SetSurfaceTemp( (Temperature)wTmp );	ar >> wTmp;	SetBottomTemp( (Temperature)wTmp );
		ar >> tmpBte;	SetDiveType( tmpBte );		ar >> tmpBte;	SetExpPro( tmpBte );
		ar >> tmpBte;	SetCostume( (BOOL)tmpBte );
		ar >> wTmp;		SetWeight( wTmp );	ar >> tmpBte;	SetWeightKG( (BOOL)tmpBte );
		ar >> tmpStr;	SetNotes( tmpStr );	ar >> wTmp;		SetLastPG( wTmp );
		ar >> tmpTime;	SetSurfaceInt( tmpTime );	ar >> tmpStr; SetPGBeforeDive( tmpStr );
		ar >> fTmp;		SetDepth( fTmp );	ar >> tmpBte;	SetDepthMts( (BOOL)tmpBte );
		ar >> wTmp;		SetBottomTime( wTmp );	ar >> wTmp;	SetDecompStop( wTmp );
		ar >> tmpStr;	SetPGAfterDive( tmpStr );	ar >> tmpTime;	SetABTtoDate( tmpTime );
		ar >> tmpTime;	SetABTDive( tmpTime );	ar >> wTmp;	SetRNT( wTmp );
		ar >> wTmp;	SetABT( wTmp );	ar >> wTmp;	SetTBT( wTmp );
	}
}

void CDiveData::SerializeVer1( CArchive& ar, CDiveSet* pSet )
{
	if (ar.IsStoring())
	{	}
	else
	{
		WORD wTmp;	CTime tmpTime;	CString tmpStr;	float fTmp;
		ar >> wTmp;	SetDiveNo( wTmp );		ar >> tmpTime;	SetDate( tmpTime );
		ar >> tmpStr;	SetLoc( tmpStr );
		ar >> wTmp;	SetVis( (VisStyle)wTmp );	ar >> wTmp;	SetVisDist( (float)wTmp );	ar >> wTmp;	SetVisFt( (BOOL)wTmp );
		ar >> wTmp;	SetAirStart( wTmp );		ar >> wTmp;	SetAirPSI( (BOOL)wTmp );	ar >> wTmp;	SetAirEnd( wTmp );
		ar >> wTmp;
		ar >> tmpTime;	SetTimeIn( tmpTime );	ar >> tmpTime;	SetTimeOut( tmpTime );
		ar >> wTmp;	SetAirTemp( (Temperature)wTmp );	ar >> wTmp;	SetSurfaceTemp( (Temperature)wTmp );
		ar >> wTmp;	SetBottomTemp( (Temperature)wTmp );
		ar >> wTmp; SetFresh( (BOOL)wTmp );	ar >> wTmp; SetShore( (BOOL)wTmp );	ar >> wTmp; SetWaves( (BOOL)wTmp );
		ar >> wTmp; SetSurf( (BOOL)wTmp );	ar >> wTmp; SetSalt( (BOOL)wTmp );	ar >> wTmp; SetBoat( (BOOL)wTmp );
		ar >> wTmp; SetCurrent( (BOOL)wTmp );	ar >> wTmp; SetSurge( (BOOL)wTmp );	ar >> wTmp;	SetWeight( wTmp );
        ar >> wTmp;	SetWeightKG( (BOOL)wTmp );	ar >> wTmp; SetCostume( (BOOL)wTmp );	ar >> wTmp; SetWetSuit( (BOOL)wTmp );
		ar >> wTmp; SetUSuit( (BOOL)wTmp );		ar >> wTmp; SetSDrySuit( (BOOL)wTmp );	ar >> wTmp; SetDrySuit( (BOOL)wTmp );
		ar >> wTmp; SetGloves( (BOOL)wTmp );	ar >> wTmp; SetMittens( (BOOL)wTmp );	ar >> wTmp; SetHood( (BOOL)wTmp );
		ar >> wTmp; SetSocks( (BOOL)wTmp );
		ar >> tmpTime;	SetSurfaceInt( tmpTime );	ar >> tmpStr;	SetPGAfterDive( tmpStr );
		ar >> fTmp;	SetDepth( fTmp );	ar >> wTmp;	SetBottomTime( wTmp );	ar >> wTmp;	SetDecompStop( wTmp );
		ar >> tmpStr;	SetPGBeforeDive( tmpStr );	ar >> tmpStr;	SetNotes( tmpStr );
		ar >> tmpTime;	SetABTtoDate( tmpTime );	ar >> tmpTime;	SetABTDive( tmpTime );
		ar >> tmpTime;	pSet->SetTotalABT( tmpTime );	ar >> wTmp;	SetRNT( wTmp );
		ar >> wTmp;	SetABT( wTmp );		ar >> wTmp;	SetTBT( wTmp );
		ar >> wTmp;	SetLastPG( wTmp );
		SetDepthMts( TRUE );
	}
}

//CDiveData& CDiveData::operator=( CDiveData* pData )
CDiveData& CDiveData::TransInfo( CDiveData* pData )
{
	m_nDiveNo		= 0; //pData->m_nDiveNo;
	m_date			= pData->m_date;
	m_location		= pData->m_location;
	m_visibility	= pData->m_visibility;
	m_visDist		= pData->m_visDist;
	m_btVisFeet		= pData->m_btVisFeet;
	m_nAirStart		= 0;	// pData->m_nAirStart;
	m_nAirEnd		= 0;	// pData->m_nAirEnd;
	m_btAirPSI		= pData->m_btAirPSI;
	m_timeIn		= pData->m_timeOut + CTimeSpan( 0, 0, 1, 0 );
	m_timeOut		= pData->m_timeOut + CTimeSpan( 0, 0, 1, 0 );
	m_air			= pData->m_air;		
	m_surface		= pData->m_surface;		
	m_bottom		= pData->m_bottom;
	m_btDiveType	= pData->m_btDiveType;
	m_btExpPro		= pData->m_btExpPro;
	//m_btCostume		= pData->m_btCostume;
	m_nWeight		= pData->m_nWeight;
	m_btKG			= pData->m_btKG;		
	//m_notes			= pData->m_notes;			
	//m_nLstPG		= pData->m_nLstPG;	
	//m_surfaceInt	= pData->m_surfaceInt;
	//m_PGBeforeDive	= pData->m_PGBeforeDive;
	//m_depth			= pData->m_depth;		
	m_btDepthMts	= pData->m_btDepthMts;	
	//m_nBottomTime	= pData->m_nBottomTime;
	//m_nStop			= pData->m_nStop;			
	//m_PGAfterDive	= pData->m_PGAfterDive;	
	m_ABTtoDate		= 0;	// Only used in V1	// pData->m_ABTtoDate;		
	m_ABTDive		= 0;	// Only used in V1	// pData->m_ABTDive;		
	m_nRNT			= 0;	// Only used in V1	// pData->m_nRNT;			
	m_nABT			= 0;	// Only used in V1	// pData->m_nABT;		
	m_nTBT			= 0;	// Only used in V1	// pData->m_nTBT;

	return *this;
}
