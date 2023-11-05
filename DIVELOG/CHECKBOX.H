// CHECKBOX.H - interface of the CCheckBox class

//////////////////////////////////////////////////////////////////////////
// CCheckBox

class CCheckBox : public CWnd
{
private:
	CCheckBox();
	DECLARE_DYNCREATE( CCheckBox )
	~CCheckBox();

public:
	CCheckBox( const CRect rect, const CString checked, 
				const CString Unchecked, CWnd* pParent, const UINT nID );
	
protected:
	BOOL		m_bState;
	CRect		m_rect;
	CString		m_checkedRes;	// The name of the checked bitmap
	CString		m_uncheckedRes;
	CWnd*		m_pParent;
	UINT		m_nID;
	CBitmapButton*	m_pBitmapButton;
public:
	static CDocument*	m_pDoc;
	
public:
	void	ChangeState();	// if button is checked, uncheck it, or if button is unchecked, check it
	void	SetState( BOOL bState );
	BOOL	GetState() const;
	UINT	GetID() const;
	void	Enable( BOOL bEnable = TRUE );
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckBox)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
        