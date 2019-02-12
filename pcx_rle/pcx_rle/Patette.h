#pragma once

const int BYTES_PER_PAL = 3;

class CPatette
{
public:
    CPatette();
    ~CPatette();

    COLORREF GetColor(int cidx);
    bool SetPaletteData(const BYTE *pData, int palCount);
    int GetPaletteCount() const { return m_palCount; }
    BYTE *GetPaletteData() const { return m_palData; }
    void Release();
    void FadePaletteData(double per);

protected:
    int m_palCount;
    BYTE *m_palData;
};

