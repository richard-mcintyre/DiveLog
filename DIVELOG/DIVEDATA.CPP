// DIVEDATA.CPP - implementation of the CDiveData & CDiveSet classes

#include "stdafx.h"
#include "divedata.h"
#include "divedoc.h"
#include "tables.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CDiveData

IMPLEMENT_DYNCREATE( CDiveData, CObject )

CDiveData::CDiveData()
{
	m_nDiveNo = 1;
	m_date = CTime( CTime::GetCurrentTime().GetYear(),
						CTime::GetCurrentTime().GetMonth(),
							CTime::GetCurrentTime().GetDay(), 0, 0, 0 );
	m_location = "";
	m_nAirStart	=	0;	m_bPSIStart	=	FALSE;	m_nAirEnd	=	0;	m_bPSIEnd	=	FALSE;
	m_timeIn = CTime( 1970, 1, 1, 0, 0, 0 );	m_timeOut = CTime( 1970, 1, 1, 0, 0, 0 );
	
	m_air = CDiveData::Warm;	m_surface = CDiveData::Warm;	m_bottom = CDiveData::Warm;

	m_Visibility = Good;	m_VisDist = 0;	m_bVisFeet = TRUE;
	m_bFresh = FALSE;	m_bShore = FALSE;	m_bWaves = FALSE;	m_bSurf = FALSE;	m_bSalt = FALSE;
	m_bBoat = FALSE;	m_bCurrent = FALSE;	m_bSurge = FALSE;
	m_nWeight = 0;		m_bKG = FALSE;
	m_bSwimmingCost = FALSE;	m_bWetSuit = FALSE;	m_bUnderSuit = FALSE;	m_bSemiDrySuit = FALSE;
	m_bDrySuit = FALSE;	m_bGloves = FALSE;	m_bMittens = FALSE;	m_bHood = FALSE;	m_bSocks = FALSE;
	m_surfaceInt = CTime( 1970, 1, 1, 0, 0, 0 );		m_PGBeforeDive = "A";
	m_nBottomTime = 0;	m_nDepth = 0;	m_nStop = 0;	m_PGAfterDive = "A";
	m_comments = "";	m_ABTtoDate = CTime( 1970, 1, 1, 0, 0, 0 );
	m_ABTDive = CTime( 1970, 1, 1, 0, 0, 0 );		// ABT this dive
	m_nRNT = m_nABT = m_nTBT = m_nLastDivePG = 0;
}

CDiveData::~CDiveData()
{	}

void CDiveData::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)m_nDiveNo;		ar << m_date;
		ar << m_location;			ar << (WORD)m_Visibility;
		ar << (WORD)m_VisDist;		ar << (WORD)m_bVisFeet;
		ar << (WORD)m_nAirStart;	ar << (WORD)m_bPSIStart;
		ar << (WORD)m_nAirEnd;		ar << (WORD)m_bPSIEnd;
		ar << m_timeIn;				ar << m_timeOut;
		ar << (WORD)m_air;			ar << (WORD)m_surface;
		ar << (WORD)m_bottom;		ar << (WORD)m_bFresh;
		ar << (WORD)m_bShore;		ar << (WORD)m_bWaves;
		ar << (WORD)m_bSurf;		ar << (WORD)m_bSalt;
		ar << (WORD)m_bBoat;		ar << (WORD)m_bCurrent;
		ar << (WORD)m_bSurge;		ar << (WORD)m_nWeight;
		ar << (WORD)m_bKG;			ar << (WORD)m_bSwimmingCost;
		ar << (WORD)m_bWetSuit;		ar << (WORD)m_bUnderSuit;
		ar << (WORD)m_bSemiDrySuit;	ar << (WORD)m_bDrySuit;
		ar << (WORD)m_bGloves;		ar << (WORD)m_bMittens;
		ar << (WORD)m_bHood;		ar << (WORD)m_bSocks;
    	ar << m_surfaceInt;			ar << m_PGBeforeDive;
		ar << m_nDepth;				ar << (WORD)m_nBottomTime;
		ar << (WORD)m_nStop;		ar << m_PGAfterDive;
		ar << m_comments;			ar << m_ABTtoDate;
		ar << m_ABTDive;			ar << m_pDiveSet->m_totalABT; 
		ar << (WORD)m_nRNT;			ar << (WORD)m_nABT;
		ar << (WORD)m_nTBT;			ar << (WORD)m_nLastDivePG;
	}
	else
	{
		WORD wTmp;
		ar >> wTmp;	m_nDiveNo = wTmp;		ar >> m_date;
		ar >> m_location;					ar >> wTmp;	m_Visibility = (VisStyle)wTmp;
		ar >> wTmp;	m_VisDist = wTmp;		ar >> wTmp;	m_bVisFeet = wTmp;
		ar >> wTmp;	m_nAirStart = wTmp;		ar >> wTmp;	m_bPSIStart = wTmp;
		ar >> wTmp;	m_nAirEnd = wTmp;		ar >> wTmp;	m_bPSIEnd = wTmp;
		ar >> m_timeIn;						ar >> m_timeOut;
		ar >> wTmp;	m_air = (Temperature)wTmp;
		ar >> wTmp;	m_surface = (Temperature)wTmp;
		ar >> wTmp;	m_bottom = (Temperature)wTmp;
		ar >> wTmp;	m_bFresh = wTmp;		ar >> wTmp;	m_bShore = wTmp;
		ar >> wTmp;	m_bWaves = wTmp;		ar >> wTmp;	m_bSurf = wTmp;
		ar >> wTmp;	m_bSalt = wTmp;			ar >> wTmp;	m_bBoat = wTmp;
		ar >> wTmp;	m_bCurrent = wTmp;		ar >> wTmp;	m_bSurge = wTmp;
		ar >> wTmp;	m_nWeight = wTmp;		ar >> wTmp;	m_bKG = wTmp;
		ar >> wTmp;	m_bSwimmingCost = wTmp;	ar >> wTmp;	m_bWetSuit = wTmp;
		ar >> wTmp;	m_bUnderSuit = wTmp;	ar >> wTmp;	m_bSemiDrySuit = wTmp;
		ar >> wTmp;	m_bDrySuit = wTmp;		ar >> wTmp;	m_bGloves = wTmp;
		ar >> wTmp;	m_bMittens = wTmp;		ar >> wTmp;	m_bHood = wTmp;
		ar >> wTmp;	m_bSocks = wTmp;    	ar >> m_surfaceInt;
		ar >> m_PGBeforeDive;				ar >> m_nDepth;
		ar >> wTmp;	m_nBottomTime = wTmp;	ar >> wTmp;	m_nStop = wTmp;
		ar >> m_PGAfterDive;				ar >> m_comments;
		ar >> m_ABTtoDate;					ar >> m_ABTDive;
		ar >> m_pDiveSet->m_totalABT; 		ar >> wTmp;	m_nRNT = wTmp;
		ar >> wTmp;	m_nABT = wTmp;			ar >> wTmp;	m_nTBT = wTmp;
		ar >> wTmp;	m_nLastDivePG = wTmp;
	}
}

void CDiveData::TransferInfo( CDiveData* pData )
{
	m_nDiveNo	=	pData->m_nDiveNo + 1;
//	m_date		=	pData->m_date;
	m_location	=	pData->m_location;
	m_Visibility	=	pData->m_Visibility;
	m_VisDist	=	pData->m_VisDist;
	m_bVisFeet	=	pData->m_bVisFeet;
//	m_nAirStart	=	pData->m_nAirStart;
//	m_bPSIStart	=	pData->m_bPSIStart;
//	m_nAirEnd	=	pData->m_nAirEnd;
//	m_bPSIEnd	=	pData->m_bPSIEnd;
//	m_timeIn	=	pData->m_timeOut + CTimeSpan( 0, 0, 1, 0 );
//	m_timeOut	=	pData->m_timeOut + CTimeSpan( 0, 0, 1, 0 );
	m_air		=	pData->m_air;
	m_surface	=	pData->m_surface;
	m_bottom	=	pData->m_bottom;
	m_bFresh	=	pData->m_bFresh;
	m_bShore	=	pData->m_bShore;
	m_bWaves	=	pData->m_bWaves;
	m_bSurf		=	pData->m_bSurf;
	m_bSalt		=	pData->m_bSalt;
	m_bBoat		=	pData->m_bBoat;
	m_bCurrent	=	pData->m_bCurrent;
	m_bSurge	=	pData->m_bSurge;
	m_nWeight	=	pData->m_nWeight;
	m_bKG		=	pData->m_bKG;
	m_bSwimmingCost	=	pData->m_bSwimmingCost;
	m_bWetSuit		=	pData->m_bWetSuit;
	m_bUnderSuit	=	pData->m_bUnderSuit;
	m_bSemiDrySuit	=	pData->m_bSemiDrySuit;
	m_bDrySuit	=	pData->m_bDrySuit;
	m_bGloves	=	pData->m_bGloves;
	m_bMittens	=	pData->m_bMittens;
	m_bHood		=	pData->m_bHood;
	m_bSocks	=	pData->m_bSocks;
	m_surfaceInt	=	CTime( 1970, 1, 1, 0, 0, 0 );
	m_PGBeforeDive	=	pData->m_PGAfterDive;
	m_nDepth		=	0;
	m_nBottomTime	=	0;
	m_nStop			=	0;
	m_PGAfterDive	=	pData->m_PGAfterDive;
//	m_comments	=	pData->m_comments;
	m_ABTtoDate	=	m_pDiveSet->m_totalABT;
	m_ABTDive	=	CTime( 1970, 1, 1, 0, 0, 0 );
	m_nRNT		=	pData->m_nRNT;
	m_nABT		=	pData->m_nABT;
	m_nTBT		=	pData->m_nTBT;
	m_nLastDivePG = ((const char)pData->m_PGAfterDive.GetAt( 0 )) - 'A';
	
	m_pDiveSet->DateChange( m_date );
}

//////////////////////////////////////////////////////////////////////////
// CDiveSet

IMPLEMENT_SERIAL( CDiveSet, CObject, 1 )    

CDiveSet::CDiveSet()
{
	m_fileVersion = 0x01;	// Version 1
	m_totalABT = CTime( 1970, 1, 1, 0, 0, 0 );
}

CDiveSet::CDiveSet( CDiveDoc* pDoc )
{
	m_fileVersion = 0x01;	// Version 1
	m_totalABT = CTime( 1970, 1, 1, 0, 0, 0 );
	m_nCurIndex = -1;
	m_pDoc = pDoc;
}

CDiveSet::~CDiveSet()
{
	RemoveAll();
}

CDiveData* CDiveSet::GetRecord( int nIndex ) const
{	return (CDiveData*)m_data.GetAt( nIndex );	}

CDiveData* CDiveSet::GetCurRecord() const
{	return (CDiveData*)m_data.GetAt( m_nCurIndex );	}

void CDiveSet::SetCurRecord( CDiveData* pData )
{
	delete m_data.GetAt( m_nCurIndex );
	pData->m_pDiveSet = this;
	m_data.SetAt( m_nCurIndex, pData );
}

void CDiveSet::Add( CDiveData* pData )
{
	m_nCurIndex = m_data.Add( pData );
	pData->m_pDiveSet = this;
}

void CDiveSet::Delete()
{
	CDiveData* pData = (CDiveData*)m_data.GetAt( m_nCurIndex );
	m_totalABT -= CTimeSpan( 0, 0, pData->m_nBottomTime, 0 );
	delete pData;
	m_data.RemoveAt( m_nCurIndex );
	m_nCurIndex = 0;
}

void CDiveSet::FirstRecord()
{	m_nCurIndex = 0;	}

void CDiveSet::LastRecord()
{	m_nCurIndex = m_data.GetUpperBound();	}

void CDiveSet::PrevRecord()
{
	if( m_nCurIndex == 0 )
		return;
	m_nCurIndex--;
}

void CDiveSet::NextRecord()
{
	if( m_nCurIndex == m_data.GetUpperBound() )
		return;
	m_nCurIndex++;
}

int CDiveSet::GetCurIndex() const
{	return m_nCurIndex;	}

int CDiveSet::GetNoOfRecs() const
{	return m_data.GetUpperBound();	};

void CDiveSet::RemoveAll()
{
	for( int loop=0; loop<=m_data.GetUpperBound(); loop++ )
	{
		CDiveData* pData = (CDiveData*)m_data.GetAt( loop );
		delete pData;
	}
	m_data.RemoveAll();
}

void CDiveSet::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)m_data.GetUpperBound();
		for( int loop=0; loop<=m_data.GetUpperBound(); loop++ )
		{
			CDiveData* pData = (CDiveData*)m_data.GetAt( loop );
			pData->Serialize( ar );
		}
	}
	else
	{
		RemoveAll();	// Clear current records
		WORD wTmp;
		ar >> wTmp;
		for( int loop=0; loop<=(int)wTmp; loop++ )
		{
			CDiveData* pData = new CDiveData();
			pData->m_pDiveSet = this;
			pData->Serialize( ar );
			m_data.Add( pData );
		}		
	}
}


void CDiveSet::DateChange( CTime prevDate )
{
	// The date or time fields have changed
	if( m_data.GetSize()==1 )
		return;	// Only one record
		
	CDiveData* pTmpData;
	CDiveData* pCurDive = (CDiveData*)m_data.GetAt( m_nCurIndex );
	m_data.RemoveAt( m_nCurIndex );
	
	if( pCurDive->m_date < ((CDiveData*)m_data.GetAt( 0 ))->m_date )
	{
		m_data.InsertAt( 0, pCurDive );
		m_nCurIndex = 0;
		ChangeDiveNos( 0 );
		RecalcDiveInfo();
		return;
	}
	
	for( int loop=0; loop<=m_data.GetUpperBound(); loop++ )
	{
		pTmpData = (CDiveData*)m_data.GetAt( loop );
		if( pTmpData->m_date > pCurDive->m_date )
			break;
	}
	    
	m_data.InsertAt( loop, pCurDive );
	m_nCurIndex = loop;
	ChangeDiveNos( 0 );
	RecalcDiveInfo();
}

void CDiveSet::ChangeDiveNos( int nStartIndex )
{
	ASSERT( nStartIndex <= m_data.GetUpperBound() );
	
	int nDiveNum = 1;
	
	CTime	lastDate = CTime( 1970, 1, 1, 0, 0, 0 );
	CDiveData* pDiveData = (CDiveData*)m_data.GetAt( 0 );
		
	for( int loop=0; loop<=m_data.GetUpperBound(); loop++ )
	{
		CDiveData* pData = (CDiveData*)m_data.GetAt( loop );
		if( pData->m_date == lastDate )
		{
			pData->m_nDiveNo = nDiveNum;
		}
		else
		{
			nDiveNum = 1;
			pData->m_nDiveNo = nDiveNum;
		}
		nDiveNum++;
		lastDate = pData->m_date;
	}	
}

void CDiveSet::RecalcDiveInfo()
{
	int nLastDive = 0;
	int lastPG;
	CTimeSpan	ABTtoDate( 0, 0, 0, 0 );
	
	for( int loop=0; loop<=GetNoOfRecs(); loop++ )
	{
		CDiveData* pData = (CDiveData*)GetRecord( loop );
		
		int nDepth;
		float remainder = pData->m_nDepth - (int)pData->m_nDepth;
		if( remainder > 0 )
		{
			nDepth = (int)pData->m_nDepth;
			nDepth++;	// force rounding up
		}
		else
			nDepth = (int)pData->m_nDepth;
			
		// if the surface or bottom temp is cold then at 4m depth
		if( pData->m_surface == CDiveData::Cold || pData->m_bottom == CDiveData::Cold )
			nDepth += 4;

		if( pData->m_nDiveNo == 1 )
		{
			pData->m_nLastDivePG = 0;
			pData->m_PGBeforeDive = "A";
			
			int nPG = m_pDoc->m_pTable1->Find( nDepth, pData->m_nBottomTime );
			if( nPG > 25 )
				nPG = '?' - 'A';

			int nOffset = 'A';	char PG = nOffset + nPG;
			pData->m_PGAfterDive = PG;
			pData->m_nRNT = pData->m_nABT = pData->m_nTBT = 0;
			if( nPG == '?' - 'A' )
			{
				int nBottom = pData->m_nBottomTime;
				nPG = 999;	// Must be > 25 for the next loop to take effect
				while( nPG > 25 )
				{
					nBottom--;
					nPG = m_pDoc->m_pTable1->Find( nDepth, nBottom );
				}
			}
			lastPG = nPG;
		}
		else
		{
			// Calculate the pressure group for the other dives
			pData->m_nLastDivePG = lastPG;
			CString si = pData->m_surfaceInt.Format( "%H%M" );
			const char* pszSI = si;
			int nSI = (int)strtol( pszSI, (char**)&pszSI, 10 );
			int nPG = m_pDoc->m_pTable2->Find( lastPG, nSI );
			int nOffset = 'A';	char PG = nOffset + nPG;
			pData->m_PGBeforeDive = PG;
			
			
			CPoint tmpPt = m_pDoc->m_pTable3->Find( nPG, nDepth );
			if( tmpPt == CPoint( 999, 999 ) )
			{
				AfxMessageBox( "Depth to deep!" );
				tmpPt = CPoint( 0, 0 );
			}
			int nRNT = tmpPt.x;
			int nANDL = tmpPt.y;
							       
			// The ABT should not be greater than the ANDL
			if( pData->m_nBottomTime > nANDL )
				nPG = '?' - 'A';
			
			pData->m_nRNT = tmpPt.x;
			pData->m_nABT = pData->m_nBottomTime;
			pData->m_nTBT = pData->m_nRNT + pData->m_nABT;
				
			
			if( nPG == '?' - 'A' )
			{
				int nBottom = pData->m_nTBT; // m_nBottomTime;
				nPG = 999;	// Must be > 25 for the next loop to take effect
				while( nPG > 25 )
				{
					nBottom--;
					nPG = m_pDoc->m_pTable1->Find( nDepth, nBottom );
				}
				lastPG = nPG;
				pData->m_PGAfterDive = '?';
			}
			else
            {
				lastPG = nPG;
				// Now calculate the pressure group at the end of the dive using TBT
				nPG = m_pDoc->m_pTable1->Find( nDepth, pData->m_nTBT );
				pData->m_PGAfterDive = nOffset + nPG;
			}
		}
		pData->m_ABTtoDate = CTime( 1970, 1, 1, ABTtoDate.GetHours(), ABTtoDate.GetMinutes(), 0 );
		int nHours = pData->m_nBottomTime / 60;
		int nMins = pData->m_nBottomTime - (nHours * 60);
		pData->m_ABTtoDate += CTimeSpan( 0, nHours, nMins, 0 );
		pData->m_ABTDive = CTime( 1970, 1, 1, nHours, nMins, 0 );
		ABTtoDate = CTimeSpan( 0, pData->m_ABTtoDate.GetHour(), pData->m_ABTtoDate.GetMinute(), 0 );
	}
}

