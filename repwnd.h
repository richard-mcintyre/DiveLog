// repwnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportWnd frame

class CReportWnd : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CReportWnd)
protected:
	CReportWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportWnd)
	//}}AFX_VIRTUAL

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;

// Implementation
protected:
	virtual ~CReportWnd();

	// Generated message map functions
	//{{AFX_MSG(CReportWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
