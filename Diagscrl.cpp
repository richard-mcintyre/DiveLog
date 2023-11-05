//---------------------------------------------------------------------------
// Plumber Custom Control Pack 1                                     05/08/94
//
//	You may use the source code contained in this control pack freely in your
//	applications.  You may not give/share/sell the source code in any way,
//	modified or unmodified.  By using the source code, you agree that there
//	are no warranties, either expressed or implied associated with it 
//	(including, but not limited to warranties of merchantability and 
//	fitness for a particular purpose).					-- rpg     71101,1063
//---------------------------------------------------------------------------

#include "stdafx.h"

#include "DiagScrl.h"

//----- Control state flags.
#define PPDS_STATE_GRAYED      0x0001
#define PPDS_STATE_HIDDEN      0x0002
#define PPDS_STATE_MOUSEOUT    0x0004
#define PPDS_STATE_UPCLICK     0x0008
#define PPDS_STATE_DOWNCLICK   0x0010
//----- Combination of click states.
#define PPDS_STATE_CLICKED     (PPDS_STATE_UPCLICK | PPDS_STATE_DOWNCLICK)
//----- Combination of state flags.
#define PPDS_STATE_ALL         0x001F

//----- Timer identifiers.
#define IDT_FIRSTCLICK      500
#define IDT_HOLDCLICK       501

#define CTICKS_FIRSTCLICK   400
#define CTICKS_HOLDCLICK    50

static CString DSWndClassName;


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////

CDiagScroll::CDiagScroll ()
{
	m_wState  = 0;
	m_dwStyle = 0;
	
	m_pWndAssociate = NULL;
}

CDiagScroll::~CDiagScroll()
{
}

BEGIN_MESSAGE_MAP(CDiagScroll, CWnd)
	//{{AFX_MSG_MAP(CDiagScroll)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	ON_WM_SHOWWINDOW()
	ON_WM_CANCELMODE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDiagScroll::CalcClickedRgn (CRect& Rect, CRgn& Rgn)
{
	short       cx, cy;
	
	CPoint		Points [4];

	GetClientRect (&Rect);

	cx = ((short)Rect.right  - (short)Rect.left);
	cy = ((short)Rect.bottom - (short)Rect.top);
	
	if (StateTest (PPDS_STATE_DOWNCLICK))
	{
		Points[0].x = 0;
		Points[0].y = cy;
		Points[1].x = cx;
		Points[1].y = 0;
		Points[2].x = cx;
		Points[2].y = cy;          
		Points[3].x = 0;
		Points[3].y = cy;

		Rgn.CreatePolygonRgn (Points, 3, WINDING);
	}
	
	if (StateTest (PPDS_STATE_UPCLICK))
	{
		Points[0].x = 0;
		Points[0].y = cy;
		Points[1].x = 0;
		Points[1].y = 0;
		Points[2].x = cx;
		Points[2].y = 0;          
		Points[3].x = 0;
		Points[3].y = cy;

		Rgn.CreatePolygonRgn (Points, 3, WINDING);
	}	
}

BOOL CDiagScroll::Create (DWORD dwStyle, CRect& Rect, CWnd* pParent, UINT nID)
{
	if (DSWndClassName.GetLength() == 0)
	 	DSWndClassName = AfxRegisterWndClass (CS_GLOBALCLASS 	| CS_HREDRAW 	| 
	 										   CS_VREDRAW 		| CS_DBLCLKS,
	 										   ::LoadCursor (NULL, IDC_ARROW));

	return CWnd::Create (DSWndClassName, NULL, dwStyle, Rect, pParent, nID);
}

void CDiagScroll::DrawLowerTriangle (CDC* pDC, CPen* pPenHigh, CPen* pPenShadow, BOOL fClicked)
{        
	CRect	Rect;
	CPen*	pOldPen;
	
	pOldPen = pDC->SelectObject (pPenShadow);

	GetClientRect (&Rect);
	
	if (fClicked)
	{
		//----- Diagonal line (shadow)
		pDC->MoveTo (Rect.left  + 2, Rect.bottom - 2);
		pDC->LineTo (Rect.right - 1, Rect.top    + 1);
	} else
	{
		//----- Lower and Right lines of triangle (shadow)
		pDC->MoveTo (Rect.left  + 1, Rect.bottom - 1);
		pDC->LineTo (Rect.right - 1, Rect.bottom - 1);
		pDC->LineTo (Rect.right - 1, Rect.top);

		pDC->SelectObject (pPenHigh);
		
		//----- Diagonal line (highlighted)
		pDC->MoveTo (Rect.left  + 1, Rect.bottom - 1);
		pDC->LineTo (Rect.right - 1, Rect.top + 1);
	}
	
	pDC->SelectObject (pOldPen);
}

void CDiagScroll::DrawUpperTriangle (CDC* pDC, CPen* pPenHigh, CPen* pPenShadow, BOOL fClicked)
{
	CRect 	Rect;
		
	CPen*	pOldPen;
	
	pOldPen = pDC->SelectObject (pPenShadow);
	
	GetClientRect (&Rect);
	
	if (fClicked)
	{
		//----- Left and Upper lines of triangle (shadow)
		pDC->MoveTo (Rect.left,      Rect.bottom - 2);
		pDC->LineTo (Rect.left,      Rect.top);
		pDC->LineTo (Rect.right - 1, Rect.top);
	} else
	{
		//----- Diagonal line (shadow)
		pDC->MoveTo (Rect.left,      Rect.bottom - 2);
		pDC->LineTo (Rect.right - 1, Rect.top    - 1);
		
		pDC->SelectObject (pPenHigh);
		
		//----- Left and Upper lines of triangle (highlighted)
		pDC->MoveTo (Rect.left,      Rect.bottom - 3);
		pDC->LineTo (Rect.left,      Rect.top);
		pDC->LineTo (Rect.right - 2, Rect.top);
	}
	
	pDC->SelectObject (pOldPen);    
}

WNDPROC* CDiagScroll::GetSuperWndProcAddr()
{
	static WNDPROC NEAR pfnSuper;
	
	return &pfnSuper;
}

void CDiagScroll::Notify (UINT Msg)
{
	if (m_pWndAssociate->GetSafeHwnd() != NULL)
		m_pWndAssociate->SendMessage (Msg, (WPARAM) m_hWnd);
}

void CDiagScroll::OnCancelMode()
{
//	CWnd::OnCancelMode();
	
	StateClear (PPDS_STATE_DOWNCLICK | PPDS_STATE_UPCLICK | PPDS_STATE_MOUSEOUT);

	KillTimer (IDT_FIRSTCLICK);
	KillTimer (IDT_HOLDCLICK);

	ReleaseCapture();
}

int CDiagScroll::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//----- Our associate is the parent by default.
#ifdef WIN32
	m_pWndAssociate = FromHandle ((HWND) ::GetWindowLong (GetSafeHwnd(), GWL_HWNDPARENT));
#else
	m_pWndAssociate = FromHandle ((HWND) ::GetWindowWord (GetSafeHwnd(), GWW_HWNDPARENT));
#endif
	
	//----- Copy styles
	m_dwStyle  = lpCreateStruct->style;

	ASSERT ((PPDS_VERTICAL & m_dwStyle) || (PPDS_HORIZONTAL & m_dwStyle));

	//----- check for autosize
    if (m_dwStyle & PPDS_AUTOSIZE)
		SetWindowPos (&wndTop, 0, 0, 
					  lpCreateStruct->cy, 		// width == Height
					  lpCreateStruct->cy, 			
					  SWP_NOMOVE | SWP_NOZORDER);
    
	//----- Clear out all initial states.
	StateClear (PPDS_STATE_ALL);
		
	return 0;
}

void CDiagScroll::OnEnable(BOOL bEnable)
{
//	CWnd::OnEnable(bEnable);
	
	if (bEnable)
		StateClear (PPDS_STATE_GRAYED);
	else
		StateSet (PPDS_STATE_GRAYED);
	
	//----- Force a repaint since the control will look different.
	InvalidateRect (NULL, TRUE);
	UpdateWindow   ();
}

BOOL CDiagScroll::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;		
	
//	return CWnd::OnEraseBkgnd(pDC);
}

void CDiagScroll::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnLButtonDown (nFlags, point);
	
//	CWnd::OnLButtonDblClk(nFlags, point);
}

void CDiagScroll::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect 	Rect;
	CRgn 	Rgn;
	
	//----- Get the mouse coordinates.
	int x = point.x;
	int y = point.y;
	
	//----- Only need to hit-test the upper half
	GetClientRect (&Rect);
	
	int cx = Rect.right - Rect.left;
	
	//----- assumes rect is a square
	WORD wState = (x <= (cx - y)) ? PPDS_STATE_UPCLICK : PPDS_STATE_DOWNCLICK;
				
	//----- Change state and repaint
	StateClear (PPDS_STATE_DOWNCLICK | PPDS_STATE_UPCLICK);
	StateSet   (wState);
	
	CalcClickedRgn (Rect, Rgn);
	InvalidateRgn  (&Rgn, TRUE);
				
	UpdateWindow   ();
	
	PositionChange ();
	
	SetCapture ();
	
	SetTimer (IDT_FIRSTCLICK, CTICKS_FIRSTCLICK, NULL);

//	CWnd::OnLButtonDown(nFlags, point);
}

void CDiagScroll::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect Rect;
	CRgn  Rgn;
	
	KillTimer (IDT_FIRSTCLICK);
	KillTimer (IDT_HOLDCLICK);
				
	ReleaseCapture ();
				
	if (StateTest (PPDS_STATE_CLICKED) && !StateTest (PPDS_STATE_MOUSEOUT))
	{
		//----- Calculate the rectangle before clearing states.
		CalcClickedRgn (Rect, Rgn);
				
		//----- Clear the states so we repaint properly.
		StateClear (PPDS_STATE_MOUSEOUT);
		StateClear (PPDS_STATE_CLICKED);
				
		InvalidateRgn (&Rgn, TRUE);
		UpdateWindow  ();
	}
	
	//----- Insure that we clear out the states.
	StateClear (PPDS_STATE_MOUSEOUT);
	StateClear (PPDS_STATE_CLICKED);

//	CWnd::OnLButtonUp(nFlags, point);
}

void CDiagScroll::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect Rect;
	CRgn  Rgn;
	
	if (!StateTest (PPDS_STATE_CLICKED))
		return;
				
	//----- Get the area we originally clicked and the new POINT
	CalcClickedRgn (Rect, Rgn);
				
	WORD wState = m_wState;
				
	//----- Hit-Test the rectange and change the state if necessary.
	if (Rgn.PtInRegion (point))
		StateClear (PPDS_STATE_MOUSEOUT);
	else
		StateSet (PPDS_STATE_MOUSEOUT);
				
	// If the state changed, repaint the appropriate part of the control.
	if (wState != m_wState)
	{
		InvalidateRgn (&Rgn, TRUE);
		UpdateWindow  ();
	}
		
//	CWnd::OnMouseMove(nFlags, point);
}

void CDiagScroll::OnPaint()
{
	CPaintDC dc (this); // device context for painting
	
	CRect		Rect;

	CPoint		TopArrow    [3];	
	CPoint		BottomArrow [3];    
	
    WORD        xAdd1 = 0;
    WORD		yAdd1 = 0;
    WORD        xAdd2 = 0;
    WORD		yAdd2 = 0;

    WORD        cx,  cy;    					// Whole dimensions
    WORD        cx2, cy2;   					// Half dimensions
    WORD        cx4, cy4;   					// Quarter dimensions

	COLORREF 	ColorFace;
	COLORREF	ColorText;
	COLORREF	ColorShadow;
	COLORREF	ColorHighlight;

	CPen		PenFace;
	CPen		PenText;
	CPen		PenShadow;
	CPen		PenHighlight;
	CPen*		pOldPen;
    
    CBrush		BrushArrow;
    CBrush		BrushFace;
    CBrush		BrushBlack;
	CBrush*		pOldBrush;
	                                                   
                                                   
    GetClientRect (&Rect);						// get the control's dimensions

	ColorFace 	 	= ::GetSysColor (COLOR_BTNFACE);
	ColorText	 	= ::GetSysColor (COLOR_BTNTEXT);
	ColorShadow		= ::GetSysColor (COLOR_BTNSHADOW);
	ColorHighlight 	= ::GetSysColor (COLOR_BTNHIGHLIGHT);

	PenFace.CreatePen (PS_SOLID, 1, ColorFace);
	PenText.CreatePen (PS_SOLID, 1, ColorText);
	PenShadow.CreatePen (PS_SOLID, 1, ColorShadow);
	PenHighlight.CreatePen (PS_SOLID, 1, ColorHighlight);
	
	BrushFace.CreateSolidBrush (ColorFace);
	BrushArrow.CreateSolidBrush (ColorText);
	BrushBlack.FromHandle ((HBRUSH) ::GetStockObject (BLACK_BRUSH));

    cx  = ((WORD)Rect.right  - (WORD)Rect.left);
    cy 	= ((WORD)Rect.bottom - (WORD)Rect.top);
    cx2 = cx  >> 1;
    cy2 = cy  >> 1;
    cx4 = cx2 >> 1;
    cy4 = cy2 >> 1;

	if (!StateTest (PPDS_STATE_MOUSEOUT))
	{
		if (StateTest (PPDS_STATE_UPCLICK))
		{
			xAdd1=1;
			yAdd1=1;
		}
	
		if (StateTest (PPDS_STATE_DOWNCLICK))
		{
			xAdd2=1;
			yAdd2=1;
		}
	}

    pOldBrush = dc.SelectObject (&BrushFace);
    pOldPen   = dc.SelectObject (&PenFace);

	dc.Rectangle (&Rect);

	//----- Draw diagonal line
	dc.SelectObject (&PenText);
	dc.MoveTo (cx - 1, 0);
	dc.LineTo (    -1, cy);

	DrawUpperTriangle (&dc, &PenHighlight, &PenShadow, xAdd1);
	DrawLowerTriangle (&dc, &PenHighlight, &PenShadow, xAdd2);

    //----- Select default line color.
    dc.SelectObject (&PenText);

    //----- Draw the arrows depending on the enable state.
    if (StateTest (PPDS_STATE_GRAYED))
	{
		int cx3  = cx / 3 - 1;
		int cx23 = (cx * 2) / 3;

		if (PPDS_VERTICAL & m_dwStyle)
		{
			dc.MoveTo (cx3,     cy4 - 2);      	// Top arrow
			dc.LineTo (cx3 - 3, cy4 + 1);
			
			dc.MoveTo (cx23 - 3, cy2 + cy4 - 2);// Bottom arrow
			dc.LineTo (cx23 + 3, cy2 + cy4 - 2);
			
			dc.SelectObject (&PenHighlight);
			dc.MoveTo		(cx3 - 3, cy4 + 1);    		// Top arrow
			dc.LineTo		(cx3 + 3, cy4 + 1);
			dc.MoveTo		(cx23 + 3, cy2 + cy4 - 2);  // Bottom arrow
			dc.LineTo		(cx23,     cy2 + cy4 + 1);
			dc.SetPixel		(cx23,     cy2 + cy4 + 1, ColorHighlight);
		} else
		{
			dc.MoveTo (cx3 - 2, cy4);        // Left arrow
			dc.LineTo (cx3 + 1, cy4 - 3);   
			
			dc.MoveTo (cx23 - 2, cy2 + cy4 - 3);    // Right arrow
			dc.LineTo (cx23 - 2, cy2 + cy4 + 3);
			
			dc.SelectObject (&PenHighlight);
			dc.MoveTo (cx3 + 1, cy4 - 3);		// Left arrow
			dc.LineTo (cx3 + 1, cy4 + 3); 
			
			dc.MoveTo (cx23 + 1, cy2 + cy4);		// right arrow
			dc.LineTo (cx23 - 2, cy2 + cy4 + 3);
 		}		
	} else
	{
		int cx3  = cx / 3;
		int cx23 = (cx * 2) / 3;
		
		if (PPDS_VERTICAL & m_dwStyle)
		{
			//----- Top arrow polygon (facing up)
			TopArrow[0].x = xAdd1 + cx3 - 1;
			TopArrow[0].y = yAdd1 + cy4 - 2;
			TopArrow[1].x = xAdd1 + cx3 - 4;
			TopArrow[1].y = yAdd1 + cy4 + 1;
			TopArrow[2].x = xAdd1 + cx3 + 2;
			TopArrow[2].y = yAdd1 + cy4 + 1;
			
			//----- Bottom arrow polygon (facing down)
			BottomArrow[0].x = xAdd2 + cx23;
			BottomArrow[0].y = yAdd2 + cy2  + cy4 + 1;
			BottomArrow[1].x = xAdd2 + cx23 - 3;
			BottomArrow[1].y = yAdd2 + cy2  + cy4 - 2;
			BottomArrow[2].x = xAdd2 + cx23 + 3;
			BottomArrow[2].y = yAdd2 + cy2  + cy4 - 2;
		} else
		{
			//----- Top arrow polygon (facing left)
			TopArrow[0].x = xAdd1 + cx3 - 1;
			TopArrow[0].y = yAdd1 + cy4 - 2;
			TopArrow[1].x = xAdd1 + cx3 - 1;
			TopArrow[1].y = yAdd1 + cy4 + 4;
			TopArrow[2].x = xAdd1 + cx3 - 4;
			TopArrow[2].y = yAdd1 + cy4 + 1;
			
			//----- Bottom arrow polygon (facing right)
			BottomArrow[0].x = xAdd2 + cx23 - 1;
			BottomArrow[0].y = yAdd2 + cy2  + cy4 - 4;
			BottomArrow[1].x = xAdd2 + cx23 + 2;
			BottomArrow[1].y = yAdd2 + cy2  + cy4 - 1;
			BottomArrow[2].x = xAdd2 + cx23 - 1;
			BottomArrow[2].y = yAdd2 + cy2  + cy4 + 2;
		}

		//----- Draw the arrows
		dc.SelectObject (&BrushArrow);
		dc.Polygon		(TopArrow,    3);
		dc.Polygon		(BottomArrow, 3);
	}

	//----- Clean up
    dc.SelectObject (pOldBrush);
    dc.SelectObject (pOldPen);

	PenFace.DeleteObject ();
	PenText.DeleteObject ();
	PenShadow.DeleteObject ();
	PenHighlight.DeleteObject ();
    
    BrushArrow.DeleteObject ();
    BrushFace.DeleteObject ();
    BrushBlack.DeleteObject ();
}

void CDiagScroll::OnShowWindow(BOOL bShow, UINT nStatus)
{
//	CWnd::OnShowWindow(bShow, nStatus);
	
	// Set or clear the hidden flag. Windows will automatically force a 
	// repaint if we become visible.
	if (bShow)
		StateClear (PPDS_STATE_HIDDEN);
	else
		StateSet (PPDS_STATE_HIDDEN);
}

void CDiagScroll::OnTimer(UINT nIDEvent)
{
	// We run two timers:  the first is the initial delay after the first 
	// click before we begin repeating, the second is the repeat rate.
	if (nIDEvent == IDT_FIRSTCLICK)
	{
		KillTimer (nIDEvent);
		SetTimer  (IDT_HOLDCLICK, CTICKS_HOLDCLICK, NULL);
	}
	
	// Send a new scroll message if the mouse is still in the originally clicked area.
	if (!StateTest (PPDS_STATE_MOUSEOUT))
		PositionChange ();

//	CWnd::OnTimer(nIDEvent);
}
                                   
void CDiagScroll::PositionChange ()
{
	WORD         wScrollMsg;
	WORD         wScrollCode;
		
	if (StateTest (PPDS_STATE_UPCLICK))
		wScrollCode = SB_LINEUP;
		
	if (StateTest (PPDS_STATE_DOWNCLICK))
		wScrollCode = SB_LINEDOWN;
		
	wScrollMsg = (PPDS_VERTICAL & m_dwStyle) ? WM_VSCROLL : WM_HSCROLL;
		
	if (m_pWndAssociate->GetSafeHwnd() != NULL)
		m_pWndAssociate->SendMessage (wScrollMsg, wScrollCode);
}
                                   
CWnd* CDiagScroll::SetAssociate (CWnd* NewWnd)
{
	ASSERT (::IsWindow (NewWnd->GetSafeHwnd()));

	CWnd* pOldWnd = m_pWndAssociate;
	
	//----- Get our ID value, then send WM_COMMAND notifications.
#ifdef WIN32
	long wID = GetWindowLong (GetSafeHwnd(), GWL_ID);
#else
	WORD wID = GetWindowWord (GetSafeHwnd(), GWW_ID);
#endif

	Notify (PPDS_ASSOCIATELOSS);
	
	m_pWndAssociate = NewWnd;
	
	Notify (PPDS_ASSOCIATEGAIN);
	
	return (pOldWnd);
}

