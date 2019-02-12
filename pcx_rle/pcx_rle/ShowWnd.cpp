// GridWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ShowWnd.h"
#include "MemDC.h"


// CGridWnd

IMPLEMENT_DYNAMIC(CShowWnd, CStatic)

CShowWnd::CShowWnd()
{
    m_rbd = NULL;
}

CShowWnd::~CShowWnd()
{
}

void CShowWnd::UpdateGridWnd()
{
    if(GetSafeHwnd() != NULL)
    {
        RedrawWindow();
    }
}

BEGIN_MESSAGE_MAP(CShowWnd, CStatic)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CShowWnd::DrawBmpData(CDC *pDC, const CRect& rcClient)
{
    for (int row = 0; row < m_rbd->GetBmpHeight(); row++)
    {
        for (int col = 0; col < m_rbd->GetBmpWidth(); col++)
        {
            pDC->SetPixel(col, row, m_rbd->GetPixelColor(row, col));
        }
    }
}

// CShowWnd message handlers
void CShowWnd::OnPaint()
{
    CPaintDC dc(this); // device context for painting
	
    CRect rcClient;
	GetClientRect(rcClient);

    if (m_rbd != nullptr)
    {
        CMemoryDC memDC(&dc, &rcClient);
        DrawBmpData(&memDC, rcClient);
    }
}

BOOL CShowWnd::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
    //return CStatic::OnEraseBkgnd(pDC);
}

void CShowWnd::PreSubclassWindow()
{
    DWORD dwStyle = GetStyle();
    SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

    CStatic::PreSubclassWindow();
}

BOOL CShowWnd::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Add your specialized code here and/or call the base class

    return CStatic::PreCreateWindow(cs);
}
