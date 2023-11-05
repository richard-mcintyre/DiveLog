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
	m_wData.RemoveAll();
}

CDepth::~CDepth()
{
	m_wData.RemoveAll();
}

int CDepth::Find( int nLength )
{
	if( nLength > (int)m_wData.GetAt( m_wData.GetUpperBound() ) )
	{
		int nTmp = 30;	// returning over 25 will tell the user the dive is too long
		return nTmp;
	}
	
	int nLast;		
	for( int loop=0; loop<=m_wData.GetUpperBound(); loop++ )
	{
		if( m_wData.GetAt( loop ) >= (WORD)nLength && m_wData.GetAt( loop ) != 10000 )
		{
			nLast = loop;
			break;
		}
		else
			nLast = loop;
	}
	return loop;
}

void CDepth::AddLength( int nLength )
{
	m_wData.Add( (WORD)nLength );
}

//////////////////////////////////////////////////////////////////////////
// CTable1

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

BOOL CTable1::LoadTable()
{
	CFile table1File;
		
	if( !table1File.Open( "TABLE1.DAT",	CFile::modeRead ) )
		return FALSE;	// problem opening file
	
	CArchive ar( &table1File, CArchive::load );
	
	int nElements;
	WORD wTmp;
	
	for( int loop=0; loop<=11; loop++ )
	{
		CDepth* pDepth = new CDepth();
		ar >> wTmp;	nElements = wTmp;
		for( int loop2=0; loop2<=nElements; loop2++ )
		{
			ar >> wTmp;
			pDepth->AddLength( (int)wTmp );
		}
		ar >> wTmp;	// not used
		m_depths.Add( pDepth );
	}
	
	ar.Close();
	table1File.Close();

	return TRUE;	
}

int CTable1::Find( int nDepth, int nLength )
{
	if( nDepth > 42 )	nDepth = 42;
	
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

BOOL CTable2::LoadTable()
{
	CFile table2File;
		
	if( !table2File.Open( "TABLE2.DAT",	CFile::modeRead ) )
		return FALSE;	// problem opening file
	
	CArchive ar( &table2File, CArchive::load );
	
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

	ar.Close();
	table2File.Close();

	return TRUE;	
}

int CTable2::Find( int nPG, int nSI )
{
	ASSERT( nPG < 26 );	// Makes sure PG is between A and Z
	CSurfaceInt* pSI = (CSurfaceInt*)m_PG.GetAt( nPG );
	return pSI->Find( nSI );
}

//////////////////////////////////////////////////////////////////////////
// CRNT_ABT

IMPLEMENT_DYNCREATE( CRNT_ABT, CObject )

CRNT_ABT::CRNT_ABT()
{
	m_RNT.RemoveAll();
	m_ABT.RemoveAll();
}

CRNT_ABT::~CRNT_ABT()
{
	m_RNT.RemoveAll();
	m_ABT.RemoveAll();
}

void CRNT_ABT::Add( int nRNT, int nABT )
{
	m_RNT.Add( nRNT );
	m_ABT.Add( nABT );
}

int CRNT_ABT::GetRNT( int nIndex )
{
	if( nIndex > m_RNT.GetUpperBound() )
		return 999;
	return m_RNT.GetAt( nIndex );
}

int CRNT_ABT::GetABT( int nIndex )
{
	if( nIndex > m_ABT.GetUpperBound() )
		return 999;
	return m_ABT.GetAt( nIndex );
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

BOOL CTable3::LoadTable()
{
	CFile table3File;
		
	if( !table3File.Open( "TABLE3.DAT",	CFile::modeRead ) )
		return FALSE;	// problem opening file
	
	CArchive ar( &table3File, CArchive::load );
	
	int nElements;
	WORD wTmp, wRNT, wABT;
	
	for( int loop=0; loop<=25; loop++ )
	{
		CRNT_ABT* pTmp = new CRNT_ABT();
		ar >> wTmp;	nElements = wTmp;
		for( int loop2=0; loop2<=nElements; loop2++ )
		{
			ar >> wRNT;	ar >> wABT;
			pTmp->Add( (int)wRNT, (int)wABT );
		}
		m_PG.Add( pTmp );
	}
	
	ar.Close();
	table3File.Close();

	return TRUE;	
}

CPoint CTable3::Find( int nPG, int nDepth )
{
	CRNT_ABT* pTmp = (CRNT_ABT*)m_PG.GetAt( nPG );
	
	if( nDepth > 40 )
		return CPoint( 0, 0 );
	
	while( TRUE )
	{
		if( nDepth==10 || nDepth==12 || nDepth==14 || nDepth==16 ||
				nDepth==18 || nDepth==20 || nDepth==22 || nDepth==25 ||
					nDepth==30 || nDepth==35 || nDepth==40 )
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
	}
	
	return CPoint( pTmp->GetRNT( nIndex ), pTmp->GetABT( nIndex ) );
}

