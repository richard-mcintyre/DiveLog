// TABLES.H - interface of the table classes

//////////////////////////////////////////////////////////////////////////
// CDepth

class CDepth : public CObject
{
public:
	CDepth();
	DECLARE_DYNCREATE( CDepth )
	virtual ~CDepth();

private:
	CWordArray		m_wData;
	
public:
	int		Find( int nLength );
	void	AddLength( int nLength );
};

//////////////////////////////////////////////////////////////////////////
// CTable1

class CTable1 : public CObject
{
public:
	CTable1( );
	DECLARE_DYNCREATE( CTable1 )
	virtual ~CTable1();
	
private:
	CObArray	m_depths;
	
public:
	BOOL	LoadTable();		// loads table1.dat
	int		Find( int nDepth, int nLength );
};	

//////////////////////////////////////////////////////////////////////////
// CSurfaceInt

class CSurfaceInt : public CObject
{
public:
	CSurfaceInt();
	DECLARE_DYNCREATE( CSurfaceInt )
	virtual ~CSurfaceInt();

private:
	CWordArray		m_wData;
	
public:
	int		Find( int nLength );
	void	AddSI( int nSI );
};

//////////////////////////////////////////////////////////////////////////
// CTable2

class CTable2 : public CObject
{
public:
	CTable2( );
	DECLARE_DYNCREATE( CTable2 )
	virtual ~CTable2();
	
private:
	CObArray	m_PG;	// An array of pressure groups
	
public:
	BOOL	LoadTable();		// loads table2.dat
	int		Find( int nPG, int nSI );
};	

//////////////////////////////////////////////////////////////////////////
// CRNT_ABT

class CRNT_ABT : public CObject
{
public:
	CRNT_ABT();
	DECLARE_DYNCREATE( CRNT_ABT )
	virtual ~CRNT_ABT();
	
private:
	CWordArray m_RNT;
	CWordArray m_ABT;
	
public:
	void	Add( int nRNT, int nABT );
	int		GetRNT( int nIndex );
	int		GetABT( int nIndex );
};

//////////////////////////////////////////////////////////////////////////
// CTable3

class CTable3 : public CObject
{
public:
	CTable3();
	DECLARE_DYNCREATE( CTable3 )
	virtual ~CTable3();
	
private:
	CObArray	m_PG;	// An array of pressure groups
	
public:
	BOOL	LoadTable();		// loads table3.dat
	CPoint	Find( int nPG, int nDepth );	// returns CPoint( RNT, ABT )
};


