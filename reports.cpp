/////////////////////////////////////////////////////////////////////////
// reports.cpp

#include "stdafx.h"
#include "divelog.h"
#include "divedata.h"
#include "reports.h"
#include "editdate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReport

IMPLEMENT_DYNCREATE( CReport, CObject )

CReport::CReport( )
{
	m_pDiveSet = NULL;
	m_strLoc = "";
	m_nFilterDepth = -1;
}

CReport::CReport( CDiveSet* pDiveSet )
{
	m_pDiveSet = pDiveSet;
	m_strLoc = "";
	m_nFilterDepth = -1;
}

CReport::~CReport( )
{
	for( int i=0; i<=m_columns.GetUpperBound(); i++ )
	{
		CColumn* pCol = (CColumn*)m_columns.GetAt( i );
		delete pCol;
	}
	for( i=0; i<=m_repColumns.GetUpperBound(); i++ )
	{
		CColumn* pCol = (CColumn*)m_repColumns.GetAt( i );
		delete pCol;
	}
}

void CReport::NewCol( CString name, CColumn::ColType colType, int nWidth )
{
	CColumn* pCol = new CColumn( name, colType, nWidth );
	m_columns.Add( pCol );
}

CColumn* CReport::GetCol( int nCol )
{
	ASSERT( nCol <= m_columns.GetUpperBound( ) );
	return (CColumn*)m_columns.GetAt( nCol );
}

CColumn* CReport::GetRepCol( int nCol )
{
	ASSERT( nCol <= m_repColumns.GetUpperBound( ) );
	return (CColumn*)m_repColumns.GetAt( nCol );
}

/////////////////////////////////////////////////////////////////////////////
// CColumn

BOOL CColumn::m_bWarnDate = TRUE;

IMPLEMENT_DYNCREATE( CColumn, CObject )

CColumn::CColumn( )
{	}

CColumn::CColumn( CString name, ColType colType, int nWidth )
{
	m_colName = name;
	m_colType = colType;
	//m_nWidth = nWidth;
	m_repName = AfxGetApp()->GetProfileString( "Reports", m_colName, m_colName );
	m_nWidth = AfxGetApp()->GetProfileInt( "Reports", m_colName+"W", nWidth );
}

CString CColumn::GetString( CDiveData* pData )
{
	ASSERT_VALID( pData );
	CString str;
	switch( m_colType )
	{
		case Text:
			if( m_colName == "Location" )	str = pData->GetLoc( );
			else if( m_colName == "Notes" )	str = pData->GetNotes( );
			else if( m_colName == "PG Before Dive" )	str = pData->GetPGBeforeDive( );
			else if( m_colName == "PG After Dive" )		str = pData->GetPGAfterDive( );
			else str = "Unable to find column!";
			break;
		case Bool:		str = GetBoolString( pData );		break;
		case Date:
		{	if( m_colName != "Date" )	{	str = "Unable to find date column";	break;	}
			CTime date = pData->GetDate( );
			str = date.Format( "%d %B %y" );
			break;	}
		case Time:
		{	CTime time;
			if( m_colName == "Time In" )		time = pData->GetTimeIn( );
			else if( m_colName == "Time Out" )	time = pData->GetTimeOut( );
			else if( m_colName == "Surface Interval" )	time = pData->GetSI( );
			else {	str = "Unable to find time column";	break;	}
			str = time.Format( "%H:%M" );
			break;	}
		case Integer:	str = GetIntString( pData );	break;
		case Temperature:
			if( m_colName == "Air Temperature" )
			{
				switch( pData->GetAirTemp() )
				{
					case CDiveData::Cold:	str = "Cold";	break;
					case CDiveData::Warm:	str = "Warm";	break;
					case CDiveData::Hot:	str = "Hot";	break;
				}
			}
			if( m_colName == "Surface Temperature" )
			{
				switch( pData->GetSurfaceTemp() )
				{
					case CDiveData::Cold:	str = "Cold";	break;
					case CDiveData::Warm:	str = "Warm";	break;
					case CDiveData::Hot:	str = "Hot";	break;
				}
			}
			if( m_colName == "Bottom Temperature" )
			{
				switch( pData->GetBottomTemp() )
				{
					case CDiveData::Cold:	str = "Cold";	break;
					case CDiveData::Warm:	str = "Warm";	break;
					case CDiveData::Hot:	str = "Hot";	break;
				}
			}
			break;
		case Real:	str = GetRealString( pData );	break;
		case VisStyle:
			switch( pData->GetVis() )
			{
				case CDiveData::Good:		str = "Good";	break;
				case CDiveData::Medium:		str = "Medium";	break;
				case CDiveData::Poor:		str = "Poor";	break;
			}
			break;

		default:
			str = "Unable to find column!";
	}

	return str;		
}

CString CColumn::GetBoolString( CDiveData* pData )
{
	if( m_colName == "Fresh" )		return (pData->GetFresh()) ? "Y" : "N";
	else if( m_colName == "Shore" )	return (pData->GetShore()) ? "Y" : "N";
	else if( m_colName == "Waves" )	return (pData->GetWaves()) ? "Y" : "N";
	else if( m_colName == "Surf" )	return (pData->GetSurf()) ? "Y" : "N";
	else if( m_colName == "Salt" )	return (pData->GetSalt()) ? "Y" : "N";
	else if( m_colName == "Boat" )	return (pData->GetBoat()) ? "Y" : "N";
	else if( m_colName == "Current" )		return (pData->GetCurrent()) ? "Y" : "N";
	else if( m_colName == "Surge" )			return (pData->GetSurge()) ? "Y" : "N";
	else if( m_colName == "Wet Suit" )		return (pData->GetWetSuit()) ? "Y" : "N";
	else if( m_colName == "Under Suit" )	return (pData->GetUSuit()) ? "Y" : "N";
	else if( m_colName == "Semi Dry Suit" )	return (pData->GetSDrySuit()) ? "Y" : "N";
	else if( m_colName == "Dry Suit" )		return (pData->GetDrySuit()) ? "Y" : "N";
	else if( m_colName == "Gloves" )		return (pData->GetGloves()) ? "Y" : "N";
	else if( m_colName == "Mittens" )		return (pData->GetMittens()) ? "Y" : "N";
	else if( m_colName == "Hood" )	return (pData->GetHood()) ? "Y" : "N";
	else if( m_colName == "Socks" )	return (pData->GetSocks()) ? "Y" : "N";

	return "Unable to find column!";
}

CString CColumn::GetIntString( CDiveData* pData )
{
	int nVal = 0;
	if( m_colName == "Air Start" || m_colName == "Air End" )
	{
		char buf[10];
		if( m_colName == "Air Start" )	wsprintf( buf, "%d", pData->GetAirStart() );
		if( m_colName == "Air End" )	wsprintf( buf, "%d", pData->GetAirEnd() );
		CString str = buf;
		if( pData->GetAirPSI() )	str += " psi";
		else	str += " bar";
		return str;
	}
	else if( m_colName == "Weight" )
	{
		char buf[10];
		wsprintf( buf, "%d", pData->GetWeight() );	CString str = buf;
		if( pData->GetWeightKG() )		str += " kgs";
		else	str += " lbs";
		return str;
	}
	else if( m_colName == "Bottom Time" )	nVal = pData->GetBottomTime( );
	else if( m_colName == "Decompression Stop" )	nVal = pData->GetDecompStop( );
	else if( m_colName == "R.N.T." )	nVal = pData->GetRNT( );
	else if( m_colName == "A.B.T." )	nVal = pData->GetABT( );
	else if( m_colName == "T.B.T." )	nVal = pData->GetTBT( );

	char buf[10];
	wsprintf( buf, "%d", nVal );
	return CString( buf );
}

CString CColumn::GetRealString( CDiveData* pData )
{
	char buf[10];	CString str;
	if( m_colName == "Visibility Distance" )
	{
		_gcvt( pData->GetVisDist(), 3, buf );	str = buf;
		if( str.Right( 1 ) == '.' )		str = str.Left( str.GetLength()-1 );
		if( pData->GetVisFt() )		str += " ft";
		else	str += " mtrs";
	}
	else if( m_colName == "Depth" )
	{
		_gcvt( pData->GetDepth(), 3, buf );	str = buf;
		if( str.Right( 1 ) == '.' )		str = str.Left( str.GetLength()-1 );
		if( pData->GetDepthMts() )		str += " mtrs";
		else	str += " ft";
	}
	return str;
}

BOOL CColumn::TestColumn( CString strVal, CString strOperand, CDiveData* pData )
{
	ASSERT_VALID( pData );
	ASSERT( strOperand=="=" || strOperand=="<>" || strOperand==">" || strOperand=="<" );

	strVal.MakeUpper();
	CString str;
	

	switch( m_colType )
	{
		case Text:
		{	if( m_colName == "Location" )	str = pData->GetLoc( );
			else if( m_colName == "Notes" )	str = pData->GetNotes( );
			else if( m_colName == "PG Before Dive" )	str = pData->GetPGBeforeDive( );
			else if( m_colName == "PG After Dive" )		str = pData->GetPGAfterDive( );
			str.MakeUpper();
			if( strOperand == "=" )			{	if( strVal == str )	return TRUE;	}
			else if( strOperand == "<>" )	{	if( strVal != str )	return TRUE;	}
			else if( strOperand == ">" )	{	if( strVal < str )	return TRUE;	}
			else if( strOperand == "<" )	{	if( strVal > str )	return TRUE;	}
			break; 	}
		case Bool:
		{	str = GetBoolString( pData );
			str.MakeUpper();
			if( strOperand == "=" )			{	if( strVal == str )	return TRUE;	}
			else if( strOperand == "<>" )	{	if( strVal != str )	return TRUE;	}
			else if( strOperand == ">" )	{	if( strVal < str )	return TRUE;	}
			else if( strOperand == "<" )	{	if( strVal > str )	return TRUE;	}
			break; 	}
		case Date:
		{	CTime date = pData->GetDate( );

			CEditDate edit;
			int nDay, nMonth, nYear;
			nDay = nMonth = nYear;
			
			BOOL bResult = FALSE;

			if( strVal.GetLength() != 0 )
				bResult = edit.ParseDate( strVal, nMonth, nDay, nYear );

			if( bResult && nYear != 0 )
			{
				CTime tmp( nYear, nMonth, nDay, 0, 0, 0 );
				CTime newDate( date.GetYear(), date.GetMonth(), date.GetDay(), 0, 0, 0 ); 
				if( strOperand == "=" )			{	if( newDate == tmp )	return TRUE;	}
				else if( strOperand == "<>" )	{	if( newDate != tmp )	return TRUE;	}
				else if( strOperand == ">" )	{	if( newDate > tmp )	return TRUE;	}
				else if( strOperand == "<" )	{	if( newDate < tmp )	return TRUE;	}
			}
			else
			{
				if( m_bWarnDate )
				{
					AfxMessageBox( "Invalide date in filter!", MB_ICONEXCLAMATION|MB_OK );
					CColumn::m_bWarnDate = FALSE;
				}
			}

			break; 	}
		case Time:
		{	CTime time;
			if( m_colName == "Time In" )		time = pData->GetTimeIn( );
			else if( m_colName == "Time Out" )	time = pData->GetTimeOut( );
			else if( m_colName == "Surface Interval" )	time = pData->GetSI( );

			CString strHrs = strVal.Left( 2 );	CString strMins = strVal.Right( 2 );
			const char* pszText = strHrs;
			int nHrs = (int)strtol( pszText, (char**)&pszText, 10 );
			pszText = strMins;	int nMins = (int)strtol( pszText, (char**)&pszText, 10 );
			
			CTime tmp( 1970, 1, 1, nHrs, nMins, 0 );
			if( strOperand == "=" )			{	if( time == tmp )	return TRUE;	}
			else if( strOperand == "<>" )	{	if( time != tmp )	return TRUE;	}
			else if( strOperand == ">" )	{	if( time < tmp )	return TRUE;	}
			else if( strOperand == "<" )	{	if( time > tmp )	return TRUE;	}
			break;	}
		case Integer:
		{	int nVal;
			if( m_colName == "Bottom Time" )	{	nVal = pData->GetBottomTime( );		return CompInt( nVal, strVal, strOperand );	}
			else if( m_colName == "Decompression Stop" )	{	nVal = pData->GetDecompStop( );		return CompInt( nVal, str, strOperand );	}
			else if( m_colName == "R.N.T." )	{	nVal = pData->GetRNT( );		return CompInt( nVal, strVal, strOperand );	}
			else if( m_colName == "A.B.T." )	{	nVal = pData->GetABT( );		return CompInt( nVal, strVal, strOperand );	}
			else if( m_colName == "T.B.T." )	{	nVal = pData->GetTBT( );		return CompInt( nVal, strVal, strOperand );	}
			else if( m_colName == "Air Start" )	{	nVal = pData->GetAirStart( );	return CompAir( nVal, strVal, strOperand, pData->GetAirPSI() );	}
			else if( m_colName == "Air End" )	{	nVal = pData->GetAirEnd( );		return CompAir( nVal, strVal, strOperand, pData->GetAirPSI() );	}
			else if( m_colName == "Weight" )	{	nVal = pData->GetWeight( );		return CompWeight( nVal, strVal, strOperand, pData->GetWeightKG() );	}
			return FALSE;
			break;	}
		case Temperature:
		{	CDiveData::Temperature temp;
			if( m_colName == "Air Temperature" )			temp = pData->GetAirTemp( );
			else if( m_colName == "Surface Temperature" )	temp = pData->GetSurfaceTemp( );
			else if( m_colName == "Bottom Temperature" )	temp = pData->GetBottomTemp( );

			int nData = (int)temp;
			int nVal = 9;
			if( strVal == "COLD" )			nVal = 0;
			else if( strVal == "WARM" )		nVal = 1;
			else if( strVal == "HOT" )		nVal = 2;

			if( nVal == 9 )	return FALSE;
			if( strOperand == "=" )			{	if( nVal == nData )	return TRUE;	}
			else if( strOperand == "<>" )	{	if( nVal != nData )	return TRUE;	}
			else if( strOperand == ">" )	{	if( nVal < nData )	return TRUE;	}
			else if( strOperand == "<" )	{	if( nVal > nData )	return TRUE;	}
			return FALSE;
			break;	}
		case Real:
		{	float nVal;
			if( m_colName == "Visibility Distance" )
			{
				if( strVal.Right( 1 ) == "M" )
				{
					if( pData->GetVisFt() )	return FALSE;
					strVal = strVal.Left( strVal.GetLength()-1 );
				}
				else if( strVal.Right( 1 ) == "F" )
				{
					if( !pData->GetVisFt() ) return FALSE;
					strVal = strVal.Left( strVal.GetLength()-1 );
				}

				nVal = pData->GetVisDist();
				float nStr = (float)atof( strVal );
				if( strOperand == "=" )			{	if( nVal == nStr )	return TRUE;	}
				else if( strOperand == "<>" )	{	if( nVal != nStr )	return TRUE;	}
				else if( strOperand == ">" )	{	if( nVal > nStr )	return TRUE;	}
				else if( strOperand == "<" )	{	if( nVal < nStr )	return TRUE;	}
				return FALSE;
			}
			else if( m_colName == "Depth" )
			{
				if( strVal.Right( 1 ) == "M" )
				{
					if( !pData->GetDepthMts() )	return FALSE;
					strVal = strVal.Left( strVal.GetLength()-1 );
				}
				else if( strVal.Right( 1 ) == "F" )
				{
					if( pData->GetDepthMts() ) return FALSE;
					strVal = strVal.Left( strVal.GetLength()-1 );
				}

				nVal = pData->GetDepth();
				float nStr = (float)atof( strVal );
				if( strOperand == "=" )			{	if( nVal == nStr )	return TRUE;	}
				else if( strOperand == "<>" )	{	if( nVal != nStr )	return TRUE;	}
				else if( strOperand == ">" )	{	if( nVal > nStr )	return TRUE;	}
				else if( strOperand == "<" )	{	if( nVal < nStr )	return TRUE;	}
				return FALSE;
			}
			break;	}
		case VisStyle:
		{	CDiveData::VisStyle style;
			ASSERT( m_colName == "Visibility Type" );
			style = pData->GetVis( );

			int nData = (int)style;
			int nVal = 9;
			if( strVal == "GOOD" )			nVal = 0;
			else if( strVal == "MEDIUM" )	nVal = 1;
			else if( strVal == "POOR" )		nVal = 2;

			if( nVal == 9 )	return FALSE;
			if( strOperand == "=" )			{	if( nVal == nData )	return TRUE;	}
			else if( strOperand == "<>" )	{	if( nVal != nData )	return TRUE;	}
			else if( strOperand == ">" )	{	if( nVal < nData )	return TRUE;	}
			else if( strOperand == "<" )	{	if( nVal > nData )	return TRUE;	}
			return FALSE;
			break;	}
	}

	return FALSE;
}

BOOL CColumn::CompInt( int nVal, CString str, CString strOperand )
{
	const char* pszStr = str;
	int nStr = (int)strtol( pszStr, (char**)&pszStr, 10 );

	if( strOperand == "=" )			{	if( nVal == nStr )	return TRUE;	}
	else if( strOperand == "<>" )	{	if( nVal != nStr )	return TRUE;	}
	else if( strOperand == ">" )	{	if( nVal > nStr )	return TRUE;	}
	else if( strOperand == "<" )	{	if( nVal < nStr )	return TRUE;	}
	return FALSE;
}

BOOL CColumn::CompAir( int nVal, CString str, CString strOperand, BOOL bPSI )
{
	if( str.Right( 1 )=="B" )
	{
		if( bPSI )	return FALSE;	// measurement in bar not psi
		str = str.Left( str.GetLength()-1 );
		return CompInt( nVal, str, strOperand );
	}
	else if( str.Right( 1 )=="P" )
	{
		if( !bPSI )	return FALSE;	// measurement in psi not bar
		str = str.Left( str.GetLength()-1 );
		return CompInt( nVal, str, strOperand );
	}
	else
		return CompInt( nVal, str, strOperand );

	ASSERT( FALSE );	// Should not get to this point
}

BOOL CColumn::CompWeight( int nVal, CString str, CString strOperand, BOOL bKG )
{
	if( str.Right( 1 )=="L" )
	{
		if( bKG )	return FALSE;	// measurement in kgs not lbs
		str = str.Left( str.GetLength()-1 );
		return CompInt( nVal, str, strOperand );
	}
	else if( str.Right( 1 )=="K" )
	{
		if( !bKG )	return FALSE;	// measurement in lbs not kgs
		str = str.Left( str.GetLength()-1 );
		return CompInt( nVal, str, strOperand );
	}
	else
		return CompInt( nVal, str, strOperand );

	ASSERT( FALSE );	// Should not get to this point
}





