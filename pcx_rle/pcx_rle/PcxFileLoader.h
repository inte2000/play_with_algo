#pragma once

#include "RawBmpData.h"
#include "PcxFileHeader.h"

const int PALETTE_256_SIZE = 768;

class CPcxFileLoader
{
public:
    CPcxFileLoader();
    ~CPcxFileLoader();

    bool LoadPcxFile(const char *fileName, CRawBmpData& rbd);
    const CPcxFileHeader& GetHeader() const { return m_header; }

protected:
    bool ReadFileHeader(std::ifstream& file, CPcxFileHeader& header);
    bool ReadPcxData(std::ifstream& file, CRawBmpData& rbd);
    bool DecodePcxData(BYTE *data, CRawBmpData& rbd);
    BYTE* DecodePcxLine(BYTE *source, int line, CRawBmpData& rbd);
    bool CheckSupportFormat(const CPcxFileHeader& header);

protected:
    CPcxFileHeader m_header;
};

