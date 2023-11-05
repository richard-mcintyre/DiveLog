// CALENDER.H : interface of the CCalendar class

#define PP_OFFSET			100

// Control styles.
#define PPC_AUTOSIZE		0x0001L
#define PPC_SHOWENDS		0x0002L
#define PPC_SELECTENDS      0x0004L
#define PPC_SHOWSELECTED	0x0008L
#define PPC_ENABLEBUTTONS   0x0010L
#define PPC_ENABLEKEYBOARD	0x0020L
#define PPC_SINGLECLICK		0x0040L
#define PPC_HIDELOSEFOCUS	0x0080L
#define PPC_DEFAULT			(WS_BORDER | PPC_SHOWSELECTED | PPC_ENABLEBUTTONS | PPC_ENABLEKEYBOARD | PPC_SINGLECLICK | PPC_AUTOSIZE)
							 
// Notification codes sent via SendMessage
#define PPC_DATECHANGED		(WM_USER + PP_OFFSET + 10)
#define PPC_ASSOCIATEGAIN   (WM_USER + PP_OFFSET + 11)
#define PPC_ASSOCIATELOSS   (WM_USER + PP_OFFSET + 12)
#define PPC_DATEFINISHED	(WM_USER + PP_OFFSET + 13)

#define PPC_COLOR_FACE			0
#define PPC_COLOR_ARROW			1
#define PPC_COLOR_SHADOW		2
#define PPC_COLOR_HIGHLIGHT		3
#define PPC_COLOR_FRAME			4

#define PPC_COLOR_BACK			5
#define PPC_COLOR_BACKENDS		6
#define PPC_COLOR_BACKSELECTED	7
#define PPC_COLOR_BACKMARKED	8

#define PPC_COLOR_TEXT			9
#define PPC_COLOR_TEXTENDS		10
#define PPC_COLOR_TEXTSELECTED	11
#define PPC_COLOR_TEXTMARKED	12

#define PPC_COLOR_COUNT			13


class CCalendar : public CWnd
{
// Construction
public:
    CCalendar();
    
// Attributes
public:

private:
	BOOL				m_Created;				// TRUE if the control has been created
	BOOL				m_AutoSize;				// TRUE if want to Size based on font size
	BOOL				m_EnableButtons;
	BOOL				m_EnableKeyboard;
	BOOL				m_SingleClick;			// TRUE if single click on a date returns FINISHED
	BOOL				m_HideLoseFocus;		// TRUE if control is hidden when focus is lost
	BOOL				m_ShowSelected;			// TRUE if want to highlight selected date
	BOOL				m_ShowEnds;				// TRUE if want to show prior/next month's dates
	BOOL				m_SelectEnds;			// TRUE if allow selecting next/prior month's dates

	int					m_DateIndex;			// index of currently selected date
	BOOL				m_MarkedDate [42];		// 7 ways/week, 6 weeks
		
	CFont				m_TextFont;
	CFont				m_BoldFont;
	
	CTime				m_MonthTime;
	
	int					m_TextWidth;
	int					m_TextHeight;

	BOOL				m_UseDefault [PPC_COLOR_COUNT];
	COLORREF			m_UserColors [PPC_COLOR_COUNT];
	
	CWnd*				m_pWndAssociate;  		// Associate window handle
	DWORD       		m_dwStyle;        		// Copy of GetWindowLong(hWnd, GWL_STYLE)
	WORD        		m_wState;         		// State flags

	static char* 		szMonths  [13];
	static int 			nMonthMax [13];
	static WORD 		DefaultColors [PPC_COLOR_COUNT];

// Operations
public:
	BOOL		Create (DWORD dwStyle, CRect& Rect, CWnd* pParent, UINT nID);

	void		ClearMarked (BOOL Update = FALSE);

	BOOL		GetAutoSize		 ()	{ return m_AutoSize;		};
	BOOL		GetButtonsActive ()	{ return m_EnableButtons; 	};
	BOOL		GetKeyboardActive()	{ return m_EnableKeyboard;	};
	BOOL		GetSelectEnds	 () { return m_SelectEnds;		};
	BOOL		GetShowEnds		 () { return m_ShowEnds;		};
	BOOL		GetShowSelected	 () { return m_ShowSelected;	};
	BOOL		GetSingleClickOk ()	{ return m_SingleClick;		};
	
	CTime		GetSelectedDate ()	{ return DateFromIndex (m_DateIndex); };
	BOOL 		MarkDate 		(CTime Date, BOOL Mark = TRUE, BOOL Update = TRUE);
	void		SelectDate  	(CTime Date);

	int			GetControlWidth	();
	int			GetControlHeight();

	CWnd* 		SetAssociate (CWnd* NewWnd);
	CWnd*		GetAssociate ()	{ return (m_pWndAssociate); };


	void		SetTextFont	(CFont* pFont, BOOL Resize = TRUE);
	
	COLORREF	SetTextColor	 	 (COLORREF Color);
	COLORREF	SetEndsTextColor	 (COLORREF Color);
	COLORREF	SetMarkedTextColor	 (COLORREF Color);
	COLORREF	SetSelectedTextColor (COLORREF Color);
	
	COLORREF	SetBackColor		 (COLORREF Color);
	COLORREF	SetEndsBackColor	 (COLORREF Color);
	COLORREF	SetMarkedBackColor	 (COLORREF Color);
	COLORREF	SetSelectedBackColor (COLORREF Color);

// Implementation
public:
	virtual ~CCalendar();

private:
	void  	CalcClickedRect (CRect& Rect);

	CTime	DateFromIndex (int Index);
	
	void 	DrawArrow  (CDC* pDC, CPen* Pen, CBrush* Brush,
						CRect* pRect, BOOL Clicked, BOOL Left);
	void 	DrawButton (CDC* pDC, CPen* Pen, CBrush* Brush,
						CRect* pRect, BOOL Clicked);

	void	DrawButton (CDC* pDC, CPen* Pen, CBrush* Brush, BOOL Left);
	void	DrawDates  (CDC* pDC, CPen* Pen, CBrush* Brush, CRect& ClipRect);
	void	DrawDays   (CDC* pDC, CPen* Pen, CBrush* Brush);
	void	DrawMonth  (CDC* pDC, CPen* Pen, CBrush* Brush);
	void	DrawFrame  (CDC* pDC, CPen* Pen, CBrush* Brush);
	
	COLORREF GetColor (int ColorIndex);

	void 	GetButtonRect (CRect& Rect, BOOL Left);
	void 	GetDateRect   (CRect& Rect, int Index);
	void	GetDatesRect  (CRect& Rect);
	void	GetDaysRect   (CRect& Rect);
	void	GetMonthRect  (CRect& Rect);

	void	GetDateRectIndicies (CRect Rect, int& Start, int& End);
	
	int 	GetEndMonth 	(int Month, int Year);
	int 	GetFirstDOW 	(int Month, int Year);

	int		IndexFromDate (CTime& Date);
	int 	IndexFromPoint(CPoint Point);
	
	BOOL	IsLeapYear	(int Year)
				{ return (((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0)); };
				
	void	MoveDateIndex (int Change);
	void 	NextMonth 	(BOOL Forward);   
	void	Notify		(UINT Msg);
	void 	SelectDateIndex (int Index);
	void 	SetCalendarSize (BOOL Resize);

	void 	StateSet 	(WORD wFlags) { m_wState |= wFlags;  };
	void	StateClear	(WORD wFlags) { m_wState &= ~wFlags; };
	BOOL	StateTest	(WORD wFlags) { return (m_wState & wFlags); };

	// Generated message map functions
protected:
	virtual WNDPROC* 	GetSuperWndProcAddr();

	//{{AFX_MSG(CCalendar)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


