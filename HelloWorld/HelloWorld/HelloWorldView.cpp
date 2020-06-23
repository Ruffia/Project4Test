
// HelloWorldView.cpp : CHelloWorldView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHelloWorldView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CHelloWorldView 构造/析构

CHelloWorldView::CHelloWorldView()
{
	// TODO: 在此处添加构造代码
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHelloWorldView 绘制

void CHelloWorldView::OnDraw(CDC* pDC)
{
	CHelloWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect recClient;
	this->GetClientRect(recClient);

	// TODO: 在此处为本机数据添加绘制代码
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


// CHelloWorldView 打印


void CHelloWorldView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHelloWorldView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHelloWorldView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHelloWorldView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CHelloWorldView 诊断

#ifdef _DEBUG
void CHelloWorldView::AssertValid() const
{
	CView::AssertValid();
}

void CHelloWorldView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHelloWorldDoc* CHelloWorldView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelloWorldDoc)));
	return (CHelloWorldDoc*)m_pDocument;
}
#endif //_DEBUG


// CHelloWorldView 消息处理程序
