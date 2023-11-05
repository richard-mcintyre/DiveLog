// frontpg.h : header file
//

class CDiveView;

/////////////////////////////////////////////////////////////////////////////
// CFrontPg dialog

class CFrontPg : public CDialog
{
// Construction
public:
	CFrontPg(CDiveView* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFrontPg)
	enum { IDD = IDD_FRONT_PAGE };
	CEdit	m_ctlEdit;
	//}}AFX_DATA

private:
	CDiveView*	m_pView;

public:
	BOOL	Create( CDiveView* pParent, UINT nDlg );

private:
	virtual void OnOK( );
	virtual void OnCancel( );

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CFrontPg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditFront();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
