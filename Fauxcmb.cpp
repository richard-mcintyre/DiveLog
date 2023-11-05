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

#define OEMRESOURCE	// <----- must be defined before windows.h is #included

#include "StdAfx.h"

#include "FauxCmb.h"

//----- Control state flags.
#define PPFC_STATE_GRAYED      0x0001
#define PPFC_STATE_HIDDEN      0x0002
#define PPFC_STATE_MOUSEOUT    0x0004
#define PPFC_STATE_CLICKED     0x0008

//----- Combination of state flags.
#define PPFC_STATE_ALL         0x001F

static CString FCWndClassName;


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////

CFauxCmb::CFauxCmb ()
{
	m_pWndAssociate = NULL;
	
	m_wState  = 0;
	m_dwStyle = 0;
		
	m_DefinedWidth  = 0;
	m_DefinedHeight = 0;
}

CFauxCmb::~CFauxCmb()
{
}

BEGIN_MESSAGE_MAP(CFauxCmb, CWnd)
	//{{AFX_MSG_MAP(CFauxCmb)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	ON_WM_SHOWWINDOW()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CFauxCmb::Create (DWORD dwStyle, CRect& Rect, CWnd* pParent, UINT nID)
{
	if (FCWndClassName.GetLength() == 0)
	 	FCWndClassName = AfxRegisterWndClass (CS_GLOBALCLASS 	| CS_HREDRAW 	| 
	 										   CS_VREDRAW 		| CS_DBLCLKS,
	 										   ::LoadCursor (NULL, IDC_ARROW));

	m_DefinedWidth  = Rect.Width();
	m_DefinedHeight = Rect.Height();

	return CWnd::Create (FCWndClassName, NULL, dwStyle, Rect, pParent, nID);
}

WNDPROC* CFauxCmb::GetSuperWndProcAddr()
{
	static WNDPROC NEAR pfnSuper;
	
	return &pfnSuper;
}

void CFauxCmb::Notify (UINT Msg)
{
	if (m_pWndAssociate->GetSafeHwnd() != NULL)
		m_pWndAssociate->SendMessage (Msg, (WPARAM) m_hWnd);
}

void CFauxCmb::OnCancelMode()
{
//	CWnd::OnCancelMode();
	
	StateClear (PPFC_STATE_CLICKED);

	ReleaseCapture();
}

int CFauxCmb::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//----- make the control the same size as a vertical scroll bar button, or
	//----- the defined size
	int Width  = (m_DefinedWidth  > 0) ? m_DefinedWidth  : ::GetSystemMetrics (SM_CXVSCROLL);
	int Height = (m_DefinedHeight > 0) ? m_DefinedHeight : ::GetSystemMetrics (SM_CYVSCROLL);
	
	SetWindowPos (&wndTop, 0, 0, Width, Height, SWP_NOMOVE | SWP_NOZORDER);
	
	//----- Our associate is the parent by default.
#ifdef WIN32
	m_pWndAssociate = FromHandle ((HWND) ::GetWindowLong (GetSafeHwnd(), GWL_HWNDPARENT));
#else
	m_pWndAssociate = FromHandle ((HWND) ::GetWindowWord (GetSafeHwnd(), GWW_HWNDPARENT));
#endif
	
	//----- Copy styles
	m_dwStyle  = lpCreateStruct->style;
	
	//----- Clear out all initial states.
	StateClear (PPFC_STATE_ALL);
	
	return 0;
}

void CFauxCmb::OnEnable(BOOL bEnable)
{
//	CWnd::OnEnable(bEnable);
	
	if (bEnable)
		StateClear (PPFC_STATE_GRAYED);
	else
		StateSet (PPFC_STATE_GRAYED);
	
	//----- Force a repaint since the control will look different.
	InvalidateRect (NULL, TRUE);
	UpdateWindow   ();
}

BOOL CFauxCmb::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;		
	
//	return CWnd::OnEraseBkgnd(pDC);
}

void CFauxCmb::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnLButtonDown (nFlags, point);
	
//	CWnd::OnLButtonDblClk(nFlags, point);
}

void CFauxCmb::OnLButtonDown(UINT nFlags, CPoint point)
{
	WORD wState = PPFC_STATE_CLICKED;
				
	//----- Change state and repaint
	StateClear (PPFC_STATE_CLICKED);
	StateSet   (wState);
	
	InvalidateRect (NULL, TRUE);
				
	UpdateWindow   ();
	
//	Notify (PPFC_BTNCLICKED);

	SetCapture ();
	
//	CWnd::OnLButtonDown(nFlags, point);
}

void CFauxCmb::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture ();
				
	// Repaint if necessary, only if we are clicked AND the mouse
	// is still in the boundaries of the control.
	if (StateTest (PPFC_STATE_CLICKED) && !StateTest(PPFC_STATE_MOUSEOUT))
	{
		//----- Clear the states so we repaint properly.
		StateClear (PPFC_STATE_MOUSEOUT);
		StateClear (PPFC_STATE_CLICKED);

		InvalidateRect (NULL, TRUE);
		UpdateWindow  ();

		Notify (PPFC_BTNCLICKED);
	} else
	{
		//----- Just Clear the states
		StateClear (PPFC_STATE_MOUSEOUT);
		StateClear (PPFC_STATE_CLICKED);
	}

//	CWnd::OnLButtonUp(nFlags, point);
}

void CFauxCmb::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect Rect;
	
	if (!StateTest (PPFC_STATE_CLICKED))
		return;
				
	//----- Get the area we originally clicked and the new POINT
	GetClientRect (&Rect);
				
	WORD wState = m_wState;
				
	//----- Hit-Test the rectange and change the state if necessary.
	if (Rect.PtInRect (point))
		StateClear (PPFC_STATE_MOUSEOUT);
	else
		StateSet (PPFC_STATE_MOUSEOUT);
				
	// If the state changed, repaint the appropriate part of the control.
	if (wState != m_wState)
	{
		InvalidateRect (NULL, TRUE);
		UpdateWindow  ();
	}
		
//	CWnd::OnMouseMove(nFlags, point);
}

void CFauxCmb::OnPaint()
{
	CPaintDC dc (this); // device context for painting
	
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
	                                                   
	CRect		Rect;
                                                   
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

    cx = ((short)Rect.right  - (short)Rect.left);
	cy = ((short)Rect.bottom - (short)Rect.top);
    cx2 = cx  >> 1;
    cy2 = cy  >> 1;
    cx4 = cx2 >> 1;
    cy4 = cy2 >> 1;


    // If one half is depressed, set the x/yAdd varaibles that we use to shift 
    // the small arrow image down and right.
	if (!StateTest (PPFC_STATE_MOUSEOUT))
		if (StateTest (PPFC_STATE_CLICKED))
		{
			xAdd1=1;
			yAdd1=1;
		}
	

    //----- Draw the face color and the outer frame
    pOldBrush = dc.SelectObject (&BrushFace);
    pOldPen   = dc.SelectObject (&PenText);

    dc.Rectangle (Rect.left, Rect.top, Rect.right, Rect.bottom);

    //----- Draw the arrows depending on the enable state.
    if (StateTest (PPFC_STATE_GRAYED))
	{
	} else
	{
		//----- Draw the shading
		if (StateTest (PPFC_STATE_CLICKED) && !StateTest (PPFC_STATE_MOUSEOUT))
		{
			dc.SelectObject (&PenShadow);

			dc.MoveTo (Rect.left  + 1, Rect.bottom - 2);
			dc.LineTo (Rect.left  + 1, Rect.top + 1);
			dc.LineTo (Rect.right - 1, Rect.top + 1);
		} else                            
		{
			dc.SelectObject (&PenHighlight);

			dc.MoveTo (Rect.left  + 1, Rect.bottom - 3);
			dc.LineTo (Rect.left  + 1, Rect.top + 1);
			dc.LineTo (Rect.right - 2, Rect.top + 1);
			
			dc.SelectObject (&PenShadow);
		 	dc.MoveTo (Rect.right - 2, Rect.top + 1);
		 	dc.LineTo (Rect.right - 2, Rect.bottom - 2);
		 	dc.LineTo (Rect.left  + 1, Rect.bottom - 2);
		 	dc.LineTo (Rect.left  + 2, Rect.bottom - 3);
		 	dc.LineTo (Rect.right - 3, Rect.bottom - 3);
		 	dc.LineTo (Rect.right - 3, Rect.top + 2);
		}
		
		//----- Draw the combo arrow
		CDC 		MemDC;
	
		CBitmap 	Bitmap;
		CBitmap* 	pOldBitmap; 
		
		BITMAP		BmpInfo;
	
		if (!MemDC.CreateCompatibleDC (&dc)) return;
		if (!Bitmap.LoadOEMBitmap (OBM_COMBO)) return;
		pOldBitmap = MemDC.SelectObject (&Bitmap);
		if (pOldBitmap == NULL) return;
		
	    Bitmap.GetObject (sizeof (BmpInfo), &BmpInfo);

		dc.BitBlt (Rect.left + (Rect.Width()  - BmpInfo.bmWidth)  / 2 + xAdd1, 
				   Rect.top  + (Rect.Height() - BmpInfo.bmHeight) / 2 + yAdd1, 
				   BmpInfo.bmWidth,
				   BmpInfo.bmHeight,
				   &MemDC, 0, 0, SRCAND);
		
		MemDC.SelectObject (pOldBitmap);
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

void CFauxCmb::OnShowWindow(BOOL bShow, UINT nStatus)
{
//	CWnd::OnShowWindow(bShow, nStatus);
	
	// Set or clear the hidden flag. Windows will automatically force a 
	// repaint if we become visible.
	if (bShow)
		StateClear (PPFC_STATE_HIDDEN);
	else
		StateSet (PPFC_STATE_HIDDEN);
}

CWnd* CFauxCmb::SetAssociate (CWnd* NewWnd)
{
	ASSERT (::IsWindow (NewWnd->GetSafeHwnd()));

	CWnd* pOldWnd = m_pWndAssociate;
	
	//----- Get our ID value, then send WM_COMMAND notifications.
#ifdef WIN32
	long wID = GetWindowLong (GetSafeHwnd(), GWL_ID);
#else
	WORD wID = GetWindowWord (GetSafeHwnd(), GWW_ID);
#endif
	
	Notify (PPFC_ASSOCIATELOSS);
	
	m_pWndAssociate = NewWnd;
	
	Notify (PPFC_ASSOCIATEGAIN);
	
	return (pOldWnd);
}

