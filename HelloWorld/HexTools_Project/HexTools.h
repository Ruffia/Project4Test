// HexTools.h : Haupt-Header-Datei f�r die Anwendung HEXTOOLS
//

#if !defined(AFX_HEXTOOLS_H__60EC903F_D258_4893_AF29_2AD39F4FD708__INCLUDED_)
#define AFX_HEXTOOLS_H__60EC903F_D258_4893_AF29_2AD39F4FD708__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CHexToolsApp:
// Siehe HexTools.cpp f�r die Implementierung dieser Klasse
//

class CHexToolsApp : public CWinApp
{
public:
	CHexToolsApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CHexToolsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CHexToolsApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_HEXTOOLS_H__60EC903F_D258_4893_AF29_2AD39F4FD708__INCLUDED_)
