// HexText.cpp: Implementierung der Klasse CHexText.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxwin.h>
#include "HexText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CHexText::CHexText()
{}
CHexText::~CHexText()
{}

//Parameter :"ABC<32>abc<<DE<64>HIJK"
//Return    :"ABC abc<DE@HIJK"
CString CHexText::Brackets2Hex( CString & strSource)
{
	return CHexText::Brackets2Hex(strSource,strSource.GetLength());
}
CString CHexText::Brackets2Hex( LPCSTR strSource)
{
	return CHexText::Brackets2Hex(strSource,strlen(strSource));
}
CString CHexText::Brackets2Hex( LPCSTR strSource, int length)
{
	CString strLine;
   LPSTR szNew = strLine.GetBuffer(length +1);
   int n=0;
	char *chBuffer = (char*)strSource;
	int i=0;
	BYTE ch = 0xff;
	while( i < length /*&& ch != 0*/)
	{
		
		ch = (BYTE)chBuffer[i];					 // 
		if( ch == '<' )							 // abc<156> '<'-Zeichen heißt: jetzt kommt ein Buchstabe als Dec
		{
			i++;								 //		
			if( (BYTE)chBuffer[i] == '<' )		 // abc<<fg	 2'<'-Zeichen heißen: der Buchstabe '<' ist gemeint
			{									 
				szNew[n++] = '<';
				i++;
				continue;						 // Den String weiter durchsuchen
			}									  //	i
			ch = atoi( &chBuffer[i] );			  //    156>  ->  char(156)
//			if( ch != 0)
				szNew[n++] = (char)ch;
			while( chBuffer[i] >= '0'			  // Zahlen überspringen
				&& chBuffer[i] <= '9'
//				&& chBuffer[i] != 0)
				&& i<length)
					i++;
//			if(chBuffer[i] == 0)
//				break;
			while(chBuffer[i] != '>'			  // '>' suchen
//				&& chBuffer[i] != 0)
				&& i<length)
					i++;
			if(chBuffer[i] == '>')				  // '>' überspringen
					i++;
		}
		else									  // es ist kein '<' aufgetreten
		{
			szNew[n++] = (char)ch;
			i++;
		}
	}
   strLine.ReleaseBuffer(n);
	return strLine;

}

//Parameter :"ABC abc<DE@HIJK"
//Return    :"ABC<32>abc<<DE<64>HIJK"
CString CHexText::Hex2Brackets( CString & strSource)
{
	return CHexText::Hex2Brackets(strSource,strSource.GetLength());
}
CString CHexText::Hex2Brackets( LPCSTR strSource)
{
	return CHexText::Hex2Brackets(strSource,strlen(strSource));
}
CString CHexText::Hex2Brackets( LPCSTR strSource, int length)
{
	CString strEditString;
	CString strBuffer;
	for(int i=0 ; i < length; i++)
	{
		BYTE ch = (BYTE)strSource[i];
		if( (ch < 32) || (ch > 127) )
		{
			strBuffer.Format("<%d>",ch);
			strEditString += strBuffer;
		}
		else
		{
			if( ch=='<' )//aus'<' ---> mach '<<'
				strEditString += '<';
			strEditString += ch;
		}
	}
	return strEditString;
}
//Parameter :"AB\0CD"
//Return    :"41 42 00 43"
CString CHexText::Ascii2Hex( CString & strSource)
{
	return CHexText::Ascii2Hex(strSource,strSource.GetLength());
}
CString CHexText::Ascii2Hex( LPCSTR strSource)
{
	return CHexText::Ascii2Hex(strSource,strlen(strSource));
}
CString CHexText::Ascii2Hex( LPCSTR strSource, int length)
{
	CString strReturn;
	CString strBuffer;
	for( int i=0 ; i< length ; i++)
	{
		strBuffer.Format("%02X ", *(BYTE*)&strSource[i]);
		strReturn += strBuffer;
	}
	return strReturn;
}

//Parameter :"41 42 00 43"
//Return    :"AB\0CD" 
CString CHexText::Hex2Ascii( CString & strSource)
{
	return CHexText::Hex2Ascii(strSource,strSource.GetLength());
}
CString CHexText::Hex2Ascii( LPCSTR strSource)
{
	return CHexText::Hex2Ascii(strSource,strlen(strSource));
}
CString CHexText::Hex2Ascii( LPCSTR strSource, int length)
{
	CString strReturn;
	LPTSTR pNewStr = strReturn.GetBufferSetLength(length);
	int nCount=0;
	char *pStr = (char*)strSource;
	int nRead;
	while( strSource + length > pStr )
	{
		int c;
		if ( 0 < sscanf(pStr,"%2x%n",&c,&nRead))
		{
			pNewStr[nCount] =(char)c;
			nCount++;
			pStr += nRead;
		}
		else
			pStr+= 3;
	}
	strReturn.ReleaseBuffer(nCount);
	return strReturn;
}

// DataExchange for Editcontrols
void	DDX_TextHexBracket(CDataExchange* pDX,int nID, CString &str)
{
	CString strBuffer;
	if( pDX->m_bSaveAndValidate)
	{
		DDX_Text(pDX,nID,str);
		str = CHexText::Brackets2Hex(str);
	}
	else
	{
		str = CHexText::Hex2Brackets(str);
		DDX_Text(pDX,nID,str);
	}
}
void	DDX_TextHexAscii(CDataExchange* pDX,int nID, CString &str)
{
	CString strBuffer;
	if( pDX->m_bSaveAndValidate)
	{
		DDX_Text(pDX,nID,strBuffer);
		str = CHexText::Hex2Ascii(str);
	}
	else
	{
		str = CHexText::Ascii2Hex(strBuffer);
		DDX_Text(pDX,nID,str);
	}
}
// Edit :"41 42 00 43"  <--> CString:"AB\0CD"
// CString::GetLength()  ist ausschlaggebend für die Anzahl
// der Bytes. NICHT NULL-TERMINIERT !
void DDX_HexText(CDataExchange* pDX,int nID, CString &str)
{
	CString strBuffer;
	if( pDX->m_bSaveAndValidate)
	{
		DDX_Text(pDX,nID,strBuffer);
		str = CHexText::Hex2Ascii(strBuffer);
	}
	else
	{
		strBuffer = CHexText::Ascii2Hex(str);
		DDX_Text(pDX,nID,strBuffer);
	}
}
void DDX_HexText(CDataExchange* pDX, int nIDC, int &nValue)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CString value;
	if (pDX->m_bSaveAndValidate)
	{
		int nLen = ::GetWindowTextLength(hWndCtrl);
		::GetWindowText(hWndCtrl, value.GetBufferSetLength(nLen), nLen+1);
		value.ReleaseBuffer();
		sscanf( value , "%x",&nValue ); 
	}
	else
	{
		value.Format("%X",nValue);
		SetWindowText(hWndCtrl, value);
	}
}
void DDX_HexText(CDataExchange* pDX, int nIDC, short &nValue)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CString value;
	if (pDX->m_bSaveAndValidate)
	{
		int nLen = ::GetWindowTextLength(hWndCtrl);
		::GetWindowText(hWndCtrl, value.GetBufferSetLength(nLen), nLen+1);
		value.ReleaseBuffer();
		sscanf( value , "%hx",&nValue ); 
	}
	else
	{
		value.Format("%hX",nValue);
		SetWindowText(hWndCtrl, value);
	}
}
void DDX_HexText(CDataExchange* pDX, int nIDC, DWORD &dwValue)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CString value;
	if (pDX->m_bSaveAndValidate)
	{
		int nLen = ::GetWindowTextLength(hWndCtrl);
		::GetWindowText(hWndCtrl, value.GetBuffer(nLen+1), nLen+1);
		value.ReleaseBuffer();
		sscanf( value , "%x",&dwValue ); 
	}
	else
	{
		value.Format("%X",dwValue);
		SetWindowText(hWndCtrl, value);
	}
}
void DDX_HexText(CDataExchange* pDX, int nIDC, WORD &wValue)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CString value;
	if (pDX->m_bSaveAndValidate)
	{
		int nLen = ::GetWindowTextLength(hWndCtrl);
		::GetWindowText(hWndCtrl, value.GetBufferSetLength(nLen), nLen+1);
		value.ReleaseBuffer();
		sscanf( value , "%hx",&wValue ); 
	}
	else
	{
		value.Format("%hX",wValue);
		SetWindowText(hWndCtrl, value);
	}
}
void DDX_HexText(CDataExchange* pDX, int nIDC, BYTE &bValue)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CString value;
	if (pDX->m_bSaveAndValidate)
	{
		int nLen = ::GetWindowTextLength(hWndCtrl);
		::GetWindowText(hWndCtrl, value.GetBufferSetLength(nLen), nLen+1);
		value.ReleaseBuffer();
		int nBuffer;
		sscanf( value , "%x",&nBuffer );
		bValue = nBuffer&0xFF; 
	}
	else
	{
		value.Format("%02X",bValue);
		SetWindowText(hWndCtrl, value);
	}
}
void DDX_HexText(CDataExchange* pDX, int nIDC, char &bValue)
{
   DDX_HexText(pDX,nIDC,(BYTE&)bValue);
}

