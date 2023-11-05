// TABLES.CPP - implementation of the table classes

#include "stdafx.h"
#include "tables.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CDepth, CObject )

//////////////////////////////////////////////////////////////////////////
// CDepth

CDepth::CDepth()
{
	m_bData.RemoveAll();
}

CDepth::~CDepth()
{
	m_bData.RemoveAll();
}

int CDepth::Find( int nLength )
{
	if( nLength > (int)m_bData.GetAt( m_bData.GetUpperBound() ) )
		return 30;		// returning over 25 will tell the user the dive is too long
	
	int nLast;		
	for( int loop=0; loop<=m_bData.GetUpperBound(); loop++ )
	{
		if( m_bData.GetAt( loop ) >= (BYTE)nLength && m_bData.GetAt( loop ) != 0 )
		{
			nLast = loop;
			break;
		}
		else
			nLast = loop;
	}
	return loop;
}

void CDepth::AddLength( BYTE bLength )
{
	m_bData.Add( bLength );
}


IMPLEMENT_DYNCREATE( CTable1, CObject )

CTable1::CTable1()
{
	m_depths.RemoveAll();
}

CTable1::~CTable1()
{
	for( int loop=0; loop<=m_depths.GetUpperBound(); loop++ )
	{
		CDepth* pDepth = (CDepth*)m_depths.GetAt( loop );
		delete pDepth;
	}
	m_depths.RemoveAll();
}

BOOL CTable1::LoadTable( CArchive& ar )
{
	BYTE bData;
	
	for( int loop=0; loop<=11; loop++ )
	{
		CDepth* pDepth = new CDepth();
		BYTE bElements;
		ar >> (BYTE)bElements;
		for( int loop2=0; loop2<=bElements; loop2++ )
		{
			ar >> (BYTE)bData;
			pDepth->AddLength( bData );
		}
		m_depths.Add( pDepth );
	}
	
	return TRUE;	
}

int CTable1::FindMtrs( int nDepth, int nLength )
{
	ASSERT( nDepth <= 42 );
	
	while( TRUE )
	{
		if( nDepth != 10 && nDepth != 12 && nDepth != 14 && nDepth != 16 &&
				nDepth != 18 && nDepth != 20 && nDepth != 22 && nDepth != 25 &&
					nDepth != 30 && nDepth != 35 && nDepth != 40 && nDepth != 42 )
			nDepth++;  
		else
			break;
	}
	
	int nIndex = 0;
	
	switch( nDepth )
	{
		case 10:	nIndex = 0;	break;
		case 12:	nIndex = 1;	break;
		case 14:	nIndex = 2;	break;
		case 16:	nIndex = 3;	break;
		case 18:	nIndex = 4;	break;
		case 20:	nIndex = 5;	break;
		case 22:	nIndex = 6;	break;
		case 25:	nIndex = 7;	break;
		case 30:	nIndex = 8;	break;
		case 35:	nIndex = 9;	break;
		case 40:	nIndex = 10;	break;
		case 42:	nIndex = 11;	break;
	}
	
	CDepth* pDepth = (CDepth*)m_depths.GetAt( nIndex );
	return pDepth->Find( nLength );
}

int CTable1::FindFt( int nDepth, int nLength )
{
	ASSERT( nDepth <= 140 );
	
	while( TRUE )
	{
		if( nDepth != 35 && nDepth != 40 && nDepth != 50 && nDepth != 60 &&
				nDepth != 70 && nDepth != 80 && nDepth != 90 && nDepth != 100 &&
					nDepth != 110 && nDepth != 120 && nDepth != 130 && nDepth != 140 )
			nDepth++;  
		else
			break;
	}

	int nIndex = 0;
	
	switch( nDepth )
	{
		case 35:	nIndex = 0;	break;
		case 40:	nIndex = 1;	break;
		case 50:	nIndex = 2;	break;
		case 60:	nIndex = 3;	break;
		case 70:	nIndex = 4;	break;
		case 80:	nIndex = 5;	break;
		case 90:	nIndex = 6;	break;
		case 100:	nIndex = 7;	break;
		case 110:	nIndex = 8;	break;
		case 120:	nIndex = 9;	break;
		case 130:	nIndex = 10;	break;
		case 140:	nIndex = 11;	break;
	}
	
	CDepth* pDepth = (CDepth*)m_depths.GetAt( nIndex );
	return pDepth->Find( nLength );
}

//////////////////////////////////////////////////////////////////////////
// CSurfaceInt

IMPLEMENT_DYNCREATE( CSurfaceInt, CObject )

CSurfaceInt::CSurfaceInt()
{
	m_wData.RemoveAll();
}

CSurfaceInt::~CSurfaceInt()
{
	m_wData.RemoveAll();
}

int CSurfaceInt::Find( int nLength )
{
	// if the length is greater than the length of time in the table
	// then return pressure group A
	if( nLength >= (int)m_wData.GetAt( 0 ) )
		return 0;	// PG - A
	
	for( int loop=0; loop<=m_wData.GetUpperBound(); loop++ )
	{
		if( nLength > (int)m_wData.GetAt( loop ) )
			break;
	}
	loop--;
	return loop;
}

void CSurfaceInt::AddSI( int nSI )
{
	m_wData.Add( nSI );
}

//////////////////////////////////////////////////////////////////////////
// CTable2

IMPLEMENT_DYNCREATE( CTable2, CObject )

CTable2::CTable2()
{
	m_PG.RemoveAll();
}

CTable2::~CTable2()
{
	for( int loop=0; loop<=m_PG.GetUpperBound(); loop++ )
	{
		CSurfaceInt* pSI = (CSurfaceInt*)m_PG.GetAt( loop );
		delete pSI;
	}
	m_PG.RemoveAll();
}

BOOL CTable2::LoadTable( CArchive& ar )
{
	int nElements;
	WORD wTmp;
	
	for( int loop=0; loop<=25; loop++ )
	{
		CSurfaceInt* pSI = new CSurfaceInt();
		ar >> wTmp;	nElements = wTmp;
		for( int loop2=0; loop2<=nElements; loop2++ )
		{
			ar >> wTmp;
			pSI->AddSI( (int)wTmp );
		}
		m_PG.Add( pSI );
	}

	return TRUE;	
}

int CTable2::Find( int nPG, int nSI )
{
	ASSERT( nPG <= 25 );	// Makes sure PG is between A and Z
	CSurfaceInt* pSI = (CSurfaceInt*)m_PG.GetAt( nPG );
	return pSI->Find( nSI );
}

//////////////////////////////////////////////////////////////////////////
// CRNT_ABT

IMPLEMENT_DYNCREATE( CRNT_ABT, CObject )

CRNT_ABT::CRNT_ABT()
{
	m_RNT_ABT.RemoveAll();
}

CRNT_ABT::~CRNT_ABT()
{
	m_RNT_ABT.RemoveAll();
}

void CRNT_ABT::Add( BYTE bRNT, BYTE bABT )
{
	m_RNT_ABT.Add( Combine( bRNT, bABT ) );
}

void CRNT_ABT::Add( WORD wRNT_ABT )
{
	m_RNT_ABT.Add( wRNT_ABT );
}

int CRNT_ABT::GetRNT( const int nIndex )
{
	ASSERT( nIndex <= m_RNT_ABT.GetUpperBound() );
	return LOBYTE( m_RNT_ABT.GetAt( nIndex ) );
}

int CRNT_ABT::GetABT( const int nIndex )
{
	ASSERT( nIndex <= m_RNT_ABT.GetUpperBound() );
	return HIBYTE( m_RNT_ABT.GetAt( nIndex ) );
}


WORD CRNT_ABT::GetAt( const int nIndex )
{
	ASSERT( nIndex <= m_RNT_ABT.GetUpperBound() );
	return m_RNT_ABT.GetAt( nIndex );
}

//////////////////////////////////////////////////////////////////////////
// CTable3

IMPLEMENT_DYNCREATE( CTable3, CObject )

CTable3::CTable3()
{
	m_PG.RemoveAll();
}

CTable3::~CTable3()
{
	for( int loop=0; loop<=m_PG.GetUpperBound(); loop++ )
	{
		CRNT_ABT* pTmp = (CRNT_ABT*)m_PG.GetAt( loop );
		delete pTmp;
	}
	m_PG.RemoveAll();
}

BOOL CTable3::LoadTable( CArchive& ar )
{
	int nElements;
	BYTE bTmp;
	WORD wRNT_ABT;
	
	for( int loop=0; loop<=25; loop++ )
	{
		CRNT_ABT* pTmp = new CRNT_ABT();
		ar >> (BYTE)bTmp;	nElements = bTmp;
		for( int loop2=0; loop2<=nElements; loop2++ )
		{
			ar >> wRNT_ABT;
			pTmp->Add( wRNT_ABT );
		}
		m_PG.Add( pTmp );
	}

	return TRUE;	
}

WORD CTable3::FindMtrs( int nPG, int nDepth )
{
	CRNT_ABT* pTmp = (CRNT_ABT*)m_PG.GetAt( nPG );
	
	if( nDepth > 42 )
		return 0;
	
	while( TRUE )
	{
		if( nDepth==10 || nDepth==12 || nDepth==14 || nDepth==16 ||
				nDepth==18 || nDepth==20 || nDepth==22 || nDepth==25 ||
					nDepth==30 || nDepth==35 || nDepth==40 || nDepth==42 )
			break;
		nDepth++;
	}

	int nIndex;
	
	// Convert nDepth to a index
	switch( nDepth )
	{
		case 10:	nIndex = 0;	break;
		case 12:	nIndex = 1;	break;
		case 14:	nIndex = 2;	break;
		case 16:	nIndex = 3;	break;
		case 18:	nIndex = 4;	break;
		case 20:	nIndex = 5;	break;
		case 22:	nIndex = 6;	break;
		case 25:	nIndex = 7;	break;
		case 30:	nIndex = 8;	break;
		case 35:	nIndex = 9;	break;
		case 40:	nIndex = 10;	break;    
		case 42:	nIndex = 11;	break;
	}
	
	return pTmp->GetAt( nIndex );
}

WORD CTable3::FindFt( int nPG, int nDepth )
{
	CRNT_ABT* pTmp = (CRNT_ABT*)m_PG.GetAt( nPG );
	
	if( nDepth > 140 )
		return 0;
	
	while( TRUE )
	{
		if( nDepth != 35 && nDepth != 40 && nDepth != 50 && nDepth != 60 &&
				nDepth != 70 && nDepth != 80 && nDepth != 90 && nDepth != 100 &&
					nDepth != 110 && nDepth != 120 && nDepth != 130 && nDepth != 140 )
			nDepth++;  
		else
			break;
	}

	int nIndex = 0;
	
	// Convert nDepth to a index
	switch( nDepth )
	{
		case 35:	nIndex = 0;	break;
		case 40:	nIndex = 1;	break;
		case 50:	nIndex = 2;	break;
		case 60:	nIndex = 3;	break;
		case 70:	nIndex = 4;	break;
		case 80:	nIndex = 5;	break;
		case 90:	nIndex = 6;	break;
		case 100:	nIndex = 7;	break;
		case 110:	nIndex = 8;	break;
		case 120:	nIndex = 9;	break;
		case 130:	nIndex = 10;	break;
		case 140:	nIndex = 11;	break;
	}
	
	return pTmp->GetAt( nIndex );
}

