// divedoc.h : interface of the CDiveDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CForm;
class CTable1;
class CTable2;
class CTable3;
class CDiveSet;
class CReportData;

class CDiveDoc : public CDocument
{
protected: // create from serialization only
	CDiveDoc();
	DECLARE_DYNCREATE(CDiveDoc)

// Attributes
private:
	CForm*		m_pForm;
	
public:
	CStringArray	m_locations;
	CDiveSet*		m_pDiveSet;
	CTable1*	m_pTable1;
	CTable2*	m_pTable2;
	CTable3*	m_pTable3;
	
// Operations
public:
	void	DrawForm( CDC* pDC ) const;
	CTable1*	GetTable1() const	{	return m_pTable1;	}
	CTable2*	GetTable2() const	{	return m_pTable2;	}
	CTable3*	GetTable3() const	{	return m_pTable3;	}
	void		ReadLocations();
	
// Implementation
public:
	virtual ~CDiveDoc();
	virtual BOOL OnOpenDocument( const char* pszPathName );
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	virtual BOOL OnNewDocument();
	
protected:
//	virtual BOOL OnOpenDocument( const char* pszPathName );
	virtual void DeleteContents();

// Generated message map functions
protected:
	//{{AFX_MSG(CDiveDoc)
	afx_msg void OnLocations();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
