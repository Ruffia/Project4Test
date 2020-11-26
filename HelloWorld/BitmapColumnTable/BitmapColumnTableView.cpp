
// BitmapColumnTableView.cpp : CBitmapColumnTableView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BitmapColumnTable.h"
#endif

#include "BitmapColumnTableDoc.h"
#include "BitmapColumnTableView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBitmapColumnTableView

IMPLEMENT_DYNCREATE(CBitmapColumnTableView, CView)

BEGIN_MESSAGE_MAP(CBitmapColumnTableView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBitmapColumnTableView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBitmapColumnTableView ����/����

CBitmapColumnTableView::CBitmapColumnTableView()
{
	// TODO: �ڴ˴���ӹ������

}

CBitmapColumnTableView::~CBitmapColumnTableView()
{
}

BOOL CBitmapColumnTableView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBitmapColumnTableView ����

void CBitmapColumnTableView::OnDraw(CDC* /*pDC*/)
{
	CBitmapColumnTableDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CBitmapColumnTableView ��ӡ


void CBitmapColumnTableView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBitmapColumnTableView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBitmapColumnTableView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CBitmapColumnTableView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CBitmapColumnTableView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBitmapColumnTableView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBitmapColumnTableView ���

#ifdef _DEBUG
void CBitmapColumnTableView::AssertValid() const
{
	CView::AssertValid();
}

void CBitmapColumnTableView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitmapColumnTableDoc* CBitmapColumnTableView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitmapColumnTableDoc)));
	return (CBitmapColumnTableDoc*)m_pDocument;
}
#endif //_DEBUG


// CBitmapColumnTableView ��Ϣ�������
