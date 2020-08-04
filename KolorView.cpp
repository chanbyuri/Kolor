
// KolorView.cpp: CKolorView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Kolor.h"
#endif

#include "KolorDoc.h"
#include "KolorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKolorView

IMPLEMENT_DYNCREATE(CKolorView, CView)

BEGIN_MESSAGE_MAP(CKolorView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_EQUAL_COLOR, &CKolorView::OnEqualColor)
END_MESSAGE_MAP()

// CKolorView 생성/소멸

CKolorView::CKolorView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CKolorView::~CKolorView()
{
}

BOOL CKolorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CKolorView 그리기

void CKolorView::OnDraw(CDC* pDC)
{
	CKolorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	unsigned char R, G, B;
	for (int i = 0; i < pDoc->m_height; i++)
		for (int k = 0; k < pDoc->m_width; k++) {
			R = pDoc->m_InputImageR[i][k];
			G = pDoc->m_InputImageG[i][k];
			B = pDoc->m_InputImageB[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
		}

	for (int i = 0; i < pDoc->m_Re_height; i++)
		for (int k = 0; k < pDoc->m_Re_width; k++) {
			R = pDoc->m_OutputImageR[i][k];
			G = pDoc->m_OutputImageG[i][k];
			B = pDoc->m_OutputImageB[i][k];
			pDC->SetPixel(k + 5 + pDoc->m_width + 5, i + 5, RGB(R, G, B));
		}
}

// CKolorView 인쇄

BOOL CKolorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CKolorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CKolorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CKolorView 진단

#ifdef _DEBUG
void CKolorView::AssertValid() const
{
	CView::AssertValid();
}

void CKolorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolorDoc* CKolorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolorDoc)));
	return (CKolorDoc*)m_pDocument;
}
#endif //_DEBUG


// CKolorView 메시지 처리기


void CKolorView::OnEqualColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
