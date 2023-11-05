
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)
#include <ctl3d.h>

class CDiveApp : public CWinApp
{
public:
	CDiveApp( );
	
	void	CreateTable1();
	void	CreateTable2();
	void	CreateTable2Part2( CArchive& ar2 );	// for optimisation purposes
	void	CreateTable3();
	void	CreateTable3Part2( CArchive& ar3 );	// for optimisation purposes
	
	virtual BOOL InitInstance( );
	virtual int ExitInstance( );
};

CDiveApp::CDiveApp()
{
	m_pszAppName = "Logic Software";
}

CDiveApp NEAR theApp;

BOOL CDiveApp::InitInstance()
{
	Ctl3dRegister( AfxGetInstanceHandle() );
	Ctl3dAutoSubclass( AfxGetInstanceHandle() );

	CreateTable1();
	CreateTable2();
	CreateTable3();
	
	AfxMessageBox( "Data files created" );
	return TRUE;
	
}

int CDiveApp::ExitInstance()
{
	Ctl3dUnregister( AfxGetInstanceHandle() );
	return CWinApp::ExitInstance();
}

void CDiveApp::CreateTable1()
{
	CFile table1File;
	CFileException fe;
	CDocument tmpDoc;
	
	if( !table1File.Open( "TABLE1.DAT",
			CFile::modeCreate|CFile::modeWrite, &fe ) )
	{
		tmpDoc.ReportSaveLoadException( "TABLE1.DAT", &fe, TRUE,
												AFX_IDP_INVALID_FILENAME );
		return;
	}
	
	CArchive ar1( &table1File, CArchive::store );
	
	// Depth - 10m   
	ar1 << (WORD)25;	// number of elements
	ar1 << (WORD)10;	ar1 << (WORD)20;	ar1 << (WORD)26;	ar1 << (WORD)30;	ar1 << (WORD)34;
	ar1 << (WORD)37;	ar1 << (WORD)41;	ar1 << (WORD)45;	ar1 << (WORD)50;	ar1 << (WORD)54;
	ar1 << (WORD)59;	ar1 << (WORD)64;	ar1 << (WORD)70;	ar1 << (WORD)75;	ar1 << (WORD)82;
	ar1 << (WORD)88;	ar1 << (WORD)95;	ar1 << (WORD)104;	ar1 << (WORD)112;	ar1 << (WORD)122;
	ar1 << (WORD)133;	ar1 << (WORD)145;	ar1 << (WORD)160;	ar1 << (WORD)178;	ar1 << (WORD)199;
	ar1 << (WORD)219;
	ar1 << (WORD)160;	// safety stop requied
    
	// Depth - 12m   
	ar1 << (WORD)25;	// number of elements
	ar1 << (WORD)9;		ar1 << (WORD)17;	ar1 << (WORD)23;	ar1 << (WORD)26;	ar1 << (WORD)29;
	ar1 << (WORD)32;	ar1 << (WORD)35;	ar1 << (WORD)38;	ar1 << (WORD)42;	ar1 << (WORD)45;
	ar1 << (WORD)49;	ar1 << (WORD)53;	ar1 << (WORD)57;	ar1 << (WORD)62;	ar1 << (WORD)66;
	ar1 << (WORD)71;	ar1 << (WORD)76;	ar1 << (WORD)82;	ar1 << (WORD)88;	ar1 << (WORD)94;
	ar1 << (WORD)101;	ar1 << (WORD)108;	ar1 << (WORD)116;	ar1 << (WORD)125;	ar1 << (WORD)134;
	ar1 << (WORD)147;
	ar1 << (WORD)116;	// safety stop requied
    
	// Depth - 14m
	ar1 << (WORD)24;	// number of elements
    ar1 << (WORD)8;		ar1 << (WORD)15;	ar1 << (WORD)19;	ar1 << (WORD)22;	ar1 << (WORD)24;
    ar1 << (WORD)27;	ar1 << (WORD)29;	ar1 << (WORD)32;	ar1 << (WORD)35;	ar1 << (WORD)37;
    ar1 << (WORD)40;	ar1 << (WORD)43;	ar1 << (WORD)47;	ar1 << (WORD)50;	ar1 << (WORD)53;
    ar1 << (WORD)57;	ar1 << (WORD)61;	ar1 << (WORD)64;	ar1 << (WORD)68;	ar1 << (WORD)73;
    ar1 << (WORD)77;	ar1 << (WORD)82;	ar1 << (WORD)87;	ar1 << (WORD)92;	ar1 << (WORD)98;
	ar1 << (WORD)82;	// safety stop requied
	
	// Depth - 16m
	ar1 << (WORD)23;	// number of elements
	ar1 << (WORD)7;		ar1 << (WORD)13;	ar1 << (WORD)17;	ar1 << (WORD)19;	ar1 << (WORD)21;
	ar1 << (WORD)23;	ar1 << (WORD)25;	ar1 << (WORD)27;	ar1 << (WORD)29;	ar1 << (WORD)32;
	ar1 << (WORD)34;	ar1 << (WORD)37;	ar1 << (WORD)39;	ar1 << (WORD)42;	ar1 << (WORD)45;
	ar1 << (WORD)48;	ar1 << (WORD)50;	ar1 << (WORD)53;	ar1 << (WORD)56;	ar1 << (WORD)60;
	ar1 << (WORD)63;	ar1 << (WORD)67;	ar1 << (WORD)70;	ar1 << (WORD)72;
	ar1 << (WORD)63;	// safety stop requied
	
	// Depth - 18m
	ar1 << (WORD)22;	// number of elements
    ar1 << (WORD)6;		ar1 << (WORD)11;	ar1 << (WORD)15;	ar1 << (WORD)16;	ar1 << (WORD)18;
    ar1 << (WORD)20;	ar1 << (WORD)22;	ar1 << (WORD)24;	ar1 << (WORD)26;	ar1 << (WORD)28;
    ar1 << (WORD)30;	ar1 << (WORD)32;	ar1 << (WORD)34;	ar1 << (WORD)36;	ar1 << (WORD)39;
    ar1 << (WORD)41;	ar1 << (WORD)43;	ar1 << (WORD)46;	ar1 << (WORD)48;	ar1 << (WORD)51;
    ar1 << (WORD)53;	ar1 << (WORD)55;	ar1 << (WORD)56;
    ar1 << (WORD)51;	// safety stop requied
    	
	// Depth - 20m
	ar1 << (WORD)20;	// number of elements
	ar1 << (WORD)6;		ar1 << (WORD)10;	ar1 << (WORD)13;	ar1 << (WORD)15;	ar1 << (WORD)16;
	ar1 << (WORD)18;	ar1 << (WORD)20;	ar1 << (WORD)21;	ar1 << (WORD)23;	ar1 << (WORD)25;
	ar1 << (WORD)26;	ar1 << (WORD)28;	ar1 << (WORD)30;	ar1 << (WORD)32;	ar1 << (WORD)34;
	ar1 << (WORD)36;	ar1 << (WORD)38;	ar1 << (WORD)40;	ar1 << (WORD)42;	ar1 << (WORD)44;
	ar1 << (WORD)45;
	ar1 << (WORD)40;	// safety stop requied

	// Depth - 22m
	ar1 << (WORD)18;	// number of elements
	ar1 << (WORD)5;		ar1 << (WORD)9;		ar1 << (WORD)12;	ar1 << (WORD)13;	ar1 << (WORD)15;
	ar1 << (WORD)16;	ar1 << (WORD)18;	ar1 << (WORD)19;	ar1 << (WORD)21;	ar1 << (WORD)22;
	ar1 << (WORD)24;	ar1 << (WORD)25;	ar1 << (WORD)27;	ar1 << (WORD)29;	ar1 << (WORD)30;
	ar1 << (WORD)32;	ar1 << (WORD)34;	ar1 << (WORD)36; 	ar1 << (WORD)37;
	ar1 << (WORD)32;	// safety stop requied	

	// Depth - 25m
	ar1 << (WORD)16;	// number of elements
   	ar1 << (WORD)4;		ar1 << (WORD)8;		ar1 << (WORD)10;	ar1 << (WORD)11;	ar1 << (WORD)13;
   	ar1 << (WORD)14;	ar1 << (WORD)15;	ar1 << (WORD)17;	ar1 << (WORD)18;	ar1 << (WORD)19;
   	ar1 << (WORD)21;	ar1 << (WORD)22;	ar1 << (WORD)23;	ar1 << (WORD)25;	ar1 << (WORD)26;
   	ar1 << (WORD)28;	ar1 << (WORD)29;
	ar1 << (WORD)25;	// safety stop requied   	
                                                                                                    
	// Depth - 30m
	ar1 << (WORD)13;	// number of elements
	ar1 << (WORD)3;		ar1 << (WORD)6;		ar1 << (WORD)8;		ar1 << (WORD)9;		ar1 << (WORD)10;
	ar1 << (WORD)11;	ar1 << (WORD)12;	ar1 << (WORD)13;	ar1 << (WORD)14;	ar1 << (WORD)15;
	ar1 << (WORD)16;	ar1 << (WORD)17;    ar1 << (WORD)19;	ar1 << (WORD)20;
	ar1 << (WORD)1;	// safety stop requied

	// Depth - 35m
	ar1 << (WORD)10;	// number of elements
	ar1 << (WORD)3;		ar1 << (WORD)5;		ar1 << (WORD)7;		ar1 << (WORD)8;		ar1 << (WORD)10000;
	ar1 << (WORD)9;		ar1 << (WORD)10;	ar1 << (WORD)11;	ar1 << (WORD)12;	ar1 << (WORD)13;
	ar1 << (WORD)14;
	ar1 << (WORD)1;	// safety stop requied

	// Depth - 40m
	ar1 << (WORD)6;	// number of elements
	ar1 << (WORD)10000;	ar1 << (WORD)5;		ar1 << (WORD)6;		ar1 << (WORD)10000;	ar1 << (WORD)7;
	ar1 << (WORD)8;		ar1 << (WORD)9;
	ar1 << (WORD)1;	// safety stop requied

	// Depth - 42m
	ar1 << (WORD)5;	// number of elements
	ar1 << (WORD)10000;	ar1 << (WORD)4;		ar1 << (WORD)10000;	ar1 << (WORD)6;		ar1 << (WORD)7;
	ar1 << (WORD)8;
	ar1 << (WORD)1;	// safety stop requied

	ar1.Close();
	table1File.Close();
}

void CDiveApp::CreateTable2()
{
	CFile table2File;
	CFileException fe;
	CDocument tmpDoc;
	
	if( !table2File.Open( "TABLE2.DAT",
			CFile::modeCreate|CFile::modeWrite, &fe ) )
	{
		tmpDoc.ReportSaveLoadException( "TABLE2.DAT", &fe, TRUE,
												AFX_IDP_INVALID_FILENAME );
		return;
	}
	
	CArchive ar2( &table2File, CArchive::store );
	
	// A
	ar2 << (WORD)0;	// number of elements
	ar2 << (WORD)300;
		
	// B
	ar2 << (WORD)1;	// number of elements
	ar2 << (WORD)348;	ar2 << (WORD)47;
	
	// C
	ar2 << (WORD)2;	// number of elements
	ar2 << (WORD)410;	ar2 << (WORD)109;	ar2 << (WORD)21;

	// D
	ar2 << (WORD)3;	// number of elements
	ar2 << (WORD)419;	ar2 << (WORD)118;	ar2 << (WORD)30;	ar2 << (WORD)8;

	// E
	ar2 << (WORD)4;	// number of elements
	ar2 << (WORD)428;	ar2 << (WORD)127;	ar2 << (WORD)38;	ar2 << (WORD)16;	ar2 << (WORD)7;

	// F
	ar2 << (WORD)5;	// number of elements
	ar2 << (WORD)435;	ar2 << (WORD)134;	ar2 << (WORD)46;	ar2 << (WORD)24;	ar2 << (WORD)15;
	ar2 << (WORD)7;
		
	// G
	ar2 << (WORD)6;	// number of elements
	ar2 << (WORD)442;	ar2 << (WORD)141;	ar2 << (WORD)53;	ar2 << (WORD)31;	ar2 << (WORD)22;
	ar2 << (WORD)13;	ar2 << (WORD)6;
	
	// H
	ar2 << (WORD)7;	// number of elements
	ar2 << (WORD)448;	ar2 << (WORD)147;	ar2 << (WORD)59;	ar2 << (WORD)37;	ar2 << (WORD)28;
	ar2 << (WORD)20;	ar2 << (WORD)12;	ar2 << (WORD)5;
	
	// I
	ar2 << (WORD)8;	// number of elements
	ar2 << (WORD)454;	ar2 << (WORD)153;	ar2 << (WORD)105;	ar2 << (WORD)43;	ar2 << (WORD)34;
	ar2 << (WORD)26;	ar2 << (WORD)18;	ar2 << (WORD)11;	ar2 << (WORD)5;
	
	// J
	ar2 << (WORD)9;	// number of elements
	ar2 << (WORD)500;	ar2 << (WORD)159;	ar2 << (WORD)111;	ar2 << (WORD)49;	ar2 << (WORD)40;
	ar2 << (WORD)31;	ar2 << (WORD)24;	ar2 << (WORD)17;	ar2 << (WORD)11;	ar2 << (WORD)5;
	
	// K
	ar2 << (WORD)10;	// number of elements
	ar2 << (WORD)505;	ar2 << (WORD)204;	ar2 << (WORD)116;	ar2 << (WORD)54;	ar2 << (WORD)45;
	ar2 << (WORD)37;	ar2 << (WORD)29;	ar2 << (WORD)22;	ar2 << (WORD)16;	ar2 << (WORD)10;
	ar2 << (WORD)4;
	
	// L
	ar2 << (WORD)11;	// number of elements
	ar2 << (WORD)510;	ar2 << (WORD)209;	ar2 << (WORD)121;	ar2 << (WORD)59;	ar2 << (WORD)50;
	ar2 << (WORD)42;	ar2 << (WORD)34;	ar2 << (WORD)27;	ar2 << (WORD)21;	ar2 << (WORD)15;
	ar2 << (WORD)9;		ar2 << (WORD)4;
	
	// M
	ar2 << (WORD)12;	// number of elements
	ar2 << (WORD)515;	ar2 << (WORD)214;	ar2 << (WORD)125;	ar2 << (WORD)104;	ar2 << (WORD)55;
	ar2 << (WORD)46;	ar2 << (WORD)39;	ar2 << (WORD)32;	ar2 << (WORD)25;	ar2 << (WORD)19;
	ar2 << (WORD)14;	ar2 << (WORD)9;		ar2 << (WORD)4;

	CreateTable2Part2( ar2 );
	
	ar2.Close();
	table2File.Close();
}

void CDiveApp::CreateTable2Part2( CArchive& ar2 )
{
	// N
	ar2 << (WORD)13;	// number of elements
	ar2 << (WORD)519;	ar2 << (WORD)218;	ar2 << (WORD)130;	ar2 << (WORD)108;	ar2 << (WORD)59;
	ar2 << (WORD)51;	ar2 << (WORD)43;	ar2 << (WORD)36;	ar2 << (WORD)30;	ar2 << (WORD)24;
	ar2 << (WORD)18;	ar2 << (WORD)13;	ar2 << (WORD)8;		ar2 << (WORD)3;
	
	// O
	ar2 << (WORD)14;	// number of elements
	ar2 << (WORD)524;	ar2 << (WORD)223;	ar2 << (WORD)134;	ar2 << (WORD)112;	ar2 << (WORD)103;
	ar2 << (WORD)55;	ar2 << (WORD)47;	ar2 << (WORD)41;	ar2 << (WORD)34;	ar2 << (WORD)28;
	ar2 << (WORD)23;	ar2 << (WORD)17;	ar2 << (WORD)12;	ar2 << (WORD)8;		ar2 << (WORD)3;
	
	// P
	ar2 << (WORD)15;	// number of elements
	ar2 << (WORD)528;	ar2 << (WORD)227;	ar2 << (WORD)138;	ar2 << (WORD)116;	ar2 << (WORD)107;
	ar2 << (WORD)59;	ar2 << (WORD)51;	ar2 << (WORD)45;	ar2 << (WORD)38;	ar2 << (WORD)32;
	ar2 << (WORD)27;	ar2 << (WORD)21;	ar2 << (WORD)16;	ar2 << (WORD)12;	ar2 << (WORD)7;
	ar2 << (WORD)3;
	
	// Q
	ar2 << (WORD)16;	// number of elements
	ar2 << (WORD)531;	ar2 << (WORD)230;	ar2 << (WORD)142;	ar2 << (WORD)120;	ar2 << (WORD)111;
	ar2 << (WORD)103;	ar2 << (WORD)55;	ar2 << (WORD)48;	ar2 << (WORD)42;	ar2 << (WORD)36;
	ar2 << (WORD)30;	ar2 << (WORD)25;	ar2 << (WORD)20;	ar2 << (WORD)16;	ar2 << (WORD)11;
	ar2 << (WORD)7;		ar2 << (WORD)3;
    
	// R
	ar2 << (WORD)17;	// number of elements
	ar2 << (WORD)535;	ar2 << (WORD)234;	ar2 << (WORD)146;	ar2 << (WORD)124;	ar2 << (WORD)115;
	ar2 << (WORD)107;	ar2 << (WORD)59;	ar2 << (WORD)52;	ar2 << (WORD)46;	ar2 << (WORD)40;
	ar2 << (WORD)34;	ar2 << (WORD)29;	ar2 << (WORD)24;	ar2 << (WORD)19;	ar2 << (WORD)15;
	ar2 << (WORD)11;	ar2 << (WORD)7;		ar2 << (WORD)3;
    
	// S
	ar2 << (WORD)18;	// number of elements
	ar2 << (WORD)539;	ar2 << (WORD)238;	ar2 << (WORD)149;	ar2 << (WORD)127;	ar2 << (WORD)118;
	ar2 << (WORD)110;	ar2 << (WORD)103;	ar2 << (WORD)56;	ar2 << (WORD)49;	ar2 << (WORD)43;
	ar2 << (WORD)38;	ar2 << (WORD)32;	ar2 << (WORD)27;	ar2 << (WORD)23;	ar2 << (WORD)18;
	ar2 << (WORD)14;	ar2 << (WORD)10;	ar2 << (WORD)6;		ar2 << (WORD)3;
	
	// T
	ar2 << (WORD)19;	// number of elements
	ar2 << (WORD)542;	ar2 << (WORD)241;	ar2 << (WORD)153;	ar2 << (WORD)131;	ar2 << (WORD)122;
	ar2 << (WORD)113;	ar2 << (WORD)106;	ar2 << (WORD)59;	ar2 << (WORD)53;	ar2 << (WORD)47;
	ar2 << (WORD)41;	ar2 << (WORD)36;	ar2 << (WORD)31;	ar2 << (WORD)26;	ar2 << (WORD)22;
	ar2 << (WORD)17;	ar2 << (WORD)13;	ar2 << (WORD)10;	ar2 << (WORD)6;		ar2 << (WORD)2;
	
	// U
	ar2 << (WORD)20;	// number of elements
	ar2 << (WORD)545;	ar2 << (WORD)244;	ar2 << (WORD)156;	ar2 << (WORD)134;	ar2 << (WORD)125;
	ar2 << (WORD)117;	ar2 << (WORD)109;	ar2 << (WORD)102;	ar2 << (WORD)56;	ar2 << (WORD)50;
	ar2 << (WORD)44;	ar2 << (WORD)39;	ar2 << (WORD)34;	ar2 << (WORD)29;	ar2 << (WORD)25;
	ar2 << (WORD)21;	ar2 << (WORD)17;	ar2 << (WORD)13;	ar2 << (WORD)9;		ar2 << (WORD)6;
	ar2 << (WORD)2;
    
	// V
	ar2 << (WORD)21;	// number of elements
	ar2 << (WORD)548;	ar2 << (WORD)247;	ar2 << (WORD)159;	ar2 << (WORD)137;	ar2 << (WORD)128;
	ar2 << (WORD)120;	ar2 << (WORD)112;	ar2 << (WORD)105;	ar2 << (WORD)59;	ar2 << (WORD)53;
	ar2 << (WORD)47;	ar2 << (WORD)42;	ar2 << (WORD)37;	ar2 << (WORD)33;	ar2 << (WORD)28;
	ar2 << (WORD)24;	ar2 << (WORD)20;	ar2 << (WORD)16;	ar2 << (WORD)12;	ar2 << (WORD)9;
	ar2 << (WORD)5;		ar2 << (WORD)2;
        
	// W
	ar2 << (WORD)22;	// number of elements
	ar2 << (WORD)551;	ar2 << (WORD)250;	ar2 << (WORD)202;	ar2 << (WORD)140;	ar2 << (WORD)131;
	ar2 << (WORD)123;	ar2 << (WORD)115;	ar2 << (WORD)108;	ar2 << (WORD)102;	ar2 << (WORD)56;
	ar2 << (WORD)50;	ar2 << (WORD)45;	ar2 << (WORD)40;	ar2 << (WORD)36;	ar2 << (WORD)31;
	ar2 << (WORD)27;	ar2 << (WORD)23;	ar2 << (WORD)19;	ar2 << (WORD)15;	ar2 << (WORD)12;
	ar2 << (WORD)8;		ar2 << (WORD)5;		ar2 << (WORD)2;
        
	// X
	ar2 << (WORD)23;	// number of elements
	ar2 << (WORD)554;	ar2 << (WORD)253;	ar2 << (WORD)205;	ar2 << (WORD)143;	ar2 << (WORD)134;
	ar2 << (WORD)126;	ar2 << (WORD)118;	ar2 << (WORD)111;	ar2 << (WORD)105;	ar2 << (WORD)59;
	ar2 << (WORD)53;	ar2 << (WORD)48;	ar2 << (WORD)43;	ar2 << (WORD)39;	ar2 << (WORD)34;
	ar2 << (WORD)30;	ar2 << (WORD)26;	ar2 << (WORD)22;	ar2 << (WORD)18;	ar2 << (WORD)15;
	ar2 << (WORD)11;	ar2 << (WORD)8;		ar2 << (WORD)5;		ar2 << (WORD)2;
        
	// Y                                
	ar2 << (WORD)24;	// number of elements
	ar2 << (WORD)557;	ar2 << (WORD)256;	ar2 << (WORD)208;	ar2 << (WORD)146;	ar2 << (WORD)137;
	ar2 << (WORD)129;	ar2 << (WORD)121;	ar2 << (WORD)114;	ar2 << (WORD)108;	ar2 << (WORD)102;
	ar2 << (WORD)56;	ar2 << (WORD)51;	ar2 << (WORD)46;	ar2 << (WORD)41;	ar2 << (WORD)37;
	ar2 << (WORD)33;	ar2 << (WORD)29;	ar2 << (WORD)25;	ar2 << (WORD)21;	ar2 << (WORD)18;
	ar2 << (WORD)14;	ar2 << (WORD)11;	ar2 << (WORD)8;		ar2 << (WORD)5;		ar2 << (WORD)2;
	    
	// Z
	ar2 << (WORD)25;	// number of elements
	ar2 << (WORD)600;	ar2 << (WORD)259;	ar2 << (WORD)211;	ar2 << (WORD)149;	ar2 << (WORD)140;
	ar2 << (WORD)131;	ar2 << (WORD)124;	ar2 << (WORD)117;	ar2 << (WORD)111;	ar2 << (WORD)105;
	ar2 << (WORD)59;	ar2 << (WORD)54;	ar2 << (WORD)49;	ar2 << (WORD)44;	ar2 << (WORD)40;
	ar2 << (WORD)35;	ar2 << (WORD)31;	ar2 << (WORD)28;	ar2 << (WORD)24;	ar2 << (WORD)20;
	ar2 << (WORD)17;	ar2 << (WORD)14;	ar2 << (WORD)11;	ar2 << (WORD)8;		ar2 << (WORD)5;
	ar2 << (WORD)2;
}

void CDiveApp::CreateTable3()
{
	CFile table3File;
	CFileException fe;
	CDocument tmpDoc;

	if( !table3File.Open( "TABLE3.DAT",
			CFile::modeCreate|CFile::modeWrite, &fe ) )
	{
		tmpDoc.ReportSaveLoadException( "TABLE3.DAT", &fe, TRUE,
												AFX_IDP_INVALID_FILENAME );
		return;
	}
	
	CArchive ar3( &table3File, CArchive::store );
	
    // This table is store as a series of points
    
	// A
	ar3 << (WORD)10;	// number of elements
	ar3 << (WORD)10;	ar3 << (WORD)209;	ar3 << (WORD)9;		ar3 << (WORD)138;
	ar3 << (WORD)8;		ar3 << (WORD)90;	ar3 << (WORD)7;		ar3 << (WORD)65;
	ar3 << (WORD)6;		ar3 << (WORD)50;	ar3 << (WORD)6;		ar3 << (WORD)39;
	ar3 << (WORD)5;		ar3 << (WORD)32;	ar3 << (WORD)4;		ar3 << (WORD)25;
	ar3 << (WORD)3;		ar3 << (WORD)17;	ar3 << (WORD)3;		ar3 << (WORD)11;	
	ar3 << (WORD)2;		ar3 << (WORD)7;
	
	// B
	ar3 << (WORD)10;	// number of elements
	ar3 << (WORD)20;	ar3 << (WORD)199;	ar3 << (WORD)17;	ar3 << (WORD)130;
	ar3 << (WORD)15;	ar3 << (WORD)83;	ar3 << (WORD)13;	ar3 << (WORD)59;
	ar3 << (WORD)11;	ar3 << (WORD)45;	ar3 << (WORD)10;	ar3 << (WORD)35;
	ar3 << (WORD)9;		ar3 << (WORD)28;	ar3 << (WORD)8;		ar3 << (WORD)21;
	ar3 << (WORD)6;		ar3 << (WORD)14;	ar3 << (WORD)5;		ar3 << (WORD)9;
	ar3 << (WORD)5;		ar3 << (WORD)4;

	// C
	ar3 << (WORD)10;	// number of elements
	ar3 << (WORD)26;	ar3 << (WORD)193;	ar3 << (WORD)23;	ar3 << (WORD)124;
	ar3 << (WORD)19;	ar3 << (WORD)79;	ar3 << (WORD)17;	ar3 << (WORD)55;
	ar3 << (WORD)15;	ar3 << (WORD)41;	ar3 << (WORD)13;	ar3 << (WORD)32;
	ar3 << (WORD)12;	ar3 << (WORD)25;	ar3 << (WORD)10;	ar3 << (WORD)19;
	ar3 << (WORD)8;		ar3 << (WORD)12;	ar3 << (WORD)7;		ar3 << (WORD)7;
	ar3 << (WORD)6;		ar3 << (WORD)0;

	// D
	ar3 << (WORD)10;	// number of elements
	ar3 << (WORD)30;	ar3 << (WORD)189;	ar3 << (WORD)26;	ar3 << (WORD)121;
	ar3 << (WORD)22;	ar3 << (WORD)76;	ar3 << (WORD)19;	ar3 << (WORD)53;
	ar3 << (WORD)16;	ar3 << (WORD)40;	ar3 << (WORD)15;	ar3 << (WORD)30;
	ar3 << (WORD)13;	ar3 << (WORD)24;	ar3 << (WORD)11;	ar3 << (WORD)18;
	ar3 << (WORD)9;		ar3 << (WORD)11;	ar3 << (WORD)8;		ar3 << (WORD)6;
	ar3 << (WORD)7;		ar3 << (WORD)0;

	// E
	ar3 << (WORD)10;	// number of elements
	ar3 << (WORD)34;	ar3 << (WORD)185;	ar3 << (WORD)29;	ar3 << (WORD)118;
	ar3 << (WORD)24;	ar3 << (WORD)74;	ar3 << (WORD)21;	ar3 << (WORD)51;
	ar3 << (WORD)18;	ar3 << (WORD)38;	ar3 << (WORD)16;	ar3 << (WORD)29;
	ar3 << (WORD)15;	ar3 << (WORD)22;	ar3 << (WORD)13;	ar3 << (WORD)16;
	ar3 << (WORD)10;	ar3 << (WORD)10;	ar3 << (WORD)9;		ar3 << (WORD)5;
	ar3 << (WORD)7;		ar3 << (WORD)0;

	// F
	ar3 << (WORD)10;	// number of elements
	ar3 << (WORD)37;	ar3 << (WORD)182;	ar3 << (WORD)32;	ar3 << (WORD)115;
	ar3 << (WORD)27;	ar3 << (WORD)71;	ar3 << (WORD)23;	ar3 << (WORD)49;
	ar3 << (WORD)20;	ar3 << (WORD)36;	ar3 << (WORD)18;	ar3 << (WORD)27;
	ar3 << (WORD)16;	ar3 << (WORD)21;	ar3 << (WORD)14;	ar3 << (WORD)15;
	ar3 << (WORD)11;	ar3 << (WORD)9;		ar3 << (WORD)9;		ar3 << (WORD)5;
	ar3 << (WORD)8;		ar3 << (WORD)0;

	// G
	ar3 << (WORD)10;	// number of elements
	ar3 << (WORD)41;	ar3 << (WORD)178;	ar3 << (WORD)35;	ar3 << (WORD)112;
	ar3 << (WORD)29;	ar3 << (WORD)69;	ar3 << (WORD)25;	ar3 << (WORD)47;
	ar3 << (WORD)22;	ar3 << (WORD)34;	ar3 << (WORD)20;	ar3 << (WORD)25;
	ar3 << (WORD)18;	ar3 << (WORD)19;	ar3 << (WORD)15;	ar3 << (WORD)14;
	ar3 << (WORD)12;	ar3 << (WORD)8;		ar3 << (WORD)10;	ar3 << (WORD)4;
	ar3 << (WORD)9;		ar3 << (WORD)0;

	// H
	ar3 << (WORD)9;	// number of elements
	ar3 << (WORD)45;	ar3 << (WORD)174;	ar3 << (WORD)38;	ar3 << (WORD)109;
	ar3 << (WORD)32;	ar3 << (WORD)66;	ar3 << (WORD)27;	ar3 << (WORD)45;
	ar3 << (WORD)24;	ar3 << (WORD)32;	ar3 << (WORD)21;	ar3 << (WORD)24;
	ar3 << (WORD)19;	ar3 << (WORD)18;	ar3 << (WORD)17;	ar3 << (WORD)12;
	ar3 << (WORD)13;	ar3 << (WORD)7;		ar3 << (WORD)11;	ar3 << (WORD)3;

	// I
	ar3 << (WORD)9;	// number of elements
	ar3 << (WORD)50;	ar3 << (WORD)169;	ar3 << (WORD)42;	ar3 << (WORD)105;
	ar3 << (WORD)35;	ar3 << (WORD)63;	ar3 << (WORD)29;	ar3 << (WORD)43;
	ar3 << (WORD)26;	ar3 << (WORD)30;	ar3 << (WORD)23;	ar3 << (WORD)22;
	ar3 << (WORD)21;	ar3 << (WORD)16;	ar3 << (WORD)18;	ar3 << (WORD)11;
	ar3 << (WORD)14;	ar3 << (WORD)6;		ar3 << (WORD)12;	ar3 << (WORD)0;

	// J
	ar3 << (WORD)9;	// number of elements
	ar3 << (WORD)54;	ar3 << (WORD)165;	ar3 << (WORD)45;	ar3 << (WORD)102;
	ar3 << (WORD)37;	ar3 << (WORD)61;	ar3 << (WORD)32;	ar3 << (WORD)40;
	ar3 << (WORD)28;	ar3 << (WORD)28;	ar3 << (WORD)25;	ar3 << (WORD)20;
	ar3 << (WORD)22;	ar3 << (WORD)15;	ar3 << (WORD)19;	ar3 << (WORD)10;
	ar3 << (WORD)15;	ar3 << (WORD)5;		ar3 << (WORD)13;	ar3 << (WORD)0;

	CreateTable3Part2( ar3 );
		
	ar3.Close();
	table3File.Close();
}


void CDiveApp::CreateTable3Part2( CArchive& ar3 )
{
	// K
	ar3 << (WORD)9;	// number of elements
	ar3 << (WORD)59;	ar3 << (WORD)160;	ar3 << (WORD)49;	ar3 << (WORD)98;
	ar3 << (WORD)40;	ar3 << (WORD)58;	ar3 << (WORD)34;	ar3 << (WORD)38;
	ar3 << (WORD)30;	ar3 << (WORD)26;	ar3 << (WORD)26;	ar3 << (WORD)19;
	ar3 << (WORD)24;	ar3 << (WORD)13;	ar3 << (WORD)21;	ar3 << (WORD)8;
	ar3 << (WORD)16;	ar3 << (WORD)4;		ar3 << (WORD)14;	ar3 << (WORD)0;

	// L
	ar3 << (WORD)8;	// number of elements
	ar3 << (WORD)64;	ar3 << (WORD)155;	ar3 << (WORD)53;	ar3 << (WORD)94;
	ar3 << (WORD)43;	ar3 << (WORD)55;	ar3 << (WORD)37;	ar3 << (WORD)35;
	ar3 << (WORD)32;	ar3 << (WORD)24;	ar3 << (WORD)28;	ar3 << (WORD)17;
	ar3 << (WORD)25;	ar3 << (WORD)12;	ar3 << (WORD)22;	ar3 << (WORD)7;
	ar3 << (WORD)17;	ar3 << (WORD)3;

	// M
	ar3 << (WORD)8;	// number of elements
	ar3 << (WORD)70;	ar3 << (WORD)149;	ar3 << (WORD)57;	ar3 << (WORD)90;
	ar3 << (WORD)47;	ar3 << (WORD)51;	ar3 << (WORD)39;	ar3 << (WORD)33;
	ar3 << (WORD)34;	ar3 << (WORD)22;	ar3 << (WORD)30;	ar3 << (WORD)15;
	ar3 << (WORD)27;	ar3 << (WORD)10;	ar3 << (WORD)23;	ar3 << (WORD)6;
	ar3 << (WORD)19;	ar3 << (WORD)0;

	// N
	ar3 << (WORD)8;	// number of elements
	ar3 << (WORD)75;	ar3 << (WORD)144;	ar3 << (WORD)62;	ar3 << (WORD)85;
	ar3 << (WORD)50;	ar3 << (WORD)48;	ar3 << (WORD)42;	ar3 << (WORD)30;
	ar3 << (WORD)36;	ar3 << (WORD)20;	ar3 << (WORD)32;	ar3 << (WORD)13;
	ar3 << (WORD)29;	ar3 << (WORD)8;		ar3 << (WORD)25;	ar3 << (WORD)4;
	ar3 << (WORD)20;	ar3 << (WORD)0;

	// O
	ar3 << (WORD)7;	// number of elements
	ar3 << (WORD)82;	ar3 << (WORD)137;	ar3 << (WORD)66;	ar3 << (WORD)81;
	ar3 << (WORD)53;	ar3 << (WORD)45;	ar3 << (WORD)45;	ar3 << (WORD)27;
	ar3 << (WORD)39;	ar3 << (WORD)17;	ar3 << (WORD)34;	ar3 << (WORD)11;
	ar3 << (WORD)30;	ar3 << (WORD)7;		ar3 << (WORD)26;	ar3 << (WORD)3;

	// P
	ar3 << (WORD)7;	// number of elements
	ar3 << (WORD)88;	ar3 << (WORD)131;	ar3 << (WORD)71;	ar3 << (WORD)76;
	ar3 << (WORD)57;	ar3 << (WORD)41;	ar3 << (WORD)48;	ar3 << (WORD)24;
	ar3 << (WORD)41;	ar3 << (WORD)15;	ar3 << (WORD)36;	ar3 << (WORD)9;
	ar3 << (WORD)32;	ar3 << (WORD)5;		ar3 << (WORD)28;	ar3 << (WORD)0;

	// Q
	ar3 << (WORD)7;	// number of elements
	ar3 << (WORD)95;	ar3 << (WORD)124;	ar3 << (WORD)76;	ar3 << (WORD)71;
	ar3 << (WORD)61;	ar3 << (WORD)37;	ar3 << (WORD)50;	ar3 << (WORD)22;
	ar3 << (WORD)43;	ar3 << (WORD)13;	ar3 << (WORD)38;	ar3 << (WORD)7;
	ar3 << (WORD)34;	ar3 << (WORD)3;		ar3 << (WORD)29;	ar3 << (WORD)0;

	// R
	ar3 << (WORD)6;	// number of elements
	ar3 << (WORD)104;	ar3 << (WORD)115;	ar3 << (WORD)82;	ar3 << (WORD)65;
	ar3 << (WORD)64;	ar3 << (WORD)34;	ar3 << (WORD)53;	ar3 << (WORD)19;
	ar3 << (WORD)46;	ar3 << (WORD)10;	ar3 << (WORD)40;	ar3 << (WORD)5;
	ar3 << (WORD)36;	ar3 << (WORD)0;

	// S
	ar3 << (WORD)6;	// number of elements
	ar3 << (WORD)112;	ar3 << (WORD)107;	ar3 << (WORD)88;	ar3 << (WORD)59;
	ar3 << (WORD)68;	ar3 << (WORD)30;	ar3 << (WORD)56;	ar3 << (WORD)16;
	ar3 << (WORD)48;	ar3 << (WORD)8;		ar3 << (WORD)42;	ar3 << (WORD)3;	
	ar3 << (WORD)37;	ar3 << (WORD)0;

	// T
	ar3 << (WORD)5;	// number of elements
	ar3 << (WORD)122;	ar3 << (WORD)97;	ar3 << (WORD)94;	ar3 << (WORD)53;
	ar3 << (WORD)73;	ar3 << (WORD)25;	ar3 << (WORD)60;	ar3 << (WORD)12;
	ar3 << (WORD)51;	ar3 << (WORD)5;		ar3 << (WORD)44;	ar3 << (WORD)0;

	// U
	ar3 << (WORD)5;	// number of elements
	ar3 << (WORD)133;	ar3 << (WORD)86;	ar3 << (WORD)101;	ar3 << (WORD)46;
	ar3 << (WORD)77;	ar3 << (WORD)21;	ar3 << (WORD)63;	ar3 << (WORD)9;
	ar3 << (WORD)53;	ar3 << (WORD)3;		ar3 << (WORD)45;	ar3 << (WORD)0;

	// V
	ar3 << (WORD)4;	// number of elements
	ar3 << (WORD)145;	ar3 << (WORD)74;	ar3 << (WORD)108;	ar3 << (WORD)39;
	ar3 << (WORD)82;	ar3 << (WORD)16;	ar3 << (WORD)67;	ar3 << (WORD)5;
	ar3 << (WORD)55;	ar3 << (WORD)0;
	
	// W
	ar3 << (WORD)4;	// number of elements
	ar3 << (WORD)160;	ar3 << (WORD)59;	ar3 << (WORD)116;	ar3 << (WORD)31;
	ar3 << (WORD)87;	ar3 << (WORD)11;	ar3 << (WORD)70;	ar3 << (WORD)2;
	ar3 << (WORD)56;	ar3 << (WORD)0;
	
	// X
	ar3 << (WORD)3;	// number of elements
	ar3 << (WORD)178;	ar3 << (WORD)41;	ar3 << (WORD)125;	ar3 << (WORD)22;
	ar3 << (WORD)92;	ar3 << (WORD)6;		ar3 << (WORD)72;	ar3 << (WORD)0;
	
	// Y
	ar3 << (WORD)2;	// number of elements
	ar3 << (WORD)199;	ar3 << (WORD)20;	ar3 << (WORD)134;	ar3 << (WORD)13;
	ar3 << (WORD)98;	ar3 << (WORD)0;
	
	// Z
	ar3 << (WORD)1;	// number of elements
	ar3 << (WORD)219;	ar3 << (WORD)0;		ar3 << (WORD)147;	ar3 << (WORD)0;
}