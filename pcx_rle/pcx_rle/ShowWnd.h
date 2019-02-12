#pragma once

#include "RawBmpData.h"

// CShowWnd

class CShowWnd : public CStatic
{
	DECLARE_DYNAMIC(CShowWnd)

public:
	CShowWnd();
	virtual ~CShowWnd();

    void SetBmpData(CRawBmpData *rbd) { m_rbd = rbd; }
    void UpdateGridWnd();

protected:
	DECLARE_MESSAGE_MAP()

    virtual void PreSubclassWindow();
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
    void DrawBmpData(CDC *pDC, const CRect& rcClient);

protected:
    CRawBmpData *m_rbd;
};



