// FORM.CPP - implementation of the CForm class

#include "stdafx.h"
#include "form.h"
#include "drwtools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CForm

IMPLEMENT_DYNCREATE( CForm, CObject )

CForm::CForm()
{
	m_bPaper = FALSE;
	m_crPaper = RGB( 0, 0, 0 );
}

CForm::~CForm()
{
	for( int loop=0; loop<=m_objects.GetUpperBound(); loop++ )
	{
		CObject* pObj = (CObject*)m_objects.GetAt( loop );
		delete pObj;
	}
	m_objects.RemoveAll();
}

BOOL CForm::LoadForm( const CString filename )
{
	// Open file and construct archive
	CFile file;
	if( !file.Open( filename, CFile::modeRead | CFile::shareDenyNone ) )
	{
		AfxMessageBox( "Can`t find " + filename );
		return FALSE;
	}
	CArchive ar( &file, CArchive::load );
	
	BYTE ident1, ident2, ident3, ver;
	WORD wTmp;
	// Get identifier (LSV) and form version number
	ar >> ident1;	ar >> ident2;	ar >> ident3;	ar >> ver;
	if( ident1 != 0x4C || ident2 != 0x53 || ident3 != 0x56 || ver != 0x01 )
	{
		AfxMessageBox( filename + " is corrupted!, re-install" );
		return FALSE;		// Only support forms created in version 1
	}
	
	ar >> wTmp;		// Total No. of pages - Not used in Dive Log
	ar >> wTmp;		// Next button id - Not used in Dive Log
	ar >> wTmp;		// Next text id - Not used in Dive Log
	
	BOOL bSuccess = TRUE;
	
	ar >> wTmp;	m_bPaper = wTmp;		ar >> m_crPaper;
	ar >> wTmp;	const int nTotalObjs = wTmp;		// Total number of objects on this page
	
	for( int loop=0; loop<=nTotalObjs; loop++ )
	{
		if( !bSuccess )
			break;	// there is a problem
		ar >> wTmp;
		switch( wTmp )
		{
			case ID_FILE_RECT:	// Rectangle
			{		CRectDraw* pRect = new CRectDraw();
					pRect->SetType( CRectDraw::Rect );
					bSuccess = pRect->Load( ar );
					m_objects.Add( pRect );
					break;	}
			case ID_FILE_CIRCLE:	// Ellipse
			{		CEllipseDraw* pEllipse = new CEllipseDraw();
					pEllipse->SetType( CEllipseDraw::Circle );
					bSuccess = pEllipse->Load( ar );
					m_objects.Add( pEllipse );
					break;	}
			case ID_FILE_TEXT: // Text
			{		CTextDraw* pText = new CTextDraw();
					pText->SetType( CTextDraw::Text );
					bSuccess = pText->Load( ar );
					m_objects.Add( pText );
					break;	}
			case ID_FILE_LINE:	// Line
			{		CLineDraw* pLine = new CLineDraw();
					pLine->SetType( CLineDraw::Line );
					bSuccess = pLine->Load( ar );
					m_objects.Add( pLine );
					break;	}
		}
	}

	ar.Close();		file.Close();
	return bSuccess;
}

void CForm::DrawForm( CDC* pDC ) const
{
	if( m_bPaper )
	{
		CPen pen;		pen.CreatePen( PS_NULL, 1, m_crPaper );
		CBrush brush;	brush.CreateSolidBrush( m_crPaper );
		CPen* pOldPen = pDC->SelectObject( &pen );
		CBrush* pOldBrush = pDC->SelectObject( &brush );
		pDC->Rectangle( 0, 0, 640, 480 );
		pDC->SelectObject( pOldPen );
		pDC->SelectObject( pOldBrush );
	}
		
	for( int loop=0; loop<=m_objects.GetUpperBound(); loop++ )
	{
		CBaseDraw* pBaseDraw = (CBaseDraw*)m_objects.GetAt( loop );
		pBaseDraw->Draw( pDC );
	}
}

BOOL CForm::IsFormLoaded() const
{
	return m_objects.GetSize() == 0 ? FALSE : TRUE;
}
