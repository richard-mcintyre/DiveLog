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
	CByteArray		m_bData;
	
public:
	int		Find( int nLength );
	void	AddLength( BYTE bLength );
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
	CObArray	m_depths;  // an array of CByteArrays
	
public:
	BOOL	LoadTable( CArchive& ar );
	int		FindMtrs( int nDepth, int nLength );
	int		FindFt( int nDepth, int nLength );
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
	CObArray	m_PG;	// An array of pressure groups (CWordArray)
	
public:
	BOOL	LoadTable( CArchive& ar );
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
	CWordArray m_RNT_ABT;		// LO-Byte = RNT, HI-Byte = ABT
	
public:
	void	Add( BYTE bRNT, BYTE bABT );
	void	Add( WORD wRNT_ABT );
	int		GetRNT( const int nIndex );
	int		GetABT( const int nIndex );
	WORD	GetAt( const int nIndex );
	
private:
	WORD	Combine( BYTE b1, BYTE b2 )	{	return (WORD)((UINT)((BYTE)b1|((WORD)b2<<8)));	}
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
	CObArray	m_PG;	// An array of pressure groups (CWordArray)
	
public:
	BOOL	LoadTable( CArchive& ar );
	WORD	FindMtrs( int nPG, int nDepth );	// returns LO-Byte = RNT, HI-Byte = ABT
	WORD	FindFt( int nPG, int nDepth );	// returns LO-Byte = RNT, HI-Byte = ABT
};


