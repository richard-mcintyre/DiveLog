//---------------------------------------------------------------------------
// Plumber Custom Control Pack 1                                     05/08/94
//
//	You may use the source code contained in this control pack freely in your
//	applications.  You may not give/share/sell the source code in any way,
//	modified or unmodified.  By using the source code, you agree that there
//	are no warranties, either expressed or implied associated with it 
//	(including, but not limited to warranties of merchantability and 
//	fitness for a particular purpose).					-- rpg     71101,1063
//---------------------------------------------------------------------------

#include "StdAfx.h"

#include "CalenDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

LRESULT CALLBACK AFX_EXPORT BootCalenDlg (HWND hWnd, UINT Message, WPARAM w, LPARAM l)
{
	if (Message == WM_NCCREATE)
	{
		CCalenDlg* pCalenDlg = new CCalenDlg ();
		
		::SetWindowLong (hWnd, GWL_WNDPROC, (LONG) DefWindowProc);
		
		pCalenDlg->SubclassWindow (hWnd);
		
		return AfxWndProc (hWnd, Message, w, l);
	}                                           
	
	TRACE ("BootCalenDlg: We should never get to this point!");
	ASSERT (FALSE);
	
	return 0;
}

BEGIN_MESSAGE_MAP(CCalenDlg, CCalendar)
	//{{AFX_MSG_MAP(CCalenDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCalenDlg::PostNcDestroy ()
{
	delete this;
}

void CCalenDlg::RegisterControl ()
{
	WNDCLASS        wc;

	//----- Check to see if the class has been registered
	if (::GetClassInfo (AfxGetInstanceHandle(), "PPCalendar", &wc))
		return;
		
	wc.style		 = CS_BYTEALIGNWINDOW | CS_PARENTDC | CS_SAVEBITS;
	wc.lpfnWndProc   = BootCalenDlg;
	wc.cbClsExtra    = NULL;
	wc.cbWndExtra    = NULL;
	wc.hInstance     = AfxGetInstanceHandle ();
	wc.hCursor       = ::LoadCursor (NULL, IDC_ARROW);
	wc.hIcon         = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = "PPCalendar";

	if (!::RegisterClass (&wc))
		AfxThrowResourceException ();		
}

