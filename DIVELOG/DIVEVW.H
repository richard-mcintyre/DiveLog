// divevw.h : interface of the CDiveView class
//
/////////////////////////////////////////////////////////////////////////////

class CCheckBox;

class CDiveView : public CView
{
protected: // create from serialization only
	CDiveView();
	DECLARE_DYNCREATE(CDiveView)

// Attributes
private:
	CFont*		m_pArialFont;
	CFont*		m_pArialBoldFont;
	CObArray	m_checkBoxes;
	CObArray	m_fldList;
	
	CEdit*		m_pComments;
	CButton*	m_pCommentsZoom;
	
public:
	CDiveDoc* GetDocument();

// Operations
private:
	void 	CreateChkBox( const CRect rect, const CString checked,
								const CString Unchecked, const UINT nID );
	CCheckBox*	GetCheckBox( UINT nID );
	CString		intToStr( int nVal );
	void		ChangeChkBoxState( UINT nID, BOOL bState );
public:
	void		InvalidateFlds( );
	

// Implementation
public:
	virtual ~CDiveView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual	void OnInitialUpdate();

// Generated message map functions
protected:
	//{{AFX_MSG(CDiveView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRecordAdd();
	afx_msg void OnRecordDelete();
	afx_msg void OnRecordFirst();
	afx_msg void OnRecordLast();
	afx_msg void OnRecordNext();
	afx_msg void OnRecordPrev();
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnCommentsZoomClicked();
	afx_msg void OnVisGoodClicked( );
	afx_msg void OnVisOkClicked( );
	afx_msg void OnVisPoorClicked( );
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCheckFreshClicked( );
	afx_msg void OnCheckSaltClicked( );
	afx_msg void OnCheckShoreClicked( );
	afx_msg void OnCheckBoatClicked( );
	afx_msg void OnCheckWavesClicked( );
	afx_msg void OnCheckCurrentClicked( );
	afx_msg void OnCheckSurfClicked( );
	afx_msg void OnCheckSurgeClicked( );
	afx_msg void OnCheckSocksClicked( );
	afx_msg void OnCheckHoodClicked( );
	afx_msg void OnCheckMittensClicked( );
	afx_msg void OnCheckGlovesClicked( );
	afx_msg void OnCheckUSuitClicked( );
	afx_msg void OnCheckDSuitClicked( );
	afx_msg void OnCheckSemiDSuitClicked( );
	afx_msg void OnCheckWetSuitClicked( );
	afx_msg void OnCheckCostumeClicked( );
	afx_msg void OnTempAirLowClicked( );
	afx_msg void OnTempAirMedClicked( );
	afx_msg void OnTempAirHighClicked( );
	afx_msg void OnTempSurfaceLowClicked( );
	afx_msg void OnTempSurfaceMedClicked( );
	afx_msg void OnTempSurfaceHighClicked( );
	afx_msg void OnTempBottomLowClicked( );
	afx_msg void OnTempBottomMedClicked( );
	afx_msg void OnTempBottomHighClicked( );
	afx_msg void OnComboDblClick( );
	afx_msg void OnCommentsChange( );
	afx_msg LRESULT OnEditFldFinished( WPARAM wParam, LPARAM lParam );
};

#ifndef _DEBUG  // debug version in divevw.cpp
inline CDiveDoc* CDiveView::GetDocument()
   { return (CDiveDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
