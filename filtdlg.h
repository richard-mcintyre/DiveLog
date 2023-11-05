// filtdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilterDlg dialog

class CReport;

class CFilterDlg : public CDialog
{
// Construction
public:
	CFilterDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilterDlg)
	enum { IDD = IDD_REPORTS_FILTER };
	CEdit	m_ctlValue3;
	CEdit	m_ctlValue2;
	CEdit	m_ctlValue1;
	CComboBox	m_ctlOper3;
	CComboBox	m_ctlOper2;
	CComboBox	m_ctlOper1;
	CComboBox	m_ctlJoin2;
	CComboBox	m_ctlJoin1;
	CComboBox	m_ctlCol3;
	CComboBox	m_ctlCol2;
	CComboBox	m_ctlCol1;
	//}}AFX_DATA
	CReport*	m_pReport;
	CStringArray	m_strCols;		// Columns
	CStringArray	m_strOpers;		// Operands
	CStringArray	m_strValue;		// Value
	CStringArray	m_strJoins;		// Logical operators
	int				m_nFilterDepth;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeJoin1();
	afx_msg void OnCloseupJoin1();
	afx_msg void OnCloseupJoin2();
	afx_msg void OnEditchangeJoin2();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
