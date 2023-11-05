/////////////////////////////////////////////////////////////////////////
// reports.h

//class CDiveSet;
//class CDiveData;

class CColumn : public CObject
{		 
protected:
	DECLARE_DYNCREATE( CColumn );
	CColumn( );

public:
	static enum ColType{ Text, Bool, Date, Time, Integer, Temperature, Real, VisStyle };

public:
	CColumn( CString name, ColType colType, int nWidth );

private:
	CString		m_colName;
	CString		m_repName;
	ColType		m_colType;
	int			m_nWidth;
	static BOOL	m_bWarnDate;

public:
	CString	GetName( ) const		{	return m_colName;	}
	int		GetWidth( ) const		{	return m_nWidth;	}
	void	SetWidth( int nWidth )	{	m_nWidth = nWidth;	}
	CString	GetRepName( ) const				{	return m_repName;	}
	void	SetRepName( CString str )		{	m_repName = str;	}
	CString	GetString( CDiveData* pData );
	CString GetIntString( CDiveData* pData );
	CString GetRealString( CDiveData* pData );
	BOOL	TestColumn( CString strVal, CString strOperand, CDiveData* pData );

private:
	CString GetBoolString( CDiveData* pData );
	BOOL	CompInt( int nVal, CString str, CString strOperand );
	BOOL	CompAir( int nVal, CString str, CString strOperand, BOOL bPSI );
	BOOL	CompWeight( int nVal, CString str, CString strOperand, BOOL bKG );
};
	
class CReport : public CObject
{
protected:
	DECLARE_DYNCREATE( CReport );
	CReport( );

public:
	CReport( CDiveSet* pDiveSet );
	~CReport( );

private:
	CDiveSet*	m_pDiveSet;
	CObArray	m_columns;
	CString		m_strLoc;

public:
	CObArray	m_repColumns;
	CStringArray	m_strCols;		// Columns
	CStringArray	m_strOpers;		// Operands
	CStringArray	m_strValue;		// Value
	CStringArray	m_strJoins;		// Logical operators
	int				m_nFilterDepth;

public:
	void		NewCol( CString name, CColumn::ColType, int nWidth );
	CColumn*	GetCol( int nCol );
	int			GetColUpperBound( ) const			{	return m_columns.GetUpperBound();	}
	CColumn*	GetRepCol( int nCol );
	int			GetRepColUpperBound( ) const		{	return m_repColumns.GetUpperBound();	}
	CDiveSet*	GetDiveSet( ) const					{	return m_pDiveSet;					}
	void		SetDiveSet( CDiveSet* pSet )		{	m_pDiveSet = pSet;					}
	CString		GetLocation( ) const				{	return m_strLoc;		}
	void		SetLocation( CString strLoc )		{	m_strLoc = strLoc;		}
};
