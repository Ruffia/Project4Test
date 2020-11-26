#if !defined(AFX_BITWND_H__CE32218D_87AD_49E0_8560_ABD326F5FA1E__INCLUDED_)
#define AFX_BITWND_H__CE32218D_87AD_49E0_8560_ABD326F5FA1E__INCLUDED_

#include "afxtempl.h"
// Autor :  Michael Schikora , schiko@schikos.de
//
// This code is free with this restrictions:
// If you use it in any commercial or noncommecial application,
// my name should appear at least in one of the following program parts:
// about box, manual , help file, readme file
// The copyright will still belong to me.
// I would be glad to get a e-mail if you do so.
//
// Good luck!
// Schiko   
//
// How to Use :
//
// I used the MFC RTTI for allocating the control in the DDX funktion.
// So I have to include the "BitWnd.h" only in my Dlg.cpp file
// and I don't need a control member in my header ;)
//
//Add some STATIC-controls to your DlgRecource like :
//   IDC_MY_DWORD_VALUE
//   IDC_MY_SHORT_VALUE
//Add member variables to your DlgClass
//   DWORD m_dwMyValue;
//   short m_sMyValue;
//
//Add the DDX_BitWnd(..) Functions to your DoDataExchange()
//   DDX_BitWnd(pDX,IDC_MY_DWORD_VALUE,m_dwMyValue); //horizontal low bit right (95% for me) 
//   DDX_BitWnd(pDX,                            // CDataExchange
//              IDC_MY_SHORT_VALUE,             // ID is also used for WM_COMMAND
//              m_sMyValue,                     // the value
//              FALSE,                          // vertical low bit top
//              0,                              // Create checks for all bits
//              NULL,                           // displays default Text "0".."n"   
//              0x800F,                         // enables only bit 4..14
//              0);                             // no spaces behind each 4th Checkbox
//
//That's all

// 
/////////////////////////////////////////////////////////////////////////////
// Fenster CBitChecker


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitWnd.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CBitWnd 

class CBitWnd : public CWnd
{
// Konstruktion
public:
   CBitWnd(BOOL bAutoDelete = FALSE);
   DECLARE_DYNAMIC(CBitWnd);
// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CBitWnd)
	protected:
	virtual void PreSubclassWindow();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CBitWnd();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
   int CreateChecks();
public:
   void EnableChecks(DWORD dwDisableMask = 0x00000000);
   // Text without an array: Format("%d",i)
   void SetCaptions(CStringArray* pArray=NULL);
	//{{AFX_MSG(CBitWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
   afx_msg void OnCheckBoxes(UINT nID);

	DECLARE_MESSAGE_MAP()


public:
	UINT m_ID;  	// our own ID. the checkboxes have the following nT_bits IDs
   BOOL m_bAutoDelete;    // deletes the Control in OnDestroy
   BOOL GetValue(LPVOID pValue,BOOL bGet=TRUE);
   BOOL SetValue(LPVOID pValue){return GetValue(pValue,FALSE);};
	int  m_nCountOfBits;   // its number of bits
   HWND m_hDlgWnd;
private:
	BOOL     m_bVertical;  // whether we want rows or columns
	LPVOID   m_pValue;  // the data
   DWORD    m_dwDisableMask; // Mayby some Checkboxes should be disabled( only 32 bit )
   int      m_nSpaceExtra; // Space between each 4th checkbox in Pixel
	CButton* m_arCheckBoxes;  // the checkbox-windows

public:
   static void DDX_BitWnd(CDataExchange *pDX,UINT nID,CBitWnd &wnd,LPVOID pValue,BOOL bVertical=FALSE,int nCountOfBits = 0,CStringArray *pStringArray=NULL,DWORD dwDisableMask=0x00000000,int nSpaceExtra = 2)
   {
      BOOL bCreateChecks = (wnd.m_hWnd == NULL && !pDX->m_bSaveAndValidate);
      // not subclassed yet
      //use the MFC subclass function
      DDX_Control(pDX,nID,wnd);

      if( bCreateChecks )
      {
         wnd.m_bVertical=(BOOL)bVertical;
         wnd.m_nSpaceExtra = nSpaceExtra;
         wnd.m_ID = nID;
         wnd.m_hDlgWnd = pDX->m_pDlgWnd->m_hWnd;
         wnd.CreateChecks();
         wnd.OnSize(0,0,0);

      }
      wnd.EnableChecks(dwDisableMask);
      wnd.SetCaptions(pStringArray);
      if(pDX->m_bSaveAndValidate)
         wnd.GetValue(pValue);
      else
         wnd.SetValue(pValue);
   }
};
//template <typename T_>
//inline void DDX_BitWnd(
//    CDataExchange* pDX,     //
//    UINT nID,               //BN_CLICK sends WM_COMMAND to the Parent with this ID
//    T_ &value,              //the value
//    BOOL bVertical=FALSE,   //default low bit right ,vertical: low bit top
//    int nCountOfBits = 0,   //0 : creates sizeof(value)*8 Checkboxes
//    CStringArray *pStringArray=NULL// NULL: text="0".."n"
//    DWORD dwDisableMask=0x00000000, // You may disable some of the lowest 32 bits
//    int nSpaceExtra = 2)    // the space behind each 4th Checkbox in Pixel
template <typename T_>
inline void DDX_BitWnd(CDataExchange* pDX,UINT nID,T_ &value,BOOL bVertical=FALSE,int nCountOfBits = 0,CStringArray *pStringArray=NULL,DWORD dwDisableMask=0x00000000,int nSpaceExtra = 2)
{
   CWnd *pControl = pDX->m_pDlgWnd->GetDlgItem(nID);
   if( ! pControl->IsKindOf(RUNTIME_CLASS(CBitWnd)) )
   {
      CBitWnd *pNew = new CBitWnd;//(TRUE) ; //autodelete on destroy
      pControl = (CBitWnd*)pNew;
      if(nCountOfBits)// don't create checkboxes for all bits
      {
         ASSERT(nCountOfBits <= sizeof(T_)*8);
         pNew->m_nCountOfBits = nCountOfBits;
      }
      else
         pNew->m_nCountOfBits = sizeof(T_)*8;
      pNew->m_bAutoDelete = TRUE;
   }
   ASSERT(pControl);
   CBitWnd::DDX_BitWnd(pDX,nID,*(CBitWnd*)pControl,& value, bVertical,nCountOfBits,pStringArray,dwDisableMask,nSpaceExtra);
}
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_BITWND_H__CE32218D_87AD_49E0_8560_ABD326F5FA1E__INCLUDED_
