
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)
#include <ctl3d.h>

class CDiveApp : public CWinApp
{
public:
	CDiveApp( );
	
	void	WriteMTable1( CArchive& ar );
	void	WriteMTable2( CArchive& ar );
	void	WriteMTable3( CArchive& ar );
	
	void	WriteFTable1( CArchive& ar );
	void	WriteFTable2( CArchive& ar );
	void	WriteFTable3( CArchive& ar );

	WORD	Tab3( BYTE b1, BYTE b2 )	{	return (WORD)((UINT)((BYTE)b1|((WORD)b2<<8)));	}
	
	virtual BOOL InitInstance( );
	virtual int ExitInstance( );
};

CDiveApp::CDiveApp()
{
	m_pszAppName = "C-Base Design";
}

CDiveApp NEAR theApp;

BOOL CDiveApp::InitInstance()
{
	CFile file;
	CFileException fe;
	CDocument tmpDoc;

	Ctl3dRegister( AfxGetInstanceHandle() );
	Ctl3dAutoSubclass( AfxGetInstanceHandle() );


	if( !file.Open( "TABLES.DAT", CFile::modeCreate|CFile::modeWrite, &fe ) )
	{
		tmpDoc.ReportSaveLoadException( "TABLES.DAT", &fe, TRUE, AFX_IDP_INVALID_FILENAME );
		return TRUE;
	}
	
	CArchive ar( &file, CArchive::store );
	
	ar << (BYTE)'D';	ar << (BYTE)'A';	ar << (BYTE)'T';	ar << (BYTE)0x01;

	WriteMTable1( ar );	WriteMTable2( ar );	WriteMTable3( ar );
	WriteFTable1( ar );/*	WriteFTable2( ar );*/	WriteFTable3( ar );

	ar.Close();
	file.Close();
	
	AfxMessageBox( "Data file created" );
	return TRUE;
	
}

int CDiveApp::ExitInstance()
{
	Ctl3dUnregister( AfxGetInstanceHandle() );
	return CWinApp::ExitInstance();
}

void CDiveApp::WriteMTable1( CArchive& ar)
{
	CByteArray depth10;
	depth10.Add( 10 );	depth10.Add( 20 );	depth10.Add( 26 );	depth10.Add( 30 );	depth10.Add( 34 );
	depth10.Add( 37 );	depth10.Add( 41 );	depth10.Add( 45 );	depth10.Add( 50 );	depth10.Add( 54 );
	depth10.Add( 59 );	depth10.Add( 64 );	depth10.Add( 70 );	depth10.Add( 75 );	depth10.Add( 82 );
	depth10.Add( 88 );	depth10.Add( 95 );	depth10.Add( 104 );	depth10.Add( 112 );	depth10.Add( 122 );
	depth10.Add( 133 );	depth10.Add( 145 );	depth10.Add( 160 );	depth10.Add( 178 );	depth10.Add( 199 );
	depth10.Add( 219 );
	
    CByteArray depth12;
    depth12.Add( 9 );	depth12.Add( 17 );	depth12.Add( 23 );	depth12.Add( 26 );	depth12.Add( 29 );
    depth12.Add( 32 );	depth12.Add( 35 );	depth12.Add( 38 );	depth12.Add( 42 );	depth12.Add( 45 );
    depth12.Add( 49 );	depth12.Add( 53 );	depth12.Add( 57 );	depth12.Add( 62 );	depth12.Add( 66 );
	depth12.Add( 71 );	depth12.Add( 76 );	depth12.Add( 82 );	depth12.Add( 88 );	depth12.Add( 94 );
	depth12.Add( 101 );	depth12.Add( 108 );	depth12.Add( 116 );	depth12.Add( 125 );	depth12.Add( 134 );
	depth12.Add( 147 );
	
	CByteArray depth14;
	depth14.Add( 8 );	depth14.Add( 15 );	depth14.Add( 19 );	depth14.Add( 22 );	depth14.Add( 24 );
	depth14.Add( 27 );	depth14.Add( 29 );	depth14.Add( 32 );	depth14.Add( 35 );	depth14.Add( 37 );
	depth14.Add( 40 );	depth14.Add( 43 );	depth14.Add( 47 );	depth14.Add( 50 );	depth14.Add( 53 );
	depth14.Add( 57 );	depth14.Add( 61 );	depth14.Add( 64 );	depth14.Add( 68 );	depth14.Add( 73 );
	depth14.Add( 77 );	depth14.Add( 82 );	depth14.Add( 87 );	depth14.Add( 92 );	depth14.Add( 98 );	
	
	CByteArray depth16;
	depth16.Add( 7 );	depth16.Add( 13 );	depth16.Add( 17 );	depth16.Add( 19 );	depth16.Add( 21 );
	depth16.Add( 23 );	depth16.Add( 25 );	depth16.Add( 27 );	depth16.Add( 29 );	depth16.Add( 32 );
	depth16.Add( 34 );	depth16.Add( 37 );	depth16.Add( 39 );	depth16.Add( 42 );	depth16.Add( 45 );
	depth16.Add( 48 );	depth16.Add( 50 );	depth16.Add( 53 );	depth16.Add( 56 );	depth16.Add( 60 );
	depth16.Add( 63 );	depth16.Add( 67 );	depth16.Add( 70 );	depth16.Add( 72 );
	
	CByteArray depth18;
	depth18.Add( 6 );	depth18.Add( 11 );	depth18.Add( 15 );	depth18.Add( 16 );	depth18.Add( 18 );
	depth18.Add( 20 );	depth18.Add( 22 );	depth18.Add( 24 );	depth18.Add( 26 );	depth18.Add( 28 );
	depth18.Add( 30 );	depth18.Add( 32 );	depth18.Add( 34 );	depth18.Add( 36 );	depth18.Add( 39 );
	depth18.Add( 41 );	depth18.Add( 43 );	depth18.Add( 46 );	depth18.Add( 48 );	depth18.Add( 51 );
	depth18.Add( 53 );	depth18.Add( 55 );	depth18.Add( 56 );
	
	CByteArray depth20;
	depth20.Add( 6 );	depth20.Add( 10 );	depth20.Add( 13 );	depth20.Add( 15 );	depth20.Add( 16 );
	depth20.Add( 18 );	depth20.Add( 20 );	depth20.Add( 21 );	depth20.Add( 23 );	depth20.Add( 25 );
	depth20.Add( 26 );	depth20.Add( 28 );	depth20.Add( 30 );	depth20.Add( 32 );	depth20.Add( 34 );
	depth20.Add( 36 );	depth20.Add( 38 );	depth20.Add( 40 );	depth20.Add( 42 );	depth20.Add( 44 );
	depth20.Add( 45 );
	
	CByteArray depth22;
	depth22.Add( 5 );	depth22.Add( 9 );	depth22.Add( 12 );	depth22.Add( 13 );	depth22.Add( 15 );
	depth22.Add( 16 );	depth22.Add( 18 );	depth22.Add( 19 );	depth22.Add( 21 );	depth22.Add( 22 );
	depth22.Add( 24 );	depth22.Add( 25 );	depth22.Add( 27 );	depth22.Add( 29 );	depth22.Add( 30 );
	depth22.Add( 32 );	depth22.Add( 34 );	depth22.Add( 36 );	depth22.Add( 37 );
	
	CByteArray depth25;
	depth25.Add( 4 );	depth25.Add( 8 );	depth25.Add( 10 );	depth25.Add( 11 );	depth25.Add( 13 );
	depth25.Add( 14 );	depth25.Add( 15 );	depth25.Add( 17 );	depth25.Add( 18 );	depth25.Add( 19 );
	depth25.Add( 21 );	depth25.Add( 22 );	depth25.Add( 23 );	depth25.Add( 25 );	depth25.Add( 26 );
	depth25.Add( 28 );	depth25.Add( 29 );
	
	CByteArray depth30;
	depth30.Add( 3 );	depth30.Add( 6 );	depth30.Add( 8 );	depth30.Add( 9 );	depth30.Add( 10 );
	depth30.Add( 11 );	depth30.Add( 12 );	depth30.Add( 13 );	depth30.Add( 14 );	depth30.Add( 15 );
	depth30.Add( 16 );	depth30.Add( 17 );	depth30.Add( 19 );	depth30.Add( 20 );
	
	CByteArray depth35;
	depth35.Add( 3 );	depth35.Add( 5 );	depth35.Add( 7 );	depth35.Add( 8 );	depth35.Add( 0 );
	depth35.Add( 9 );	depth35.Add( 10 );	depth35.Add( 11 );	depth35.Add( 12 );	depth35.Add( 13 );
	depth35.Add( 14 );
	
	CByteArray depth40;
	depth40.Add( 0 );	depth40.Add( 5 );	depth40.Add( 6 );	depth40.Add( 0 );	depth40.Add( 7 );
	depth40.Add( 8 );	depth40.Add( 9 );
	
	CByteArray depth42;
	depth42.Add( 0 );	depth42.Add( 4 );	depth42.Add( 0 );	depth42.Add( 6 );	depth42.Add( 7 );
	depth42.Add( 8 );
	
	ar << (BYTE)depth10.GetUpperBound();	for( int loop=0; loop<=depth10.GetUpperBound(); loop++ )	ar << depth10.GetAt( loop );
	ar << (BYTE)depth12.GetUpperBound();	for( loop=0; loop<=depth12.GetUpperBound(); loop++ )	ar << depth12.GetAt( loop );
	ar << (BYTE)depth14.GetUpperBound();	for( loop=0; loop<=depth14.GetUpperBound(); loop++ )	ar << depth14.GetAt( loop );
	ar << (BYTE)depth16.GetUpperBound();	for( loop=0; loop<=depth16.GetUpperBound(); loop++ )	ar << depth16.GetAt( loop );
	ar << (BYTE)depth18.GetUpperBound();	for( loop=0; loop<=depth18.GetUpperBound(); loop++ )	ar << depth18.GetAt( loop );
	ar << (BYTE)depth20.GetUpperBound();	for( loop=0; loop<=depth20.GetUpperBound(); loop++ )	ar << depth20.GetAt( loop );
	ar << (BYTE)depth22.GetUpperBound();	for( loop=0; loop<=depth22.GetUpperBound(); loop++ )	ar << depth22.GetAt( loop );
	ar << (BYTE)depth25.GetUpperBound();	for( loop=0; loop<=depth25.GetUpperBound(); loop++ )	ar << depth25.GetAt( loop );
	ar << (BYTE)depth30.GetUpperBound();	for( loop=0; loop<=depth30.GetUpperBound(); loop++ )	ar << depth30.GetAt( loop );
	ar << (BYTE)depth35.GetUpperBound();	for( loop=0; loop<=depth35.GetUpperBound(); loop++ )	ar << depth35.GetAt( loop );
	ar << (BYTE)depth40.GetUpperBound();	for( loop=0; loop<=depth40.GetUpperBound(); loop++ )	ar << depth40.GetAt( loop );
	ar << (BYTE)depth42.GetUpperBound();	for( loop=0; loop<=depth42.GetUpperBound(); loop++ )	ar << depth42.GetAt( loop );	
}

void CDiveApp::WriteMTable2( CArchive& ar )
{
	ar << (WORD)0;	// number of elements - A
	ar << (WORD)300;
	ar << (WORD)1;	// number of elements - B
	ar << (WORD)348;	ar << (WORD)47;
	ar << (WORD)2;	// number of elements - C
	ar << (WORD)410;	ar << (WORD)109;	ar << (WORD)21;
	ar << (WORD)3;	// number of elements - D
	ar << (WORD)419;	ar << (WORD)118;	ar << (WORD)30;		ar << (WORD)8;
	ar << (WORD)4;	// number of elements - E               
	ar << (WORD)428;	ar << (WORD)127;	ar << (WORD)38;		ar << (WORD)16;		ar << (WORD)7;
	ar << (WORD)5;	// number of elements - F
	ar << (WORD)435;	ar << (WORD)134;	ar << (WORD)46;		ar << (WORD)24;		ar << (WORD)15;
	ar << (WORD)7;
	ar << (WORD)6;	// number of elements - G
	ar << (WORD)442;	ar << (WORD)141;	ar << (WORD)53;		ar << (WORD)31;		ar << (WORD)22;
	ar << (WORD)13;		ar << (WORD)6;
	ar << (WORD)7;	// number of elements - H
	ar << (WORD)448;	ar << (WORD)147;	ar << (WORD)59;		ar << (WORD)37;		ar << (WORD)28;
	ar << (WORD)20;		ar << (WORD)12;		ar << (WORD)5;
	ar << (WORD)8;	// number of elements - I
	ar << (WORD)454;	ar << (WORD)153;	ar << (WORD)105;	ar << (WORD)43;		ar << (WORD)34;
	ar << (WORD)26;		ar << (WORD)18;		ar << (WORD)11;		ar << (WORD)5;
	ar << (WORD)9;	// number of elements - J
	ar << (WORD)500;	ar << (WORD)159;	ar << (WORD)111;	ar << (WORD)49;		ar << (WORD)40;
	ar << (WORD)31;		ar << (WORD)24;		ar << (WORD)17;		ar << (WORD)11;		ar << (WORD)5;
	ar << (WORD)10;	// number of elements - K
	ar << (WORD)505;	ar << (WORD)204;	ar << (WORD)116;	ar << (WORD)54;		ar << (WORD)45;
	ar << (WORD)37;		ar << (WORD)29;		ar << (WORD)22;		ar << (WORD)16;		ar << (WORD)10;
	ar << (WORD)4;
	ar << (WORD)11;	// number of elements - L
	ar << (WORD)510;	ar << (WORD)209;	ar << (WORD)121;	ar << (WORD)59;		ar << (WORD)50;
	ar << (WORD)42;		ar << (WORD)34;		ar << (WORD)27;		ar << (WORD)21;		ar << (WORD)15;
	ar << (WORD)9;		ar << (WORD)4;
	ar << (WORD)12;	// number of elements - M
	ar << (WORD)515;	ar << (WORD)214;	ar << (WORD)125;	ar << (WORD)104;	ar << (WORD)55;
	ar << (WORD)46;		ar << (WORD)39;		ar << (WORD)32;		ar << (WORD)25;		ar << (WORD)19;
	ar << (WORD)14;		ar << (WORD)9;		ar << (WORD)4;
	ar << (WORD)13;	// number of elements - N
	ar << (WORD)519;	ar << (WORD)218;	ar << (WORD)130;	ar << (WORD)108;	ar << (WORD)59;
	ar << (WORD)51;		ar << (WORD)43;		ar << (WORD)36;		ar << (WORD)30;		ar << (WORD)24;
	ar << (WORD)18;		ar << (WORD)13;		ar << (WORD)8;		ar << (WORD)3;
	ar << (WORD)14;	// number of elements - O
	ar << (WORD)524;	ar << (WORD)223;	ar << (WORD)134;	ar << (WORD)112;	ar << (WORD)103;
	ar << (WORD)55;		ar << (WORD)47;		ar << (WORD)41;		ar << (WORD)34;		ar << (WORD)28;
	ar << (WORD)23;		ar << (WORD)17;		ar << (WORD)12;		ar << (WORD)8;		ar << (WORD)3;
	ar << (WORD)15;	// number of elements - P
	ar << (WORD)528;	ar << (WORD)227;	ar << (WORD)138;	ar << (WORD)116;	ar << (WORD)107;
	ar << (WORD)59;		ar << (WORD)51;		ar << (WORD)45;		ar << (WORD)38;		ar << (WORD)32;
	ar << (WORD)27;		ar << (WORD)21;		ar << (WORD)16;		ar << (WORD)12;		ar << (WORD)7;
	ar << (WORD)3;
	ar << (WORD)16;	// number of elements - Q
	ar << (WORD)531;	ar << (WORD)230;	ar << (WORD)142;	ar << (WORD)120;	ar << (WORD)111;
	ar << (WORD)103;	ar << (WORD)55;		ar << (WORD)48;		ar << (WORD)42;		ar << (WORD)36;
	ar << (WORD)30;		ar << (WORD)25;		ar << (WORD)20;		ar << (WORD)16;		ar << (WORD)11;
	ar << (WORD)7;		ar << (WORD)3;
	ar << (WORD)17;	// number of elements - R
	ar << (WORD)535;	ar << (WORD)234;	ar << (WORD)146;	ar << (WORD)124;	ar << (WORD)115;
	ar << (WORD)107;	ar << (WORD)59;		ar << (WORD)52;		ar << (WORD)46;		ar << (WORD)40;
	ar << (WORD)34;		ar << (WORD)29;		ar << (WORD)24;		ar << (WORD)19;		ar << (WORD)15;
	ar << (WORD)11;		ar << (WORD)7;		ar << (WORD)3;
	ar << (WORD)18;	// number of elements - S
	ar << (WORD)539;	ar << (WORD)238;	ar << (WORD)149;	ar << (WORD)127;	ar << (WORD)118;
	ar << (WORD)110;	ar << (WORD)103;	ar << (WORD)56;		ar << (WORD)49;		ar << (WORD)43;
	ar << (WORD)38;		ar << (WORD)32;		ar << (WORD)27;		ar << (WORD)23;		ar << (WORD)18;
	ar << (WORD)14;		ar << (WORD)10;		ar << (WORD)6;		ar << (WORD)3;
	ar << (WORD)19;	// number of elements - T
	ar << (WORD)542;	ar << (WORD)241;	ar << (WORD)153;	ar << (WORD)131;	ar << (WORD)122;
	ar << (WORD)113;	ar << (WORD)106;	ar << (WORD)59;		ar << (WORD)53;		ar << (WORD)47;
	ar << (WORD)41;		ar << (WORD)36;		ar << (WORD)31;		ar << (WORD)26;		ar << (WORD)22;
	ar << (WORD)17;		ar << (WORD)13;		ar << (WORD)10;		ar << (WORD)6;		ar << (WORD)2;
	ar << (WORD)20;	// number of elements - U
	ar << (WORD)545;	ar << (WORD)244;	ar << (WORD)156;	ar << (WORD)134;	ar << (WORD)125;
	ar << (WORD)117;	ar << (WORD)109;	ar << (WORD)102;	ar << (WORD)56;		ar << (WORD)50;
	ar << (WORD)44;		ar << (WORD)39;		ar << (WORD)34;		ar << (WORD)29;		ar << (WORD)25;
	ar << (WORD)21;		ar << (WORD)17;		ar << (WORD)13;		ar << (WORD)9;		ar << (WORD)6;
	ar << (WORD)2;
	ar << (WORD)21;	// number of elements - V
	ar << (WORD)548;	ar << (WORD)247;	ar << (WORD)159;	ar << (WORD)137;	ar << (WORD)128;
	ar << (WORD)120;	ar << (WORD)112;	ar << (WORD)105;	ar << (WORD)59;		ar << (WORD)53;
	ar << (WORD)47;		ar << (WORD)42;		ar << (WORD)37;		ar << (WORD)33;		ar << (WORD)28;
	ar << (WORD)24;		ar << (WORD)20;		ar << (WORD)16;		ar << (WORD)12;		ar << (WORD)9;
	ar << (WORD)5;		ar << (WORD)2;
	ar << (WORD)22;	// number of elements - W
	ar << (WORD)551;	ar << (WORD)250;	ar << (WORD)202;	ar << (WORD)140;	ar << (WORD)131;
	ar << (WORD)123;	ar << (WORD)115;	ar << (WORD)108;	ar << (WORD)102;	ar << (WORD)56;
	ar << (WORD)50;		ar << (WORD)45;		ar << (WORD)40;		ar << (WORD)36;		ar << (WORD)31;
	ar << (WORD)27;		ar << (WORD)23;		ar << (WORD)19;		ar << (WORD)15;		ar << (WORD)12;
	ar << (WORD)8;		ar << (WORD)5;		ar << (WORD)2;
	ar << (WORD)23;	// number of elements - X
	ar << (WORD)554;	ar << (WORD)253;	ar << (WORD)205;	ar << (WORD)143;	ar << (WORD)134;
	ar << (WORD)126;	ar << (WORD)118;	ar << (WORD)111;	ar << (WORD)105;	ar << (WORD)59;
	ar << (WORD)53;		ar << (WORD)48;		ar << (WORD)43;		ar << (WORD)39;		ar << (WORD)34;
	ar << (WORD)30;		ar << (WORD)26;		ar << (WORD)22;		ar << (WORD)18;		ar << (WORD)15;
	ar << (WORD)11;		ar << (WORD)8;		ar << (WORD)5;		ar << (WORD)2;
	ar << (WORD)24;	// number of elements - Y
	ar << (WORD)557;	ar << (WORD)256;	ar << (WORD)208;	ar << (WORD)146;	ar << (WORD)137;
	ar << (WORD)129;	ar << (WORD)121;	ar << (WORD)114;	ar << (WORD)108;	ar << (WORD)102;
	ar << (WORD)56;		ar << (WORD)51;		ar << (WORD)46;		ar << (WORD)41;		ar << (WORD)37;
	ar << (WORD)33;		ar << (WORD)29;		ar << (WORD)25;		ar << (WORD)21;		ar << (WORD)18;
	ar << (WORD)14;		ar << (WORD)11;		ar << (WORD)8;		ar << (WORD)5;		ar << (WORD)2;
	ar << (WORD)25;	// number of elements - Z
	ar << (WORD)600;	ar << (WORD)259;	ar << (WORD)211;	ar << (WORD)149;	ar << (WORD)140;
	ar << (WORD)131;	ar << (WORD)124;	ar << (WORD)117;	ar << (WORD)111;	ar << (WORD)105;
	ar << (WORD)59;		ar << (WORD)54;		ar << (WORD)49;		ar << (WORD)44;		ar << (WORD)40;
	ar << (WORD)35;		ar << (WORD)31;		ar << (WORD)28;		ar << (WORD)24;		ar << (WORD)20;
	ar << (WORD)17;		ar << (WORD)14;		ar << (WORD)11;		ar << (WORD)8;		ar << (WORD)5;
	ar << (WORD)2;
}

void CDiveApp::WriteMTable3( CArchive& ar )
{
	ar << (BYTE)10;	// number of elements - A
	ar << Tab3( 10, 209 );	ar << Tab3( 9, 138 );	ar << Tab3( 8, 90 );	ar << Tab3( 7, 65 );
	ar << Tab3( 6, 50 );	ar << Tab3( 6, 39 );	ar << Tab3( 5, 32 );	ar << Tab3( 4, 25 );
	ar << Tab3( 3, 17 );	ar << Tab3( 3, 11 );	ar << Tab3( 2, 7 );
	ar << (BYTE)10;	// number of elements - B
	ar << Tab3( 20, 199 );	ar << Tab3( 17, 130 );	ar << Tab3( 15, 83 );	ar << Tab3( 13, 59 );
	ar << Tab3( 11, 45 );	ar << Tab3( 10, 35 );	ar << Tab3( 9, 28 );	ar << Tab3( 8, 21 );
	ar << Tab3( 6, 14 );	ar << Tab3( 5, 9 );		ar << Tab3( 5, 4 );
	ar << (BYTE)10;	// number of elements - C
	ar << Tab3( 26, 193 );	ar << Tab3( 23, 124 );	ar << Tab3( 19, 79 );	ar << Tab3( 17, 55 );
	ar << Tab3( 15, 41 );	ar << Tab3( 13, 32 );	ar << Tab3( 12, 25 );	ar << Tab3( 10, 19 );
	ar << Tab3( 8, 12 );	ar << Tab3( 7, 7 );		ar << Tab3( 6, 0 );
	ar << (BYTE)10;	// number of elements - D
	ar << Tab3( 30, 189 );	ar << Tab3( 26, 121 );	ar << Tab3( 22, 76 );	ar << Tab3( 19, 53 );
	ar << Tab3( 16, 40 );	ar << Tab3( 15, 30 );	ar << Tab3( 13, 24 );	ar << Tab3( 11, 18 );
	ar << Tab3( 9, 11 );	ar << Tab3( 8, 6 );		ar << Tab3( 7, 0 );
	ar << (BYTE)10;	// number of elements - E
	ar << Tab3( 34, 185 );	ar << Tab3( 29, 118 );	ar << Tab3( 24, 74 );	ar << Tab3( 21, 51 );
	ar << Tab3( 18, 38 );	ar << Tab3( 16, 29 );	ar << Tab3( 15, 22 );	ar << Tab3( 13, 16 );
	ar << Tab3( 10, 10 );	ar << Tab3( 9, 5 );		ar << Tab3( 7, 0 );
	ar << (BYTE)10;	// number of elements - F
	ar << Tab3( 37, 182 );	ar << Tab3( 32, 115 );	ar << Tab3( 27, 71 );	ar << Tab3( 23, 49 );
	ar << Tab3( 20, 36 );	ar << Tab3( 18, 27 );	ar << Tab3( 16, 21 );	ar << Tab3( 14, 15 );
	ar << Tab3( 11, 9 );	ar << Tab3( 9, 5 );	ar << Tab3( 8, 0 );
	ar << (BYTE)10;	// number of elements - G
	ar << Tab3( 41, 178 );	ar << Tab3( 35, 112 );	ar << Tab3( 29, 69 );	ar << Tab3( 25, 47 );
	ar << Tab3( 22, 34 );	ar << Tab3( 20, 25 );	ar << Tab3( 18, 19 );	ar << Tab3( 15, 14 );
	ar << Tab3( 12, 8 );	ar << Tab3( 10, 4 );	ar << Tab3( 9, 0 );
	ar << (BYTE)9;	// number of elements - H
	ar << Tab3( 45, 174 );	ar << Tab3( 38, 109 );	ar << Tab3( 32, 66 );	ar << Tab3( 27, 45 );
	ar << Tab3( 24, 32 );	ar << Tab3( 21, 24 );	ar << Tab3( 19, 18 );	ar << Tab3( 17, 12 );
	ar << Tab3( 13, 7 );	ar << Tab3( 11, 3 );
	ar << (BYTE)9;	// number of elements - I
	ar << Tab3( 50, 169 );	ar << Tab3( 42, 105 );	ar << Tab3( 35, 63 );	ar << Tab3( 29, 43 );
	ar << Tab3( 26, 30 );	ar << Tab3( 23, 22 );	ar << Tab3( 21, 16 );	ar << Tab3( 18, 11 );
	ar << Tab3( 14, 6 );	ar << Tab3( 12, 0 );
	ar << (BYTE)9;	// number of elements - J
	ar << Tab3( 54, 165 );	ar << Tab3( 45, 102 );	ar << Tab3( 37, 61 );	ar << Tab3( 32, 40 );
	ar << Tab3( 28, 28 );	ar << Tab3( 25, 20 );	ar << Tab3( 22, 15 );	ar << Tab3( 19, 10 );
	ar << Tab3( 15, 5 );	ar << Tab3( 13, 0 );
	ar << (BYTE)9;	// number of elements - K
	ar << Tab3( 59, 160 );	ar << Tab3( 49, 98 );	ar << Tab3( 40, 58 );	ar << Tab3( 34, 38 );
	ar << Tab3( 30, 26 );	ar << Tab3( 26, 19 );	ar << Tab3( 24, 13 );	ar << Tab3( 21, 8 );
	ar << Tab3( 16, 4 );	ar << Tab3( 14, 0 );
	ar << (BYTE)8;	// number of elements - L
	ar << Tab3( 64, 155 );	ar << Tab3( 53, 94 );	ar << Tab3( 43, 55 );	ar << Tab3( 37, 35 );
	ar << Tab3( 32, 24 );	ar << Tab3( 28, 17 );	ar << Tab3( 25, 12 );	ar << Tab3( 22, 7 );
	ar << Tab3( 17, 3 );
	ar << (BYTE)8;	// number of elements - M
	ar << Tab3( 70, 149 );	ar << Tab3( 57, 90 );	ar << Tab3( 47, 51 );	ar << Tab3( 39, 33 );
	ar << Tab3( 34, 22 );	ar << Tab3( 30, 15 );	ar << Tab3( 27, 10 );	ar << Tab3( 23, 6 );
	ar << Tab3( 19, 0 );
	ar << (BYTE)8;	// number of elements - N
	ar << Tab3( 75, 144 );	ar << Tab3( 62, 85 );	ar << Tab3( 50, 48 );	ar << Tab3( 42, 30 );
	ar << Tab3( 36, 20 );	ar << Tab3( 32, 13 );	ar << Tab3( 29, 8 );	ar << Tab3( 25, 4 );
	ar << Tab3( 20, 0 );
	ar << (BYTE)7;	// number of elements - O
	ar << Tab3( 82, 137 );	ar << Tab3( 66, 81 );	ar << Tab3( 53, 45 );	ar << Tab3( 45, 27 );
	ar << Tab3( 39, 17 );	ar << Tab3( 34, 11 );	ar << Tab3( 30, 7 );	ar << Tab3( 26, 3 );
	ar << (BYTE)7;	// number of elements - P
	ar << Tab3( 88, 131 );	ar << Tab3( 71, 76 );	ar << Tab3( 57, 41 );	ar << Tab3( 48, 24 );
	ar << Tab3( 41, 15 );	ar << Tab3( 36, 9 );	ar << Tab3( 32, 5 );	ar << Tab3( 28, 0 );
	ar << (BYTE)7;	// number of elements - Q
	ar << Tab3( 95, 124 );	ar << Tab3( 76, 71 );	ar << Tab3( 61, 37 );	ar << Tab3( 50, 22 );
	ar << Tab3( 43, 13 );	ar << Tab3( 38, 7 );	ar << Tab3( 34, 3 );	ar << Tab3( 29, 0 );
	ar << (BYTE)6;	// number of elements - R
	ar << Tab3( 104, 115 );	ar << Tab3( 82, 65 );	ar << Tab3( 64, 34 );	ar << Tab3( 53, 19 );
	ar << Tab3( 46, 10 );	ar << Tab3( 40, 5 );	ar << Tab3( 36, 0 );
	ar << (BYTE)6;	// number of elements - S
	ar << Tab3( 112, 107 );	ar << Tab3( 88, 59 );	ar << Tab3( 68, 30 );	ar << Tab3( 56, 16 );
	ar << Tab3( 48, 8 );	ar << Tab3( 42, 3 );	ar << Tab3( 37, 0 );
	ar << (BYTE)5;	// number of elements - T
	ar << Tab3( 122, 97 );	ar << Tab3( 94, 53 );	ar << Tab3( 73, 25 );	ar << Tab3( 60, 12 );
	ar << Tab3( 51, 5 );	ar << Tab3( 44, 0 );
	ar << (BYTE)5;	// number of elements - U
	ar << Tab3( 133, 86 );	ar << Tab3( 101, 46 );	ar << Tab3( 77, 21 );	ar << Tab3( 63, 9 );
	ar << Tab3( 53, 3 );	ar << Tab3( 45, 0 );
	ar << (BYTE)4;	// number of elements - V
	ar << Tab3( 145, 74 );	ar << Tab3( 108, 39 );	ar << Tab3( 82, 16 );	ar << Tab3( 67, 5 );
	ar << Tab3( 55, 0 );
	ar << (BYTE)4;	// number of elements - W
	ar << Tab3( 160, 59 );	ar << Tab3( 116, 31 );	ar << Tab3( 87, 11 );	ar << Tab3( 70, 2 );
	ar << Tab3( 56, 0 );
	ar << (BYTE)3;	// number of elements - X
	ar << Tab3( 178, 41 );	ar << Tab3( 125, 22 );	ar << Tab3( 92, 6 );	ar << Tab3( 72, 0 );
	ar << (BYTE)2;	// number of elements - Y
	ar << Tab3( 199, 20 );	ar << Tab3( 134, 13 );	ar << Tab3( 98, 0 );
	ar << (BYTE)1;	// number of elements - Z
	ar << Tab3( 219, 0 );	ar << Tab3( 147, 0 );
}

void CDiveApp::WriteFTable1( CArchive& ar)
{
	CByteArray depth35;
	depth35.Add( 10 );	depth35.Add( 19 );	depth35.Add( 25 );	depth35.Add( 29 );	depth35.Add( 32 );
	depth35.Add( 36 );	depth35.Add( 40 );	depth35.Add( 44 );	depth35.Add( 48 );	depth35.Add( 52 );
	depth35.Add( 57 );	depth35.Add( 62 );	depth35.Add( 67 );	depth35.Add( 73 );	depth35.Add( 79 );
	depth35.Add( 85 );	depth35.Add( 92 );	depth35.Add( 100 );	depth35.Add( 108 );	depth35.Add( 117 );
	depth35.Add( 127 );	depth35.Add( 139 );	depth35.Add( 152 );	depth35.Add( 168 );	depth35.Add( 188 );
	depth35.Add( 205 );
	
    CByteArray depth40;
    depth40.Add( 9 );	depth40.Add( 16 );	depth40.Add( 22 );	depth40.Add( 25 );	depth40.Add( 27 );
    depth40.Add( 31 );	depth40.Add( 34 );	depth40.Add( 37 );	depth40.Add( 40 );	depth40.Add( 44 );
    depth40.Add( 48 );	depth40.Add( 51 );	depth40.Add( 55 );	depth40.Add( 60 );	depth40.Add( 64 );
	depth40.Add( 69 );	depth40.Add( 74 );	depth40.Add( 79 );	depth40.Add( 85 );	depth40.Add( 91 );
	depth40.Add( 97 );	depth40.Add( 104 );	depth40.Add( 111 );	depth40.Add( 120 );	depth40.Add( 129 );
	depth40.Add( 140 );
	
	CByteArray depth50;
	depth50.Add( 7 );	depth50.Add( 13 );	depth50.Add( 17 );	depth50.Add( 19 );	depth50.Add( 21 );
	depth50.Add( 24 );	depth50.Add( 26 );	depth50.Add( 28 );	depth50.Add( 31 );	depth50.Add( 33 );
	depth50.Add( 36 );	depth50.Add( 39 );	depth50.Add( 41 );	depth50.Add( 44 );	depth50.Add( 47 );
	depth50.Add( 50 );	depth50.Add( 53 );	depth50.Add( 57 );	depth50.Add( 60 );	depth50.Add( 63 );
	depth50.Add( 67 );	depth50.Add( 71 );	depth50.Add( 75 );	depth50.Add( 80 );
	
	CByteArray depth60;
	depth60.Add( 6 );	depth60.Add( 11 );	depth60.Add( 14 );	depth60.Add( 16 );	depth60.Add( 17 );
	depth60.Add( 19 );	depth60.Add( 21 );	depth60.Add( 23 );	depth60.Add( 25 );	depth60.Add( 27 );
	depth60.Add( 29 );	depth60.Add( 31 );	depth60.Add( 33 );	depth60.Add( 35 );	depth60.Add( 37 );
	depth60.Add( 39 );	depth60.Add( 42 );	depth60.Add( 44 );	depth60.Add( 47 );	depth60.Add( 49 );
	depth60.Add( 52 );	depth60.Add( 54 );	depth60.Add( 55 );
	
	CByteArray depth70;
	depth70.Add( 5 );	depth70.Add( 9 );	depth70.Add( 12 );	depth70.Add( 13 );	depth70.Add( 15 );
	depth70.Add( 16 );	depth70.Add( 18 );	depth70.Add( 19 );	depth70.Add( 21 );	depth70.Add( 22 );
	depth70.Add( 24 );	depth70.Add( 26 );	depth70.Add( 27 );	depth70.Add( 29 );	depth70.Add( 31 );
	depth70.Add( 33 );	depth70.Add( 35 );	depth70.Add( 36 );	depth70.Add( 38 );	depth70.Add( 40 );
	
	CByteArray depth80;
	depth80.Add( 4 );	depth80.Add( 8 );	depth80.Add( 10 );	depth80.Add( 11 );	depth80.Add( 13 );
	depth80.Add( 14 );	depth80.Add( 15 );	depth80.Add( 17 );	depth80.Add( 18 );	depth80.Add( 19 );
	depth80.Add( 21 );	depth80.Add( 22 );	depth80.Add( 23 );	depth80.Add( 25 );	depth80.Add( 26 );
	depth80.Add( 28 );	depth80.Add( 29 );	depth80.Add( 30 );
	
	CByteArray depth90;
	depth90.Add( 4 );	depth90.Add( 7 );	depth90.Add( 9 );	depth90.Add( 10 );	depth90.Add( 11 );
	depth90.Add( 12 );	depth90.Add( 13 );	depth90.Add( 15 );	depth90.Add( 16 );	depth90.Add( 47 );
	depth90.Add( 18 );	depth90.Add( 19 );	depth90.Add( 21 );	depth90.Add( 22 );	depth90.Add( 23 );
	depth90.Add( 24 );	depth90.Add( 25 );
	
	CByteArray depth100;
	depth100.Add( 3 );	depth100.Add( 6 );	depth100.Add( 8 );	depth100.Add( 9 );	depth100.Add( 10 );
	depth100.Add( 11 );	depth100.Add( 12 );	depth100.Add( 13 );	depth100.Add( 14 );	depth100.Add( 15 );
	depth100.Add( 16 );	depth100.Add( 17 );	depth100.Add( 18 );	depth100.Add( 19 );	depth100.Add( 20 );

	CByteArray depth110;
	depth110.Add( 3 );	depth110.Add( 6 );	depth110.Add( 7 );	depth110.Add( 8 );	depth110.Add( 9 );
	depth110.Add( 10 );	depth110.Add( 11 );	depth110.Add( 12 );	depth110.Add( 13 );	depth110.Add( 0 );
	depth110.Add( 15 );	depth110.Add( 15 );	depth110.Add( 16 );
	
	CByteArray depth120;
	depth120.Add( 3 );	depth120.Add( 5 );	depth120.Add( 6 );	depth120.Add( 7 );	depth120.Add( 8 );
	depth120.Add( 9 );	depth120.Add( 10 );	depth120.Add( 11 );	depth120.Add( 0 );	depth120.Add( 12 );
	depth120.Add( 13 );
	
	CByteArray depth130;
	depth130.Add( 3 );	depth130.Add( 5 );	depth130.Add( 6 );	depth130.Add( 7 );	depth130.Add( 0 );
	depth130.Add( 8 );	depth130.Add( 9 );	depth130.Add( 10 );
	
	CByteArray depth140;
	depth140.Add( 0 );	depth140.Add( 4 );	depth140.Add( 5 );	depth140.Add( 6 );	depth140.Add( 7 );
	depth140.Add( 8 );
	
	ar << (BYTE)depth35.GetUpperBound();	for( int loop=0; loop<=depth35.GetUpperBound(); loop++ )	ar << depth35.GetAt( loop );
	ar << (BYTE)depth40.GetUpperBound();	for( loop=0; loop<=depth40.GetUpperBound(); loop++ )	ar << depth40.GetAt( loop );
	ar << (BYTE)depth50.GetUpperBound();	for( loop=0; loop<=depth50.GetUpperBound(); loop++ )	ar << depth50.GetAt( loop );
	ar << (BYTE)depth60.GetUpperBound();	for( loop=0; loop<=depth60.GetUpperBound(); loop++ )	ar << depth60.GetAt( loop );
	ar << (BYTE)depth70.GetUpperBound();	for( loop=0; loop<=depth70.GetUpperBound(); loop++ )	ar << depth70.GetAt( loop );
	ar << (BYTE)depth80.GetUpperBound();	for( loop=0; loop<=depth80.GetUpperBound(); loop++ )	ar << depth80.GetAt( loop );
	ar << (BYTE)depth90.GetUpperBound();	for( loop=0; loop<=depth90.GetUpperBound(); loop++ )	ar << depth90.GetAt( loop );
	ar << (BYTE)depth100.GetUpperBound();	for( loop=0; loop<=depth100.GetUpperBound(); loop++ )	ar << depth100.GetAt( loop );
	ar << (BYTE)depth110.GetUpperBound();	for( loop=0; loop<=depth110.GetUpperBound(); loop++ )	ar << depth110.GetAt( loop );
	ar << (BYTE)depth120.GetUpperBound();	for( loop=0; loop<=depth120.GetUpperBound(); loop++ )	ar << depth120.GetAt( loop );
	ar << (BYTE)depth130.GetUpperBound();	for( loop=0; loop<=depth130.GetUpperBound(); loop++ )	ar << depth130.GetAt( loop );
	ar << (BYTE)depth140.GetUpperBound();	for( loop=0; loop<=depth140.GetUpperBound(); loop++ )	ar << depth140.GetAt( loop );	
}

void CDiveApp::WriteFTable2( CArchive& ar )
{
	ar << (WORD)0;	// number of elements - A
	ar << (WORD)300;
	ar << (WORD)1;	// number of elements - B
	ar << (WORD)348;	ar << (WORD)47;
	ar << (WORD)2;	// number of elements - C
	ar << (WORD)410;	ar << (WORD)109;	ar << (WORD)21;
	ar << (WORD)3;	// number of elements - D
	ar << (WORD)419;	ar << (WORD)118;	ar << (WORD)30;		ar << (WORD)8;
	ar << (WORD)4;	// number of elements - E               
	ar << (WORD)428;	ar << (WORD)127;	ar << (WORD)38;		ar << (WORD)16;		ar << (WORD)7;
	ar << (WORD)5;	// number of elements - F
	ar << (WORD)435;	ar << (WORD)134;	ar << (WORD)46;		ar << (WORD)24;		ar << (WORD)15;
	ar << (WORD)7;
	ar << (WORD)6;	// number of elements - G
	ar << (WORD)442;	ar << (WORD)141;	ar << (WORD)53;		ar << (WORD)31;		ar << (WORD)22;
	ar << (WORD)13;		ar << (WORD)6;
	ar << (WORD)7;	// number of elements - H
	ar << (WORD)448;	ar << (WORD)147;	ar << (WORD)59;		ar << (WORD)37;		ar << (WORD)28;
	ar << (WORD)20;		ar << (WORD)12;		ar << (WORD)5;
	ar << (WORD)8;	// number of elements - I
	ar << (WORD)454;	ar << (WORD)153;	ar << (WORD)105;	ar << (WORD)43;		ar << (WORD)34;
	ar << (WORD)26;		ar << (WORD)18;		ar << (WORD)11;		ar << (WORD)5;
	ar << (WORD)9;	// number of elements - J
	ar << (WORD)500;	ar << (WORD)159;	ar << (WORD)111;	ar << (WORD)49;		ar << (WORD)40;
	ar << (WORD)31;		ar << (WORD)24;		ar << (WORD)17;		ar << (WORD)11;		ar << (WORD)5;
	ar << (WORD)10;	// number of elements - K
	ar << (WORD)505;	ar << (WORD)204;	ar << (WORD)116;	ar << (WORD)54;		ar << (WORD)45;
	ar << (WORD)37;		ar << (WORD)29;		ar << (WORD)22;		ar << (WORD)16;		ar << (WORD)10;
	ar << (WORD)4;
	ar << (WORD)11;	// number of elements - L
	ar << (WORD)510;	ar << (WORD)209;	ar << (WORD)121;	ar << (WORD)59;		ar << (WORD)50;
	ar << (WORD)42;		ar << (WORD)34;		ar << (WORD)27;		ar << (WORD)21;		ar << (WORD)15;
	ar << (WORD)9;		ar << (WORD)4;
	ar << (WORD)12;	// number of elements - M
	ar << (WORD)515;	ar << (WORD)214;	ar << (WORD)125;	ar << (WORD)104;	ar << (WORD)55;
	ar << (WORD)46;		ar << (WORD)39;		ar << (WORD)32;		ar << (WORD)25;		ar << (WORD)19;
	ar << (WORD)14;		ar << (WORD)9;		ar << (WORD)4;
	ar << (WORD)13;	// number of elements - N
	ar << (WORD)519;	ar << (WORD)218;	ar << (WORD)130;	ar << (WORD)108;	ar << (WORD)59;
	ar << (WORD)51;		ar << (WORD)43;		ar << (WORD)36;		ar << (WORD)30;		ar << (WORD)24;
	ar << (WORD)18;		ar << (WORD)13;		ar << (WORD)8;		ar << (WORD)3;
	ar << (WORD)14;	// number of elements - O
	ar << (WORD)524;	ar << (WORD)223;	ar << (WORD)134;	ar << (WORD)112;	ar << (WORD)103;
	ar << (WORD)55;		ar << (WORD)47;		ar << (WORD)41;		ar << (WORD)34;		ar << (WORD)28;
	ar << (WORD)23;		ar << (WORD)17;		ar << (WORD)12;		ar << (WORD)8;		ar << (WORD)3;
	ar << (WORD)15;	// number of elements - P
	ar << (WORD)528;	ar << (WORD)227;	ar << (WORD)138;	ar << (WORD)116;	ar << (WORD)107;
	ar << (WORD)59;		ar << (WORD)51;		ar << (WORD)45;		ar << (WORD)38;		ar << (WORD)32;
	ar << (WORD)27;		ar << (WORD)21;		ar << (WORD)16;		ar << (WORD)12;		ar << (WORD)7;
	ar << (WORD)3;
	ar << (WORD)16;	// number of elements - Q
	ar << (WORD)531;	ar << (WORD)230;	ar << (WORD)142;	ar << (WORD)120;	ar << (WORD)111;
	ar << (WORD)103;	ar << (WORD)55;		ar << (WORD)48;		ar << (WORD)42;		ar << (WORD)36;
	ar << (WORD)30;		ar << (WORD)25;		ar << (WORD)20;		ar << (WORD)16;		ar << (WORD)11;
	ar << (WORD)7;		ar << (WORD)3;
	ar << (WORD)17;	// number of elements - R
	ar << (WORD)535;	ar << (WORD)234;	ar << (WORD)146;	ar << (WORD)124;	ar << (WORD)115;
	ar << (WORD)107;	ar << (WORD)59;		ar << (WORD)52;		ar << (WORD)46;		ar << (WORD)40;
	ar << (WORD)34;		ar << (WORD)29;		ar << (WORD)24;		ar << (WORD)19;		ar << (WORD)15;
	ar << (WORD)11;		ar << (WORD)7;		ar << (WORD)3;
	ar << (WORD)18;	// number of elements - S
	ar << (WORD)539;	ar << (WORD)238;	ar << (WORD)149;	ar << (WORD)127;	ar << (WORD)118;
	ar << (WORD)110;	ar << (WORD)103;	ar << (WORD)56;		ar << (WORD)49;		ar << (WORD)43;
	ar << (WORD)38;		ar << (WORD)32;		ar << (WORD)27;		ar << (WORD)23;		ar << (WORD)18;
	ar << (WORD)14;		ar << (WORD)10;		ar << (WORD)6;		ar << (WORD)3;
	ar << (WORD)19;	// number of elements - T
	ar << (WORD)542;	ar << (WORD)241;	ar << (WORD)153;	ar << (WORD)131;	ar << (WORD)122;
	ar << (WORD)113;	ar << (WORD)106;	ar << (WORD)59;		ar << (WORD)53;		ar << (WORD)47;
	ar << (WORD)41;		ar << (WORD)36;		ar << (WORD)31;		ar << (WORD)26;		ar << (WORD)22;
	ar << (WORD)17;		ar << (WORD)13;		ar << (WORD)10;		ar << (WORD)6;		ar << (WORD)2;
	ar << (WORD)20;	// number of elements - U
	ar << (WORD)545;	ar << (WORD)244;	ar << (WORD)156;	ar << (WORD)134;	ar << (WORD)125;
	ar << (WORD)117;	ar << (WORD)109;	ar << (WORD)102;	ar << (WORD)56;		ar << (WORD)50;
	ar << (WORD)44;		ar << (WORD)39;		ar << (WORD)34;		ar << (WORD)29;		ar << (WORD)25;
	ar << (WORD)21;		ar << (WORD)17;		ar << (WORD)13;		ar << (WORD)9;		ar << (WORD)6;
	ar << (WORD)2;
	ar << (WORD)21;	// number of elements - V
	ar << (WORD)548;	ar << (WORD)247;	ar << (WORD)159;	ar << (WORD)137;	ar << (WORD)128;
	ar << (WORD)120;	ar << (WORD)112;	ar << (WORD)105;	ar << (WORD)59;		ar << (WORD)53;
	ar << (WORD)47;		ar << (WORD)42;		ar << (WORD)37;		ar << (WORD)33;		ar << (WORD)28;
	ar << (WORD)24;		ar << (WORD)20;		ar << (WORD)16;		ar << (WORD)12;		ar << (WORD)9;
	ar << (WORD)5;		ar << (WORD)2;
	ar << (WORD)22;	// number of elements - W
	ar << (WORD)551;	ar << (WORD)250;	ar << (WORD)202;	ar << (WORD)140;	ar << (WORD)131;
	ar << (WORD)123;	ar << (WORD)115;	ar << (WORD)108;	ar << (WORD)102;	ar << (WORD)56;
	ar << (WORD)50;		ar << (WORD)45;		ar << (WORD)40;		ar << (WORD)36;		ar << (WORD)31;
	ar << (WORD)27;		ar << (WORD)23;		ar << (WORD)19;		ar << (WORD)15;		ar << (WORD)12;
	ar << (WORD)8;		ar << (WORD)5;		ar << (WORD)2;
	ar << (WORD)23;	// number of elements - X
	ar << (WORD)554;	ar << (WORD)253;	ar << (WORD)205;	ar << (WORD)143;	ar << (WORD)134;
	ar << (WORD)126;	ar << (WORD)118;	ar << (WORD)111;	ar << (WORD)105;	ar << (WORD)59;
	ar << (WORD)53;		ar << (WORD)48;		ar << (WORD)43;		ar << (WORD)39;		ar << (WORD)34;
	ar << (WORD)30;		ar << (WORD)26;		ar << (WORD)22;		ar << (WORD)18;		ar << (WORD)15;
	ar << (WORD)11;		ar << (WORD)8;		ar << (WORD)5;		ar << (WORD)2;
	ar << (WORD)24;	// number of elements - Y
	ar << (WORD)557;	ar << (WORD)256;	ar << (WORD)208;	ar << (WORD)146;	ar << (WORD)137;
	ar << (WORD)129;	ar << (WORD)121;	ar << (WORD)114;	ar << (WORD)108;	ar << (WORD)102;
	ar << (WORD)56;		ar << (WORD)51;		ar << (WORD)46;		ar << (WORD)41;		ar << (WORD)37;
	ar << (WORD)33;		ar << (WORD)29;		ar << (WORD)25;		ar << (WORD)21;		ar << (WORD)18;
	ar << (WORD)14;		ar << (WORD)11;		ar << (WORD)8;		ar << (WORD)5;		ar << (WORD)2;
	ar << (WORD)25;	// number of elements - Z
	ar << (WORD)600;	ar << (WORD)259;	ar << (WORD)211;	ar << (WORD)149;	ar << (WORD)140;
	ar << (WORD)131;	ar << (WORD)124;	ar << (WORD)117;	ar << (WORD)111;	ar << (WORD)105;
	ar << (WORD)59;		ar << (WORD)54;		ar << (WORD)49;		ar << (WORD)44;		ar << (WORD)40;
	ar << (WORD)35;		ar << (WORD)31;		ar << (WORD)28;		ar << (WORD)24;		ar << (WORD)20;
	ar << (WORD)17;		ar << (WORD)14;		ar << (WORD)11;		ar << (WORD)8;		ar << (WORD)5;
	ar << (WORD)2;
}

void CDiveApp::WriteFTable3( CArchive& ar )
{
	ar << (BYTE)10;	// number of elements - A
	ar << Tab3( 10, 195 );	ar << Tab3( 9, 131 );	ar << Tab3( 7, 73 );	ar << Tab3( 6, 49 );
	ar << Tab3( 5, 35 );	ar << Tab3( 4, 26 );	ar << Tab3( 4, 21 );	ar << Tab3( 3, 17 );
	ar << Tab3( 3, 13 );	ar << Tab3( 3, 10 );	ar << Tab3( 3, 7 );
	ar << (BYTE)10;	// number of elements - B
	ar << Tab3( 19, 186 );	ar << Tab3( 16, 124 );	ar << Tab3( 13, 67 );	ar << Tab3( 11, 44 );
	ar << Tab3( 9, 31 );	ar << Tab3( 8, 22 );	ar << Tab3( 7, 18 );	ar << Tab3( 6, 14 );
	ar << Tab3( 6, 10 );	ar << Tab3( 5, 8 );		ar << Tab3( 5, 5 );             
	ar << (BYTE)10;	// number of elements - C
	ar << Tab3( 25, 180 );	ar << Tab3( 22, 118 );	ar << Tab3( 17, 63 );	ar << Tab3( 14, 41 );
	ar << Tab3( 12, 28 );	ar << Tab3( 10, 20 );	ar << Tab3( 9, 16 );	ar << Tab3( 8, 12 );
	ar << Tab3( 7, 9 );		ar << Tab3( 6, 7 );		ar << Tab3( 6, 4 );
	ar << (BYTE)10;	// number of elements - D   
	ar << Tab3( 29, 176 );	ar << Tab3( 25, 115 );	ar << Tab3( 19, 61 );	ar << Tab3( 16, 39 );
	ar << Tab3( 13, 27 );	ar << Tab3( 11, 19 );	ar << Tab3( 10, 15 );	ar << Tab3( 9, 11 );
	ar << Tab3( 8, 8 );	ar << Tab3( 7, 6 );	ar << Tab3( 7, 3 );
	ar << (BYTE)10;	// number of elements - E
	ar << Tab3( 32, 173 );	ar << Tab3( 27, 113 );	ar << Tab3( 21, 59 );	ar << Tab3( 17, 38 );
	ar << Tab3( 15, 25 );	ar << Tab3( 13, 17 );	ar << Tab3( 11, 14 );	ar << Tab3( 10, 10 );
	ar << Tab3( 9, 7 );	ar << Tab3( 8, 5 );	ar << Tab3( 8, 0 );
	ar << (BYTE)10;	// number of elements - F
	ar << Tab3( 36, 169 );	ar << Tab3( 31, 109 );	ar << Tab3( 24, 56 );	ar << Tab3( 19, 36 );
	ar << Tab3( 16, 24 );	ar << Tab3( 14, 16 );	ar << Tab3( 12, 13 );	ar << Tab3( 11, 9 );
	ar << Tab3( 10, 6 );	ar << Tab3( 9, 4 );	ar << Tab3( 8, 0 );
	ar << (BYTE)10;	// number of elements - G
	ar << Tab3( 40, 165 );	ar << Tab3( 34, 106 );	ar << Tab3( 26, 54 );	ar << Tab3( 21, 34 );
	ar << Tab3( 18, 22 );	ar << Tab3( 15, 15 );	ar << Tab3( 13, 12 );	ar << Tab3( 12, 8 );
	ar << Tab3( 11, 5 );	ar << Tab3( 10, 3 );	ar << Tab3( 9, 0 );
	ar << (BYTE)10;	// number of elements - H
	ar << Tab3( 44, 161 );	ar << Tab3( 37, 103 );	ar << Tab3( 28, 52 );	ar << Tab3( 23, 32 );
	ar << Tab3( 19, 21 );	ar << Tab3( 17, 13 );	ar << Tab3( 15, 10 );	ar << Tab3( 13, 7 );
	ar << Tab3( 12, 4 );	ar << Tab3( 11, 2 );	ar << Tab3( 10, 0 );
	ar << (BYTE)9;	// number of elements - I
	ar << Tab3( 48, 157 );	ar << Tab3( 40, 100 );	ar << Tab3( 31, 49 );	ar << Tab3( 25, 30 );
	ar << Tab3( 21, 19 );	ar << Tab3( 18, 12 );	ar << Tab3( 16, 9 );	ar << Tab3( 14, 6 );
	ar << Tab3( 13, 3 );	ar << Tab3( 12, 0 );
	ar << (BYTE)9;	// number of elements - J
	ar << Tab3( 52, 153 );	ar << Tab3( 44, 96 );	ar << Tab3( 33, 47 );	ar << Tab3( 27, 28 );
	ar << Tab3( 22, 18 );	ar << Tab3( 19, 11 );	ar << Tab3( 17, 8 );	ar << Tab3( 15, 5 );
	ar << Tab3( 14, 2 );	ar << Tab3( 12, 0 );
	ar << (BYTE)9;	// number of elements - K
	ar << Tab3( 57, 148 );	ar << Tab3( 48, 92 );	ar << Tab3( 36, 44 );	ar << Tab3( 29, 26 );
	ar << Tab3( 24, 16 );	ar << Tab3( 21, 9 );	ar << Tab3( 18, 7 );	ar << Tab3( 16, 4 );
	ar << Tab3( 14, 2 );	ar << Tab3( 13, 0 );
	ar << (BYTE)8;	// number of elements - L
	ar << Tab3( 62, 143 );	ar << Tab3( 51, 89 );	ar << Tab3( 38, 42 );	ar << Tab3( 31, 24 );
	ar << Tab3( 26, 14 );	ar << Tab3( 22, 8 );	ar << Tab3( 19, 6 );	ar << Tab3( 17, 3 );
	ar << Tab3( 15, 0 );
	ar << (BYTE)8;	// number of elements - M
	ar << Tab3( 67, 138 );	ar << Tab3( 55, 85 );	ar << Tab3( 41, 39 );	ar << Tab3( 33, 22 );
	ar << Tab3( 27, 13 );	ar << Tab3( 23, 7 );	ar << Tab3( 21, 4 );	ar << Tab3( 18, 2 );
	ar << Tab3( 16, 0 );
	ar << (BYTE)7;	// number of elements - N
	ar << Tab3( 73, 132 );	ar << Tab3( 60, 80 );	ar << Tab3( 44, 36 );	ar << Tab3( 35, 20 );
	ar << Tab3( 29, 11 );	ar << Tab3( 25, 5 );	ar << Tab3( 22, 3 );	ar << Tab3( 19, 0 );
	ar << (BYTE)7;	// number of elements - O
	ar << Tab3( 79, 126 );	ar << Tab3( 64, 76 );	ar << Tab3( 47, 33 );	ar << Tab3( 37, 18 );
	ar << Tab3( 31, 9 );	ar << Tab3( 26, 4 );	ar << Tab3( 23, 2 );	ar << Tab3( 20, 0 );
	ar << (BYTE)6;	// number of elements - P
	ar << Tab3( 85, 120 );	ar << Tab3( 69, 71 );	ar << Tab3( 50, 30 );	ar << Tab3( 39, 16 );
	ar << Tab3( 33, 7 );	ar << Tab3( 28, 2 );	ar << Tab3( 24, 0 );
	ar << (BYTE)6;	// number of elements - Q
	ar << Tab3( 92, 113 );	ar << Tab3( 74, 66 );	ar << Tab3( 53, 27 );	ar << Tab3( 42, 13 );
	ar << Tab3( 34, 6 );	ar << Tab3( 29, 0 );	ar << Tab3( 25, 0 );
	ar << (BYTE)5;	// number of elements - R
	ar << Tab3( 100, 105 );	ar << Tab3( 79, 61 );	ar << Tab3( 57, 23 );	ar << Tab3( 44, 11 );
	ar << Tab3( 36, 4 );	ar << Tab3( 30, 0 );
	ar << (BYTE)4;	// number of elements - S
	ar << Tab3( 108, 97 );	ar << Tab3( 85, 55 );	ar << Tab3( 60, 20 );	ar << Tab3( 47, 8 );
	ar << Tab3( 38, 2 );
	ar << (BYTE)4;	// number of elements - T
	ar << Tab3( 117, 88 );	ar << Tab3( 91, 49 );	ar << Tab3( 63, 17 );	ar << Tab3( 49, 6 );
	ar << Tab3( 40, 0 );
	ar << (BYTE)3;	// number of elements - U
	ar << Tab3( 127, 78 );	ar << Tab3( 97, 43 );	ar << Tab3( 67, 13 );	ar << Tab3( 52, 3 );
	ar << (BYTE)3;	// number of elements - V
	ar << Tab3( 139, 66 );	ar << Tab3( 104, 36 );	ar << Tab3( 71, 9 );	ar << Tab3( 54, 1 );
	ar << (BYTE)3;	// number of elements - W
	ar << Tab3( 152, 53 );	ar << Tab3( 111, 29 );	ar << Tab3( 75, 5 );	ar << Tab3( 55, 0 );
	ar << (BYTE)2;	// number of elements - X
	ar << Tab3( 168, 37 );	ar << Tab3( 120, 20 );	ar << Tab3( 80, 0 );
	ar << (BYTE)1;	// number of elements - Y
	ar << Tab3( 188, 17 );	ar << Tab3( 129, 11 );
	ar << (BYTE)1;	// number of elements - Z
	ar << Tab3( 205, 0 );	ar << Tab3( 140, 0 );
}