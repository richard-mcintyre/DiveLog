// repdoc.h : header file
//

class CDiveSet;

/////////////////////////////////////////////////////////////////////////////
// CReportDoc document

class CReportDoc : public CDocument
{
protected:
	CReportDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReportDoc)

// Attributes
private:
	CReport*	m_pReport;
	CDiveSet*	m_pDiveSet;
	CDiveSet*	m_pRepSet;
	BOOL		m_bRecords;		// if records exists in report
	short		m_nRecs;		// number of records in the report
	short		m_nColsWidth;	// width of all report columns

// Operations
public:
	void	SetReport( CReport* pReport )		{	m_pReport = pReport;	}
	void	SetDiveSet( CDiveSet* pSet )		{	m_pDiveSet = pSet;		}
	void	DoReport( CReport* pReport, CDiveSet* pSet );
	CReport*	GetReport( ) const				{	return m_pReport;		}
	CDiveSet*	GetDiveSet( ) const				{	return m_pDiveSet;		}
	CDiveSet*	GetRepSet( ) const				{	return m_pRepSet;		}
	BOOL		IsRepRecords( ) const			{	return m_bRecords;		}
	short	GetNoOfRecs( ) const				{	return m_nRecs;			}
	short	GetColsWidth( ) const				{	return m_nColsWidth;	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDoc)
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CReportDoc)
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
