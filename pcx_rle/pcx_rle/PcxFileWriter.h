#pragma once

#include "RawBmpData.h"
#include "PcxFileHeader.h"

class CPcxFileWriter
{
public:
    CPcxFileWriter();
    ~CPcxFileWriter();

    bool SavePcxFile(const char *fileName, CRawBmpData& rbd);

protected:
    bool WriteFileHeader(std::ofstream& file, CPcxFileHeader& header);
    bool WritePcxData(std::ofstream& file, CRawBmpData& rbd);
    bool WritePaletteData(std::ofstream& file, CPatette& pal);
    bool EncodePcxData(std::ofstream& file, CRawBmpData& rbd);
    int EncodePcxLine(BYTE *buffer, int row, CRawBmpData& rbd);

};

