// CHECKBOX.CPP - implementation of the CCheckBox class

#include "stdafx.h"
#include "checkbox.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CCheckBox, CWnd )

BEGIN_MESSAGE_MAP( CCheckBox, CWnd )
	//{{AFX_MSG_MAP(CCheckBox)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// CCheckBox

CDocument*	CCheckBox::m_pDoc = NULL;

CCheckBox::CCheckBox()
{	}

CCheckBox::CCheckBox( const CRect rect, const CString checked, 
						const CString Unchecked, CWnd* pParent, const UINT nID )
{
	m_rect = rect;
	m_checkedRes = checked;
	m_uncheckedRes = Unchecked;
	m_pParent = pParent;
	m_nID = nID;
	m_bState = FALSE;
	
    m_pBitmapButton = new CBitmapButton();
	m_pBitmapButton->Create( NULL, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW,
																m_rect, m_pParent, m_nID );
	m_pBitmapButton->LoadBitmaps( m_uncheckedRes, m_checkedRes );
	
	
}

CCheckBox::~CCheckBox()
{
	delete m_pBitmapButton;
}

void CCheckBox::ChangeState()
{
	m_bState = m_bState ? FALSE : TRUE;
	if( m_bState )		m_pBitmapButton->LoadBitmaps( m_checkedRes, m_uncheckedRes );
	else				m_pBitmapButton->LoadBitmaps( m_uncheckedRes, m_checkedRes );
	m_pBitmapButton->Invalidate();
	m_pDoc->SetModifiedFlag();
}

void CCheckBox::SetState( BOOL bState )
{
	if( m_bState!=bState )
		ChangeState();
}

BOOL CCheckBox::GetState() const
{
	return m_bState;
}

UINT CCheckBox::GetID() const
{
	return m_nID;
}

void CCheckBox::Enable( BOOL bEnable )
{
	m_pBitmapButton->EnableWindow( bEnable );
}


void CCheckBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd ::OnLButtonUp(nFlags, point);
}

