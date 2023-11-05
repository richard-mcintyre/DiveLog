// DIAGSCRL.H - interface of the CDiagScroll class

//////////////////////////////////////////////////////////////////////////
// CDiagScroll

#define PP_OFFSET			100

// Control specific styles.
#define PPDS_VERTICAL       0x0001L
#define PPDS_HORIZONTAL     0x0002L
#define PPDS_AUTOSIZE		0x0004L
#define PPDS_DEFAULT		(WS_BORDER | PPDS_VERTICAL | PPDS_AUTOSIZE)

// Notification codes sent via SendMessage
#define PPDS_ASSOCIATEGAIN   (WM_USER + PP_OFFSET + 30)
#define PPDS_ASSOCIATELOSS   (WM_USER + PP_OFFSET + 31)
                                                   
class CDiagScroll : public CWnd
{
public:
    CDiagScroll 		();
    
// Attributes
private:
	CWnd*				m_pWndAssociate;  		// Associate window handle
	DWORD       		m_dwStyle;        		// Copy of GetWindowLong(hWnd, GWL_STYLE)
	WORD        		m_wState;         		// State flags

// Operations
public:

// Implementation
public:
	virtual ~CDiagScroll();

	BOOL 	Create (DWORD dwStyle, CRect& Rect, CWnd* pParent, UINT nID);
	CWnd*	SetAssociate	(CWnd* pWnd);
	CWnd*	GetAssociate   	()	{ return (m_pWndAssociate); };

private:
	void	PositionChange ();
	void 	Notify (UINT Msg);
	void  	CalcClickedRgn (CRect& Rect, CRgn& Rgn);
	void 	DrawUpperTriangle (CDC* pDC, CPen* pPenHigh, CPen* pPenShadow, BOOL fClicked);
	void 	DrawLowerTriangle (CDC* pDC, CPen* pPenHigh, CPen* pPenShadow, BOOL fClicked);
	void 	StateSet 	(WORD wFlags) { m_wState |= wFlags;  };
	void	StateClear	(WORD wFlags) { m_wState &= ~wFlags; };
	BOOL	StateTest	(WORD wFlags) { return (m_wState & wFlags); };

	// Generated message map functions
protected:
	virtual WNDPROC* 	GetSuperWndProcAddr();

	//{{AFX_MSG(CDiagScroll)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCancelMode();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

