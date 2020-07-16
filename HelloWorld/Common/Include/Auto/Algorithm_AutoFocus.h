#if !defined(Algorithm_AUTO_FOCUS__INCLUDED_)
#define Algorithm_AUTO_FOCUS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Algorithm_AutoFocus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Algorithm_AutoFocus

const double OL_TO_LED	= 64.0;

const UINT AutoFocus_Analyze_Continue		= 0;
const UINT AutoFocus_Analyze_Completed		= 1;
const UINT AutoFocus_Analyze_Failure		= 2;

AFX_EXT_API void WINAPI AutoFocus_Initialize(
	long& 		lFieldLens,
	double&		dblMagnifier );

AFX_EXT_API BOOL WINAPI Analyze_Image( 
	LPVOID		lpImageBuff,
	CSize		sizeImage,
	double&		dfSharpness,
	double&		dfParamX,
	double&		dfParamY,
	double&		dfTotal );

AFX_EXT_API UINT WINAPI AutoFocus_Analyze_Image( 
	LPVOID		lpImageBuff,
	CSize		sizeImage,
	double&		dfSharpness,
	long& 		lFieldLens,
	double&		dblMagnifier );

///////////////////////////////////////////////////////
// 2009.04.15_�Զ��۽��㷨�Ż�
AFX_EXT_API void WINAPI AutoFocus_Initialize2(
	long& 		lFieldLens,
	double&		dblMagnifier );

AFX_EXT_API UINT WINAPI AutoFocus_Analyze_Image2( 
	LPVOID		lpImageBuff,
	CSize		sizeImage,
	double&		dfSharpness,
	long& 		lFieldLens,
	double&		dblMagnifier );
// 2009.04.15_�Զ��۽��㷨�Ż�
///////////////////////////////////////////////////////

/*
double WINAPI CtrlToMag( WORD wCtrl );

WORD WINAPI MagToCtrl( double dfMag );
*/

#endif // Algorithm_AUTO_FOCUS__INCLUDED_
