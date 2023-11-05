// DIADLG.H - interface of the CDiagDlg class

//////////////////////////////////////////////////////////////////////////
// CDiagDlg

class CDiagDlg : public CDiagScroll
{
public:
	static void	RegisterControl ();
// Generated message map functions
protected:
	virtual void	PostNcDestroy ();

	//{{AFX_MSG(CDiagDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


