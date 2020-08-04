
// KolorDoc.cpp: CKolorDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Kolor.h"
#endif

#include "KolorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKolorDoc

IMPLEMENT_DYNCREATE(CKolorDoc, CDocument)

BEGIN_MESSAGE_MAP(CKolorDoc, CDocument)
END_MESSAGE_MAP()


// CKolorDoc 생성/소멸

CKolorDoc::CKolorDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CKolorDoc::~CKolorDoc()
{
}

BOOL CKolorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CKolorDoc serialization

void CKolorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CKolorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CKolorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CKolorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CKolorDoc 진단

#ifdef _DEBUG
void CKolorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKolorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKolorDoc 명령


BOOL CKolorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CImage m_bitmap;
	m_bitmap.Load(lpszPathName);

	// 기존 메모리 해제
	freeInputImage(m_old_height);
	//중요! 입력 영상 크기 결정
	m_height = m_bitmap.GetHeight();
	m_width = m_bitmap.GetWidth();
	m_old_height = m_height;
	m_old_width = m_width;

	// 메모리 할당
	m_InputImageR = malloc2D(m_height, m_width);
	m_InputImageG = malloc2D(m_height, m_width);
	m_InputImageB = malloc2D(m_height, m_width);

	//칼라 이미지-> 메모리
	COLORREF pixel;
	for(int i=0;i<m_height;i++)
		for (int k = 0; k < m_width; k++) {
			pixel = m_bitmap.GetPixel(i, k);
			m_InputImageR[k][i] = (unsigned char)GetRValue(pixel);
			m_InputImageG[k][i] = (unsigned char)GetGValue(pixel);
			m_InputImageB[k][i] = (unsigned char)GetBValue(pixel);
		}
	return TRUE;
}


void CKolorDoc::freeInputImage(int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR != NULL) {
		for (int i = 0; i < h; i++)
			free(m_InputImageR[i]);
		free(m_InputImageR);
	}
	m_InputImageR = NULL;
	if (m_InputImageG != NULL) {
		for (int i = 0; i < h; i++)
			free(m_InputImageG[i]);
		free(m_InputImageG);
	}
	m_InputImageG = NULL;
	if (m_InputImageB != NULL) {
		for (int i = 0; i < h; i++)
			free(m_InputImageB[i]);
		free(m_InputImageB);
	}
	m_InputImageB = NULL;
}
void CKolorDoc::freeOutputImage(int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (m_OutputImageR != NULL) {
		for (int i = 0; i < h; i++)
			free(m_OutputImageR[i]);
		free(m_OutputImageR);
	}
	m_OutputImageR = NULL;
	if (m_OutputImageG != NULL) {
		for (int i = 0; i < h; i++)
			free(m_OutputImageG[i]);
		free(m_OutputImageG);
	}
	m_OutputImageG = NULL;
	if (m_OutputImageB != NULL) {
		for (int i = 0; i < h; i++)
			free(m_OutputImageB[i]);
		free(m_OutputImageB);
	}
	m_OutputImageB = NULL;
}

unsigned char** CKolorDoc::malloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char **p;
	p = (unsigned char**)malloc(h * sizeof(unsigned char*));
	for (int i = 0; i < h; i++)
		p[i] = (unsigned char*)malloc(w * sizeof(unsigned char));
	return p;
}


void CKolorDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	freeInputImage(m_height);
	freeOutputImage(m_Re_height);

	CDocument::OnCloseDocument();
}
