// divelog.cpp : Defines the class behaviors for the application.
//
 
#include "stdafx.h"
#include "divelog.h"
#include <ctl3d.h>
#include <dos.h>
#include <direct.h>

#include "mainfrm.h"
#include "divedoc.h"
#include "divevw.h"
#include "thghtdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CDiveApp

BEGIN_MESSAGE_MAP(CDiveApp, CWinApp)
	//{{AFX_MSG_MAP(CDiveApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiveApp construction

CDiveApp::CDiveApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CDiveApp::~CDiveApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDiveApp object

CDiveApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CDiveApp initialization

BOOL CDiveApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Ctl3dRegister( AfxGetInstanceHandle() );
	Ctl3dAutoSubclass( AfxGetInstanceHandle() );
	
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplate = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDiveDoc),
		RUNTIME_CLASS(CMDIChildWnd),        // standard MDI child frame
		RUNTIME_CLASS(CDiveView));
	AddDocTemplate(m_pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// enable file manager drag/drop and DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes();

	// simple command line parsing
	if (m_lpCmdLine[0] == '\0')
	{
		// create a new (empty) document
		OnFileNew();
	}
	else
	{
		CString cmdLine = m_lpCmdLine;
		if( cmdLine == "/REG" )
		{
			CRegDlg dlg;
			dlg.DoModal();
			
			OnFileNew();
		}
		else
		{
			// open an existing document
			if( OpenDocumentFile(m_lpCmdLine)==NULL )
				OnFileNew();
		}
	}

	m_splash.Create( m_pMainWnd );
	m_dwSplashTime = :: GetCurrentTime();

	m_pMainWnd->DragAcceptFiles();
	
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

 	return TRUE;
}

int CDiveApp::ExitInstance()
{
	Ctl3dUnregister( AfxGetInstanceHandle() );
	return CWinApp::ExitInstance();
}

BOOL CDiveApp::OnIdle( LONG lCount )
{
	// Call base class idle first
	BOOL bResult = CWinApp::OnIdle( lCount );

	// Now do our stuff
	if( m_splash.m_hWnd != NULL )
	{
		if( ::GetCurrentTime() - m_dwSplashTime > 3000 )
		{
			// timeout expired,  destroy the splash window
			m_splash.DestroyWindow();
			m_pMainWnd->UpdateWindow();
			BOOL bShow = AfxGetApp()->GetProfileInt( "Thoughts", "Show", TRUE );
			if( bShow )
			{
				CThoughtDlg dlg;
				dlg.DoModal();
			}
		}
		else
		{
			// Check again later
			bResult = TRUE;
		}
	}
	return bResult;
}                             
    
BOOL CDiveApp::PreTranslateMessage(MSG* pMsg)
{
	BOOL bResult = CWinApp::PreTranslateMessage( pMsg );

	if (m_splash.m_hWnd != NULL &&
		(pMsg->message == WM_KEYDOWN ||
		 pMsg->message == WM_SYSKEYDOWN ||
		 pMsg->message == WM_LBUTTONDOWN ||
		 pMsg->message == WM_RBUTTONDOWN ||
		 pMsg->message == WM_MBUTTONDOWN ||
		 pMsg->message == WM_NCLBUTTONDOWN ||
		 pMsg->message == WM_NCRBUTTONDOWN ||
		 pMsg->message == WM_NCMBUTTONDOWN))
	{
		m_splash.DestroyWindow();
		m_pMainWnd->UpdateWindow();
		BOOL bShow = AfxGetApp()->GetProfileInt( "Thoughts", "Show", TRUE );
		if( bShow )
		{
			CThoughtDlg dlg;
			dlg.DoModal();
		}
	}
                 
	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDiveApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDiveApp commands

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// fill available memory infomation
	CString str, strFmt;
	strFmt.LoadString(IDS_AVAIL_MEM);
	wsprintf(str.GetBuffer(80), strFmt, GetFreeSpace(0) / 1024L);
	str.ReleaseBuffer();
	SetDlgItemText(IDC_AVAIL_MEM, str);

	// fill math coprocessor information
	if (GetWinFlags() & WF_80x87)
		str.LoadString(IDS_MATH_COPR_PRESENT);
	else
		str.LoadString(IDS_MATH_COPR_NOTPRESENT);
	SetDlgItemText(IDC_MATH_COPR, str);

	// fill disk free information
	struct _diskfree_t diskfree;
	if (_dos_getdiskfree(_getdrive(), &diskfree) == 0)
	{
		strFmt.LoadString(IDS_DISK_SPACE);
		wsprintf(str.GetBuffer(80), strFmt,
			(DWORD)diskfree.avail_clusters *
			(DWORD)diskfree.sectors_per_cluster *
			(DWORD)diskfree.bytes_per_sector / (DWORD)1024L);
		str.ReleaseBuffer();
	}
	else
		str.LoadString(IDS_DISK_SPACE_UNAVAIL);
	SetDlgItemText(IDC_DISK_SPACE, str);
	
	SetDlgItemText( IDC_RELEASED, __DATE__ /*" - " __TIME__*/ );
	            
#ifdef _DEBUG
	SetDlgItemText( IDC_DEBUG, " DEBUG " );
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}
/////////////////////////////////////////////////////////////////////////////
// CSplashDlg dialog


BOOL CSplashDlg::Create(CWnd* pParent)
{
	//{{AFX_DATA_INIT(CSplashWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    
    if (!CDialog::Create(CSplashDlg::IDD, pParent))
	{
		TRACE("Warning: creation of CSplashWnd dialog failed\n");
		return FALSE;
	}
	
	return TRUE;
}   

void CSplashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplashDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSplashDlg, CDialog)
	//{{AFX_MSG_MAP(CSplashDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplashDlg message handlers

BOOL CSplashDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetWindowPos( NULL, 0, 0, 522, 319, SWP_NOMOVE|SWP_NOZORDER );
	CenterWindow();
	
	CFile file;
	if( file.Open( "REGINFO.DAT", CFile::modeRead ) )
	{
		CArchive ar( &file, CArchive::load );
		
		ar >> m_name;
		ar >> m_company;
	
		ar.Close();
		file.Close();
	}
	else
	{
		CRegDlg dlg;
		dlg.DoModal();
		
		if( file.Open( "REGINFO.DAT", CFile::modeRead ) )
		{
			CArchive ar( &file, CArchive::load );
			
			ar >> m_name;
			ar >> m_company;
		
			ar.Close();
			file.Close();
		}
		else
		{
			m_name = "Unknown User";
			m_company = "Unknown Company";
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSplashDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CBitmap bitmap;
	bitmap.LoadBitmap( ID_SPLASH );
	
	CDC* pDisplayMemDC = new CDC;
	pDisplayMemDC->CreateCompatibleDC( &dc );
	
	CBitmap* pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject( &bitmap );
	dc.BitBlt( 0, 0, 520, 317, pDisplayMemDC, 0, 0, SRCCOPY );
    pDisplayMemDC->SelectObject( pOldBitmap );


	CFont font;
	font.CreateFont(	-10 * dc.GetDeviceCaps (LOGPIXELSY) / 72, 0, 0, 0, 600, 0, 0, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, /*"Arial" );*/"MS San Serf" );
	
	CFont* pOldFont = dc.SelectObject( &font );
	int nOldBkMode = dc.SetBkMode( TRANSPARENT );
	dc.TextOut( 255, 50, m_name );
	dc.TextOut( 255, 65, m_company );
	dc.SetBkMode( nOldBkMode );
	dc.SelectObject( pOldFont );
	
	delete pDisplayMemDC;
	
	// Do not call CDialog::OnPaint() for painting messages
}
/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog


CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDlg)
	m_company = "";
	m_name = "";
	//}}AFX_DATA_INIT
}

void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDlg)
	DDX_Text(pDX, IDC_COMPANY, m_company);
	DDX_Text(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegDlg, CDialog)
	//{{AFX_MSG_MAP(CRegDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers

void CRegDlg::OnOK()
{
	CFile file( "REGINFO.DAT", CFile::modeCreate|CFile::modeWrite );
	CArchive ar( &file, CArchive::store );
	
	UpdateData();
	ar << m_name;	ar << m_company;

	ar.Close();	file.Close();
	
	CDialog::OnOK();
}

BOOL CRegDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDiveApp::OnFileNew()
{
	CWinApp::OnFileNew();
    
    CMDIFrameWnd* pFrameWnd = (CMDIFrameWnd*)AfxGetMainWnd();
    CMDIChildWnd* pChildWnd = pFrameWnd->MDIGetActive();
    pChildWnd->MDIMaximize();
}

void CDiveApp::OnFileOpen()
{
	CWinApp::OnFileOpen();
    CMDIFrameWnd* pFrameWnd = (CMDIFrameWnd*)AfxGetMainWnd();
    CMDIChildWnd* pChildWnd = pFrameWnd->MDIGetActive();
    pChildWnd->MDIMaximize();
}

CDocument* CDiveApp::OpenDocumentFile( LPCSTR lpszFileName )
{
	CDocument* pDoc = CWinApp::OpenDocumentFile( lpszFileName );
    CMDIFrameWnd* pFrameWnd = (CMDIFrameWnd*)AfxGetMainWnd();
    CMDIChildWnd* pChildWnd = pFrameWnd->MDIGetActive();
    pChildWnd->MDIMaximize();
    // pDoc->UpdateAllViews( NULL );

    // Invalidate the fields to show the first record
   	POSITION pos = pDoc->GetFirstViewPosition();
	CDiveView* pView = (CDiveView*)pDoc->GetNextView(pos);
	ASSERT_VALID(pView);
	pView->InvalidateFlds( );

    return pDoc;
}