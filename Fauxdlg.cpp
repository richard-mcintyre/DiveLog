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

#define OEMRESOURCE		// <----- must be defined before windows.h is #included

#include "StdAfx.h"

#include "FauxDlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


LRESULT CALLBACK AFX_EXPORT BootFauxDlg (HWND hWnd, UINT Message, WPARAM w, LPARAM l)
{
	if (Message == WM_NCCREATE)
	{
		CFauxDlg* pFC = new CFauxDlg ();
		
		::SetWindowLong (hWnd, GWL_WNDPROC, (LONG) DefWindowProc);
		//----- switch WndProc's
		
		pFC->SubclassWindow (hWnd);
		
		return AfxWndProc (hWnd, Message, w, l);
	}                                           
	
	TRACE ("BootFauxDlg: We should never get to this point!");
	ASSERT (FALSE);
	
	return 0;
}

BEGIN_MESSAGE_MAP(CFauxDlg, CFauxCmb)
	//{{AFX_MSG_MAP(CFauxDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CFauxDlg::PostNcDestroy ()
{
	delete this;                                                
}

void CFauxDlg::RegisterControl ()
{
	WNDCLASS        wc;

	//----- Check to see if the class has been registered
	if (::GetClassInfo (AfxGetInstanceHandle(), "PPFauxCombo", &wc))
		return;
		
	wc.style		 = CS_BYTEALIGNWINDOW | CS_HREDRAW | CS_PARENTDC | CS_SAVEBITS | 
					   CS_DBLCLKS | CS_VREDRAW;
	wc.lpfnWndProc   = BootFauxDlg;
	wc.cbClsExtra    = NULL;
	wc.cbWndExtra    = NULL;
	wc.hInstance     = AfxGetInstanceHandle ();
	wc.hCursor       = ::LoadCursor (NULL, IDC_ARROW);
	wc.hIcon         = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = "PPFauxCombo";

	if (!::RegisterClass (&wc))
		AfxThrowResourceException ();		
}

