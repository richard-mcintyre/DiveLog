// buddata.h : header file
//

class CBudData;

///////////////////////////////////////////////////////////////////////////
// CBudSet

class CBudSet : public CObject
{
public:
	CBudSet( );
	DECLARE_DYNCREATE( CBudSet )
	~CBudSet();

public:
	static enum Index{ Unindexed, A, B, C, D, E, F, G, H, I, J, K, L, M,
									N, O, P, Q, R, S, T, U, V, W, X, Y, Z };
private:
	CObArray	m_recs;
	CUIntArray	m_access;

public:
	int			AddRec( CBudData* pData );
	int			RemoveRec( const int nIndex );
	int			GetNoOfRecs( ) const		{	return m_recs.GetUpperBound();	}
	int			BudPrev( int nIndex, CBudData** pData );
	int			BudNext( int nIndex, CBudData** pData );
	int			BudFirst( CBudData** pData );
	int			BudLast( CBudData** pData );
	CBudData*	GetBudData( int nIndex ) const;
	BOOL		IsLastBud( int nIndex );
	void		LastNameChanged( CString strOld, CString strNew, int& nIndex );
	int			GetQuickIndex( CBudSet::Index ind ) const	{	return m_access.GetAt( ind );	}
	int			FindBud( CString let, CBudData** pData );

private:
	int			IncAccess( CString strLetter );
	int			DeIncAccess( CString strLetter );

public:
	virtual void Serialize( CArchive& ar );	// overridden for i/o	
};

/////////////////////////////////////////////////////////////////////////////
// CBudData - A buddy record

class CBudData : public CObject
{
public:
	CBudData();
	DECLARE_DYNCREATE( CBudData )
	~CBudData();

private:
	CString	m_strTitle;
	CString	m_strFirstName;
	CString	m_strLastName;
	CString	m_strAddress;
	CString	m_strPhone;
	CString	m_strFAX;
	CString m_strNotes;

public:		// inline functions
	CString	GetTitle( ) const				{	return m_strTitle;		}
	void	SetTitle( CString str )			{	m_strTitle = str;		}
	CString	GetFirstName( ) const			{	return m_strFirstName;	}
	void	SetFirstName( CString str )		{	m_strFirstName = str;	}
	CString	GetLastName( ) const			{	return m_strLastName;	}
	void	SetLastName( CString str )		{	m_strLastName = str;	}
	CString	GetAddress( ) const				{	return m_strAddress;	}
	void	SetAddress( CString str )		{	m_strAddress = str;		}
	CString	GetPhone( ) const				{	return m_strPhone;		}
	void	SetPhone( CString str )			{	m_strPhone = str;		}
	CString	GetFAX( ) const					{	return m_strFAX;		}
	void	SetFAX( CString str )			{	m_strFAX = str;			}
	CString	GetNotes( ) const				{	return m_strNotes;		}
	void	SetNotes( CString str )			{	m_strNotes = str;		}

public:
	virtual void Serialize( CArchive& ar );	// overridden for i/o	
	CBudData&	operator=( CBudData* pData );
};

