// buddypg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuddyP1 dialog

class CDiveView;
class CBudData;

class CBuddyP1 : public CDialog
{
// Construction
public:
	CBuddyP1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBuddyP1)
	enum { IDD = IDD_BUDDY_PAGE1 };
	CString	m_strTitle;
	CString	m_strAddress;
	CString	m_strFAX;
	CString	m_strFirstName;
	CString	m_strLastName;
	CString	m_strPhone;
	//}}AFX_DATA


public:
	BOOL	Create( CDiveView* pParent, UINT nDlg = CBuddyP1::IDD );
	void	UpdateControls( CBudData* pData );

private:
	CDiveView*	m_pView;
	void	UpdateButtons( );

private:
	virtual void OnOK();
	virtual void OnCancel();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuddyP1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuddyP1)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillfocusTitle();
	afx_msg void OnChangeTitle();
	afx_msg void OnChangeFirstname();
	afx_msg void OnKillfocusFirstname();
	afx_msg void OnChangeLastname();
	afx_msg void OnKillfocusLastname();
	afx_msg void OnChangeAddress();
	afx_msg void OnKillfocusAddress();
	afx_msg void OnChangePhone();
	afx_msg void OnKillfocusPhone();
	afx_msg void OnChangeFax();
	afx_msg void OnKillfocusFax();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CBuddyP2 dialog

class CBuddyP2 : public CDialog
{
// Construction
public:
	CBuddyP2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBuddyP2)
	enum { IDD = IDD_BUDDY_PAGE2 };
	CButton	m_ctlButZ;
	CButton	m_ctlButY;
	CButton	m_ctlButX;
	CButton	m_ctlButW;
	CButton	m_ctlButV;
	CButton	m_ctlButU;
	CButton	m_ctlButT;
	CButton	m_ctlButS;
	CButton	m_ctlButR;
	CButton	m_ctlButQ;
	CButton	m_ctlButP;
	CButton	m_ctlButO;
	CButton	m_ctlButN;
	CButton	m_ctlButM;
	CButton	m_ctlButL;
	CButton	m_ctlButK;
	CButton	m_ctlButJ;
	CButton	m_ctlButI;
	CButton	m_ctlButH;
	CButton	m_ctlButG;
	CButton	m_ctlButF;
	CButton	m_ctlButE;
	CButton	m_ctlButD;
	CButton	m_ctlButC;
	CButton	m_ctlButB;
	CButton	m_ctlButA;
	CString	m_strNotes;
	//}}AFX_DATA

public:
	BOOL	Create( CDiveView* pParent, UINT nDlg = CBuddyP2::IDD );
	void	UpdateControls( CBudData* pData );
	void	UpdateButtons( );

private:
	CDiveView*	m_pView;

private:
	virtual void OnOK();
	virtual void OnCancel();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuddyP2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuddyP2)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChangeNotes();
	afx_msg void OnKillfocusNotes();
	afx_msg void OnButtonA();
	afx_msg void OnButtonB();
	afx_msg void OnButtonC();
	afx_msg void OnButtonD();
	afx_msg void OnButtonE();
	afx_msg void OnButtonF();
	afx_msg void OnButtonG();
	afx_msg void OnButtonH();
	afx_msg void OnButtonI();
	afx_msg void OnButtonJ();
	afx_msg void OnButtonK();
	afx_msg void OnButtonL();
	afx_msg void OnButtonM();
	afx_msg void OnButtonN();
	afx_msg void OnButtonO();
	afx_msg void OnButtonP();
	afx_msg void OnButtonQ();
	afx_msg void OnButtonR();
	afx_msg void OnButtonS();
	afx_msg void OnButtonT();
	afx_msg void OnButtonU();
	afx_msg void OnButtonV();
	afx_msg void OnButtonW();
	afx_msg void OnButtonX();
	afx_msg void OnButtonY();
	afx_msg void OnButtonZ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
