// FAUXDLG.H - interface of the CFauxDlg class

//////////////////////////////////////////////////////////////////////////
// CFauxDlg
class CFauxDlg : public CFauxCmb
{
public:
	static void 		RegisterControl ();

// Generated message map functions
protected:
	virtual void 		PostNcDestroy ();

	//{{AFX_MSG(CFauxDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

