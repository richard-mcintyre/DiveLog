// divedoc.h : interface of the CDiveDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CDiveSet;
class CDiveData;
class CBudSet;
class CBudData;

class CDiveDoc : public CDocument
{
protected: // create from serialization only
	CDiveDoc();
	DECLARE_DYNCREATE(CDiveDoc)

// Attributes
private:
	CDiveSet*	m_pDiveSet;
	CDiveData*	m_pCurDive;
	CPoint		m_curIndex;
	CString		m_frontText;
	CBudSet*	m_pBudSet;
	CBudData*	m_pCurBud;
	int			m_nBudIndex;

public:
	CObArray	m_defDives;
	
// Operations
public:
	void		SetFrontText( CString str )	{	m_frontText = str;		}
	CString		GetFrontText( ) const		{	return m_frontText;		}
	CDiveData*	GetCurRecord( ) const		{	return m_pCurDive;		}
	CPoint		GetCurIndex( ) const		{	return m_curIndex;		}
	CDiveData*	GetDiveData( CPoint index ) const;
	CDiveData*	NewDive( );
	CDiveData*	RemoveDive( );
	CDiveData*	DivePrev( );
	CDiveData*	DiveNext( );
	CDiveData*	DiveFirst( );
	CDiveData*	DiveLast( );
	BOOL		IsFirstDive( ) const;
	BOOL		IsLastDive( ) const;
	BOOL		IsDiveBegin( ) const;	// is the dive the first of the day?
	int			GetNoOfDayDives( int nDay ) const;	// Get the no. of dives on a day
	void		DateChanged( );
	void		DateFinished( );
	CDiveSet*	GetDiveSet( ) const			{	return m_pDiveSet;		}
	CBudData*	GetBudCurRecord( ) const	{	return m_pCurBud;		}
	int			GetBudIndex( ) const		{	return m_nBudIndex;		}
	CBudData*	NewBud( );
	CBudData*	RemoveBud( );
	CBudData*	BudPrev( );
	CBudData*	BudNext( );
	CBudData*	BudFirst( );
	CBudData*	BudLast( );
	BOOL		IsFirstBud( ) const;
	BOOL		IsLastBud( ) const;
	CBudSet*	GetBudSet( ) const			{	return m_pBudSet;		}
	int&		GetBudIndex( )				{	return m_nBudIndex;		}
	CBudData*	FindBud( CString let );

private:
	void		CalcAll();
	void		CalcDiveTables();

// Implementation
public:
	virtual ~CDiveDoc();
	virtual BOOL OnOpenDocument(const char* pszPathName);
	virtual BOOL OnSaveDocument( LPCTSTR lpszPathName );
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CDiveDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
