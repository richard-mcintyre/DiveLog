// repview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportView view

class CReportView : public CScrollView
{
protected:
	CReportView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReportView)

// Attributes
private:
	CFont		m_textFont;
	CFont		m_boldFont;
	CFont		m_prnTextFont;		// printing font
	CFont		m_prnBoldFont;		//	"	"	 "
	BOOL		m_bPrinting;
	CPoint		m_prnIndex;
	int			m_nPrnRecs;		

public:
	CReportDoc* GetDocument();
	void		CorrectScrollSize();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CReportView();

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo );

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CReportView)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in divevw.cpp
inline CReportDoc* CReportView::GetDocument()
   { return (CReportDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
