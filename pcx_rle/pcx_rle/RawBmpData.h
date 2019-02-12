#pragma once

#include "Patette.h"

class CRawBmpData
{
public:
    CRawBmpData();
    ~CRawBmpData();

    bool Init(int width, int height);
    void Release();
    int GetBmpWidth() const { return m_width; }
    int GetBmpHeight() const { return m_height; }
    void SetPixel(int row, int col, BYTE cidx);
    BYTE GetPixel(int row, int col);
    COLORREF GetPixelColor(int row, int col);
    void Fade(double per);
    CPatette& GetPatette() { return m_palette; }
    const CPatette& GetPatette() const { return m_palette; }
protected:
    int m_width;
    int m_height;
    BYTE *m_data;
    CPatette m_palette;
};

