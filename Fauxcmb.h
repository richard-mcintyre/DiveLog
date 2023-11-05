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

#ifndef _FAUXCMB_
#define _FAUXCMB_ 

#define OEMRESOURCE		// <----- must be defined before windows.h is #included

#ifndef PP_OFFSET
#define PP_OFFSET			100
#endif

//----- Notification Message
#define PPFC_BTNCLICKED		(WM_USER + PP_OFFSET + 20)
#define PPFC_ASSOCIATEGAIN	(WM_USER + PP_OFFSET + 21)
#define PPFC_ASSOCIATELOSS	(WM_USER + PP_OFFSET + 22)
                                                   
class CFauxCmb : public CWnd
{
// Construction
public:
    CFauxCmb 		();
    
	
// Attributes
public:

protected:
	int					m_DefinedWidth;
	int					m_DefinedHeight;

private:
	CWnd*				m_pWndAssociate;  		// Associate window handle
	DWORD       		m_dwStyle;        		// Copy of GetWindowLong(hWnd, GWL_STYLE)
	WORD        		m_wState;         		// State flags

// Operations
public:
	CWnd* 	SetAssociate (CWnd* NewWnd);
	CWnd*	GetAssociate ()	{ return (m_pWndAssociate); };

	BOOL 	Create (DWORD dwStyle, CRect& Rect, CWnd* pParent, UINT nID);


// Implementation
public:
	virtual ~CFauxCmb();

private:
	void 	Notify (UINT Msg);

	void 	StateSet 	(WORD wFlags) { m_wState |= wFlags;  };
	void	StateClear	(WORD wFlags) { m_wState &= ~wFlags; };
	BOOL	StateTest	(WORD wFlags) { return (m_wState & wFlags); };

	// Generated message map functions
protected:
	virtual WNDPROC* 	GetSuperWndProcAddr();

	//{{AFX_MSG(CFauxCmb)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

