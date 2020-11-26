// HexText.h: Schnittstelle für die Klasse CHexText.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXTEXT_H__7EC2FFC3_857A_11D4_8794_00104B4A122C__INCLUDED_)
#define AFX_HEXTEXT_H__7EC2FFC3_857A_11D4_8794_00104B4A122C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHexText  
{
public:
	CHexText();
	virtual ~CHexText();

//Parameter :"ABC<32>abc<<DE<64>HIJK"
//Return    :"ABC abc<DE@HIJK"
	static CString Brackets2Hex( CString & strSource);
	static CString Brackets2Hex( LPCSTR strSource);
	static CString Brackets2Hex( LPCSTR strSource, int length);

//Parameter :"ABC abc<DE@HIJK"
//Return    :"ABC<32>abc<<DE<64>HIJK"
	static CString Hex2Brackets( CString & strSource);
	static CString Hex2Brackets( LPCSTR strSource);
	static CString Hex2Brackets( LPCSTR strSource, int length);

//Parameter :"AB\0CD"
//Return    :"41 42 00 43"
	static CString Ascii2Hex( CString & strSource);
	static CString Ascii2Hex( LPCSTR strSource);
	static CString Ascii2Hex( LPCSTR strSource, int length);

//Parameter :"41 42 00 43"
//Return    :"AB\0CD" 
	static CString Hex2Ascii( CString & strSource);
	static CString Hex2Ascii( LPCSTR strSource);
	static CString Hex2Ascii( LPCSTR strSource, int length);
};
// DataExchange for Editcontrols
void	DDX_TextHexBracket(CDataExchange* pDX,int nID, CString &str);
void	DDX_TextHexAscii(CDataExchange* pDX,int nID, CString &str);
void	DDX_HexText(CDataExchange* pDX,int nID, CString &str);
void	DDX_HexText(CDataExchange* pDX, int nIDC, int &nValue);
void	DDX_HexText(CDataExchange* pDX, int nIDC, short &nValue);
void	DDX_HexText(CDataExchange* pDX, int nIDC, char &nValue);
void	DDX_HexText(CDataExchange* pDX, int nIDC, DWORD &dwValue);
void	DDX_HexText(CDataExchange* pDX, int nIDC, WORD &wValue);
void	DDX_HexText(CDataExchange* pDX, int nIDC, BYTE &bValue);



#endif // !defined(AFX_HEXTEXT_H__7EC2FFC3_857A_11D4_8794_00104B4A122C__INCLUDED_)
