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

#include "StdAfx.h"

#include "Calendar.h"

//----- Control state flags.
#define PPC_STATE_GRAYED      0x0001
#define PPC_STATE_HIDDEN      0x0002
#define PPC_STATE_MOUSEOUT    0x0004
#define PPC_STATE_LEFTCLICK   0x0008  	// clicked on left button
#define PPC_STATE_RIGHTCLICK  0x0010  	// clicked on right button
#define PPC_STATE_CALCLICK	  0x0020	// clicked on calendar area
//----- Combination of click states.
#define PPC_STATE_CLICKED     (PPC_STATE_LEFTCLICK | PPC_STATE_RIGHTCLICK | PPC_STATE_CALCLICK)
//----- Combination of state flags.
#define PPC_STATE_ALL         0x002F

static CString CalWndClassName;


#define BORDER 		2							// width of the border
#define TEXTINDENT	2							// indent before text

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

char* CCalendar::szMonths  [13] = { "", "January", 
										"February", 
										"March", 
										"April", 
										"May", 
										"June",
										"July", 
										"August", 
										"September", 
										"October", 
										"November", 
										"December" };;

int   CCalendar::nMonthMax [13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

WORD CCalendar::DefaultColors [PPC_COLOR_COUNT] = { COLOR_BTNFACE,		// face
												COLOR_BTNTEXT,		// arrow
												COLOR_BTNSHADOW,	// shadow
												COLOR_BTNHIGHLIGHT,	// highlight
												COLOR_WINDOWFRAME,	// frame
												COLOR_BTNFACE,		// text background
												COLOR_BTNFACE,		// ends background
												COLOR_BTNFACE,		// selected background
												COLOR_HIGHLIGHT,	// marked background
												COLOR_BTNTEXT,		// text foreground
												COLOR_BTNSHADOW,	// ends text
												COLOR_BTNTEXT,		// selected text
												COLOR_HIGHLIGHTTEXT	// marked text
											  };
											  

/////////////////////////////////////////////////////////////////////////////

CCalendar::CCalendar ()
{
	m_Created = FALSE;
 
 	m_wState  = 0;
 	m_dwStyle = 0;
 	
	m_AutoSize 	 	 = TRUE;
	m_EnableButtons  = TRUE;
	m_EnableKeyboard = TRUE;
	m_SingleClick	 = TRUE;
	m_HideLoseFocus  = FALSE;
	m_ShowEnds		 = FALSE;
	m_SelectEnds	 = FALSE;

	m_MonthTime	 	 = CTime::GetCurrentTime();

	m_DateIndex		 = IndexFromDate (m_MonthTime);

	for (int x = 0; x < PPC_COLOR_COUNT; x++)
		m_UseDefault [x] = TRUE;
		
	ClearMarked ();

#ifdef WIN32
	CClientDC dc( NULL );
#else
	CClientDC dc( this );
#endif
	
	//----- Create a 9 point Sans Serif Font
	m_TextFont.CreateFont (-9 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 400, 0, 0, 0,
					   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
					   DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");

	//----- Create a 9 point Sans Serif Font in BOLD
	m_BoldFont.CreateFont (-9 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 700, 0, 0, 0,
					   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
					   DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");

}

CCalendar::~CCalendar()
{
}

BEGIN_MESSAGE_MAP(CCalendar, CWnd)
	//{{AFX_MSG_MAP(CCalendar)
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
	ON_WM_KILLFOCUS()
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCalendar::CalcClickedRect (CRect& Rect)
{
	if (StateTest (PPC_STATE_LEFTCLICK))
	{
		GetButtonRect (Rect, TRUE);
	} else 
	if (StateTest (PPC_STATE_RIGHTCLICK))
	{
		GetButtonRect (Rect, FALSE);
	} else
	if (StateTest (PPC_STATE_CALCLICK))
	{
		GetDatesRect (Rect);
	}
}

void CCalendar::ClearMarked (BOOL Update)
{
	for (int x = 0; x < 42; x++)
		m_MarkedDate [x] = FALSE;       

	if (Update)
	{
		CRect Rect;

		GetDatesRect (Rect);				// repaint the cleard dates
	
		InvalidateRect (&Rect);
		
		UpdateWindow ();
	}	
}

BOOL CCalendar::Create (DWORD dwStyle, CRect& Rect, CWnd* pParent, UINT nID)
{
	if (CalWndClassName.GetLength() == 0)
	 	CalWndClassName = AfxRegisterWndClass (CS_BYTEALIGNWINDOW | CS_PARENTDC | CS_SAVEBITS, 
	 										   ::LoadCursor (NULL, IDC_ARROW));

	ASSERT(pParent != NULL);
	
	if (dwStyle & WS_POPUP)
		nID = NULL;								// no menu for a popup window

	return CWnd::CreateEx (NULL,
						   CalWndClassName, 
						   NULL,
						   dwStyle,
						   Rect.left,
						   Rect.top,
						   Rect.Width(),
						   Rect.Height(),
						   pParent->GetSafeHwnd(), 
						   (HMENU) NULL);
}

CTime CCalendar::DateFromIndex (int Index)
{
	ASSERT (Index >= 0);
	ASSERT (Index < 42);
	
	int FirstDOW = GetFirstDOW (m_MonthTime.GetMonth(), m_MonthTime.GetYear());

	//----- Create a time object for the first day in the month
	CTime FirstDay (m_MonthTime.GetYear(), 
					m_MonthTime.GetMonth(), 1, 0, 0, 0);       
					
	//----- create # of day index differs from first day
	CTimeSpan Diff (Index - FirstDOW, 0, 0, 3600);	// the 3600 is to deal with daylight savings
	
	return FirstDay + Diff;
}

void CCalendar::DrawArrow  (CDC* pDC, CPen* Pen, CBrush* Brush, 
							CRect* pRect, BOOL Clicked, BOOL Left)
{
	int cx2 = pRect->Width() / 2;
	int cx4 = pRect->Width() / 4;

	int cy2 = pRect->Height() / 2;
	int cy4 = pRect->Height() / 4;
		
	int Add = Clicked ? 1 : 0;
		
	pDC->SelectObject (&Pen   [PPC_COLOR_ARROW]);
	pDC->SelectObject (&Brush [PPC_COLOR_ARROW]);
				
	if (Left)
	{
		CPoint		LeftArrow    [3];	
			
		LeftArrow [0].x = pRect->left + Add + cx2 - 3;
		LeftArrow [0].y = pRect->top  + Add + cy2 - 3;
		LeftArrow [1].x = pRect->left + Add + cx2 - 6;
		LeftArrow [1].y = pRect->top  + Add + cy2;
		LeftArrow [2].x = pRect->left + Add + cx2 - 3;
		LeftArrow [2].y = pRect->top  + Add + cy2 + 3;
			                                              
		pDC->Polygon (LeftArrow, 3);
			
		LeftArrow [0].x = pRect->left + Add + cx2 + 4;
		LeftArrow [1].x = pRect->left + Add + cx2 + 1;
		LeftArrow [2].x = pRect->left + Add + cx2 + 4;
			                                              
		pDC->Polygon (LeftArrow, 3);
	} else
	{			
		CPoint		RightArrow    [3];	
			
		RightArrow [0].x = pRect->left + Add + cx2 - 5;
		RightArrow [0].y = pRect->top  + Add + cy2 - 3;
		RightArrow [1].x = pRect->left + Add + cx2 - 2;
		RightArrow [1].y = pRect->top  + Add + cy2;
		RightArrow [2].x = pRect->left + Add + cx2 - 5;
		RightArrow [2].y = pRect->top  + Add + cy2 + 3;
			                                              
		pDC->Polygon (RightArrow, 3);
			
		RightArrow [0].x = pRect->left + Add + cx2 + 2;
		RightArrow [1].x = pRect->left + Add + cx2 + 5;
		RightArrow [2].x = pRect->left + Add + cx2 + 2;
			                                              
		pDC->Polygon (RightArrow, 3);
	}	
}

void CCalendar::DrawButton (CDC* pDC, CPen* Pen, CBrush* Brush,
							CRect* pRect, BOOL Clicked)
{        
	//----- Border around button
	pDC->SelectObject (&Pen   [PPC_COLOR_FRAME]);
	pDC->SelectObject (&Brush [PPC_COLOR_FACE]);

    pDC->Rectangle (pRect);						// filled in with current brush

	if (Clicked)
	{
		//----- shadow on left and top edge when clicked
		pDC->SelectObject (&Pen [PPC_COLOR_SHADOW]);
		pDC->MoveTo (pRect->left  + 1, pRect->bottom - 2);
		pDC->LineTo (pRect->left  + 1, pRect->top    + 1);
		pDC->LineTo (pRect->right - 2, pRect->top    + 1);
	} else
	{
		//----- Left and upper borders
		pDC->SelectObject (&Pen [PPC_COLOR_HIGHLIGHT]);
		pDC->MoveTo (pRect->left  + 1, pRect->bottom - 2);
		pDC->LineTo (pRect->left  + 1, pRect->top    + 1);
		pDC->LineTo (pRect->right - 2, pRect->top    + 1);
		
		pDC->SelectObject (&Pen [PPC_COLOR_SHADOW]);
		pDC->LineTo (pRect->right - 2, pRect->bottom - 2);
		pDC->LineTo (pRect->left  + 1, pRect->bottom - 2);
	}
}   

void CCalendar::DrawButton (CDC* pDC, CPen* Pen, CBrush* Brush, BOOL Left)
{
	if (m_EnableButtons && !StateTest (PPC_STATE_GRAYED))
	{
		//----- Draw buttons
		CRect ButtonRect;
		BOOL  Clicked;

		if (Left)
		{
			GetButtonRect (ButtonRect, TRUE);
			Clicked = StateTest (PPC_STATE_LEFTCLICK) && !StateTest (PPC_STATE_MOUSEOUT);
			DrawButton (pDC, Pen, Brush, &ButtonRect, Clicked);
			DrawArrow  (pDC, Pen, Brush, &ButtonRect, Clicked, TRUE);
		} else
		{
			GetButtonRect (ButtonRect, FALSE);
			Clicked = StateTest (PPC_STATE_RIGHTCLICK) && !StateTest (PPC_STATE_MOUSEOUT);
			DrawButton (pDC, Pen, Brush, &ButtonRect, Clicked);
			DrawArrow  (pDC, Pen, Brush, &ButtonRect, Clicked, FALSE);
		}
	}
}

void CCalendar::DrawDates (CDC* pDC, CPen* Pen, CBrush* Brush, CRect& ClipRect)
{
	CRect RectDates;
	char Date [3];              
	
	int StartX;
	int EndX;

	BOOL ColorChange = FALSE;

	CBrush	TempBrush;

	int MaxDate = GetEndMonth (m_MonthTime.GetMonth(), m_MonthTime.GetYear());

	int FirstDOW = GetFirstDOW (m_MonthTime.GetMonth(), m_MonthTime.GetYear());
	
	pDC->SelectObject (&m_TextFont);

	pDC->SetTextColor (GetColor (PPC_COLOR_TEXT));
	pDC->SetBkColor   (GetColor (PPC_COLOR_BACK));

	GetDateRectIndicies (ClipRect, StartX, EndX);

	ASSERT (StartX >= 0);
	ASSERT (EndX < 42);

	GetDateRect (RectDates, StartX);

	for (int x = StartX; x <= EndX; x++)
	{
		if ((x < FirstDOW) || ((x - FirstDOW + 1) > MaxDate))		// display next/prev month
		{
		 	if (m_ShowEnds)
			{   
				if (m_DateIndex != x)           // if selected date, colors will be set below
				{
					pDC->SetTextColor (GetColor (PPC_COLOR_TEXTENDS));
					pDC->SetBkColor   (GetColor (PPC_COLOR_BACKENDS));

					TempBrush.CreateSolidBrush (GetColor (PPC_COLOR_BACKENDS));
					pDC->FillRect (&RectDates, &TempBrush);
					TempBrush.DeleteObject();

					ColorChange = TRUE;
				}	
								 
				
				if (x < FirstDOW)
				{                                              
					int PrevMax;
					
					int PrevMonth = m_MonthTime.GetMonth();
					int PrevYear  = m_MonthTime.GetYear ();           
					
					if (PrevMonth == 1)
					{
			 			PrevMonth = 12;
			 			PrevYear--;
    				} else
    					PrevMonth--;
    					
                    PrevMax = GetEndMonth (PrevMonth, PrevYear);

		 			::wsprintf (Date, "%2i", PrevMax + (x - FirstDOW + 1));
		 		} else
		 		 	::wsprintf (Date, "%2i", x - MaxDate - FirstDOW + 1);
		 	} else
		 		::wsprintf (Date, "");	 	
		} else
		{
		 	::wsprintf (Date, "%2i", x - FirstDOW + 1);
		}
	 	
		if (m_DateIndex == x)					// Bold today's date
		{
			pDC->SelectObject (&m_BoldFont);

			if (!m_MarkedDate [x])				// if marked, it will be changed below
			{
				pDC->SetTextColor (GetColor (PPC_COLOR_TEXTSELECTED));
				pDC->SetBkColor   (GetColor (PPC_COLOR_BACKSELECTED));
	
				TempBrush.CreateSolidBrush (GetColor (PPC_COLOR_BACKSELECTED));
				pDC->FillRect (&RectDates, &TempBrush);
				TempBrush.DeleteObject();

				ColorChange = TRUE;
			}
		}

		if (m_MarkedDate [x])					// marked date
		{
			pDC->SetTextColor (GetColor (PPC_COLOR_TEXTMARKED));
			pDC->SetBkColor   (GetColor (PPC_COLOR_BACKMARKED));

			TempBrush.CreateSolidBrush (GetColor (PPC_COLOR_BACKMARKED));
			pDC->FillRect (&RectDates, &TempBrush);
			TempBrush.DeleteObject();

			ColorChange = TRUE;		
		}
				
		if (!ColorChange)
			pDC->FillRect (&RectDates, &Brush [PPC_COLOR_FACE]);

		if (StateTest (PPC_STATE_GRAYED))		// the final word!
			pDC->SetTextColor (GetColor (PPC_COLOR_SHADOW));
			
	 	pDC->DrawText (Date, -1, &RectDates, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
		if (ColorChange)
		{
			pDC->SetTextColor (GetColor (PPC_COLOR_TEXT));
			pDC->SetBkColor   (GetColor (PPC_COLOR_BACK));
		
			ColorChange = FALSE;
		}
		
		if (m_DateIndex == x)					// restore font & draw border
		{
			pDC->SelectObject (&m_TextFont);                                            
			
			if ((m_ShowSelected) && !StateTest (PPC_STATE_GRAYED))
//				(GetFocus() == (this)))			// have to have the focus to draw the border
			{
				pDC->SelectObject (&Pen [PPC_COLOR_SHADOW]);
			 	pDC->MoveTo (RectDates.left,       RectDates.bottom - 1);
			 	pDC->LineTo (RectDates.left,       RectDates.top       );
			 	pDC->LineTo (RectDates.right - 1,  RectDates.top       );
			 	
			 	pDC->SelectObject (&Pen [PPC_COLOR_HIGHLIGHT]);
			 	pDC->LineTo (RectDates.right - 1, RectDates.bottom - 1);
			 	pDC->LineTo (RectDates.left,      RectDates.bottom - 1);
			}
		}
			
		if (((x + 1) % 7) == 0)
		{
			RectDates.top     = RectDates.bottom;
			RectDates.bottom += m_TextHeight;
			
			RectDates.right   = BORDER + TEXTINDENT;		// then fall through to below
		}

	 	RectDates.left   = RectDates.right;
	 	RectDates.right += m_TextWidth * 3;
	}
}

void CCalendar::DrawDays (CDC* pDC, CPen* Pen, CBrush* Brush)
{
	//----- Draw the Days Text
	static CString Days ("SuMoTuWeThFrSa");

	CBrush TempBrush;

	CRect RectDays;
	
    GetDaysRect (RectDays);

	pDC->SelectObject (&m_BoldFont);

	//----- adjust to draw first day
	RectDays.left   = BORDER + TEXTINDENT;
	RectDays.right  = BORDER + TEXTINDENT + m_TextWidth  * 3;

	if (StateTest (PPC_STATE_GRAYED))
		pDC->SetTextColor (GetColor (PPC_COLOR_SHADOW));
	else
		pDC->SetTextColor (GetColor (PPC_COLOR_TEXT));

	pDC->SetBkColor   (GetColor (PPC_COLOR_BACK));

	TempBrush.CreateSolidBrush (GetColor (PPC_COLOR_BACK));

	for (int x = 0; x < 7; x++)
	{
		pDC->FillRect (&RectDays, &TempBrush);
		pDC->DrawText (Days.Mid (x * 2, 2), -1, &RectDays, DT_CENTER | DT_TOP | DT_SINGLELINE);
		
		RectDays.left   = RectDays.right;
		RectDays.right += m_TextWidth * 3;
	}

	//----- Draw the line below Days
	pDC->SelectObject (&Pen [PPC_COLOR_SHADOW]);

	GetClientRect (&RectDays);

	pDC->MoveTo (RectDays.left  + BORDER + TEXTINDENT, 
				 RectDays.top + BORDER + m_TextHeight * 2 - 2);
	pDC->LineTo (RectDays.right - BORDER - TEXTINDENT, 
				 RectDays.top + BORDER + m_TextHeight * 2 - 2);
}

void CCalendar::DrawFrame (CDC* pDC, CPen* Pen, CBrush* Brush)
{
	CRect Rect;
	
	GetClientRect (&Rect);
	
	//----- Draw a frame around the Calendar
//	if (m_ShowBorder)
//		pDC->SelectObject (&Pen [PPC_COLOR_FRAME]);
//	else
		pDC->SelectObject (&Pen [PPC_COLOR_FACE]);
			
	pDC->SelectObject (&Brush [PPC_COLOR_FACE]);

	pDC->Rectangle (&Rect);

    //----- Draw the Outer 3D Effect
    pDC->SelectObject (&Pen [PPC_COLOR_HIGHLIGHT]);
 	pDC->MoveTo (0, 			 Rect.bottom - 1);
	pDC->LineTo (0, 			 0);
	pDC->LineTo (Rect.right - 1, 0);

	pDC->SelectObject (&Pen [PPC_COLOR_SHADOW]);
	pDC->LineTo (Rect.right - 1, Rect.bottom - 1);
	pDC->LineTo (0, 			 Rect.bottom - 1);
}

void CCalendar::DrawMonth (CDC* pDC, CPen* Pen, CBrush* Brush)
{
	char Buffer [10];
	CString Str;
	
	CRect RectMonth;
	CBrush TempBrush;
		
	GetMonthRect (RectMonth);
	
	if (StateTest (PPC_STATE_GRAYED))
		pDC->SetTextColor (GetColor (PPC_COLOR_SHADOW));
	else
		pDC->SetTextColor (GetColor (PPC_COLOR_TEXT));
	
	pDC->SetBkColor   (GetColor (PPC_COLOR_BACK));

	TempBrush.CreateSolidBrush (GetColor (PPC_COLOR_BACK));

	pDC->FillRect (&RectMonth, &TempBrush);

	pDC->SelectObject (&m_BoldFont);
    
	::wsprintf (Buffer, "%04i", m_MonthTime.GetYear());

    Str  = szMonths [m_MonthTime.GetMonth()];
    Str += " ";
    Str += Buffer;

	pDC->DrawText (Str, -1, &RectMonth, 
					 DT_CENTER | DT_VCENTER | DT_BOTTOM | DT_SINGLELINE);
}

void CCalendar::GetButtonRect (CRect& Rect, BOOL Left)
{
	if (Left)
	{
		//----- Left button
		Rect.left   = BORDER + 2;
		Rect.top    = BORDER + 2;
	    Rect.bottom = Rect.top  + m_TextHeight - 4;
	    Rect.right  = Rect.left + m_TextWidth  * 3;
	} else
	{
		GetClientRect (&Rect);
		
		//----- right button
//		Rect.left   = BORDER + 2;
		Rect.top    = BORDER + 2;
	    Rect.bottom = Rect.top  + m_TextHeight - 4;
//	    Rect.right  = Rect.left + m_TextWidth  * 3;
		
	    Rect.right = Rect.right - BORDER - 2;
		Rect.left  = Rect.right - m_TextWidth * 3;
	}
}

COLORREF CCalendar::GetColor (int ColorIndex)
{
	ASSERT (ColorIndex >=  0);
	ASSERT (ColorIndex < PPC_COLOR_COUNT);

	return m_UseDefault [ColorIndex] ?
		   ::GetSysColor (DefaultColors [ColorIndex]) : 
		   m_UserColors [ColorIndex] ;
}

int CCalendar::GetControlHeight ()
{
	if (m_Created)
	{
		CRect Rect;
		
		GetClientRect (&Rect);
		
		return Rect.Height();	
	} else
	{
    	if (!m_AutoSize)
    		return -1;							// don't have a clue until it is created
			
		//----- If the calendar is being autosized, it's easy to figure out how big
		//----- it will be
		CClientDC dc (this);
		
		TEXTMETRIC tm;
			
		CFont* pOldFont = dc.SelectObject (&m_TextFont);
		
		dc.GetTextMetrics (&tm);
		
		dc.SelectObject (pOldFont);
				
		//----- Fudge on the character sizes to give reasonable spacing
		int TextHeight = tm.tmHeight + tm.tmHeight / 3;
	
		return TextHeight * 8 +    		// 2 header rows
			   BORDER * 2;				// 6 remaining for the weeks (5 or 6 weeks)
										// 4 = border
	}
}

int CCalendar::GetControlWidth ()
{
	if (m_Created)
	{
		CRect Rect;
		
		GetClientRect (&Rect);
		
		return Rect.Width();	
	} else
	{
    	if (!m_AutoSize)
    		return -1;							// don't have a clue until it is created
			
		//----- If the calendar is being autosized, it's easy to figure out how big
		//----- it will be
		CClientDC dc (this);
		
		TEXTMETRIC tm;
			
		CFont* pOldFont = dc.SelectObject (&m_TextFont);
		
		dc.GetTextMetrics (&tm);
		
		dc.SelectObject (pOldFont);
				
		//----- Fudge on the character sizes to give reasonable spacing
		int TextWidth  = tm.tmAveCharWidth + tm.tmAveCharWidth * 6 / 10; 
	
		return TextWidth  * 7  * 3 + 		// 7 columns, 3 chars wide each
			   TEXTINDENT * 2 +				//
			   BORDER * 2;					// 4 = border
	}
}

void CCalendar::GetDateRect (CRect& Rect, int Index)
{
	int Row = Index / 7;
	int Col = Index % 7;

	Rect.left   = BORDER + TEXTINDENT + m_TextWidth  * 3 * Col;
	Rect.top    = BORDER + m_TextHeight * (Row + 2);
    Rect.bottom = BORDER + m_TextHeight * (Row + 3);
	Rect.right  = BORDER + TEXTINDENT + m_TextWidth  * 3 * (Col + 1);
}

void CCalendar::GetDateRectIndicies (CRect Rect, int& Start, int& End)
{
	int Row;
	int Col;

	//----- The rect we're checking should only be in the dates area
	ASSERT (Rect.top >= ((m_TextHeight * 2) + BORDER));

	//----- find the starting index
	Row = (Rect.top  - (m_TextHeight * 2) - BORDER) / m_TextHeight;
	Col = (Rect.left - BORDER - TEXTINDENT) / (m_TextWidth * 3);

	Start = (Row * 7) + Col;
	
	//----- find the ending index
	Row = (Rect.bottom - (m_TextHeight * 2) - BORDER - 1) / m_TextHeight;
	Col = (Rect.right  - BORDER - TEXTINDENT - 1) / (m_TextWidth * 3);

	End = (Row * 7) + Col;
}

void CCalendar::GetDatesRect (CRect& Rect)
{
	GetClientRect (&Rect);
	
	Rect.left    = BORDER + TEXTINDENT;
	Rect.top     = BORDER + m_TextHeight * 2;
    Rect.bottom -= 1;
    Rect.right  -= TEXTINDENT;
}   

void CCalendar::GetDaysRect (CRect& Rect)
{
	GetClientRect (&Rect);
	
	Rect.left   = BORDER + TEXTINDENT;
	Rect.top    = BORDER + m_TextHeight;
    Rect.bottom = BORDER + m_TextHeight * 2;
	Rect.right -= (BORDER + TEXTINDENT);
}

int CCalendar::GetEndMonth (int Month, int Year)
{
    int LastDay = nMonthMax [Month];
	
	if (Month == 2)			// check for leap year
		if (IsLeapYear (Year))
			LastDay++;
	
	return LastDay;
}

int CCalendar::GetFirstDOW (int Month, int Year)
{
	//----- find index of first day in the month
	int FirstDOW = CTime (Year, Month, 1, 0, 0, 0).GetDayOfWeek ();
	FirstDOW--;									// make it zero based (Sunday == 0)
    
    return FirstDOW;
}

void CCalendar::GetMonthRect (CRect& Rect)
{
	CRect ButtonRect;
	
	GetButtonRect (ButtonRect, TRUE);
	
	Rect.left = ButtonRect.right + 1;   
	
	GetButtonRect (ButtonRect, FALSE);
	
	Rect.right = ButtonRect.left - 1;

	Rect.top    = BORDER;
	Rect.bottom = BORDER + m_TextHeight;
}

WNDPROC* CCalendar::GetSuperWndProcAddr()
{
	static WNDPROC NEAR pfnSuper;
	
	return &pfnSuper;
}

int CCalendar::IndexFromDate (CTime& Date)
{
	int FirstDOW = GetFirstDOW (m_MonthTime.GetMonth(), m_MonthTime.GetYear());

	//----- Create a time object for the first day in the month
	CTime FirstDay (m_MonthTime.GetYear(), 
					m_MonthTime.GetMonth(), 1, 0, 0, 0);       
						
	CTime IndexDay (Date.GetYear(), Date.GetMonth(), Date.GetDay(), 0, 0, 0);
	
	//----- create # of day index differs from first day
	CTimeSpan Diff = IndexDay - FirstDay;
	
//	Diff += CTimeSpan (0, 0, 0, 3600);	// the 3600 is to deal with daylight savings
	
	int Index = FirstDOW + (int) Diff.GetDays();
	
	if ((Index < 0) || (Index > 41))
		return -1;
		
	return Index;
}

int CCalendar::IndexFromPoint (CPoint Point)
{
	CRect Rect;
	
	for (int Row = 0; Row < 6; Row++)
		for (int Col = 0; Col < 7; Col++)  
		{
			GetDateRect (Rect, (Row * 7) + Col);
				
			if (Rect.PtInRect (Point))
			{
				BOOL Ok = FALSE;
				
				if (m_ShowEnds && m_SelectEnds)
					Ok = TRUE;
				else
				{								// check if it is a valid date ...				
					int Index = (Row * 7) + Col;
					
					int MaxDate = GetEndMonth (m_MonthTime.GetMonth(), m_MonthTime.GetYear());

					int FirstDOW = GetFirstDOW (m_MonthTime.GetMonth(), m_MonthTime.GetYear());

					Ok = (Index >= FirstDOW) && ((Index - FirstDOW) < MaxDate);
				}
				
				if (Ok)
			 		return ((Row * 7) + Col);
			 	else
			 		return -1;					// invalid point
			}
		}

	return m_DateIndex;
}

BOOL CCalendar::MarkDate (CTime Date, BOOL Mark, BOOL Update)
{
	int Index = IndexFromDate (Date);
	
	if (Index == -1)
		return FALSE;
		
	ASSERT (Index >= 0);
	ASSERT (Index < 42);

	if (m_MarkedDate [Index] != Mark)
	{
		CRect Rect;

		m_MarkedDate [Index]  = Mark;

		GetDateRect (Rect, Index);				// repaint the marked date

		InvalidateRect (&Rect);
		
		if (Update)
			UpdateWindow ();
	}	
	
	return TRUE;
}

void CCalendar::MoveDateIndex (int Change)
{
	BOOL ShowPrev;
	
	int TempIndex = m_DateIndex + Change;
	
	int FirstDOW = GetFirstDOW (m_MonthTime.GetMonth(), m_MonthTime.GetYear());
	
	if (TempIndex >= 0)
	{
		if (TempIndex < 42)
		{
			if (m_ShowEnds)
			{
	 			SelectDateIndex (TempIndex);
				return;		
			}
			
	 		if (TempIndex < FirstDOW)                                    
	 			ShowPrev = TRUE;				// display previous month
    		else
    		{
				int EndMonth = GetEndMonth (m_MonthTime.GetMonth(), m_MonthTime.GetYear());
				
				if ((TempIndex - FirstDOW) >= EndMonth)
					ShowPrev = FALSE;				// display next month
				else
				{
					SelectDateIndex (TempIndex);	// index is Ok
					return;
				}	
			}
		} else
			ShowPrev = FALSE;					// display next month
	} else
		ShowPrev = TRUE;						// display previous month	 	
		
	//----- if we've got to this point, the month needs to be changed
	if (ShowPrev)
	{             
		int Year  = m_MonthTime.GetYear();
		int Month = m_MonthTime.GetMonth();
		int Day;
		
		//----- go back one month
		Month -= 1;
		if (Month < 1)
		{
			Month = 12;
			Year--;
		}
			
		if (Year < 1970)
			Year = 1970;

		Day = GetEndMonth (Month, Year);

		if ((TempIndex < 0) || !m_ShowEnds) // figure out which day to go to
			Day = Day + TempIndex - FirstDOW + 1;

		SelectDate (CTime (Year, Month, Day, 0, 0, 0));
	} else
	{
		int Year  = m_MonthTime.GetYear();
		int Month = m_MonthTime.GetMonth();
		int Day;

		Month += 1;
		
		if (Month > 12)
		{
			Month = 1;
			Year++;
		}

		if (Year > 2038)
			Year = 2038;
		
		Day = GetEndMonth (m_MonthTime.GetMonth(), m_MonthTime.GetYear());

	    Day = TempIndex - (FirstDOW + Day) + 1;
		
		SelectDate (CTime (Year, Month, Day, 0, 0, 0));
	}		
}

void CCalendar::NextMonth (BOOL Forward)
{
	CTime TempDate = DateFromIndex (m_DateIndex);

	int Year = m_MonthTime.GetYear();
	
	int Month = m_MonthTime.GetMonth();
	
	int Day  = TempDate.GetDay();
		
	Month += Forward ? 1 : -1;
	
	if (Month > 12)
	{
		Month = 1;
		Year++;
	} else if (Month < 1)
	{
		Month = 12;
		Year--;
	}
	
	if (Year < 1970)
		Year = 1970;
	else if (Year > 2038)
		Year = 2038;
	
	int MaxDay = GetEndMonth (Month, Year);
	
	if (Day > MaxDay)
		Day = MaxDay;
	
	m_MonthTime = CTime (Year, Month, Day, 0, 0, 0);
	
	m_DateIndex	= IndexFromDate (m_MonthTime);

	ClearMarked ();

	//----- invalidate the appropriate areas
	CRect Rect;
	
	GetMonthRect   (Rect);
	InvalidateRect (&Rect, TRUE);
	UpdateWindow   ();

	GetDatesRect   (Rect);
	InvalidateRect (&Rect, TRUE);
	UpdateWindow   ();

	Notify (PPC_DATECHANGED);
}

void CCalendar::Notify (UINT Msg)
{
	m_pWndAssociate->SendMessage (Msg, (WPARAM) m_hWnd);
}

void CCalendar::OnCancelMode()
{
	CWnd::OnCancelMode();
	
	StateClear (PPC_STATE_LEFTCLICK | PPC_STATE_RIGHTCLICK);

	ReleaseCapture();
}

void CCalendar::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_EnableKeyboard)
	{
		CWnd::OnChar (nChar, nRepCnt, nFlags);
		
		return;
	}
	
	switch (nChar)        
	{
		case 't'	  : // Tt    - Today
		case 'T'	  :
			SelectDate (CTime::GetCurrentTime());
			break;
			
		case 'm'	  : // Mm	 - First day in month
		case 'M'	  :
			SelectDate (CTime (m_MonthTime.GetYear(), m_MonthTime.GetMonth(), 1, 0, 0, 0));
			break;

		case 'h'	  : // Hh    - Last day in month
		case 'H'      :
			SelectDate (CTime (m_MonthTime.GetYear(), 
						 	   m_MonthTime.GetMonth(), 
						 	   GetEndMonth (m_MonthTime.GetMonth(), m_MonthTime.GetYear()),
						 	   0, 0, 0));
			break;

		case 'y'	  : // Yy    - First day in year
		case 'Y'      : 
			SelectDate (CTime (m_MonthTime.GetYear(), 1, 1, 0, 0, 0));
			break;
	
    	case 'r'	  : // Rr    - Last day in year
    	case 'R'	  :
			SelectDate (CTime (m_MonthTime.GetYear(), 12, 31, 0, 0, 0));
			break;
    	
		case 'w'	  : // Ww	 - First day in week
		case 'W'	  :
			SelectDateIndex ((m_DateIndex / 7) * 7);
			break;

		case 'k'	  : // Kk    - Last day in week
		case 'K'	  :
			SelectDateIndex ((m_DateIndex / 7) * 7 + 6);
			break;

		case '-'	  :
		case '_'	  :
			MoveDateIndex (-1);
			break;

		case '+'	  :
		case '='      :
			MoveDateIndex (1);
			break;

		default : 
			CWnd::OnChar (nChar, nRepCnt, nFlags);
			break;
	}
}

int CCalendar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//----- Copy styles
	m_dwStyle  = lpCreateStruct->style;

	//----- setup control variabled
	m_ShowEnds		= (BOOL) (m_dwStyle & PPC_SHOWENDS);
	m_SelectEnds	= (BOOL) (m_dwStyle & PPC_SELECTENDS);
	m_ShowSelected	= (BOOL) (m_dwStyle & PPC_SHOWSELECTED);
	m_EnableButtons = (BOOL) (m_dwStyle & PPC_ENABLEBUTTONS);
	m_EnableKeyboard= (BOOL) (m_dwStyle & PPC_ENABLEKEYBOARD);
	m_SingleClick	= (BOOL) (m_dwStyle & PPC_SINGLECLICK);
	m_HideLoseFocus = (BOOL) (m_dwStyle & PPC_HIDELOSEFOCUS);
	m_AutoSize		= (BOOL) (m_dwStyle & PPC_AUTOSIZE);
		
	SetFont (&m_TextFont, FALSE);
	
	//----- Resize the control, if necessary
	SetCalendarSize (m_AutoSize);

	//----- Our associate is the parent by default.
#ifdef WIN32
	m_pWndAssociate = FromHandle ((HWND) ::GetWindowLong (GetSafeHwnd(), GWL_HWNDPARENT));
#else
	m_pWndAssociate = FromHandle ((HWND) ::GetWindowWord (GetSafeHwnd(), GWW_HWNDPARENT));
#endif
	
	//----- Clear out all initial states.
	StateClear (PPC_STATE_ALL);

	m_Created = TRUE;
	
	return 0;
}

void CCalendar::OnEnable(BOOL bEnable)
{
	CWnd::OnEnable (bEnable);
	
	// Handles disabling/enabling case.  Example of a change-state-and-repaint 
	// strategy since we let the painting code take care of the visuals.
	if (bEnable)
		StateClear (PPC_STATE_GRAYED);
	else
		StateSet (PPC_STATE_GRAYED);
	
	//----- Force a repaint since the control will look different.
	InvalidateRect (NULL, TRUE);
	UpdateWindow   ();
}

BOOL CCalendar::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;		
	
//	return CWnd::OnEraseBkgnd(pDC);
}

UINT CCalendar::OnGetDlgCode()
{
	//----- In a dialog, we want to process all chars and arrows
	return (DLGC_WANTCHARS | DLGC_WANTARROWS);
}

void CCalendar::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_EnableKeyboard)
	{
		CWnd::OnKeyDown (nChar, nRepCnt, nFlags);
		
		return;
	}
	
	switch (nChar)        
	{
		case VK_PRIOR :	// PGUP  - prior month
			NextMonth (FALSE);
			break;
			
		case VK_NEXT  : // PGDN  - next month        
			NextMonth (TRUE);
			break;
			
		case VK_HOME  : // HOME  - First month in year
			SelectDate (CTime (m_MonthTime.GetYear(), 1, 1, 0, 0, 0));
			break;

		case VK_END   : // END   - Last month in year
			SelectDate (CTime (m_MonthTime.GetYear(), 12, 31, 0, 0, 0));
			break;
			
		case VK_LEFT  : // LEFT  - Move selected date left one day
			MoveDateIndex (-1);
			break;

		case VK_RIGHT : // RIGHT - Move selected date right one day
			MoveDateIndex (1);
			break;

		case VK_UP	  : // UP    - Move selected date up one week
			MoveDateIndex (-7);
			break;

		case VK_DOWN  : // DOWN  - Move selected date down one week
			MoveDateIndex (7);
			break;

		case VK_RETURN: // RETURN - Send finished if m_SingleClick is true
			if (m_SingleClick)
				Notify (PPC_DATEFINISHED);
			break;

		case VK_ESCAPE :
			Notify (PPC_DATEFINISHED);
			break;
			
		default : 
			CWnd::OnKeyDown (nChar, nRepCnt, nFlags);
			break;
	}
}

void CCalendar::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
	
	if (m_HideLoseFocus)
	{
		ShowWindow (SW_HIDE);
    
		ReleaseCapture ();
    }
    
	Notify (PPC_DATEFINISHED);
}

void CCalendar::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnLButtonDown (nFlags, point);
	
//	CWnd::OnLButtonDblClk(nFlags, point);
}

void CCalendar::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect 	Rect;
	
	if (m_HideLoseFocus)
	{
		GetClientRect (&Rect);
		if (!Rect.PtInRect (point))
		{
			ShowWindow (SW_HIDE);
	    
			ReleaseCapture ();
		
			Notify (PPC_DATEFINISHED);
		}	
	}

	WORD wState;

    BOOL ButtonClicked	= FALSE;

	if (GetFocus() != (this))
		SetFocus();
		    
	//----- Click in the left button?
	GetButtonRect (Rect, TRUE);

	if (Rect.PtInRect (point))
	{
		if (m_EnableButtons)
		{
			wState = PPC_STATE_LEFTCLICK;
    
    		ButtonClicked = TRUE;
		}	
	} else
	{
		//----- Click in the right button?
	 	GetButtonRect (Rect, FALSE);
	 	
	 	if (Rect.PtInRect (point))
	 	{
	 	 	if (m_EnableButtons)
	 	 	{
	 	 		wState = PPC_STATE_RIGHTCLICK;
	 	 	
	 	 		ButtonClicked = TRUE;
	 	 	}
	 	} else
	 	{
	 	 	//----- Click in the calendar portion
			GetDatesRect (Rect);

			if (Rect.PtInRect (point))
			{
			 	wState = PPC_STATE_CALCLICK;

				StateClear (PPC_STATE_LEFTCLICK | PPC_STATE_RIGHTCLICK);
				StateSet   (wState);
			 	
			 	SelectDateIndex (IndexFromPoint (point));

				if (!m_HideLoseFocus)
					SetCapture();
			}
	 	}
	}
	
	if (ButtonClicked)
	{
		//----- Change state and repaint
		StateClear (PPC_STATE_LEFTCLICK | PPC_STATE_RIGHTCLICK);
		StateSet   (wState);
	
		InvalidateRect  (&Rect, TRUE);
				
		UpdateWindow   ();
	
		if (!m_HideLoseFocus)
			SetCapture ();
	}
	
//	CWnd::OnLButtonDown(nFlags, point);
}

void CCalendar::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect Rect;
	
	if (!m_HideLoseFocus)
		ReleaseCapture ();
				
	// Repaint if necessary, only if we are clicked AND the mouse
	// is still in the boundaries of the control.
	if (StateTest (PPC_STATE_CLICKED) && !StateTest (PPC_STATE_MOUSEOUT))
	{
		BOOL ButtonUp = FALSE;
		
		if (StateTest (PPC_STATE_LEFTCLICK))
		{
			NextMonth (FALSE);
			ButtonUp = TRUE;	
		} else if (StateTest (PPC_STATE_RIGHTCLICK))
		{
			NextMonth (TRUE);
			ButtonUp = TRUE;
		} else if (StateTest (PPC_STATE_CALCLICK))
		{
			if (m_SingleClick)
				if (IndexFromPoint (point) != -1)
					Notify (PPC_DATEFINISHED);
		}
		
		if (ButtonUp)
		{
			//----- Calculate the rectangle before clearing states.
			CalcClickedRect (Rect);

			StateClear (PPC_STATE_MOUSEOUT);
			StateClear (PPC_STATE_CLICKED);

			InvalidateRect (&Rect, TRUE);
			UpdateWindow  ();

			Notify (PPC_DATECHANGED);
		}
	}
	
 	//----- just clear the states
	StateClear (PPC_STATE_MOUSEOUT);
	StateClear (PPC_STATE_CLICKED);
	
//	CWnd::OnLButtonUp(nFlags, point);
}

void CCalendar::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect Rect;
	
	if (!StateTest (PPC_STATE_CLICKED))
		return;
				
	//----- Get the area we originally clicked and the new POINT
	CalcClickedRect (Rect);
				
	if (StateTest (PPC_STATE_CALCLICK))
	{
	 	if (Rect.PtInRect (point))
	 	{
	 		SelectDateIndex (IndexFromPoint (point));
			//----- takes care of updating highlighted rect
	 		StateClear (PPC_STATE_MOUSEOUT);
	 	} else
	 		StateSet (PPC_STATE_MOUSEOUT);
	} else
	{
		WORD wState = m_wState;

		//----- Hit-Test the rectange and change the state if necessary.
		if (Rect.PtInRect (point))
			StateClear (PPC_STATE_MOUSEOUT);
		else
			StateSet (PPC_STATE_MOUSEOUT);
					
		// If the state changed, repaint the appropriate part of the control.
		if (wState != m_wState)
		{
			InvalidateRect (&Rect, TRUE);
			UpdateWindow  ();
		}
	}
			
//	CWnd::OnMouseMove(nFlags, point);
}

void CCalendar::OnPaint()
{
	CPaintDC dc (this); // device context for painting
	
	CPen*		pOldPen;
	CBrush*		pOldBrush;
	CFont*		pOldFont;                                                   
                                                   
	CRect		Rect;
	CRect		ClipRect;
	CRect		TestRect;
	
	CPen		Pen  [5];		// FACE, ARROW, SHADOW, HIGHLIGHT, FRAME
	CBrush		Brush[2];		// FACE, ARROW

	CDC 		MemDC;

	CBitmap 	Bitmap;
	CBitmap* 	pOldBitmap;

	dc.GetClipBox (&ClipRect);
	dc.LPtoDP	  (&ClipRect);

	GetClientRect (&Rect);    

	if (!MemDC.CreateCompatibleDC (&dc)) return;
	if (!Bitmap.CreateCompatibleBitmap (&dc, Rect.Width(), Rect.Height())) return;
	pOldBitmap = MemDC.SelectObject (&Bitmap);
	if (pOldBitmap == NULL) return;

	//----- Create all drawing items
	Pen [PPC_COLOR_FACE     ].CreatePen (PS_SOLID, 1, GetColor (PPC_COLOR_FACE));
	Pen [PPC_COLOR_ARROW    ].CreatePen (PS_SOLID, 1, GetColor (PPC_COLOR_ARROW));
	Pen [PPC_COLOR_SHADOW   ].CreatePen	(PS_SOLID, 1, GetColor (PPC_COLOR_SHADOW));
	Pen [PPC_COLOR_HIGHLIGHT].CreatePen (PS_SOLID, 1, GetColor (PPC_COLOR_HIGHLIGHT));
	Pen [PPC_COLOR_FRAME    ].CreatePen (PS_SOLID, 1, GetColor (PPC_COLOR_FRAME));
	
	Brush [PPC_COLOR_FACE ].CreateSolidBrush (GetColor (PPC_COLOR_FACE));
	Brush [PPC_COLOR_ARROW].CreateSolidBrush (GetColor (PPC_COLOR_ARROW));


	pOldBrush = MemDC.SelectObject (&Brush [PPC_COLOR_FACE]);
	pOldPen   = MemDC.SelectObject (&Pen   [PPC_COLOR_FACE]);
	pOldFont  = MemDC.SelectObject (&m_BoldFont);

	DrawFrame      (&MemDC, Pen, Brush);		// Always, 

	GetMonthRect   (TestRect);					// Month Year
	if (TestRect.IntersectRect (&TestRect, &ClipRect))
		DrawMonth      (&MemDC, Pen, Brush);	
	
	GetDaysRect	   (TestRect);					// days (SU, MO, ...
	if (TestRect.IntersectRect (&TestRect, &ClipRect))
		DrawDays       (&MemDC, Pen, Brush);
	
	GetButtonRect  (TestRect, TRUE);			// left button
	if (TestRect.IntersectRect (&TestRect, &ClipRect))
		DrawButton (&MemDC, Pen, Brush, TRUE);

	GetButtonRect  (TestRect, FALSE);			// right button
	if (TestRect.IntersectRect (&TestRect, &ClipRect))
		DrawButton (&MemDC, Pen, Brush, FALSE);

	GetDatesRect   (TestRect);					// dates
	if (TestRect.IntersectRect (&TestRect, &ClipRect))	
		DrawDates      (&MemDC, Pen, Brush, TestRect);	// TestRect contains intersection of the two
		
	//----- Copy the necessary area to the screen
	GetClientRect (&Rect);
	Rect.IntersectRect (&Rect, &ClipRect);
	dc.BitBlt (Rect.left, Rect.top, Rect.Width(), Rect.Height(),
			   &MemDC, Rect.left, Rect.top, SRCCOPY);

	//----- Clean up
	MemDC.SelectObject (pOldBitmap);
	MemDC.SelectObject (pOldBrush);
	MemDC.SelectObject (pOldPen);
	MemDC.SelectObject (pOldFont);
}

void CCalendar::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	
	if (m_ShowSelected)							// show the selected date
	{
		CRect DateRect;

		GetDateRect (DateRect, m_DateIndex);
		
		InvalidateRect (&DateRect);
		UpdateWindow ();
	}   

	if (m_HideLoseFocus)
		SetCapture();							// track all mouse movements
}

void CCalendar::OnShowWindow(BOOL bShow, UINT nStatus)
{
//	CWnd::OnShowWindow(bShow, nStatus);
	
	if (bShow)
		StateClear (PPC_STATE_HIDDEN);
	else
		StateSet (PPC_STATE_HIDDEN);
}

void CCalendar::SelectDate  (CTime Date)
{
	int DY = Date.GetYear();			// Kludgy, but the direct approach didn't work
	int MY = m_MonthTime.GetYear();
	int DM = Date.GetMonth();
	int MM = m_MonthTime.GetMonth();

	if ((DY != MY) || (DM != MM))
	{
		m_MonthTime = Date;

		ClearMarked ();
	}
		
//	SelectDateIndex (IndexFromDate (Date)); 
	int TmpIndex = IndexFromDate (Date);
	
	if (TmpIndex != -1)
	{
		m_DateIndex = TmpIndex;
			
		CRect Rect;
	
		GetMonthRect   (Rect);
		InvalidateRect (&Rect);
		UpdateWindow   ();
	
		GetDatesRect   (Rect);
		InvalidateRect (&Rect);
		UpdateWindow   ();
	
		Notify (PPC_DATECHANGED);
	}
}
	
void CCalendar::SelectDateIndex (int Index)
{
	if (Index == -1) return;
	
    if (Index != m_DateIndex)
	{                       
		CRect OldRect;
		CRect NewRect;
			
		GetDateRect (OldRect, m_DateIndex);
		GetDateRect (NewRect, Index);

		m_DateIndex = Index;
		
		if (m_ShowSelected)
		{
			InvalidateRect (&OldRect);
			UpdateWindow ();
			
			InvalidateRect (&NewRect);
			UpdateWindow ();

			Notify (PPC_DATECHANGED);
		}
	}
}

CWnd* CCalendar::SetAssociate (CWnd* NewWnd)
{
	ASSERT (::IsWindow (NewWnd->GetSafeHwnd()));

	//----- Get our ID value, then send WM_COMMAND notifications.
#ifdef WIN32
	long wID = GetWindowLong (GetSafeHwnd(), GWL_ID);
#else
	WORD wID = GetWindowWord (GetSafeHwnd(), GWW_ID);
#endif

	CWnd* pOldWnd = m_pWndAssociate;
	
	Notify (PPC_ASSOCIATELOSS);
	
	m_pWndAssociate = NewWnd;
	
	Notify (PPC_ASSOCIATEGAIN);
	
	return (pOldWnd);
}

void CCalendar::SetCalendarSize (BOOL Resize)
{
	if (Resize)
	{
		CClientDC dc (this);
	
		TEXTMETRIC tm;
		
		CFont* pOldFont = dc.SelectObject (&m_TextFont);
	
		dc.GetTextMetrics (&tm);
	
		dc.SelectObject (pOldFont);
			
		//----- Fudge on the character sizes to give reasonable spacing
		m_TextWidth  = tm.tmAveCharWidth + tm.tmAveCharWidth * 6 / 10; 

		m_TextHeight = tm.tmHeight + tm.tmHeight / 3;

		int cx	=  m_TextWidth  * 7  * 3 + 		// 7 columns, 3 chars wide each
				   TEXTINDENT * 2 +				//
				   BORDER * 2;					// 4 = border
				   
		int cy  = m_TextHeight * 8 +    		// 2 header rows
				  BORDER * 2 +					// 6 remaining for the weeks (5 or 6 weeks)
												// 4 = border
				  1;
		
		SetWindowPos (&wndTop, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER);
	} else
	{                                                        
		CRect Rect;
		
		GetClientRect (&Rect);
		
		//----- Adapt character spacing to the size of the control
//	 	m_TextWidth  = (lpCreateStruct->cx - TEXTINDENT * 2 - BORDER * 2) / 7 / 3;
//	 	m_TextHeight = (lpCreateStruct->cy - BORDER * 2) / 8;
	 	m_TextWidth  = (Rect.Width () - TEXTINDENT * 2 - BORDER * 2) / 7 / 3;
	 	m_TextHeight = (Rect.Height() - BORDER * 2) / 8;
	}
}

void CCalendar::SetTextFont (CFont* pFont, BOOL Resize)
{
	LOGFONT lf;
	
	if (pFont->GetObject (sizeof (lf), &lf) == 0)
		return;
	
    m_TextFont.DeleteObject ();
	m_BoldFont.DeleteObject ();
	
    m_TextFont.CreateFontIndirect (&lf);
	SetFont (&m_TextFont, FALSE);

	lf.lfWeight = 700;							// make it bold;
	
	m_BoldFont.CreateFontIndirect (&lf);
	
    if (m_Created)								// control exists
    {
    	SetCalendarSize (Resize);
    
    	InvalidateRect (NULL);
    	UpdateWindow   ();
    }
}

COLORREF CCalendar::SetTextColor (COLORREF Color)
{ 
	COLORREF OldColor = GetColor (PPC_COLOR_TEXT);
	
	m_UserColors [PPC_COLOR_TEXT] = Color; 
	m_UseDefault [PPC_COLOR_TEXT] = FALSE;			
			  
	return OldColor;
}

COLORREF CCalendar::SetEndsTextColor (COLORREF Color)
{ 
	COLORREF OldColor = GetColor (PPC_COLOR_TEXTENDS);
	
	m_UserColors [PPC_COLOR_TEXTENDS] = Color; 
	m_UseDefault [PPC_COLOR_TEXTENDS] = FALSE;			
			  
	return OldColor;
}

COLORREF CCalendar::SetMarkedTextColor	(COLORREF Color)
{ 
	COLORREF OldColor = GetColor (PPC_COLOR_TEXTMARKED);
	
	m_UserColors [PPC_COLOR_TEXTMARKED] = Color; 
	m_UseDefault [PPC_COLOR_TEXTMARKED] = FALSE;			
			  
	return OldColor;
}

COLORREF CCalendar::SetSelectedTextColor (COLORREF Color)
{ 
	COLORREF OldColor = GetColor (PPC_COLOR_TEXTSELECTED);
	
	m_UserColors [PPC_COLOR_TEXTSELECTED] = Color; 
	m_UseDefault [PPC_COLOR_TEXTSELECTED] = FALSE;			
			  
	return OldColor;
}

COLORREF CCalendar::SetBackColor (COLORREF Color)
{ 
	COLORREF OldColor = GetColor (PPC_COLOR_BACK);
	
	m_UserColors [PPC_COLOR_BACK] = Color; 
	m_UseDefault [PPC_COLOR_BACK] = FALSE;			
			  
	return OldColor;
}

COLORREF CCalendar::SetEndsBackColor (COLORREF Color)
{ 
	COLORREF OldColor = GetColor (PPC_COLOR_BACKENDS);
	
	m_UserColors [PPC_COLOR_BACKENDS] = Color; 
	m_UseDefault [PPC_COLOR_BACKENDS] = FALSE;			
			  
	return OldColor;
}

COLORREF CCalendar::SetMarkedBackColor	 (COLORREF Color)
{ 
	COLORREF OldColor = GetColor (PPC_COLOR_BACKMARKED);
	
	m_UserColors [PPC_COLOR_BACKMARKED] = Color; 
	m_UseDefault [PPC_COLOR_BACKMARKED] = FALSE;			
			  
	return OldColor;
}

COLORREF CCalendar::SetSelectedBackColor (COLORREF Color)
{ 
	COLORREF OldColor = GetColor (PPC_COLOR_BACKSELECTED);
	
	m_UserColors [PPC_COLOR_BACKSELECTED] = Color; 
	m_UseDefault [PPC_COLOR_BACKSELECTED] = FALSE;			
			  
	return OldColor;
}







