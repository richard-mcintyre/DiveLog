// backpg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackPg dialog

class CBackPg : public CDialog
{
// Construction
public:
	CBackPg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBackPg)
	enum { IDD = IDD_BACK_PAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
	BOOL	Create( CWnd* pParent, UINT nDlg );

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CBackPg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
