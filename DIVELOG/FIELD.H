// FIELD.H - interface of the field classes

class CDiveDoc;
class CEditDate;
                
// Notification codes sent via SendMessage
#define BF_FINISHED		( WM_USER + 1 )

//////////////////////////////////////////////////////////////////////////
// CBaseFld - base class for all fields

class CBaseFld : public CEdit
{
public:
	CBaseFld();
	virtual ~CBaseFld();

public:
	static enum fldName{ Visibility, AirStart, AirEnd, TimeIn, TimeOut, Weight, SI, Depth, BottomTime, Stop };

protected:
	CWnd*	m_pParent;
	CDiveSet*	m_pDiveSet;
	CDiveDoc*	m_pDoc;
	CRect	m_rect;
	BOOL	m_bDisplayed;
	fldName	m_fldName;
		
public:
	void	Create( CRect rect, CWnd* pParent, CDiveSet* pDiveSet, CDiveDoc* pDoc );
	BOOL	HitTest( CPoint point ) const;
	CRect	GetRect( ) const;
	fldName GetFieldName() const;
	BOOL	IsFieldDisplayed();
	virtual	void	DisplayFld( CDiveData* pDiveData ) = 0;	// pure virtual
	virtual	BOOL	RemoveFld( CDiveData* pDiveData ) = 0;

protected:
	BOOL	CreateEdit( DWORD dwStyle, const RECT& rect, CWnd* pParent, UINT nID );

// Generated message map functions
protected:
	//{{AFX_MSG(CBaseFld)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// CEditFld

class CEditFld : public CBaseFld
{
public:
	CEditFld();
	DECLARE_DYNCREATE( CEditFld )

protected:

public:
	void	DisplayFld( CDiveData* pDiveData );
	BOOL	RemoveFld( CDiveData* pDiveData );
	void	SetFldName( fldName fn );
};

//////////////////////////////////////////////////////////////////////////
// CEditDateFld

class CEditDateFld : public CBaseFld
{
public:
	CEditDateFld();
	DECLARE_DYNCREATE( CEditDateFld )

protected:
	CEditDate*	m_pEditDate;

public:
	void	DisplayFld( CDiveData* pDiveData );
	BOOL	RemoveFld( CDiveData* pDiveData );
};

//////////////////////////////////////////////////////////////////////////
// CComboFld

class CComboFld : public CBaseFld
{
public:
	CComboFld();
	DECLARE_DYNCREATE( CComboFld )

protected:
	CComboBox*	m_pCombo;
	int			m_nComboHeight;

public:
	void	DisplayFld( CDiveData* pDiveData );
	BOOL	RemoveFld( CDiveData* pDiveData );
	void	SetHeight( int nHeight );
};

