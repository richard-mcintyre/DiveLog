// toolbar.h : header file
//

class CTipDlg;

/////////////////////////////////////////////////////////////////////////////
// CLSToolBar window

class CLSToolBar : public CToolBar
{
// Construction
public:
	CLSToolBar();

// Attributes
private:
	BOOL	m_bActive;	// tool tip active?
	BOOL	m_bMouse;	// Mouse over toolbar?
	CString	m_text;		// The tool tip text
	CString m_displayedText;
	int		m_nButtons;	// Number of buttons on tool bar
	CStringArray* m_pTips;	// The actual tips
	CRect	m_tipWndPos;
	
	CTipDlg*	m_pTipDlg;
	BOOL		m_bTipActive;
	BOOL		m_bLeftBDown;
	
	COLORREF	m_textColor;
	COLORREF	m_fillColor;
	BOOL		m_bDisplayTips;
	LOGFONT		m_logFont;
	int			m_time;
	
// Operations
public:
	void	SetNoOfButtons( int nButtons )		{	m_nButtons = nButtons;	}
	void	SetTipsText( CStringArray* pTips )	{	m_pTips = pTips;		}
	void	DisplayTip();
	void	ShowProperties();

// Implementation
public:
	virtual ~CLSToolBar();

protected:
	// Generated message map functions
	//{{AFX_MSG(CLSToolBar)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CTipDlg dialog

class CTipDlg : public CDialog
{
// Construction
public:
	CTipDlg(CWnd* pParent = NULL);	// standard constructor
	~CTipDlg();
	
// Dialog Data
	//{{AFX_DATA(CTipDlg)
	enum { IDD = IDD_TOOLTIP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CString	m_text;		// The tool tip text
	CRect	m_pos;
	COLORREF	m_textColor;
	COLORREF	m_fillColor;
	CFont*		m_pFont;
		
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CTipDlg)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CToolBarPropDlg dialog

class CToolBarPropDlg : public CDialog
{
// Construction
public:
	CToolBarPropDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CToolBarPropDlg)
	enum { IDD = IDD_TOOLBAR_PROP };
	BOOL	m_bShow;
	int		m_time;
	BOOL	m_bTips;
	//}}AFX_DATA
	
	COLORREF	m_textColor;
	COLORREF	m_fillColor;
	LOGFONT		m_logFont;

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CToolBarPropDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSetfillcolor();
	afx_msg void OnSettextcolor();
	afx_msg void OnFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
