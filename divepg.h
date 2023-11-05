// divepg.h : header file
//

class CEditDate;
class CDiveView;
class CDiveData;

/////////////////////////////////////////////////////////////////////////////
// CDivePg1 dialog

class CDivePg1 : public CDialog
{
// Construction
public:
	CDivePg1(CDiveView* pParent = NULL);	// standard constructor
	~CDivePg1();

// Dialog Data
	//{{AFX_DATA(CDivePg1)
	enum { IDD = IDD_DIVE_PAGE1 };
	CComboBox	m_ctlLocation;
	CString	m_editVis;
	CString	m_editAirStart;
	CString	m_meaAirStart;
	CString	m_meaVis;
	CString	m_editAirEnd;
	CString	m_meaAirEnd;
	CString	m_editTimeIn;
	CString	m_editTimeOut;
	int		m_radioVis;
	int		m_radioAir;
	int		m_radioBottom;
	int		m_radioSurface;
	//}}AFX_DATA

public:
	BOOL	Create( CDiveView* pParent, UINT nDlg = CDivePg1::IDD );
	void	UpdateControls( CDiveData* pData );

private:
	CFont		m_textFont;
	CFont		m_smallFont;
	CEditDate*	m_pDateCtrl;
	CTime		m_curDate;
	CDiveView*	m_pView;
	CPoint		m_tmpPoint;
	BOOL		m_bCaptured;

private:
	virtual void OnOK();
	virtual void OnCancel();
	
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDivePg1)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnKillfocusEditVis();
	afx_msg void OnKillfocusEditAirStart();
	afx_msg void OnKillfocusEditAirEnd();
	afx_msg void OnKillfocusEditTimeIn();
	afx_msg void OnKillfocusEditTimeOut();
	afx_msg void OnRadioVis();
	afx_msg void OnRadioAir();
	afx_msg void OnRadioSurface();
	afx_msg void OnRadioBottom();
	afx_msg void OnChangeEditDate();
	afx_msg void OnEditchangeLocationCombo();
	afx_msg void OnSelendokLocationCombo();
	afx_msg void OnChangeEditVis();
	afx_msg void OnChangeEditAirStart();
	afx_msg void OnChangeEditAirEnd();
	afx_msg void OnChangeEditTimeIn();
	afx_msg void OnChangeEditTimeOut();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRadioSurfaceWarm();
	afx_msg void OnRadioSurfaceHot();
	afx_msg void OnRadioBottomHot();
	afx_msg void OnRadioBottomWarm();
	afx_msg void OnRadioAirHot();
	afx_msg void OnRadioAirWarm();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	LRESULT OnDateTest(WPARAM WParam, LPARAM LParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDivePg2 dialog

class CDivePg2 : public CDialog
{
// Construction
public:
	CDivePg2(CDiveView* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDivePg2)
	enum { IDD = IDD_DIVE_PAGE2 };
	CString	m_editSI;
	CString	m_meaDepth;
	UINT	m_editStop;
	UINT	m_editBottomTime;
	CString	m_editWeight;
	CString	m_meaWeight;
	BOOL	m_bBoat;
	BOOL	m_bCurrent;
	BOOL	m_bDrySuit;
	BOOL	m_bFresh;
	BOOL	m_bGloves;
	BOOL	m_bHood;
	BOOL	m_bMittens;
	BOOL	m_bSalt;
	BOOL	m_bSDrySuit;
	BOOL	m_bShore;
	BOOL	m_bSocks;
	BOOL	m_bSurf;
	BOOL	m_bSurge;
	BOOL	m_bUnderSuit;
	BOOL	m_bWaves;
	BOOL	m_bWetSuit;
	CString	m_pgAfter;
	CString	m_pgBefore;
	CString	m_strABT;
	CString	m_strRNT;
	CString	m_strTBT;
	CString	m_editDepth;
	//}}AFX_DATA
private:
	CFont		m_smallFont;
	CDiveView*	m_pView;

public:
	BOOL	Create( CDiveView* pParent, UINT nDlg = CDivePg2::IDD );
	void	UpdateControls( CDiveData* pData );
	void 	CalcDiveTables();
	void	DisplayABTTimes( CDiveData* pData );

private:
	virtual void OnOK();
	virtual void OnCancel();

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDivePg2)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEditSI();
	afx_msg void OnKillfocusEditDepth();
	afx_msg void OnKillfocusEditBottomTime();
	afx_msg void OnKillfocusEditStop();
	afx_msg void OnNotes();
	afx_msg void OnKillfocusEditWeight();
	afx_msg void OnCheckBoxClicked();
	afx_msg void OnChangeEditSi();
	afx_msg void OnChangeEditDepth();
	afx_msg void OnChangeEditBottomTime();
	afx_msg void OnChangeEditStop();
	afx_msg void OnChangeEditWeight();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
