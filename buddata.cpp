// buddata.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "buddata.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////
// CBudSet

IMPLEMENT_DYNCREATE( CBudSet, CObject )

CBudSet::CBudSet( )
{
	for( int i=0; i<=26; i++ )
		m_access.Add( 0 );
}

CBudSet::~CBudSet()
{
	for( int loop=0; loop<=m_recs.GetUpperBound(); loop++ )
	{
		CBudData* pData = (CBudData*)m_recs.GetAt( loop );
		delete pData;
	}
}

int CBudSet::AddRec( CBudData* pData )
{
	ASSERT_VALID( pData );

	IncAccess( pData->GetLastName() );
    
    BOOL bAdded = FALSE;
    for( int i=0; i<=m_recs.GetUpperBound(); i++ )
    {
    	CBudData* pBudData = (CBudData*)m_recs.GetAt( i );
    	if( pBudData->GetLastName() >= pData->GetLastName() )
    	{
    		m_recs.InsertAt( i, pData );
    		bAdded = TRUE;
    		break;
    	}
    }
    
    if( !bAdded )
        return m_recs.Add( pData );
    else
    	return i;
    
        
    
    /*
	int nIndex = 0;	int nPlaceA=-1;
	BOOL bResult = FALSE;
	for( int i=0; i<=m_recs.GetUpperBound(); i++ )
	{
		CBudData* pBudData = (CBudData*)m_recs.GetAt( i );
		CString scr = pBudData->GetLastName();
		CString dest = pData->GetLastName();
		CString str = scr.Left( 1 );
		CString str2 = dest.Left( 1 );
		str.MakeUpper( );	str2.MakeUpper( );
		if( str2 >= "A" && str2 <= "Z" )
		{
			if( scr >= dest )
			{
				nIndex = i;
				char buf[20];
				wsprintf( buf, "nIndex = %d", nIndex );
				AfxMessageBox( buf );
				bResult = TRUE;
				break;
			}
			
		}
		else
		{
			if( scr >= "A" )
			{
				nIndex = i;
				break;
			}
			else if( scr > dest )
			{
				nIndex = i;
				break;
			}
		}
	}

	if( bResult )
	{
		m_recs.InsertAt( i, pData );
		char buf[20];
		wsprintf( buf, "if 1 i = %d", i );
		AfxMessageBox( buf );
	}
	else
	{
		m_recs.InsertAt( (nPlaceA==-1) ? 0 : nPlaceA, pData );
		char buf[20];
		wsprintf( buf, "if 2 i = %d", i );
		AfxMessageBox( buf );
    }
    
	return nIndex;*/
}

int CBudSet::FindBud( CString let, CBudData** pData )
{
	let = let.Left( 1 );	let.MakeUpper();

	int nIndex = 0;	int nPlaceA=-1;
	BOOL bResult = FALSE;
	for( int i=0; i<=m_recs.GetUpperBound(); i++ )
	{
		CBudData* pBudData = (CBudData*)m_recs.GetAt( i );
		CString scr = pBudData->GetLastName();
		CString str = scr.Left( 1 );
		str.MakeUpper( );
		if( scr > let )
		{
			nIndex = i;
			bResult = TRUE;
			break;
		}
		else if( str == "A" && nPlaceA != -1 )
			nPlaceA = i;
	}

	if( !bResult )
		i = (nPlaceA==-1) ? 0 : nPlaceA; 

	*pData = (CBudData*)m_recs.GetAt( i );
	return i;
}

void CBudSet::LastNameChanged( CString strOld, CString strNew, int& nIndex )
{
	DeIncAccess( strOld );

	CBudData* pData = (CBudData*)m_recs.GetAt( nIndex );
	m_recs.RemoveAt( nIndex );

	nIndex = AddRec( pData );
}

int CBudSet::RemoveRec( const int nIndex )
{	   
	ASSERT( nIndex <= m_recs.GetUpperBound() );

	CBudData* pData = (CBudData*)m_recs.GetAt( nIndex );
	DeIncAccess( pData->GetLastName() );
	m_recs.RemoveAt( nIndex );
	delete pData;
	return m_recs.GetUpperBound();
}
					
int CBudSet::BudPrev( int nIndex, CBudData** pData )
{
	ASSERT( nIndex >=0 && nIndex <= m_recs.GetUpperBound() );

	nIndex = ( nIndex == 0 ) ? 0 : nIndex - 1;

	*pData = (CBudData*)m_recs.GetAt( nIndex );
	return nIndex;
}

int CBudSet::BudNext( int nIndex, CBudData** pData )
{
	ASSERT( nIndex >=0 && nIndex <= m_recs.GetUpperBound() );

	nIndex = ( nIndex == m_recs.GetUpperBound() ) ? m_recs.GetUpperBound() : nIndex + 1;

	*pData = (CBudData*)m_recs.GetAt( nIndex );
	return nIndex;
}	

int CBudSet::BudFirst( CBudData** pData )
{
	*pData = (CBudData*)m_recs.GetAt( 0 );
	return 0;
}

int CBudSet::BudLast( CBudData** pData )
{
	*pData = (CBudData*)m_recs.GetAt( m_recs.GetUpperBound() );
	return m_recs.GetUpperBound();
}

CBudData* CBudSet::GetBudData( int nIndex ) const
{
	ASSERT( nIndex >=0 && nIndex <= m_recs.GetUpperBound() );
	return (CBudData*)m_recs.GetAt( nIndex );
}

BOOL CBudSet::IsLastBud( int nIndex )
{
	return ( nIndex==m_recs.GetUpperBound() ) ? TRUE : FALSE;
}

int CBudSet::IncAccess( CString strLetter )
{
	strLetter.MakeUpper();
	if( strLetter.GetLength()==0 )
	{
		UINT tmp = m_access.GetAt( Unindexed );
		m_access.SetAt( Unindexed, tmp + 1 );
		return tmp + 1;
	}

	char let = strLetter.GetAt( 0 );
	CBudSet::Index index = CBudSet::Unindexed;
	switch( let )
	{
		case 'A':	index = CBudSet::A;	break;
		case 'B':	index = CBudSet::B;	break;
		case 'C':	index = CBudSet::C;	break;
		case 'D':	index = CBudSet::D;	break;
		case 'E':	index = CBudSet::E;	break;
		case 'F':	index = CBudSet::F;	break;
		case 'G':	index = CBudSet::G;	break;
		case 'H':	index = CBudSet::H;	break;
		case 'I':	index = CBudSet::I;	break;
		case 'J':	index = CBudSet::J;	break;
		case 'K':	index = CBudSet::K;	break;
		case 'L':	index = CBudSet::L;	break;
		case 'M':	index = CBudSet::M;	break;
		case 'N':	index = CBudSet::N;	break;
		case 'O':	index = CBudSet::O;	break;
		case 'P':	index = CBudSet::P;	break;
		case 'Q':	index = CBudSet::Q;	break;
		case 'R':	index = CBudSet::R;	break;
		case 'S':	index = CBudSet::S;	break;
		case 'T':	index = CBudSet::T;	break;
		case 'U':	index = CBudSet::U;	break;
		case 'V':	index = CBudSet::V;	break;
		case 'W':	index = CBudSet::W;	break;
		case 'X':	index = CBudSet::X;	break;
		case 'Y':	index = CBudSet::Y;	break;
		case 'Z':	index = CBudSet::Z;	break;
	}

	UINT tmp = m_access.GetAt( index );
	m_access.SetAt( index, tmp + 1 );
	return tmp + 1;
}

int CBudSet::DeIncAccess( CString strLetter )
{
	strLetter.MakeUpper();
	if( strLetter.GetLength()==0 )
	{
		UINT tmp = m_access.GetAt( Unindexed );
		m_access.SetAt( Unindexed, tmp - 1 );
		return tmp - 1;
	}

	char let = strLetter.GetAt( 0 );
	CBudSet::Index index = CBudSet::Unindexed;
	switch( let )
	{
		case 'A':	index = CBudSet::A;	break;
		case 'B':	index = CBudSet::B;	break;
		case 'C':	index = CBudSet::C;	break;
		case 'D':	index = CBudSet::D;	break;
		case 'E':	index = CBudSet::E;	break;
		case 'F':	index = CBudSet::F;	break;
		case 'G':	index = CBudSet::G;	break;
		case 'H':	index = CBudSet::H;	break;
		case 'I':	index = CBudSet::I;	break;
		case 'J':	index = CBudSet::J;	break;
		case 'K':	index = CBudSet::K;	break;
		case 'L':	index = CBudSet::L;	break;
		case 'M':	index = CBudSet::M;	break;
		case 'N':	index = CBudSet::N;	break;
		case 'O':	index = CBudSet::O;	break;
		case 'P':	index = CBudSet::P;	break;
		case 'Q':	index = CBudSet::Q;	break;
		case 'R':	index = CBudSet::R;	break;
		case 'S':	index = CBudSet::S;	break;
		case 'T':	index = CBudSet::T;	break;
		case 'U':	index = CBudSet::U;	break;
		case 'V':	index = CBudSet::V;	break;
		case 'W':	index = CBudSet::W;	break;
		case 'X':	index = CBudSet::X;	break;
		case 'Y':	index = CBudSet::Y;	break;
		case 'Z':	index = CBudSet::Z;	break;
	}

	UINT tmp = m_access.GetAt( index );
	m_access.SetAt( index, tmp - 1 );
	return tmp - 1;
}


void CBudSet::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)m_recs.GetUpperBound();
		for( int loop=0; loop<=m_recs.GetUpperBound(); loop++ )
		{
			CBudData* pData = (CBudData*)m_recs.GetAt( loop );
			pData->Serialize( ar );
		}
		ar << (WORD)m_recs.GetUpperBound();
		for( loop=0; loop<=m_access.GetUpperBound(); loop++ )
			ar << (WORD)m_access.GetAt( loop );
	}
	else
	{
		WORD wTmp;
		ar >> wTmp;
		for( int loop=0; loop<=(int)wTmp; loop++ )
		{
			CBudData* pData = new CBudData;
			pData->Serialize( ar );	/*m_recs.*/AddRec( pData );
		}
		/*
		ar >> wTmp;
		for( loop=0; loop<=(int)wTmp; loop++ )
		{
			WORD tmp;
			ar >> tmp;
			m_access.SetAt( loop, (UINT)tmp );
		}*/
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBudData - A buddy record

IMPLEMENT_DYNCREATE( CBudData, CObject )

CBudData::CBudData()
{	}
	
CBudData::~CBudData()
{	}

void CBudData::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
		ar << GetTitle();
		ar << GetFirstName();
		ar << GetLastName();
		ar << GetAddress();
		ar << GetPhone();
		ar << GetFAX();
		ar << GetNotes();
	}
	else
	{
		CString tmpStr;
		ar >> tmpStr;	SetTitle( tmpStr );
		ar >> tmpStr;	SetFirstName( tmpStr );
		ar >> tmpStr;	SetLastName( tmpStr );
		ar >> tmpStr;	SetAddress( tmpStr );
		ar >> tmpStr;	SetPhone( tmpStr );
		ar >> tmpStr;	SetFAX( tmpStr );
		ar >> tmpStr;	SetNotes( tmpStr );
	}
}

CBudData& CBudData::operator=( CBudData* pData )
{
	m_strTitle		= pData->m_strTitle;
	m_strFirstName	= pData->m_strFirstName;
	m_strLastName	= pData->m_strLastName;
	m_strAddress	= pData->m_strAddress;
	m_strPhone		= pData->m_strAddress;
	m_strFAX		= pData->m_strPhone;
	m_strNotes		= pData->m_strNotes;

	return *this;
}

