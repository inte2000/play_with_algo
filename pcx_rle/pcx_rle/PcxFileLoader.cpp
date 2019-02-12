#include "stdafx.h"
#include "PcxFileLoader.h"


CPcxFileLoader::CPcxFileLoader()
{
}


CPcxFileLoader::~CPcxFileLoader()
{
}


bool CPcxFileLoader::LoadPcxFile(const char *fileName, CRawBmpData& rbd)
{
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (ReadFileHeader(file, m_header))
    {
        if (rbd.Init(m_header.GetBmpWidth(), m_header.GetBmpHeight()))
        {
            return ReadPcxData(file, rbd);
        }
    }

    return false;
}

bool CPcxFileLoader::ReadFileHeader(std::ifstream& file, CPcxFileHeader& header)
{
    if (file.bad())
    {
        return false;
    }
    if (!header.ReadHeader(file))
    {
        return false;
    }

    return CheckSupportFormat(header);
}

bool CPcxFileLoader::ReadPcxData(std::ifstream& file, CRawBmpData& rbd)
{
    file.seekg(0, std::ios_base::end);
    int fileSize = file.tellg();

    int dataSize = fileSize - PCX_HEADER_SIZE;
    BYTE *data = new BYTE[dataSize]; //除了文件头，剩下的部分一次性读出来
    if (data == nullptr)
    {
        return false;
    }
    file.seekg(PCX_HEADER_SIZE, std::ios_base::beg);
    file.read((char *)data, dataSize);

    BYTE *pal = data + dataSize - PALETTE_256_SIZE; //最后的768字节是256调色板
    CPatette& palette = rbd.GetPatette();
    palette.SetPaletteData(pal, 256);

    bool bSuccess = DecodePcxData(data, rbd);

    delete[] data;
    return bSuccess;
}

bool CPcxFileLoader::DecodePcxData(BYTE *data, CRawBmpData& rbd)
{
    BYTE *source = data;
    for (int i = 0; i < m_header.GetBmpHeight(); i++)
    {
        source = DecodePcxLine(source, i, rbd);
    }

    return true;
}

BYTE* CPcxFileLoader::DecodePcxLine(BYTE *source, int line, CRawBmpData& rbd)
{
    int bytes = m_header.GetBytesPreLine();
    int col = 0;
    while (bytes > 0)
    {
        if (*source > 0xc0)
        {
            int count = *source++ & 0x3f;
            BYTE c = *source++;
            bytes -= count;
            while (count > 0)
            {
                rbd.SetPixel(line, col++, c);
                count--;
            }
        }
        else
        {
            rbd.SetPixel(line, col++, *source++);
            bytes--;
        }
    }
    return source;
}

bool CPcxFileLoader::CheckSupportFormat(const CPcxFileHeader& header)
{
    if ((header.GetBitsPrePixel() == 8) 
        && (header.GetPlanes() == 1)
        && (header.GetVersion() >= PCX_VER_SUPPORT))
    {
        return true;
    }


    return false;
}