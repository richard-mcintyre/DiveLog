// reprtdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportsDlg dialog

class CDiveSet;
class CReport;
class CColumn;

class CReportsDlg : public CDialog
{
// Construction
public:
	CReportsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportsDlg)
	enum { IDD = IDD_REPORTS };
	CEdit	m_ctlRepWidth;
	CEdit	m_ctlRepName;
	CListBox	m_ctlRepCols;
	CListBox	m_ctlCols;
	CString	m_repName;
	int		m_repWidth;
	//}}AFX_DATA
  	CDiveSet*	m_pDiveSet;
	CReport*	m_pReport;
	CColumn*	m_pCurCol;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkColsList();
	afx_msg void OnDblclkRepcolsList();
	afx_msg void OnInsert();
	afx_msg void OnRemove();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnRemoveAll();
	afx_msg void OnInsertAll();
	afx_msg void OnFilter();
	afx_msg void OnSelchangeRepcolsList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
