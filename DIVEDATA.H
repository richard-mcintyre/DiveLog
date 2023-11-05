// DIVEDATA.H - interface of the CDiveData, CDiveDay and CDiveSet

class CDiveData;		// forward declaration
class CDiveDay;

// Dive type
#define	DT_FRESH	0x01L
#define DT_SALT		0x02L
#define DT_SHORE	0x04L
#define DT_BOAT		0x08L
#define DT_WAVES	0x10L
#define DT_CURRENT	0x20L
#define DT_SURF		0x40L
#define DT_SURGE	0x80L

// Exposure Protection
#define EP_DRYSUIT	0x01L
#define EP_WETSUIT  0x02L
#define EP_SDRYSUIT	0x04L
#define EP_USUIT	0x08L
#define EP_GLOVES	0x10L
#define EP_MITTENS	0x20L
#define EP_HOOD		0x40L
#define EP_SOCKS	0x80L

///////////////////////////////////////////////////////////////////////////
// CDiveSet

class CDiveSet : public CObject
{
public:
	CDiveSet( );
	DECLARE_DYNCREATE( CDiveSet )
	~CDiveSet();

private:
	CObArray	m_diveDay;
	BYTE		m_fileVersion;
	CTime		m_totalABT;

public:
	BOOL		m_bReport;
	
public:
	CPoint		AddDive( CDiveData* pData );
	CPoint		RemoveDive( const CPoint index );
	int			AddDay( CDiveDay* pDay );
	CDiveDay*	GetDay( int nIndex ) const;
	int			GetNoOfDives( ) const		{	return m_diveDay.GetUpperBound();	}
	CPoint		DivePrev( CPoint index, CDiveData** pData );
	CPoint		DiveNext( CPoint index, CDiveData** pData );
	CPoint		DiveFirst( CPoint index, CDiveData** pData );
	CPoint		DiveLast( CPoint index, CDiveData** pData );
	CDiveData*	GetDiveData( CPoint index ) const;
	int			GetNoOfDayDives( int nDay ) const;
	BOOL		IsLastDive( CPoint index );
	CPoint		DateChanged( CPoint oldIndex, CDiveData** pData );
	CTime		GetTotalABT( ) const		{	return m_totalABT;		}
	void		SetTotalABT( CTime tm )		{	m_totalABT = tm;		}
	BYTE		GetFileVersion( ) const		{	return m_fileVersion;	}
	void		SetFileVersion( BYTE fv )	{	m_fileVersion = fv;		}
	CTime		GetABTtoDate( CDiveData* pData );
	void		CalcRNTDay( CPoint index );
	int			GetDiveNo( CPoint index );

public:
	virtual void Serialize( CArchive& ar );	// overridden for i/o	
	virtual void SerializeVer1( CArchive& ar );
};

///////////////////////////////////////////////////////////////////////////
// CDiveDay

class CDiveDay : public CObject
{
public:
	CDiveDay( CTime date = CTime( 1980, 1, 1, 0, 0, 0 ) );
	DECLARE_DYNCREATE( CDiveDay )
	~CDiveDay();
	
private:
	CObArray	m_diveData;
	CTime		m_date;
	
public:
	int			AddDive( CDiveData* pData );
	CDiveData*	GetDive( int nIndex );
	void		RemoveEntry( int nIndex );
	int			GetNoOfDives( ) const		{	return m_diveData.GetUpperBound();	}
	CTime		GetDate( ) const			{	return m_date;						}
	void		SetDate( CTime date )		{	m_date = date;						}
	BOOL		GetTotalABT( CTimeSpan& ts, CDiveData* pData );
	
public:
	virtual void Serialize( CArchive& ar );	// overridden for i/o	
};

///////////////////////////////////////////////////////////////////////////
// CDiveData

class CDiveData : public CObject
{
public:
	CDiveData();
	DECLARE_DYNCREATE( CDiveData )
	~CDiveData();

public:
	static enum	VisStyle{	Good, Medium, Poor	};
	static enum Temperature{	Cold, Warm, Hot	};
private:
	int		m_nDiveNo;		// dive no done this day
	CTime	m_date;
	CString	m_location;
	VisStyle	m_visibility;	float	m_visDist;	BYTE	m_btVisFeet;
	int			m_nAirStart;	int		m_nAirEnd;	BYTE	m_btAirPSI;
	CTime	m_timeIn;		CTime	m_timeOut;
	Temperature	m_air;	Temperature	m_surface;	Temperature	m_bottom;
	
	BYTE	m_btDiveType;
	BYTE	m_btExpPro;
	BYTE	m_btCostume;	// for Dive Log v1
	int		m_nWeight;		BYTE	m_btKG;			CString	m_notes;
	
	// Dive Table info.
	int		m_nLstPG;	// Pressure group from previous dive
	CTime	m_surfaceInt;
	CString	m_PGBeforeDive;
	float	m_depth;	BYTE	m_btDepthMts;
	int		m_nBottomTime;
	int		m_nStop;	// five meter stop
	CString	m_PGAfterDive;
	
	CTime	m_ABTtoDate;
	CTime	m_ABTDive;		// ABT this dive
	
	// Table 3 info
	int		m_nRNT;
	int		m_nABT;
	int		m_nTBT;

private:
	void	SetDTState( BYTE val )				{	m_btDiveType |= val;			}
	void	ClearDTState( BYTE val )			{	m_btDiveType &= ~val;			}
	BOOL	GetDTState( BYTE val ) const		{	return (m_btDiveType & val)!=0 ? TRUE : FALSE;	}
	void	SetEPState( BYTE val )				{	m_btExpPro |= val;			}
	void	ClearEPState( BYTE val )			{	m_btExpPro &= ~val;			}
	BOOL	GetEPState( BYTE val ) const		{	return (m_btExpPro & val)!=0 ? TRUE : FALSE;	}
	BYTE	GetDiveType( ) const				{	return m_btDiveType;		}
	void	SetDiveType( BYTE byte )			{	m_btDiveType = byte;		}
    BYTE	GetExpPro( ) const					{	return m_btExpPro;			}
	void	SetExpPro( BYTE byte )				{	m_btExpPro = byte;			}

public:		// inline functions
	int		GetDiveNo( ) const					{	return m_nDiveNo;			}
	void	SetDiveNo( const int nDive )		{	m_nDiveNo = nDive;			}
	CTime	GetDate( ) const					{	return m_date;				}
	void	SetDate( CTime date )				{	m_date = date;				}
	CString GetLoc( ) const						{	return m_location;			}
	void	SetLoc( const CString loc )			{	m_location = loc;			}
	VisStyle	GetVis( ) const					{	return m_visibility;		}
	void	SetVis( const VisStyle vis )		{	m_visibility = vis;			}
	float	GetVisDist( ) const					{	return m_visDist;			}
	void	SetVisDist( const float dist )		{	m_visDist = dist;			}
	BOOL	GetVisFt( ) const					{	return (BOOL)m_btVisFeet;	}
	void	SetVisFt( const BOOL bFt )			{	m_btVisFeet = (BYTE)bFt;	}
	int		GetAirStart( ) const				{	return m_nAirStart;			}
	void	SetAirStart( const int nAir )		{	m_nAirStart = nAir;			}
	int		GetAirEnd( ) const					{	return m_nAirEnd;			}
	void	SetAirEnd( const int nAir )			{	m_nAirEnd = nAir;			}
	BOOL	GetAirPSI( ) const					{	return (BOOL)m_btAirPSI;	}
	void	SetAirPSI( const BOOL bPSI )		{	m_btAirPSI = (BYTE)bPSI;	}
	CTime	GetTimeIn( ) const					{	return m_timeIn;			}
	void	SetTimeIn( const CTime tm )			{	m_timeIn = tm;				}
	CTime	GetTimeOut( ) const					{	return m_timeOut;			}
	void	SetTimeOut( const CTime tm )		{	m_timeOut = tm;				}
	Temperature	GetAirTemp( ) const				{	return m_air;				}
	void		SetAirTemp( const Temperature tmp )		{	m_air = tmp;				}
	Temperature	GetSurfaceTemp( ) const					{	return m_surface;			}
	void		SetSurfaceTemp( const Temperature tmp )	{	m_surface = tmp;			}
	Temperature	GetBottomTemp( ) const					{	return m_bottom;			}
	void		SetBottomTemp( const Temperature tmp )	{	m_bottom = tmp;				}
    BOOL	GetFresh( ) const					{	return GetDTState( DT_FRESH );							}
	void	SetFresh( const BOOL b )			{	b ? SetDTState( DT_FRESH ) : ClearDTState( DT_FRESH );	}
	BOOL	GetShore( ) const					{	return GetDTState( DT_SHORE );							}
	void	SetShore( const BOOL b )			{	b ? SetDTState( DT_SHORE ) : ClearDTState( DT_SHORE );	}
	BOOL	GetWaves( ) const					{	return GetDTState( DT_WAVES );							}
	void	SetWaves( const BOOL b )			{	b ? SetDTState( DT_WAVES ) : ClearDTState( DT_WAVES );	}
	BOOL	GetSurf( ) const					{	return GetDTState( DT_SURF );							}
	void	SetSurf( const BOOL b )				{	b ? SetDTState( DT_SURF ) : ClearDTState( DT_SURF );	}
	BOOL	GetSalt( ) const					{	return GetDTState( DT_SALT );							}
	void	SetSalt( const BOOL b )				{	b ? SetDTState( DT_SALT ) : ClearDTState( DT_SALT );	}
	BOOL	GetBoat( ) const					{	return GetDTState( DT_BOAT );							}
	void	SetBoat( const BOOL b )				{	b ? SetDTState( DT_BOAT ) : ClearDTState( DT_BOAT );	}
	BOOL	GetCurrent( ) const					{	return GetDTState( DT_CURRENT );						}
	void	SetCurrent( const BOOL b )			{	b ? SetDTState( DT_CURRENT ) : ClearDTState( DT_CURRENT );	}
	BOOL	GetSurge( ) const					{	return GetDTState( DT_SURGE );							}
	void	SetSurge( const BOOL b )			{	b ? SetDTState( DT_SURGE ) : ClearDTState( DT_SURGE );	}
	BOOL	GetCostume( ) const					{	return (BOOL)m_btCostume;	}
	void	SetCostume( const BOOL bByte )		{	m_btCostume = (BYTE)bByte;	}
	BOOL	GetWetSuit( ) const					{	return GetEPState( EP_WETSUIT );							}
	void	SetWetSuit( const BOOL b )			{	b ? SetEPState( EP_WETSUIT ) : ClearEPState( EP_WETSUIT );	}
	BOOL	GetUSuit( ) const					{	return GetEPState( EP_USUIT );								}
	void	SetUSuit( const BOOL b )			{	b ? SetEPState( EP_USUIT ) : ClearEPState( EP_USUIT );		}
	BOOL	GetSDrySuit( ) const				{	return GetEPState( EP_SDRYSUIT );							}
	void	SetSDrySuit( const BOOL b )			{	b ? SetEPState( EP_SDRYSUIT ) : ClearEPState( EP_SDRYSUIT );}
	BOOL	GetDrySuit( ) const					{	return GetEPState( EP_DRYSUIT );							}
	void	SetDrySuit( const BOOL b )			{	b ? SetEPState( EP_DRYSUIT ) : ClearEPState( EP_DRYSUIT );	}
	BOOL	GetGloves( ) const					{	return GetEPState( EP_GLOVES );								}
	void	SetGloves( const BOOL b )			{	b ? SetEPState( EP_GLOVES ) : ClearEPState( EP_GLOVES );	}
	BOOL	GetMittens( ) const					{	return GetEPState( EP_MITTENS );							}
	void	SetMittens( const BOOL b )			{	b ? SetEPState( EP_MITTENS ) : ClearEPState( EP_MITTENS );	}
	BOOL	GetHood( ) const					{	return GetEPState( EP_HOOD );								}
	void	SetHood( const BOOL b )				{	b ? SetEPState( EP_HOOD ) : ClearEPState( EP_HOOD );		}
	BOOL	GetSocks( ) const					{	return GetEPState( EP_SOCKS );								}
	void	SetSocks( const BOOL b )			{	b ? SetEPState( EP_SOCKS ) : ClearEPState( EP_SOCKS );		}
	int		GetWeight( ) const					{	return m_nWeight;			}
	void	SetWeight( const int nWeight )		{	m_nWeight = nWeight;		}
	BOOL	GetWeightKG( ) const				{	return (BOOL)m_btKG;		}
	void	SetWeightKG( const BOOL bByte )		{	m_btKG = (BYTE)bByte;		}
	CString GetNotes( ) const					{	return m_notes;				}
	void	SetNotes( const CString notes )		{	m_notes = notes;			}
	int		GetLstPG( ) const					{	return m_nLstPG;			}
	void	SetLstPG( const int nPG )			{	m_nLstPG = nPG;				}
	CTime	GetSurfaceInt( ) const				{	return m_surfaceInt;		}
	void	SetSurfaceInt( const CTime nPG )	{	m_surfaceInt = nPG;			}
	int		GetLastPG( ) const					{	return m_nLstPG;			}
	void	SetLastPG( const int nPG )			{	m_nLstPG = nPG;				}
	CTime	GetSI( ) const						{	return m_surfaceInt;		}
	void	SetSI( const CTime si )				{	m_surfaceInt = si;			}
	CString	GetPGBeforeDive( ) const			{	return m_PGBeforeDive;		}
	void	SetPGBeforeDive( const CString pg )	{	m_PGBeforeDive = pg;		}
	float	GetDepth( ) const					{	return m_depth;				}
	void	SetDepth( const float depth )		{	m_depth = depth;			}
	BOOL	GetDepthMts( ) const				{	return (BOOL)m_btDepthMts;	}
	void	SetDepthMts( BOOL bByte )			{	m_btDepthMts = (BYTE)bByte;	}
	int		GetBottomTime( )  const				{	return m_nBottomTime;		}
	void	SetBottomTime( const int nBT )		{	m_nBottomTime = nBT;		}
	int		GetDecompStop( )  const				{	return m_nStop;				}
	void	SetDecompStop( const int nStop )	{	m_nStop = nStop;			}
	CString	GetPGAfterDive( ) const				{	return m_PGAfterDive;		}
	void	SetPGAfterDive( const CString pg )	{	m_PGAfterDive = pg;			}
	CTime	GetABTtoDate( ) const				{	return m_ABTtoDate;			}
	void	SetABTtoDate( const CTime tm )		{	m_ABTtoDate = tm;			}
	CTime	GetABTDive( ) const					{	return m_ABTDive;			}
	void	SetABTDive( const CTime tm )		{	m_ABTDive = tm;				}
	int		GetRNT( ) const						{	return m_nRNT;				}
	void	SetRNT( const int nRNT )			{	m_nRNT = nRNT;				}
	int		GetABT( ) const						{	return m_nABT;				}
	void	SetABT( const int nABT )			{	m_nABT = nABT;				}
	int		GetTBT( ) const						{	return m_nTBT;				}
	void	SetTBT( const int nTBT )			{	m_nTBT = nTBT;				}

	void	IncABTtoDate( const CTimeSpan ts )	{	m_ABTtoDate += ts;			}

public:
	virtual void Serialize( CArchive& ar );	// overridden for i/o	
	virtual void SerializeVer1( CArchive& ar, CDiveSet* pSet );
	//CDiveData&	operator=( CDiveData* pData );
	CDiveData&	TransInfo( CDiveData* pData );
};

