// defset.cpp : implementation file
//

#include "stdafx.h"
#include "divelog.h"
#include "defset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDefaultDlg dialog


CDefaultDlg::CDefaultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDefaultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDefaultDlg)
	m_bBoat = FALSE;
	m_bCurrent = FALSE;
	m_bDrySuit = FALSE;
	m_bFresh = FALSE;
	m_bGloves = FALSE;
	m_bHood = FALSE;
	m_bMittens = FALSE;
	m_bSalt = FALSE;
	m_bSDrySuit = FALSE;
	m_bShore = FALSE;
	m_bSocks = FALSE;
	m_bSurf = FALSE;
	m_bSurge = FALSE;
	m_bUSuit = FALSE;
	m_bWaves = FALSE;
	m_bWetSuit = FALSE;
	m_nWeightMea = -1;
	m_nWeight = 0;
	m_bNoDefaults = FALSE;
	//}}AFX_DATA_INIT
	m_pCur = NULL;
}


void CDefaultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDefaultDlg)
	DDX_Control(pDX, IDC_LOCATION_LIST, m_ctlLocation);
	DDX_Check(pDX, IDC_CHECK_BOAT, m_bBoat);
	DDX_Check(pDX, IDC_CHECK_CURRENT, m_bCurrent);
	DDX_Check(pDX, IDC_CHECK_DRYSUIT, m_bDrySuit);
	DDX_Check(pDX, IDC_CHECK_FRESH, m_bFresh);
	DDX_Check(pDX, IDC_CHECK_GLOVES, m_bGloves);
	DDX_Check(pDX, IDC_CHECK_HOOD, m_bHood);
	DDX_Check(pDX, IDC_CHECK_MITTENS, m_bMittens);
	DDX_Check(pDX, IDC_CHECK_SALT, m_bSalt);
	DDX_Check(pDX, IDC_CHECK_SEMI_DRYSUIT, m_bSDrySuit);
	DDX_Check(pDX, IDC_CHECK_SHORE, m_bShore);
	DDX_Check(pDX, IDC_CHECK_SOCKS, m_bSocks);
	DDX_Check(pDX, IDC_CHECK_SURF, m_bSurf);
	DDX_Check(pDX, IDC_CHECK_SURGE, m_bSurge);
	DDX_Check(pDX, IDC_CHECK_UNDERSUIT, m_bUSuit);
	DDX_Check(pDX, IDC_CHECK_WAVES, m_bWaves);
	DDX_Check(pDX, IDC_CHECK_WETSUIT, m_bWetSuit);
	DDX_Radio(pDX, IDC_WEIGHT_LBS, m_nWeightMea);
	DDX_Text(pDX, IDC_EDIT_WEIGHT, m_nWeight);
	DDX_Check(pDX, IDC_NODEFAULT, m_bNoDefaults);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDefaultDlg, CDialog)
	//{{AFX_MSG_MAP(CDefaultDlg)
	ON_CBN_SELCHANGE(IDC_LOCATION_LIST, OnSelchangeLocationList)
	ON_BN_CLICKED(IDC_NODEFAULT, OnNodefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDefaultDlg message handlers

BOOL CDefaultDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
			
	for( int loop=0; loop<=m_defDives.GetUpperBound(); loop++ )
		m_ctlLocation.AddString( ((CDefDive*)m_defDives.GetAt( loop ))->GetLocation() );

	CString str;
	m_ctlLocation.GetLBText( 0, str );
	for( int i=0; i <=m_defDives.GetUpperBound(); i++ )
	{
		CDefDive* pDefDive = (CDefDive*)m_defDives.GetAt( i );
		if( pDefDive->GetLocation() == str )
		{
			m_pCur = pDefDive;
			break;
		}
	}

	if( m_pCur==NULL )
		m_pCur = (CDefDive*)m_defDives.GetAt( 0 );
	UpdateDia( TRUE );

	m_ctlLocation.SetCurSel( m_ctlLocation.FindStringExact( 0, m_pCur->GetLocation() ) );
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDefaultDlg::UpdateDia( BOOL bInit )
{
	if( bInit )
	{
	
		m_bBoat = m_pCur->GetCBState( DEF_BOAT );
		m_bCurrent = m_pCur->GetCBState( DEF_CURRENT );	 
		m_bDrySuit = m_pCur->GetCBState( DEF_DRYSUIT );
		m_bFresh = m_pCur->GetCBState( DEF_FRESH );
		m_bGloves = m_pCur->GetCBState( DEF_GLOVES );
		m_bHood = m_pCur->GetCBState( DEF_HOOD );
		m_bMittens = m_pCur->GetCBState( DEF_MITTENS );
		m_bSalt = m_pCur->GetCBState( DEF_SALT );
		m_bSDrySuit = m_pCur->GetCBState( DEF_SDRYSUIT );
		m_bShore = m_pCur->GetCBState( DEF_SHORE );
		m_bSocks = m_pCur->GetCBState( DEF_SOCKS );
		m_bSurf = m_pCur->GetCBState( DEF_SURF );
		m_bSurge = m_pCur->GetCBState( DEF_SURGE );
		m_bUSuit = m_pCur->GetCBState( DEF_USUIT );
		m_bWaves = m_pCur->GetCBState( DEF_WAVES );
		m_bWetSuit = m_pCur->GetCBState( DEF_WETSUIT );

		m_nWeight = m_pCur->GetWeight();
		BOOL bTmp = m_pCur->IsWeightKgs();
		if( bTmp )	m_nWeightMea = 1;	else	m_nWeightMea = 0;
		m_bNoDefaults = m_pCur->IsNoDefaults();

		UpdateData( FALSE );
		EnaDisWin( );
	}
	else
	{
		UpdateData( TRUE );
		
		m_bBoat ? m_pCur->SetCBState( DEF_BOAT ) : m_pCur->ClearCBState( DEF_BOAT );
		m_bCurrent ? m_pCur->SetCBState( DEF_CURRENT ) : m_pCur->ClearCBState( DEF_CURRENT );
		m_bDrySuit ? m_pCur->SetCBState( DEF_DRYSUIT ) : m_pCur->ClearCBState( DEF_DRYSUIT );
		m_bFresh ? m_pCur->SetCBState( DEF_FRESH ) : m_pCur->ClearCBState( DEF_FRESH );
		m_bGloves ? m_pCur->SetCBState( DEF_GLOVES ) : m_pCur->ClearCBState( DEF_GLOVES );
		m_bHood ? m_pCur->SetCBState( DEF_HOOD ) : m_pCur->ClearCBState( DEF_HOOD );
		m_bMittens ? m_pCur->SetCBState( DEF_MITTENS ) : m_pCur->ClearCBState( DEF_MITTENS );
		m_bSalt ? m_pCur->SetCBState( DEF_SALT ) : m_pCur->ClearCBState( DEF_SALT );
		m_bSDrySuit ? m_pCur->SetCBState( DEF_SDRYSUIT ) : m_pCur->ClearCBState( DEF_SDRYSUIT );
		m_bShore ? m_pCur->SetCBState( DEF_SHORE ) : m_pCur->ClearCBState( DEF_SHORE );
		m_bSocks ? m_pCur->SetCBState( DEF_SOCKS ) : m_pCur->ClearCBState( DEF_SOCKS );
		m_bSurf ? m_pCur->SetCBState( DEF_SURF ) : m_pCur->ClearCBState( DEF_SURF );
		m_bSurge ? m_pCur->SetCBState( DEF_SURGE ) : m_pCur->ClearCBState( DEF_SURGE );
		m_bUSuit ? m_pCur->SetCBState( DEF_USUIT ) : m_pCur->ClearCBState( DEF_USUIT );
		m_bWaves ? m_pCur->SetCBState( DEF_WAVES ) : m_pCur->ClearCBState( DEF_WAVES );
		m_bWetSuit ? m_pCur->SetCBState( DEF_WETSUIT ) : m_pCur->ClearCBState( DEF_WETSUIT );
						
		m_pCur->SetWeight( m_nWeight );
		m_nWeightMea == 0 ? m_pCur->SetWeightMea( FALSE )	: m_pCur->SetWeightMea( TRUE );
		m_pCur->SetDefaults( m_bNoDefaults );

	 	// now switch to a new record
		CString newLoc;
		m_ctlLocation.GetLBText( m_ctlLocation.GetCurSel(), newLoc );
		for( int i=0; i <=m_defDives.GetUpperBound(); i++ )
		{
			CDefDive* pDive = (CDefDive*)m_defDives.GetAt( i );
			if( pDive->GetLocation() == newLoc )
			{
				m_pCur = pDive;
				UpdateDia( TRUE );
				break;
			}
		}
	}
}

void CDefaultDlg::OnSelchangeLocationList() 
{
	UpdateDia( FALSE );	
}

void CDefaultDlg::OnOK() 
{
	UpdateDia( FALSE );
	CDialog::OnOK();
}

void CDefaultDlg::OnNodefault() 
{
	UpdateData( TRUE );
	EnaDisWin( );
}

void CDefaultDlg::EnaDisWin( )
{
	if( m_bNoDefaults )
	{
		(GetDlgItem( IDC_GRP_WEIGHT ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_EDIT_WEIGHT ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_WEIGHT_LBS ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_WEIGHT_KGS ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_GRP_DIVE ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_FRESH ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_WAVES ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_SALT ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_CURRENT ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_SHORE ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_SURF ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_BOAT ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_SURGE ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_GRP_EXP ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_DRYSUIT ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_GLOVES ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_WETSUIT ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_MITTENS ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_SEMI_DRYSUIT ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_HOOD ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_UNDERSUIT ))->EnableWindow( FALSE );
		(GetDlgItem( IDC_CHECK_SOCKS ))->EnableWindow( FALSE );
	}
	else
	{
		(GetDlgItem( IDC_GRP_WEIGHT ))->EnableWindow( );
		(GetDlgItem( IDC_EDIT_WEIGHT ))->EnableWindow( );
		(GetDlgItem( IDC_WEIGHT_LBS ))->EnableWindow( );
		(GetDlgItem( IDC_WEIGHT_KGS ))->EnableWindow( );
		(GetDlgItem( IDC_GRP_DIVE ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_FRESH ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_WAVES ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_SALT ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_CURRENT ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_SHORE ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_SURF ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_BOAT ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_SURGE ))->EnableWindow( );
		(GetDlgItem( IDC_GRP_EXP ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_DRYSUIT ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_GLOVES ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_WETSUIT ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_MITTENS ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_SEMI_DRYSUIT ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_HOOD ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_UNDERSUIT ))->EnableWindow( );
		(GetDlgItem( IDC_CHECK_SOCKS ))->EnableWindow( );
	}
}

/////////////////////////////////////////////////////////////////////
// CDefDive - default setting for a dive

IMPLEMENT_DYNCREATE( CDefDive, CObject )

CDefDive::CDefDive(  )
{                                 
	m_location = "";
	m_check = 0;
	m_mea = 2;
}

BOOL CDefDive::IsDiveEmpty() const
{
	if( m_check == 0 && m_mea == 2 )
		return TRUE;
	return FALSE;
}

void CDefDive::SetWeight( BYTE nVal )
{
	BYTE loByte = LOBYTE( m_mea );
	m_mea = (WORD)((UINT)((BYTE)loByte|((WORD)nVal<<8)));
}

BYTE CDefDive::GetWeight( )
{
	return HIBYTE( m_mea );
}

void CDefDive::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
		ar << m_location;
		ar << m_check;
		ar << m_mea;
	}
	else
	{
		ar >> m_location;
		ar >> m_check;
		ar >> m_mea;
	}
}
