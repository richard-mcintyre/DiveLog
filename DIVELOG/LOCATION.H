// LOCATION.H - interface of the CLocationDlg class

/////////////////////////////////////////////////////////////////////////////
// CLocationDlg dialog

class CLocationDlg : public CDialog
{
// Construction
public:
	CLocationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLocationDlg)
	enum { IDD = IDD_LOCATIONLIST };
	CComboBox	m_ctlList;
	CString	m_strEdit;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CLocationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
