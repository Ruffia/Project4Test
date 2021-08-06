#include "resource.h"
#include <Windows.h>
#include <WinGDI.h>
#pragma comment(lib, "Msimg32.lib")

BOOL PaintBmp(HWND hWnd)
{
	// 获取窗口的客户区域的显示设备上下文环境的句柄
	HDC hDC = ::GetDC(hWnd);
	// 创建一个与hDC兼容的内存设备上下文环境
	HDC hBuf = ::CreateCompatibleDC(hDC);
	// 加载位图, 获取位图句柄
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, "image\\bg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 选择位图句柄到hBuf中, 并获取返回的原来位图句柄
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp);
	// 绘图
	::BitBlt(hDC, 0, 0, 764, 397, hBuf, 0, 0, SRCCOPY);
	// 还原位图对象
	::SelectObject(hBuf, hOldBmp);
	// 释放位图
	::DeleteObject(hBmp);
	// 释放兼容的内存设备上下文环境
	::DeleteDC(hBuf);
	// 释放设备上下文环境
	::ReleaseDC(hWnd, hDC);

	return TRUE;
}


BOOL PaintTransparentBmp(HWND hWnd)
{
	// 获取窗口的客户区域的显示设备上下文环境的句柄
	HDC hDC = ::GetDC(hWnd);
	// 创建一个与hDC兼容的内存设备上下文环境
	HDC hBuf = ::CreateCompatibleDC(hDC);
	// 加载位图, 获取位图句柄
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, "image\\2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 选择位图句柄到hBuf中, 并获取返回的原来位图句柄
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp);
	// 透明色为蓝色 绘制
	::TransparentBlt(hDC, 200, 100, 177, 130, hBuf, 0, 0, 177, 130, RGB(255, 0, 255));
	// 还原位图对象
	::SelectObject(hBuf, hOldBmp);
	// 释放位图
	::DeleteObject(hBmp);
	// 释放兼容的内存设备上下文环境
	::DeleteDC(hBuf);
	// 释放设备上下文环境
	::ReleaseDC(hWnd, hDC);

	return TRUE;
}


BOOL CALLBACK ProgMainDlg(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_INITDIALOG == uiMsg)
	{
	}
	else if (WM_CLOSE == uiMsg)
	{
		::EndDialog(hWnd, NULL);
	}
	else if (WM_PAINT == uiMsg)
	{
		// 绘制背景
		//PaintBmp(hWnd);
		// 绘制人物
		PaintTransparentBmp(hWnd);
	}

	return FALSE;
}


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevinstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	::DialogBoxParam(hInstance, (LPCSTR)IDD_DIALOG1, NULL, (DLGPROC)ProgMainDlg, NULL);

	::ExitProcess(NULL);
	return 0;
}