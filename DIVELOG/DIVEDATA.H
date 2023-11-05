// DIVEDATA.H - interface of the CDiveData & CDiveSet classes

//////////////////////////////////////////////////////////////////////////
// CDiveData

class CDiveDoc;
class CDiveSet;

class CDiveData : public CObject
{
public:
	CDiveData();
	DECLARE_SERIAL( CDiveData )
	~CDiveData();

public:
	CDiveSet* m_pDiveSet;
	
// DiveData for current dive
public:
	int			m_nDiveNo;
	CTime		m_date;
	CString		m_location;
	
	// Visibility
	static enum	VisStyle{ Good, OK, Poor };
	VisStyle	m_Visibility;	int	m_VisDist;	BOOL	m_bVisFeet;

	int			m_nAirStart;	BOOL		m_bPSIStart;
	int			m_nAirEnd;		BOOL		m_bPSIEnd;
	CTime		m_timeIn;		CTime		m_timeOut;
	
	// Temperature
	static enum Temperature{ Cold, Warm, Hot };
	Temperature	m_air;	Temperature	m_surface;	Temperature	m_bottom;

	BOOL		m_bFresh;	BOOL		m_bShore;	BOOL		m_bWaves;
	BOOL		m_bSurf;	BOOL		m_bSalt;	BOOL		m_bBoat;
	BOOL		m_bCurrent;	BOOL		m_bSurge;
	// Weight
	int			m_nWeight;	BOOL		m_bKG;
	
	// Exposure protection
	BOOL	m_bSwimmingCost;	BOOL		m_bWetSuit;	BOOL		m_bUnderSuit;
	BOOL	m_bSemiDrySuit;		BOOL		m_bDrySuit;	BOOL		m_bGloves;
	BOOL	m_bMittens;			BOOL		m_bHood;	BOOL		m_bSocks;
	CString		m_comments;
	
	// Dive table info
	int			m_nLastDivePG;	// Pressure group from previous dive
	CTime		m_surfaceInt;
	CString		m_PGBeforeDive;
	float		m_nDepth;
	int			m_nBottomTime;
	int			m_nStop;	// a five meter stop
	CString		m_PGAfterDive;
	
	CTime		m_ABTtoDate;
	CTime		m_ABTDive;		// ABT this dive
	
	// Table3 info
	int		m_nRNT;
	int		m_nABT;
	int		m_nTBT;
	
	void	TransferInfo( CDiveData* pData );
	
// Overridables
	virtual void Serialize(CArchive& ar);   // overridden for i/o
};	

//////////////////////////////////////////////////////////////////////////
// CDiveSet

class CDiveSet : public CObject
{
private:
	CDiveSet( );
public:
	CDiveSet( CDiveDoc* pDoc );
	DECLARE_SERIAL( CDiveSet )
	~CDiveSet();
	
protected:
	CObArray	m_data;
	int			m_nCurIndex;
	CDiveDoc*	m_pDoc;

public:
	// File version
	BYTE	m_fileVersion;
	CTime	m_totalABT; 	// Total actual bottom time from all dives
	
public:
	CDiveData*	GetCurRecord() const;
	CDiveData*	GetRecord( int nIndex ) const;
	void		SetCurRecord( CDiveData* pData );
	void		Add( CDiveData* pData );
	void		Delete();
	void		FirstRecord();
	void		LastRecord();
	void		PrevRecord();
	void		NextRecord();
	int			GetCurIndex() const;
	int			GetNoOfRecs() const;
	void		RemoveAll();
	void		DateChange( CTime prevDate = NULL );
	void		RecalcDiveInfo();
	void		ChangeDiveNos( int nStartIndex );

public:
// Overridables
	virtual void Serialize(CArchive& ar);   // overridden for i/o
};

