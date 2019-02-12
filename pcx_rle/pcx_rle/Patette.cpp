#include "stdafx.h"
#include "Patette.h"


CPatette::CPatette()
{
    m_palData = nullptr;
    m_palCount = 0;
}


CPatette::~CPatette()
{
    Release();
}

COLORREF CPatette::GetColor(int cidx)
{
    assert(m_palData != nullptr);

    if ((cidx < 0) || (cidx >= m_palCount))
    {
        return RGB(0, 0, 0);
    }

    int pos = cidx * BYTES_PER_PAL;

    return RGB(m_palData[pos], m_palData[pos + 1], m_palData[pos + 2]);
}

bool CPatette::SetPaletteData(const BYTE *pData, int palCount)
{
    assert(m_palData == nullptr);
    m_palData = new BYTE[ palCount * BYTES_PER_PAL];
    if (m_palData != nullptr)
    {
        m_palCount = palCount;
        memcpy(m_palData, pData, palCount * BYTES_PER_PAL);
        return true;
    }

    return false;
}

void CPatette::Release()
{
    m_palCount = 0;
    if (m_palData != nullptr)
    {
        delete[] m_palData;
        m_palData = nullptr;
    }
}

void CPatette::FadePaletteData(double per)
{
    for (int i = 0; i < m_palCount; i++)
    {
        int pos = i * BYTES_PER_PAL;
        m_palData[pos] = m_palData[pos] * per;
        m_palData[pos + 1] = m_palData[pos + 1] * per;
        m_palData[pos + 2] = m_palData[pos + 2] * per;
    }
}
