
// HelloWorldView.cpp : CHelloWorldView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "HelloWorld.h"
#endif

#include "HelloWorldDoc.h"
#include "HelloWorldView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char* Float2HexString(const float f) 
{
	unsigned char *hex = (unsigned char *)&f;
	char* sHex = new char[2*8 + 1];
	memset(sHex,0,17);
	sprintf_s(sHex,17,"%02X%02X%02X%02X",hex[0],hex[1],hex[2],hex[3]);
	return sHex;
}

DWORD Float2DWORD(const float f) 
{
	unsigned char *hex = (unsigned char *)&f;
	char* sHex = new char[2*8 + 1];
	memset(sHex,0,17);
	sprintf_s(sHex,16,"%02X%02X%02X%02X",hex[0],hex[1],hex[2],hex[3]);
	DWORD dValue = (DWORD)strtoul(sHex, NULL, 16);
	delete sHex;
	sHex = NULL;
	return dValue;
}

DWORD HexStringToDword(char* szBuf)
{	
	DWORD dwValue = 0;	
	BYTE bValue;	
	BYTE k;	
	for(k=0;k<10;++k)	
	{		
		if(*szBuf >= '0' && *szBuf <= '9')		
		{			
			bValue = *szBuf - '0';		
		}		
		else if(*szBuf >= 'a' && *szBuf <= 'f')		
		{			
			bValue = *szBuf - 'a' + 10;		
		}		
		else if(*szBuf >= 'A' && *szBuf <= 'F')		
		{			
			bValue = *szBuf - 'A' + 10;		
		}		
		else if(*szBuf =='x' || *szBuf == 'X')		
		{			
			dwValue = 0;			
			szBuf ++;			
			continue;		
		}		
		else
		{			
			break;		
		}		
		dwValue <<= 4;		
		dwValue |= bValue;		
		szBuf ++;	
	}	
	return dwValue;
}


// CHelloWorldView

IMPLEMENT_DYNCREATE(CHelloWorldView, CView)

BEGIN_MESSAGE_MAP(CHelloWorldView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHelloWorldView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CHelloWorldView ����/����

CHelloWorldView::CHelloWorldView()
{
	// TODO: �ڴ˴���ӹ������
	char* sHex = Float2HexString(1.0625f);
	DWORD dValue = HexStringToDword(sHex);
	delete sHex;
	sHex = NULL;
}

CHelloWorldView::~CHelloWorldView()
{
}

BOOL CHelloWorldView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CHelloWorldView ����

void CHelloWorldView::OnDraw(CDC* pDC)
{
	CHelloWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect recClient;
	this->GetClientRect(recClient);

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//pDC->DrawText(_T("Hello World"),CRect(50,
	//	50,500,500),0);

	pDC->DrawText(_T("Hello World"),CRect(300,
		200,500,500),0);

	pDC->Draw3dRect(100,200,200,200,RGB(255,0,0),RGB(0,255,0));

	pDC->Rectangle(CRect(300,400,600,600));

	pDC->Ellipse(CRect(600,200,1000,600));

	//pDC->DrawText(_T("Hello World"),CRect(recClient.Width()/2.f,
	//	recClient.Height()/2.f,500,500),0);
}


// CHelloWorldView ��ӡ


void CHelloWorldView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHelloWorldView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CHelloWorldView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CHelloWorldView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CHelloWorldView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHelloWorldView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHelloWorldView ���

#ifdef _DEBUG
void CHelloWorldView::AssertValid() const
{
	CView::AssertValid();
}

void CHelloWorldView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHelloWorldDoc* CHelloWorldView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelloWorldDoc)));
	return (CHelloWorldDoc*)m_pDocument;
}
#endif //_DEBUG


// CHelloWorldView ��Ϣ�������
