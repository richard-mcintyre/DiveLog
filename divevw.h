// divevw.h : interface of the CDiveView class
//
/////////////////////////////////////////////////////////////////////////////

class CFrontPg;
class CBackPg;
class CDivePg1;
class CDivePg2;
class CBuddyP1;
class CBuddyP2;
class CCalendar;

class CDiveView : public CScrollView
{
protected: // create from serialization only
	CDiveView();
	DECLARE_DYNCREATE(CDiveView)

// Attributes
public:
	CDiveDoc* GetDocument();
	static enum Section{	Front, Dive, Buddy, Back	};
private:
	CFrontPg*	m_pFrontPg;
	CBackPg*	m_pBackPg;
	CDivePg1*	m_pDivePg1;
	CDivePg2*	m_pDivePg2;
	CBuddyP1*	m_pBuddyPg1;
	CBuddyP2*	m_pBuddyPg2;
	CBitmapButton	m_nextPage;
	CBitmapButton	m_prevPage;
	Section		m_curSection;
	CRect		m_rightPgRect;
	CRect		m_leftPgRect;
	CRect		m_coverRect;
	CPoint		m_tmpPoint;		// used in OnLButtonDown
	CRect		m_leftDiveTab;
	CRect		m_rightDiveTab;
	CRect		m_leftBuddyTab;
	CRect		m_rightBuddyTab;
	BOOL		m_bLDiveTab;
	BOOL		m_bRDiveTab;
	BOOL		m_bLBuddyTab;
	BOOL		m_bRBuddyTab;
	CRect		m_rectDraw;
	CSize		m_size;
	BOOL		m_bBlank;		// Print blank dive
	//static CLIPFORMAT	m_cbDive;
	                         
// Operations
private:
	void	DrawBindingRing( CPoint pt, int nWidth, CDC* pDC );
	CRect	DrawTab( CPoint startPt, CString m_text, BOOL bBold,
						BOOL bRight, COLORREF cr, CDC* pDC, BOOL bDraw = TRUE );
	void	DrawShadowedRect( CRect rect, CDC* pDC );
	void	DrawCheckBox( CDC* pDC, CRect rect, BOOL bChecked, CString str="" );
	void	RemoveDive( );

public:
	void	OnNextpage();
	void	OnPrevpage();
	void	UpdateDivePageControls();
	CDivePg1*	GetDivePage1( ) const		{	return m_pDivePg1;	}
	CDivePg2*	GetDivePage2( ) const		{	return m_pDivePg2;	}
	void	RemoveCurDive( )				{	RemoveDive();		}
	void	RemoveCurBud( )				{	RemoveDive();		}
	CBuddyP2*	GetBudPage2( ) const		{	return m_pBuddyPg2;	}
	void	FindBud( CString let );

// Implementation
public:
	virtual ~CDiveView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate(); // called first time after construct

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo );

// Generated message map functions
protected:
	//{{AFX_MSG(CDiveView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDiveNew();
	afx_msg void OnRecordPrev();
	afx_msg void OnRecordNext();
	afx_msg void OnRecordFirst();
	afx_msg void OnRecordLast();
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnEditLocations();
	afx_msg void OnDefSetttings();
	afx_msg void OnReports();
	afx_msg void OnDiveRemove();
	afx_msg void OnEditCopy();
	afx_msg void OnFilePrintBlank();
	afx_msg void OnUpdateDefSetttings(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDiveNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDiveRemove(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	afx_msg void OnNextPageClicked();
	afx_msg void OnPrevPageClicked();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in divevw.cpp
inline CDiveDoc* CDiveView::GetDocument()
   { return (CDiveDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
