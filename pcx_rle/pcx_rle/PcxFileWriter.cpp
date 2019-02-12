#include "stdafx.h"
#include "PcxFileWriter.h"


CPcxFileWriter::CPcxFileWriter()
{
}


CPcxFileWriter::~CPcxFileWriter()
{
}

bool CPcxFileWriter::SavePcxFile(const char *fileName, CRawBmpData& rbd)
{
    CPcxFileHeader header;

    header.SetBitsPrePixel(8);
    int bytesPreLine = (rbd.GetBmpWidth() * 8 + 7) >> 3;
    if (bytesPreLine & 1)
        bytesPreLine++;

    header.SetBytesPreLine(bytesPreLine);
    header.SetBmpWidth(rbd.GetBmpWidth());
    header.SetBmpHeight(rbd.GetBmpHeight());

    std::ofstream file(fileName, std::ios::out | std::ios::binary);
    if (WriteFileHeader(file, header))
    {
        return WritePcxData(file, rbd);
    }

    return false;

}

bool CPcxFileWriter::WriteFileHeader(std::ofstream& file, CPcxFileHeader& header)
{
    return header.WriteHeader(file);
}

bool CPcxFileWriter::WritePcxData(std::ofstream& file, CRawBmpData& rbd)
{
    if (!EncodePcxData(file, rbd))
    {
        return false;
    }

    CPatette& pal = rbd.GetPatette();
    return WritePaletteData(file, pal);
}

bool CPcxFileWriter::WritePaletteData(std::ofstream& file, CPatette& pal)
{
    BYTE sig = 0x0C;
    file.write((const char *)&sig, 1); //调色板标志
    if (!file)
    {
        return false;
    }

    file.write((const char *)pal.GetPaletteData(), pal.GetPaletteCount() * BYTES_PER_PAL);
    if (file)
    {
        return true;
    }

    return false;
}

bool CPcxFileWriter::EncodePcxData(std::ofstream& file, CRawBmpData& rbd)
{
    BYTE *buf = new BYTE[rbd.GetBmpWidth() * 2]; //一行数据压缩后一般都会小于原字节数，但是偶尔也有例外
    if (buf == nullptr)
    {
        return false;
    }

    for (int row = 0; row < rbd.GetBmpHeight(); row++)
    {
        int len = EncodePcxLine(buf, row, rbd);
        file.write((const char *)buf, len);
        if (!file)
        {
            delete[] buf;
            return false;
        }
    }

    delete[] buf;
    return true;
}

int CPcxFileWriter::EncodePcxLine(BYTE *buffer, int row, CRawBmpData& rbd)
{
    BYTE *dest = buffer;

    int col = 0;
    while (col < rbd.GetBmpWidth())
    {
        int count = 0;
        BYTE c = rbd.GetPixel(row, col);
        do
        {
            count++;
            col++;
        } while ( (c == rbd.GetPixel(row, col)) && (count < 0x3f) 
                  && (col < rbd.GetBmpWidth()) );

        if (c >= 0xc0 || count > 1)
        {
            *dest++ = count | 0xc0;
        }
        *dest++ = c;
    }

    return (dest - buffer);
}
