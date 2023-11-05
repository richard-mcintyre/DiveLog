// defset.h : header file
//

// Dive type
#define	DEF_FRESH		0x0001L
#define DEF_SALT		0x0002L
#define DEF_SHORE		0x0004L
#define DEF_BOAT		0x0008L
#define DEF_WAVES		0x0010L
#define DEF_CURRENT		0x0020L
#define DEF_SURF		0x0040L
#define DEF_SURGE		0x0080L

// Exposure Protection
#define DEF_DRYSUIT		0x0100L
#define DEF_WETSUIT 	0x0200L
#define DEF_SDRYSUIT	0x0400L
#define DEF_USUIT		0x0800L
#define DEF_GLOVES		0x1000L
#define DEF_MITTENS		0x2000L
#define DEF_HOOD		0x4000L
#define DEF_SOCKS		0x8000L

class CDefDive;

/////////////////////////////////////////////////////////////////////////////
// CDefaultDlg dialog

class CDefaultDlg : public CDialog
{
// Construction
public:
	CDefaultDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDefaultDlg)
	enum { IDD = IDD_DEFAULTS };
	CComboBox	m_ctlLocation;
	BOOL	m_bBoat;
	BOOL	m_bCurrent;
	BOOL	m_bDrySuit;
	BOOL	m_bFresh;
	BOOL	m_bGloves;
	BOOL	m_bHood;
	BOOL	m_bMittens;
	BOOL	m_bSalt;
	BOOL	m_bSDrySuit;
	BOOL	m_bShore;
	BOOL	m_bSocks;
	BOOL	m_bSurf;
	BOOL	m_bSurge;
	BOOL	m_bUSuit;
	BOOL	m_bWaves;
	BOOL	m_bWetSuit;
	int		m_nWeightMea;
	BYTE	m_nWeight;
	BOOL	m_bNoDefaults;
	//}}AFX_DATA

public:
	CObArray	m_defDives;
	CDefDive*	m_pCur;

private:
	void	UpdateDia( BOOL bInit );
	void	EnaDisWin( );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDefaultDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDefaultDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLocationList();
	virtual void OnOK();
	afx_msg void OnNodefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CDefDive : public CObject
{
	DECLARE_DYNCREATE( CDefDive )
public:
	CDefDive( );

private:
	CString	m_location;
	WORD	m_check;	// Dive type check boxes (LOBYTE)
						// Exposure protection check boxes (HIBYTE)
	WORD	m_mea;		// depth, weight, tank pressures measurment

public:
	void	SetCBState( WORD wVal )			{	m_check |= wVal;			}
	void	ClearCBState( WORD wVal )		{	m_check &= ~wVal;			}
	BOOL	GetCBState( WORD wVal ) const	{	return (m_check & wVal)!=0 ? TRUE : FALSE;	}
	BYTE	GetWeight( );
	CString	GetLocation( ) const			{	return m_location;			}
	void	SetWeight( BYTE nVal );
	void	SetLocation( CString str )		{	m_location = str;			}	
	WORD	GetCheck( ) const				{	return m_check;				}
	void	SetCheck( WORD wVal )			{	m_check = wVal;				}
	WORD	GetMea( ) const					{	return m_mea;				}
	void	SetMea( WORD wVal )				{	m_mea = wVal;				}
	BOOL	IsDiveEmpty() const;
	void	SetWeightMea( BOOL bKgs )		{	if(bKgs) m_mea |= 0x01L; else m_mea &= ~0x01L;	}
	BOOL	IsWeightKgs( )					{	return (m_mea & 0x01L)!=0 ? TRUE : FALSE;		}
	void	SetDefaults( BOOL bDef )		{	if(bDef) m_mea |= 0x02L; else m_mea &= ~0x02L;	}
	BOOL	IsNoDefaults( )					{	return (m_mea & 0x02L)!=0 ? TRUE : FALSE;	}

	virtual void Serialize( CArchive& ar );
};



	
