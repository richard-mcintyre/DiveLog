// FORM.H - interface of the CForm class

#define	ID_FILE_RECT		1
#define	ID_FILE_CIRCLE		2
#define	ID_FILE_TEXT		3
#define ID_FILE_LINE		4

class CForm : public CObject
{
public:
	CForm();
	DECLARE_DYNCREATE( CForm )
	~CForm();
	
private:
	CObArray	m_objects;		// The list of drawing objects on this form
	BOOL		m_bPaper;		// Use paper colour?
	COLORREF	m_crPaper;		// The paper colour

public:
	BOOL	LoadForm( const CString filename );
	void	DrawForm( CDC* pDC ) const;
	BOOL	IsFormLoaded() const;
};

