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

#ifndef _EDITDATE_
#define _EDITDATE_

#include "Calendar.h"
#include "FauxCmb.h"
#include "DiagScrl.h"

enum DateFormat { YYMMDD, DDMMYY, MMDDYY, DDMMM, DDMMMYY, MMMDDYY, DEFAULT };

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class CEditDate : public CEdit
{
public:
				CEditDate();

	void		InitDate	(CString& 	StrDate, 
							 BOOL 		InitIfBlank = TRUE);

	void		InitFormat  (BOOL DayZero, 
							 BOOL MonthZero, 
							 BOOL YearCentury, 
							 DateFormat Format = DEFAULT,
							 char Seperator = (char) 0);

	void		GetDateStr	(CString& StrDate);
	CTime		GetDate		();

	void 		AttachCombo  ();
	void		AttachScroll ();

	void 		DetachCombo  ();
	void		DetachScroll ();

	void		ShowCalendar ();
		
protected:
	CTime		m_Date;

	DateFormat	m_Format;
	BOOL		m_DayZero;						// TRUE to display day with a leading zero
	BOOL		m_MonthZero;
	BOOL		m_YearCentury;

	char		m_Seperator;

	BOOL		m_Modified;

	CCalendar* 		m_pCalendar;
	CFauxCmb*		m_pCombo;
	CDiagScroll*	m_pScroll;

	static char	 szScratch [10];
	static char* szMonths  [13];
	static int   nMonthMax [13];

protected:			
	void		DecrementDate ();
	void		IncrementDate ();
	
	int 		GetEndMonth (int Month, int Year);
	BOOL		IsLeapYear	(int Year)
					{ return (((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0)); };
				
	void		SetDateStr	(CString& StrDate);

	void		DisplayDate (BOOL WantFocus = TRUE);

	const char* StrDD (int Year);
	const char* StrMM (int Year);
	const char* StrYY (int Year);

	void		MoveSeperatorHighlight();	

public:
	BOOL		ParseDate (CString StrDate, int& Month, int& Day, int& Year);	

protected:
	int			AdjustYear (int OldYear);

	void 		StripLeadingSpaces (CString& Str, BOOL StripSeperator = FALSE);

	int 		GetDD  (CString& Str, BOOL StripSeperator = FALSE);
	int 		GetMM  (CString& Str, BOOL StripSeperator = FALSE);
	int 		GetMMM (CString& Str);
	int 		GetYY  (CString& Str, BOOL StripSeperator = FALSE);


protected:
	//{{AFX_MSG(CEditDate)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus (CWnd* pOldWnd);
	afx_msg void OnShowWindow (BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnCalendarDateChanged (WPARAM WParam, LPARAM LParam);
	afx_msg LRESULT OnCalendarDateFinished (WPARAM WParam, LPARAM LParam);
	afx_msg LRESULT OnComboClicked (WPARAM WParam, LPARAM LParam);
	//}}AFX_MSG
	afx_msg void OnTestFunc();
	DECLARE_MESSAGE_MAP()
};

#endif

