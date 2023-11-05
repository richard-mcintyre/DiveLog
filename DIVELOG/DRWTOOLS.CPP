// DRWTOOLS.CPP - implementation of the drawable classes

#include "stdafx.h"
#include "drwtools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CBaseDraw

CBaseDraw::CBaseDraw( )
{
	m_ObjectType = Undefined;
	m_boundingRect.SetRectEmpty();
}

CBaseDraw::~CBaseDraw( )
{	}

CBaseDraw::ObjType CBaseDraw::GetType( ) const
{	return m_ObjectType;	}

CRect CBaseDraw::GetRect( ) const
{	return m_boundingRect;	}

void CBaseDraw::SetType( const ObjType ObjectType )
{	m_ObjectType = ObjectType;	}

void CBaseDraw::SetRect( const CRect rect )
{	m_boundingRect = rect;	}

//////////////////////////////////////////////////////////////////////////
// CEllipseDraw

IMPLEMENT_DYNCREATE( CEllipseDraw, CObject )

CEllipseDraw::CEllipseDraw( )
{
	m_bPen = FALSE;		m_PenColour = RGB( 0, 0, 0 );
	m_bBrush = FALSE;	m_BrushColour = RGB( 0, 0, 0 );
	m_nLineWidth = 0;
	m_bShadow = FALSE;
	m_style = CEllipseDraw::Undefined;
	m_nStep = 0;
}

BOOL CEllipseDraw::Load( CArchive& ar )
{
	WORD wTmp;	CRect tmpRect;
	ar >> m_PenColour;
	ar >> m_BrushColour;
	ar >> wTmp;	m_nLineWidth = wTmp;
	ar >> wTmp;	m_bPen = wTmp;
	ar >> wTmp;	m_bBrush = wTmp;
	ar >> wTmp;	m_bShadow = wTmp;
	ar >> wTmp;	m_style = (CEllipseDraw::Style)wTmp;
	ar >> wTmp;	m_nStep = wTmp;
	ar >> tmpRect;	SetRect( tmpRect );
	return TRUE;
}

void CEllipseDraw::Draw( CDC* pDC ) const
{
	if( m_bShadow )		// Draw a shadow ?
	{
		CPen pen;		pen.CreatePen( PS_NULL, 1, RGB( 0, 0, 0 ) );
		CBrush brush;	brush.CreateSolidBrush( RGB( 225, 225, 225 ) );
		CPen* pOldPen = pDC->SelectObject( &pen );
		CBrush* pOldBrush = pDC->SelectObject( &brush );
		CRect tmpRect;
		tmpRect = GetRect();	tmpRect.OffsetRect( CPoint( 10, 10 ) );
		pDC->Ellipse( tmpRect );
		pDC->SelectObject( pOldPen );
		pDC->SelectObject( pOldBrush );
	}		

	CPen pen;
	if( m_bPen )	pen.CreatePen( PS_SOLID, m_nLineWidth, m_PenColour );
	else			pen.CreatePen( PS_NULL, m_nLineWidth, m_PenColour );
    CPen* pOldPen = pDC->SelectObject( &pen );
    
	CBrush brush;
	CBrush* pOldBrush = NULL;
	if( m_bBrush )
	{
		brush.CreateSolidBrush( m_BrushColour );
		pOldBrush = pDC->SelectObject( &brush );
	}
	else
		pOldBrush = (CBrush*)pDC->SelectStockObject( NULL_BRUSH );
	
	pDC->Ellipse( GetRect( ) );
	
	if( m_style == CEllipseDraw::Raised )			DrawStep( pDC, m_nStep, TRUE );
	else if( m_style == CEllipseDraw::Recessed )	DrawStep( pDC, m_nStep, FALSE );
	
	pDC->SelectObject( pOldPen );
	if( pOldBrush!=NULL )
		pDC->SelectObject( pOldBrush );
}

void CEllipseDraw::DrawStep( CDC* pDC, int nStep, BOOL bRaised ) const
{
	CRect localRect;
	localRect = GetRect();		// Get a copy of the bounding rectangle
	if( m_bPen )
		localRect.InflateRect( (m_nLineWidth-(m_nLineWidth*2)), (m_nLineWidth-(m_nLineWidth*2)) );

	CPen pen;
	if( bRaised )	pen.CreatePen( PS_SOLID, nStep, RGB( 255, 255, 255 ) );
	else			pen.CreatePen( PS_SOLID, nStep, RGB( 128, 128, 128 ) );
	CPen* pOldPen = pDC->SelectObject( &pen );
	
	pDC->Arc( localRect, CPoint( localRect.right, localRect.top ),
							CPoint( localRect.left, localRect.bottom ) );

	pDC->SelectObject( pOldPen );

	CPen pen2;
	if( bRaised )	pen2.CreatePen( PS_SOLID, nStep, RGB( 128, 128, 128 ) );
	else			pen2.CreatePen( PS_SOLID, nStep, RGB( 255, 255, 255 ) );
	CPen* pOldPen2 = pDC->SelectObject( &pen2 );
	
	pDC->Arc( localRect, CPoint( localRect.left, localRect.bottom ),
							CPoint( localRect.right, localRect.top ) );
	pDC->SelectObject( pOldPen2 );
}

//////////////////////////////////////////////////////////////////////////
// CLineDraw

IMPLEMENT_DYNCREATE( CLineDraw, CObject )

CLineDraw::CLineDraw( )
{
	m_PenColour = RGB( 0, 0, 0 );
	m_nLineWidth = 0;
}

BOOL CLineDraw::Load( CArchive& ar )
{
	WORD wTmp;	CPoint	topLeft, bottomRight;
	ar >> m_PenColour;
	ar >> wTmp;	m_nLineWidth = wTmp;
	ar >> topLeft;
	ar >> bottomRight;
	SetRect( CRect( topLeft.x, topLeft.y, bottomRight.x, bottomRight.y ) );
	
	return TRUE;
}

void CLineDraw::Draw( CDC* pDC ) const
{
	CPen pen;	pen.CreatePen( PS_SOLID, m_nLineWidth, m_PenColour );
	CPen* pOldPen = pDC->SelectObject( &pen );
	
	pDC->MoveTo( GetRect().TopLeft() );
	pDC->LineTo( GetRect().BottomRight() );
	
	pDC->SelectObject( pOldPen );
}

//////////////////////////////////////////////////////////////////////////
// CRectDraw

IMPLEMENT_DYNCREATE( CRectDraw, CObject )

CRectDraw::CRectDraw( )
{
	m_bPen = FALSE;		m_PenColour = RGB( 0, 0, 0 );
	m_bBrush = FALSE;	m_BrushColour = RGB( 0, 0, 0 );
	m_nLineWidth = 0;
	m_bShadow = FALSE;
	m_style = CRectDraw::Undefined;
	m_nStep = 0;
}

BOOL CRectDraw::Load( CArchive& ar )
{
	WORD wTmp;	CRect tmpRect;
	ar >> m_PenColour;
	ar >> m_BrushColour;
	ar >> wTmp;	m_nLineWidth = wTmp;
	ar >> wTmp;	m_bPen = wTmp;
	ar >> wTmp;	m_bBrush = wTmp;
	ar >> wTmp;	m_bShadow = wTmp;
	ar >> wTmp; m_style = (CRectDraw::Style)wTmp;
	ar >> wTmp;	m_nStep = wTmp;
	ar >> tmpRect;	SetRect( tmpRect );
	return TRUE;
}

void CRectDraw::Draw( CDC* pDC ) const
{
	if( m_bShadow )
	{
		CPen pen;		pen.CreatePen( PS_NULL, 1, RGB( 0, 0, 0 ) );
		CBrush brush;	brush.CreateSolidBrush( RGB( 225, 225, 225 ) );
		CPen* pOldPen = pDC->SelectObject( &pen );
		CBrush* pOldBrush = pDC->SelectObject( &brush );
		CRect tmpRect;
		tmpRect = GetRect();	tmpRect.OffsetRect( CPoint( 10, 10 ) );
		pDC->Rectangle( tmpRect );
		pDC->SelectObject( pOldPen );
		pDC->SelectObject( pOldBrush );
	}		

	CPen pen;
	if( m_bPen )	pen.CreatePen( PS_SOLID, m_nLineWidth, m_PenColour );
	else			pen.CreatePen( PS_NULL, m_nLineWidth, m_PenColour );
    CPen* pOldPen = pDC->SelectObject( &pen );
    
	CBrush brush;
	CBrush* pOldBrush = NULL;
	if( m_bBrush )
	{
		brush.CreateSolidBrush( m_BrushColour );
		pOldBrush = pDC->SelectObject( &brush );
	}
	else
		pOldBrush = (CBrush*)pDC->SelectStockObject( NULL_BRUSH );
	
	pDC->Rectangle( GetRect( ) );
	
	if( m_style == CRectDraw::Raised )			DrawStep( pDC, m_nStep, TRUE );
	else if( m_style == CRectDraw::Recessed )	DrawStep( pDC, m_nStep, FALSE );
	
	pDC->SelectObject( pOldPen );
	if( pOldBrush!=NULL )
		pDC->SelectObject( pOldBrush );
}

void CRectDraw::DrawStep( CDC* pDC, int nStep, BOOL bRaised ) const
{
	int nBorder = 0;
	if( m_bPen )
		nBorder = 1;
		
	CPen pen;
	if( bRaised )	pen.CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
	else			pen.CreatePen( PS_SOLID, 1, RGB( 128, 128, 128 ) );
	CPen* pOldPen = pDC->SelectObject( &pen );
	
	for( int loop=0; loop<=nStep; loop++ )
	{
		pDC->MoveTo( GetRect().left + (nBorder+loop),	GetRect().top + (nBorder+loop) ); 	// Top
		pDC->LineTo( GetRect().right - (nBorder+loop),	GetRect().top + (nBorder+loop) );
		pDC->MoveTo( GetRect().left + (nBorder+loop),	GetRect().top + (nBorder+loop) );	// Left
		pDC->LineTo( GetRect().left + (nBorder+loop),	GetRect().bottom - (nBorder+loop) );
	}
	                                                                    
	pDC->SelectObject( pOldPen );

	CPen pen2;
	if( bRaised )	pen2.CreatePen( PS_SOLID, 1, RGB( 128, 128, 128 ) );
	else			pen2.CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
	CPen* pOldPen2 = pDC->SelectObject( &pen2 );

	for( loop=0; loop<=nStep; loop++ )
	{
		pDC->MoveTo( GetRect().left + (nBorder+loop),	GetRect().bottom - (nBorder+(loop+1)) );	// Bottom
		pDC->LineTo( GetRect().right - (nBorder+loop),	GetRect().bottom - (nBorder+(loop+1)) );
		pDC->MoveTo( GetRect().right - (nBorder+(loop+1)), GetRect().top + (nBorder+loop) );	// Right
		pDC->LineTo( GetRect().right - (nBorder+(loop+1)), GetRect().bottom - (nBorder+loop) );
	}
                                                                                                  
	pDC->SelectObject( pOldPen2 );
}

//////////////////////////////////////////////////////////////////////////
// CTextDraw

IMPLEMENT_DYNCREATE( CTextDraw, CObject )

CTextDraw::CTextDraw( )
{
	m_colour = RGB( 0, 0, 0 );
	m_bShadow = FALSE;
	m_text = "";
	m_flags = 0;
	m_bDefaultSize = FALSE;
}

BOOL CTextDraw::Load( CArchive& ar )
{
	WORD wTmp;	CRect tmpRect;	CString strTmp;
	ar >> tmpRect;	SetRect( tmpRect );
	ar >> m_colour;
	ar >> wTmp;	m_logFont.lfHeight	=	wTmp;
	ar >> wTmp;	m_logFont.lfWidth	=	wTmp;
	ar >> wTmp;	m_logFont.lfEscapement	=	wTmp;
	ar >> wTmp;	m_logFont.lfOrientation	=	wTmp;
	ar >> wTmp;	m_logFont.lfWeight	=	wTmp;
	ar >> m_logFont.lfItalic;
	ar >> m_logFont.lfUnderline;
	ar >> m_logFont.lfStrikeOut;
	ar >> m_logFont.lfCharSet;
	ar >> m_logFont.lfOutPrecision;
	ar >> m_logFont.lfClipPrecision;
	ar >> m_logFont.lfQuality;
	ar >> m_logFont.lfPitchAndFamily;
	ar >> strTmp;
	for( int loop=0; loop<=strTmp.GetLength() - 1; loop++ )
		m_logFont.lfFaceName[loop] = strTmp.GetAt( loop );
	m_logFont.lfFaceName[loop] = NULL;
	ar >> wTmp;	m_bShadow = wTmp;
	ar >> m_text;
	ar >> wTmp;	if( (BOOL)wTmp == TRUE )	m_flags = DT_BOTTOM;
	ar >> wTmp;	if( (BOOL)wTmp == TRUE )	m_flags |= DT_CENTER;
	ar >> wTmp;	if( (BOOL)wTmp == TRUE )	m_flags |= DT_LEFT;
	ar >> wTmp;	if( (BOOL)wTmp == TRUE )	m_flags |= DT_NOPREFIX;
	ar >> wTmp;	if( (BOOL)wTmp == TRUE )	m_flags |= DT_RIGHT;
	ar >> wTmp;	if( (BOOL)wTmp == TRUE )	m_flags |= DT_SINGLELINE;
	ar >> wTmp;	if( (BOOL)wTmp == TRUE )	m_flags |= DT_TOP;
	ar >> wTmp;	if( (BOOL)wTmp == TRUE )	m_flags |= DT_WORDBREAK;
	ar >> wTmp;	if( (BOOL)wTmp == TRUE )	m_flags |= DT_VCENTER;
	ar >> wTmp;	m_bDefaultSize = wTmp;
	ar >> wTmp;	// Not used
	ar >> wTmp; // Not used
	return TRUE;
}

void CTextDraw::Draw( CDC* pDC ) const
{
	CRect localRect = GetRect();
	
	CFont font;	font.CreateFontIndirect( &m_logFont );
	CFont* pOldFont = pDC->SelectObject( &font );
	
	if( m_bDefaultSize )	// Calculate the bounding rectangle
		pDC->DrawText( m_text, m_text.GetLength(), localRect, DT_CALCRECT | m_flags );
	
	if( m_bShadow )	// Create shadowed text
	{
		CFont shadowFont;	shadowFont.CreateFontIndirect( &m_logFont );
		CFont* pOldShadowFont = pDC->SelectObject( &shadowFont );
		COLORREF oldTxtClr = pDC->SetTextColor( RGB( 179, 179, 179 ) );
		int oldBkMode = pDC->SetBkMode( TRANSPARENT );
		CRect tmpRect = localRect;	tmpRect.OffsetRect( CPoint( 10, 10 ) );
		pDC->DrawText( m_text, m_text.GetLength(), tmpRect, m_flags );
		pDC->SelectObject( pOldShadowFont );
		pDC->SetTextColor( oldTxtClr );
		pDC->SetBkMode( oldBkMode );
	}

	COLORREF oldTxtClr = pDC->SetTextColor( m_colour );
	int oldBkMode = pDC->SetBkMode( TRANSPARENT );
	pDC->DrawText( m_text, m_text.GetLength(), localRect, m_flags );
	pDC->SelectObject( pOldFont );
	pDC->SetTextColor( oldTxtClr );
	pDC->SetBkMode( oldBkMode );
}
