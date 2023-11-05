// divedoc.cpp : implementation of the CDiveDoc class

#include "stdafx.h"
#include "divelog.h"
#include "form.h"
#include "tables.h"
#include "location.h"
#include "divedata.h"

#include "divedoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc

IMPLEMENT_DYNCREATE(CDiveDoc, CDocument)

BEGIN_MESSAGE_MAP(CDiveDoc, CDocument)
	//{{AFX_MSG_MAP(CDiveDoc)
	ON_COMMAND(IDM_LOCATIONS, OnLocations)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc construction/destruction

CDiveDoc::CDiveDoc()
{
	m_pForm = new CForm();
	m_pDiveSet = new CDiveSet( this );
	m_pTable1 = new CTable1();
	m_pTable2 = new CTable2();
	m_pTable3 = new CTable3();
}

CDiveDoc::~CDiveDoc()
{
	delete m_pForm;
	delete m_pDiveSet;
	delete m_pTable1;
	delete m_pTable2;
	delete m_pTable3;
}

BOOL CDiveDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

BOOL CDiveDoc::OnOpenDocument( const char* pszPathName )
{
	if( CDocument::OnOpenDocument( pszPathName ) )
	{
		UpdateAllViews( NULL );
		return TRUE;
	}
	return FALSE;
}

void CDiveDoc::DeleteContents()
{
	if( !m_pForm->IsFormLoaded() )
	{
		// programme just started
		if( !m_pForm->LoadForm( "FORMDATA.LSV" ) )		return;
		
		if( !m_pTable1->LoadTable() || !m_pTable2->LoadTable()
											|| !m_pTable3->LoadTable() )
		{
			AfxMessageBox( "Problem with a table data file!" );
			return;
		}
		ReadLocations();
	}
	
	m_pDiveSet->RemoveAll();
	CDiveData* pDiveData = new CDiveData();
	m_pDiveSet->Add( pDiveData );
    m_pDiveSet->m_totalABT = CTime( 1970, 1, 1, 0, 0, 0 );
}


void CDiveDoc::DrawForm( CDC* pDC ) const
{
	m_pForm->DrawForm( pDC );
}

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc serialization

void CDiveDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (BYTE)0x44;	ar << (BYTE)0x56;	ar << (BYTE)0x4C;	// DVL ident
		ar << (BYTE)m_pDiveSet->m_fileVersion;
	}
	else
	{
		BYTE ident1, ident2, ident3;
		ar >> ident1;	ar >> ident2;	ar >> ident3;
		ar >> (BYTE)m_pDiveSet->m_fileVersion;
		if( ident1 != 0x44 || ident2 != 0x56 || ident3 != 0x4C )
		{
			AfxMessageBox( "Not a dive data file!" );
			return;
		}
		if( m_pDiveSet->m_fileVersion != 0x01 )
		{
			AfxMessageBox( "File version not supported!" );
			return;
		}
	}
	m_pDiveSet->Serialize( ar );
}

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc diagnostics

#ifdef _DEBUG
void CDiveDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDiveDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiveDoc commands

void CDiveDoc::OnLocations()
{
	CLocationDlg dlg;
	
	if( dlg.DoModal()==IDOK )
		ReadLocations();
}

void CDiveDoc::ReadLocations()
{
 	// Read in the locations
 	m_locations.RemoveAll();
	int nEntries = AfxGetApp()->GetProfileInt( "Location", "Entries", -1 );
	for( int loop = 1; loop<=nEntries; loop++ )
	{
		char buf[20];
		wsprintf( buf, "String%d", loop );
		m_locations.Add( AfxGetApp()->GetProfileString( "Location", buf ) );
	}
}


