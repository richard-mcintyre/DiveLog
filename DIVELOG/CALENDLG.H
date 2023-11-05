// CALENDLG.H - interface of the CCalenDlg class

//////////////////////////////////////////////////////////////////////////
// CCalenDlg

class CCalenDlg : public CCalendar
{
public:
	static void	RegisterControl ();

	// Generated message map functions
protected:
	virtual void PostNcDestroy ();

	//{{AFX_MSG(CCalenDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


