// DRWTOOLS.H - interface of the drawable classes

//////////////////////////////////////////////////////////////////////////
// CBaseDraw - Base class for all drawable objects in the form

class CBaseDraw : public CObject
{
public:
    CBaseDraw();
	virtual ~CBaseDraw( );
	
public:
	static enum ObjType {	Undefined, Rect, Circle, Text, Line		};
private:
	ObjType		m_ObjectType;
	CRect		m_boundingRect;
	
public:
	ObjType	GetType( ) const;
	CRect	GetRect( ) const;
	void	SetType( const ObjType ObjectType );
	void	SetRect( const CRect rect );
	
	virtual	BOOL	Load( CArchive& ar ) = 0;	// Pure virtual
	virtual void	Draw( CDC* pDC ) const = 0;	// Pure virtual
};

////////////////////////////////////////////////////////////////////////////
// CEllipseDraw

class CEllipseDraw : public CBaseDraw
{
public:
	CEllipseDraw( );
	DECLARE_DYNCREATE( CEllipseDraw )
	
private:
	static enum Style	{	Undefined, Flat, Raised, Recessed	};
	
	BOOL		m_bPen;		// Use a pen?
	COLORREF	m_PenColour;
	BOOL		m_bBrush;	// Use a brush?
	COLORREF	m_BrushColour;
	int			m_nLineWidth;
	BOOL		m_bShadow;	// Draw a shadow?
	Style		m_style;
	int			m_nStep;	// Amount stepped when raised or recessed
	
public:
	BOOL	Load( CArchive& ar );
	void	Draw( CDC* pDC ) const;
	
private:
	void	DrawStep( CDC* pDC, int nStep, BOOL bRaised ) const;
};
  
////////////////////////////////////////////////////////////////////////////
// CLineDraw

class CLineDraw : public CBaseDraw
{
public:
	CLineDraw( );
	DECLARE_DYNCREATE( CLineDraw )
	
private:
	COLORREF	m_PenColour;
	int			m_nLineWidth;

public:
	BOOL	Load( CArchive& ar );
	void	Draw( CDC* pDC ) const;
};

////////////////////////////////////////////////////////////////////////////
// CRectDraw

class CRectDraw : public CBaseDraw
{
public:
	CRectDraw( );
	DECLARE_DYNCREATE( CRectDraw )
	
private:
	static enum Style	{	Undefined, Flat, Raised, Recessed	};
	
	BOOL		m_bPen;		// Use a pen?
	COLORREF	m_PenColour;
	BOOL		m_bBrush;	// Use a brush?
	COLORREF	m_BrushColour;
	int			m_nLineWidth;
	BOOL		m_bShadow;	// Draw a shadow?
	Style		m_style;
	int			m_nStep;	// Amount stepped when raised or recessed
	
public:
	BOOL	Load( CArchive& ar );
	void	Draw( CDC* pDC ) const;
	
private:
	void	DrawStep( CDC* pDC, int nStep, BOOL bRaised ) const;
};

////////////////////////////////////////////////////////////////////////////
// CTextDraw

class CTextDraw : public CBaseDraw
{
public:
	CTextDraw( );
	DECLARE_DYNCREATE( CTextDraw )
	
private:
	COLORREF	m_colour;
	LOGFONT		m_logFont;
	BOOL		m_bShadow;
	CString		m_text;			// The text
	UINT		m_flags;		// Draw text flags
	BOOL		m_bDefaultSize;	// Calculate the bounding rect

public:
	BOOL	Load( CArchive& ar );
	void	Draw( CDC* pDC ) const;
};



