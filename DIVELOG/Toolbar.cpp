// toolbar.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "toolbar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLSToolBar

CLSToolBar::CLSToolBar()
{
	m_bActive = FALSE;
	m_bMouse = FALSE;
	m_pTipDlg = NULL;
	m_bTipActive = FALSE;
	m_bLeftBDown = FALSE;
	m_bDisplayTips = AfxGetApp()->GetProfileInt( "ToolTips", "Display", TRUE );
	int r, g, b;
	r = AfxGetApp()->GetProfileInt( "ToolTips", "TextRColour", 0 );
	g = AfxGetApp()->GetProfileInt( "ToolTips", "TextGColour", 0 );
	b = AfxGetApp()->GetProfileInt( "ToolTips", "TextBColour", 0 );
	m_textColor = RGB( r, g, b );        
	r = AfxGetApp()->GetProfileInt( "ToolTips", "FillRColour", 255 );
	g = AfxGetApp()->GetProfileInt( "ToolTips", "FillGColour", 255 );
	b = AfxGetApp()->GetProfileInt( "ToolTips", "FillBColour", 128 );
	m_fillColor = RGB( r, g, b );
	m_time = AfxGetApp()->GetProfileInt( "ToolTips", "Time", 1 );
	m_logFont.lfHeight = AfxGetApp()->GetProfileInt( "ToolTips", "Height",	-10 );
	m_logFont.lfWidth = AfxGetApp()->GetProfileInt( "ToolTips", "Width",	0 );
	m_logFont.lfEscapement = AfxGetApp()->GetProfileInt( "ToolTips", "Escapement",	0 );
	m_logFont.lfOrientation = AfxGetApp()->GetProfileInt( "ToolTips", "Orientation",	0 );
	m_logFont.lfWeight = AfxGetApp()->GetProfileInt( "ToolTips", "Weight",	100 );
	m_logFont.lfItalic = AfxGetApp()->GetProfileInt( "ToolTips", "Italic",	FALSE );
	m_logFont.lfUnderline = AfxGetApp()->GetProfileInt( "ToolTips", "Underline",	FALSE );
	m_logFont.lfStrikeOut = AfxGetApp()->GetProfileInt( "ToolTips", "StrikeOut",	FALSE );
	m_logFont.lfCharSet = AfxGetApp()->GetProfileInt( "ToolTips", "CharSet",	0 );
	m_logFont.lfOutPrecision = AfxGetApp()->GetProfileInt( "ToolTips", "OutPrecision",	3 );
	m_logFont.lfClipPrecision = AfxGetApp()->GetProfileInt( "ToolTips", "ClipPrecision",	2 );
	m_logFont.lfQuality = AfxGetApp()->GetProfileInt( "ToolTips", "Quality",	1 );
	m_logFont.lfPitchAndFamily = AfxGetApp()->GetProfileInt( "ToolTips", "PitchAndFamily",	34 );
	CString tmpStr = AfxGetApp()->GetProfileString( "ToolTips", "FaceName",	"MS Sans Serif" );
		
	for( int loop=0; loop<=tmpStr.GetLength()-1; loop++ )
		m_logFont.lfFaceName[loop] = tmpStr.GetAt(loop);
	m_logFont.lfFaceName[loop]=NULL;
}

CLSToolBar::~CLSToolBar()
{
}

BEGIN_MESSAGE_MAP(CLSToolBar, CToolBar)
	//{{AFX_MSG_MAP(CLSToolBar)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSToolBar message handlers

void CLSToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_bLeftBDown || !m_bDisplayTips )
	{
		CToolBar::OnMouseMove(nFlags, point);
		return;
	}
		
	CRect wndRect;	GetWindowRect( wndRect );
	point.x += wndRect.left;	point.y += wndRect.top;

	if( wndRect.PtInRect( point ) && !m_bMouse )
	{
		m_bMouse = TRUE;
		SetCapture();
	}
	else if( !wndRect.PtInRect( point ) && m_bMouse )
	{
		m_bMouse = FALSE;
		ReleaseCapture();
		if( m_bTipActive )
		{
			m_pTipDlg->DestroyWindow();
			delete m_pTipDlg;
			m_bTipActive = FALSE;
		}
	}
	else if( m_bMouse )
	{   
		// Get the text for the button the mouse is over
		CPoint actual = point;
		actual.x -= wndRect.left;	actual.y -= wndRect.top;
		if( actual.x > 9 || actual.y > 3 || actual.y < 24 )
		{
		 	CRect rect;
			for( int loop=0; loop<=m_nButtons-1; loop++ )
			{
				GetItemRect( loop, rect );
				if( rect.PtInRect( actual ) )
				{
					if( loop > m_pTips->GetUpperBound() )
						m_text = "";
					else
					{
						m_text = m_pTips->GetAt( loop );
					}
					m_tipWndPos = CRect( actual.x-5, actual.y+15, 50, 15 );
					break;
				}
				else
					m_text = "";
			}

			if( m_bTipActive && m_displayedText!=m_text )
			{
				DisplayTip();
			}
			else if( !m_bActive && m_displayedText!=m_text )
			{
				SetTimer( 9, (1000*m_time), NULL );
				m_bActive = TRUE;
			}
		}
	}

	CToolBar::OnMouseMove(nFlags, point);
}

void CLSToolBar::OnTimer(UINT nIDEvent)
{
	KillTimer( 9 );
	DisplayTip();	
	m_bActive = FALSE;
	CToolBar::OnTimer(nIDEvent);
}

void CLSToolBar::DisplayTip()
{
	if( m_bTipActive )
	{
		m_pTipDlg->DestroyWindow();
		delete m_pTipDlg;
		m_bTipActive = FALSE;
	}
	
	if( m_bMouse && m_bTipActive == FALSE )	
	{
		m_pTipDlg = new CTipDlg;
		
		CPaintDC dc( m_pTipDlg );
	
		CFont* pFont = new CFont;	// font is delete when tip window is destroyed
		pFont->CreateFontIndirect( &m_logFont );
		
		CFont* pOldFont = dc.SelectObject( pFont );
	
		CRect size( 10, 10, 10, 10 );
		dc.DrawText( m_text, m_text.GetLength(), size, DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_CALCRECT );
	
		dc.SelectObject( pOldFont );
		
		m_tipWndPos.right = size.Width();
		m_tipWndPos.bottom = size.Height();
		
		m_tipWndPos.InflateRect( 5, 10 );
		m_tipWndPos.top += 10;
		//m_tipWndPos.bottom += 10;
				
		m_pTipDlg->SetWindowPos( NULL, m_tipWndPos.left, m_tipWndPos.top,
								m_tipWndPos.right, m_tipWndPos.bottom, SWP_NOZORDER|SWP_NOACTIVATE );
		m_pTipDlg->m_pos = m_tipWndPos;
		m_pTipDlg->m_text = m_text;
		m_displayedText = m_text;
		m_pTipDlg->m_textColor = m_textColor;
		m_pTipDlg->m_fillColor = m_fillColor;
		m_pTipDlg->m_pFont = pFont;

		if( m_text!="" )
			m_pTipDlg->ShowWindow( SW_SHOW );
		TRACE( "Displayed Tip!\n" );
		m_bTipActive = TRUE;
	}
}

void CLSToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bMouse = FALSE;
	ReleaseCapture();
	if( m_bTipActive )
	{
		m_pTipDlg->DestroyWindow();
		delete m_pTipDlg;
		m_bTipActive = FALSE;
    }
	m_bLeftBDown = TRUE;
	CToolBar::OnLButtonDown(nFlags, point);
}          

void CLSToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLeftBDown = FALSE;
	m_displayedText = "";

	CToolBar::OnLButtonUp(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CTipDlg dialog


CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTipDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//Create( CTipDlg::IDD, pParent );
	Create( IDD_TOOLTIP, pParent );
}

CTipDlg::~CTipDlg()
{
	delete m_pFont;
	DestroyWindow();
}

void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTipDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTipDlg, CDialog)
	//{{AFX_MSG_MAP(CTipDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTipDlg message handlers


void CTipDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CBrush brush;
	brush.CreateSolidBrush( m_fillColor );

	CBrush* pOldBrush = dc.SelectObject( &brush );
	CFont* pOldFont = dc.SelectObject( m_pFont );
	int nOldBkMode = dc.SetBkMode( TRANSPARENT );
	COLORREF oldTxtCol = dc.SetTextColor( m_textColor );
	
	dc.Rectangle( CRect( 0, 0, m_pos.right, m_pos.bottom ) );
	dc.DrawText( m_text, m_text.GetLength(), CRect( 0, 0, m_pos.right, m_pos.bottom ),
															 DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	
	dc.SetTextColor( oldTxtCol );
	dc.SetBkMode( nOldBkMode );
	dc.SelectObject( pOldFont );
	dc.SelectObject( pOldBrush );
	
	// Do not call CDialog::OnPaint() for painting messages
}


void CLSToolBar::OnRButtonUp(UINT nFlags, CPoint point)
{
	// Destroy a tool tip window if one exists
	m_bMouse = FALSE;
	ReleaseCapture();
	if( m_bTipActive )
	{
		m_pTipDlg->DestroyWindow();
		delete m_pTipDlg;
		m_bTipActive = FALSE;
    }

	CRect wndRect;	GetWindowRect( wndRect );
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu( MF_STRING, ID_VIEW_TOOLBAR, "Hide\0" );
	menu.AppendMenu( MF_STRING, ID_TOOLBAR_PROP, "Properties\0" );
	menu.TrackPopupMenu( TPM_LEFTALIGN|TPM_RIGHTBUTTON,
											point.x + wndRect.left, point.y + wndRect.top, this );
	CToolBar::OnRButtonUp(nFlags, point);
}

void CLSToolBar::ShowProperties()
{
	CToolBarPropDlg dlg;
	
	dlg.m_bShow = IsWindowVisible();
	dlg.m_textColor = m_textColor;
	dlg.m_fillColor = m_fillColor;
	dlg.m_bTips = m_bDisplayTips;
	dlg.m_logFont = m_logFont;
	dlg.m_time = m_time;
		
	if( dlg.DoModal()==IDOK )
	{
		if( IsWindowVisible()!=dlg.m_bShow )
			::SendMessage( AfxGetMainWnd()->GetSafeHwnd(), WM_COMMAND, ID_VIEW_TOOLBAR, 0 );
		m_textColor = dlg.m_textColor;
		m_fillColor = dlg.m_fillColor;
		m_bDisplayTips = dlg.m_bTips;
		m_logFont = dlg.m_logFont;
		m_time = dlg.m_time;

		AfxGetApp()->WriteProfileInt( "ToolTips", "Time", m_time );
		AfxGetApp()->WriteProfileInt( "ToolTips", "Display", m_bDisplayTips );
		AfxGetApp()->WriteProfileInt( "ToolTips", "TextRColour", GetRValue( m_textColor ) );
		AfxGetApp()->WriteProfileInt( "ToolTips", "TextGColour", GetGValue( m_textColor ) );
		AfxGetApp()->WriteProfileInt( "ToolTips", "TextBColour", GetBValue( m_textColor ) );
		AfxGetApp()->WriteProfileInt( "ToolTips", "FillRColour", GetRValue( m_fillColor ) );
		AfxGetApp()->WriteProfileInt( "ToolTips", "FillGColour", GetGValue( m_fillColor ) );
		AfxGetApp()->WriteProfileInt( "ToolTips", "FillBColour", GetBValue( m_fillColor ) );
		AfxGetApp()->WriteProfileInt( "ToolTips", "Height",	m_logFont.lfHeight );
		AfxGetApp()->WriteProfileInt( "ToolTips", "Width",	m_logFont.lfWidth );
		AfxGetApp()->WriteProfileInt( "ToolTips", "Escapement",	m_logFont.lfEscapement );
		AfxGetApp()->WriteProfileInt( "ToolTips", "Orientation",	m_logFont.lfOrientation );
		AfxGetApp()->WriteProfileInt( "ToolTips", "Weight",	m_logFont.lfWeight );
		AfxGetApp()->WriteProfileInt( "ToolTips", "Italic",	m_logFont.lfItalic );
		AfxGetApp()->WriteProfileInt( "ToolTips", "Underline",	m_logFont.lfUnderline );
		AfxGetApp()->WriteProfileInt( "ToolTips", "StrikeOut",	m_logFont.lfStrikeOut );
		AfxGetApp()->WriteProfileInt( "ToolTips", "CharSet",	m_logFont.lfCharSet );
		AfxGetApp()->WriteProfileInt( "ToolTips", "OutPrecision",	m_logFont.lfOutPrecision );
		AfxGetApp()->WriteProfileInt( "ToolTips", "ClipPrecision",	m_logFont.lfClipPrecision );
		AfxGetApp()->WriteProfileInt( "ToolTips", "Quality",	m_logFont.lfQuality );
		AfxGetApp()->WriteProfileInt( "ToolTips", "PitchAndFamily",	m_logFont.lfPitchAndFamily );
		AfxGetApp()->WriteProfileString( "ToolTips", "FaceName",	m_logFont.lfFaceName );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarPropDlg dialog


CToolBarPropDlg::CToolBarPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolBarPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolBarPropDlg)
	m_bShow = FALSE;
	m_time = 0;
	m_bTips = FALSE;
	//}}AFX_DATA_INIT
}

void CToolBarPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolBarPropDlg)
	DDX_Check(pDX, IDC_SHOW, m_bShow);
	DDX_Text(pDX, IDC_TIME, m_time);
	DDV_MinMaxInt(pDX, m_time, 0, 32676);
	DDX_Check(pDX, IDC_TOOLTIPS, m_bTips);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CToolBarPropDlg, CDialog)
	//{{AFX_MSG_MAP(CToolBarPropDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SETFILLCOLOR, OnSetfillcolor)
	ON_BN_CLICKED(IDC_SETTEXTCOLOR, OnSettextcolor)
	ON_BN_CLICKED(IDC_FONT, OnFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CToolBarPropDlg message handlers

BOOL CToolBarPropDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CToolBarPropDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CWnd* pTextWnd = GetDlgItem( IDC_SAMPLE_TEXT );
	CDC* pTextDC = pTextWnd->GetDC();
	pTextWnd->Invalidate( );
	pTextWnd->UpdateWindow();
    
	CPen pen;
	pen.CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	
	CBrush brush;
	brush.CreateSolidBrush( m_textColor );

	CPen* pOldPen = pTextDC->SelectObject( &pen );
	CBrush* pOldBrush = pTextDC->SelectObject( &brush );
	pTextDC->Rectangle( 0, 0, 15, 15 );
	pTextDC->SelectObject( pOldPen );
	pTextDC->SelectObject( pOldBrush );
	pTextWnd->ReleaseDC( pTextDC );
	
    CWnd* pBrushWnd = GetDlgItem( IDC_SAMPLE_FILL );
	CDC* pBrushDC = pBrushWnd->GetDC();
	pBrushWnd->Invalidate( );
	pBrushWnd->UpdateWindow();

	CBrush brush2;
	brush2.CreateSolidBrush( m_fillColor );

	pOldPen = pBrushDC->SelectObject( &pen );
	pOldBrush = pBrushDC->SelectObject( &brush2 );
	pBrushDC->Rectangle( 0, 0, 15, 15 );
	pBrushDC->SelectObject( pOldPen );
	pBrushDC->SelectObject( pOldBrush );
	pBrushWnd->ReleaseDC( pBrushDC );

	// Do not call CDialog::OnPaint() for painting messages
}

void CToolBarPropDlg::OnSetfillcolor()
{
	CColorDialog dlg( m_fillColor );
	
	if( dlg.DoModal()==IDOK )
		m_fillColor = dlg.GetColor();
	OnPaint();
}

void CToolBarPropDlg::OnSettextcolor()
{
	CColorDialog dlg( m_textColor );
	
	if( dlg.DoModal()==IDOK )
		m_textColor = dlg.GetColor();
	OnPaint();
}

void CToolBarPropDlg::OnFont()
{
	CFontDialog dlg( &m_logFont );
	
	dlg.m_cf.rgbColors = m_textColor;	
	if( !dlg.DoModal() )
		return;
		
	m_textColor = dlg.GetColor();
	m_logFont.lfHeight		=	dlg.m_lf.lfHeight;
	m_logFont.lfWidth		=	dlg.m_lf.lfWidth;
	m_logFont.lfEscapement	=	dlg.m_lf.lfEscapement;
	m_logFont.lfOrientation	=	dlg.m_lf.lfOrientation;       
	m_logFont.lfWeight		=	dlg.m_lf.lfWeight;
	m_logFont.lfItalic		=	dlg.m_lf.lfItalic;
	m_logFont.lfUnderline	=	dlg.m_lf.lfUnderline;
	m_logFont.lfStrikeOut	=	dlg.m_lf.lfStrikeOut;
	m_logFont.lfCharSet		=	dlg.m_lf.lfCharSet;
	m_logFont.lfOutPrecision	=	dlg.m_lf.lfOutPrecision;
	m_logFont.lfClipPrecision	=	dlg.m_lf.lfClipPrecision; 
	m_logFont.lfQuality			=	dlg.m_lf.lfQuality;
	m_logFont.lfPitchAndFamily	=	dlg.m_lf.lfPitchAndFamily;
	for( int loop=0; loop<=dlg.GetFaceName().GetLength()-1; loop++ )
		m_logFont.lfFaceName[loop] = dlg.GetFaceName().GetAt(loop);
	m_logFont.lfFaceName[loop]=NULL;
	OnPaint();
}
