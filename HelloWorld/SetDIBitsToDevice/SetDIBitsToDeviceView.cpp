
// SetDIBitsToDeviceView.cpp : CSetDIBitsToDeviceView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SetDIBitsToDevice.h"
#endif

#include "SetDIBitsToDeviceDoc.h"
#include "SetDIBitsToDeviceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSetDIBitsToDeviceView

IMPLEMENT_DYNCREATE(CSetDIBitsToDeviceView, CView)

BEGIN_MESSAGE_MAP(CSetDIBitsToDeviceView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSetDIBitsToDeviceView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSetDIBitsToDeviceView ����/����

CSetDIBitsToDeviceView::CSetDIBitsToDeviceView()
{
	// TODO: �ڴ˴���ӹ������

}

CSetDIBitsToDeviceView::~CSetDIBitsToDeviceView()
{
}

BOOL CSetDIBitsToDeviceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSetDIBitsToDeviceView ����

void CSetDIBitsToDeviceView::OnDraw(CDC* /*pDC*/)
{
	CSetDIBitsToDeviceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSetDIBitsToDeviceView ��ӡ


void CSetDIBitsToDeviceView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSetDIBitsToDeviceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSetDIBitsToDeviceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSetDIBitsToDeviceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CSetDIBitsToDeviceView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSetDIBitsToDeviceView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSetDIBitsToDeviceView ���

#ifdef _DEBUG
void CSetDIBitsToDeviceView::AssertValid() const
{
	CView::AssertValid();
}

void CSetDIBitsToDeviceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSetDIBitsToDeviceDoc* CSetDIBitsToDeviceView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSetDIBitsToDeviceDoc)));
	return (CSetDIBitsToDeviceDoc*)m_pDocument;
}
#endif //_DEBUG


// CSetDIBitsToDeviceView ��Ϣ�������
