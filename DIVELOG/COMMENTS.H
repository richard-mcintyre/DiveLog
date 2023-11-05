// COMMENTS.H - interface of the CCommentsDlg

/////////////////////////////////////////////////////////////////////////////
// CCommentsDlg dialog

class CCommentsDlg : public CDialog
{
// Construction
public:
	CCommentsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCommentsDlg)
	enum { IDD = IDD_COMMENTS };
	CString	m_Comments;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CCommentsDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
