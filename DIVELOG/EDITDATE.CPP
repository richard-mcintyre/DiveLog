// EDITDATE.CPP - implementation of the CEditDate class

#include "stdafx.h"
#include "calender.h"
#include "fauxcmb.h"
#include "diagscrl.h"

#include "editdate.h"

#include <ctype.h>
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

char  CEditDate::szScratch [10];
char* CEditDate::szMonths  [13] = { "", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", 
	  	 			  		            "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };;
int   CEditDate::nMonthMax [13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

BEGIN_MESSAGE_MAP(CEditDate, CEdit)
	//{{AFX_MSG_MAP(CEditDate)
	ON_WM_CHAR()
	ON_WM_VSCROLL()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE (PPC_DATECHANGED, OnCalendarDateChanged)
	ON_MESSAGE (PPC_DATEFINISHED, OnCalendarDateFinished)
	ON_MESSAGE (PPFC_BTNCLICKED, OnComboClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// CEditDate

CEditDate::CEditDate()
{
	char Buffer [15];
	
 	m_pCalendar = NULL;	m_pCombo	= NULL;	m_pScroll	= NULL;
	m_DayZero     = FALSE;	m_MonthZero   = FALSE;	m_YearCentury = FALSE;
	
	m_Date = CTime::GetCurrentTime();

	if (::GetProfileString ("Intl", "sDate", "", Buffer, 2) == 1)
		m_Seperator = Buffer [0];
	else
		m_Seperator = '/';

	if (::GetProfileString ("Intl", "sShortDate", "", Buffer, 11))
	{
		//----- figure out which format to use
		switch (Buffer[0])
		{
			case 'd' :
			case 'D' : m_Format = DDMMYY; break;
			
			case 'Y' :
			case 'y' : m_Format = YYMMDD; break;

		 	case 'm' :
		 	case 'M' : 
		 	default  : m_Format = MMDDYY;
		}
                                              
		// now find the Zero and Century values
		CString Str = Buffer;                         
		CString Tmp;
		int Index;
		
		while (Str.GetLength())
		{
			if ((Index = Str.Find (m_Seperator)) != -1)       
			{
				Tmp = Str.Left (Index);
				Str = Str.Right (Str.GetLength() - Index - 1);
			}
			else
			{
			 	Tmp = Str;
			 	Str = "";
			}
			Tmp.MakeUpper();
			switch (Tmp[0])
			{
				case 'D' : m_DayZero     = (Tmp.GetLength() == 2); break;
				case 'M' : m_MonthZero   = (Tmp.GetLength() == 2); break;
				case 'Y' : m_YearCentury = (Tmp.GetLength() == 4); break;
			}
		}
	}
	else
		m_Format = MMDDYY;	
}

int CEditDate::AdjustYear (int Year)
{
	if (Year <= 37)
		return (Year + 2000);
	else if (Year >= 70)
		if (Year < 100)
			return (Year + 1900);
		else if ((Year >= 1970) && (Year <= 2037))
			return Year;
		else
			return 0;
	else
		return 0;
}

void CEditDate::AttachCombo ()
{
	if (m_pCombo == NULL)
	{
		CRect ClientRect;
		CRect ComboRect;
		                 
		// Figure out (in terms of its parent) where everything goes
		GetWindowRect (&ClientRect);
		GetParent()->ScreenToClient (&ClientRect);

		ComboRect = ClientRect;
			
		//- Resize edit control to account for combo box
		int   EditWidth = ClientRect.Width() - ::GetSystemMetrics (SM_CXVSCROLL) - 5;

		SetWindowPos (&wndTop, ClientRect.left, ClientRect.top, EditWidth, ClientRect.Height(), 
					  SWP_NOMOVE | SWP_NOZORDER);

		ComboRect.left  = ComboRect.right;		// autosize width
    
		// create the combo box
		m_pCombo = new CFauxCmb;

		m_pCombo->Create (WS_CHILD | WS_CLIPSIBLINGS,
						  ComboRect, 
						  GetParent(), 		// make a child of the edit control's parent
						  0);
		
		m_pCombo->GetClientRect (&ComboRect);
		m_pCombo->SetWindowPos (&wndTop, ClientRect.right - ComboRect.Width(),
								 ClientRect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_pCombo->ShowWindow (SW_SHOW);
		m_pCombo->SetAssociate (this);
	}
}

void CEditDate::AttachScroll ()
{
	if (m_pScroll == NULL)
	{
		CRect ClientRect;
		CRect ScrollRect;
		                 
		// Figure out (in terms of its parent) where everything goes
		GetWindowRect (&ClientRect);
		GetParent()->ScreenToClient (&ClientRect);
		ScrollRect = ClientRect;
			
		// create the combo box
		m_pScroll = new CDiagScroll;
		m_pScroll->Create (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | PPDS_DEFAULT,
						  ScrollRect, 
						  GetParent(), 		// make a child of the edit control's parent
						  0);
        
        m_pScroll->GetClientRect (&ScrollRect);
        
		// Resize edit control to account for scroll box
		int EditWidth = ClientRect.Width() - ScrollRect.Width() - 7;

		SetWindowPos (&wndTop, ClientRect.left, ClientRect.top, EditWidth, ClientRect.Height(), 
					  SWP_NOMOVE | SWP_NOZORDER);
		m_pScroll->SetWindowPos (&wndTop, 
								 ClientRect.right - ScrollRect.Width() - 2,
								 ClientRect.top,
								 0,
								 0,
								 SWP_NOSIZE | SWP_NOZORDER);
								
		m_pScroll->ShowWindow (SW_SHOW);
		m_pScroll->SetAssociate (this);
	}
}

void CEditDate::DecrementDate ()
{
	if (m_Modified)
	{
		CString StrDate;
		
		GetWindowText (StrDate);
		SetDateStr (StrDate);
		m_Modified = FALSE;
	}

	if ((m_Date.GetYear()   < 1970) || 
	   ((m_Date.GetYear()  == 1970) &&	
	    (m_Date.GetMonth() == 1)    &&
	    (m_Date.GetDay()   == 1)))
	    ;	// don't do anything
	else
	{
	 	CTimeSpan OneDay (1,0,0,0);
 	
 		m_Date -= OneDay;
	}
	DisplayDate ();
}

void CEditDate::DetachCombo ()
{
	if (m_pCombo != NULL)
	{             
		CRect ClientRect;
		CRect ComboRect;
			                 
		// Figure out (in terms of its parent) where everything goes
		GetWindowRect (&ClientRect);
		GetParent()->ScreenToClient (&ClientRect);
		m_pCombo->GetClientRect (&ComboRect);
	
		// Resize edit control to account for loss of combo box
		int   EditWidth = ClientRect.Width() + ComboRect.Width() + 5;
		SetWindowPos (&wndTop, ClientRect.left, ClientRect.top, EditWidth, 
					  	ClientRect.Height(), SWP_NOMOVE | SWP_NOZORDER);
	
		m_pCombo->DestroyWindow ();
		delete m_pCombo;
		m_pCombo = NULL;
	}
}

void CEditDate::DetachScroll ()
{
	if (m_pScroll != NULL)
	{
		CRect ClientRect;
		CRect ScrollRect;
		                 
		// Figure out (in terms of its parent) where everything goes
		GetWindowRect (&ClientRect);
		GetParent()->ScreenToClient (&ClientRect);
        m_pScroll->GetClientRect (&ScrollRect);
        
		// Resize edit control to account for loss of scroll box
		int EditWidth = ClientRect.Width() + ScrollRect.Width() + 7;
		SetWindowPos (&wndTop, ClientRect.left, ClientRect.top, EditWidth, ClientRect.Height(), 
					  SWP_NOMOVE | SWP_NOZORDER);
		
		m_pScroll->DestroyWindow();
		delete m_pScroll;
		m_pScroll = NULL;
	}	
	
}

void CEditDate::DisplayDate (BOOL WantFocus)
{
	CString Str;

	BOOL HighlightAll = TRUE;
			
	if (m_Format == MMDDYY)
	{
		Str  = StrMM (m_Date.GetMonth());	Str += m_Seperator;
		Str += StrDD (m_Date.GetDay());		Str += m_Seperator;
		Str += StrYY (m_Date.GetYear());
		HighlightAll = FALSE;
	}
	else
	if (m_Format == DDMMYY)
	{           
		Str  = StrDD (m_Date.GetDay());		Str += m_Seperator;
		Str += StrMM (m_Date.GetMonth());	Str += m_Seperator;
		Str += StrYY (m_Date.GetYear());		
		HighlightAll = FALSE;
	}
	else
	if (m_Format == YYMMDD)
	{
		Str  = StrYY (m_Date.GetYear());		Str += m_Seperator;
		Str += StrMM (m_Date.GetMonth());		Str += m_Seperator;
		Str += StrDD (m_Date.GetDay());		
		HighlightAll = FALSE;		
	}
	else
	if (m_Format == DDMMM)
	{   
		Str  = StrDD  (m_Date.GetDay());
		Str += szMonths [m_Date.GetMonth()];
	}
	else
	if (m_Format == MMMDDYY)
	{
		Str  = szMonths [m_Date.GetMonth()];
		Str += StrDD  (m_Date.GetDay());
		Str += StrYY  (m_Date.GetYear());
	}
	else
	if (m_Format == DDMMMYY)
	{
		Str  = StrDD  (m_Date.GetDay());
		Str += szMonths [m_Date.GetMonth()];
		Str += StrYY  (m_Date.GetYear());
	}

	SetWindowText (Str);

	if (HighlightAll)
		SetSel (0, -1);								// highlight entire selection
	else
		SetSel (0, Str.Find (m_Seperator));

	if ((GetFocus() != this) && WantFocus)
		SetFocus();
}

CTime CEditDate::GetDate ()
{
	CString tmpDate;
		
	GetWindowText (tmpDate);
	SetDateStr (tmpDate);							// validates what is in edit control
	DisplayDate ();

	return m_Date;
}

void CEditDate::GetDateStr (CString& StrDate)
{
	CString tmpDate;
		
	GetWindowText (tmpDate);
	SetDateStr (tmpDate);   					// validates what is in edit control
	DisplayDate ();

	GetWindowText (StrDate);
}

int CEditDate::GetDD (CString& Str, BOOL StripSeperator)
{
	// Get DD Day Value
	if (Str.GetLength())
	{                   
		StripLeadingSpaces (Str, StripSeperator);
		
		for (int x = 0; x < Str.GetLength() && isdigit(Str[x]); x++);
			
		if (x > 2)			// string is bad
			return -1;						
				
		int Day = ::atoi (Str);
		if (Day > 31)
			return -1;
	
		Str = Str.Right (Str.GetLength() - x);		// strip off the DD value
		return Day;
	}
	else
		return -1;
}

int CEditDate::GetEndMonth (int Month, int Year)
{
    int LastDay = nMonthMax [Month];
	
	if (Month == 2)			// check for leap year
		if (IsLeapYear (Year))
			LastDay++;
	
	return LastDay;
}

int CEditDate::GetMM (CString& Str, BOOL StripSeperator)
{
	// Get MM Value
	if (Str.GetLength())
	{                   
		StripLeadingSpaces (Str, StripSeperator);
		for (int x = 0; x < Str.GetLength() && isdigit(Str[x]); x++);
			
		if (x > 2)			// string is bad
			return -1;						

		int Month = ::atoi (Str);
		if ((Month == 0) || (Month > 12))
			return -1;
		
		Str = Str.Right (Str.GetLength() - x);		// strip off the YY value
		return Month;
	}
	else
		return -1;
}

int CEditDate::GetMMM (CString& Str)
{
	// Get MMM value
	if (Str.GetLength())
	{
		StripLeadingSpaces (Str);	
					
		CString Tmp = Str.Left (3);
		
		if (Tmp.GetLength() != 3)
			return -1;
			
		for (int x = 1; (x < 13) && (Tmp != szMonths[x]); x++) ;
		
		if (x == 13)						// couldn't find month;
			return -1;
										
		if (Tmp == szMonths[x])
		{
			Str = Str.Right (Str.GetLength() - 3);
			return x;
		}
		else
			return -1;	
	}
	else
		return -1;	
}

int CEditDate::GetYY (CString& Str, BOOL StripSeperator)
{
	// Get YY Value
	if (Str.GetLength())
	{                   
		StripLeadingSpaces (Str, StripSeperator);
		for (int x = 0; x < Str.GetLength() && isdigit(Str[x]); x++) ;
			
		int Year = AdjustYear(::atoi (Str));
		Str = Str.Right (Str.GetLength() - x);		// strip off the YY value
		return Year;
	}
	else
		return -1;
}

void CEditDate::IncrementDate ()
{
	if (m_Modified)
	{
		CString StrDate;
		
		GetWindowText (StrDate);
		SetDateStr (StrDate);
		m_Modified = FALSE;
	}
	
	if (m_Date < CTime (2037, 12, 31, 0, 0, 0))
	{
 		CTimeSpan OneDay (1,0,0,0);
 		m_Date += OneDay;
 	}	
	DisplayDate ();
}

void CEditDate::InitDate (CString& StrDate, BOOL InitIfBlank)
{
	m_Modified = FALSE;
	m_Date = CTime::GetCurrentTime();
	if (InitIfBlank)
	{
		SetDateStr (StrDate);
		DisplayDate ();
	}
	else
	if (StrDate.GetLength())
	{
		SetDateStr (StrDate);
		DisplayDate ();
	}	

	GetWindowText (StrDate);
}                                    
    
void CEditDate::InitFormat (BOOL DayZero, BOOL MonthZero, BOOL YearCentury, 
						    DateFormat Format, char Seperator)
{
	if (Format != DEFAULT)
		m_Format = Format;

	if (Seperator != (char) 0)
		m_Seperator = Seperator;
	
	m_DayZero     = DayZero;
	m_MonthZero   = MonthZero;
	m_YearCentury = YearCentury;
}

void CEditDate::MoveSeperatorHighlight ()
{
	int First;
	int Last;
	int Seperator;
		
	CString StrDate;

	GetWindowText (StrDate);

	GetSel (First, Last);
	
	if ((First == 0) && (Last == 0))
	{
		SetSel (0, StrDate.Find (m_Seperator));
		
		return;
    }

	CString Tmp = StrDate.Right (StrDate.GetLength() - Last);
	
	if (StrDate.GetLength())
	{
		Seperator = Tmp.Find (m_Seperator);
		
		if (Seperator != -1)
		{
			CString Tmp1 = Tmp.Right (Tmp.GetLength() - Seperator - 1);

			int NextSeperator = Tmp1.Find (m_Seperator);
			
			if (NextSeperator == -1)
				SetSel (Last + Seperator + 1, -1);	
			else
				SetSel (Last + Seperator + 1, Last + NextSeperator + 1);
		}
		else
			SetSel (0, StrDate.Find (m_Seperator));
	}
	else										// highlight the month
		SetSel (0, StrDate.Find (m_Seperator));
}
    
LRESULT CEditDate::OnCalendarDateChanged (WPARAM WParam, LPARAM LParam)
{
	if (WParam == (WPARAM) m_pCalendar->GetSafeHwnd())
	{
		m_Date = m_pCalendar->GetSelectedDate();
		DisplayDate (FALSE);
	}		

	return (LRESULT) 0;
}

LRESULT CEditDate::OnCalendarDateFinished (WPARAM WParam, LPARAM LParam)
{
	if (WParam == (WPARAM) m_pCalendar->GetSafeHwnd())
	{
		CString StrDate;
		m_pCalendar->ShowWindow (SW_HIDE);
		GetWindowText (StrDate);
		SetSel (0, StrDate.Find (m_Seperator));
		SetFocus();								// grab the focus back
    }
    
	SetSel (0, -1);
	return (LRESULT) 0;
}

//---------------------------------------------------------------------------

void CEditDate::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if ((nChar >= '0' && nChar <= '9') || 
		nChar == VK_BACK)
	{                       
		m_Modified = TRUE;
	
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	if (nChar == '-' || nChar == '_')
	{
		DecrementDate ();
	}
	else
	if (nChar == '+' || nChar == '=')
	{
	   IncrementDate ();
	}
	else
	if ((m_Format == MMDDYY) ||						// check for the other keys
	    (m_Format == DDMMYY) ||
	    (m_Format == YYMMDD))
		switch (nChar)
		{
		 	case 'T' :  // Today
		 	case 't' :	
		 		m_Date = CTime::GetCurrentTime();
		 		DisplayDate ();
		 		break;
		 		
		 	case 'W' :  // beginning of week
		 	case 'w' :          
		 		{
		 			int DOW = m_Date.GetDayOfWeek () - 1;		// zero based

				 	CTimeSpan OneDay (1,0,0,0);
 	        
 	        		for (int x = DOW; x > 0; x--)
			 			m_Date -= OneDay;
		 		}       
		 		DisplayDate ();
		 		break;
		 	
		 	case 'K' :  // end of week
		 	case 'k' :
		 		{
		 			int DOW = m_Date.GetDayOfWeek ();		// zero based

				 	CTimeSpan OneDay (1,0,0,0);
 	        
 	        		for (int x = DOW; x < 7; x++)
			 			m_Date += OneDay;
		 		}       
		 		DisplayDate ();
		 		break;
		 	
		 	case 'M' :  // beginning of month
		 	case 'm' :
		 	    m_Date = CTime (m_Date.GetYear(), m_Date.GetMonth(), 1, 0, 0, 0);
		 	    DisplayDate();
		 	    break;
		 	    
		 	case 'H' :  // end of month
		 	case 'h' : 
		 	    m_Date = CTime (m_Date.GetYear(), 
		 	    				m_Date.GetMonth(), 
		 	    				GetEndMonth (m_Date.GetMonth(), m_Date.GetYear()), 
		 	    				0, 0, 0);
		 	    DisplayDate();
		 	    break;
		 	
		 	case 'Y' :  // beginning of year
		 	case 'y' :
				m_Date = CTime (m_Date.GetYear(), 1, 1, 0, 0, 0);
				DisplayDate ();
		 		break;
		 	
		 	case 'R' :  // end of year
		 	case 'r' :
				m_Date = CTime (m_Date.GetYear(), 12, 31, 0, 0, 0);
				DisplayDate ();
		 		break;
		 	
		 	default  :
		 		if (nChar == (UINT) m_Seperator)
		 		{
		 			CString Str;
		 			
 					GetWindowText (Str);
					int Seperator = 0;
					
					// Count the /'s in the date string 					
 					for (int x = 0; x < Str.GetLength(); x++)
 						if (Str[x] == m_Seperator)
 							Seperator++;

					if (Seperator == 2)
						MoveSeperatorHighlight ();
					else
					{
						m_Modified = TRUE;
					
						CEdit::OnChar(nChar, nRepCnt, nFlags);
					}
				}
				else
					::MessageBeep (MB_ICONEXCLAMATION);
				break;
		}
	else										// allow this for other date formats
		if ((nChar >= 'a' && nChar <= 'z') || (nChar >= 'A' && nChar <= 'Z') || 
																		(nChar == ' '))
		{                       
			m_Modified = TRUE;
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
		else
			::MessageBeep (MB_ICONEXCLAMATION);
}

LRESULT CEditDate::OnComboClicked (WPARAM WParam, LPARAM LParam)
{
	if (WParam == (WPARAM) m_pCombo->GetSafeHwnd())
		ShowCalendar ();			
	return (LRESULT) 0;
}

void CEditDate::OnDestroy()
{
	if (m_pCalendar != NULL)
	{
		if (m_pCalendar->GetSafeHwnd())
			m_pCalendar->DestroyWindow ();
	 	delete m_pCalendar;
	}
	                          
	if (m_pCombo != NULL)
	{
		if (m_pCombo->GetSafeHwnd())
			m_pCombo->DestroyWindow ();
		delete m_pCombo;
	}

	if (m_pScroll != NULL)
	{
		if (m_pScroll->GetSafeHwnd())
			m_pScroll->DestroyWindow ();
		delete m_pScroll;
	}
	CEdit::OnDestroy();
}

void CEditDate::OnSetFocus (CWnd* pOldWnd)
{
	if ((m_Format == MMDDYY) || (m_Format == DDMMYY) ||	(m_Format == YYMMDD))
	{
		SetSel (0,0);
		MoveSeperatorHighlight ();
	}

	CEdit::OnSetFocus (pOldWnd);
}

void CEditDate::OnShowWindow (BOOL bShow, UINT nStatus)
{
 	CEdit::OnShowWindow (bShow, nStatus);
 	
 	if (m_pCombo != NULL)	m_pCombo->ShowWindow (bShow ? SW_SHOW : SW_HIDE);
 	if (m_pScroll != NULL)	m_pCombo->ShowWindow (bShow ? SW_SHOW : SW_HIDE);
}

void CEditDate::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	switch (nSBCode)
	{
		case SB_LINEUP   : IncrementDate (); break;
		case SB_LINEDOWN : DecrementDate (); break;
		default 		 : CEdit::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

BOOL CEditDate::ParseDate (CString StrDate, int& Month, int& Day, int& Year)
{
	Day 	= 0;
	Month 	= 0;
	Year 	= 0;
	
	StripLeadingSpaces (StrDate);
	
	if (StrDate.GetLength () == 0)
		return FALSE;
			
	if ((m_Format == DDMMM) || (m_Format == DDMMMYY))
	{
		if ((Day = GetDD (StrDate)) != -1)
			if ((Month = GetMMM (StrDate)) != -1)
				if (m_Format == DDMMM)
					// check if day is valid for the month
					return TRUE;				
				else 								// get year value
					if ((Year = GetYY (StrDate)) != -1)
						if (Day <= GetEndMonth (Month, Year))
							return TRUE;

		return FALSE;
	} else
	if (m_Format == MMMDDYY)
	{
		if ((Month = GetMMM (StrDate)) != -1)
			if ((Day = GetDD (StrDate)) != -1)
				if ((Year = GetYY (StrDate)) != -1)
					if (Day <= GetEndMonth (Month, Year))
						return TRUE;
		
		return FALSE;
	} else
	if (m_Format == MMDDYY)
	{
		if ((Month = GetMM (StrDate)) != -1)
			if ((Day = GetDD (StrDate, TRUE)) != -1)
				if ((Year = GetYY (StrDate, TRUE)) != -1)
					if (Day <= GetEndMonth (Month, Year))
						return TRUE;

		return FALSE;	
	} else
	if (m_Format == DDMMYY)
	{
		if ((Day = GetDD (StrDate)) != -1)
			if ((Month = GetMM (StrDate, TRUE)) != -1)
				if ((Year = GetYY (StrDate, TRUE)) != -1)
					if (Day <= GetEndMonth (Month, Year))
						return TRUE;

		return FALSE;	
	} else
	if (m_Format == YYMMDD)
	{
		if ((Year = GetYY (StrDate)) != -1)
			if ((Month = GetMM (StrDate, TRUE)) != -1)
				if ((Day = GetDD (StrDate, TRUE)) != -1)
					if (Day <= GetEndMonth (Month, Year))
						return TRUE;

		return FALSE;	
	}

	return FALSE;
}
                                    
void CEditDate::SetDateStr (CString& StrDate)
{
	m_Date = CTime::GetCurrentTime();

	if (StrDate.GetLength())					// parse string to get date	
	{    
		int Month;
		int Day;
		int Year;
		
		if (ParseDate (StrDate, Month, Day, Year))
		{                                       
			if ((Year == 0) || (Year < 1970) || (Year > 2037))
				Year = m_Date.GetYear ();
				
			if (Month == 0)
				Month = m_Date.GetMonth ();
				                         
			if (Day == 0)
				Day = m_Date.GetDay ();
				
			CTime tmpDate (Year, Month, Day, 0, 0, 0);
			
			m_Date = tmpDate;
		}
	}
}                                    

void CEditDate::ShowCalendar ()
{
	CRect ClientRect;
	
	GetClientRect (&ClientRect);
	ClientToScreen (&ClientRect);

	if (m_pCalendar == NULL)
	{
		m_pCalendar = new CCalendar;
		m_pCalendar->Create (WS_POPUP | WS_CLIPCHILDREN | PPC_DEFAULT | PPC_HIDELOSEFOCUS,
							 ClientRect, 
							 GetParent(), 		// make a child of the edit control's parent
							 0);    
		
		m_pCalendar->SetAssociate (this);
	}

	int MaxX = ::GetSystemMetrics (SM_CXSCREEN);		
	int MaxY = ::GetSystemMetrics (SM_CYSCREEN);

	int y = ClientRect.bottom - 1;
	int x = ClientRect.left;
	
	// move the calendar into the correct place
	int CalX = m_pCalendar->GetControlWidth();
	int CalY = m_pCalendar->GetControlHeight();
	
	if (x + CalX > MaxX)
		x = MaxX - CalX;
	else if (x < 0)
		x = 0;
		
	if (y + CalY > MaxY)
		y = ClientRect.top - CalY - 1;

	// set the date
	m_pCalendar->SelectDate (GetDate());
	// show the window
	m_pCalendar->SetWindowPos (NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);

	m_pCalendar->SetFocus();
}

void CEditDate::StripLeadingSpaces (CString& Str, BOOL StripSeperator)
{
	if ((Str[0] == ' ')	||			// strip leading blanks
	   ((Str[0] == m_Seperator) && StripSeperator))
	{
		for (int x = 1; 
			 x < Str.GetLength() && 
			 ((Str[x] == ' ')    || 
			 ((Str[x] == m_Seperator) && StripSeperator)); 
			 x++) 
			 ; // do nothing
					
		Str = Str.Right (Str.GetLength() - x);
	}			
}

const char* CEditDate::StrDD (int Day)
{
	if (m_DayZero)
		::wsprintf (szScratch, "%02i", Day);
	else
		::wsprintf (szScratch, "%i", Day);
		
	return szScratch;
}                    

const char* CEditDate::StrMM (int Month)
{
 	if (m_MonthZero)
 		::wsprintf (szScratch, "%02i", Month);
 	else
 		::wsprintf (szScratch, "%i", Month);

	return szScratch;
}

const char* CEditDate::StrYY (int Year)
{
 	if (m_YearCentury)
 		::wsprintf (szScratch, "%04i", Year);
 	else
		::wsprintf (szScratch, "%02i", Year > 1999 ? Year - 2000 : Year - 1900);
		
	return szScratch;		
}