#include "resource.h"
#include <Windows.h>
#include <WinGDI.h>
#pragma comment(lib, "Msimg32.lib")

BOOL PaintBmp(HWND hWnd)
{
	// ��ȡ���ڵĿͻ��������ʾ�豸�����Ļ����ľ��
	HDC hDC = ::GetDC(hWnd);
	// ����һ����hDC���ݵ��ڴ��豸�����Ļ���
	HDC hBuf = ::CreateCompatibleDC(hDC);
	// ����λͼ, ��ȡλͼ���
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, "image\\bg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ѡ��λͼ�����hBuf��, ����ȡ���ص�ԭ��λͼ���
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp);
	// ��ͼ
	::BitBlt(hDC, 0, 0, 764, 397, hBuf, 0, 0, SRCCOPY);
	// ��ԭλͼ����
	::SelectObject(hBuf, hOldBmp);
	// �ͷ�λͼ
	::DeleteObject(hBmp);
	// �ͷż��ݵ��ڴ��豸�����Ļ���
	::DeleteDC(hBuf);
	// �ͷ��豸�����Ļ���
	::ReleaseDC(hWnd, hDC);

	return TRUE;
}


BOOL PaintTransparentBmp(HWND hWnd)
{
	// ��ȡ���ڵĿͻ��������ʾ�豸�����Ļ����ľ��
	HDC hDC = ::GetDC(hWnd);
	// ����һ����hDC���ݵ��ڴ��豸�����Ļ���
	HDC hBuf = ::CreateCompatibleDC(hDC);
	// ����λͼ, ��ȡλͼ���
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, "image\\2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ѡ��λͼ�����hBuf��, ����ȡ���ص�ԭ��λͼ���
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp);
	// ͸��ɫΪ��ɫ ����
	::TransparentBlt(hDC, 200, 100, 177, 130, hBuf, 0, 0, 177, 130, RGB(255, 0, 255));
	// ��ԭλͼ����
	::SelectObject(hBuf, hOldBmp);
	// �ͷ�λͼ
	::DeleteObject(hBmp);
	// �ͷż��ݵ��ڴ��豸�����Ļ���
	::DeleteDC(hBuf);
	// �ͷ��豸�����Ļ���
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
		// ���Ʊ���
		//PaintBmp(hWnd);
		// ��������
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