#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#pragma comment(lib,"DDraw.lib")

LPDIRECTDRAW lpDD; // DirectDraw����
LPDIRECTDRAWSURFACE lpDDSPrimary; // DirectDraw��ҳ��
char szMsg1[] = "Hello World, I am DirectDraw boy !";
char szMsg2[] = "�� ESC �˳�";

//��������
LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
BOOL InitWindow( HINSTANCE hInstance, int nCmdShow );
BOOL InitDDraw();
void FreeDDraw(void);

//*******************************************************************
//������WinMain()
//���ܣ�Win32Ӧ�ó�����ں��������г�ʼ��������������Ϣѭ��
//*******************************************************************
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	//��ʼ��������
	if ( !InitWindow( hInstance, nCmdShow ) )
	{
		return FALSE;
	}
	
	//��ʼ��DirectDraw��������ʵ��DirectDraw����
	if ( !InitDDraw())
	{
		MessageBox(GetActiveWindow(), "��ʼ��DirectDraw�����г���", "Error", MB_OK );
		FreeDDraw();
		DestroyWindow(GetActiveWindow());
		return FALSE;
	}
	//������Ϣѭ��
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


static BOOL InitWindow( HINSTANCE hInstance, int nCmdShow )
{
	HWND hwnd; //���ھ��
	WNDCLASS wc; //������ṹ
	//��䴰����ṹ
	wc.style = 0;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( hInstance, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "dxHello";
	
	
	//ע�ᴰ����
	RegisterClass( &wc );
	//����������
	hwnd = CreateWindowEx(
		0,
		"dxHello",
		"",
		WS_POPUP,
		0, 0,
		GetSystemMetrics( SM_CXSCREEN )/2,
		GetSystemMetrics( SM_CYSCREEN )/2,
		NULL,
		NULL,
		hInstance,
		NULL );
	if( !hwnd ) return FALSE;
	//��ʾ�����´���
	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );
	return TRUE;
}
//******************************************************************
//������WinProc()
//���ܣ�������������Ϣ
//******************************************************************
LRESULT CALLBACK WinProc( HWND hWnd, UINT message, 
						 WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	case WM_KEYDOWN://������Ϣ
		switch( wParam )
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_DESTROY://�˳���Ϣ
		FreeDDraw();
		PostQuitMessage( 0 );
		break;
	}
	
	//����ȱʡ��Ϣ�������
	return DefWindowProc(hWnd, message, wParam, lParam);
}


BOOL InitDDraw(void)
{
	DDSURFACEDESC ddsd; //ҳ������
	HDC hdc; //�豸�������
	
	//����DirectCraw����
	if ( DirectDrawCreate( NULL, &lpDD, NULL ) != DD_OK )
	{
		return FALSE;
	}
	
	// ȡ�ö�ռ��ȫ��ģʽ
	if ( lpDD->SetCooperativeLevel( GetActiveWindow(),DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN ) != DD_OK)
	{
		return FALSE;
	}

	//������ʾģʽ
	if ( lpDD->SetDisplayMode( 1600, 900, 8 ) != DD_OK)
	{
		return FALSE;
	}

	//�����ҳ����Ϣ
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	//������ҳ�����
	if ( lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL ) != DD_OK)
	{
		return FALSE;
	}

	//�������
	if ( lpDDSPrimary->GetDC(&hdc) != DD_OK)
	{
		return FALSE; 
	}

	SetBkColor( hdc, RGB( 0, 0, 255 ) );
	SetTextColor( hdc, RGB( 255, 255, 0 ) );
	TextOut( hdc, 220, 200, szMsg1, lstrlen(szMsg1));
	TextOut( hdc, 280, 240, szMsg2, lstrlen(szMsg2));
	lpDDSPrimary->ReleaseDC(hdc);
	return TRUE;
}

//******************************************************************
//������FreeDDraw()
//���ܣ��ͷ����е�DirectDraw����
//******************************************************************
void FreeDDraw( void )
{
	if( lpDD != NULL )
	{
		if( lpDDSPrimary != NULL )
		{
			lpDDSPrimary->Release();
			lpDDSPrimary = NULL;
		}
		lpDD->Release();
		lpDD = NULL;
	}
}
