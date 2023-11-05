/*                   DISCLAIMER AND AGREEMENT

Users of DiveLog must accept this disclaimer of warranty. If you
do not accept this disclaimer, do not use DiveLog.

   "DIVE LOG IS SUPPLIED AS IS.  THE AUTHOR DISCLAIMS ALL
   WARRANTIES, EXPRESSED OR IMPLIED, INCLUDING, WITHOUT
   LIMITATION, THE WARRANTIES OF MERCHANTABILITY AND OF
   FITNESS FOR ANY PURPOSE.

   "THE AUTHOR ASSUMES NO LIABILITY FOR DAMAGES, DIRECT OR
   CONSEQUENTIAL, WHICH MAY RESULT FROM THE USE OF DIVE LOG,
   EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE POSSIBILITY OF
   SUCH DAMAGES.

   "THE LICENCE AGREEMENT AND WARRANTY SHALL BE CONSTRUED,
   INTERPRETED AND GOVERNED BY THE LAWS OF ENGLAND AND WALES.
   YOU MAY HAVE OTHER RIGHTS WHICH VARY FROM ONE STATE TO
   ANOTHER."

Dive Log is a freeware program, and is provided at no charge to
users .  Feel free to share it with your friends
and colleagues, but please do not give it away altered or as part
of another system.

*/
// FIELD.CPP - implementation of the field classes

#include "stdafx.h"
#include "resource.h"
#include "divedata.h"
#include "field.h"
#include "calender.h"
#include "calendlg.h"
#include "fauxcmb.h"
#include "diagscrl.h"
#include "editdate.h"
#include "divedoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CBaseFld - base class for all fields

BEGIN_MESSAGE_MAP( CBaseFld, CEdit )
	//{{AFX_MSG_MAP(CBaseFld)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBaseFld::CBaseFld()
{
	m_pParent = NULL;
	m_pDiveSet = NULL;
	m_rect.SetRectEmpty();
	m_bDisplayed = FALSE;
	m_pDoc = NULL;
}

CBaseFld::~CBaseFld()
{	}

void CBaseFld::Create( CRect rect, CWnd* pParent, CDiveSet* pDiveSet, CDiveDoc* pDoc )
{
	ASSERT_VALID( pDoc );
	
	m_pParent = pParent;
	m_pDiveSet = pDiveSet;
	m_rect = rect;
	m_pDoc = pDoc;
}

BOOL CBaseFld::HitTest( CPoint point ) const
{
	return m_rect.PtInRect( point );
}

BOOL CBaseFld::IsFieldDisplayed()
{	return m_bDisplayed;	}

BOOL CBaseFld::CreateEdit( DWORD dwStyle, const RECT& rect, CWnd* pParent, UINT nID )
{
	CClientDC dc( this );
	CRect tmpRect = rect;
	dc.DPtoLP( tmpRect );
	
	return CEdit::Create( dwStyle, tmpRect, pParent, nID );
}

CRect CBaseFld::GetRect( ) const
{	return m_rect;	}

CBaseFld::fldName CBaseFld::GetFieldName() const
{	return m_fldName;	}

//////////////////////////////////////////////////////////////////////////
// CBaseFld Message map functions

void CBaseFld::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if( nChar == 9 || nChar == 13 )
	{
		m_pParent->SendMessage( BF_FINISHED , (WPARAM)m_fldName );
	}
	CEdit ::OnChar(nChar, nRepCnt, nFlags);
}


//////////////////////////////////////////////////////////////////////////
// CEditFld

IMPLEMENT_DYNCREATE( CEditFld, CObject )

CEditFld::CEditFld()
{
}

void CEditFld::DisplayFld( CDiveData* pDiveData )
{
	if( m_bDisplayed )	return;		// We are already displayed
	
	m_bDisplayed = TRUE;
	
   	CreateEdit( WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL, m_rect, m_pParent, ID_CUR_FIELD );
	
	switch( m_fldName )
	{
		case Visibility:
		{		char buf[5];	wsprintf( buf, "%d", pDiveData->m_VisDist );
				SetWindowText( buf );
				break;	}       
		case AirStart:
		{		char buf[5];	wsprintf( buf, "%d", pDiveData->m_nAirStart );
				SetWindowText( buf );
				break;	}       
		case AirEnd:
		{		char buf[5];	wsprintf( buf, "%d", pDiveData->m_nAirEnd );
				SetWindowText( buf );
				break;	}
		case TimeIn:
		{		SetWindowText( pDiveData->m_timeIn.Format( "%H:%M" ) );
				break;	}
		case TimeOut:
		{		SetWindowText( pDiveData->m_timeOut.Format( "%H:%M" ) );
				break;	}
		case Weight:
		{		char buf[5];	wsprintf( buf, "%d", pDiveData->m_nWeight );
				SetWindowText( buf );
				break;	}
		case SI:
		{		SetWindowText( pDiveData->m_surfaceInt.Format( "%H:%M" ) );
				break;	}
		case Depth:
		{		char buf[10];	_gcvt( pDiveData->m_nDepth, 3, buf );
				SetWindowText( buf );
				break;	}
		case BottomTime:
		{		char buf[5];	wsprintf( buf, "%d", pDiveData->m_nBottomTime );
				SetWindowText( buf );
				break;	}
		case Stop:
		{		char buf[5];	wsprintf( buf, "%d", pDiveData->m_nStop );
				SetWindowText( buf );
				break;	}
	}

	SetFocus();
	SetSel( 0, -1 );	// Select all text
}

BOOL CEditFld::RemoveFld( CDiveData* pDiveData )
{
 	if( !m_bDisplayed )	return FALSE;	// Control doesn`t exist
 	
 	m_bDisplayed = FALSE;
 	
	CString text;
	GetWindowText( text );   
	
	switch( m_fldName )
	{
		case Visibility:
		{		if( text.Right( 1 ) == "m" )		pDiveData->m_bVisFeet=FALSE;
				else if( text.Right( 1 ) == "f" )	pDiveData->m_bVisFeet = TRUE;
				const char* pszText = text;
				pDiveData->m_VisDist = (int)strtol( pszText, (char**)&pszText, 10 );
				m_pParent->InvalidateRect( CRect( 138, 127, 160, 140 ), FALSE );	// Update m/f
				break;	}
		case AirStart:
		{		if( text.Right( 1 ) == "p" )		pDiveData->m_bPSIStart=TRUE;
				else if( text.Right( 1 ) == "b" )	pDiveData->m_bPSIStart = FALSE;
				const char* pszText = text;
				pDiveData->m_nAirStart = (int)strtol( pszText, (char**)&pszText, 10 );
				m_pParent->InvalidateRect( CRect( 233, 82, 260, 97 ), FALSE );	// Update p/b
				break;	}
		case AirEnd:
		{		if( text.Right( 1 ) == "p" )		pDiveData->m_bPSIEnd=TRUE;
				else if( text.Right( 1 ) == "b" )	pDiveData->m_bPSIEnd = FALSE;
				const char* pszText = text;
				pDiveData->m_nAirEnd = (int)strtol( pszText, (char**)&pszText, 10 );
				m_pParent->InvalidateRect( CRect( 317, 82, 350, 97 ), FALSE );	// Update p/b
				break;	}
		case TimeIn:
		{		CString hour = text.Left( 2 );	const char* pszHour = hour;
				CString mins = text.Right( 2 );	const char* pszMins = mins;
				int nHour = (int)strtol( pszHour, (char**)&pszHour, 10 );
				int nMins = (int)strtol( pszMins, (char**)&pszMins, 10 );
				if( pDiveData->m_timeIn != CTime( 1970, 1, 1, nHour, nMins, 0 ) )
				{
					CTime oldTime = pDiveData->m_timeIn;
					pDiveData->m_timeIn = CTime( 1970, 1, 1, nHour, nMins, 0 );
				}
				break;	}
		case TimeOut:
		{		CString hour = text.Left( 2 );	const char* pszHour = hour;
				CString mins = text.Right( 2 );	const char* pszMins = mins;
				int nHour = (int)strtol( pszHour, (char**)&pszHour, 10 );
				int nMins = (int)strtol( pszMins, (char**)&pszMins, 10 );
				if( pDiveData->m_timeOut != CTime( 1970, 1, 1, nHour, nMins, 0 ) )
				{
					CTime oldTime = pDiveData->m_timeOut;
					pDiveData->m_timeOut = CTime( 1970, 1, 1, nHour, nMins, 0 );
				}
				break;	}
        case Weight:
		{		if( text.Right( 1 ) == "k" )		pDiveData->m_bKG = TRUE;
				else if( text.Right( 1 ) == "l" )	pDiveData->m_bKG = FALSE;
				const char* pszText = text;
				pDiveData->m_nWeight = (int)strtol( pszText, (char**)&pszText, 10 );
				m_pParent->InvalidateRect( CRect( 600, 307, 630, 320 ), FALSE );	// Update k/l
				break;	}
		case SI:
		{		CString hour = text.Left( 2 );	const char* pszHour = hour;
				CString mins = text.Right( 2 );	const char* pszMins = mins;
				int nHour = (int)strtol( pszHour, (char**)&pszHour, 10 );
				int nMins = (int)strtol( pszMins, (char**)&pszMins, 10 );
				pDiveData->m_surfaceInt = CTime( 1970, 1, 1, nHour, nMins, 0 );
				break;	}
		case Depth:
		{		float nDepth = (float)atof( text );
				if( nDepth < 0 || nDepth > 42 )
					AfxMessageBox( "Depth must be between 1 and 42" );
				else
				{
					pDiveData->m_nDepth = nDepth;
				}
				break;	}
		case BottomTime:
		{		const char* pszText = text;
				pDiveData->m_pDiveSet->m_totalABT -= CTimeSpan( 0, 0, pDiveData->m_nBottomTime, 0 );
				pDiveData->m_nBottomTime = (int)strtol( pszText, (char**)&pszText, 10 );
				pDiveData->m_pDiveSet->m_totalABT += CTimeSpan( 0, 0, pDiveData->m_nBottomTime, 0 );
				break;	}
		case Stop:
		{		const char* pszText = text;
				pDiveData->m_nStop = (int)strtol( pszText, (char**)&pszText, 10 );
				break;	}
	}
	
	DestroyWindow();
	return TRUE;
}

void CEditFld::SetFldName( fldName fn )
{	m_fldName = fn;	}

//////////////////////////////////////////////////////////////////////////
// CEditDateFld

IMPLEMENT_DYNCREATE( CEditDateFld, CObject )

CEditDateFld::CEditDateFld()
{
	m_pEditDate = NULL;
}

void CEditDateFld::DisplayFld( CDiveData* pDiveData )
{
	m_bDisplayed = TRUE;
	if( m_pEditDate!=NULL )	return;	// We are already displayed
	m_pEditDate = new CEditDate();
	m_pEditDate->Create( WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL, m_rect, m_pParent, ID_CUR_FIELD );
	m_pEditDate->AttachCombo();    
	CString date = pDiveData->m_date.Format( "%d/%m/%y" );
	m_pEditDate->InitDate( date ); 
	m_pEditDate->ShowCalendar();
}

BOOL CEditDateFld::RemoveFld( CDiveData* pDiveData )
{
	m_bDisplayed = FALSE;
	if( m_pEditDate==NULL )	return FALSE;
	m_pEditDate->DetachCombo();
	if( pDiveData->m_date != m_pEditDate->GetDate() )
	{
		CTime oldDate = pDiveData->m_date;
		pDiveData->m_date = m_pEditDate->GetDate();
		m_pDiveSet->DateChange( oldDate );
		m_pParent->InvalidateRect( CRect( 75, 16, 145, 37 ), FALSE );	// Could have changed
	}
	delete m_pEditDate;	m_pEditDate = NULL;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// CComboFld

IMPLEMENT_DYNCREATE( CComboFld, CObject )

CComboFld::CComboFld()
{
	m_pCombo = NULL;
	m_nComboHeight = 70;	// Default 70 pixels including edit box
}

void CComboFld::DisplayFld( CDiveData* pDiveData )
{
	m_bDisplayed = TRUE;
	if( m_pCombo!=NULL )	return;
	m_pCombo = new CComboBox();
	CRect rect = m_rect;	rect.bottom += m_nComboHeight;	// for listbox part
	m_pCombo->Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_SIMPLE, rect, m_pParent, ID_CUR_FIELD );
	for( int loop=0; loop<=m_pDoc->m_locations.GetUpperBound(); loop++ )
		m_pCombo->AddString( m_pDoc->m_locations.GetAt( loop ) );
	if( m_pCombo->SelectString( -1, pDiveData->m_location )==CB_ERR )
			m_pCombo->SetWindowText( pDiveData->m_location );
	m_pCombo->SetFocus();
}

BOOL CComboFld::RemoveFld( CDiveData* pDiveData )
{
	m_bDisplayed = FALSE;
	if( m_pCombo==NULL )	return FALSE;
	m_pCombo->GetWindowText( pDiveData->m_location );
	delete m_pCombo;	m_pCombo=NULL;
	return TRUE;
}

void CComboFld::SetHeight( int nHeight )
{	m_nComboHeight = nHeight;	}

