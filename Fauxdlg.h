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

#ifndef _FAUXDLG_
#define _FAUXDLG_ 

#define OEMRESOURCE		// <----- must be defined before windows.h is #included

#include "FauxCmb.h"
                                                   
class CFauxDlg : public CFauxCmb
{
// Construction
public:
	
// Attributes
public:

private:

// Operations
public:
	static void 		RegisterControl ();

// Implementation
public:

private:

	// Generated message map functions
protected:
	virtual void 		PostNcDestroy ();

	//{{AFX_MSG(CFauxDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

