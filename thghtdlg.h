// thghtdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThoughtDlg dialog

class CThoughtDlg : public CDialog
{
// Construction
public:
	CThoughtDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CThoughtDlg)
	enum { IDD = IDD_THOUGHT_DAY };
	BOOL	m_bShow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThoughtDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThoughtDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
