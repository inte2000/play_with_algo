#include "stdafx.h"
#include "PcxFileHeader.h"


CPcxFileHeader::CPcxFileHeader()
{
    memset(&m_data, 0, sizeof(m_data));
    m_data.flag = PCX_HEADER_FLAG;
    m_data.version = PCX_VER_SUPPORT;
    m_data.bitsPrePixel = 8;
    m_data.encodeing = PCX_HEADER_ENCODE;
    m_data.planes = 1;
    m_data.paletteType = 1;
    m_data.hRes = 96;
    m_data.vRes = 96;
}


CPcxFileHeader::~CPcxFileHeader()
{
}

bool CPcxFileHeader::ReadHeader(std::ifstream& file)
{
    file.read((char *)&m_data, PCX_HEADER_SIZE);
    if (file)
    {
        if ((m_data.flag == PCX_HEADER_FLAG) && (m_data.encodeing == PCX_HEADER_ENCODE))
        {
            return true;
        }
    }

    return false;
}

bool CPcxFileHeader::WriteHeader(std::ofstream& file)
{
    file.write((const char *)&m_data, PCX_HEADER_SIZE);
    if (file)
    {
        return true;
    }

    return false;
}

void CPcxFileHeader::SetBmpWidth(int width)
{
    m_data.xMin = 0;
    m_data.xMax = width - 1;
}

void CPcxFileHeader::SetBmpHeight(int height)
{
    m_data.yMin = 0;
    m_data.yMax = height - 1;
}
