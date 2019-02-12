#include "stdafx.h"
#include "RawBmpData.h"


CRawBmpData::CRawBmpData()
{
    m_width = 0;
    m_height = 0;
    m_data = nullptr;
}


CRawBmpData::~CRawBmpData()
{
    Release();
}

bool CRawBmpData::Init(int width, int height)
{
    Release();
    m_data = new BYTE[width * height];
    if (m_data != nullptr)
    {
        memset(m_data, 0, width * height * sizeof(BYTE));
        m_width = width;
        m_height = height;

        return true;
    }

    return false;
}

void CRawBmpData::Release()
{
    m_width = 0;
    m_height = 0;
    if (m_data != nullptr)
    {
        delete[] m_data;
        m_data = nullptr;
    }
    m_palette.Release();
}

void CRawBmpData::SetPixel(int row, int col, BYTE cidx) 
{
    assert(m_data != nullptr);
    m_data[row * m_width + col] = cidx;
}

BYTE CRawBmpData::GetPixel(int row, int col)
{
    assert(m_data != nullptr);
    return m_data[row * m_width + col];
}

COLORREF CRawBmpData::GetPixelColor(int row, int col)
{
    BYTE cidx = m_data[row * m_width + col];

    return m_palette.GetColor(cidx);
}

void CRawBmpData::Fade(double per)
{
    m_palette.FadePaletteData(per);
}
